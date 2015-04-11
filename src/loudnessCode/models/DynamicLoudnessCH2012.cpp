/*
 * Copyright (C) 2014 Dominic Ward <contactdominicward@CHail.com>
 *
 * This file is part of Loudness
 *
 * Loudness is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Loudness is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Loudness.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include "../thirdParty/cnpy/cnpy.h"
#include "../support/AuditoryTools.h"
#include "../modules/FrameGenerator.h"
#include "../modules/FIR.h"
#include "../modules/IIR.h"
#include "../modules/Window.h"
#include "../modules/PowerSpectrum.h"
#include "../modules/CompressSpectrum.h"
#include "../modules/WeightSpectrum.h"
#include "../modules/DoubleRoexBank.h"
#include "../modules/BinauralInhibitionMG2007.h"
#include "../modules/InstantaneousLoudness.h"
#include "../modules/ARAverager.h"
#include "DynamicLoudnessCH2012.h"

namespace loudness{

    DynamicLoudnessCH2012::DynamicLoudnessCH2012(const string& pathToFilterCoefs) :
        Model("DynamicLoudnessCH2012", true),
        pathToFilterCoefs_(pathToFilterCoefs)
    {
        configureModelParameters("faster");
    }

    DynamicLoudnessCH2012::DynamicLoudnessCH2012() :
        Model("DynamicLoudnessCH2012", true),
        pathToFilterCoefs_("")
    {
        configureModelParameters("faster");
    }

    DynamicLoudnessCH2012::~DynamicLoudnessCH2012()
    {
    }

    void DynamicLoudnessCH2012::setStartAtWindowCentre(bool startAtWindowCentre)
    {
        startAtWindowCentre_ = startAtWindowCentre;
    }
    
    void DynamicLoudnessCH2012::setUseDiffuseFieldResponse(bool useDiffuseFieldResponse)
    {
        useDiffuseFieldResponse_ = useDiffuseFieldResponse;
    }

    void DynamicLoudnessCH2012::setDioticPresentation(bool dioticPresentation)
    {
        dioticPresentation_ = dioticPresentation;
    }

    void DynamicLoudnessCH2012::setOutputSpecificLoudness(bool outputSpecificLoudness)
    {
        outputSpecificLoudness_ = outputSpecificLoudness;
    }

    void DynamicLoudnessCH2012::setInhibitSpecificLoudness(bool inhibitSpecificLoudness)
    {
        inhibitSpecificLoudness_ = inhibitSpecificLoudness;
    }

    void DynamicLoudnessCH2012::setSampleSpectrumUniformly(bool sampleSpectrumUniformly)
    {
        sampleSpectrumUniformly_ = sampleSpectrumUniformly;
    }

    void DynamicLoudnessCH2012::setFilterSpacing(Real filterSpacing)
    {
        filterSpacing_ = filterSpacing;
    }

    void DynamicLoudnessCH2012::setCompressionCriterion(Real compressionCriterion)
    {
        compressionCriterion_ = compressionCriterion;
    }

    void DynamicLoudnessCH2012::setPathToFilterCoefs(string pathToFilterCoefs)
    {
        pathToFilterCoefs_ = pathToFilterCoefs;
    }

    void DynamicLoudnessCH2012::configureModelParameters(const string& setName)
    {
        //common to all
        setRate(1000);
        setUseDiffuseFieldResponse(false);
        setSampleSpectrumUniformly(true);
        setOutputSpecificLoudness(true);
        setInhibitSpecificLoudness(true);
        setDioticPresentation(true);
        setFilterSpacing(0.1);
        setCompressionCriterion(0.0);
        setStartAtWindowCentre(true);
        attackTimeSTL_ = 0.016;
        releaseTimeSTL_ = 0.032;
        attackTimeLTL_ = 0.01;
        releaseTimeLTL_ = 2.0;

        if (setName == "faster")
        {
            setFilterSpacing(0.25);
            setCompressionCriterion(0.3);
            LOUDNESS_DEBUG(name_ << ": using a filter spacing of 0.25 Cams"
                   << " with 0.3 Cam spectral compression criterion.");
        }
        else if (setName != "CH2012")
        {
            configureModelParameters("CH2012");
            LOUDNESS_DEBUG(name_ << "Using Settings from Chen and Hu 2012 paper.");
        }
    }

    bool DynamicLoudnessCH2012::initializeInternal(const SignalBank &input)
    {
        //if filter coefficients have not been provided
        //use spectral weighting to approximate outer and middle ear response
        if(!pathToFilterCoefs_.empty())
        {
            //load numpy array holding the filter coefficients
            cnpy::NpyArray arr = cnpy::npy_load(pathToFilterCoefs_);
            Real *data = reinterpret_cast<Real*> (arr.data);

            //check if filter is IIR or FIR
            bool iir = false;
            if(arr.shape[0]==2)
                iir = true;

            //load the coefficients
            RealVec bCoefs, aCoefs;
            for(unsigned int i=0; i<arr.shape[1];i++)
            {
                bCoefs.push_back(data[i]);
                if(iir)
                    aCoefs.push_back(data[i+arr.shape[1]]);
            }
            
            //create module
            if(iir)
            {
                modules_.push_back(unique_ptr<Module> 
                        (new IIR(bCoefs, aCoefs))); 
                outputNames_.push_back("IIR");
            }
            else
            {
                modules_.push_back(unique_ptr<Module>
                        (new FIR(bCoefs))); 
                outputNames_.push_back("FIR");
            }

            //clean up
            delete [] data;
        }

        /*
         * Multi-resolution spectrogram
         */
        RealVec bandFreqsHz {10, 80, 500, 1250, 2540, 4050, 16001};

        //window spec
        RealVec windowSizeSecs {0.128, 0.064, 0.032, 0.016, 0.008, 0.004};
        vector<int> windowSizeSamples(6,0);
        //round to nearest sample and force to be even such that centre samples
        //are aligned.
        for(int w=0; w<6; w++)
        {
            windowSizeSamples[w] = (int)round(windowSizeSecs[w] * input.getFs());
            windowSizeSamples[w] += windowSizeSamples[w]%2;
        }
        
        //Frame generator
        int hopSize = round(input.getFs() / rate_);
        modules_.push_back(unique_ptr<Module> 
                (new FrameGenerator(windowSizeSamples[0], hopSize, startAtWindowCentre_)));
        outputNames_.push_back("FrameGenerator");
        
        //configure windowing: Periodic hann window
        modules_.push_back(unique_ptr<Module>
                (new Window("hann", windowSizeSamples, true)));
        outputNames_.push_back("HannWindows");

        //power spectrum
        modules_.push_back(unique_ptr<Module> 
                (new PowerSpectrum(bandFreqsHz, windowSizeSamples, sampleSpectrumUniformly_))); 
        outputNames_.push_back("PowerSpectrum");

        /*
         * Compression
         */
        if(compressionCriterion_ > 0)
        {
            modules_.push_back(unique_ptr<Module>
                    (new CompressSpectrum(compressionCriterion_))); 
            outputNames_.push_back("CompressedPowerSpectrum");
        }

        /*
         * Spectral weighting
         */
        if(pathToFilterCoefs_.empty())
        {
            string middleEar = "CHGM2011";
            string outerEar = "ANSIS342007_FREEFIELD";
            if(useDiffuseFieldResponse_)
                outerEar = "ANSIS342007_DIFFUSEFIELD";

            modules_.push_back(unique_ptr<Module> 
                    (new WeightSpectrum(middleEar, outerEar))); 
            outputNames_.push_back("WeightedPowerSpectrum");
        }

        /*
         * Roex filters
         */

        // Set up scaling factors depending on output config
        Real doubleRoexBankfactor, instantaneousLoudnessFactor;
        if (outputSpecificLoudness_)
        {
            doubleRoexBankfactor = 1.53e-8;
            instantaneousLoudnessFactor = 1.0;
            outputNames_.push_back("SpecificLoudnessPattern");
            LOUDNESS_DEBUG(name_ << ": Excitation pattern will be scaled for specific loudness");
        }
        else
        {
            doubleRoexBankfactor = 1.0;
            instantaneousLoudnessFactor = 1.53e-8;
            outputNames_.push_back("ExcitationPattern");
        }

        bool usingBinauralInhibition = inhibitSpecificLoudness_ *
            (input.getNEars() == 2) * outputSpecificLoudness_;
        if (usingBinauralInhibition)
            doubleRoexBankfactor /= 0.75;

        modules_.push_back(unique_ptr<Module> (new DoubleRoexBank(1.5, 40.2,
                        filterSpacing_, doubleRoexBankfactor)));

        /*
         * Binaural inhibition
         */
        if (usingBinauralInhibition)
        {
            modules_.push_back(unique_ptr<Module> (new BinauralInhibitionMG2007));
            outputNames_.push_back("InhibitedSpecificLoudnessPattern");
        }
        else
        {
            LOUDNESS_DEBUG(name_ << ": No binaural inhibition.");
        }
        
        /*
        * Instantaneous loudness
        */   
        modules_.push_back(unique_ptr<Module>
                (new InstantaneousLoudness(instantaneousLoudnessFactor, dioticPresentation_)));
        outputNames_.push_back("InstantaneousLoudness");

        /*
         * Short-term loudness
         */
        modules_.push_back(unique_ptr<Module>
                (new ARAverager(attackTimeSTL_, releaseTimeSTL_)));
        outputNames_.push_back("ShortTermLoudness");

        /*
         * Long-term loudness
         */
        modules_.push_back(unique_ptr<Module>
                (new ARAverager(attackTimeLTL_, releaseTimeLTL_)));
        outputNames_.push_back("LongTermLoudness");
        
        //configure targets
        configureLinearTargetModuleChain();

        return 1;
    }
}

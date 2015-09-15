/*
 * Copyright (C) 2014 Dominic Ward <contactdominicward@gmail.com>
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

#include "FastRoexBank.h"
#include "../support/AuditoryTools.h"

namespace loudness{

    FastRoexBank::FastRoexBank(Real camStep,
            bool isExcitationPatternInterpolated,
            bool isInterpolationCubic) :
        Module("FastRoexBank"),
        camStep_(camStep),
        isExcitationPatternInterpolated_(isExcitationPatternInterpolated),
        isInterpolationCubic_(isInterpolationCubic)
    {}

    FastRoexBank::~FastRoexBank() {}

    bool FastRoexBank::initializeInternal(const SignalBank &input)
    {
        //Camstep limit is 0.1
        if(camStep_ <= 0.1)
            isExcitationPatternInterpolated_ = false;
        
        /*
         * Level per ERB precalculations
         */
        rectBinIndices_.resize(input.getNChannels());

        for (int i = 0; i < input.getNChannels(); ++i)
        {
            //ERB number of Centre frequency
            Real cam = hertzToCam (input.getCentreFreq(i));

            //rectangular ERB band edges in Hz
            Real freqLo = camToHertz (cam - 0.5);
            Real freqHi = camToHertz (cam + 0.5);

            //lower and upper bin indices
            rectBinIndices_[i].resize(2);
            rectBinIndices_[i][0] = i;
            rectBinIndices_[i][1] = i + 1;

            /* Find components falling within the band:
             * This follows the Fortran code in Glasberg and Moore's 1990 paper
             * which uses the inclusive interval [fLo, fHi].  An alternative
             * approach is to find the nearest DFT bins to the lower and upper
             * band edges, which would require a nearest search (bins may not be
             * uniformly spaced). Decided to go with the first prodedure for
             * simplicity and follow original code.
             */
            bool first = true;
            int j = 0;
            while (j < input.getNChannels())
            {
                if (input.getCentreFreq(j) > freqHi) 
                    break;
                else if (input.getCentreFreq(j) >= freqLo)
                {
                    if(first)
                        rectBinIndices_[i][0] = j;
                    first = false;
                    rectBinIndices_[i][1] = j + 1;
                }
                j++;
            }
        }	

        /*
         * Excitation pattern variables
         */

        //number of roex filters to use
        Real camLo = 1.8;
        Real camHi = 38.9;
        nFilters_ = std::floor((camHi - camLo) / camStep_) + 1;

        LOUDNESS_DEBUG(name_
                << ": interpolation applied: " << isExcitationPatternInterpolated_
                << " filter spacing in Cams: " << camStep_
                << " Total number of filters: " << nFilters_);

        //see ANSI S3.4 2007 p.11
        const Real p51_1k = 4000.0 / centreFreqToCambridgeERB (1000.0);

        //p upper is level invariant
        pu_.assign (nFilters_, 0.0);
        
        //p lower is level dependent
        pl_.assign (nFilters_, 0.0);

        //comp_level holds level per ERB on each component
        compLevel_.assign (input.getNChannels(), 0.0);

        //centre freqs in Hz
        fc_.assign (nFilters_, 0.0);

        //initialize output SignalBank
        if (isExcitationPatternInterpolated_)
        {
            //centre freqs in cams
            cams_.assign (nFilters_, 0.0);

            //required for log interpolation
            excitationLevel_.assign (nFilters_, 0.0);

            //372 filters over [1.8, 38.9] in 0.1 steps
            output_.initialize (input.getNEars(), 372, 1, input.getFs());
            output_.setChannelSpacingInCams (0.1);
            for (int i = 0; i < 372; ++i)
                output_.setCentreFreq (i, camToHertz (1.8 + i * 0.1));
        }
        else
        {
            output_.initialize (input.getNEars(), nFilters_, 1, input.getFs());
            output_.setChannelSpacingInCams (camStep_);
        }
        output_.setFrameRate (input.getFrameRate());

        //fill the above arrays and calculate roex filter response for upper skirt
        for (int i = 0; i < nFilters_; ++i)
        {
            //filter frequency in Cams
            Real cam = camLo + (i * camStep_);

            //filter frequency in Hz
            fc_[i] = camToHertz (cam);

            if (isExcitationPatternInterpolated_)
                cams_[i] = cam;
            else
                output_.setCentreFreq (i, fc_[i]); //some redundancy here

            //get the ERB of the filter
            Real erb = centreFreqToCambridgeERB (fc_[i]);
            //ANSI S3.4 sec 3.5 p.11
            pu_[i] = 4.0 * fc_[i] / erb;
            //from Eq (3)
            pl_[i] = 0.35 * (pu_[i] / p51_1k);
        }
        
        //generate lookup table for rounded exponential
        generateRoexTable(1024);
        
        return 1;
    }

    void FastRoexBank::processInternal(const SignalBank &input)
    {
        for (int ear = 0; ear < input.getNEars(); ++ear)
        {
            /*
             * Part 1: Obtain the level per ERB about each input component
             */
            int nChannels = input.getNChannels();
            const Real* inputPowerSpectrum = input.getSingleSampleReadPointer (ear, 0);
            Real* outputExcitationPattern = output_.getSingleSampleWritePointer (ear, 0);

            Real runningSum = 0.0;
            int j = 0;
            int k = rectBinIndices_[0][0];
            for (int i = 0; i < nChannels; ++i)
            {
                //running sum of component powers
                while (j < rectBinIndices_[i][1])
                    runningSum += inputPowerSpectrum[j++];

                //subtract components outside the window
                while (k < rectBinIndices_[i][0])
                    runningSum -= inputPowerSpectrum[k++];

                //convert to dB, subtract 51 here to save operations later
                compLevel_[i] = powerToDecibels (runningSum, 1e-10, -100.0) - 51;
            }

            /*
             * Part 2: Complete roex filter response and compute excitation per ERB
             */
            Real g = 0.0, p = 0.0, pg = 0.0, excitationLin = 0.0;
            int idx = 0;
            for (int i = 0; i < nFilters_; ++i)
            {
                excitationLin = 0.0;
                j = 0;

                while (j < nChannels)
                {
                    //normalised deviation
                    g = (input.getCentreFreq(j) - fc_[i]) / fc_[i];

                    if (g > 2)
                        break;
                    if (g < 0) //lower skirt - level dependent
                    {
                        //Complete Eq (3)
                        p = pu_[i] - (pl_[i] * compLevel_[j]); //51dB subtracted above
                        p = max(p, 0.1); //p can go negative for very high levels
                        pg = -p * g; //p * abs (g)
                    }
                    else //upper skirt
                    {
                        pg = pu_[i] * g; //p * abs(g)
                    }
                    
                    //excitation
                    idx = (int)(pg / step_ + 0.5);
                    idx = min (idx, roexIdxLimit_);
                    excitationLin += roexTable_[idx] * inputPowerSpectrum[j++]; 
                }

                //excitation level
                if (isExcitationPatternInterpolated_)
                    excitationLevel_[i] = log (excitationLin + 1e-10);
                else
                    outputExcitationPattern[i] = excitationLin;
            }

            /*
             * Part 3: Interpolate to estimate 
             * 0.1~Cam res excitation pattern
             */
            if (isExcitationPatternInterpolated_)
            {
                spline_.set_points (cams_,
                        excitationLevel_,
                        isInterpolationCubic_);
                for (int i = 0; i < 372; ++i)
                {
                    excitationLin = exp (spline_ (1.8 + i * 0.1));
                    outputExcitationPattern[i] = excitationLin;
                }
            }
        }
    }

    void FastRoexBank::resetInternal(){};

    void FastRoexBank::generateRoexTable(int size)
    {
        size = max (size, 512);
        roexIdxLimit_ = size - 1;
        roexTable_.resize (size);

        double pgLim = 20.48; //end value is 20.46
        double pg;
        step_ = pgLim / size;
        
        for (int i = 0; i < size; ++i)
        {
            pg = step_ * i;
            roexTable_[i] = (1 + pg) * exp (-pg);
        }
    }
}


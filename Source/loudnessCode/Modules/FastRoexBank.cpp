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
#include "../Support/AuditoryTools.h"

namespace loudness{

    FastRoexBank::FastRoexBank(Real camStep, bool interp) :
        Module("FastRoexBank"),
        camStep_(camStep),
        interp_(interp)
    {}

    FastRoexBank::~FastRoexBank() {}

    bool FastRoexBank::initializeInternal(const SignalBank &input)
    {


        //Camstep limit is 0.1
        if(camStep_ <= 0.1)
            interp_ = false;
        /*
         * Level per ERB precalculations
         */
        rectBinIndices_.resize(input.getNChannels());

        for(int i=0; i<input.getNChannels(); i++)
        {
            //ERB number of Centre frequency
            Real cam = FreqToCam(input.getCentreFreq(i));

            //rectangular ERB band edges in Hz
            Real freqLo = CamToFreq(cam-0.5);
            Real freqHi = CamToFreq(cam+0.5);

            //lower and upper bin indices
            rectBinIndices_[i].resize(2);
            rectBinIndices_[i][0] = i;
            rectBinIndices_[i][1] = i+1;

            //sum components falling within the filter
            bool first = true;
            int j=0;
            while(j<input.getNChannels())
            {
                if(input.getCentreFreq(j)>freqHi) 
                    break;
                else if(input.getCentreFreq(j)>=freqLo)
                {
                    if(first)
                        rectBinIndices_[i][0] = j;
                    first = false;
                    rectBinIndices_[i][1] = j+1;
                }
                j++;
            }
        }	

        /*
         * Excitation pattern variables
         */

        //number of roex filters to use
        //+1 inclusive, can exceed end value if fractional part of 
        //argument to round is >=0.5
        Real camLo = 1.8;
        Real camHi = 38.9;
        nFilters_ = round((camHi-camLo)/camStep_)+1; 

        const Real p51_1k = 4000 / FreqToERB(1000.0);

        //p upper is level invariant
        pu_.assign(nFilters_, 0.0);
        
        //p lower is level dependent
        pl_.assign(nFilters_, 0.0);

        //comp_level holds level per ERB on each component
        compLevel_.assign(input.getNChannels(), 0.0);

        //required for log interpolation
        if(interp_)
            excitationLevel_.assign(nFilters_, 0.0);
        
        //centre freqs in cams
        cams_.assign(nFilters_, 0);

        //centre freqs in Hz
        fc_.assign(nFilters_, 0);

        //initialize output SignalBank
        if(interp_)
        {
            output_.initialize(372, 1, input.getFs());
            for(int i=0; i<372; i++)
            {
                output_.setCentreFreq(i, CamToFreq(1.8 + i*0.1));
                LOUDNESS_DEBUG("FastRoexBank: Centre freq: " 
                        << output_.getCentreFreq(i));
            }
        }
        else
        {
            output_.initialize(nFilters_, 1, input.getFs());
        }
        output_.setFrameRate(input.getFrameRate());

        //fill the above arrays and calculate roex filter response for upper skirt
        Real erb;
        for(int i=0; i<nFilters_; i++)
        {
            cams_[i] = camLo+(i*camStep_);
            fc_[i] = CamToFreq(cams_[i]);
            if(!interp_)
                output_.setCentreFreq(i, fc_[i]); //some redundancy here
            erb = FreqToERB(fc_[i]);
            pu_[i] = 4*fc_[i]/erb;
            pl_[i] = 0.35*(pu_[i]/p51_1k);
        }
        
        //generate lookup table for rounded exponential
        generateRoexTable(1024);
        
        return 1;
    }


    void FastRoexBank::processInternal(const SignalBank &input)
    {
        /*
         * Part 1: Obtain the level per ERB about each input component
         */
        Real runningSum = 0;
        int j = 0;
        int k = rectBinIndices_[0][0];
        int nChannels = input.getNChannels();
        for(int i=0; i<nChannels; i++)
        {
            //running sum of component powers
            while(j<rectBinIndices_[i][1])
                runningSum += input.getSample(j++,0);

            //subtract components outside the window
            while(k<rectBinIndices_[i][0])
                runningSum -= input.getSample(k++,0);

            //convert to dB, subtract 51 here to save operations later
            if (runningSum < 1e-10)
                compLevel_[i] = -151.0;
            else
                compLevel_[i] = 10*log10(runningSum)-51;

            LOUDNESS_DEBUG("FastRoexBank: ERB/dB : " << compLevel_[i]+1e-10);
        }

        /*
         * Part 2: Complete roex filter response and compute excitation per ERB
         */
        Real g, p, pg, excitationLin;
        int idx;
        for(int i=0; i<nFilters_; i++)
        {
            excitationLin = 0;
            j = 0;

            while(j<nChannels)
            {
                //normalised deviation
                g = (input.getCentreFreq(j)-fc_[i])/fc_[i];

                if(g>2)
                    break;
                if(g<0) //lower skirt - level dependent
                {
                    p = pu_[i]-(pl_[i]*compLevel_[j]); //51dB subtracted above
                    p = p < 0.1 ? 0.1 : p; //p can go negative for very high levels
                    pg = -p*g; 
                }
                else //upper skirt
                {
                    pg = pu_[i]*g; 
                }
                
                //excitation
                idx = (int)(pg/step_ + 0.5);
                idx = idx > roexIdxLimit_ ? roexIdxLimit_ : idx;
                excitationLin += roexTable_[idx]*input.getSample(j++,0); 
            }

            //excitation level
            if(interp_)
                excitationLevel_[i] = log(excitationLin + 1e-10);
            else
                output_.setSample(i, 0, excitationLin);
        }

        /*
         * Part 3: Interpolate to estimate 
         * 0.1~Cam res excitation pattern
         */
        if(interp_)
        {
            spline_.set_points(cams_, excitationLevel_);
            for(int i=0; i < 372; i++)
            {
                excitationLin = exp(spline_(1.8 + i*0.1));
                output_.setSample(i, 0, excitationLin);
            }
        }
    }

    void FastRoexBank::resetInternal(){};

    void FastRoexBank::generateRoexTable(int size)
    {
        size = size < 512 ? 512 : size;
        roexIdxLimit_ = size-1;
        roexTable_.resize(size);

        double pgLim = 20.48; //end value is 20.46
        double pg;
        step_ = pgLim / size;
        
        for(int i=0; i<size; i++)
        {
            pg = step_*i;
            roexTable_[i] = (1+pg) * exp(-pg);
        }
    }
}


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

#include "IIR.h"

namespace loudness{

    IIR::IIR() : Module("IIR") {};

    IIR::IIR(const RealVec &bCoefs, const RealVec &aCoefs) :
        Module("IIR")
    {
        setBCoefs(bCoefs);
        setACoefs(aCoefs);
    }

    IIR::~IIR()
    {
    }

    bool IIR::initializeInternal(const SignalBank &input)
    {
        //constants
        uint n_b = bCoefs_.size();
        uint n_a = aCoefs_.size();
        if(n_b*n_a > 0)
        {
            if(n_b > n_a)
            {
                aCoefs_.resize(n_b,0);
                order_ = n_b-1;
            }
            else
            {
                bCoefs_.resize(n_b,0);
                order_ = n_a-1;
            }

            LOUDNESS_DEBUG("IIR: Filter order is: " << order_);
            orderMinus1_ = order_-1;

            //Normalise coefficients if a[0] != 1
            normaliseCoefs();

            //internal delay line - single vector for all ears
            z_.assign(input.getNEars()*order_, 0.0);

            //output SignalBank
            output_.initialize(input);

            return 1;
        }
        {
            LOUDNESS_ERROR(name_ << ": No filter coefficients");
            return 0;
        }
    }

    void IIR::processInternal(const SignalBank &input)
    {
        for(int ear=0; ear<input.getNEars(); ear++)
        {
            int smp, j;
            const Real* inputSignal = input.getSignalReadPointer(ear, 0);
            Real* outputSignal = output_.getSignalWritePointer(ear, 0);
            Real* z = &z_[ear * order_];
            Real x;

            for(smp=0; smp<input.getNSamples(); smp++)
            {
                //input sample
                x = inputSignal[smp] * gain_;

                //output sample
                outputSignal[smp] = bCoefs_[0] * x + z[0];

                //fill delay
                for (j=1; j<order_; j++)
                    z[j-1] = bCoefs_[j] * x + z[j];
                z[orderMinus1_] = bCoefs_[order_] * x;

                for (j=1; j<order_; j++)
                    z[j-1] -= aCoefs_[j] * outputSignal[smp];
                z[orderMinus1_] -= aCoefs_[order_] * outputSignal[smp];
            }
        }
    }

    void IIR::resetInternal()
    {
        resetDelayLine();
    }
}

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

#ifndef FIR_H
#define FIR_H

#include "../Support/Filter.h"

/*
 * =====================================================================================
 *        Class:  FIR
 *  Description:  Performs FIR filtering of an input SignalBank using direct form 2.
 *
 * =====================================================================================
 */

namespace loudness{

    class FIR : public Module, public Filter
    {
        public:

            FIR();
            FIR(const RealVec &bCoefs);

            virtual ~FIR();

        private:

            virtual bool initializeInternal(const SignalBank &input);
            /*
            *--------------------------------------------------------------------------------------
            *       Class:  FIR
            *      Method:  FIR :: ProcessInternal
            * Description:  Performs FIR filtering of the input SignalBank.
            *               Filtered data is stored in the output SignalBank.
            *  Parameters:  input:  The SignalBank to be filtered.
            *--------------------------------------------------------------------------------------
            */
            virtual void processInternal(const SignalBank &input);
            virtual void resetInternal();

    };
}

#endif


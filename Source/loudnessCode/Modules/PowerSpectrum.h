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

#ifndef POWERSPECTRUM_H
#define POWERSPECTRUM_H

#include <fftw3.h>
#include "../Support/Module.h"

namespace loudness{

    /**
     * @class PowerSpectrum
     * @brief Computes the power spectrum of an input SignalBank.  
     *
     * A multi-resolution power spectrum can be obtained by constructing the
     * object with a vector of non-overlapping frequency bands and a vector of
     * window lengths corresponding to each band. The band edges should be
     * specified in Hz and the window sizes in in seconds.
     *
     * For example:
     *  RealVec bandFreqs{20, 100, 500};
     *  RealVec windowSpec{0.064, 0.032};
     *  PowerSpectrum object(bandFreqs, windowSpec, true)
     *
     * Will construct a PowerSpectrum object which uses a 64ms window for all
     * frequency bins in the interval [20, 100) and a 32ms window for all bins
     * in the interval [100, 500). Thus the input SignalBank should hold a 64ms
     * frames worth of input samples. The windows are all time-aligned at their
     * centre points. The booleon argument corresponds to whether uniform
     * spectral sampling is used (default is true). If uniform is false, the per
     * band spectrum is sampled non-uniformly at intervals corresponding to
     * fs/windowSize. Casual zero padding is applied when the internally
     * calculated FFT size is greater than the window size (powers of two).
     *
     * In the current implementation, a Hann window is applied to all segments
     * and both DC and Nyquist are not computed.
     *
     * Each spectrum is scaled such that the sum of component powers in a given
     * band equals the average power in that band (see
     * http://www.dadisp.com/webhelp/dsphelp.htm#mergedprojects/refman2/SPLGROUP/POWSPEC.htm).
     *
     * @todo Develop window class to allow for more functions.
     *
     * @author Dominic Ward
     *
     * @sa FrameGenerator
     */
    class PowerSpectrum: public Module
    {
    public:

        /**
         * @brief Constructs a PowerSpectrum object.
         *
         * @param bandFreqsHz A vector of consecutive band edges in Hz.
         * @param windowSizeSecs A vector of window lengths for each band in ms.
         * @param uniform true for uniform spectral sampling, false otherwise.
         */
        PowerSpectrum(const RealVec& bandFreqsHz, const RealVec& windowSizeSecs, bool uniform);

        virtual ~PowerSpectrum();

    private:

        virtual bool initializeInternal(const SignalBank &input);

        virtual void processInternal(const SignalBank &input);

        virtual void resetInternal();

        void hannWindow(RealVec &w, int fftSize);

        RealVec bandFreqsHz_, windowSizeSecs_;
        bool uniform_;
        int nWindows_;
        Real temporalCentre_;
        Real *fftInputBuf_, *fftOutputBuf_;
        vector<int> windowSizeSamps_, fftSize_, windowDelay_;
        vector<fftw_plan> fftPlans_;
        RealVecVec windows_;
        vector<vector<int> > bandBinIndices_; 
    };
}

#endif


#include "SPLMeter.h"
#include <cmath>

SPLMeter::SPLMeter(SPLMeter::Integrator integrator, 
                   double reference,
                   int numBlocksToAverage)
      : ref_ (reference * reference),
        numBlocksToAverage_(numBlocksToAverage),
        isRunningSumActive_(false),
        isAverageReady_(false)
{
    switch (integrator)
    {
        case SLOW:
            attackTime_ = 1.0;
            releaseTime_ = 1.0;
        case FAST:
            attackTime_ = 0.125;
            releaseTime_ = 0.125;
        case IMPULSE:
            attackTime_ = 0.035;
            releaseTime_ = 1.500;
        default:
            attackTime_ = 1.0;
            releaseTime_ = 1.0;
    }

};

void SPLMeter::initialize (const loudness::SignalBank& input)
{
    int fs = input.getFs();
    attackCoefficient_ = 1 - exp ( -1.0 / (fs * attackTime_) );
    releaseCoefficient_ = 1 - exp ( -1.0 / (fs * releaseTime_) );

    yPrevs_.assign (input.getNEars(), 0.0);
    runningSums_.assign (input.getNEars(), 0.0);
    averageLevels_.assign(input.getNEars(), 0.0);

    numBlocksSummed_ = 0;
    isRunningSumActive_ = false;
    isAverageReady_ = false;
}

void SPLMeter::process(const loudness::SignalBank& input)
{
    earAverage_ = 0.0;
    for (int ear = 0; ear < input.getNEars(); ++ear)
    {
        const loudness::Real* ptr = input.getSignalReadPointer(ear, 0, 0);

        for (int smp = 0; smp < input.getNSamples(); smp++)
        {
            //square
            double x = ptr[smp] * ptr[smp];

            //average
            if (x > yPrevs_[ear])
                yPrevs_[ear] = attackCoefficient_ * (x - yPrevs_[ear]) + yPrevs_[ear];
            else
                yPrevs_[ear] = releaseCoefficient_ * (x - yPrevs_[ear]) + yPrevs_[ear];
        }

        earAverage_ += yPrevs_[ear];

        if (isRunningSumActive_)
            runningSums_[ear] += yPrevs_[ear];
    }

    earAverage_ /= input.getNEars();

    if (isRunningSumActive_)
    {
        numBlocksSummed_++;
        if (numBlocksSummed_ == numBlocksToAverage_)
        {
            for (int ear = 0; ear < input.getNEars(); ++ear)
            {
                averageLevels_[ear] = 10 * log10 ((runningSums_[ear] + 1e-10) 
                                     / (numBlocksToAverage_ * ref_));
                runningSums_[ear] = 0.0;
            }

            isRunningSumActive_ = false;
            isAverageReady_ = true;
            numBlocksSummed_ = 0;
        }
    }
}

double SPLMeter::getLevel()
{
    return 10 * log10 ((earAverage_ + 1e-10) / ref_);
}

void SPLMeter::setRunningSumActive(bool isRunningSumActive)
{
    isRunningSumActive_ = isRunningSumActive;
}

bool SPLMeter::isRunningSumActive() const
{
    return isRunningSumActive_;
}

bool SPLMeter::isAverageReady() const
{
    return isAverageReady_;
}

void SPLMeter::setAverageReady (bool isAverageReady)
{
    isAverageReady_ = isAverageReady;
}

void SPLMeter::setNumBlocksToAverage (int numBlocksToAverage)
{
    numBlocksToAverage_ = numBlocksToAverage;
}

double SPLMeter::getAverageLevel (int earIdx) const
{
    return averageLevels_[earIdx];
}

void SPLMeter::reset()
{
    yPrevs_.assign (yPrevs_.size(), 0.0);
    runningSums_.assign (runningSums_.size(), 0.0);
    averageLevels_.assign(averageLevels_.size(), 0.0);
    numBlocksSummed_ = 0;
    isRunningSumActive_ = false;
    isAverageReady_ = false;
}

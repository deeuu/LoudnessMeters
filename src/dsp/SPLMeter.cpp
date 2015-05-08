#include "SPLMeter.h"
#include <cmath>

SPLMeter::SPLMeter(SPLMeter::Integrator integrator, float reference)
      : ref_ (reference * reference)
{
    switch (integrator)
    {
        case SLOW:
            attackTime_ = 1000.0f;
            releaseTime_ = 1000.0f;
        case FAST:
            attackTime_ = 125.0f;
            releaseTime_ = 125.0f;
        case IMPULSE:
            attackTime_ = 35.0f;
            releaseTime_ = 1500.0f;
        default:
            attackTime_ = 1000.0f;
            releaseTime_ = 1000.0f;
    }
};

void SPLMeter::initialize (const loudness::SignalBank& input)
{
    int fs = input.getFs();
    attackCoefficient_ = 1 - exp ( -1.0 / (fs * attackTime_) );
    releaseCoefficient_ = 1 - exp ( -1.0 / (fs * releaseTime_) );

    output_.initialize(input.getNEars(), 1, 1, fs);
}

void SPLMeter::process(const loudness::SignalBank& input)
{
    for (int ear = 0; ear < input.getNEars(); ++ear)
    {
        const loudness::Real* ptr = input.getSignalReadPointer(ear, 0, 0);
        loudness::Real* out = output_.getSignalWritePointer(ear, 0, 0);

        for (int smp = 0; smp < input.getNSamples(); smp++)
        {
            //square
            loudness::Real x = ptr[smp] * ptr[smp];

            //average
            if (x > out[0])
                out[0] = attackCoefficient_ * (x - out[0]) + out[0];
            else
                out[0] = releaseCoefficient_ * (x - out[0]) + out[0];
        }
    }
}

loudness::Real SPLMeter::getLevel(int earIdx)
{
    return 10 * log10 ((output_.getSample(earIdx, 0, 0) + 1e-10) / ref_);
}

loudness::Real SPLMeter::getAverageLevel()
{
    loudness::Real avg = 0.0f;
    for (int ear = 0; ear < output_.getNEars(); ++ear)
    {
        avg = output_.getSample(ear, 0, 0);
    }
    avg /= output_.getNEars();

    return 10 * log10 ((avg+ 1e-10) / ref_);
}

void SPLMeter::reset()
{
    output_.reset();
}

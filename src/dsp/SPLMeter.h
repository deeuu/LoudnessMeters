#ifndef SPLMETER_H
#define SPLMETER_H 

#include "../loudnessCode/support/SignalBank.h"

class SPLMeter
{
public:

    enum Integrator{
        SLOW,
        FAST,
        IMPULSE
    };

    SPLMeter (SPLMeter::Integrator integrator, float reference = 2e-5);
    ~SPLMeter(){};

    void initialize (const loudness::SignalBank& input);

    void process (const loudness::SignalBank& input);

    loudness::Real getLevel(int earIdx);
    loudness::Real getAverageLevel();

    void reset();

private:
    float attackTime_, releaseTime_;
    float attackCoefficient_, releaseCoefficient_;
    float ref_;
    loudness::SignalBank output_;
};

#endif

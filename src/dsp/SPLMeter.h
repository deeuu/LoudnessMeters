#ifndef SPLMETER_H
#define SPLMETER_H 

#include <vector>
#include "../loudnessCode/support/SignalBank.h"

class SPLMeter
{
public:

    enum Integrator{
        SLOW,
        FAST,
        IMPULSE
    };

    SPLMeter (SPLMeter::Integrator integrator,
              double reference = 2e-5,
              int numBlocksToAverage = 100);
    ~SPLMeter(){};

    void initialize (const loudness::SignalBank& input);

    void process (const loudness::SignalBank& input);

    double getLevel();

    double getAverageLevel (int earIdx) const;

    bool isRunningSumActive() const;

    bool isAverageReady() const;

    void setRunningSumActive (bool isRunningSumActive);

    void setAverageReady (bool isAverageReady);

    void setNumBlocksToAverage (int numBlocksToAverage);

    void reset();

private:
    double attackTime_, releaseTime_;
    double attackCoefficient_, releaseCoefficient_;
    double ref_;
    double earAverage_;
    bool isRunningSumActive_, isAverageReady_;
    int numBlocksSummed_, numBlocksToAverage_;
    std::vector<double> yPrevs_, runningSums_, averageLevels_;
};

#endif

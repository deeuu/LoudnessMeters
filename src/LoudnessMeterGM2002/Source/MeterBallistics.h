#ifndef METER_BALLISTICS_H_INCLUDED
#define METER_BALLISTICS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MeterBallistics : private Timer
{
public:
    //==========================================================================
    //      Constructor and Destructor
    //==========================================================================
    MeterBallistics (unsigned int numMetersInit, double minLevelInit, double maxLevelInit, bool clipToRangeInit = true);
    virtual ~MeterBallistics();

    //==========================================================================
    //      Get and Set Level
    //==========================================================================
    void setMeterLevel (unsigned int index, double newLevel);
    double getMeterLevel (unsigned int index);
    double getMeterTargetLevel (unsigned int index);

    //==========================================================================
    //      Set Meter Range
    //==========================================================================
    void setNumMeters (unsigned int newNumMeters);
    void setMeterRange (double newMinLevel, double newMaxLevel);
    void setClipToRange (bool newValue);

    //==========================================================================
    //      Set the time it takes for the meter to rise and fall its full range
    //==========================================================================
    void setMeterRiseTime (unsigned int index, unsigned int fullScaleRiseTimeInMilliseconds);
    void setMeterDecayTime (unsigned int index, unsigned int fullScaleDecayTimeInMilliseconds);

    //==========================================================================
    //      Timer Callback
    //==========================================================================
    void timerCallback() override;
    virtual void meterLevelChanged (int index) = 0;

private:
    int updatePeriod;
    unsigned int numMeters;

    Array <double> targetLevels, currentLevels, previousLevels;

    double minLevel, maxLevel;
    bool clipToRange;
    Array <double> riseStepSizes, decayStepSizes;

    CriticalSection mutex;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterBallistics)
};

#endif // METER_BALLISTICS_H_INCLUDED

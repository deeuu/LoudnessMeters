#include "MeterBallistics.h"

//==========================================================================
//      Constructor and Destructor
//==========================================================================
MeterBallistics::MeterBallistics (unsigned int numMetersInit, double minLevelInit, double maxLevelInit, bool clipToRangeInit)
    : updatePeriod (10),
      numMeters (numMetersInit),
      minLevel (minLevelInit),
      maxLevel (maxLevelInit),
      clipToRange (clipToRangeInit)
{
    // max level should be greater than min level
    jassert (maxLevel > minLevel);

    for (unsigned int n = 0; n < numMeters; ++n)
    {
        targetLevels.add (minLevel);
        currentLevels.add (minLevel);
        previousLevels.add (minLevel);
        riseStepSizes.add (5);
        decayStepSizes.add (50);

        holdTimes.add (0);
        holdSteps.add (0);
    }
}

MeterBallistics::~MeterBallistics()
{
}

//==========================================================================
//      Get and Set Level
//==========================================================================
void MeterBallistics::setMeterLevel (unsigned int index, double newLevel)
{
    GenericScopedLock <CriticalSection> lock (mutex);

    if (clipToRange)
    {
        if (newLevel < minLevel)
        {
            newLevel = minLevel;
        }
        else if (newLevel > maxLevel)
        {
            newLevel = maxLevel;
        }
    }

    previousLevels.set (index, currentLevels [index]);
    targetLevels.set (index, newLevel);

    startTimer (updatePeriod);
}

double MeterBallistics::getMeterLevel (unsigned int index)
{
    GenericScopedLock <CriticalSection> lock (mutex);
    return currentLevels [index];
}

double MeterBallistics::getMeterTargetLevel (unsigned int index)
{
    GenericScopedLock <CriticalSection> lock (mutex);
    return targetLevels [index];
}

//==========================================================================
//      Set Meter Range
//==========================================================================
void MeterBallistics::setNumMeters (unsigned int newNumMeters)
{
    GenericScopedLock <CriticalSection> lock (mutex);

    if (newNumMeters > numMeters)
    {
        int extraMeters = newNumMeters - numMeters;
        int lastIndex = numMeters - 1;

        for (int i = 0; i < extraMeters; ++i)
        {
            targetLevels.add (minLevel);
            currentLevels.add (minLevel);
            previousLevels.add (minLevel);
            riseStepSizes.add (500);
            decayStepSizes.add (50);

            holdTimes.add (0);
            holdSteps.add (0);
        }
    }
    else if (newNumMeters < numMeters)
    {
        int numToRemove = numMeters - newNumMeters;

        targetLevels.removeLast (numToRemove);
        currentLevels.removeLast (numToRemove);
        previousLevels.removeLast (numToRemove);
        riseStepSizes.removeLast (numToRemove);
        decayStepSizes.removeLast (numToRemove);
    }

    numMeters = newNumMeters;
}

void MeterBallistics::setMeterRange (double newMinLevel, double newMaxLevel)
{
    // max level should be greater than min level
    jassert (maxLevel > minLevel);

    minLevel = newMinLevel;
    maxLevel = newMaxLevel;
}

void MeterBallistics::setClipToRange (bool newValue)
{
    clipToRange = newValue;
}

//==========================================================================
//      Set the time it takes for the meter to rise and fall its full range
//==========================================================================
void MeterBallistics::setMeterRiseTime (unsigned int index, unsigned int fullScaleRiseTimeInMilliseconds)
{
    GenericScopedLock <CriticalSection> lock (mutex);

    double valueRange = maxLevel - minLevel;
    riseStepSizes.set (index, updatePeriod * valueRange / fullScaleRiseTimeInMilliseconds);
}

void MeterBallistics::setMeterDecayTime (unsigned int index, unsigned int fullScaleDecayTimeInMilliseconds)
{
    GenericScopedLock <CriticalSection> lock (mutex);

    double valueRange = maxLevel - minLevel;
    decayStepSizes.set (index, updatePeriod * valueRange / fullScaleDecayTimeInMilliseconds);
}

void MeterBallistics::setMeterHoldTime (unsigned int index, unsigned int holdTimeInMilliseconds)
{
    GenericScopedLock <CriticalSection> lock (mutex);

    holdTimes.set (index, holdTimeInMilliseconds / updatePeriod);
    holdSteps.set (index, holdTimes [index]);
}

//==========================================================================
//      Timer Callback
//==========================================================================
void MeterBallistics::timerCallback()
{
    GenericScopedLock <CriticalSection> lock (mutex);

    bool allMetersAtTargets = true;

    for (unsigned int index = 0; index < numMeters; ++index)
    {
        double distanceToTarget = targetLevels [index] - currentLevels [index];

        if (distanceToTarget < 0.0)
        {
            if (holdSteps [index] <= 0)
            {
                if (fabs (distanceToTarget) > decayStepSizes [index])
                {
                    currentLevels.set (index, currentLevels [index] - decayStepSizes [index]);
                    allMetersAtTargets = false;
                }
                else
                {
                    currentLevels.set (index, targetLevels [index]);
                }
            }
            else
            {
                holdSteps.set (index, holdSteps [index] - 1);
                allMetersAtTargets = false;
            }
        }
        else if (distanceToTarget > 0.0)
        {
            if (fabs (distanceToTarget) > riseStepSizes [index])
            {
                currentLevels.set (index, currentLevels [index] + riseStepSizes [index]);
                allMetersAtTargets = false;
            }
            else
            {
                currentLevels.set (index, targetLevels [index]);
            }

            holdSteps.set (index, holdTimes [index]);
        }

        meterLevelChanged (index);
    }

    if (allMetersAtTargets)
    {
        stopTimer();
    }
}

#ifndef __SPECIFIC_LOUDNESS_GRAPH__
#define __SPECIFIC_LOUDNESS_GRAPH__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterBallistics.h"

class StereoSpecificLoudnessGraph : public Component,
                              private MeterBallistics
{
public:
    StereoSpecificLoudnessGraph();
    ~StereoSpecificLoudnessGraph();

    void paint (Graphics&);
    void resized();

    void setGraduationColour (Colour newColour);

    //==========================================================================
    //      setting meter values
    //==========================================================================
    void setSpecificLoudnessValues (const Array <double> &frequencies, const Array <double> &leftValues, const Array <double> &rightValues);

private:
    int height, width, labelSize, graphX, graphY, graphWidth, graphHeight;

    Colour graduationColour, leftTraceColour, rightTraceColour;

    int numMeters;

    // again may change this is lazy :P
    static const int minPhons = 0, maxPhons = 10;

    float phonsToY (double levelInPhons); 
    float camsToX (double frequencyInCams);
    virtual void meterLevelChanged (int index) override;

    Array <double> centreFrequencies;

    CriticalSection mutex;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoSpecificLoudnessGraph)
};


#endif // __SPECIFIC_LOUDNESS_GRAPH__

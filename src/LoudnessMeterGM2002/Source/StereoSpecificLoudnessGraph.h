#ifndef __SPECIFIC_LOUDNESS_GRAPH__
#define __SPECIFIC_LOUDNESS_GRAPH__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterBallistics.h"
#include "Graduations.h"

class StereoSpecificLoudnessGraph : public Component,
                                    private MeterBallistics
{
public:
    StereoSpecificLoudnessGraph();
    ~StereoSpecificLoudnessGraph();

    void paint (Graphics&);
    void resized();
    void setGraphBounds (int x, int y, int width, int height);

    void setGraduationColour (Colour newColour);

    //==========================================================================
    //      setting meter values
    //==========================================================================
    void setSpecificLoudnessValues (const Array <double> &frequencies, const Array <double> &leftValues, const Array <double> &rightValues);

private:
    Colour graduationColour, leftTraceColour, rightTraceColour;

    int labelHeight;
    int graphX, graphY, graphWidth, graphHeight;
    int xGraduationsX, xGraduationsY, xGraduationsWidth, xGraduationsHeight;
    int yGraduationsX, yGraduationsY, yGraduationsWidth, yGraduationsHeight;

    float minCams, maxCams;
    float minLevel, maxLevel;

    int numMeters;

    Graduations xGraduations, yGraduations;

    float levelToY (double level); 
    float camsToX (double frequencyInCams);
    virtual void meterLevelChanged (int index) override;

    Array <double> centreFrequencies;

    CriticalSection mutex;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoSpecificLoudnessGraph)
};


#endif // __SPECIFIC_LOUDNESS_GRAPH__

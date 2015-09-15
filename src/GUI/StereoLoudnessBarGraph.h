#ifndef STEREO_LOUDNESS_BAR_GRAPH_H_INCLUDED
#define STEREO_LOUDNESS_BAR_GRAPH_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterBallistics.h"
#include "BarGraph.h"
#include "Graduations.h"

class StereoLoudnessBarGraph : public Component,
                               private MeterBallistics
{
public:
    StereoLoudnessBarGraph();
    ~StereoLoudnessBarGraph();

    void paint (Graphics&);
    void resized();
    void setMeterBounds (int x, int y, int width, int height);

    void setGraduationColour (Colour newColour);

    void setRange (float newMinLevel, float newMaxLevel);

    void setMeterLevels (float leftLevel, float leftPeak, float rightLevel, float rightPeak);
    
private:
    BarGraph bars [2];

    int labelHeight;
    float minLevel, maxLevel;

    int barWidth;

    Colour graduationColour;
    Graduations graduations;

    virtual void meterLevelChanged (int index) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoLoudnessBarGraph)
};

#endif // STEREO_LOUDNESS_BAR_GRAPH_H_INCLUDED

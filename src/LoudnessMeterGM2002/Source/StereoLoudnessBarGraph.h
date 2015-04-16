#ifndef __STEREO_LOUDNESS_BAR_GRAPH__
#define __STEREO_LOUDNESS_BAR_GRAPH__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterBallistics.h"
#include "BarGraph.h"

class StereoLoudnessBarGraph : public Component,
                               private MeterBallistics
{
public:
    StereoLoudnessBarGraph();
    ~StereoLoudnessBarGraph();

    void paint (Graphics&);
    void resized();

    void setGraduationColour (Colour newColour);

    void setPhonsRange (double newMinPhons, double newMaxPhons);

    void setMeterLevels (double leftLevel, double leftPeak, double rightLevel, double rightPeak);
    
private:
    BarGraph bars [2];

    int width, height, barWidth, barHeight;
    double minPhons, maxPhons;

    Colour graduationColour;

    virtual void meterLevelChanged (int index) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoLoudnessBarGraph)
};

#endif // __STEREO_LOUDNESS_BAR_GRAPH__

#ifndef __STEREO_LOUDNESS_BAR_GRAPH__
#define __STEREO_LOUDNESS_BAR_GRAPH__

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

    void setGraduationColour (Colour newColour);

    void setPhonsRange (float newMinPhons, float newMaxPhons);

    void setMeterLevels (float leftLevel, float leftPeak, float rightLevel, float rightPeak);
    
private:
    BarGraph bars [2];

    float minPhons, maxPhons;

    Colour graduationColour;
    Graduations graduations;

    virtual void meterLevelChanged (int index) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoLoudnessBarGraph)
};

#endif // __STEREO_LOUDNESS_BAR_GRAPH__

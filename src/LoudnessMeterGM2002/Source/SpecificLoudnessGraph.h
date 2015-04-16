#ifndef __SPECIFIC_LOUDNESS_GRAPH__
#define __SPECIFIC_LOUDNESS_GRAPH__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterBallistics.h"

class SpecificLoudnessGraph : public Component,
                              private MeterBallistics
{
public:
    SpecificLoudnessGraph();
    ~SpecificLoudnessGraph();

    void paint (Graphics&);
    void resized();

    void setGraduationColour (Colour newColour);

    //==========================================================================
    //      setting meter values
    //==========================================================================
    void setSpecificLoudnessValues (const Array <double> &values);

private:
    int height, width, labelSize, graphX, graphY, graphWidth, graphHeight;

    Colour graduationColour, traceColour;

    // no idea what this should be, for now it is a suitably big number
    static const int numMeters = 30;

    // again may change this is lazy :P
    static const int minPhons = 0, maxPhons = 60;

    float phonsToY (double levelInPhons); 
    virtual void meterLevelChanged (int index) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpecificLoudnessGraph)
};


#endif // __SPECIFIC_LOUDNESS_GRAPH__

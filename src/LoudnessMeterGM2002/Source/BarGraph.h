#ifndef BAR_GRAPH_H_INCLUDED
#define BAR_GRAPH_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class BarGraph : public Component
{
public:
    BarGraph();
    ~BarGraph();

    void paint (Graphics&);
    void resized();

    void setProportionFilled (double newValue);
    void setPeakPosition (double newValue);
    void setLevels (double proportionFilled, double peakLevel);

private:
    double value, peakPosition;
    Colour peakColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BarGraph)
};

#endif  // BAR_GRAPH_H_INCLUDED

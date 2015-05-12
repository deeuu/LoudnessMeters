#ifndef LOUDNESS_VALUE_DISPLAY_H_INCLUDED
#define LOUDNESS_VALUE_DISPLAY_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class LoudnessValueDisplay : public Component
{
public:

    LoudnessValueDisplay(const String& labelText, 
                         const Colour& labelColour, 
                         const Colour& valueColour);
    ~LoudnessValueDisplay();

    void setValueToDisplay (double newValueToDisplay, int numberOfDecimalPlaces = 1);

    void paint (Graphics& g) override;

private:

    String valueToDisplay, labelText;

    Colour valueColour, labelColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoudnessValueDisplay)
};

#endif // LOUDNESS_VALUE_DISPLAY_H_INCLUDED

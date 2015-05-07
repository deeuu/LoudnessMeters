#ifndef __LOUDNESS_VALUE_DISPLAY__
#define __LOUDNESS_VALUE_DISPLAY__

#include "../JuceLibraryCode/JuceHeader.h"

class LoudnessValueDisplay : public Component
{
public:

    LoudnessValueDisplay(const String& labelText, 
                         const Colour& labelColour, 
                         const Colour& valueColour);
    ~LoudnessValueDisplay();

    void setValueToDisplay (double newValueToDisplay, int numberOfDecimalPlaces);

    void paint (Graphics& g) override;

private:

    String valueToDisplay, labelText;

    Colour valueColour, labelColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoudnessValueDisplay)
};

#endif // __SETTINGS_BUTTON__

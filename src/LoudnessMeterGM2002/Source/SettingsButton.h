#ifndef __SETTINGS_BUTTON__
#define __SETTINGS_BUTTON__

#include "../JuceLibraryCode/JuceHeader.h"

class SettingsButton : public Button
{
public:
    SettingsButton();
    ~SettingsButton();

    void paintButton (Graphics &g, bool isMouseOverButton, bool isButtonDown);

private:
    Colour bodyColour, bodyColourMouseOver, bodyColourDown;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsButton)
};

#endif // __SETTINGS_BUTTON__

#ifndef SETTINGS_BUTTON_H_INCLUDED
#define SETTINGS_BUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SettingsButton : public Button
{
public:
    SettingsButton (const String& textInit);
    ~SettingsButton();

    void paintButton (Graphics &g, bool isMouseOverButton, bool isButtonDown);

private:
    String text;
    Colour bodyColour, bodyColourMouseOver, bodyColourDown;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsButton)
};

#endif // SETTINGS_BUTTON_H_INCLUDED

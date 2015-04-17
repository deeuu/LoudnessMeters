#ifndef __SETTINGS_SCREEN__
#define __SETTINGS_SCREEN__

#include "../JuceLibraryCode/JuceHeader.h"

class SettingsScreen : public Component
{
public:
    SettingsScreen();
    ~SettingsScreen();

    void paint (Graphics&);
    void resized();

    TextButton submitButton;

private:
    ComboBox modelRate, camSpacing, compression, filter;
    Label modelRateLabel, camSpacingLabel, compressionLabel, filterLabel;

    static const int boxHeight = 20, boxWidth = 80, boxY = 20, boxSpacing = 10;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsScreen)
};


#endif  // __SETTINGS_SCREEN__

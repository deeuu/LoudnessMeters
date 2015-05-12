#ifndef __SETTINGS_SCREEN__
#define __SETTINGS_SCREEN__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class SettingsScreen : public Component,
                       public ComboBox::Listener
{
public:
    SettingsScreen (const LoudnessParameters &loudnessParametersInit);
    ~SettingsScreen();

    void paint (Graphics&);
    void resized();

    TextButton submitButton;

    void comboBoxChanged (ComboBox *boxThatChanged) override;

    LoudnessParameters getLoudnessParameters();

private:
    ComboBox modelRate, camSpacing, compression, filter;
    Label modelRateLabel, camSpacingLabel, compressionLabel, filterLabel;

    static const int boxHeight = 20, boxWidth = 80, boxY = 60, boxSpacing = 10;

    void setLoudnessParameters (const LoudnessParameters &newLoudnessParameters);
    LoudnessParameters loudnessParameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsScreen)
};


#endif  // __SETTINGS_SCREEN__

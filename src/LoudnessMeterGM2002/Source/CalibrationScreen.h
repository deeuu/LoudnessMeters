#ifndef __CALIBRATION_SCREEN__
#define __CALIBRATION_SCREEN__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class CalibrationScreen : public Component,
                          public ComboBox::Listener,
                          public TextEditor::Listener
{
public:
    CalibrationScreen ();
    ~CalibrationScreen();

    void paint (Graphics&);
    void resized();

    TextButton submitButton, calibrateButton;

    void comboBoxChanged (ComboBox *boxThatChanged) override;
    void textEditorReturnKeyPressed (TextEditor& editorThatChanged) override;

    const MeasuredLevels& getMeasuredLevels() const;

private:

    ComboBox channelSelector;
    TextEditor calibrationEditor;
    TextEditor::LengthAndCharacterRestriction calibrationEditorTextFilter;

    static const int boxHeight = 20, boxWidth = 80, boxY = 20, boxSpacing = 10;

    MeasuredLevels measuredLevels;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CalibrationScreen)
};


#endif  // __SETTINGS_SCREEN__

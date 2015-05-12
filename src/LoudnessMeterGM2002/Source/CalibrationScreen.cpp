#include "../JuceLibraryCode/JuceHeader.h"
#include "CalibrationScreen.h"

CalibrationScreen::CalibrationScreen ()
    : submitButton ("Calibrate"),
      measureButton("Measure"),
      calibrationEditorLabel("", "SPL"),
      gainEditorLabel("", "Gain (dB)"),
      calibrationEditorTextFilter(4, "0123456789.-")
{
    addAndMakeVisible(channelSelector);
    channelSelector.setBounds (0, 
                               boxY, 
                               boxWidth,
                               boxHeight);
    channelSelector.addItem ("Left", 1);
    channelSelector.addItem ("Right", 2);
    channelSelector.addListener (this);
    channelSelector.setSelectedId (1);

    addAndMakeVisible (calibrationEditor);
    calibrationEditor.setBounds (80, boxY, boxWidth, boxHeight);
    calibrationEditor.setInputFilter (&calibrationEditorTextFilter, false);
    calibrationEditor.addListener (this);
    calibrationEditorLabel.attachToComponent (&calibrationEditor, false);

    addAndMakeVisible (measureButton);
    measureButton.setBounds (160, boxY + boxHeight + boxSpacing, boxWidth, boxHeight);

    addAndMakeVisible (gainEditor);
    gainEditor.setBounds (240, boxY, boxWidth, boxHeight);
    gainEditor.setInputFilter (&calibrationEditorTextFilter, false);
    gainEditor.addListener (this);
    gainEditorLabel.attachToComponent (&gainEditor, false);

    addAndMakeVisible (submitButton);
    submitButton.setBounds (80, boxY + boxHeight + boxSpacing, boxWidth, boxHeight);

    userInputLevels[0] = 94.0;
    userInputLevels[1] = 94.0;
    calibrationLevels[0] = 0.0;
    calibrationLevels[1] = 0.0;

    calibrationEditor.setText (String (userInputLevels[0], 2));
    gainEditor.setText (String (calibrationLevels[0], 2));
}

CalibrationScreen::~CalibrationScreen()
{
}

void CalibrationScreen::paint (Graphics& g)
{
    g.fillAll (Colour (0xffbbbbbb));
    g.setColour (Colours::black);
    g.setFont (18);
    g.drawFittedText ("SPL Calibration", 0, 10, getWidth(), 20, Justification::centred, 1);
}

void CalibrationScreen::resized()
{
    int width = getWidth();
    int midPoint = width / 2;

    channelSelector.setTopLeftPosition (midPoint - 2 * boxWidth - 1.5 * boxSpacing, boxY);
    calibrationEditor.setTopLeftPosition (midPoint - boxWidth - 0.5 * boxSpacing, boxY);
    measureButton.setTopLeftPosition (midPoint + 0.5 * boxSpacing, boxY);
    gainEditor.setTopLeftPosition (midPoint + boxWidth + 1.5 * boxSpacing, boxY);
    submitButton.setTopLeftPosition (midPoint - 0.5 * boxWidth, boxY + boxHeight + boxSpacing);
}

void CalibrationScreen::comboBoxChanged (ComboBox *boxThatChanged)
{
    if (boxThatChanged == &channelSelector)
    {
        if (channelSelector.getSelectedId() == 1)
        {
            calibrationEditor.setText(String(userInputLevels[0], 2));
            gainEditor.setText(String(calibrationLevels[0], 2));
        }
        else if (channelSelector.getSelectedId() == 2)
        {
            calibrationEditor.setText(String(userInputLevels[1], 2));
            gainEditor.setText(String(calibrationLevels[1], 2));
        }

        currentUserInputChannel = channelSelector.getSelectedId() - 1;
    }
}

void CalibrationScreen::textEditorTextChanged (TextEditor& editorThatChanged)
{
    if (&editorThatChanged == &calibrationEditor)
    {
        if (channelSelector.getSelectedId() == 1)
            userInputLevels[0] = calibrationEditor.getText().getFloatValue();
        else if (channelSelector.getSelectedId() == 2)
            userInputLevels[1] = calibrationEditor.getText().getFloatValue();
    }
    else if (&editorThatChanged == &gainEditor)
    {
        if (channelSelector.getSelectedId() == 1)
            calibrationLevels[0] = gainEditor.getText().getFloatValue();
        else if (channelSelector.getSelectedId() == 2)
            calibrationLevels[1] = gainEditor.getText().getFloatValue();
    }

}

int CalibrationScreen::getCurrentUserInputChannel() const
{
    return currentUserInputChannel; 
}

double CalibrationScreen::getCurrentUserInputLevel() const
{
    return userInputLevels[currentUserInputChannel];
}

double CalibrationScreen::getCalibrationLevel (int channel) const
{
    return calibrationLevels[channel];
}

void CalibrationScreen::setCalibrationLevelsToUnity ()
{
    calibrationLevels[0] = 0.0;
    calibrationLevels[1] = 0.0;
    gainEditor.setText(String(calibrationLevels[0], 2));
}

void CalibrationScreen::updateBasedOnCalibrationMeasurement (int measurementChannel,
                                                             double userLevel, 
                                                             double calibrationLevel)
{
    userInputLevels[measurementChannel] = userLevel;
    calibrationLevels[measurementChannel] = calibrationLevel;
    channelSelector.setSelectedId (measurementChannel + 1);
    calibrationEditor.setText (String (userLevel, 2));
    gainEditor.setText (String (calibrationLevel, 2));
}

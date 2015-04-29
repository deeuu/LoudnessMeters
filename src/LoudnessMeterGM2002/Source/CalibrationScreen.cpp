#include "../JuceLibraryCode/JuceHeader.h"
#include "CalibrationScreen.h"

CalibrationScreen::CalibrationScreen ()
    : submitButton ("OK"),
      calibrateButton("Cal"),
      calibrationEditorTextFilter(4, "0123456789.")
{
    addAndMakeVisible(channelSelector);
    channelSelector.setBounds (boxSpacing, boxY, boxWidth, boxHeight);
    channelSelector.addItem("Left", 1);
    channelSelector.addItem("Right", 2);
    channelSelector.addListener (this);

    addAndMakeVisible(calibrationEditor);
    calibrationEditor.setBounds(boxSpacing * 2 + boxWidth, boxY, boxWidth / 2, boxHeight);
    calibrationEditor.setInputFilter(&calibrationEditorTextFilter, false);
    calibrationEditor.addListener (this);

    addAndMakeVisible (calibrateButton);
    calibrateButton.setBounds (70, boxY + boxHeight + boxSpacing, 40, 20);

    addAndMakeVisible (submitButton);
    submitButton.setBounds (140, boxY + boxHeight + boxSpacing, 40, 20);

    measuredLevels.left = measuredLevels.right = 94.0f; //20 * log10 (50000.0f);
}

CalibrationScreen::~CalibrationScreen()
{
}

void CalibrationScreen::paint (Graphics& g)
{
    g.fillAll (Colour (0xffaaaaaa));
}

void CalibrationScreen::resized()
{
    int width = getWidth();
    int midPoint = width / 2;

    //submitButton.setTopLeftPosition (midPoint - 40, boxY + boxHeight + boxSpacing);
    //submitButton.setTopLeftPosition (midPoint - 40, boxY + boxHeight + boxSpacing);
    //calibrateButton.setTopLeftPosition (midPoint + 40, boxY + boxHeight + boxSpacing);
}

void CalibrationScreen::comboBoxChanged (ComboBox *boxThatChanged)
{
    if (boxThatChanged == &channelSelector)
    {
        if (channelSelector.getSelectedId() == 1)
            calibrationEditor.setText(String(measuredLevels.left));

        if (channelSelector.getSelectedId() == 2)
            calibrationEditor.setText(String(measuredLevels.right));
    }
}

const MeasuredLevels& CalibrationScreen::getMeasuredLevels() const
{
    return measuredLevels;
}

void CalibrationScreen::textEditorReturnKeyPressed (TextEditor& editorThatChanged)
{
    if (&editorThatChanged == &calibrationEditor)
    {
        if (channelSelector.getSelectedId() == 1)
        {
            measuredLevels.left = calibrationEditor.getText().getFloatValue();
            //Logger::outputDebugString ("Left value: " + String(calibrationGainLeft));
        }
        if (channelSelector.getSelectedId() == 2)
        {
            measuredLevels.right = calibrationEditor.getText().getFloatValue();
        }
    }
}

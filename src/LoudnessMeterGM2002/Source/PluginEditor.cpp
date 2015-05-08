/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LoudnessMeterAudioProcessorEditor::LoudnessMeterAudioProcessorEditor (LoudnessMeterAudioProcessor& p)
    : AudioProcessorEditor (&p),
      processor (p),
      loudnessValues (processor.getPointerToLoudnessValues()),
      settingsButton (Colours::blue),
      calibrationButton (Colours::red),
      settingsScreen (processor.getLoudnessParameters()),
      displayForLTL("Long Term", Colours::lightgrey, Colours::yellow),
      displayForPeakSTL("Peak", Colours::lightgrey, Colours::yellow),
      displayForSPL("SPL", Colours::lightgrey, Colours::yellow)
{
    int generalSpacing = 10;
    int windowWidth = 700;
    int windowHeight = 350;
    setSize (windowWidth, windowHeight);
   
    int goldenPoint = windowWidth / 1.618;
    int specLoudGraphWidth = goldenPoint - 1.5 * generalSpacing;
    int specLoudGraphHeight = 300;
    addAndMakeVisible (specificLoudness);
    specificLoudness.setGraduationColour (Colours::lightgrey);
    specificLoudness.setBounds (generalSpacing, 
                                generalSpacing,
                                specLoudGraphWidth,
                                specLoudGraphHeight);

    int barX = goldenPoint + 0.5 * generalSpacing;
    int barWidth = (windowWidth - goldenPoint - 2.5 * generalSpacing) / 2;
    addAndMakeVisible (barGraph);
    barGraph.setGraduationColour (Colours::lightgrey);
    barGraph.setPhonsRange (0, 34);
    barGraph.setBounds (barX,
                        generalSpacing,
                        barWidth, 
                        specLoudGraphHeight);

    int valueDisplayWidth = barWidth / 1.5;
    int valueDisplayHeight = valueDisplayWidth;
    int displayForLTLX = barX + barWidth 
                         + (windowWidth - (barX + barWidth)
                         - valueDisplayWidth)/2;
    addAndMakeVisible (displayForLTL);
    displayForLTL.setBounds (displayForLTLX, generalSpacing, 
                             valueDisplayWidth, valueDisplayHeight);

    addAndMakeVisible (displayForPeakSTL);
    displayForPeakSTL.setBounds (displayForLTLX, 
                                 valueDisplayHeight + generalSpacing,
                                 valueDisplayWidth, valueDisplayHeight);

    addAndMakeVisible (displayForSPL);
    displayForSPL.setBounds (displayForLTLX, 
                             valueDisplayHeight * 2 + generalSpacing * 2,
                             valueDisplayWidth, valueDisplayHeight);

    int settingsWidth = 20, settingsHeight = 20;
    int settingsX = displayForLTLX + generalSpacing;
    int settingsY = specLoudGraphHeight + generalSpacing - settingsHeight;
    addAndMakeVisible (settingsButton);
    settingsButton.setBounds (settingsX, settingsY,
                              settingsWidth, settingsHeight);
    settingsButton.addListener (this);

    int calibrationX = settingsX + barWidth;
    addAndMakeVisible (calibrationButton);
    calibrationButton.setBounds (settingsX + settingsWidth + generalSpacing,
                                 settingsY, settingsWidth,
                                 settingsHeight);
    calibrationButton.addListener (this);
    
    addAndMakeVisible (settingsScreen);
    settingsScreen.setBounds (0, getHeight(), getWidth(), 70);
    settingsScreen.submitButton.addListener (this);
    oldLoudnessParameters = settingsScreen.getLoudnessParameters();

    addAndMakeVisible (calibrationScreen);
    calibrationScreen.setBounds (0, getHeight(), getWidth(), 70);
    calibrationScreen.submitButton.addListener (this);
    calibrationScreen.calibrateButton.addListener (this);
    
    startTimer (50);
}

LoudnessMeterAudioProcessorEditor::~LoudnessMeterAudioProcessorEditor()
{
}

//==============================================================================
void LoudnessMeterAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);
}

void LoudnessMeterAudioProcessorEditor::resized()
{
}

void LoudnessMeterAudioProcessorEditor::buttonClicked (Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == &settingsButton)
    {
        //Show the settings screen to allow model config
        showSettings(settingsScreen);
    }
    else if (buttonThatWasClicked == &(settingsScreen.submitButton))
    {
        hideSettings (settingsScreen);

        //Get the new params from GUI
        LoudnessParameters newLoudnessParameters = settingsScreen.getLoudnessParameters();

        //Update only if a parameter has changed
        if (newLoudnessParameters.modelRate != oldLoudnessParameters.modelRate ||
            newLoudnessParameters.camSpacing != oldLoudnessParameters.camSpacing ||
            newLoudnessParameters.compression != oldLoudnessParameters.compression ||
            newLoudnessParameters.filter != oldLoudnessParameters.filter)
        {
            processor.setLoudnessParameters (newLoudnessParameters);
            oldLoudnessParameters = newLoudnessParameters;
        }
    }
    else if (buttonThatWasClicked == &calibrationButton)
    {
        //shoow calibraton screen to allow calibration
        showSettings(calibrationScreen);
    }
    else if (buttonThatWasClicked == &(calibrationScreen.calibrateButton))
    {
        processor.calibrate (calibrationScreen.getMeasuredLevels());
    }
    else if (buttonThatWasClicked == &(calibrationScreen.submitButton))
    {
        hideSettings (calibrationScreen);
    }
}

void LoudnessMeterAudioProcessorEditor::timerCallback()
{
    if (processor.loudnessValuesReady())
    {
        //update bar graphs
        barGraph.setMeterLevels (loudnessValues->leftLTL,
                                 loudnessValues->leftPeakSTL,
                                 loudnessValues->rightLTL,
                                 loudnessValues->rightPeakSTL);

        //update specific loudness graph
        specificLoudness.setSpecificLoudnessValues (loudnessValues->centreFrequencies, 
                                                    loudnessValues->leftSpecificLoudness,
                                                    loudnessValues->rightSpecificLoudness);

        //update number displays
        displayForLTL.setValueToDisplay (loudnessValues->overallLTL, 1);
        displayForPeakSTL.setValueToDisplay (loudnessValues->overallPeakSTL, 1);
        displayForSPL.setValueToDisplay (loudnessValues->averageSPL, 1);
          
        processor.updateLoudnessValues();
    }
}

void LoudnessMeterAudioProcessorEditor::showSettings (Component &screenToShow)
{
    animator.animateComponent (&screenToShow,
                               Rectangle <int> (0, getHeight() - 80, getWidth(), 80),
                               1.0f, 1000, false, 0.0, 0.0);
}

void LoudnessMeterAudioProcessorEditor::hideSettings (Component &screenToHide)
{
    animator.animateComponent (&screenToHide,
                               Rectangle <int> (0, getHeight(), getWidth(), 80),
                               1.0f, 1000, false, 0.0, 0.0);
    repaint();
}

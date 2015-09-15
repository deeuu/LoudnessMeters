#include "../JuceLibraryCode/JuceHeader.h"
#include "SettingsScreen.h"

SettingsScreen::SettingsScreen (const LoudnessParameters &loudnessParametersInit)
    : submitButton ("OK"),
      modelRateLabel ("", "Model Rate"),
      camSpacingLabel ("", "Cam Spacing"),
      compressionLabel ("", "Compression"),
      filterLabel ("", "Outer Ear")
{
    addAndMakeVisible (modelRate);
    modelRate.setBounds (10, boxY, boxWidth, boxHeight);
    modelRate.addItem ("62.5", 1);
    modelRate.addItem ("125", 2);
    modelRate.addItem ("250", 3);
    modelRate.addItem ("500", 4);
    modelRate.addItem ("1000", 5);
    modelRate.addListener (this);
    modelRateLabel.attachToComponent (&modelRate, false);

    addAndMakeVisible (camSpacing);
    camSpacing.setBounds (80, boxY, boxWidth, boxHeight);
    camSpacing.addItem ("0.25", 1);
    camSpacing.addItem ("0.5", 2);
    camSpacing.addItem ("0.75", 3);
    camSpacing.addItem ("1.0", 4);
    camSpacing.addListener (this);
    camSpacingLabel.attachToComponent (&camSpacing, false);

    addAndMakeVisible (compression);
    compression.setBounds (160, boxY, boxWidth, boxHeight);
    compression.addItem ("0.1", 1);
    compression.addItem ("0.2", 2);
    compression.addItem ("0.3", 3);
    compression.addItem ("0.4", 4);
    compression.addListener (this);
    compressionLabel.attachToComponent (&compression, false);

    addAndMakeVisible (filter);
    filter.setBounds (240, boxY, boxWidth, boxHeight);
    filter.addItem ("Free Field", 1);
    filter.addItem ("Diffuse Field", 2);
    filter.addItem ("DT990", 3);
    filter.addItem ("None", 4);
    filter.addListener (this);
    filterLabel.attachToComponent (&filter, false);

    addAndMakeVisible (submitButton);
    submitButton.setBounds (75, boxY + boxHeight + boxSpacing, 40, 20);

    setLoudnessParameters (loudnessParametersInit);
}

SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::paint (Graphics& g)
{
    g.fillAll (Colour (0xffbbbbbb));
    g.setColour (Colours::black);
    g.setFont (18);
    g.drawFittedText ("Model Settings", 0, 10, getWidth(), 20, Justification::centred, 1);
}

void SettingsScreen::resized()
{
    int width = getWidth();
    int midPoint = width / 2;

    modelRate.setTopLeftPosition (midPoint - 2 * boxWidth - 1.5 * boxSpacing, boxY);
    camSpacing.setTopLeftPosition (midPoint - boxWidth - boxSpacing / 2, boxY);
    compression.setTopLeftPosition (midPoint + boxSpacing / 2, boxY);
    filter.setTopLeftPosition (midPoint + 1.5 * boxSpacing + boxWidth, boxY);
    submitButton.setTopLeftPosition (midPoint - 20, boxY + boxHeight + boxSpacing);
}

void SettingsScreen::comboBoxChanged (ComboBox *boxThatChanged)
{
    if (boxThatChanged == &modelRate)
    {
        if (modelRate.getSelectedId() == 1)
        {
            loudnessParameters.modelRate = 62.5;
        }
        else if (modelRate.getSelectedId() == 2)
        {
            loudnessParameters.modelRate = 125;
        }
        else if (modelRate.getSelectedId() == 3)
        {
            loudnessParameters.modelRate = 250;
        }
        else if (modelRate.getSelectedId() == 4)
        {
            loudnessParameters.modelRate = 500;
        }
        else if (modelRate.getSelectedId() == 5)
        {
            loudnessParameters.modelRate = 1000;
        }
    }
    else if (boxThatChanged == &camSpacing)
    {
        if (camSpacing.getSelectedId() == 1)
        {
            loudnessParameters.camSpacing = 0.25;
        }
        else if (camSpacing.getSelectedId() == 2)
        {
            loudnessParameters.camSpacing = 0.5;
        }
        else if (camSpacing.getSelectedId() == 3)
        {
            loudnessParameters.camSpacing = 0.75;
        }
        else if (camSpacing.getSelectedId() == 4)
        {
            loudnessParameters.camSpacing = 1.0;
        }
    }
    else if (boxThatChanged == &compression)
    {
        if (compression.getSelectedId() == 1)
        {
            loudnessParameters.compression = 0.0;
        }
        else if (compression.getSelectedId() == 2)
        {
            loudnessParameters.compression = 0.1;
        }
        else if (compression.getSelectedId() == 3)
        {
            loudnessParameters.compression = 0.2;
        }
        else if (compression.getSelectedId() == 4)
        {
            loudnessParameters.compression = 0.3;
        }
    }
    else if (boxThatChanged == &filter)
    {
        if (filter.getSelectedId() == 1)
        {
            loudnessParameters.filter = 0;
        }
        else if (filter.getSelectedId() == 2)
        {
            loudnessParameters.filter = 1;
        }
        else if (filter.getSelectedId() == 3)
        {
            loudnessParameters.filter = 2;
        }
        else if (filter.getSelectedId() == 4)
        {
            loudnessParameters.filter = 3;
        }
    }
}

LoudnessParameters SettingsScreen::getLoudnessParameters()
{
    return loudnessParameters;
}

void SettingsScreen::setLoudnessParameters (const LoudnessParameters &newLoudnessParameters)
{
    loudnessParameters = newLoudnessParameters;

    // display model rate
    if (loudnessParameters.modelRate == 62.5)
    {
        modelRate.setSelectedId (1);
    }
    else if (loudnessParameters.modelRate == 125)
    {
        modelRate.setSelectedId (2);
    }
    else if (loudnessParameters.modelRate == 250)
    {
        modelRate.setSelectedId (3);
    }
    else if (loudnessParameters.modelRate == 500)
    {
        modelRate.setSelectedId (4);
    }
    else
    {
        modelRate.setSelectedId (5);
    }

    // display cam spacing
    if (loudnessParameters.camSpacing == 0.25)
    {
        camSpacing.setSelectedId (1);
    }
    else if (loudnessParameters.camSpacing == 0.5)
    {
        camSpacing.setSelectedId (2);
    }
    else if (loudnessParameters.camSpacing == 0.75)
    {
        camSpacing.setSelectedId (3);
    }
    else
    {
        camSpacing.setSelectedId (4);
    }

    // display compression
    if (loudnessParameters.compression == 0.0)
    {
        compression.setSelectedId (1);
    }
    else if (loudnessParameters.compression == 0.1)
    {
        compression.setSelectedId (2);
    }
    else if (loudnessParameters.compression == 0.2)
    {
        compression.setSelectedId (3);
    }
    else
    {
        compression.setSelectedId (4);
    }
    // display outer ear filter
    if (loudnessParameters.filter == 0.0)
    {
        filter.setSelectedId (1);
    }
    else if (loudnessParameters.filter == 0.1)
    {
        filter.setSelectedId (2);
    }
    else if (loudnessParameters.filter == 0.2)
    {
        filter.setSelectedId (3);
    }
    else
    {
        filter.setSelectedId (4);
    }
}

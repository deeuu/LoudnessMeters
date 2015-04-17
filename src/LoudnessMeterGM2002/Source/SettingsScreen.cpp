#include "../JuceLibraryCode/JuceHeader.h"
#include "SettingsScreen.h"

SettingsScreen::SettingsScreen()
    : submitButton ("OK"),
      modelRateLabel ("", "Model Rate"),
      camSpacingLabel ("", "Cam Spacing"),
      compressionLabel ("", "Compression"),
      filterLabel ("", "Filter")
{
    addAndMakeVisible (modelRate);
    modelRate.setBounds (10, boxY, boxWidth, boxHeight);
    modelRate.addItem ("1000", 1);
    modelRate.addItem ("500", 2);
    modelRate.addItem ("250", 3);
    modelRate.addItem ("125", 4);
    modelRate.addItem ("62.5", 5);
    modelRateLabel.attachToComponent (&modelRate, false);

    addAndMakeVisible (camSpacing);
    camSpacing.setBounds (80, boxY, boxWidth, boxHeight);
    camSpacing.addItem ("0.25", 1);
    camSpacing.addItem ("0.5", 2);
    camSpacing.addItem ("0.75", 3);
    camSpacing.addItem ("1.0", 4);
    camSpacingLabel.attachToComponent (&camSpacing, false);

    addAndMakeVisible (compression);
    compression.setBounds (160, boxY, boxWidth, boxHeight);
    compression.addItem ("0.0", 1);
    compression.addItem ("0.1", 2);
    compression.addItem ("0.2", 3);
    compression.addItem ("0.3", 4);
    compressionLabel.attachToComponent (&compression, false);

    addAndMakeVisible (filter);
    filter.setBounds (240, boxY, boxWidth, boxHeight);
    filter.addItem ("Free Field", 1);
    filter.addItem ("Diffuse Field", 2);
    filter.addItem ("DT990", 3);
    filter.addItem ("Middle Ear", 4);
    filterLabel.attachToComponent (&filter, false);

    addAndMakeVisible (submitButton);
    submitButton.setBounds (75, boxY + boxHeight + boxSpacing, 40, 20);
}

SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::paint (Graphics& g)
{
    g.fillAll (Colour (0xffaaaaaa));
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

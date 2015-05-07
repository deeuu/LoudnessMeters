#include "LoudnessValueDisplay.h"

LoudnessValueDisplay::LoudnessValueDisplay(const String& labelText, 
                                           const Colour& labelColour,
                                           const Colour& valueColour)
    :   labelText(labelText),
        labelColour(labelColour),
        valueColour(valueColour)
{
    valueToDisplay = String("0.0");
}

LoudnessValueDisplay::~LoudnessValueDisplay()
{
}

void LoudnessValueDisplay::setValueToDisplay (double newValueToDisplay, int numberOfDecimalPlaces)
{
    valueToDisplay = String (newValueToDisplay, numberOfDecimalPlaces);
}

void LoudnessValueDisplay::paint (Graphics& g)
{
    int xPos = 0, yPos = 0;
    int height = getHeight() / 2;
    g.setColour (labelColour);
    g.drawFittedText (labelText, xPos, yPos, getWidth(), height,
                      Justification::centred, 1); 
    Rectangle <float> rect (xPos, yPos + height, getWidth(), height);
    g.setColour (Colours::black);
    g.fillEllipse (rect);

    g.setColour (valueColour);
    g.drawFittedText (valueToDisplay, xPos, yPos + height, getWidth(), height, Justification::centred, 1); 
}

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

    repaint();
}

void LoudnessValueDisplay::paint (Graphics& g)
{
    int xPos = 0, yPos = 0;
    int height = getHeight() / 3;
    int circleHeight = 2 * height;
    g.setColour (labelColour);
    g.drawFittedText (labelText, xPos, yPos, getWidth(), height,
                      Justification::centred, 1); 
    Rectangle <float> rect (getWidth() / 6, yPos + height, circleHeight, circleHeight);
    g.setColour (Colours::black);
    g.fillEllipse (rect);

    g.setColour (valueColour);
    g.setFont (20);
    g.drawFittedText (valueToDisplay, xPos,
                      yPos + height, getWidth(), 
                      circleHeight, Justification::centred, 1); 
}

#include "SettingsButton.h"

SettingsButton::SettingsButton (const String& textInit)
    : Button (textInit),
      text (textInit),
      bodyColour (0xffaaaaaa),
      bodyColourMouseOver (0xff999999),
      bodyColourDown (0xff888888)
{
}

SettingsButton::~SettingsButton()
{
}

void SettingsButton::paintButton (Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
    int width = getWidth();
    int height = getHeight();

    if (isButtonDown)
    {
        g.setColour (bodyColourDown);
    }
    else if (isMouseOverButton)
    {
        g.setColour (bodyColourMouseOver);
    }
    else
    {
        g.setColour (bodyColour);
    }

    g.fillAll();

    g.setColour (Colours::black);
    g.drawFittedText (text, 0, 0, width, height, Justification::centred, 1);
    g.drawRect (0, 0, width, height, 1);
}

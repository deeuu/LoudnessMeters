#include "SettingsButton.h"

SettingsButton::SettingsButton(const Colour& colour)
    : Button ("Settings"),
      faceColour (colour),
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
    float width = static_cast <float> (getWidth());
    float height = static_cast <float> (getHeight());

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

    g.fillEllipse (0, 0, width, height);

    Path symbolPath;
    symbolPath.addPolygon (Point <float> (width / 2.0f, height / 2.0f), 6, width / 2.5f, float_Pi / 6.0f);

    Path innerPath;
    innerPath.addEllipse (2.0f * width / 5.0f, 2.0f * height / 5.0f, width / 5.0f, height / 5.0f);

    symbolPath.addPath (innerPath, AffineTransform::verticalFlip (height));
    
    g.setColour (faceColour);
    g.fillPath (symbolPath);
}

#include "Graduations.h"

Graduations::Graduations (Style styleInit, Type typeInit)
    : style (styleInit),
      type (typeInit),
      colour (Colours::black),
      fontHeight (12.0f),
      isAxis (false),
      minValue (0.1f),
      maxValue (10.0f)
{
    setSize (20, 200);

    setAndGetRange (minValue, maxValue);
    calculateEndOffset();
}

Graduations::~Graduations()
{
}

void Graduations::paint (Graphics &g)
{
    g.setColour (colour);

    if (type == Linear)
    {
        paintLinearGraduations (g);
    }
    else if (type == Logarithmic)
    {
        paintLogarithmicGraduations (g);
    }

    if (isAxis)
    {
        paintAxisLine (g);
    }
}

void Graduations::resized()
{
}

void Graduations::setColour (Colour newColour)
{
    colour = newColour;
    repaint();
}

void Graduations::setFontHeight (float newFontHeight)
{
    fontHeight = newFontHeight;
    calculateEndOffset();
    repaint();
}

void Graduations::showAxisLine (bool newValue)
{
    isAxis = newValue;
    repaint();
}

void Graduations::setAndGetRange (float &newMinValue, float &newMaxValue)
{
    // the min value should be less than the max value
    jassert (newMinValue < newMaxValue);

    minValue = newMinValue;
    maxValue = newMaxValue;

    calculateTickIncrements();

    newMinValue = minValue;
    newMaxValue = maxValue;

    repaint();
}

float Graduations::getEndOffset()
{
    return endOffset;
}

float Graduations::coordinateToValue (float coordinate)
{
    int dimension = getDimension();

    float minCoordinate = endOffset;
    float maxCoordinate = dimension - endOffset;
    float coordinateRange = maxCoordinate - minCoordinate;

    float scaledAndOffsetCoordinate = (coordinate - minCoordinate) / coordinateRange;

    if (style & Vertical)
    {
        scaledAndOffsetCoordinate = 1.0f - scaledAndOffsetCoordinate;
    }

    if (type == Linear)
    {
        float valueRange = maxValue - minValue;
        return valueRange * scaledAndOffsetCoordinate + minValue;
    }
    else if (type == Logarithmic)
    {
        float valueRatio = maxValue / minValue;
        return minValue * pow (valueRatio, scaledAndOffsetCoordinate);
    }
}

float Graduations::valueToCoordinate (float value)
{
    float scaledAndOffsetValue = 0;

    if (type == Linear)
    {
        float valueRange = maxValue - minValue;
        scaledAndOffsetValue = (value - minValue) / valueRange;
    }
    else if (type == Logarithmic)
    {
        float valueRatio = maxValue / minValue;
        float scaledValue = value / minValue;
        scaledAndOffsetValue = log (scaledValue) / log (valueRatio);
    }

    if (style & Vertical)
    {
        scaledAndOffsetValue = 1.0f - scaledAndOffsetValue;
    }

    int dimension = getDimension();

    float minCoordinate = endOffset;
    float maxCoordinate = dimension - endOffset;
    float coordinateRange = maxCoordinate - minCoordinate;

    return coordinateRange * scaledAndOffsetValue + minCoordinate;
}

void Graduations::calculateTickIncrements()
{
    float dimension = getDimension();

    if (type == Linear)
    {
        // try to have a tick every 10 pixels or so
        float approxNumTicks = dimension / 10.0f;        
        float valueRange = maxValue - minValue;
        float approxTickIncrement = valueRange / approxNumTicks;
        float roundingValue = 0;

        smallTickIncrement = roundLinearTickIncrement (approxTickIncrement, roundingValue);

        largeTickIncrement = smallTickIncrement * 10.0f / roundingValue;

        minValue = floorToNearestX (minValue, largeTickIncrement);
        maxValue = ceilToNearestX (maxValue, largeTickIncrement);
    }
    else if (type == Logarithmic)
    {
        // logarithmic scales have to start above zero
        jassert (minValue > 0.0f && maxValue > 0.0f);

        minValue = previousPowerOfTen (minValue);
        maxValue = nextPowerOfTen (maxValue);
    }
}

void Graduations::calculateEndOffset()
{
    if (style & Vertical)
    {
        endOffset = fontHeight / 2.0f;
    }
    else if (style & Horizontal)
    {
        endOffset = fontHeight;
    }
}

int Graduations::getDimension()
{
    if (style & Vertical)
    {
        return getHeight();
    }
    else if (style & Horizontal)
    {
        return getWidth();
    }
}

void Graduations::paintLinearGraduations (Graphics &g)
{
    for (float value = minValue; value <= maxValue; value += smallTickIncrement)
    {
        float lineThickness = 1.0f;

        if (fmod (value, largeTickIncrement) == 0)
        {
            lineThickness = 2.0f;
            paintValue (g, value);
        }

        paintTick (g, value, lineThickness);
    }
}

void Graduations::paintLogarithmicGraduations (Graphics &g)
{
    int counter = 0;

    for (float value = minValue; value <= maxValue; value += previousPowerOfTen (value), counter = (counter + 1) % 9)
    {
        float lineThickness = 1.0f;

        if (counter == 0)
        {
            lineThickness = 2.0f;
            paintValue (g, value);
        }

        paintTick (g, value, lineThickness);
    }
}

void Graduations::paintTick (Graphics &g, float value, float lineThickness)
{
    float coordinate = valueToCoordinate (value);

    if (style == VerticalLeft)
    {
        float lineStartX = 2.0f * fontHeight;
        float lineEndX = getWidth();

        g.drawLine (lineStartX, coordinate, lineEndX, coordinate, lineThickness);
    }
    else if (style == VerticalCentre)
    {
        float line1StartX = 0.0f;
        float line1EndX = (getWidth() - 2.0f * fontHeight) / 2.0f;
        float line2StartX = getWidth() - line1EndX;
        float line2EndX = getWidth();

        g.drawLine (line1StartX, coordinate, line1EndX, coordinate, lineThickness);
        g.drawLine (line2StartX, coordinate, line2EndX, coordinate, lineThickness);
    }
    else if (style == VerticalRight)
    {
        float lineStartX = 0.0f;
        float lineEndX = getWidth() - 2.0f * fontHeight;

        g.drawLine (lineStartX, coordinate, lineEndX, coordinate, lineThickness);
    }
    else if (style == HorizontalBottom)
    {
        float lineStartY = 0.0f;
        float lineEndY = getHeight() - 1.2f * fontHeight;

        g.drawLine (coordinate, lineStartY, coordinate, lineEndY, lineThickness);
    }
    else if (style == HorizontalCentre)
    {
        float line1StartY = 0.0f;
        float line1EndY = (getHeight() - 1.2f * fontHeight) / 2.0f;
        float line2StartY = getHeight() - line1EndY;
        float line2EndY = getHeight();

        g.drawLine (coordinate, line1StartY, coordinate, line1EndY, lineThickness);
        g.drawLine (coordinate, line2StartY, coordinate, line2EndY, lineThickness);
    }
    else if (style == HorizontalTop)
    {
        float lineStartY = 1.2f * fontHeight;
        float lineEndY = getHeight();

        g.drawLine (coordinate, lineStartY, coordinate, lineEndY, lineThickness);
    }
}

void Graduations::paintValue (Graphics &g, float value)
{
    float coordinate = valueToCoordinate (value);

    g.setFont (fontHeight);

    int textWidth = 2 * fontHeight;
    int textX = 0;
    int textY = 0;

    if (style == VerticalLeft)
    {
        textX = 0;
        textY = coordinate - fontHeight / 2;
    }
    else if (style == VerticalCentre)
    {
        textX = (getWidth() - 2 * fontHeight) / 2;
        textY = coordinate - fontHeight / 2;
    }
    else if (style == VerticalRight)
    {
        textX = getWidth() - 2 * fontHeight;
        textY = coordinate - fontHeight / 2;
    }
    else if (style == HorizontalBottom)
    {
        textX = coordinate - fontHeight;
        textY = getHeight() - fontHeight;
    }
    else if (style == HorizontalCentre)
    {
        textX = coordinate - fontHeight;
        textY = (getHeight() - fontHeight) / 2;
    }
    else if (style == HorizontalCentre)
    {
        textX = coordinate - fontHeight;
        textY = 0;
    }

    g.drawFittedText (String (value), textX, textY, textWidth, fontHeight, Justification::centred, 1);
}

void Graduations::paintAxisLine (Graphics &g)
{
    int width = getWidth();
    int height = getHeight();
    float lineThickness = 2.0f;

    if (style == VerticalLeft)
    {
        g.drawLine (width - 1, endOffset, width - 1, height - endOffset, lineThickness);
    }
    else if (style == VerticalCentre)
    {
        g.drawLine (width - 1, endOffset, width - 1, height - endOffset, lineThickness);
        g.drawLine (1, endOffset, 1, height - endOffset, lineThickness);
    }
    else if (style == VerticalRight)
    {
        g.drawLine (1, endOffset, 1, height - endOffset, lineThickness);
    }
    else if (style == HorizontalBottom)
    {
        g.drawLine (endOffset, 1, width - endOffset, 1, lineThickness);
    }
    else if (style == HorizontalCentre)
    {
        g.drawLine (endOffset, 1, width - endOffset, 1, lineThickness);
        g.drawLine (endOffset, height - 1, width - endOffset, height - 1, lineThickness);
    }
    else if (style == HorizontalCentre)
    {
        g.drawLine (endOffset, height - 1, width - endOffset, height - 1, lineThickness);
    }
}

float Graduations::roundLinearTickIncrement (float value, float &roundingValue)
{
    float sigFig = previousPowerOfTen (value);
    float roundedValue = floor (value / sigFig);

    if (roundedValue <= 1)
    {
        roundedValue = 1;
    }
    else if (roundedValue <= 2)
    {
        roundedValue = 2;
    }
    else 
    {
        roundedValue = 5;
    }

    roundingValue = roundedValue;
    
    return sigFig * roundedValue;
}

float Graduations::previousPowerOfTen (float value)
{
    return pow (10.0f, floor (log10 (1.01 * value)));
}

float Graduations::nextPowerOfTen (float value)
{
    return pow (10.0f, ceil (log10 (value)));
}

float Graduations::floorToNearestX (float value, float x)
{
    return x * floor (value / x);
}

float Graduations::ceilToNearestX (float value, float x)
{
    return x * ceil (value / x);
}

#include "Graduations.h"

Graduations::Graduations (Style styleInit, Type typeInit, float minValueInit, float maxValueInit)
    : style (styleInit),
      type (typeInit),
      colour (Colours::black),
      fontHeight (10.0f),
      minValue (minValueInit),
      maxValue (maxValueInit)
{
    // the min value should be less than the max value
    jassert (minValueInit < maxValueInit);

    calculateTickIncrements();
    calculateEndOffset();
}

Graduations::~Graduations()
{
}

void Graduations::paint (Graphics &g)
{
    if (type == Linear)
    {
        paintLinearGraduations (g);
    }
    else if (type == Logarithmic)
    {
        paintLogarithmicGraduations (g);
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


void Graduations::setRange (int newMinValue, int newMaxValue)
{
    // the min value should be less than the max value
    jassert (newMinValue < newMaxValue);

    minValue = newMinValue;
    maxValue = newMaxValue;

    calculateTickIncrements();
    calculateEndOffset();
    
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

    if (style | Vertical)
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

    if (style | Vertical)
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
        // try to have a tick every 20 pixels or so
        float approxNumTicks = dimension / 20.0f;        
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
    }
}

void Graduations::calculateEndOffset()
{
    if (style | Vertical)
    {
        endOffset = fontHeight / 2.0f;
    }
    else if (style | Horizontal)
    {
        endOffset = 2.0f * fontHeight;
    }
}

int Graduations::getDimension()
{
    if (style | Vertical)
    {
        return getHeight();
    }
    else if (style | Horizontal)
    {
        return getWidth();
    }
}

void Graduations::paintLinearGraduations (Graphics &g)
{
    float x = 0, y = 0;
    float *coordinate;

    if (style | Vertical)
    {
        coordinate = &y;
    }
    else if (style | Horizontal)
    {
        coordinate = &x;
    }

    switch (style)
    {
        case VerticalLeft:
            break;
            
        case VerticalCentre:
            break;
            
        case VerticalRight:
            break;
            
        case HorizontalBottom:
            break;
            
        case HorizontalCentre:
            break;
            
        case HorizontalTop:
            break;
    }
}

void Graduations::paintLogarithmicGraduations (Graphics &g)
{
}

float Graduations::roundLinearTickIncrement (float value, float &roundingValue)
{
    float sigFig = pow (10.0f, floor (log10 (value)));
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

float Graduations::floorToNearestX (float value, float x)
{
    return x * floor (value / x);
}

float Graduations::ceilToNearestX (float value, float x)
{
    return x * ceil (value / x);
}

#include "../JuceLibraryCode/JuceHeader.h"
#include "BarGraph.h"

BarGraph::BarGraph()
    : value (0),
      peakPosition (0),
      peakColour (0xffff0000)
{
}

BarGraph::~BarGraph()
{
}

void BarGraph::paint (Graphics& g)
{
    int width = getWidth();
    int height = getHeight();

    // give us some background
    g.fillAll (Colours::black);

    // draw the level in
    int barTop = height * (1 - value);
    int barHeight = height * value;
    ColourGradient barGradient (Colour (0xff00ff00), 0, height, Colour (0xffff0000), 0, 0, false);
    barGradient.addColour (0.7, Colour (0xffffff00));
    g.setGradientFill (barGradient);
    g.fillRect (0, barTop, width, barHeight);

    // draw the peak level
    g.setColour (peakColour);
    g.drawLine (0, peakPosition, width, peakPosition, 2.0f);

    // do some fancy pretty making
    ColourGradient fancyGradient (Colour (0xaaffffff), 0, 0, Colour (0x00000000), width / 2, 0, false);
    g.setGradientFill (fancyGradient);
    g.fillAll();

    // draw a little border
    g.setColour (Colours::black);
    g.drawRect (0, 0, width, height);
}

void BarGraph::resized()
{
}

void BarGraph::setProportionFilled (double newValue)
{
    value = newValue;
    repaint();
}

void BarGraph::setPeakPosition (double newValue)
{
    peakPosition = getHeight() * (1 - newValue);
    repaint();
}

void BarGraph::setLevels (double proportionFilled, double peakLevel)
{
    value = proportionFilled;
    peakPosition = getHeight() * (1 - peakLevel);
    repaint();
}

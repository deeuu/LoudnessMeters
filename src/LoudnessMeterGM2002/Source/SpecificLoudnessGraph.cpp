#include "../JuceLibraryCode/JuceHeader.h"
#include "SpecificLoudnessGraph.h"

SpecificLoudnessGraph::SpecificLoudnessGraph()
    : MeterBallistics (numMeters, minPhons, maxPhons),
      width (0),
      height (0),
      labelSize (0),
      graphX (0),
      graphY (0),
      graphWidth (0),
      graphHeight (0),
      graduationColour (Colours::black),
      traceColour (0xaa00ff00)
{
    for (unsigned int i = 0; i < numMeters; ++i)
    {
        setMeterRiseTime (i, 10);
        setMeterDecayTime (i, 1000);
    }
}

SpecificLoudnessGraph::~SpecificLoudnessGraph()
{
}

void SpecificLoudnessGraph::paint (Graphics& g)
{
    // draw background
    g.setColour (Colours::black);
    g.fillRect (graphX, graphY, graphWidth, graphHeight);

    // draw trace
    g.saveState();
    g.setColour (traceColour);
    g.reduceClipRegion (graphX, graphY, graphWidth, graphHeight);

    Path tracePath;
    float x = graphX;
    float xIncrement = graphWidth / (numMeters - 1);
    tracePath.startNewSubPath (x, phonsToY (getMeterLevel (0)));

    for (unsigned int i = 1; i < numMeters; ++i)
    {
        x += xIncrement;
        tracePath.lineTo (x, phonsToY (getMeterLevel (i)));
    }

    g.strokePath (tracePath, PathStrokeType (2.0f));

    // draw axes
    g.restoreState();
    g.setColour (graduationColour);
    g.drawLine (graphX, graphY, graphX, graphY + graphHeight, 2);
    g.drawLine (graphX, graphY + graphHeight, graphX + graphWidth, graphY + graphHeight, 2);

    // draw Y graduations
    int x1 = 7 * labelSize / 8;

    float numYGraduations = (maxPhons - minPhons) / 2;
    float yGraduationDistance = (graphHeight - 1) / numYGraduations;
    float y = graphY + 1;

    for (int i = 0; i <= numYGraduations; ++i)
    {
        float lineWidth = 0.5f;

        if (i % 5 == 0)
        {
            lineWidth = 2.0f;

            String graduationValue (maxPhons - i * 2);
            g.drawFittedText (graduationValue, 0, y - labelSize / 4, x1 - 2, labelSize / 2, Justification::right, 1);
        }
        
        g.drawLine (x1, y, graphX, y, lineWidth);
        y += yGraduationDistance;
    }

    // draw X graduations
    int y1 = graphY + graphHeight;
    int y2 =  y1 + labelSize / 8;

    float xGraduationDistance = (graphWidth - 1) / 20.0f;
    x = graphX;

    int labelWidth = 7 * labelSize / 8;

    for (int i = 0; i < 21; ++i)
    {
        float lineWidth = 0.5f;

        if (i % 5 == 0)
        {
            lineWidth = 2.0f;

            String graduationValue (i * 2);
            g.drawFittedText (graduationValue, x - labelWidth / 2, y2 + 2, labelWidth, labelSize / 2, Justification::centred, 1);
        }
        
        g.drawLine (x, y1, x, y2, lineWidth);
        x += xGraduationDistance;
    }

}

void SpecificLoudnessGraph::resized()
{
    width = getWidth();
    height = getHeight();

    int minDimension = jmin (width, height);

    labelSize = minDimension / 8.5;

    graphX = labelSize;
    graphY = labelSize / 2;
    graphWidth = width - 1.5 * labelSize;
    graphHeight = height - 9 * labelSize / 8;
}

void SpecificLoudnessGraph::setGraduationColour (Colour newColour)
{
    graduationColour = newColour;
}

//==========================================================================
//      setting meter values
//==========================================================================
void SpecificLoudnessGraph::setSpecificLoudnessValues (const Array <double> &values)
{
    jassert (values.size() == numMeters);

    for (unsigned int i = 0; i < numMeters; ++i)
    {
        setMeterLevel (i, values [i]);
    }
}

float SpecificLoudnessGraph::phonsToY (double levelInPhons)
{
    return graphY + graphHeight - graphHeight * (levelInPhons - minPhons) / (maxPhons - minPhons);
}

void SpecificLoudnessGraph::meterLevelChanged (int index)
{
    repaint();
}

#include "../JuceLibraryCode/JuceHeader.h"
#include "StereoSpecificLoudnessGraph.h"

StereoSpecificLoudnessGraph::StereoSpecificLoudnessGraph()
    : MeterBallistics (0, minPhons, maxPhons),
      width (0),
      height (0),
      labelSize (0),
      graphX (0),
      graphY (0),
      graphWidth (0),
      graphHeight (0),
      graduationColour (Colours::black),
      leftTraceColour (0xff00ff00), rightTraceColour (0xffff0000),
      numMeters (0)
{
    for (int i = 0; i < numMeters; ++i)
    {
        setMeterRiseTime (i, 2000);
        setMeterDecayTime (i, 2000);
    }
}

StereoSpecificLoudnessGraph::~StereoSpecificLoudnessGraph()
{
}

void StereoSpecificLoudnessGraph::paint (Graphics& g)
{
    GenericScopedLock <CriticalSection> lock (mutex);

    // draw background
    g.setColour (Colours::black);
    g.fillRect (graphX, graphY, graphWidth, graphHeight);

    // draw trace
    g.saveState();
    g.reduceClipRegion (graphX, graphY, graphWidth, graphHeight);

    Path leftTracePath, rightTracePath;
    float x = camsToX (centreFrequencies [0]);
    leftTracePath.startNewSubPath (x, phonsToY (getMeterLevel (0)));
    rightTracePath.startNewSubPath (x, phonsToY (getMeterLevel (1)));

    for (int i = 1; i < numMeters / 2; ++i)
    {
        x = camsToX (centreFrequencies [i]);
        leftTracePath.lineTo (x, phonsToY (getMeterLevel (i * 2)));
        rightTracePath.lineTo (x, phonsToY (getMeterLevel (i * 2 + 1)));
    }

    g.setColour (leftTraceColour);
    g.strokePath (leftTracePath, PathStrokeType (2.0f));

    g.setColour (rightTraceColour);
    g.strokePath (rightTracePath, PathStrokeType (2.0f));

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

void StereoSpecificLoudnessGraph::resized()
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

void StereoSpecificLoudnessGraph::setGraduationColour (Colour newColour)
{
    graduationColour = newColour;
}

//==========================================================================
//      setting meter values
//==========================================================================
void StereoSpecificLoudnessGraph::setSpecificLoudnessValues (const Array <double> &frequencies, const Array <double> &leftValues, const Array <double> &rightValues)
{
    GenericScopedLock <CriticalSection> lock (mutex);

    // left and right values should contain the same number of elements
    jassert (leftValues.size() == rightValues.size());

    int newNumMeters = leftValues.size() * 2;

    if (numMeters != newNumMeters)
    {
        setNumMeters (newNumMeters);
        centreFrequencies = frequencies;
        numMeters = newNumMeters;

		for (int i = 0; i < numMeters; ++i)
        {
            setMeterDecayTime (i, 500);
        }
    }

    for (int i = 0; i < numMeters / 2; ++i)
    {
        setMeterLevel (i * 2, leftValues [i]);
        setMeterLevel (i * 2 + 1, rightValues [i]);
    }

    repaint();
}

float StereoSpecificLoudnessGraph::phonsToY (double levelInPhons)
{
    return graphY + graphHeight - graphHeight * (levelInPhons - minPhons) / (maxPhons - minPhons);
}

float StereoSpecificLoudnessGraph::camsToX (double frequencyInCams)
{
    return graphWidth * frequencyInCams / 40.2 + graphX;
}

void StereoSpecificLoudnessGraph::meterLevelChanged (int index)
{
    repaint();
}

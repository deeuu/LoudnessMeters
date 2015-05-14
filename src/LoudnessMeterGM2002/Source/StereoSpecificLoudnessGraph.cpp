#include "../JuceLibraryCode/JuceHeader.h"
#include "StereoSpecificLoudnessGraph.h"

StereoSpecificLoudnessGraph::StereoSpecificLoudnessGraph()
    : MeterBallistics (0, 0.01, 2.0f, false),
      graduationColour (Colours::black),
      leftTraceColour (0xff00ff00), rightTraceColour (0xffff0000),
      labelHeight (20.0f),
      graphX (0), graphY (0), graphWidth (0), graphHeight (0),
      xGraduationsX (0), xGraduationsY (0), xGraduationsWidth (20), xGraduationsHeight (20),
      yGraduationsX (labelHeight), yGraduationsY (0), yGraduationsWidth (30), yGraduationsHeight (30),
      minCams (0), maxCams (40),
      minLevel (0.01), maxLevel (2.0f),
      numMeters (0),
      xGraduations (Graduations::HorizontalBottom, Graduations::Linear),
      yGraduations (Graduations::VerticalLeft, Graduations::Logarithmic)
{
    setSize (200, 100);

    for (int i = 0; i < numMeters; ++i)
    {
        setMeterRiseTime (i, 2000);
        setMeterDecayTime (i, 2000);
    }

    addAndMakeVisible (xGraduations);
    addAndMakeVisible (yGraduations);

    xGraduations.setAndGetRange (minCams, maxCams);
    yGraduations.setAndGetRange (minLevel, maxLevel);

    setMeterRange (minLevel, maxLevel);

    xGraduations.showAxisLine (true);
    yGraduations.showAxisLine (true);
}

StereoSpecificLoudnessGraph::~StereoSpecificLoudnessGraph()
{
}

void StereoSpecificLoudnessGraph::paint (Graphics& g)
{
    // draw graph background
    g.setColour (Colours::black);
    g.fillRect (graphX, graphY, graphWidth, graphHeight);

    // draw traces
    GenericScopedLock <CriticalSection> lock (mutex);

    g.saveState();
    g.reduceClipRegion (graphX, graphY, graphWidth, graphHeight);

    Path leftTracePath, rightTracePath;
    float x = camsToX (centreFrequencies [0]);
    leftTracePath.startNewSubPath (x, levelToY (getMeterLevel (0)));
    rightTracePath.startNewSubPath (x, levelToY (getMeterLevel (1)));

    for (int i = 1; i < numMeters / 2; ++i)
    {
        x = camsToX (centreFrequencies [i]);
        leftTracePath.lineTo (x, levelToY (getMeterLevel (i * 2)));
        rightTracePath.lineTo (x, levelToY (getMeterLevel (i * 2 + 1)));
    }

    g.setColour (leftTraceColour);
    g.strokePath (leftTracePath, PathStrokeType (2.0f));

    g.setColour (rightTraceColour);
    g.strokePath (rightTracePath, PathStrokeType (2.0f));

    g.restoreState();

    // draw axis labels
    g.setColour (graduationColour);

    g.drawFittedText ("Frequency (cams)", graphX, getHeight() - labelHeight, graphWidth, labelHeight, Justification::centred, 1);

    g.addTransform (AffineTransform::rotation (- float_Pi / 2.0f, 0.0f, graphY + graphHeight));
    g.drawFittedText ("Specific Loudness (sones)", 0.0f, graphY + graphHeight, graphHeight, labelHeight, Justification::centred, 1);
}

void StereoSpecificLoudnessGraph::resized()
{
    int width = getWidth();
    int height = getHeight();

    float xGraduationsEndOffset = xGraduations.getEndOffset();
    float yGraduationsEndOffset = yGraduations.getEndOffset();

    xGraduationsX = yGraduationsX + yGraduationsWidth - xGraduationsEndOffset;
    xGraduationsY = height - xGraduationsHeight - yGraduationsEndOffset - 1 - labelHeight;
    xGraduationsWidth = width - xGraduationsX;
    
    yGraduationsHeight = xGraduationsY - yGraduationsY + yGraduationsEndOffset + 1;

    graphX = xGraduationsX + xGraduationsEndOffset - 1;
    graphY = yGraduationsY + yGraduationsEndOffset - 1;
    graphWidth = xGraduationsWidth - 2 * xGraduationsEndOffset + 2;
    graphHeight = yGraduationsHeight - 2 * yGraduationsEndOffset + 2;

    xGraduations.setBounds (xGraduationsX, xGraduationsY, xGraduationsWidth, xGraduationsHeight);
    yGraduations.setBounds (yGraduationsX, yGraduationsY, yGraduationsWidth, yGraduationsHeight);
}

void StereoSpecificLoudnessGraph::setGraphBounds (int x, int y, int width, int height)
{
    int componentY = y - yGraduations.getEndOffset() + 1 - yGraduationsY;
    int componentHeight = height + yGraduations.getEndOffset() - 1 + xGraduationsHeight + labelHeight;
    setBounds (x, componentY, width, componentHeight);
}

void StereoSpecificLoudnessGraph::setGraduationColour (Colour newColour)
{
    graduationColour = newColour;
    xGraduations.setColour (newColour);
    yGraduations.setColour (newColour);
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

float StereoSpecificLoudnessGraph::levelToY (double level)
{
    return yGraduationsY + yGraduations.valueToCoordinate (level);
}

float StereoSpecificLoudnessGraph::camsToX (double frequencyInCams)
{
    return xGraduationsX + xGraduations.valueToCoordinate (frequencyInCams);
}

void StereoSpecificLoudnessGraph::meterLevelChanged (int index)
{
    repaint();
}

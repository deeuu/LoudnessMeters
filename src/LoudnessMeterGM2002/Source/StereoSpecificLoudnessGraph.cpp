#include "../JuceLibraryCode/JuceHeader.h"
#include "StereoSpecificLoudnessGraph.h"

StereoSpecificLoudnessGraph::StereoSpecificLoudnessGraph()
    : MeterBallistics (0, 0.01, 2.0f),
      graduationColour (Colours::black),
      leftTraceColour (0xff00ff00), rightTraceColour (0xffff0000),
      graphX (0), graphY (0), graphWidth (0), graphHeight (0),
      xGraduationsX (0), xGraduationsY (0), xGraduationsWidth (20), xGraduationsHeight (20),
      yGraduationsX (0), yGraduationsY (0), yGraduationsWidth (30), yGraduationsHeight (30),
      minCams (0), maxCams (40),
      minPhons (0.01), maxPhons (2.0f),
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
    yGraduations.setAndGetRange (minPhons, maxPhons);

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
}

void StereoSpecificLoudnessGraph::resized()
{
    int width = getWidth();
    int height = getHeight();

    float xGraduationsEndOffset = xGraduations.getEndOffset();
    float yGraduationsEndOffset = yGraduations.getEndOffset();

    xGraduationsX = yGraduationsWidth - xGraduationsEndOffset;
    xGraduationsY = height - xGraduationsHeight;
    xGraduationsWidth = width - yGraduationsWidth;
    
    yGraduationsHeight = xGraduationsY + yGraduationsEndOffset;

    graphX = xGraduationsX + xGraduationsEndOffset;
    graphY = yGraduationsY + yGraduationsEndOffset;
    graphWidth = xGraduationsWidth - 2 * xGraduationsEndOffset;
    graphHeight = yGraduationsHeight - 2 * yGraduationsEndOffset;

    xGraduations.setBounds (xGraduationsX, xGraduationsY, xGraduationsWidth, xGraduationsHeight);
    yGraduations.setBounds (yGraduationsX, yGraduationsY, yGraduationsWidth, yGraduationsHeight);
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

float StereoSpecificLoudnessGraph::phonsToY (double levelInPhons)
{
}

float StereoSpecificLoudnessGraph::camsToX (double frequencyInCams)
{
}

void StereoSpecificLoudnessGraph::meterLevelChanged (int index)
{
    repaint();
}

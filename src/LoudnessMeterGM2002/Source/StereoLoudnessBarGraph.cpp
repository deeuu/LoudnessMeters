#include "StereoLoudnessBarGraph.h"

StereoLoudnessBarGraph::StereoLoudnessBarGraph()
    : MeterBallistics (4, 0, 34),
      labelHeight (20),
      minLevel (0), maxLevel (34),
      barWidth (20),
      graduationColour (Colours::black),
      graduations (Graduations::VerticalCentre, Graduations::Linear)
{
    addAndMakeVisible (bars [0]);
    addAndMakeVisible (bars [1]);
    addAndMakeVisible (graduations);

    setMeterRiseTime (0, 10);
    setMeterRiseTime (1, 10);
    setMeterRiseTime (2, 10);
    setMeterRiseTime (3, 10);

    setMeterDecayTime (0, 10);
    setMeterDecayTime (1, 5000);
    setMeterDecayTime (2, 10);
    setMeterDecayTime (3, 5000);

    setMeterHoldTime (1, 1000);
    setMeterHoldTime (3, 1000);

    graduations.setColour (graduationColour);
    graduations.setFontHeight (14.0f);

    setRange (minLevel, maxLevel);
}

StereoLoudnessBarGraph::~StereoLoudnessBarGraph()
{
}

void StereoLoudnessBarGraph::paint (Graphics& g)
{
    int height = getHeight();
    int width = getWidth();

    // draw labels
    g.setColour (graduationColour);

    int channelLabelY = height - 3 * labelHeight;

    g.drawFittedText ("L", 0, channelLabelY, barWidth, labelHeight, Justification::centred, 1);
    g.drawFittedText ("R", 3 * barWidth, channelLabelY, barWidth, labelHeight, Justification::centred, 1);

    g.drawFittedText ("Long-Term Loudness\n(sones)", 0, height - 2 * labelHeight, width, 2 * labelHeight, Justification::centred, 2);
}

void StereoLoudnessBarGraph::resized()
{
    int width = getWidth();
    int height = getHeight();

    int graduationWidth = width / 2;
    int graduationHeight = height - 3 * labelHeight + graduations.getEndOffset();

    int barY = graduations.getEndOffset() - 1;
    barWidth = width / 4;
    int barHeight = graduationHeight - 2 * graduations.getEndOffset() + 2;

    bars [0].setBounds (0, barY, barWidth, barHeight);
    bars [1].setBounds (barWidth + graduationWidth, barY, barWidth, barHeight);

    graduations.setBounds (barWidth, 0, graduationWidth, graduationHeight);
}

void StereoLoudnessBarGraph::setMeterBounds (int x, int y, int width, int height)
{
    int componentY = y - graduations.getEndOffset() + 1;
    int componentHeight = height + componentY + y + 3 * labelHeight;
    setBounds (x, componentY, width, componentHeight);
}

void StereoLoudnessBarGraph::setGraduationColour (Colour newColour)
{
    graduationColour = newColour;
    graduations.setColour (graduationColour);
}

void StereoLoudnessBarGraph::setRange (float newMinLevel, float newMaxLevel)
{
    graduations.setAndGetRange (newMinLevel, newMaxLevel);
    setMeterRange (newMinLevel, newMaxLevel);
    
    minLevel = newMinLevel;
    maxLevel = newMaxLevel;
}

void StereoLoudnessBarGraph::setMeterLevels (float leftLevel, float leftPeak, float rightLevel, float rightPeak)
{
    setMeterLevel (0, leftLevel);    
    setMeterLevel (1, leftPeak);
    setMeterLevel (2, rightLevel);
    setMeterLevel (3, rightPeak);
}

void StereoLoudnessBarGraph::meterLevelChanged (int index)
{
    float phonsRange = maxLevel - minLevel;

    float leftLevel = (getMeterLevel (0) - minLevel) / phonsRange;
    float leftPeak = (getMeterLevel (1) - minLevel) / phonsRange;
    bars [0].setLevels (leftLevel, leftPeak);

    float rightLevel = (getMeterLevel (2) - minLevel) / phonsRange;
    float rightPeak = (getMeterLevel (3) - minLevel) / phonsRange;
    bars [1].setLevels (rightLevel, rightPeak);
}

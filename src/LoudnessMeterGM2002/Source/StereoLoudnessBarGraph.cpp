#include "StereoLoudnessBarGraph.h"

StereoLoudnessBarGraph::StereoLoudnessBarGraph()
    : MeterBallistics (4, 0, 34),
      minPhons (0), maxPhons (34),
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
    setMeterDecayTime (1, 10);
    setMeterDecayTime (2, 10);
    setMeterDecayTime (3, 10);

    graduations.setColour (graduationColour);
    graduations.setFontHeight (14.0f);
}

StereoLoudnessBarGraph::~StereoLoudnessBarGraph()
{
}

void StereoLoudnessBarGraph::paint (Graphics& g)
{
}

void StereoLoudnessBarGraph::resized()
{
    int width = getWidth();
    int height = getHeight();

    int graduationWidth = width / 2;
    int graduationHeight = height - 20;

    int barWidth = width / 4;
    int barHeight = graduationHeight - 2 * graduations.getEndOffset() + 2;

    int barY = graduations.getEndOffset() - 1;

    bars [0].setBounds (0, barY, barWidth, barHeight);
    bars [1].setBounds (barWidth + graduationWidth, barY, barWidth, barHeight);

    graduations.setBounds (barWidth, 0, graduationWidth, graduationHeight);
}

void StereoLoudnessBarGraph::setGraduationColour (Colour newColour)
{
    graduationColour = newColour;
    graduations.setColour (graduationColour);
}

void StereoLoudnessBarGraph::setPhonsRange (float newMinPhons, float newMaxPhons)
{
    graduations.setAndGetRange (newMinPhons, newMaxPhons);
    setMeterRange (newMinPhons, newMaxPhons);
    
    minPhons = newMinPhons;
    maxPhons = newMaxPhons;
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
    float phonsRange = maxPhons - minPhons;

    float leftLevel = (getMeterLevel (0) - minPhons) / phonsRange;
    float leftPeak = (getMeterLevel (1) - minPhons) / phonsRange;
    bars [0].setLevels (leftLevel, leftPeak);

    float rightLevel = (getMeterLevel (2) - minPhons) / phonsRange;
    float rightPeak = (getMeterLevel (3) - minPhons) / phonsRange;
    bars [1].setLevels (rightLevel, rightPeak);
}

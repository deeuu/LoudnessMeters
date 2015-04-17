#include "StereoLoudnessBarGraph.h"

StereoLoudnessBarGraph::StereoLoudnessBarGraph()
    : MeterBallistics (4, 40, 120),
      width (0),
      height (0),
      barWidth (0),
      barHeight (0),
      minPhons (40), maxPhons (120),
      graduationColour (Colours::black)
{
    addAndMakeVisible (bars [0]);
    addAndMakeVisible (bars [1]);

    setMeterRiseTime (0, 10);
    setMeterRiseTime (1, 10);
    setMeterRiseTime (2, 10);
    setMeterRiseTime (3, 10);

    setMeterDecayTime (0, 500);
    setMeterDecayTime (1, 2000);
    setMeterDecayTime (2, 500);
    setMeterDecayTime (3, 2000);
}

StereoLoudnessBarGraph::~StereoLoudnessBarGraph()
{
}

void StereoLoudnessBarGraph::paint (Graphics& g)
{
    // draw graduations
    Colour lineColour (graduationColour);
    g.setColour (lineColour);

    int x1 = 1.5 * barWidth;
    int x2 = 1.75 * barWidth;
    int x3 = 3.25 * barWidth;
    int x4 = 3.5 * barWidth;

    double phonsRange = maxPhons - minPhons;
    float graduationDistance = 2 * (barHeight - 4) / phonsRange;
    float y = barWidth / 4.0f + 2;

    for (int i = 0; i < phonsRange / 2 + 1; ++i)
    {
        float lineWidth = 0.5f;

        if (i % 5 == 0)
        {
            lineWidth = 2.0f;

            String graduationValue (maxPhons - i * 2);
            g.drawFittedText (graduationValue, x2, y - barWidth / 2.0f, 1.5 * barWidth, barWidth, Justification::centred, 1);
        }
        
        g.drawLine (x1, y, x2, y, lineWidth);
        g.drawLine (x3, y, x4, y, lineWidth);
        y += graduationDistance;
    }

    // draw labels
    g.drawFittedText ("L", barWidth / 2, height - 1.5 * barWidth, barWidth, barWidth, Justification::centred, 1);
    g.drawFittedText ("R", 3.5 * barWidth, height - 1.5 * barWidth, barWidth, barWidth, Justification::centred, 1);
}

void StereoLoudnessBarGraph::resized()
{
    width = getWidth();
    height = getHeight();
    barWidth = width / 5;
    barHeight = height - 2.25 * barWidth;

    bars [0].setBounds (barWidth / 2, barWidth / 4, barWidth, barHeight);
    bars [1].setBounds (3.5 * barWidth, barWidth / 4, barWidth, barHeight);
}

void StereoLoudnessBarGraph::setGraduationColour (Colour newColour)
{
    graduationColour = newColour;
}

void StereoLoudnessBarGraph::setPhonsRange (double newMinPhons, double newMaxPhons)
{
    setMeterRange (newMinPhons, newMaxPhons);
    
    minPhons = newMinPhons;
    maxPhons = newMaxPhons;

}

void StereoLoudnessBarGraph::setMeterLevels (double leftLevel, double leftPeak, double rightLevel, double rightPeak)
{
    setMeterLevel (0, leftLevel);    
    setMeterLevel (1, leftPeak);
    setMeterLevel (2, rightLevel);
    setMeterLevel (3, rightPeak);
}

void StereoLoudnessBarGraph::meterLevelChanged (int index)
{
    double phonsRange = maxPhons - minPhons;

    double leftLevel = (getMeterLevel (0) - minPhons) / phonsRange;
    double leftPeak = (getMeterLevel (1) - minPhons) / phonsRange;
    bars [0].setLevels (leftLevel, leftPeak);

    double rightLevel = (getMeterLevel (2) - minPhons) / phonsRange;
    double rightPeak = (getMeterLevel (3) - minPhons) / phonsRange;
    bars [1].setLevels (rightLevel, rightPeak);
}

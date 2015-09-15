#ifndef LOUDNESS_CONFIG_H_INCLUDED
#define LOUDNESS_CONFIG_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

struct LoudnessParameters
{
    double modelRate, camSpacing, compression;
    int filter;
};

struct LoudnessValues
{
    double leftSTL, rightSTL, leftPeakSTL, rightPeakSTL, overallPeakSTL;
    double leftLTL, rightLTL, overallLTL, averageSPL;
    Array <double> centreFrequencies, leftSpecificLoudness, rightSpecificLoudness;
};

#endif  // LOUDNESS_CONFIG_H_INCLUDED

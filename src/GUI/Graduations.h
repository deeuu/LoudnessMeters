#ifndef GRADUATIONS_H_INCLUDED
#define GRADUATIONS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Graduations : public Component
{
public:
    enum Style
    {
        VerticalLeft = 0x11,
        VerticalCentre = 0x12,
        VerticalRight = 0x13,
        HorizontalBottom = 0x21,
        HorizontalCentre = 0x22,
        HorizontalTop = 0x23
    };

    enum Type
    {
        Linear,
        Logarithmic
    };

    Graduations (Style styleInit, Type typeInit);
    ~Graduations();

    // appearance functions
    virtual void paint (Graphics &g) override;
    virtual void resized() override;
    void setColour (Colour newColour);
    void setFontHeight (float newFontHeight);
    void showAxisLine (bool newValue);

    void setAndGetRange (float &newMinValue, float &newMaxValue);

    // get position info
    float getEndOffset();

    // utility functions
    float coordinateToValue (float coordinate);
    float valueToCoordinate (float value);
    
private:
    Style style;
    Type type;
    Colour colour;
    float fontHeight;

    bool isAxis;
    
    float minValue, maxValue;
    float smallTickIncrement, largeTickIncrement;
    float endOffset;

    void calculateTickIncrements();
    void calculateEndOffset();

    int getDimension();

    void paintLinearGraduations (Graphics &g);
    void paintLogarithmicGraduations (Graphics &g);
    void paintTick (Graphics &g, float value, float lineThickness);
    void paintValue (Graphics &g, float value);
    void paintAxisLine (Graphics &g);

    static float roundLinearTickIncrement (float value, float &roundingValue);
    static float previousPowerOfTen (float value);
    static float nextPowerOfTen (float value);
    static float floorToNearestX (float value, float x);
    static float ceilToNearestX (float value, float x);

    enum Orientation
    {
        Vertical = 0x10,
        Horizontal = 0x20
    };
};

#endif // GRADUATIONS_H_INCLUDED

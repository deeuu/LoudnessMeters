#ifndef __GRADUATIONS__
#define __GRADUATIONS__

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

    Graduations (Style styleInit, Type typeInit, float minValueInit = 0.0f, float maxValueInit = 10.0f);
    ~Graduations();

    // appearance functions
    virtual void paint (Graphics &g) override;
    virtual void resized() override;
    void setColour (Colour newColour);
    void setFontHeight (float newFontHeight);

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

    float roundLinearTickIncrement (float value, float &roundingValue);
    float floorToNearestX (float value, float x);
    float ceilToNearestX (float value, float x);

    enum Orientation
    {
        Vertical = 0x10,
        Horizontal = 0x20
    };
};

#endif // __GRADUATIONS__

#include<Lumineer_LEDAnimation.h>

void SolidColor::Initialize(Adafruit_NeoPixel& strip)
{
    return;
}

void SolidColor::Step(Adafruit_NeoPixel& strip)
{
    AnimationUtils::ColorWipe(strip, _color, 0);
}

void SolidColor::Trigger()
{
    // nothing to do
}
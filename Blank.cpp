#include<Lumineer_LEDAnimation.h>

void Blank::Initialize(Adafruit_NeoPixel& strip)
{
    // nothing to initialzie
}

void Blank::Step(Adafruit_NeoPixel& strip)
{
    AnimationUtils::ColorWipe(strip, Adafruit_NeoPixel::Color(0,0,0), 0);
}

void Blank::Trigger()
{
    // nothing to do
}
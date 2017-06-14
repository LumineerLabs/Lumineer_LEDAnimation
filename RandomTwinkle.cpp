#include<Lumineer_LEDAnimation.h>

void RandomTwinkle::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = millis() - _interval;
}

void RandomTwinkle::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();
    uint16_t i;
    if (time - _lastUpdate >= _interval)
    {
        _lastUpdate = time;

        AnimationUtils::ColorWipe(strip, 0, 0);

        for (i = 0; i < strip.numPixels(); i++)
        {
            uint8_t rand = random(_numOff + 1);

            if (rand <= _numOn)
            {
                strip.setPixelColor(i, _color);
            }
        }
        strip.show();
    }
}

void RandomTwinkle::Trigger()
{
    // nothing to do
}
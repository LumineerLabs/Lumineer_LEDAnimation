#include<Lumineer_LEDAnimation.h>

void VU::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = 0;
    _numOn = 0;
    _numOff = 0;
}

void VU::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();
    uint16_t i;
    if (_lastUpdate == 0)
    {
        _lastUpdate = time;
        uint16_t left = ((strip.numPixels() / 2) * _numOn) / 0xFF;
        uint16_t right = ((strip.numPixels() / 2) * _numOff) / 0xFF;

        AnimationUtils::ColorWipe(strip, 0, 0);

        for (i = 0; i < strip.numPixels(); i++)
        {
            if (i < strip.numPixels() / 2)
            {
                if (i >= ((strip.numPixels() / 2) - (right)))
                {
                    strip.setPixelColor(i, _color);
                }
            }
            else
            {
                if (i < ((strip.numPixels() / 2) + left))
                {
                    strip.setPixelColor(i, _color);
                }
            }
        }
        strip.show();
    }
}

void VU::Trigger()
{
    // nothing to do
}
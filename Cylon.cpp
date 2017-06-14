#include<Lumineer_LEDAnimation.h>

void Cylon::Initialize(Adafruit_NeoPixel& strip)
{
    uint8_t i = 0;
    _lastUpdate = millis() - _interval;

    for (i = 0; i < _width; i++)
    {
        strip.setPixelColor(i, _colors[0]);
    }
    for (; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, _colors[1]);
    }
    _startStep = 0;
    strip.show();
}

void Cylon::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();

    if (time - _lastUpdate >= _interval)
    {
        _lastUpdate = time;
        if (_startStep < (strip.numPixels() - _width))
        {
            uint8_t i = 0;
            uint8_t *pixels = strip.getPixels();
            for (i = strip.numPixels() - 1; i > 0; i--)
            {
                strip.setPixelColor(i, strip.getPixelColor(i - 1));
            }
            strip.setPixelColor(0, _colors[1]);
        }
        else
        {
            uint8_t i = 0;
            uint8_t *pixels = strip.getPixels();
            for (i = 0; i < strip.numPixels() - 1; i++)
            {
                strip.setPixelColor(i, strip.getPixelColor(i + 1));
            }
            strip.setPixelColor(strip.numPixels() - 1, _colors[1]);
        }
        _startStep = (_startStep + 1) % ((2 * strip.numPixels()) - (2 * _width));
        strip.show();
    }
}

void Cylon::Trigger()
{
    // nothing to do
}
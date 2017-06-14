#include <Lumineer_LEDAnimation.h>

void RandomFadingPulse::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = 0;
    _startColor = 0;
    _numSteps = 10;
    _currentStep = 0;
    _chaseDirection = 0;
    _interval = 100;

    AnimationUtils::ColorWipe(strip, 0, 0);
}

void RandomFadingPulse::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();
    uint8_t i = 0;

    if (time - _lastUpdate >= _interval)
    {
        _lastUpdate = time;

        for (i = strip.numPixels() - 1; i > 0; i--)
        {
            strip.setPixelColor(i, strip.getPixelColor(i - 1));
        }

        if (_currentStep == 0)
        {
            uint8_t rand = random(50);
            if (rand == 0)
            {
                _currentStep = _numSteps;
                _startColor = AnimationUtils::GetRandomVibrantColor();
                strip.setPixelColor(0, _startColor);
            }
            else
            {
                strip.setPixelColor(0, 0);
            }
        }
        else
        {
            uint16_t gradientStep = _numSteps - _currentStep;
            uint32_t color = AnimationUtils::GetGradientColor(_startColor, 0, _numSteps, gradientStep);
            strip.setPixelColor(0, color);
            _currentStep--;
        }
        strip.show();
    }
}

void RandomFadingPulse::Trigger()
{
    // nothing to do
}
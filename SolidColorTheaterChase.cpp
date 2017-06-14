#include<Lumineer_LEDAnimation.h>

void SolidColorTheaterChase::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = millis() - _interval;

    _firstLEDState = 1;
    _firstTransitionIndex = 1;
    _chaseDirection = 1;
}

void SolidColorTheaterChase::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();

    if (time - _lastUpdate >= _interval)
    {
        uint8_t on = _firstLEDState;
        uint8_t numLeft = _firstTransitionIndex;

        if (numLeft == 0)
        {
            if (on)
            {
                numLeft = _numOn;
            }
            else
            {
                numLeft = _numOff;
            }
        }
        _lastUpdate = millis();

        for (uint8_t i = 0; i < strip.numPixels(); i++)
        {
            if (on)
            {
                numLeft--;
                if (_chaseDirection == 0)
                {
                    strip.setPixelColor(i, _color);
                }
                else
                {
                    strip.setPixelColor(strip.numPixels() - i - 1, _color);
                }
                if (numLeft == 0)
                {
                    on = 0;
                    numLeft = _numOff;
                }
            }
            else
            {
                numLeft--;
                if (_chaseDirection == 0)
                {
                    strip.setPixelColor(i, 0);
                }
                else
                {
                    strip.setPixelColor(strip.numPixels() - i - 1, 0);
                }
                if (numLeft == 0)
                {
                    on = 1;
                    numLeft = _numOn;
                }
            }
        }
        _firstTransitionIndex++;
        if (_firstLEDState &&
            _firstTransitionIndex > _numOn)
        {
            _firstTransitionIndex = 1;
            _firstLEDState = 0;
        }
        else if (!_firstLEDState &&
                 _firstTransitionIndex > _numOff)
        {
            _firstTransitionIndex = 1;
            _firstLEDState = 1;
        }
        strip.show();
    }
}

void SolidColorTheaterChase::Trigger()
{
    // nothing to do
}
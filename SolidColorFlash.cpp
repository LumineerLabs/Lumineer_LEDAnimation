#include<Lumineer_LEDAnimation.h>

void SolidColorFlash::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = millis() - _interval;
    _currentGoal = 1;
}

void SolidColorFlash::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();
    if(time - _lastUpdate >= _interval)
    {
        _lastUpdate = time;
        if(_currentGoal == 0)
        {
            _currentGoal = 1;
            AnimationUtils::ColorWipe(strip, 0, 0);
        }
        else
        {
            _currentGoal = 0;
            AnimationUtils::ColorWipe(strip, _color, 0);
        }
    }
}

void SolidColorFlash::Trigger()
{
    // nothing to do
}
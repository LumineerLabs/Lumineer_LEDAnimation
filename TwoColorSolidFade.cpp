#include<Lumineer_LEDAnimation.h>

void TwoColorSolidFade::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = millis() - _interval;
    _currentStep = 0;
    _currentGoal = 1;
}

void TwoColorSolidFade::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();

    if (time - _lastUpdate >= _interval)
    {
        uint32_t goal = _colors[_currentGoal];
        uint32_t start = _colors[_currentGoal ? 0 : 1];
        
        _lastUpdate = time;

        uint32_t draw = AnimationUtils::GetGradientColor(start, goal, _numSteps, _currentStep); //strip.Color(red, green, blue);

        AnimationUtils::ColorWipe(strip, draw, 0);

        if (_currentStep == _numSteps)
        {
            _currentGoal = _currentGoal ? 0 : 1;
            _currentStep = 0;
        }
        else
        {
            _currentStep++;
        }
    }
}

void TwoColorSolidFade::Trigger()
{
    // nothing to do
}
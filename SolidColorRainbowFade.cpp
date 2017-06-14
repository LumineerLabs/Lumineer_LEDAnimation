#include<Lumineer_LEDAnimation.h>

void SolidColorRainbowFade::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = millis() - _interval;
    /*if (_numStops == 7)
    {*/
        _startColor = AnimationUtils::rainbow7[0];
    /*}
    else if (_numStops == 10)
    {
        _color = rainbow10[0];
    }*/
    _currentStep = 0;
    _currentGoal = 1;
}

void SolidColorRainbowFade::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();

    if (time - _lastUpdate >= _interval)
    {
        uint32_t start, goal, current;
        _lastUpdate = time;

        start = _startColor;

        /*if (_numStops == 7)
        {*/
            goal = AnimationUtils::rainbow7[_currentGoal];
        /*}
        else if (_numStops == 10)
        {
            goal = rainbow10[_currentGoal];
        }*/

        current = AnimationUtils::GetGradientColor(start, goal, _numSteps, _currentStep);

        AnimationUtils::ColorWipe(strip, current, 0);

        if (_currentStep == _numSteps)
        {
            /*if (_numStops == 7)
            {*/
                _startColor = AnimationUtils::rainbow7[_currentGoal];
            /*}
            else if (_numStops == 10)
            {
                _color = rainbow10[_currentGoal];
            }*/
            _currentGoal = (_currentGoal + 1) % _numStops;
            _currentStep = 0;
        }
        else
        {
            _currentStep++;
        }
    }
}

void SolidColorRainbowFade::Trigger()
{
    // nothing to do
}
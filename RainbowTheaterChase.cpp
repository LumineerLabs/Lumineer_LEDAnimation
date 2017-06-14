#include<Lumineer_LEDAnimation.h>

void RainbowTheaterChase::Initialize(Adafruit_NeoPixel& strip)
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
    //_currentStep = 0;
    _currentGoal = 1;
    _firstLEDState = 1;
    _firstTransitionIndex = 1;
    _chaseDirection = 1;
}

void RainbowTheaterChase::Step(Adafruit_NeoPixel& strip)
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

        current = AnimationUtils::GetGradientColor(start, goal, _numSteps, _startStep);

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
        
        for (uint8_t i = 0; i < strip.numPixels(); i++)
        {
            if (on)
            {
                numLeft--;
                if (_chaseDirection == 0)
                {
                    strip.setPixelColor(i, current);
                }
                else
                {
                    strip.setPixelColor(strip.numPixels() - i - 1, current);
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

        if (_startStep == _numSteps)
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
            _startStep = 0;
        }
        else
        {
            _startStep++;
        }

        strip.show();
    }
}

void RainbowTheaterChase::Trigger()
{
    // nothing to do
}
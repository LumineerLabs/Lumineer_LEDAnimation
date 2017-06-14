#include<Lumineer_LEDAnimation.h>

void RainbowGradientTheaterChase::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = millis() - _interval;
    _currentGoal = 1; //starting at red going to orange
    _startStep = 0;
    _firstLEDState = 1;
    _firstTransitionIndex = 1;
    _chaseDirection = 1;
}

void RainbowGradientTheaterChase::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();
    if (time - _lastUpdate >= _interval)
    {
        _lastUpdate = time;
        uint8_t red, green, blue, goalRed, goalGreen, goalBlue, startRed, startGreen, startBlue, totalRedDiff, totalGreenDiff, totalBlueDiff, i, localGoal;
        uint16_t redDelta, greenDelta, blueDelta;
        uint32_t *rainbow;
        uint32_t goal;
        localGoal = _currentGoal;
        uint32_t start;
        /*if (_numStops == 7)
        {*/
            rainbow = AnimationUtils::rainbow7;
        /*}
        else if (_numStops == 10)
        {
            rainbow = rainbow10;
        }
        else
        {
            Serial.println("invalid number of stops");
        }*/
        if (_currentGoal > 0)
        {
            start = rainbow[_currentGoal - 1];
        }
        else
        {
            start = rainbow[_numStops - 1];
        }
        goal = rainbow[_currentGoal];

        goalRed = (0x00FF0000 & goal) >> 16;
        goalGreen = (0x0000FF00 & goal) >> 8;
        goalBlue = (0x000000FF & goal);

        startRed = (0x00FF0000 & start) >> 16;
        startGreen = (0x0000FF00 & start) >> 8;
        startBlue = (0x000000FF & start);

        totalRedDiff = abs(goalRed - startRed);
        totalGreenDiff = abs(goalGreen - startGreen);
        totalBlueDiff = abs(goalBlue - startBlue);

        red = startRed;
        green = startGreen;
        blue = startBlue;

        redDelta = (((uint16_t)_startStep * totalRedDiff) / _numSteps);
        greenDelta = (((uint16_t)_startStep * totalGreenDiff) / _numSteps);
        blueDelta = (((uint16_t)_startStep * totalBlueDiff) / _numSteps);

        if (redDelta >= totalRedDiff)
        {
            red = goalRed;
        }
        else
        {
            if (goalRed > startRed)
            {
                red += redDelta;
            }
            else
            {
                red -= redDelta;
            }
        }

        if (greenDelta >= totalGreenDiff)
        {
            green = goalGreen;
        }
        else
        {
            if (goalGreen > startGreen)
            {
                green += greenDelta;
            }
            else
            {
                green -= greenDelta;
            }
        }

        if (blueDelta >= totalBlueDiff)
        {
            blue = goalBlue;
        }
        else
        {
            if (goalBlue > startBlue)
            {
                blue += blueDelta;
            }
            else
            {
                blue -= blueDelta;
            }
        }

        strip.setPixelColor(0, red, green, blue);

        //start conditions set
        //generate the rest of the gradient
        redDelta = max(totalRedDiff / _numSteps, 1);
        greenDelta = max(totalGreenDiff / _numSteps, 1);
        blueDelta = max(totalBlueDiff / _numSteps, 1);

        for (i = 1; i < strip.numPixels(); i++)
        {
            if (goalRed == red && goalGreen == green && goalBlue == blue)
            {
                //set next local goal
                localGoal = (localGoal + 1) % _numStops;

                goal = rainbow[localGoal];

                goalRed = (0x00FF0000 & goal) >> 16;
                goalGreen = (0x0000FF00 & goal) >> 8;
                goalBlue = (0x000000FF & goal);

                totalRedDiff = abs(goalRed - red);
                totalGreenDiff = abs(goalGreen - green);
                totalBlueDiff = abs(goalBlue - blue);

                redDelta = max(totalRedDiff / _numSteps, 1);
                greenDelta = max(totalGreenDiff / _numSteps, 1);
                blueDelta = max(totalBlueDiff / _numSteps, 1);
            }

            if (abs(goalRed - red) < redDelta)
            {
                red = goalRed;
            }
            else if (goalRed > red)
            {
                red += redDelta;
            }
            else if (goalRed < red)
            {
                red -= redDelta;
            }

            if (abs(goalGreen - green) < greenDelta)
            {
                green = goalGreen;
            }
            else if (goalGreen > green)
            {
                green += greenDelta;
            }
            else if (goalGreen < green)
            {
                green -= greenDelta;
            }

            if (abs(goalBlue - blue) < blueDelta)
            {
                blue = goalBlue;
            }
            else if (goalBlue > blue)
            {
                blue += blueDelta;
            }
            else if (goalBlue < blue)
            {
                blue -= blueDelta;
            }

            strip.setPixelColor(i, red, green, blue);
        }

        if (_startStep == _numSteps)
        {
            _startStep = 0;
            _currentGoal = (_currentGoal + 1) % _numStops;
            //set next goal
        }
        else
        {
            _startStep++;
        }

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

void RainbowGradientTheaterChase::Trigger()
{
    // nothing to do
}
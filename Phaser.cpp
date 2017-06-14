#include<Lumineer_LEDAnimation.h>

void Phaser::Initialize(Adafruit_NeoPixel& strip)
{
    uint8_t i = 0;
    _lastUpdate = millis() - _interval;

    for (i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, _colors[1]);
    }
    _startStep = 0;
    _currentGoal = 0;
    //if (_numStops > 0)
    //{
        /*if (_numStops == 10)
        {
            _colors[0] = rainbow10[0];
        }
        else
        {*/
            _colors[0] = AnimationUtils::rainbow7[0];
        //}
    //}
    strip.show();
}

void Phaser::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();

    if (time - _lastUpdate >= _interval)
    {
        _lastUpdate = time;
        if (_flowDirection == 0)
        {
            uint8_t i = 0;
            for (i = strip.numPixels() - 1; i > 0; i--)
            {
                strip.setPixelColor(i, strip.getPixelColor(i - 1));
            }
            if (_startStep > 0)
            {
                strip.setPixelColor(0, _colors[0]);
                _startStep--;
            }
            else
            {
                strip.setPixelColor(0, _colors[1]);
            }
        }
        else if (_flowDirection == 1)
        {
            uint8_t i = 0;
            for (i = 0; i < strip.numPixels() - 1; i++)
            {
                strip.setPixelColor(i, strip.getPixelColor(i + 1));
            }
            if (_startStep > 0)
            {
                strip.setPixelColor(strip.numPixels() - 1, _colors[0]);
                _startStep--;
            }
            else
            {
                strip.setPixelColor(strip.numPixels() - 1, _colors[1]);
            }
        }
        else
        {
            uint8_t numSegments = _flowDirection;
            uint8_t dir = 1;
            uint16_t i, j;
            uint16_t pixelsPerSegment = strip.numPixels() / numSegments;

            for (i = 0; i < numSegments; i++)
            {
                for (j = 0; j < pixelsPerSegment - 1; j++)
                {
                    if (dir == 0)
                    {
                        uint16_t pixelIndex = (i * pixelsPerSegment) + (pixelsPerSegment - j);
                        strip.setPixelColor(pixelIndex, strip.getPixelColor(pixelIndex - 1));
                    }
                    else
                    {
                        uint16_t pixelIndex = (i * pixelsPerSegment) + (j);
                        strip.setPixelColor(pixelIndex, strip.getPixelColor(pixelIndex + 1));
                    }
                }

                if (dir == 0)
                {
                    uint16_t pixelIndex = (i * pixelsPerSegment); // + (pixelsPerSegment - j);
                    if (_startStep > 0)
                    {
                        strip.setPixelColor(pixelIndex, _colors[0]);
                        strip.setPixelColor(pixelIndex + 1, _colors[0]);
                    }
                    else
                    {
                        strip.setPixelColor(pixelIndex, _colors[1]);
                        strip.setPixelColor(pixelIndex + 1, _colors[1]);
                    }
                }
                else
                {
                    uint16_t pixelIndex = (i * pixelsPerSegment) + (j);
                    if (_startStep > 0)
                    {
                        strip.setPixelColor(pixelIndex, _colors[0]);
                    }
                    else
                    {
                        strip.setPixelColor(pixelIndex, _colors[1]);
                    }
                }

                if (_startStep > 0)
                {
                    _startStep--;
                }
                dir = (dir + 1) % 2;
            }
        }
        strip.show();
    }
}

void Phaser::Trigger()
{
    _currentGoal = (_currentGoal + 1) % _numStops;
    if(_numStops > 0)
    {
        /*if(_numStops == 10)
        {
        _colors[0] = rainbow10[_currentGoal];
        }
        else
        {*/
        _colors[0] = AnimationUtils::rainbow7[_currentGoal];
        //}
    }
    _startStep = _width;
}
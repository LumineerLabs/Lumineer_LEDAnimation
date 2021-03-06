#include<Lumineer_LEDAnimation.h>

void RainbowGradient::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = millis() - _interval;
    _currentGoal = 1; //starting at red going to orange
    _startStep = 0;
}

void RainbowGradient::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();
    if(time - _lastUpdate >= _interval)
    {
        _lastUpdate = time;
        uint32_t* rainbow;
        uint8_t localGoal;
        uint16_t localStep;
        uint8_t i;
        uint32_t goal;
        uint32_t start;
        uint32_t current;
        localGoal = _currentGoal;
        /*if(_numStops == 7)
        {*/
            rainbow = AnimationUtils::rainbow7;
        /*}
        else if(_numStops == 10)
        {
            rainbow = rainbow10;
        }
        else
        {
            Serial.println("invalid number of stops");
        }*/
        
        localStep = _startStep;
        
        for(i = 0; i < strip.numPixels(); i++)
        {
            goal = rainbow[localGoal];
            if(localGoal > 0)
            {
                start = rainbow[localGoal - 1];
            }
            else
            {
                start = rainbow[_numStops - 1];
            }
            current = AnimationUtils::GetGradientColor(start, goal, _numSteps, localStep);
            
            //Serial.println(current, HEX);
            strip.setPixelColor(i, current);
            if(localStep == _numSteps)
            {
                localStep = 0;
                localGoal = (localGoal + 1) % _numStops; 
                //set next goal
            }
            else
            {
                localStep++;
            }
        }
        
        if(_startStep == _numSteps)
        {
            _startStep = 0;
            _currentGoal = (_currentGoal + 1) % _numStops; 
            //set next goal
        }
        else
        {
            _startStep++;
        }    
        strip.show();
    }
}

void RainbowGradient::Trigger()
{
    // nothing to do
}
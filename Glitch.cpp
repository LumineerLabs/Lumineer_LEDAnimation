#include<Lumineer_LEDAnimation.h>

void Glitch::Initialize(Adafruit_NeoPixel& strip)
{
    _startStep = 0;
}

void Glitch::Step(Adafruit_NeoPixel& strip)
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
        //if(_numStops == 7)
        //{
        rainbow = AnimationUtils::rainbow7;
        //}
        /*else if(_numStops == 10)
        {
            rainbow = rainbow10;
        }
        else
        {
            Serial.println("invalid number of stops");
        }*/
        if(_currentGoal > 0)
        {
            start = rainbow[_currentGoal - 1];
        }
        else
        {
            start = rainbow[_numStops - 1];
        }
        localStep = _startStep;
        
        for(i = 0; i < strip.numPixels(); i++)
        {
            goal = rainbow[localGoal];
            current = AnimationUtils::GetGradientColor(start, goal, localStep, _numSteps);
            strip.setPixelColor(i, current);
            if(localStep == _numSteps)
            {
                localStep = 0;
                localGoal = (_currentGoal + 1) % _numStops; 
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

    //^^^ swapping numsteps and current step in get gradient color led to spastic behavior
    //Setting local goal to currentGoal + 1 etc  instead of using local goal in inner loop
    //Not resetting start goal in inner loop

}

void Glitch::Trigger()
{
    // nothing to do
}
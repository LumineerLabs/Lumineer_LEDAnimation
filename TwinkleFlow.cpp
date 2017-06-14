#include<Lumineer_LEDAnimation.h>

void TwinkleFlow::Initialize(Adafruit_NeoPixel& strip)
{
    _lastUpdate = millis() - _interval;
    _currentStep = 0;
    if(_numPixels != 0)
    {
        free(_bitmap1);
        free(_bitmap2);
    }
    _numPixels = strip.numPixels();
    _bitmap1 = (uint8_t*) malloc(_numPixels);
    _bitmap2 = (uint8_t*) malloc(_numPixels);
}

TwinkleFlow::~TwinkleFlow()
{
    if(_numPixels != 0)
    {
        free(_bitmap1);
        free(_bitmap2);
    }
}

void TwinkleFlow::Step(Adafruit_NeoPixel& strip)
{
    uint32_t time = millis();

    if (time - _lastUpdate >= _interval)
    {
        _lastUpdate = time;

        Serial.println("Animate");

        // display current state
        for (uint8_t i = 0; i < strip.numPixels(); i++)
        {
            uint8_t byte_num = i / 8;
            uint8_t bit_num = i % 8;

            if (((_bitmap2[byte_num] & (1 << bit_num)) == 0) && ((_bitmap1[byte_num] & (1 << bit_num)) != 0))
            {
                strip.setPixelColor(i, _startColor);
            }
            else
            {
                strip.setPixelColor(i, 0);
            }
        }

        Serial.println("Update");
        Serial.println(_numPixels, HEX);
        uint8_t rand = random(_numOn);
        uint8_t val = 0;
        uint8_t next_val;
        if (_currentStep == 0)
        {
            if (rand == 0)
            {
                val = 0x1;
            }
            // update state
            for (size_t i = 0; i < _numPixels; i++)
            {
                next_val = (_bitmap1[i] & 0x80) >> 7;
                _bitmap1[i] = (_bitmap1[i] << 1) | val;
                val = next_val;
            }
        }

        rand = random(_numOff);
        val = 0;
        if (rand == 0)
        {
            val = 0x80;
        }

        for (size_t i = _numPixels - 1; i < _numPixels; i--)
        {
            next_val = (_bitmap2[i] & 0x1) << 7;
            _bitmap2[i] = (_bitmap2[i] >> 1) | val;
            val = next_val;
        }
        Serial.println("End Update");

        _currentStep = (_currentStep + 1) % _numSteps;

        strip.show();
    }
}

void TwinkleFlow::Trigger()
{
    // nothing to do
}
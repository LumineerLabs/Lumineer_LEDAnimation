#include <Lumineer_LEDAnimation.h>

void AnimationUtils::ColorWipe(Adafruit_NeoPixel& strip, uint32_t color, uint8_t wait)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, color);
        if (wait > 0)
        {
            strip.show();
        }
        delay(wait);
    }
    if (wait == 0)
    {
        strip.show();
    }
}

uint32_t AnimationUtils::GetRandomVibrantColor()
{
    uint8_t randSegment = random(6);
    uint8_t red, green, blue;
    uint8_t rand = random(256);
    switch (randSegment)
    {
    case 0:
        red = 0xFF;
        green = rand;
        break;
    case 1:
        green = 0xFF;
        red = rand;
        break;
    case 2:
        green = 0xFF;
        blue = rand;
        break;
    case 3:
        blue = 0xFF;
        green = rand;
        break;
    case 4:
        blue = 0xFF;
        red = rand;
        break;
    case 5:
        red = 0xFF;
        blue = rand;
        break;
    }
    return Adafruit_NeoPixel::Color(red, green, blue);
}

uint32_t AnimationUtils::GetGradientColor(uint32_t start, uint32_t goal, uint16_t numSteps, uint16_t currentStep)
{
    uint8_t redDelta, goalRed, startRed, redDiff, red;
    uint8_t greenDelta, goalGreen, startGreen, greenDiff, green;
    uint8_t blueDelta, goalBlue, startBlue, blueDiff, blue;

    goalRed = (0x00FF0000 & goal) >> 16;
    goalGreen = (0x0000FF00 & goal) >> 8;
    goalBlue = (0x000000FF & goal);

    startRed = (0x00FF0000 & start) >> 16;
    startGreen = (0x0000FF00 & start) >> 8;
    startBlue = (0x000000FF & start);

    redDelta = abs(goalRed - startRed);
    blueDelta = abs(goalBlue - startBlue);
    greenDelta = abs(goalGreen - startGreen);

    redDiff = (redDelta * currentStep) / numSteps;
    blueDiff = (blueDelta * currentStep) / numSteps;
    greenDiff = (greenDelta * currentStep) / numSteps;

    if (goalRed < startRed)
    {
        red = startRed - redDiff;
    }
    else
    {
        red = startRed + redDiff;
    }

    if (goalGreen < startGreen)
    {
        green = startGreen - greenDiff;
    }
    else
    {
        green = startGreen + greenDiff;
    }

    if (goalBlue < startBlue)
    {
        blue = startBlue - blueDiff;
    }
    else
    {
        blue = startBlue + blueDiff;
    }

    return Adafruit_NeoPixel::Color(red, green, blue);
}

uint32_t AnimationUtils::GetGradientColor(uint32_t start, uint32_t goal, float pct)
{
    uint8_t redDelta, goalRed, startRed, redDiff, red;
    uint8_t greenDelta, goalGreen, startGreen, greenDiff, green;
    uint8_t blueDelta, goalBlue, startBlue, blueDiff, blue;

    goalRed = (0x00FF0000 & goal) >> 16;
    goalGreen = (0x0000FF00 & goal) >> 8;
    goalBlue = (0x000000FF & goal);

    startRed = (0x00FF0000 & start) >> 16;
    startGreen = (0x0000FF00 & start) >> 8;
    startBlue = (0x000000FF & start);

    redDelta = abs(goalRed - startRed);
    blueDelta = abs(goalBlue - startBlue);
    greenDelta = abs(goalGreen - startGreen);

    redDiff = (uint8_t)(redDelta * pct);
    blueDiff = (uint8_t)(blueDelta * pct);
    greenDiff = (uint8_t)(greenDelta * pct);

    if (goalRed < startRed)
    {
        red = startRed - redDiff;
    }
    else
    {
        red = startRed + redDiff;
    }

    if (goalGreen < startGreen)
    {
        green = startGreen - greenDiff;
    }
    else
    {
        green = startGreen + greenDiff;
    }

    if (goalBlue < startBlue)
    {
        blue = startBlue - blueDiff;
    }
    else
    {
        blue = startBlue + blueDiff;
    }

    return Adafruit_NeoPixel::Color(red, green, blue);
}
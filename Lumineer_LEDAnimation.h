#ifndef LUMINEER_LEDANIMATION_H
#define LUMINEER_LEDANIMATION_H

#include<Adafruit_NeoPixel.h>

enum LumineerAnimation
{
    LumineerAnimation_Blank,
    LumineerAnimation_Cylon,
    LumineerAnimation_Glitch,
    LumineerAnimation_Phaser,
    LumineerAnimation_PulseFill,
    LumineerAnimation_RainbowGradient,
    LumineerAnimation_RainbowGradientTheaterChase,
    LumineerAnimation_RainbowTheaterChase,
    LumineerAnimation_RandomFadingPulse,
    LumineerAnimation_RandomTwinkle,
    LumineerAnimation_SolidColor,
    LumineerAnimation_SolidColorFlash,
    LumineerAnimation_SolidColorRainbowFade,
    LumineerAnimation_SolidColorTheaterChase,
    LumineerAnimation_TwinkleFlow,
    LumineerAnimation_TwoColorGradient,
    LumineerAnimation_TwoColorSolidFade,
    LumineerAnimation_VU,
    LumineerAnimation_NumAnimations
};

class IAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
        
        uint16_t _interval;

    protected:
        uint32_t _lastUpdate;
};

class SolidColorAnimation : public IAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);

    public:
        uint32_t _color;
};

class GradientAnimation : public IAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);

        uint16_t _width;
        uint32_t _startColor;
        uint8_t _flowDirection;
        uint8_t _numSteps; // how many steps between stops

    protected:
        uint8_t _currentGoal; // what stop are we going towards
        uint8_t _startStep; // where we are in the sequence;
        uint8_t _currentStep;
};

class TwoColorGradientAnimation : public GradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);

        uint32_t _colors[2];
};

class RainbowGradientAnimation : public GradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);

    protected:
        const uint8_t _numStops = 7;
};

class OnOffAnimation
{
    public:
        uint8_t _numOn;
        uint8_t _numOff;
        uint8_t _chaseDirection;  // 0 : away from the controler, 1: towards the controler

    protected:
        uint8_t _firstLEDState;
        uint8_t _firstTransitionIndex;
};

class AnimationController
{
    public:
        AnimationController(Adafruit_NeoPixel& strip);
        void SetAnimation(LumineerAnimation animation);
        void Next();
        void Previous();
        void Trigger();
        void Step();
        IAnimation* GetCurrentAnimation();
        LumineerAnimation GetCurrentAnimationType();

    private:
        void SetDefaults();

        IAnimation* _animation;
        LumineerAnimation _animationType;
        Adafruit_NeoPixel& _strip;
};

class AnimationUtils
{
    public:
        static uint32_t rainbow7[7];

        // Fill the dots one after the other with a color
        static void ColorWipe(Adafruit_NeoPixel& strip, uint32_t color, uint8_t delay_ms);
        static uint32_t GetRandomVibrantColor();
        static uint32_t GetGradientColor(uint32_t start, uint32_t goal, uint16_t numSteps, uint16_t currentSteps);
        static uint32_t GetGradientColor(uint32_t start, uint32_t goal, float pct);
};

// this is really just a special case of SolidColor (0, 0, 0)
class Blank : public IAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class SolidColor : public SolidColorAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class SolidColorFlash : public SolidColorAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);

    protected:
        uint8_t _currentGoal; // this is also used for the flash effect - On: [color = color, currentGoal = blank] Off: [color = blank, currentGoal = color]
};

class RainbowGradient : public RainbowGradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);

    protected:
        uint8_t _numStops; // what size rainbow to use
};

class SolidColorRainbowFade : public RainbowGradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class SolidColorTheaterChase : public SolidColorAnimation, public OnOffAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
    
    protected:
};

class RainbowGradientTheaterChase : public RainbowGradientAnimation, public OnOffAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class RainbowTheaterChase : public RainbowGradientAnimation, public OnOffAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class TwoColorSolidFade : public TwoColorGradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class TwoColorGradient : public GradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);

    protected: 
        uint8_t _firstLEDState;
        uint8_t _firstTransitionIndex;
        uint8_t _numOn;
        uint8_t _numOff;
        uint8_t _chaseDirection;  // 0 : away from the controler, 1: towards the controler
};

class Cylon : public TwoColorGradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
    private:
};

// cool with small width or large width or full width
class Phaser : public TwoColorGradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class VU : public SolidColorAnimation, public OnOffAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class RandomTwinkle : public SolidColorAnimation, public OnOffAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class PulseFill : public RainbowGradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class RandomFadingPulse : public GradientAnimation, public OnOffAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

class TwinkleFlow : public GradientAnimation, public OnOffAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);

        ~TwinkleFlow();

    private:
        uint8_t* _bitmap1;
        uint8_t* _bitmap2;
        size_t _numPixels = 0;
};

class Glitch : public RainbowGradientAnimation
{
    public:
        virtual void Initialize(Adafruit_NeoPixel& strip);
        virtual void Trigger();
        virtual void Step(Adafruit_NeoPixel& strip);
};

#endif
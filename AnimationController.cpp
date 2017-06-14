#include <Lumineer_LEDAnimation.h>

AnimationController::AnimationController(Adafruit_NeoPixel& strip)
    : _animation(new Blank()),
      _animationType(LumineerAnimation_Blank),
      _strip(strip)
{
    // process initializer list, don't do anything fancy
}

void AnimationController::SetAnimation(LumineerAnimation animationType)
{
    delete _animation;
    _animationType = animationType;

    switch(animationType)
    {
        case LumineerAnimation_Blank:
            _animation = new Blank();
            break;
        case LumineerAnimation_Cylon:
            _animation = new Cylon();
            break;
        case LumineerAnimation_Glitch:
            _animation = new Glitch();
            break;
        case LumineerAnimation_Phaser:
            _animation = new Phaser();
            break;
        case LumineerAnimation_PulseFill:
            _animation = new PulseFill();
            break;
        case LumineerAnimation_RainbowGradient:
            _animation = new RainbowGradient();
            break;
        case LumineerAnimation_RainbowGradientTheaterChase:
            _animation = new RainbowGradientTheaterChase();
            break;
        case LumineerAnimation_RainbowTheaterChase:
            _animation = new RainbowTheaterChase();
            break;
        case LumineerAnimation_RandomFadingPulse:
            _animation = new RandomFadingPulse();
            break;
        case LumineerAnimation_RandomTwinkle:
            _animation = new RandomTwinkle();
            break;
        case LumineerAnimation_SolidColor:
            _animation = new SolidColor();
            break;
        case LumineerAnimation_SolidColorFlash:
            _animation = new SolidColorFlash();
            break;
        case LumineerAnimation_SolidColorRainbowFade:
            _animation = new SolidColorRainbowFade();
            break;
        case LumineerAnimation_SolidColorTheaterChase:
            _animation = new SolidColorTheaterChase();
            break;
        case LumineerAnimation_TwinkleFlow:
            _animation = new TwinkleFlow();
            break;
        case LumineerAnimation_TwoColorGradient:
            _animation = new TwoColorGradient();
            break;
        case LumineerAnimation_TwoColorSolidFade:
            _animation = new TwoColorSolidFade();
            break;
        case LumineerAnimation_VU:
            _animation = new VU();
            break;
        default:
            _animation = new Blank();
            _animationType = LumineerAnimation_Blank;
    }

    SetDefaults();
    _animation->Initialize(_strip);
}

void AnimationController::Next()
{
    SetAnimation((LumineerAnimation)((_animationType + 1) % LumineerAnimation_NumAnimations));
}

void AnimationController::Previous()
{
    if(_animationType == 0)
    {
        SetAnimation((LumineerAnimation)(LumineerAnimation_NumAnimations - 1));
    }
    else
    {
        SetAnimation((LumineerAnimation)(_animationType - 1));
    }
}

void AnimationController::Trigger()
{
    _animation->Trigger();
}

void AnimationController::Step()
{
    _animation->Step(_strip);
}

IAnimation* AnimationController::GetCurrentAnimation()
{
    return _animation;
}

LumineerAnimation AnimationController::GetCurrentAnimationType()
{
    return _animationType;
}

void AnimationController::SetDefaults()
{
    switch(_animationType)
    {
        case LumineerAnimation_Blank:
        case LumineerAnimation_TwoColorGradient:
        case LumineerAnimation_RandomFadingPulse:
            break;
        case LumineerAnimation_SolidColor: 
            ((SolidColor*)_animation)->_color = 0xFF00FF;
            break;
        case LumineerAnimation_SolidColorFlash:
            ((SolidColorFlash*)_animation)->_color = 0xFF00FF;
            ((SolidColorFlash*)_animation)->_interval = 1000;
            break;
        case LumineerAnimation_PulseFill:
            ((PulseFill*)_animation)->_numSteps = 10;//_strip.numPixels();
            ((PulseFill*)_animation)->_interval = 200;
            break;
        case LumineerAnimation_RainbowGradient:
            ((RainbowGradient*)_animation)->_numSteps = 15;
            ((RainbowGradient*)_animation)->_interval = 30;
            break;
        case LumineerAnimation_SolidColorRainbowFade:
            ((RainbowGradient*)_animation)->_numSteps = 128;
            ((RainbowGradient*)_animation)->_interval = 30;
            break;
        case LumineerAnimation_SolidColorTheaterChase:
            ((SolidColorTheaterChase*)_animation)->_color = 0xFF00FF;
            ((SolidColorTheaterChase*)_animation)->_interval = 200;
            ((SolidColorTheaterChase*)_animation)->_numOn = 3;
            ((SolidColorTheaterChase*)_animation)->_numOff = 3;
            break;
        case LumineerAnimation_RainbowGradientTheaterChase:
            ((RainbowGradientTheaterChase*)_animation)->_interval = 200;
            ((RainbowGradientTheaterChase*)_animation)->_numOn = 5;
            ((RainbowGradientTheaterChase*)_animation)->_numOff = 5;
            ((RainbowGradientTheaterChase*)_animation)->_numSteps = 32;
            break;
        case LumineerAnimation_RainbowTheaterChase:
            ((RainbowTheaterChase*)_animation)->_interval = 200;
            ((RainbowTheaterChase*)_animation)->_numOn = 5;
            ((RainbowTheaterChase*)_animation)->_numOff = 5;
            ((RainbowTheaterChase*)_animation)->_numSteps = 32;
            break;
        case LumineerAnimation_TwoColorSolidFade:
            ((TwoColorSolidFade*)_animation)->_colors[0] = 0xFF0000;
            ((TwoColorSolidFade*)_animation)->_colors[1] = 0x0000FF;
            ((TwoColorSolidFade*)_animation)->_interval = 200;
            ((TwoColorSolidFade*)_animation)->_numSteps = 32;
            break;
        case LumineerAnimation_Cylon:
            ((Cylon*)_animation)->_colors[0] = 0xFF0000;
            ((Cylon*)_animation)->_colors[1] = 0;
            ((Cylon*)_animation)->_interval = 200;
            ((Cylon*)_animation)->_width = 5;
            break;
        case LumineerAnimation_Phaser:
            ((Phaser*)_animation)->_colors[0] = 0xFF00FF;
            ((Phaser*)_animation)->_colors[1] = 0;
            ((Phaser*)_animation)->_interval = 100;
            ((Phaser*)_animation)->_width = 3;
            ((Phaser*)_animation)->_flowDirection = 2;
            break;
        case LumineerAnimation_VU:
            ((VU*)_animation)->_color = 0xFF0000;
            break;
        case LumineerAnimation_RandomTwinkle:
            ((RandomTwinkle*)_animation)->_color = 0xFF;
            ((RandomTwinkle*)_animation)->_interval = 200;
            ((RandomTwinkle*)_animation)->_numOn = 1;
            ((RandomTwinkle*)_animation)->_numOff = 5;
            break;
        case LumineerAnimation_TwinkleFlow:
            ((TwinkleFlow*)_animation)->_startColor = 0xFF;
            ((TwinkleFlow*)_animation)->_interval = 200;
            ((TwinkleFlow*)_animation)->_numOn = 5;
            ((TwinkleFlow*)_animation)->_numOff = 5;
            break;
        case LumineerAnimation_Glitch:
            ((Glitch*)_animation)->_numSteps = 32;
            ((Glitch*)_animation)->_interval = 200;
            break;
    }
}
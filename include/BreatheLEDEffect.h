#ifndef BEATHE_LED_EFFECT_H
#define BREATHE_LED_EFFECT_H

#include <Arduino.h>
#include <FastLED.h>
#include <LEDEffect.h>
#include <CDHSV.h>

class BreatheLEDEffect : public LEDEffect {
    public:
        const char* getName() { return "BreatheLEDEffect"; }

        bool setup(const double_t delta);
        void loop(const double_t delta);
        bool destroy(const double_t delta);

        bool canSetupConcurrently() { return false; }
        bool canDestroyConcurrently() { return false; }

        BreatheLEDEffect(CDHSV* leds, const uint16_t numLeds) : LEDEffect(leds, numLeds), _isSetup{false}, _rand{random8()}, _hsv{getNewCHSV(_rand)}, _easingValues{new double[numLeds]}, _direction{true} {};
    
    private:
        bool _isSetup;
    
        uint8_t _rand;
        CDHSV _hsv;
        double_t* _easingValues; // Eases translate linear motion into eased motion, so applying an ease on top of an ease is a bad idea
        bool _direction;

        bool breatheDown(const double_t delta);
        bool breatheUp(const double_t delta);

        CDHSV getNewCHSV(const uint8_t rand);
};

#endif // BREATHE_LED_EFFECT_H
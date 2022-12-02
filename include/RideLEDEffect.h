#ifndef RIDE_LED_EFFECT_H
#define RIDE_LED_EFFECT_H

#include <Arduino.h>
#include <FastLED.h>
#include <LEDEffect.h>
#include <CDHSV.h>

class RideLEDEffect : public LEDEffect {
    public:
        const char* getName() { return "RideLEDEffect"; }

        bool setup(const double_t delta);
        void loop(const double_t delta);
        bool destroy(const double_t delta);

        bool canSetupConcurrently() { return false; }
        bool canDestroyConcurrently() { return false; }

        RideLEDEffect(CDHSV* leds, const uint16_t numLeds) : LEDEffect(leds, numLeds), _isSetup{false}, _hsv{getNewCHSV(random8())}, _easingValues{new double[numLeds]}, _direction{random8() > 127}, _slider{_direction ? 0.0 : 1.0} {};
    
    private:
        bool _isSetup;
    
        CDHSV _hsv;
        double_t* _easingValues; // Eases translate linear motion into eased motion, so applying an ease on top of an ease is a bad idea
        bool _direction;
        double_t _slider;

        bool breatheDown(const double_t delta);

        CDHSV getNewCHSV(const uint8_t rand);
};

#endif // RIDE_LED_EFFECT_H
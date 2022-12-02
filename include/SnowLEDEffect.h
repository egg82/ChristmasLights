#ifndef SNOW_LED_EFFECT_H
#define SNOW_LED_EFFECT_H

#include <Arduino.h>
#include <FastLED.h>
#include <LEDEffect.h>
#include <CDHSV.h>

class SnowLEDEffect : public LEDEffect {
    public:
        const char* getName() { return "SnowLEDEffect"; }

        bool setup(const double_t delta);
        void loop(const double_t delta);
        bool destroy(const double_t delta);

        bool canSetupConcurrently() { return false; }
        bool canDestroyConcurrently() { return false; }

        SnowLEDEffect(CDHSV* leds, const uint16_t numLeds) : LEDEffect(leds, numLeds), _isSetup{false}, _easingValues{new double[numLeds]} {};
    
    private:
        bool _isSetup;
    
        const CDHSV _hsv = CDHSV(0.0, 0.0, 120.0); // White
        double_t* _easingValues; // Eases translate linear motion into eased motion, so applying an ease on top of an ease is a bad idea

        bool breatheDown(const double_t delta);
};

#endif // SNOW_LED_EFFECT_H
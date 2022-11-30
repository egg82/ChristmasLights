#ifndef LED_EFFECT_H
#define LED_EFFECT_H

#include <Arduino.h>
#include <FastLED.h>
#include "CDHSV.h"

class LEDEffect {
    public:
        virtual const char* getName();

        virtual bool setup(const double_t delta);
        virtual void loop(const double_t delta);
        virtual bool destroy(const double_t delta);

        virtual bool canSetupConcurrently();
        virtual bool canDestroyConcurrently();

        LEDEffect(CDHSV* leds, const uint16_t numLeds) : _leds{leds}, _numLeds{numLeds} {};
    
    protected:
        CDHSV* _leds;
        uint16_t _numLeds;
};

#endif // LED_EFFECT_H
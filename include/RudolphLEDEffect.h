#ifndef RUDOLPH_LED_EFFECT_H
#define RUDOLPH_LED_EFFECT_H

#include <Arduino.h>
#include <FastLED.h>
#include <LEDEffect.h>
#include <CDHSV.h>

#define RUDOLPH_PATTERN_SIZE 32

class RudolphLEDEffect : public LEDEffect {
    public:
        const char* getName() { return "RudolphLEDEffect"; }

        bool setup(const double_t delta);
        void loop(const double_t delta);
        bool destroy(const double_t delta);

        bool canSetupConcurrently() { return false; }
        bool canDestroyConcurrently() { return false; }

        RudolphLEDEffect(CDHSV* leds, const uint16_t numLeds) : LEDEffect(leds, numLeds), _direction{random8() > 127}, _slider{_direction ? 0.0 : 1.0} {};
    
    private:
        bool _direction;
        double_t _slider;

        const CDHSV _pattern[RUDOLPH_PATTERN_SIZE] = {
            CDHSV(0.0, 255.0, 140.0), // Red nose
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(32.0, 85.0, 39.0), // Body
            CDHSV(0.0, 255.0, 0.0), // Blank

            CDHSV(0.0, 0.0, 60.0), // Charriot
            CDHSV(0.0, 255.0, 40.0), // Santa
            CDHSV(96.0, 255.0, 40.0), // Gifts
            CDHSV(0.0, 0.0, 60.0), // Charriot
            CDHSV(0.0, 255.0, 0.0) // Blank
        };
};

#endif // RUDOLPH_LED_EFFECT_H
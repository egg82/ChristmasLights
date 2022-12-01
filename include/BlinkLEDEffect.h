#ifndef BLINK_LED_EFFECT_H
#define BLINK_LED_EFFECT_H

#include <Arduino.h>
#include <FastLED.h>
#include <LEDEffect.h>
#include <CDHSV.h>

#define BLINK_PATTERN_SIZE 5
#define BLINK_TIMER_MAX 10.0

class BlinkLEDEffect : public LEDEffect {
    public:
        const char* getName() { return "BlinkLEDEffect"; }

        bool setup(const double_t delta);
        void loop(const double_t delta);
        bool destroy(const double_t delta);

        bool canSetupConcurrently() { return false; }
        bool canDestroyConcurrently() { return false; }

        BlinkLEDEffect(CDHSV* leds, const uint16_t numLeds) : LEDEffect(leds, numLeds), _timer{0.0}, _index{0} {};
    
    private:
        double_t _timer;
        uint8_t _index;

        const CDHSV _pattern[BLINK_PATTERN_SIZE] = {
            CDHSV(253.1895, 225.9555, 180.0), // Red
            CDHSV(99.4755, 255.0, 93.993), // Green
            CDHSV(0.0, 0.0, 120.0), // White
            CDHSV(32.0535, 242.658, 220.0), // Gold
            CDHSV(197.319, 218.5605, 97.9965) // Purple
        };
};

#endif // BLINK_LED_EFFECT_H
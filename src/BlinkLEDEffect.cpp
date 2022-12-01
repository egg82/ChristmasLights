#include "BlinkLEDEffect.h"

#include <Arduino.h>
#include <FastLED.h>
#include <CDHSV.h>

bool BlinkLEDEffect::setup(const double_t delta) {
    for (uint16_t i = _numLeds - 1; i >= 0; i--) {
        if (i >= _numLeds) { // Brute-force method - can't seem to get i = 0 for some reason, so a rollover to 25565 is done and then checked here
            break;
        }
        //Serial.printf("i=%d\n", i);
        //Serial.flush();

        _leds[i] = _pattern[_index];
        _index += 1;
        if (_index >= BLINK_PATTERN_SIZE) {
            _index = 0;
        }
    }
    return true;
}

void BlinkLEDEffect::loop(const double_t delta) {
    _timer += 1.0 * delta;
    if (_timer < BLINK_TIMER_MAX) {
        return;
    }
    _timer = 0.0;

    for (uint16_t i = _numLeds - 1; i > 0; i--) {
        _leds[i] = _leds[i - 1];
    }
    _leds[0] = _pattern[_index];
    _index += 1;
    if (_index >= BLINK_PATTERN_SIZE) {
        _index = 0;
    }
}

bool BlinkLEDEffect::destroy(const double_t delta) {
    for (uint16_t i = 0; i < _numLeds; i++) {
        _leds[i].v = 0.0;
    }
    return true;
}
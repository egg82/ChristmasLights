#include "RudolphLEDEffect.h"

#include <Arduino.h>
#include <FastLED.h>
#include <Easing.h>
#include <CDHSV.h>

bool RudolphLEDEffect::setup(const double_t delta) {
    for (uint16_t i = 0; i < _numLeds; i++) {
        _leds[i].h = 0.0;
        _leds[i].s = 255.0;
        _leds[i].v = 0.0;
    }

    _direction = true;
    _slider = 0.0;

    return true;
}

void RudolphLEDEffect::loop(const double_t delta) {
    int32_t lead = constrain((int32_t) (_slider * (_numLeds + RUDOLPH_PATTERN_SIZE + 1.0)), -RUDOLPH_PATTERN_SIZE, _numLeds + RUDOLPH_PATTERN_SIZE); // The +1 is because we're flooring the value

    if (_direction) {
        for (uint8_t i = 0; i < RUDOLPH_PATTERN_SIZE; i++) {
            if (lead - i >= 0 && lead - i < _numLeds) {
                _leds[lead - i] = _pattern[i];
            }
        }
        for (uint8_t i = 0; i < 5; i++) {
            if (lead - RUDOLPH_PATTERN_SIZE - i >= 0 && lead - RUDOLPH_PATTERN_SIZE - i < _numLeds) {
                _leds[lead - RUDOLPH_PATTERN_SIZE - i] = CDHSV(0.0, 255.0, 0.0); // Blank
            }
        }
        _slider += 0.001 * delta;
    } else {
        for (uint8_t i = 0; i < RUDOLPH_PATTERN_SIZE; i++) {
            if (lead + i >= 0 && lead + i < _numLeds) {
                _leds[lead + i] = _pattern[i];
            }
        }
        for (uint8_t i = 0; i < 5; i++) {
            if (lead + RUDOLPH_PATTERN_SIZE + i >= 0 && lead + RUDOLPH_PATTERN_SIZE + i < _numLeds) {
                _leds[lead + RUDOLPH_PATTERN_SIZE + i] = CDHSV(0.0, 255.0, 0.0); // Blank
            }
        }
        _slider -= 0.001 * delta;
    }

    if (_slider > 1.0) {
        _slider = 1.0;
        _direction = !_direction;
    } else if (_slider < -1.0) {
        _slider = -1.0;
        _direction = !_direction;
    }
}

bool RudolphLEDEffect::destroy(const double_t delta) {
    if (_slider < 1.0 && _slider > -1.0) {
        loop(delta);
        return false;
    }

    for (uint16_t i = 0; i < _numLeds; i++) {
        _leds[i].h = 0.0;
        _leds[i].s = 255.0;
        _leds[i].v = 0.0;
    }
    
    return true;
}
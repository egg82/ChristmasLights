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
    int32_t lead = constrain((int32_t) (_slider * (_numLeds + RUDOLPH_PATTERN_SIZE + 1.0)), -RUDOLPH_PATTERN_SIZE - 1, _numLeds + RUDOLPH_PATTERN_SIZE); // The +1 is because we're flooring the value
    //_leds[lead] = CDHSV(0.0, 255.0, 140.0);

    if (_direction) {
        /*if (lead > 0) {
            _leds[lead - 1] = CDHSV(32.0, 85.0, 39.0);
            if (lead > 1) {
                _leds[lead - 2] = CDHSV(0.0, 255.0, 0.0);
            }
        }*/
        for (uint8_t i = 0; i < RUDOLPH_PATTERN_SIZE; i++) {
            if (lead - i >= 0 && lead - i < _numLeds) {
                _leds[lead - i] = _pattern[i];
            }
        }
        _slider += 0.005 * delta;
    } else {
        /*if (lead < _numLeds - 1) {
            _leds[lead + 1] = CDHSV(32.0, 85.0, 39.0);
            if (lead < _numLeds - 2) {
                _leds[lead + 2] = CDHSV(0.0, 255.0, 0.0);
            }
        }
        _slider -= 0.005 * delta;*/

        /*for (uint8_t i = 0; i < RUDOLPH_PATTERN_SIZE; i++) {
            if (lead + i >= 0 && lead + i < _numLeds) {
                _leds[lead + i] = _pattern[i];
            }
        }
        _slider -= 0.005 * delta;*/

        for (uint16_t i = 0; i < _numLeds; i++) {
            _leds[i].h = 0.0;
            _leds[i].s = 255.0;
            _leds[i].v = 0.0;
        }

        _direction = true;
        _slider = 0.0;
    }

    if (_slider > 1.0) {
        _slider = 1.0;
        _direction = !_direction;
    } else if (_slider < 0.0) {
        _slider = 0.0;
        _direction = !_direction;
    }
}

bool RudolphLEDEffect::destroy(const double_t delta) {
    return true;
}
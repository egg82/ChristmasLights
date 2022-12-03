#include "RideLEDEffect.h"

#include <Arduino.h>
#include <FastLED.h>
#include <Easing.h>
#include <CDHSV.h>

bool RideLEDEffect::setup(const double_t delta) {
    if (!_isSetup) {
        for (uint16_t i = 0; i < _numLeds; i++) {
            _easingValues[i] = _leds[i].v / 255.0;
        }
        _isSetup = true;
    }

    if (breatheDown(delta)) {
        // We're at 0, change the color to the current color
        for (uint16_t i = 0; i < _numLeds; i++) {
            _leds[i].h = _hsv.h;
            _leds[i].s = _hsv.s;
        }
        return true;
    }
    return false;
}

void RideLEDEffect::loop(const double_t delta) {
    int32_t lead = constrain((int32_t) (_slider * (_numLeds + 1.0)), 0, _numLeds - 1); // The +1 is because we're flooring the value
    _leds[lead] = CDHSV(_hsv);
    _easingValues[lead] = 1.0;

    if (_direction) {
        _slider += 0.003 * delta;
    } else {
        _slider -= 0.003 * delta;
    }

    breatheDown(delta);

    if (_slider > 1.0) {
        _slider = 1.0;
        _direction = !_direction;
        _hsv = getNewCHSV(random8());
    } else if (_slider < 0.0) {
        _slider = 0.0;
        _direction = !_direction;
        _hsv = getNewCHSV(random8());
    }
}

bool RideLEDEffect::destroy(const double_t delta) {
    if (breatheDown(delta)) {
        _isSetup = false;
        return true;
    }
    return false;
}

bool RideLEDEffect::breatheDown(const double_t delta) {
    bool retVal = true;
    for (uint16_t i = 0; i < _numLeds; i++) {
        if (_leds[i].v > EPSILON) {
            retVal = false;
            _easingValues[i] = constrain(_easingValues[i] - 0.01 * delta, 0.0, 1.0);
            _leds[i].v = constrain(easeOutQuart(_easingValues[i]) * _hsv.v, 0.0, 255.0);
            // Dont' break, need to set the rest of the LEDs
        }
    }
    //Serial.printf("V: down %.8f %d (%.4f)\n", _leds[0].v, _leds[0].v > EPSILON, EPSILON);
    //Serial.flush();
    return retVal;
}

CDHSV RideLEDEffect::getNewCHSV(const uint8_t rand) {
    if (rand <= 51) {
        return CDHSV(253.1895, 225.9555, 180.0); // Red
    } else if (rand <= 102) {
        return CDHSV(99.4755, 255.0, 93.993); // Green
    } else if (rand <= 153) {
        return CDHSV(0.0, 0.0, 120.0); // White
    } else if (rand <= 204) {
        return CDHSV(32.0535, 242.658, 220.0); // Gold
    } else {
        return CDHSV(197.319, 218.5605, 97.9965); // Purple
    }
}
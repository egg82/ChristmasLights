#include "BreatheLEDEffect.h"

#include <Arduino.h>
#include <FastLED.h>
#include <Easing.h>
#include <CDHSV.h>

bool BreatheLEDEffect::setup(const double_t delta) {
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

void BreatheLEDEffect::loop(const double_t delta) {
    if (_direction) {
        if (breatheUp(delta)) {
            // We're at 255, change direction
            _direction = !_direction;
        }
    } else {
        if (breatheDown(delta)) {
            // We're at 0, change the color to something random and change direction
            _rand = random8();
            _hsv = getNewCHSV(_rand);
            for (uint16_t i = 0; i < _numLeds; i++) {
                _leds[i].h = _hsv.h;
                _leds[i].s = _hsv.s;
            }
            _direction = !_direction;
        }
    }
}

bool BreatheLEDEffect::destroy(const double_t delta) {
    if (breatheDown(delta)) {
        _isSetup = false;
        return true;
    }
    return false;
}

bool BreatheLEDEffect::breatheDown(const double_t delta) {
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

bool BreatheLEDEffect::breatheUp(const double_t delta) {
    bool retVal = true;
    for (uint16_t i = 0; i < _numLeds; i++) {
        if (_leds[i].v < _hsv.v - EPSILON) {
            retVal = false;
            _easingValues[i] = constrain(_easingValues[i] + 0.01 * delta, 0.0, 1.0);
            _leds[i].v = constrain(easeOutQuart(_easingValues[i]) * _hsv.v, 0.0, 255.0);
            // Dont' break, need to set the rest of the LEDs
        }
    }
    //Serial.printf("V: up %.8f %d (%.4f)\n", _leds[0].v, _leds[0].v < _hsv.v - EPSILON, _hsv.v - EPSILON);
    //Serial.flush();
    return retVal;
}

CDHSV BreatheLEDEffect::getNewCHSV(const uint8_t rand) {
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
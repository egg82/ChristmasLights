#include "SnowLEDEffect.h"

#include <Arduino.h>
#include <FastLED.h>
#include <Easing.h>
#include <CDHSV.h>

bool SnowLEDEffect::setup(const double_t delta) {
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

void SnowLEDEffect::loop(const double_t delta) {
    breatheDown(delta);
    if (random8() <= 5) {
        uint8_t leds = random8(1, (uint8_t) (_numLeds / 4));
        for (uint8_t i = 0; i < leds; i++) {
            uint16_t led = random16(0, _numLeds);
            _leds[led] = CDHSV(_hsv.h, _hsv.s, random8((uint8_t) (_hsv.v / 4), (uint8_t) _hsv.v));
            _easingValues[led] = _leds[led].v / _hsv.v;
        }
    }
}

bool SnowLEDEffect::destroy(const double_t delta) {
    if (breatheDown(delta)) {
        _isSetup = false;
        return true;
    }
    return false;
}

bool SnowLEDEffect::breatheDown(const double_t delta) {
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
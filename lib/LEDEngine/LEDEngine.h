#ifndef PRINT_DEBUG
#define PRINT_DEBUG false
#endif

#ifndef PRINT_INFO
#define PRINT_INFO true
#endif

#ifndef PRINT_WARN
#define PRINT_WARN true
#endif

#ifndef PRINT_ERROR
#define PRINT_ERROR true
#endif

#ifndef LED_ENGINE_H
#define LED_ENGINE_H

#include <Arduino.h>
#include "LEDEffect.h"
#include "CDHSV.h"

class LEDEngine {
    public:
        void switchEffect(LEDEffect* effect);
        LEDEffect* getEffect();

        void loop();

        LEDEngine(CRGB* leds, CDHSV* ledsHSV, const uint16_t numLeds, const uint32_t refreshRate) : _leds{leds}, _ledsHSV{ledsHSV}, _numLeds{numLeds}, _currentState{0}, _currentEffect{NULL}, _newState{0}, _newEffect{NULL}, _lastTime{0}, _refreshRate{(float_t) refreshRate} {};
    
    private:
        CRGB* _leds;
        CDHSV* _ledsHSV;
        uint16_t _numLeds;

        uint8_t _currentState;
        LEDEffect* _currentEffect;
        uint8_t _newState;
        LEDEffect* _newEffect;

        uint32_t _lastTime;
        float_t _refreshRate;

        bool loopEffect(LEDEffect* effect, const uint8_t state, const double_t delta);
        void showLEDs();
};

#endif // LED_ENGINE_H
#include "LEDEngine.h"

#include <Arduino.h>
#include "LEDEffect.h"
#include "CDHSV.h"

LEDEffect* LEDEngine::getEffect() {
    if (_newEffect != NULL) {
        return _newEffect;
    }
    return _currentEffect;
}

void LEDEngine::switchEffect(LEDEffect* effect) {
    if (PRINT_INFO) {
        if (effect != NULL) {
            Serial.printf("[LEDEngine] (INFO) switching to new effect %s\n", effect->getName());
            Serial.flush();
        } else {
            Serial.println("[LEDEngine] (INFO) switching to null effect");
            Serial.flush();
        }
    }

    _newEffect = effect;
    _newState = 0;
}

void LEDEngine::loop() {
    if (PRINT_DEBUG) {
        Serial.println("[LEDEngine] (DEBUG) running loop");
        Serial.flush();
    }

    uint32_t current = micros();
    double_t delta = (double_t) (current - _lastTime) / _refreshRate;
    _lastTime = current;

    if (_newEffect != NULL) { // Switched to a new effect
        if (PRINT_DEBUG) {
            Serial.println("[LEDEngine] (DEBUG) _newEffect is set");
            Serial.flush();
        }
        if (_currentEffect == NULL) { // Old effect is done
            if (PRINT_INFO) {
                Serial.println("[LEDEngine] (INFO) _currentEffect is not set, bringing _newEffect to _currentEffect");
                Serial.flush();
            }
            _currentEffect = _newEffect;
            _currentState = _newState;
            _newEffect = NULL;
            _newState = 0;
            // No return here, we want to run the new (now current) effect below
        } else { // Old effect is not done
            if (PRINT_DEBUG) {
                Serial.println("[LEDEngine] (DEBUG) _currentEffect is set, running _currentEffect loop");
                Serial.flush();
            }
            if (_currentState == 1) { // Switch old effect to destroy state if currently looping
                _currentState = 2;
            }
            if (loopEffect(_currentEffect, _currentState, delta)) {
                if (_currentState == 0) {
                    if (PRINT_INFO) {
                        Serial.println("[LEDEngine] (INFO) _currentEffect is finished with setup, switching to destroy");
                        Serial.flush();
                    }
                    _currentState = 2; // Old effect setup is done, immediately switch to destroy
                } else if (_currentState == 2) { // Old effect is done
                    if (PRINT_INFO) {
                        Serial.println("[LEDEngine] (INFO) _currentEffect is shut down, setting _currentEffect to _newEffect");
                        Serial.flush();
                    }
                    if (_currentEffect->canDestroyConcurrently() && _newEffect->canSetupConcurrently() && _newState == 0) { // Loop new effect if applicable
                        if (PRINT_DEBUG) {
                            Serial.println("[LEDEngine] (DEBUG) running _newEffect loop");
                            Serial.flush();
                        }
                        if (loopEffect(_newEffect, _newState, delta)) {
                            _newState = 1; // _newState was 0
                        }
                    }

                    _currentEffect = _newEffect;
                    _currentState = _newState;
                    _newEffect = NULL;
                    _newState = 0;
                    showLEDs();
                    return; // We just set the current effect to the new effect, no need to run the new effect
                }
            }
            if (_currentEffect->canDestroyConcurrently() && _newEffect->canSetupConcurrently() && _currentState == 2 && _newState == 0) { // Loop new effect if applicable
                if (PRINT_DEBUG) {
                    Serial.println("[LEDEngine] (DEBUG) running _newEffect loop");
                    Serial.flush();
                }
                if (loopEffect(_newEffect, _newState, delta)) {
                    _newState = 1; // _newState was 0
                }
            }
            showLEDs();
            return; // We don't want to run the current effect twice
        }
    }

    if (_currentEffect == NULL) {
        if (PRINT_DEBUG) {
            Serial.println("[LEDEngine] (DEBUG) _currentEffect is null, not running loop");
            Serial.flush();
        }
        return;
    }

    if (PRINT_DEBUG) {
        Serial.println("[LEDEngine] (DEBUG) Running _currentEffect loop");
        Serial.flush();
    }
    if (loopEffect(_currentEffect, _currentState, delta)) {
        if (_currentState == 0) {
            if (PRINT_DEBUG) {
                Serial.println("[LEDEngine] (DEBUG) _currentEffect is set up, switching to loop");
                Serial.flush();
            }
            _currentState = 1;
        } else if (_currentState == 2) {
            if (PRINT_DEBUG) {
                Serial.println("[LEDEngine] (DEBUG) _currentEffect is shut down, setting _currentEffect to null");
                Serial.flush();
            }
            _currentEffect = NULL;
            _currentState = 0;
        }
    }

    showLEDs();
}

bool LEDEngine::loopEffect(LEDEffect* effect, const uint8_t state, const double_t delta) {
    switch (state) {
        case 0:
            return effect->setup(delta);
        case 1:
            effect->loop(delta);
            return false;
        case 2:
            return effect->destroy(delta);
        
        default:
            if (PRINT_WARN) {
                Serial.printf("[LEDEngine] (WARN) loopEffect caught invalid state %d\n", state);
                Serial.flush();
            }
            return false;
    }
}

void LEDEngine::showLEDs() {
    if (PRINT_DEBUG) {
        Serial.printf("[LEDEngine] (DEBUG) setting %d LEDs to new values\n", _numLeds);
        Serial.flush();
    }

    for (uint16_t i = 0; i < _numLeds; i++) {
        _leds[i] = _ledsHSV[i].getCRGB();
    }

    if (PRINT_DEBUG) {
        Serial.println("[LEDEngine] (DEBUG) showing new LED values");
        Serial.flush();
    }

    FastLED.show();
}
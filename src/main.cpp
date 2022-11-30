#include <Arduino.h>
#include <FastLED.h>

/*#define PRINT_DEBUG true
#define PRINT_INFO true
#define PRINT_WARN true
#define PRINT_ERROR true*/

#include <LEDEngine.h>
#include <CDHSV.h>

#include "BreatheLEDEffect.h"
#include "RudolphLEDEffect.h"

#define NUM_LEDS 16
#define DATA_PIN 3
#define CLOCK_PIN 13
#define RANDOM_PIN 23

#define REFRESH_RATE 16000 // In microseconds

CRGB leds[NUM_LEDS];
CDHSV ledsHSV[NUM_LEDS];
uint8_t currentEffect;

#define NUM_EFFECTS 2
LEDEffect *effects[NUM_EFFECTS] = {
  new BreatheLEDEffect(ledsHSV, NUM_LEDS),
  new RudolphLEDEffect(ledsHSV, NUM_LEDS)
};

LEDEngine* engine;

void setup() {
  pinMode(RANDOM_PIN, INPUT);
  randomSeed(analogRead(RANDOM_PIN));

  Serial.begin(9600);

  randomSeed(random16() + analogRead(RANDOM_PIN));

  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(7500);

  randomSeed(random16() + analogRead(RANDOM_PIN));

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB();
    ledsHSV[i] = CDHSV();
  }

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);  // BGR ordering is typical
  FastLED.setBrightness(64);

  FastLED.show();

  engine = new LEDEngine(leds, ledsHSV, NUM_LEDS, REFRESH_RATE);

  // Special case on init, don't use the random effect function
  currentEffect = random8(NUM_EFFECTS);
  engine->switchEffect(effects[currentEffect]);
}

void switchEffect() {
  uint8_t effect = random8(NUM_EFFECTS);
  if (PRINT_DEBUG) {
    Serial.printf("[Main] (DEBUG) Attempting to randomly change effect to %s\n", effects[effect]->getName());
    Serial.flush();
  }
  if (effect == currentEffect) {
    return; // Let the effect go a little longer
  }

  if (PRINT_INFO) {
    Serial.printf("[Main] (INFO) Randomly changing effect to %s\n", effects[effect]->getName());
    Serial.flush();
  }

  currentEffect = effect;
  engine->switchEffect(effects[effect]);
}

void loop() {
  uint32_t start = micros();
  engine->loop();
  if (random8() == 1) {
    if (PRINT_DEBUG) {
      Serial.printf("[Main] (DEBUG) Random seed: %d\n", analogRead(RANDOM_PIN));
      Serial.flush();
    }
    randomSeed(random16() + random16() + random16() + random16() + analogRead(RANDOM_PIN));
  }
  if (random8() == 3) {
    switchEffect();
  }
  int32_t delayms = REFRESH_RATE - (micros() - start);
  if (delayms > 0) {
    //Serial.printf("Delaying for %d micros\n", delayms);
    //Serial.flush();
    delayMicroseconds(delayms);
  }
}
#ifndef EPSILON
#define EPSILON 0.001
#endif

#ifndef EASING_H
#define EASING_H

#include <Arduino.h>

// https://easings.net/

static double_t easeInSine(const double_t x) {
  return 1.0 - cos((x * PI) / 2.0);
}

static double_t easeOutSine(const double_t x) {
  return sin((x * PI) / 2.0);
}

static double_t easeInOutSine(const double_t x) {
    return -(cos(PI * x) - 1.0) / 2.0;
}

static double_t easeInCubic(const double_t x) {
    return x * x * x;
}

static double_t easeOutCubic(const double_t x) {
    return 1.0 - pow(1.0F - x, 3.0);
}

static double_t easeInOutCubic(const double_t x) {
    return x < 0.5 ? 4.0 * x * x * x : 1.0 - pow(-2.0 * x + 2.0, 3.0) / 2.0;
}

static double_t easeInQuint(const double_t x) {
    return x * x * x * x * x;
}

static double_t easeOutQuint(const double_t x) {
    return 1.0 - pow(1.0 - x, 5.0);
}

static double_t easeInOutQuint(const double_t x) {
    return x < 0.5 ? 16.0 * x * x * x * x * x : 1.0 - pow(-2.0 * x + 2.0, 5.0) / 2.0;
}

static double_t easeInCirc(const double_t x) {
    return 1.0 - sqrt(1.0 - pow(x, 2.0));
}

static double_t easeOutCirc(const double_t x) {
    return sqrt(1.0 - pow(x - 1.0, 2.0));
}

static double_t easeInOutCirc(const double_t x) {
    return x < 0.5
        ? (1.0 - sqrt(1.0 - pow(2.0 * x, 2.0))) / 2.0
        : (sqrt(1.0 - pow(-2.0 * x + 2.0, 2.0)) + 1.0) / 2.0;
}

static double_t easeInElastic(const double_t x) {
    const double_t c4 = (2.0 * PI) / 3.0;

    return x == 0.0
        ? 0.0
        : x == 1.0
        ? 1.0
        : -pow(2.0, 10.0 * x - 10.0) * sin((x * 10.0 - 10.75) * c4);
}

static double_t easeOutElastic(const double_t x) {
    const double_t c4 = (2.0 * PI) / 3.0;

    return x == 0.0
        ? 0.0
        : x == 1.0
        ? 1.0
        : pow(2.0, -10.0 * x) * sin((x * 10.0 - 0.75) * c4) + 1.0;
}

static double_t easeInOutElastic(const double_t x) {
    const double_t c5 = (2.0 * PI) / 4.5;

    return x == 0.0
        ? 0.0
        : x == 1.0
        ? 1.0
        : x < 0.5
        ? -(pow(2.0, 20.0 * x - 10.0) * sin((20.0 * x - 11.125) * c5)) / 2.0
        : (pow(2.0, -20.0 * x + 10.0) * sin((20.0 * x - 11.125) * c5)) / 2.0 + 1.0;
}

static double_t easeInQuad(const double_t x) {
    return x * x;
}

static double_t easeOutQuad(const double_t x) {
    return 1.0 - (1.0 - x) * (1.0 - x);
}

static double_t easeInOutQuad(const double_t x) {
    return x < 0.5 ? 2.0 * x * x : 1.0 - pow(-2.0 * x + 2.0, 2.0) / 2.0;
}

static double_t easeInQuart(const double_t x) {
    return x * x * x * x;
}

static double_t easeOutQuart(const double_t x) {
    return 1.0 - pow(1.0 - x, 4.0);
}

static double_t easeInOutQuart(const double_t x) {
    return x < 0.5 ? 8.0 * x * x * x * x : 1.0 - pow(-2.0 * x + 2.0, 4.0) / 2.0;
}

static double_t easeInExpo(const double_t x) {
    return x == 0.0 ? 0.0 : pow(2.0, 10.0 * x - 10.0);
}

static double_t easeOutExpo(const double_t x) {
    return x == 1.0 ? 1.0 : 1.0 - pow(2.0, -10.0 * x);
}

static double_t easeInOutExpo(const double_t x) {
    return x == 0.0
        ? 0.0
        : x == 1.0
        ? 1.0
        : x < 0.5 ? pow(2.0, 20.0 * x - 10.0) / 2.0
        : (2.0 - pow(2.0, -20.0 * x + 10.0)) / 2.0;
}

static double_t easeInBack(const double_t x) {
    const double_t c1 = 1.70158;
    const double_t c3 = c1 + 1.0;

    return c3 * x * x * x - c1 * x * x;
}

static double_t easeOutBack(const double_t x) {
    const double_t c1 = 1.70158;
    const double_t c3 = c1 + 1.0;

    return 1.0 + c3 * pow(x - 1.0, 3.0) + c1 * pow(x - 1.0, 2.0);
}

static double_t easeInOutBack(const double_t x) {
    const double_t c1 = 1.70158;
    const double_t c2 = c1 * 1.525;

    return x < 0.5
        ? (pow(2.0 * x, 2.0) * ((c2 + 1.0) * 2.0 * x - c2)) / 2.0
        : (pow(2.0 * x - 2.0, 2.0) * ((c2 + 1.0) * (x * 2.0 - 2.0) + c2) + 2.0) / 2.0;
}

static double_t easeOutBounce(const double_t x) {
    double_t x1 = x;
    const double_t n1 = 7.5625;
    const double_t d1 = 2.75;

    if (x1 < 1.0 / d1) {
        return n1 * x1 * x1;
    } else if (x1 < 2.0 / d1) {
        return n1 * (x1 -= 1.5 / d1) * x1 + 0.75;
    } else if (x1 < 2.5 / d1) {
        return n1 * (x1 -= 2.25 / d1) * x1 + 0.9375;
    } else {
        return n1 * (x1 -= 2.625 / d1) * x1 + 0.984375;
    }
}

static double_t easeInBounce(const double_t x) {
    return 1.0 - easeOutBounce(1.0 - x);
}

static double_t easeInOutBounce(const double_t x) {
    return x < 0.5
        ? (1.0 - easeOutBounce(1.0 - 2.0 * x)) / 2.0
        : (1.0 + easeOutBounce(2.0 * x - 1.0)) / 2.0;
}

#endif
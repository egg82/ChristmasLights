#ifndef CDHSV_H
#define CDHSV_H

#include <Arduino.h>
#include <FastLED.h>

struct CDHSV {
    union {
		struct {
		    union {
		        double_t hue;
		        double_t h; };
		    union {
		        double_t saturation;
		        double_t sat;
		        double_t s; };
		    union {
		        double_t value;
		        double_t val;
		        double_t v; };
		};
		double_t raw[3];
	};

    /// Array access operator to index into the chsv object
	inline double_t& operator[] (uint8_t x) __attribute__((always_inline))
    {
        return raw[x];
    }

    /// Array access operator to index into the chsv object
    inline const double_t& operator[] (uint8_t x) const __attribute__((always_inline))
    {
        return raw[x];
    }

    /// default values are UNITIALIZED
    inline CDHSV() __attribute__((always_inline)) = default;

    /// allow construction from H, S, V
    inline CDHSV( double_t ih, double_t is, double_t iv) __attribute__((always_inline))
        : h(constrain(ih, 0.0, 255.0)), s(constrain(is, 0.0, 255.0)), v(constrain(iv, 0.0, 255.0))
    {
    }

    /// allow copy construction
    inline CDHSV(const CDHSV& rhs) __attribute__((always_inline)) = default;

    inline CDHSV& operator= (const CDHSV& rhs) __attribute__((always_inline)) = default;

    inline CDHSV& setHSV(double_t ih, double_t is, double_t iv) __attribute__((always_inline))
    {
        h = constrain(ih, 0.0, 255.0);
        s = constrain(is, 0.0, 255.0);
        v = constrain(iv, 0.0, 255.0);
        return *this;
    }

    inline CHSV getCHSV() __attribute__((always_inline)) {
        return CHSV((uint8_t) h, (uint8_t) s, (uint8_t) v);
    }

    inline CRGB getCRGB() __attribute__((always_inline)) {
        return CRGB().setHSV((uint8_t) h, (uint8_t) s, (uint8_t) v);
    }
};

#endif
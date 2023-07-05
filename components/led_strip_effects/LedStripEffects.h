#ifndef __LEDSTRIPEFFECTS_H__
#define __LEDSTRIPEFFECTS_H__

#include "env.h"
#include "bits_color.h"
#include <stdbool.h>

#ifdef ESP32_IDF
    #define LEDStripEffects_tick_t   int64_t
#else
#ifdef ESP32_ARDUINO
    #define LEDStripEffects_tick_t   unsigned long
#else
    #define LEDStripEffects_tick_t   uint32_t
#endif
#endif

typedef enum {
    LEDStripEffects_state_STOP,
    LEDStripEffects_state_RUNNING
} LEDStripEffects_state_t;

typedef LEDStripEffects_state_t (*LEDStripEffects_exec_t)(void *effect, void (*setColorAt)(uint16_t index, Color_RGB_t color));

typedef struct {
    LEDStripEffects_exec_t exec;
    LEDStripEffects_state_t state;
    uint32_t indexStep;
    struct {
        uint32_t bot;
        uint32_t top;
    } limit;
} LEDStripEffects_base_t;

LEDStripEffects_state_t LEDStripEffects_run(void *effect, void (*setColorAt)(uint16_t index, Color_RGB_t color));

Color_RGB_t LEDStripEffect_getColorGradient(uint32_t colorAt, uint32_t resolution, Color_RGB_t *colorStrip, uint8_t colorCount);

#endif
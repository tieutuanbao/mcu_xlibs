#ifndef __LEDSINGLEEFFECTS_FADEWIPE_H__
#define __LEDSINGLEEFFECTS_FADEWIPE_H__

#include <stdint.h>
#include <stdbool.h>

#include "LedSingleEffects.h"

typedef struct {
    LEDSingleEffects_exec_t exec;
    struct {
        uint32_t count;
        uint32_t now;
    } led;
    LEDSingleEffect_tick_t startTick;
    uint32_t runInterval;
    uint8_t beginBrightness;
    uint8_t endBrightness;
    bool dirWipe;
} LedSingleEffects_fadeWipe_t;

LEDSingleEffects_state_t LEDSingleEffects_fadeWipe_run(LedSingleEffects_fadeWipe_t *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick);

void LEDSingleEffects_fadeWipe_init(
        LedSingleEffects_fadeWipe_t *effect,
        uint32_t LEDCount, uint8_t beginBrightness, uint8_t endBrightness, bool dirWipe,
        LEDSingleEffect_tick_t runInterval,
        LEDSingleEffect_tick_t nowTick);

#endif
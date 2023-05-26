#ifndef __LEDSINGLEEFFECTS_FADE_H__
#define __LEDSINGLEEFFECTS_FADE_H__

#include <stdint.h>
#include "LedSingleEffects.h"

typedef struct {
    LEDSingleEffects_exec_t exec;
    struct {
        uint32_t count;
    } led;
    LEDSingleEffect_tick_t startTick;
    uint32_t runInterval;
    void (*setBrightnessLED_drv)(uint32_t indexLED, uint8_t brightness);
    uint8_t beginBrightness;
    uint8_t endBrightness;
} LedSingleEffects_fade_t;

LEDSingleEffects_state_t LEDSingleEffects_fade_run(LedSingleEffects_fade_t *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick);
void LEDSingleEffects_fade_init(
        LedSingleEffects_fade_t *effect,
        uint32_t LEDCount, uint8_t beginBrightness, uint8_t endBrightness,
        LEDSingleEffect_tick_t runInterval,
        LEDSingleEffect_tick_t nowTick);

#endif
#ifndef __LEDSINGLEEFFECTS_METEORTOMID_H__
#define __LEDSINGLEEFFECTS_METEORTOMID_H__

#include <stdint.h>
#include <stdbool.h>

#include "LedSingleEffects.h"
#include "LEDSingleEffects_meteor.h"

typedef struct {
    LEDSingleEffects_exec_t exec;
    struct {
        uint32_t count;
        int32_t now;
    } led;
    LEDSingleEffect_tick_t startTick;
    uint32_t runInterval;
    uint8_t beginBrightness;
    uint8_t endBrightness;
    uint32_t meteorLength;
} LedSingleEffects_meteorToMid_t;

void LEDSingleEffects_meteorToMid_init(
        LedSingleEffects_meteorToMid_t *effect,
        uint32_t LEDCount, uint32_t meteorLength, uint8_t beginBrightness, uint8_t endBrightness,
        LEDSingleEffect_tick_t runInterval,
        LEDSingleEffect_tick_t nowTick);

#endif
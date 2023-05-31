#ifndef __LEDSINGLEEFFECTS_H__
#define __LEDSINGLEEFFECTS_H__

#include <stdio.h>
#include <stdint.h>
#include "env.h"

#ifdef ESP32
    #define LEDSingleEffect_tick_t   int64_t
#else
    #define LEDSingleEffect_tick_t   uint32_t
#endif

typedef enum {
    LEDSingle_effectState_RUNNING,
    LEDSingle_effectState_STOP
} LEDSingleEffects_state_t;

typedef void (*LEDSingleEffects_setBrightnessLED_t)(uint32_t indexLED, uint8_t brightness);
typedef LEDSingleEffects_state_t (*LEDSingleEffects_exec_t)(void *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick);

LEDSingleEffects_state_t LEDSingleEffects_run(void *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick);

uint8_t LEDSingleEffects_getFade(int32_t step, int32_t minStep, int32_t maxStep, int16_t startBrightness, int16_t stopBrightness);
void LEDSingleEffects_meteorDraw(int32_t offset, uint16_t length, uint8_t startBrn, uint8_t stopBrn, uint32_t offsetBuf, uint32_t ledCount, LEDSingleEffects_setBrightnessLED_t drv);

#endif

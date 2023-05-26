#ifndef __LEDSINGLEEFFECTS_H__
#define __LEDSINGLEEFFECTS_H__

#include <stdint.h>

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

#endif

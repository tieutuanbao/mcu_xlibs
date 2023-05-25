#include "LEDSingleEffects.h"

typedef struct {
    LEDSingleEffects_exec_t exec;
} LEDSingleEffects_t;

LEDSingleEffects_state_t LEDSingleEffects_run(void *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick) {
    return ((LEDSingleEffects_t *)effect)->exec(effect, drv, nowTick);
}
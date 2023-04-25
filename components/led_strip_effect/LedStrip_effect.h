#ifndef __LED_STRIP_EFFECT_H__
#define __LED_STRIP_EFFECT_H__

#include "env.h"
#include "color.h"
#include "LedStrip_color.h"
#include <stdbool.h>

#ifdef ESP32
    #define LedStripEffect_tick_t   int64_t
#else
    #define LedStripEffect_tick_t   uint32_t
#endif

typedef enum {
    LEDStrip_effectState_running,
    LEDStrip_effectState_stop
} LEDStripEffect_State_t;

typedef LEDStripEffect_State_t (*LEDStripEffect_exec_t)(void *eff, void (*pixelAt_set)(uint16_t index, Color_RGB_t color), LedStripEffect_tick_t currentTick);

typedef struct {
    void **effects;
    LEDStripEffect_exec_t exec;
    LedStripEffect_tick_t lastTick; // Tick bắt đầu
    uint16_t runInterval; // Tổng thời gian chạy của hiệu ứng
} LEDStripEffect_t;

typedef struct {
    void **effects;
    void (*pixelAt_set)(uint16_t index, Color_RGB_t color);
} LEDStripEffect_Drv_t;

void LEDStripEffect_addEffect(LEDStripEffect_t *parrent, LEDStripEffect_t *children);
bool LEDStripEffect_removeEffect(LEDStripEffect_t *eff, void *effect);
LEDStripEffect_State_t LEDStripEffect_run(LEDStripEffect_Drv_t *eff, LedStripEffect_tick_t currentTick);

#endif
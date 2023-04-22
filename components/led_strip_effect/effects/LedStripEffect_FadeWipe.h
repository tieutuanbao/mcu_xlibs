#ifndef __LEDSTRIPEFFECT_FADEWIPE_H__
#define __LEDSTRIPEFFECT_FADEWIPE_H__

#include "LedStrip_effect.h"
#include "LedStrip_color.h"
#include "color.h"

typedef struct {
    LEDStripEffect_t base;
    struct {
        Color_RGB_t *at;
        uint16_t count;
    } led;
    struct {
        Color_RGB_t *at;
        uint8_t count;
    } startColor;
    struct {
        Color_RGB_t *at;
        uint8_t count;
    } stopColor;
    int16_t indexLed;
    bool dir;
} LEDStripEffect_fadeWipe_t;

LEDStripEffect_fadeWipe_t *LEDStripEffect_fadeWipe_init(LEDStripEffect_fadeWipe_t *eff, LedStripEffect_tick_t currentTick, uint32_t runInterval, Color_RGB_t *ledBuffer, uint16_t ledCount,
                                                            Color_RGB_t *startColor, uint8_t startColorCount, Color_RGB_t *stopColor, uint8_t stopColorCount, bool dir);

#endif
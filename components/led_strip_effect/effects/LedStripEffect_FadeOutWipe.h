#ifndef __LEDSTRIPEFFECT_FADEOUTWIPE_H__
#define __LEDSTRIPEFFECT_FADEOUTWIPE_H__

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
    } stripColor;
    int16_t indexLed;
    bool dir;
} LEDStripEffect_fadeOutWipe_t;

LEDStripEffect_fadeOutWipe_t *LEDStripEffect_fadeOutWipe_init(LEDStripEffect_fadeOutWipe_t *eff, LedStripEffect_tick_t currentTick, uint32_t runInterval, Color_RGB_t *ledBuffer, uint16_t ledCount, Color_RGB_t *colorBuffer, uint8_t colorCountC, bool dir);

#endif
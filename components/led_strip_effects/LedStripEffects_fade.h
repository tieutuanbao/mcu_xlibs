#ifndef __LEDSTRIPEFFECTS_FADE_H__
#define __LEDSTRIPEFFECTS_FADE_H__

#include "LedStripEffects.h"
#include "bits_color.h"

typedef struct {
    LEDStripEffects_base_t base;
    struct {
        struct {
            Color_RGB_t *color;
            uint8_t length;
        } start;
        struct {
            Color_RGB_t *color;
            uint8_t length;
        } stop;
    } stripColor;
    /* private */
    uint32_t jumpBrightness; // Bước nhảy thay đổi màu sắc trong stripColor
    uint32_t limitStep;
} LEDStripEffects_fade_t;

LEDStripEffects_fade_t *LEDStripEffects_fade_init(
        LEDStripEffects_fade_t *eff,
        uint32_t limitStep,
        uint32_t limitBot, uint32_t limitTop,
        Color_RGB_t *startColor, uint8_t startColorLen,
        Color_RGB_t *stopColor, uint8_t stopColorLen
    );

#endif
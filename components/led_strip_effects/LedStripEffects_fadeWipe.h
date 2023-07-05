#ifndef __LEDSTRIPEFFECTS_FADEWIPE_H__
#define __LEDSTRIPEFFECTS_FADEWIPE_H__

#include "LedStripEffects.h"
#include "bits_color.h"

typedef struct {
    LEDStripEffects_base_t base;
    uint32_t stepPerLed;
    int32_t indexLed;
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
    bool dir;
} LEDStripEffects_fadeWipe_t;

LEDStripEffects_fadeWipe_t *LEDStripEffects_fadeWipe_init(
            LEDStripEffects_fadeWipe_t *eff,
            uint32_t stepPerLed,
            uint32_t limitBot, uint32_t limitTop,
            Color_RGB_t *startColor, uint8_t startColorLength,
            Color_RGB_t *stopColor, uint8_t stopColorLength,
            bool dir);

#endif
#ifndef __LEDSTRIP_COLOR_H__
#define __LEDSTRIP_COLOR_H__

#include "color.h"

Color_RGB_t LEDStripEffect_getColorGradient(uint32_t colorAt, uint32_t resolution, Color_RGB_t *colorStrip, uint8_t colorCount);

#endif
#ifndef __METEOR_H
#define __METEOR_H

#include "strip_led_misc.h"

void ICACHE_FLASH_ATTR meteor_draw(rgb_color_t *color_buf, uint16_t color_buf_len, int32_t offset_pos, strip_color_t *colors, uint8_t colors_size);

#endif
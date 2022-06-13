#ifndef __STRIP_LED_MISC_H
#define __STRIP_LED_MISC_H

#include "common_macros.h"
#include "color.h"

typedef struct {
    rgb_color_t value;  // Con trỏ đến màu sắc hiển thị trong hiệu ứng
    uint8_t len;        // Độ dài màu sắc hiển thị trong hiệu ứng
} strip_color_t;

#endif
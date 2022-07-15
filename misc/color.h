#ifndef __COLOR_H
#define __COLOR_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

#endif
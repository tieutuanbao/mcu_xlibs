#ifndef __COLOR_H
#define __COLOR_H

#include <stdint.h>


typedef struct __attribute__((packed)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

typedef enum {
	COLOR_BLACK,
	COLOR_RED,
	COLOR_ORANGE,
	COLOR_YELLOW,
	COLOR_CHART_GREEN,
	COLOR_GREEN,
	COLOR_SPRING_GREEN,
	COLOR_CYAN,
	COLOR_AZURE,
	COLOR_BLUE,
	COLOR_VIOLET,
	COLOR_MAGENTA,
	COLOR_ROSE,
	COLOR_WHITE,
    COLOR_IDX_MAX
} rgb_color_sample_t;

extern const rgb_color_t sample_color[];

#endif
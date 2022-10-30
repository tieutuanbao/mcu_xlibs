#ifndef __COLOR_H
#define __COLOR_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} Color_RGB_t;

typedef struct __attribute__((packed)) {
    Color_RGB_t RGB;
    uint8_t A;
} Color_ARGB_t;

#define COLOR_BLACK	            SampleColor[0]
#define COLOR_RED               SampleColor[1]
#define COLOR_ORANGE            SampleColor[2]
#define COLOR_YELLOW            SampleColor[3]
#define COLOR_CHART_GREEN       SampleColor[4]
#define COLOR_GREEN             SampleColor[5]
#define COLOR_SPRING_GREEN      SampleColor[6]
#define COLOR_CYAN              SampleColor[7]
#define COLOR_AZURE             SampleColor[8]
#define COLOR_BLUE              SampleColor[9]
#define COLOR_VIOLET            SampleColor[10]
#define COLOR_MAGENTA           SampleColor[11]
#define COLOR_ROSE              SampleColor[12]
#define COLOR_WHITE             SampleColor[13]

extern const Color_RGB_t SampleColor[];

#endif

#ifndef __COLOR_H
#define __COLOR_H

#include <stdint.h>

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
#define COLOR_BY_ID(n)          SampleColor[n]

#pragma pack(1)
typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} Color_RGB_t;

#pragma pack(1)
typedef struct {
    int16_t R;
    int16_t G;
    int16_t B;
} Color_RGB_Signed_t;

#pragma pack(1)
typedef struct {
    Color_RGB_t RGB;
    uint8_t A;
} Color_ARGB_t;

typedef enum {
    COLOR_BLACK_ID,
    COLOR_RED_ID,
    COLOR_ORANGE_ID,
    COLOR_YELLOW_ID,
    COLOR_CHART_GREEN_ID,
    COLOR_GREEN_ID,
    COLOR_SPRING_GREEN_ID,
    COLOR_CYAN_ID,
    COLOR_AZURE_ID,
    COLOR_BLUE_ID,
    COLOR_VIOLET_ID,
    COLOR_MAGENTA_ID,
    COLOR_ROSE_ID,
    COLOR_WHITE_ID,
    COLOR_MAX_ID
} SampleColorID_t;

extern const Color_RGB_t SampleColor[];

Color_RGB_t ColorRGB_fromHexCodeString(char *hexString);

#endif

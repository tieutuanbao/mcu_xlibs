#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <stdint.h>
#include "color.h"

typedef struct {
    int32_t X;
    int32_t Y;
} Point_t;

typedef struct {
    uint16_t Width;
    uint16_t Height;
} Size_t;

typedef struct {
    Point_t Start;
    Point_t Stop;
} Area_t;

typedef struct {
    void *Buf;
    Size_t Size;
} Graphics_t;


#endif

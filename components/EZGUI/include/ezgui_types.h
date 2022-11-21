#ifndef __EZGUI_TYPES_H__
#define __EZGUI_TYPES_H__

#include <stdint.h>
#include "color.h"

#define EZGUI_DEFAULT_FONT  &Arial

typedef struct {
    int32_t X;
    int32_t Y;
} Point_t;

typedef Point_t Position_t;

typedef struct {
    uint16_t Width;
    uint16_t Height;
} Size_t;

typedef struct {
    Point_t Start;
    Point_t Stop;
} Area_t;

typedef struct {
    void *Buffer;
    Size_t Size;
} EZGUI_Graphics_t;

typedef enum {
    EZGUI_PIXEL_TYPE_MONOCHOME,
    EZGUI_PIXEL_TYPE_RGB
} EZGUI_PixelType_t;

typedef void EZGUI_OBJECTS_T;
typedef void (*DrawPoint_Driver_t)(void *Buffer, Size_t BufferSize, Point_t Point, void *Color);
typedef void (*FrameBuffer_Driver_t)(void *Buffer, Size_t BufferSize, Area_t Area);

#endif

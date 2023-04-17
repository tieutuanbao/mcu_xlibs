#ifndef __EZGUI_H__
#define __EZGUI_H__

#include <stdint.h>
#include "color.h"
#include "ezgui_types.h"
#include "ezgui_obj.h"
#include "ezgui_draw.h"

typedef struct {
    EZGUI_Graphics_t Graph;
    DrawPoint_Driver_t DrawPoint_Driver;
    FrameBuffer_Driver_t FrameBuffer_Driver;
    Size_t Resolution;
    Position_t Offset;
} EZGUI_Monitor_t;

typedef struct {
    EZGUI_OBJ
    struct {
        EZGUI_Monitor_t *List;
        uint16_t Count;
    } Monitor;
} EZGUI_t;

EZGUI_t *new_EZGUI(void);
void EZGUI_Draw(EZGUI_t *GUI);
EZGUI_Monitor_t *new_EZGUI_Monitor(EZGUI_t *EZGUI);
void EZGUI_Monitor_setPixelType(EZGUI_Monitor_t *Monitor, EZGUI_PixelType_t PixelType);

#endif

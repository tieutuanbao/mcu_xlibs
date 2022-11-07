#ifndef __EZGUI_OBJ_H__
#define __EZGUI_OBJ_H__

#include <stdint.h>
#include <stdbool.h>
#include "color.h"
#include "graphic.h"
#include "ezgui_draw.h"

typedef enum {
    EZGUI_OBJ_STATE_NULL        = 0x0000,
    EZGUI_OBJ_STATE_CHECKED     = 0x0001,
    EZGUI_OBJ_STATE_FOCUSED     = 0x0002,
    EZGUI_OBJ_STATE_EDITED      = 0x0004,
    EZGUI_OBJ_STATE_HOVERED     = 0x0008,
    EZGUI_OBJ_STATE_PRESSED     = 0x0010,
    EZGUI_OBJ_STATE_SCROLLED    = 0x0020,
    EZGUI_OBJ_STATE_DISABLED    = 0x0040
} EZGUI_Objects_States_t;

typedef enum {
    EZGUI_OBJ_EVENT_NULL        = 0x0000,
    EZGUI_OBJ_EVENT_PRESS,
    EZGUI_OBJ_EVENT_RELEASE
} EZGUI_Objects_Events_t;

struct EZGUI_Objects;
typedef void (*Draw_t)(DrawPoint_t DrawPoint_Drv, struct EZGUI_Objects *ThisObject, Graphics_t *Graphic, Point_t Offset);
typedef struct EZGUI_Objects {
    uint32_t InstanceSize;
    Draw_t Draw;
    uint8_t (*ObjectEvent)(void *Sender, void *Args);
    EZGUI_Objects_States_t State;
    Point_t Point;
    Size_t Size;
    struct EZGUI_Objects **Children;
} EZGUI_Objects_t;

void EZGUI_Object_Add(EZGUI_Objects_t *parrent, EZGUI_Objects_t *children);
EZGUI_Objects_t **EZGUI_Object_HasChildren(EZGUI_Objects_t *Parrent);
EZGUI_Objects_t *EZGUI_Object_Index(EZGUI_Objects_t *Parrent, uint8_t Index);

#endif

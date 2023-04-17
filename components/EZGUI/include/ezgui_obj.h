#ifndef __EZGUI_OBJ_H__
#define __EZGUI_OBJ_H__

#include <stdint.h>
#include <stdbool.h>
#include "ezgui_types.h"
#include "color.h"

#define EZGUI_OBJ \
        struct EZGUI_Objects **Children; \
        EZGUI_ObjectDraw_t Draw; \
        Position_t Position; \
        Size_t Size; \
        uint8_t InstanceSize; \
        EZGUI_Objects_States_t State; \
        uint8_t (*ObjectEvent)(void *Sender, void *Args); \
        bool Visible; \

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

typedef void (*EZGUI_ObjectDraw_t)(void *ObjectDraw, EZGUI_Graphics_t *Graph, Position_t Offset, DrawPoint_Driver_t DrawPoint_Driver);
typedef struct EZGUI_Objects {
    EZGUI_OBJ
} EZGUI_Objects_t;

void EZGUI_Object_Add(EZGUI_Objects_t *parrent, EZGUI_Objects_t *children);
EZGUI_Objects_t **EZGUI_Object_HasChildren(EZGUI_Objects_t *Parrent);
EZGUI_Objects_t *EZGUI_Object_Index(EZGUI_Objects_t *Parrent, uint8_t Index);

#endif

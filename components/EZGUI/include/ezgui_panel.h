#ifndef __EZGUI_PANEL_H__
#define __EZGUI_PANEL_H__

#include "ezgui_types.h"
#include "ezgui_obj.h"
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    EZGUI_OBJ
    Color_ARGB_t Background;
} EZGUI_Panel_t;

EZGUI_Panel_t *new_EZGUI_Panel(EZGUI_OBJECTS_T *Parrent);

#endif

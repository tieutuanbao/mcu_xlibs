#ifndef __EZGUI_LABEL_H__
#define __EZGUI_LABEL_H__

#include "ezgui_types.h"
#include "ezgui_font.h"
#include "ezgui_obj.h"

typedef struct {
    EZGUI_OBJ

    char *Text;
    struct {
        Color_ARGB_t BackGround;
        Color_ARGB_t ForeGround;
    } Color;
    const Font_t * Font;
} EZGUI_Label_t;

EZGUI_Label_t *new_EZGUI_Label(EZGUI_OBJECTS_T *Parrent);

#endif

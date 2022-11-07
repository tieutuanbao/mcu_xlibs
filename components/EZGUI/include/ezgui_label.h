#ifndef __EZGUI_LABEL_H__
#define __EZGUI_LABEL_H__

#include "ezgui_obj.h"
#include "ezgui_font.h"

typedef struct {
    EZGUI_Objects_t Object;
    char *Text;
    struct {
        Color_ARGB_t BackGround;
        Color_ARGB_t ForeGround;
    } Color;
    const Font_t * Font;
} EZGUI_Label_t;

EZGUI_Label_t *EZGUI_Label_new(EZGUI_Objects_t *Parrent);

#endif

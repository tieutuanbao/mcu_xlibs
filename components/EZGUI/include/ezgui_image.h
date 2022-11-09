#ifndef __EZGUI_IMAGE_H__
#define __EZGUI_IMAGE_H__

#include "ezgui_obj.h"

typedef struct {
    EZGUI_Objects_t Object;
    Color_ARGB_t (*Image_GetPixel)(Point_t PosPixel);
    Color_ARGB_t *Buf;
} EZGUI_Image_t;

EZGUI_Image_t *EZGUI_Image_new(EZGUI_Objects_t *Parrent);

#endif

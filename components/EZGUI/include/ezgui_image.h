#ifndef __EZGUI_IMAGE_H__
#define __EZGUI_IMAGE_H__

#include "ezgui_obj.h"

typedef struct {
    EZGUI_Objects_t Object;
    Size_t (*GetSize_Driver)(char *FilePath);
    void (*GetData_Driver)(char *FilePath, Color_ARGB_t *Buf, Area_t Area);
    char *FilePath;
    Color_ARGB_t *Buf;
} EZGUI_Image_t;

EZGUI_Image_t *EZGUI_Image_new(EZGUI_Objects_t *Parrent);

#endif

#ifndef __EZGUI_H__
#define __EZGUI_H__


#include <stdint.h>
#include "color.h"
#include "graphic.h"
#include "ezgui_obj.h"
#include "Fonts.h"

#define EZGUI_DEFAULT_FONT  &Arial
typedef void (*Driver_t)(Graphics_t *Graphic, Area_t Area);

typedef enum {
    EZGUI_PIXEL_TYPE_MONOCHOME,
    EZGUI_PIXEL_TYPE_RGB
} EZGUI_GraphicType_t;

typedef struct {
    EZGUI_Objects_t Object;
    Size_t BlockRes;
    Size_t FullRes;
    void *Buf[2];
    DrawPoint_t DrawPoint_Drv;
    Driver_t Driver;
} EZGUI_t;

EZGUI_t *EZGUI_GUI_new(Size_t DisplaySize, Size_t BlockSize, Driver_t Driver, void *Buf1, void *Buf2, EZGUI_GraphicType_t GraphicType);
void EZGUI_Update(EZGUI_t *GUI);


#endif

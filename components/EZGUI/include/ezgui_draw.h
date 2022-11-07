#ifndef __EZGUI_DRAW_H__
#define __EZGUI_DRAW_H__

#include "graphic.h"
#include "color.h"
#include "ezgui_font.h"

typedef void (*DrawPoint_t)(Graphics_t *Graphic, Point_t Point, void *Color);

void EZGUI_Draw_Point_8bit(Graphics_t *Graphic, Point_t Point, uint8_t *Color);
void EZGUI_Draw_Point_24bit(Graphics_t *Graphic, Point_t Point, Color_RGB_t *Color);
void EZGUI_Draw_String(DrawPoint_t DrawPoint, Graphics_t *Graphic, Point_t Point, const char *str, void *Color, const Font_t *Font);
void EZGUI_Draw_Line(DrawPoint_t DrawPoint, Graphics_t *Graphic, Point_t StartPoint, Point_t StopPoint, uint8_t Step, void *Color);

#endif

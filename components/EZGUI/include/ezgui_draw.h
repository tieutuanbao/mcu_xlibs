#ifndef __EZGUI_DRAW_H__
#define __EZGUI_DRAW_H__

#include "ezgui_font.h"
#include "ezgui_types.h"

void EZGUI_Draw_Point_8bit(void *Buffer, Size_t BufferSize, Point_t Point, uint8_t *Color);
void EZGUI_Draw_Point_24bit(void *Buffer, Size_t BufferSize, Point_t Point, Color_RGB_t *Color);
void EZGUI_Draw_String(EZGUI_Graphics_t *Graph, DrawPoint_Driver_t DrawPoint_Driver, Point_t Point, const char *str, void *Color, const Font_t *Font);
void EZGUI_Draw_Line(EZGUI_Graphics_t *Graph, DrawPoint_Driver_t DrawPoint, Position_t StartPos, Position_t StopPos, uint8_t Step, void *Color);
void EZGUI_Draw_Rectangle(EZGUI_Graphics_t *Graph, DrawPoint_Driver_t DrawPoint, Position_t StartPos, Position_t StopPos, void *Color);
void EZGUI_Draw_Image(EZGUI_Graphics_t *Graph, DrawPoint_Driver_t DrawPoint, Position_t StartPos, Size_t Size, Color_ARGB_t (*Image_GetPixel)(Point_t PosPixel));

#endif

#include "ezgui_panel.h"
#include "ezgui_draw.h"

void EZGUI_Panel_Draw(EZGUI_Panel_t *Panel, EZGUI_Graphics_t *Graph, Position_t Offset, DrawPoint_Driver_t DrawPoint_Driver) {
    /* Fill Panel */
    EZGUI_Draw_Rectangle(Graph, DrawPoint_Driver, Panel->Position, (Position_t){Panel->Position.X + Graph->Size.Width - 1, Panel->Position.Y + Graph->Size.Height - 1}, &(Color_ARGB_t){.RGB = COLOR_WHITE, .A = 100});
    for(uint16_t IndexObj = 0; (Panel->Children[IndexObj] != 0); IndexObj++) {
        Panel->Children[IndexObj]->Draw(Panel->Children[IndexObj], Graph, (Position_t){.X = Panel->Position.X + Offset.X, .Y = Panel->Position.Y + Offset.Y}, DrawPoint_Driver);
    }
}

EZGUI_Panel_t *new_EZGUI_Panel(EZGUI_OBJECTS_T *Parrent) {
    EZGUI_Panel_t *Panel = (EZGUI_Panel_t *)malloc(sizeof(EZGUI_Panel_t));
    if(Panel) {
        Panel->InstanceSize = sizeof(EZGUI_Panel_t);
        Panel->Background = (Color_ARGB_t){.RGB = COLOR_WHITE, .A = 100};
        Panel->Draw = (EZGUI_ObjectDraw_t)EZGUI_Panel_Draw;
        Panel->Position = (Point_t){0, 0};
        Panel->Size = (Size_t){10, 10};
        Panel->Children = 0;
        EZGUI_Object_Add(Parrent, (EZGUI_OBJECTS_T *)Panel);
    }
    return Panel;
}

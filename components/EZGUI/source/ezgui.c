#include "ezgui.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Tạo mới một GUI
 * 
 * @param DisplaySize Kích thước màn hình
 * @param BlockSize Kích thước khối Render
 * @param Driver Driver hiển thị
 * @return EZGUI_t* 
 */
EZGUI_t *EZGUI_GUI_new(Size_t DisplaySize, Size_t BlockSize, Driver_t Driver, void *Buf1, void *Buf2, EZGUI_GraphicType_t GraphicType) {
    EZGUI_t *New_GUI = malloc(sizeof(EZGUI_t));
    New_GUI->Object.Children = 0;
    New_GUI->FullRes = DisplaySize;
    New_GUI->BlockRes = BlockSize;
    New_GUI->Driver = Driver;
    New_GUI->Buf[0] = Buf1;
    switch(GraphicType) {
        case EZGUI_PIXEL_TYPE_MONOCHOME : {
            New_GUI->DrawPoint_Drv = (DrawPoint_t)EZGUI_Draw_Point_8bit;
            break;
        }
        case EZGUI_PIXEL_TYPE_RGB : {
            New_GUI->DrawPoint_Drv = (DrawPoint_t)EZGUI_Draw_Point_24bit;
            break;
        }
    }
    return New_GUI;
}

void EZGUI_Update(EZGUI_t *GUI) {
    Graphics_t DrawGraphic = {.Buf = GUI->Buf[0], .Size = GUI->BlockRes};
    for(uint16_t IndexVer = 0; IndexVer < GUI->FullRes.Height; IndexVer += GUI->BlockRes.Height) {
        for(uint16_t IndexHor = 0; IndexHor < GUI->FullRes.Width ; IndexHor += GUI->BlockRes.Width) {
            memset(GUI->Buf[0], 0, GUI->BlockRes.Height * GUI->BlockRes.Width * 3);
            /* Render */
            for(uint8_t IndexControl = 0; GUI->Object.Children[IndexControl] != 0; IndexControl++) {
                GUI->Object.Children[IndexControl]->Draw(GUI->DrawPoint_Drv, GUI->Object.Children[IndexControl], &DrawGraphic, (Point_t){-IndexHor, -IndexVer});
            }
            /* Extract */
            GUI->Driver(&DrawGraphic, (Area_t){.Start = {.X = IndexHor, .Y = IndexVer}, .Stop = {.X = IndexHor + GUI->BlockRes.Width - 1, .Y = IndexVer + GUI->BlockRes.Height - 1}});
        }
    }
}

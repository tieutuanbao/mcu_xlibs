#include "ezgui.h"
#include <stdlib.h>
#include <string.h>

void EZGUI_Draw(EZGUI_t *EZGUI) {
    Position_t Offset = {0, 0};
    Area_t Area = {0, 0};
    for(uint16_t IndexMonitor = 0; IndexMonitor < EZGUI->Monitor.Count; IndexMonitor++) {
        for(uint16_t Y_Render = EZGUI->Monitor.List[IndexMonitor].Offset.Y; Y_Render < EZGUI->Monitor.List[IndexMonitor].Resolution.Height; Y_Render += EZGUI->Monitor.List[IndexMonitor].Graph.Size.Height) {
            for(uint16_t X_Render = EZGUI->Monitor.List[IndexMonitor].Offset.X; X_Render < EZGUI->Monitor.List[IndexMonitor].Resolution.Width; X_Render += EZGUI->Monitor.List[IndexMonitor].Graph.Size.Width) {
                if(EZGUI->Children == 0) return;
                Area.Start = (Position_t){.X = X_Render, .Y = Y_Render};
                Area.Stop = (Position_t){.X = X_Render + EZGUI->Monitor.List[IndexMonitor].Graph.Size.Width - 1, .Y = Y_Render + EZGUI->Monitor.List[IndexMonitor].Graph.Size.Height - 1};
                Offset = (Position_t){-Area.Start.X, -Area.Start.Y};
                for(uint16_t IndexObj = 0; (EZGUI->Children[IndexObj] != 0); IndexObj++) {
                    /* Render */
                    EZGUI->Children[IndexObj]->Draw(EZGUI->Children[IndexObj], &EZGUI->Monitor.List[IndexMonitor].Graph, Offset, EZGUI->Monitor.List[IndexMonitor].DrawPoint_Driver);
                }
                /* Extract */
                EZGUI->Monitor.List[IndexMonitor].FrameBuffer_Driver(EZGUI->Monitor.List[IndexMonitor].Graph.Buffer, EZGUI->Monitor.List[IndexMonitor].Graph.Size, Area);
            }
        }
    }
}
EZGUI_Monitor_t *new_EZGUI_Monitor(EZGUI_t *EZGUI) {
    if(EZGUI->Monitor.Count == 0) {
        EZGUI->Monitor.List = (EZGUI_Monitor_t *)malloc(sizeof(EZGUI_Monitor_t));
        if(EZGUI->Monitor.List != 0) {
            EZGUI->Monitor.Count++;
            return EZGUI->Monitor.List + (EZGUI->Monitor.Count - 1);
        }
    }
    return 0;
}

void EZGUI_Monitor_setPixelType(EZGUI_Monitor_t *Monitor, EZGUI_PixelType_t PixelType) {
    switch(PixelType) {
        case EZGUI_PIXEL_TYPE_MONOCHOME : {
            Monitor->DrawPoint_Driver = (DrawPoint_Driver_t)EZGUI_Draw_Point_8bit;
            break;
        }
        case EZGUI_PIXEL_TYPE_RGB : {
            Monitor->DrawPoint_Driver = (DrawPoint_Driver_t)EZGUI_Draw_Point_24bit;
            break;
        }
        default : {
            break;
        }
    }
}
EZGUI_t *new_EZGUI(void) {
    EZGUI_t *GUI = malloc(sizeof(EZGUI_t));
    if(GUI) {
        memset(GUI, 0, sizeof(EZGUI_t));
    }    
    return GUI;
}

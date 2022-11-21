#include "ezgui_label.h"
#include <stdlib.h>
#include "ezgui_draw.h"
#include "Fonts.h"

static void EZGUI_Label_Draw(EZGUI_Label_t *Label, EZGUI_Graphics_t *Graph, Position_t Offset, DrawPoint_Driver_t DrawPoint_Driver) {
    Offset.X += Label->Position.X;
    Offset.Y += Label->Position.Y;
    if(Label->Text) {
        Font_Decode_t CharInfo;
        Size_t TotalString = {0, 0};
        /* Lấy tổng chiều cao và tổng chiều ngang */
        for(uint16_t IndexChar = 0; Label->Text[IndexChar] != 0x00; IndexChar += CharInfo.ByteCount) {
            CharInfo = Font_DecodeChar(Label->Text + IndexChar, Label->Font);
            if(TotalString.Height < CharInfo.Char->Height) TotalString.Height = CharInfo.Char->Height;
            TotalString.Width += CharInfo.Char->Width;
        }
        /* Tính lại vị trí Offset */
        if(TotalString.Width < Label->Size.Width) {
            Offset.X += (Label->Size.Width - TotalString.Width) / 2;
        }
        if(TotalString.Height < Label->Size.Height) {
            Offset.Y += (Label->Size.Height - TotalString.Height) / 2;
        }
        
        EZGUI_Draw_String(Graph, DrawPoint_Driver, Offset, Label->Text, (void *)&Label->Color.ForeGround, Label->Font);
    }
}

EZGUI_Label_t *new_EZGUI_Label(EZGUI_OBJECTS_T *Parrent) {
    EZGUI_Label_t *Label = (EZGUI_Label_t *)malloc(sizeof(EZGUI_Label_t));
    if(Label) {
        Label->InstanceSize = sizeof(EZGUI_Label_t);
        Label->Draw = (EZGUI_ObjectDraw_t)EZGUI_Label_Draw;
        Label->Position = (Point_t){0, 0};
        Label->Size = (Size_t){10, 10};
        Label->Children = 0;
        Label->Font = EZGUI_DEFAULT_FONT;
        Label->Color.BackGround = (Color_ARGB_t){.RGB = COLOR_WHITE, .A = 100};;
        Label->Color.ForeGround = (Color_ARGB_t){.RGB = COLOR_BLACK, .A = 100};;
        EZGUI_Object_Add(Parrent, (EZGUI_Objects_t *)Label);
    }
    return Label;
}

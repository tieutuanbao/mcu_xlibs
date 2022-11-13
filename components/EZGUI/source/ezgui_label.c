#include "ezgui_label.h"
#include "ezgui_draw.h"
#include "ezgui.h"
#include "stdlib.h"

static void Label_Draw(DrawPoint_t DrawPoint_Drv, EZGUI_Label_t *Label, Graphics_t *Graphic, Point_t Offset) {
    if(Label->Text) {
        Offset = (Point_t){Label->Object.Point.X + Offset.X, Label->Object.Point.Y + Offset.Y};
        Font_Decode_t CharInfo;
        Size_t TotalString = {0, 0};
        /* Lấy tổng chiều cao và tổng chiều ngang */
        for(uint16_t IndexChar = 0; Label->Text[IndexChar] != 0x00; IndexChar += CharInfo.ByteCount) {
            CharInfo = Font_DecodeChar(Label->Text + IndexChar, Label->Font);
            if(TotalString.Height < CharInfo.Char->Height) TotalString.Height = CharInfo.Char->Height;
            TotalString.Width += CharInfo.Char->Width;
        }
        /* Tính lại vị trí Offset */
        if(TotalString.Width < Label->Object.Size.Width) {
            Offset.X += (Label->Object.Size.Width - TotalString.Width) / 2;
        }
        if(TotalString.Height < Label->Object.Size.Height) {
            Offset.Y += (Label->Object.Size.Height - TotalString.Height) / 2;
        }
        
        EZGUI_Draw_String(DrawPoint_Drv, Graphic, Offset, Label->Text, (void *)&Label->Color.ForeGround, Label->Font);
    }
}

EZGUI_Label_t *EZGUI_Label_new(EZGUI_Objects_t *Parrent) {
    EZGUI_Label_t *Label = (EZGUI_Label_t *)malloc(sizeof(EZGUI_Label_t));
    if(Label) {
        Label->Object.InstanceSize = sizeof(EZGUI_Label_t);
        Label->Object.Draw = (Draw_t)Label_Draw;
        Label->Object.Point = (Point_t){0, 0};
        Label->Object.Size = (Size_t){10, 10};
        Label->Font = EZGUI_DEFAULT_FONT;
        Label->Color.BackGround = (Color_ARGB_t){.RGB = COLOR_WHITE, .A = 100};;
        Label->Color.ForeGround = (Color_ARGB_t){.RGB = COLOR_BLACK, .A = 100};;
        EZGUI_Object_Add(Parrent, (EZGUI_Objects_t *)Label);
    }
    return Label;
}

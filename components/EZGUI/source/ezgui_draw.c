#include "ezgui_draw.h"
#include "ezgui_font.h"

/**
 * @brief Vẽ điểm trên Graphic monochrome
 * 
 * @param Graphic 
 * @param Point 
 * @param Color 
 */
void EZGUI_Draw_Point_8bit(Graphics_t *Graphic, Point_t Point, uint8_t *Color) {
    if((Point.X < 0) || (Point.Y < 0) || (Point.X >= Graphic->Size.Width) || (Point.Y >= Graphic->Size.Height)) return;
    if(*Color) ((uint8_t *)(Graphic->Buf))[(Point.Y >> 3) * Graphic->Size.Width + Point.X] |= 0x01 << (Point.Y % 8);
    else ((uint8_t *)(Graphic->Buf))[(Point.Y >> 3) * Graphic->Size.Width + Point.X] &= ~(0x01 << (Point.Y % 8));
}
/**
 * @brief Vẽ điểm trên Graphic Fullcolor
 * 
 * @param Graphic 
 * @param Point 
 * @param Color 
 */
void EZGUI_Draw_Point_24bit(Graphics_t *Graphic, Point_t Point, Color_RGB_t *Color) {
    if((Point.X < 0) || (Point.Y < 0) || (Point.X >= Graphic->Size.Width) || (Point.Y >= Graphic->Size.Height)) return;
    ((Color_RGB_t *)(Graphic->Buf))[Point.Y * Graphic->Size.Width + Point.X] = *Color;
}

/**
 * @brief Vẽ chữ
 * 
 * @param DrawPoint Driver vẽ điểm ảnh
 * @param str Chuỗi cần vẽ
 * @param Graphic Khối Graphic vẽ chữ lên
 * @param Point Vị trí vẽ
 * @param Color Màu nội dung
 * @param Font Font chữ
 */
void EZGUI_Draw_String(DrawPoint_t DrawPoint, Graphics_t *Graphic, Point_t Point, const char *str, void *Color, const Font_t *Font) {
    if(str == 0) return;
    if(Graphic == 0) return;
    if(Point.X > Graphic->Size.Width) return;
    if(Point.Y > Graphic->Size.Height) return;
    Font_Decode_t CharInfo;

    for(uint16_t IndexChar = 0; str[IndexChar] != 0x00; IndexChar += CharInfo.ByteCount) {
        CharInfo = Font_DecodeChar(str + IndexChar, Font);
        for(uint16_t IndexWidth = 0; IndexWidth < CharInfo.Char->Width; IndexWidth++) {
            if((Point.X >= 0) && (Point.X < Graphic->Size.Width)) {
                for(uint16_t IndexHeight = 0; IndexHeight < CharInfo.Char->Height; IndexHeight++) {
                    if(((Point.Y + IndexHeight + CharInfo.Char->Top) >= 0) && ((Point.Y + IndexHeight + CharInfo.Char->Top) < Graphic->Size.Height)) {
                        uint8_t Byte8Pixel = CharInfo.Char->Map[(IndexHeight >> 3) * CharInfo.Char->Width + IndexWidth];
                        if(Byte8Pixel & (0x01 << (IndexHeight % 8))) {
                            DrawPoint(Graphic, (Point_t){.X = Point.X, .Y = Point.Y + IndexHeight + CharInfo.Char->Top}, Color);
                        }
                    }
                }
            }
            Point.X++;
        }
        Point.X++;
    }
}
/**
 * @brief Vẽ đường thẳng
 * 
 * @param DrawPoint Driver vẽ điểm ảnh
 * @param Graphic Graphic vẽ
 * @param StartPos Điểm bắt đầu
 * @param StopPos Điểm kết thúc
 * @param Step Bước vẽ
 * @param Color Màu vẽ
 */
void EZGUI_Draw_Line(DrawPoint_t DrawPoint, Graphics_t *Graphic, Point_t StartPos, Point_t StopPos, uint8_t Step, void *Color) {
    int32_t DistanceX = StopPos.X - StartPos.X;
    int32_t DistanceY = StopPos.Y - StartPos.Y;
    if(DistanceX < 0) {
        DistanceX = -DistanceX;
    }
    if(DistanceY < 0) {
        DistanceY = -DistanceY;
    }
    int DistanceNearPoint = 2 * DistanceY - DistanceX;
    /* Đường thẳng dọc */
    if(StopPos.X == StartPos.X) {
        /* Vẽ từ dưới lên */
        if(StartPos.Y > StopPos.Y) {
            while(StartPos.Y > StopPos.Y) {
                StartPos.Y -= Step;
                if(StartPos.Y < Graphic->Size.Height) {
                    if(StartPos.Y < 0) {
                        StartPos.Y = 0;
                        DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                        break;
                    }
                    DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                }
            }
        }
        /* Vẽ từ trên xuống */
        else if(StartPos.Y < StopPos.Y) {
            while(StartPos.Y < StopPos.Y) {
                StartPos.Y += Step;
                if(StartPos.Y >= 0) {
                    if(StartPos.Y > Graphic->Size.Height) {
                        StartPos.Y = Graphic->Size.Height;
                        DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                        break;
                    }
                    DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                }
            }
        }
        /* Vẽ 1 điểm duy nhất */
        else {
            DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
        }
    }
    /* Đường thẳng ngang */
    else if(StopPos.Y == StartPos.Y) {
        /* Vẽ từ phải sang trái */
        if(StartPos.X > StopPos.X) {
            while(StartPos.X > StopPos.X) {
                StartPos.X -= Step;
                if(StartPos.X < Graphic->Size.Width) {
                    if(StartPos.X < 0) {
                        StartPos.X = 0;
                        DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                        break;
                    }
                    DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                }
            }
        }
        /* Vẽ từ trái sang phải */
        else if(StartPos.X < StopPos.X) {
            while(StartPos.X < StopPos.X) {
                StartPos.X += Step;
                if(StartPos.X > Graphic->Size.Width) {
                    StartPos.X = Graphic->Size.Width;
                    break;
                }
                DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
            }
        }
        else {
            DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
        }        
    }
    /* Đường thẳng chéo */
    else {
        if(StartPos.Y > StopPos.Y) {
            Step = -Step;
        }
        DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
        while(StartPos.X != StopPos.X) {
            if (DistanceNearPoint < 0) DistanceNearPoint += (2 * DistanceY);
            else {
                DistanceNearPoint += 2 * (DistanceY - DistanceX);
                StartPos.Y += Step;
            }
            if(StartPos.X > StopPos.X) StartPos.X--;
            else StartPos.X++;
            DrawPoint(Graphic, (Point_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
        }
    }
}

void EZGUI_Draw_Rectangle(DrawPoint_t DrawPoint, Graphics_t *Graphic, Point_t StartPos, Size_t Size, uint8_t Step, void *Color) {

}

void EZGUI_Draw_Image(DrawPoint_t DrawPoint, Graphics_t *Graphic, Point_t StartPos, Size_t Size, Color_ARGB_t (*Image_GetPixel)(Point_t PosPixel)) {
    Point_t DrawPos = {0, 0};
    Color_ARGB_t PixelColor;
    for(int32_t IndexHeight = 0; IndexHeight < Size.Height; IndexHeight++) {
        DrawPos.Y = StartPos.Y + IndexHeight;
        if((DrawPos.Y >= 0) && (DrawPos.Y < Graphic->Size.Height)) {
            for(int32_t IndexWidth = 0; IndexWidth < Size.Width; IndexWidth++) {
                DrawPos.X = StartPos.X + IndexWidth;
                if((DrawPos.X >= 0) && (DrawPos.X < Graphic->Size.Width)) {
                    PixelColor = Image_GetPixel((Point_t){.X = IndexWidth, .Y = IndexHeight});
                    DrawPoint(Graphic, DrawPos, &PixelColor);
                }
            }
        }
    }
}

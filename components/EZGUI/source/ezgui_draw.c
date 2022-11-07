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
 * @param StartPoint Điểm bắt đầu
 * @param StopPoint Điểm kết thúc
 * @param Step Bước vẽ
 * @param Color Màu vẽ
 */
void EZGUI_Draw_Line(DrawPoint_t DrawPoint, Graphics_t *Graphic, Point_t StartPoint, Point_t StopPoint, uint8_t Step, void *Color) {
    int32_t DistanceX = StopPoint.X - StartPoint.X;
    int32_t DistanceY = StopPoint.Y - StartPoint.Y;
    if(DistanceX < 0) {
        DistanceX = -DistanceX;
    }
    if(DistanceY < 0) {
        DistanceY = -DistanceY;
    }
    int DistanceNearPoint = 2 * DistanceY - DistanceX;
    /* Đường thẳng dọc */
    if(StopPoint.X == StartPoint.X) {
        /* Vẽ từ dưới lên */
        if(StartPoint.Y > StopPoint.Y) {
            while(StartPoint.Y > StopPoint.Y) {
                StartPoint.Y -= Step;
                if(StartPoint.Y < Graphic->Size.Height) {
                    if(StartPoint.Y < 0) {
                        StartPoint.Y = 0;
                        DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
                        break;
                    }
                    DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
                }
            }
        }
        /* Vẽ từ trên xuống */
        else if(StartPoint.Y < StopPoint.Y) {
            while(StartPoint.Y < StopPoint.Y) {
                StartPoint.Y += Step;
                if(StartPoint.Y >= 0) {
                    if(StartPoint.Y > Graphic->Size.Height) {
                        StartPoint.Y = Graphic->Size.Height;
                        DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
                        break;
                    }
                    DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
                }
            }
        }
        /* Vẽ 1 điểm duy nhất */
        else {
            DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
        }
    }
    /* Đường thẳng ngang */
    else if(StopPoint.Y == StartPoint.Y) {
        /* Vẽ từ phải sang trái */
        if(StartPoint.X > StopPoint.X) {
            while(StartPoint.X > StopPoint.X) {
                StartPoint.X -= Step;
                if(StartPoint.X < Graphic->Size.Width) {
                    if(StartPoint.X < 0) {
                        StartPoint.X = 0;
                        DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
                        break;
                    }
                    DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
                }
            }
        }
        /* Vẽ từ trái sang phải */
        else if(StartPoint.X < StopPoint.X) {
            while(StartPoint.X < StopPoint.X) {
                StartPoint.X += Step;
                if(StartPoint.X > Graphic->Size.Width) {
                    StartPoint.X = Graphic->Size.Width;
                    break;
                }
                DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
            }
        }
        else {
            DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
        }        
    }
    /* Đường thẳng chéo */
    else {
        if(StartPoint.Y > StopPoint.Y) {
            Step = -Step;
        }
        DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
        while(StartPoint.X != StopPoint.X) {
            if (DistanceNearPoint < 0) DistanceNearPoint += (2 * DistanceY);
            else {
                DistanceNearPoint += 2 * (DistanceY - DistanceX);
                StartPoint.Y += Step;
            }
            if(StartPoint.X > StopPoint.X) StartPoint.X--;
            else StartPoint.X++;
            DrawPoint(Graphic, (Point_t){.X = StartPoint.X, .Y = StartPoint.Y}, Color);
        }
    }
}

void EZGUI_Draw_Rectangle(DrawPoint_t DrawPoint, Graphics_t *Graphic, Point_t StartPoint, Size_t Size_t, uint8_t Step, void *Color) {

}

void EZGUI_Draw_Image
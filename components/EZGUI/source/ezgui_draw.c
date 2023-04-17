#include "ezgui_draw.h"
#include "ezgui_font.h"

/**
 * @brief Vẽ điểm trên Graphic monochrome
 * 
 * @param Graphic 
 * @param Position 
 * @param Color 
 */
void EZGUI_Draw_Point_8bit(void *Buffer, Size_t BufferSize, Position_t Position, uint8_t *Color) {
    if((Position.X < 0) || (Position.Y < 0) || (Position.X >= BufferSize.Width) || (Position.Y >= BufferSize.Height)) return;
    if(*Color) ((uint8_t *)(Buffer))[(Position.Y >> 3) * BufferSize.Width + Position.X] |= 0x01 << (Position.Y % 8);
    else ((uint8_t *)(Buffer))[(Position.Y >> 3) * BufferSize.Width + Position.X] &= ~(0x01 << (Position.Y % 8));
}
/**
 * @brief Vẽ điểm trên Graphic Fullcolor
 * 
 * @param Graphic 
 * @param Position 
 * @param Color 
 */
void EZGUI_Draw_Point_24bit(void *Buffer, Size_t BufferSize, Position_t Position, Color_RGB_t *Color) {
    if((Position.X < 0) || (Position.Y < 0) || (Position.X >= BufferSize.Width) || (Position.Y >= BufferSize.Height)) return;
    ((Color_RGB_t *)(Buffer))[Position.Y * BufferSize.Width + Position.X] = *Color;
}

/**
 * @brief Vẽ chữ
 * 
 * @param DrawPoint Driver vẽ điểm ảnh
 * @param str Chuỗi cần vẽ
 * @param Graphic Khối Graphic vẽ chữ lên
 * @param Position Vị trí vẽ
 * @param Color Màu nội dung
 * @param Font Font chữ
 */
void EZGUI_Draw_String(EZGUI_Graphics_t *Graph, DrawPoint_Driver_t DrawPoint, Position_t Position, const char *str, void *Color, const Font_t *Font) {
    if(str == 0) return;
    if(Graph == 0) return;
    if(Position.X > Graph->Size.Width) return;
    if(Position.Y > Graph->Size.Height) return;
    Font_Decode_t CharInfo;

    for(uint16_t IndexChar = 0; str[IndexChar] != 0x00; IndexChar += CharInfo.ByteCount) {
        CharInfo = Font_DecodeChar(str + IndexChar, Font);
        for(uint16_t IndexWidth = 0; IndexWidth < CharInfo.Char->Width; IndexWidth++) {
            if((Position.X >= 0) && (Position.X < Graph->Size.Width)) {
                for(uint16_t IndexHeight = 0; IndexHeight < CharInfo.Char->Height; IndexHeight++) {
                    if(((Position.Y + IndexHeight + CharInfo.Char->Top) >= 0) && ((Position.Y + IndexHeight + CharInfo.Char->Top) < Graph->Size.Height)) {
                        uint8_t Byte8Pixel = CharInfo.Char->Map[(IndexHeight >> 3) * CharInfo.Char->Width + IndexWidth];
                        if(Byte8Pixel & (0x01 << (IndexHeight % 8))) {
                            DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = Position.X, .Y = Position.Y + IndexHeight + CharInfo.Char->Top}, Color);
                        }
                    }
                }
            }
            Position.X++;
        }
        Position.X++;
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
void EZGUI_Draw_Line(EZGUI_Graphics_t *Graph, DrawPoint_Driver_t DrawPoint, Position_t StartPos, Position_t StopPos, uint8_t Step, void *Color) {
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
                if(StartPos.Y < Graph->Size.Height) {
                    if(StartPos.Y < 0) {
                        StartPos.Y = 0;
                        DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                        break;
                    }
                    DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                }
            }
        }
        /* Vẽ từ trên xuống */
        else if(StartPos.Y < StopPos.Y) {
            while(StartPos.Y < StopPos.Y) {
                StartPos.Y += Step;
                if(StartPos.Y >= 0) {
                    if(StartPos.Y > Graph->Size.Height) {
                        StartPos.Y = Graph->Size.Height;
                        DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                        break;
                    }
                    DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                }
            }
        }
        /* Vẽ 1 điểm duy nhất */
        else {
            DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
        }
    }
    /* Đường thẳng ngang */
    else if(StopPos.Y == StartPos.Y) {
        /* Vẽ từ phải sang trái */
        if(StartPos.X > StopPos.X) {
            while(StartPos.X > StopPos.X) {
                StartPos.X -= Step;
                if(StartPos.X < Graph->Size.Width) {
                    if(StartPos.X < 0) {
                        StartPos.X = 0;
                        DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                        break;
                    }
                    DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
                }
            }
        }
        /* Vẽ từ trái sang phải */
        else if(StartPos.X < StopPos.X) {
            while(StartPos.X < StopPos.X) {
                StartPos.X += Step;
                if(StartPos.X > Graph->Size.Width) {
                    StartPos.X = Graph->Size.Width;
                    break;
                }
                DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
            }
        }
        else {
            DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
        }
    }
    /* Đường thẳng chéo */
    else {
        if(StartPos.Y > StopPos.Y) {
            Step = -Step;
        }
        DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
        while(StartPos.X != StopPos.X) {
            if (DistanceNearPoint < 0) DistanceNearPoint += (2 * DistanceY);
            else {
                DistanceNearPoint += 2 * (DistanceY - DistanceX);
                StartPos.Y += Step;
            }
            if(StartPos.X > StopPos.X) StartPos.X--;
            else StartPos.X++;
            DrawPoint(Graph->Buffer, Graph->Size, (Position_t){.X = StartPos.X, .Y = StartPos.Y}, Color);
        }
    }
}

void EZGUI_Draw_Rectangle(EZGUI_Graphics_t *Graph, DrawPoint_Driver_t DrawPoint, Position_t StartPos, Position_t StopPos, void *Color) {
    Position_t DrawPos;
    for(DrawPos.Y = StartPos.Y; DrawPos.Y <= StopPos.Y; DrawPos.Y++) {
        if(DrawPos.Y >= 0) {
            for(DrawPos.X = StartPos.X; DrawPos.X <= StopPos.X; DrawPos.X++) {
                if(DrawPos.X >= 0) {
                    DrawPoint(Graph->Buffer, Graph->Size, (Position_t){DrawPos.X, DrawPos.Y}, Color);
                }
            }
        }
    }
}

void EZGUI_Draw_Image(EZGUI_Graphics_t *Graph, DrawPoint_Driver_t DrawPoint, Position_t StartPos, Size_t Size, Color_ARGB_t (*Image_GetPixel)(Point_t PosPixel)) {
    Position_t DrawPos = {0, 0};
    Color_ARGB_t PixelColor;
    for(int32_t IndexHeight = 0; IndexHeight < Size.Height; IndexHeight++) {
        DrawPos.Y = StartPos.Y + IndexHeight;
        if((DrawPos.Y >= 0) && (DrawPos.Y < Graph->Size.Height)) {
            for(int32_t IndexWidth = 0; IndexWidth < Size.Width; IndexWidth++) {
                DrawPos.X = StartPos.X + IndexWidth;
                if((DrawPos.X >= 0) && (DrawPos.X < Graph->Size.Width)) {
                    PixelColor = Image_GetPixel((Position_t){.X = IndexWidth, .Y = IndexHeight});
                    DrawPoint(Graph->Buffer, Graph->Size, DrawPos, &PixelColor);
                }
            }
        }
    }
}

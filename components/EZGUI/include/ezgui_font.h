#ifndef __EZGUI_FONT_H
#define __EZGUI_FONT_H

#include <stdint.h>

typedef struct {
    const uint8_t *Map;
    uint8_t Width;
    uint8_t Height;
    int8_t Top;
} Font_Char_t;

typedef struct {
    const Font_Char_t *Char;
    uint8_t ByteCount;
} Font_Decode_t;

typedef struct {
    const Font_Char_t *Table;
    uint16_t StartChar;
    uint16_t Size;
} Font_t;

Font_Decode_t Font_DecodeChar(const char *str, const Font_t *Font);

#endif

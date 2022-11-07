#include "ezgui_font.h"

static const uint32_t UTF8_Ref_Table[] = {
    0x0000C380, 0x0000C381, 0x00E1BAA2, 0x0000C383, 0x00E1BAA0, 0x0000C482, 0x00E1BAB0, 0x00E1BAAE, 0x00E1BAB2, 0x00E1BAB4,
    0x00E1BAB6, 0x0000C382, 0x00E1BAA6, 0x00E1BAA4, 0x00E1BAA8, 0x00E1BAAA, 0x00E1BAAC, 0x0000C490, 0x0000C388, 0x0000C389,
    0x00E1BABA, 0x00E1BABC, 0x00E1BAB8, 0x0000C38A, 0x00E1BB80, 0x00E1BABE, 0x00E1BB82, 0x00E1BB84, 0x00E1BB86, 0x0000C38C,
    0x0000C38D, 0x00E1BB88, 0x0000C4A8, 0x00E1BB8A, 0x0000C392, 0x0000C393, 0x00E1BB8E, 0x0000C395, 0x00E1BB8C, 0x0000C394,
    0x00E1BB92, 0x00E1BB90, 0x00E1BB94, 0x00E1BB96, 0x00E1BB98, 0x0000C6A0, 0x00E1BB9C, 0x00E1BB9A, 0x00E1BB9E, 0x00E1BBA0,
    0x00E1BBA2, 0x0000C399, 0x0000C39A, 0x00E1BBA6, 0x0000C5A8, 0x00E1BBA4, 0x0000C6AF, 0x00E1BBAA, 0x00E1BBA8, 0x00E1BBAC,
    0x00E1BBAE, 0x00E1BBB0, 0x00E1BBB2, 0x0000C39D, 0x00E1BBB6, 0x00E1BBB8, 0x00E1BBB4, 0x0000C3A0, 0x0000C3A1, 0x00E1BAA3,
    0x0000C3A3, 0x00E1BAA1, 0x0000C483, 0x00E1BAB1, 0x00E1BAAF, 0x00E1BAB3, 0x00E1BAB5, 0x00E1BAB7, 0x0000C3A2, 0x00E1BAA7,
    0x00E1BAA5, 0x00E1BAA9, 0x00E1BAAB, 0x00E1BAAD, 0x0000C491, 0x0000C3A8, 0x0000C3A9, 0x00E1BABB, 0x00E1BABD, 0x00E1BAB9,
    0x0000C3AA, 0x00E1BB81, 0x00E1BABF, 0x00E1BB83, 0x00E1BB85, 0x00E1BB87, 0x0000C3AC, 0x0000C3AD, 0x00E1BB89, 0x0000C4A9,
    0x00E1BB8B, 0x0000C3B2, 0x0000C3B3, 0x00E1BB8F, 0x0000C3B5, 0x00E1BB8D, 0x0000C3B4, 0x00E1BB93, 0x00E1BB91, 0x00E1BB95,
    0x00E1BB97, 0x00E1BB99, 0x0000C6A1, 0x00E1BB9D, 0x00E1BB9B, 0x00E1BB9F, 0x00E1BBA1, 0x00E1BBA3, 0x0000C3B9, 0x0000C3BA,
    0x00E1BBA7, 0x0000C5A9, 0x00E1BBA5, 0x0000C6B0, 0x00E1BBAB, 0x00E1BBA9, 0x00E1BBAD, 0x00E1BBAF, 0x00E1BBB1, 0x00E1BBB3,
    0x0000C3BD, 0x00E1BBB7, 0x00E1BBB9, 0x00E1BBB5
};

Font_Decode_t Font_DecodeChar(const char *str, const Font_t *Font) {
    Font_Decode_t CharInfo = {.Char = Font->Table + (127 - ' '), .ByteCount = 1};
    if((uint8_t)*str > 0x7F) {
        uint32_t UTF8_Code = 0;
        if(((uint8_t)*str & 0xE8) == 0xE0) {
            UTF8_Code |= (*(str++));
            UTF8_Code <<= 8;
            UTF8_Code |= (*(str++));
            UTF8_Code <<= 8;
            UTF8_Code |= *str;
            CharInfo.ByteCount = 3;
        }
        else if(((uint8_t)*str & 0xE0) ==  0xC0) {
            UTF8_Code |= (*str++);
            UTF8_Code <<= 8;
            UTF8_Code |= *str;
            CharInfo.ByteCount = 2;
        }
        for(uint8_t Index_CharCode = 0; Index_CharCode < (sizeof(UTF8_Ref_Table) / sizeof(UTF8_Ref_Table[0])); Index_CharCode++){
            if(UTF8_Code == UTF8_Ref_Table[Index_CharCode]) {
                CharInfo.Char = Font->Table + (Index_CharCode + 128 - ' ');
                return CharInfo;
            }
        }
        CharInfo.ByteCount = 1;
        return CharInfo;
    }
    else{
        if((uint8_t)*str < 32) {
            return CharInfo;
        }
        CharInfo.Char = Font->Table + ((uint8_t)(*str) - ' ');
        return CharInfo;
    }
}

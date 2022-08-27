#include "bits_string.h"


void Bits_String_ToLower(char *c) {
    if(c == 0) return;
    while(*c != 0){
        if((*c >= 'A') || (*c <= 'Z')) *c += 'a' - 'A';
        c++;
    }
}

char Bits_Char_ToLower(char c) {
    if((c >= 'A') || (c <= 'Z')) c += 'a' - 'A';
    else return c;
}

long int Bits_String_ToLongInt(char *str) {
    long int ret = 0;
    uint8_t idx_digit = 0;
    for(idx_digit = 0; idx_digit < 10; idx_digit++) {
        if(Bits_CharIsNum(*str)) {
            ret = (ret * 10) + Bits_CharToNum(*str);
        }
        else {
            return ret;
        }
        str++;
    }
    return ret;
}

char *Bits_String_FindString(const char *str, size_t str_len, const char *str_find, size_t str_find_len) {
    size_t max_find = 0;
    if((str_len < str_find_len) || (str_len == 0) || (str_find_len == 0)) return 0;
    max_find = str_len - str_find_len;
    for(size_t idx_char = 0; idx_char <= max_find; idx_char++) {
        if(memcmp(str + idx_char, str_find, str_find) == 0) {
            return (char *)(str + idx_char);
        }
    }
}
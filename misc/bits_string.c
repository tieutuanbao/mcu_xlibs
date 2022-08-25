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
#include "bits_string.h"

void Bits_String_ToLower(char *c) {
    if(c == 0) return;
    while(*c != 0){
        if((*c >= 'A') || (*c <= 'Z')) *c += 'a' - 'A';
        c++;
    }
}

char Bits_Char_ToLower(char c) {
    if((c >= 'A') || (c <= 'Z')) return (c - 'A' + 'a');
    else return c;
}

long int Bits_String_ToInt(char *str) {
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
        if(memcmp(str + idx_char, str_find, str_find_len) == 0) {
            return (char *)(str + idx_char);
        }
    }
    return 0;
}

int Bits_sprintf(char * str, const char * format, ... ) {
    va_list args;
    va_start(args, format);
    vsprintf(str,format, args);
    va_end(args);
    return 0;
}

char *Bits_Int_ToString(long int num, char *buf, uint8_t size_buf) {
    long int temp_div = 0;
    uint8_t count_digit = 0;
    /* Đếm số digit trong num */
    count_digit = Bits_Int_CountDigit(num);    
    if(count_digit > size_buf) count_digit = size_buf;  /* Giới hạn số digit theo size_buf */    
    temp_div = Bits_Int_Pow(10, count_digit);
    for(uint8_t idx_digit = 0; idx_digit < count_digit; idx_digit++) {
        temp_div /= 10;
        buf[idx_digit] = ((num / temp_div) % 10) + '0';
    }
    return buf;
}
#include "bits_string.h"

uint8_t Bits_Char_toNum(char c, uint8_t base) {
    switch(base) {
        case 10: {
            return (c - '0');
        }
        case 16: {
            if((c >= 'A') && (c <= 'F')) {
                return c - 55;
            }
            else if((c >= 'a') && (c <= 'f')) {
                return c - 87;
            }
            else if((c >= '0') && (c <= '9')) {
                return c - '0';
            }
            return 0;
        }
    }
    return 0;
}

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


/**
 * @brief 
 * 
 * @param str Chuỗi cần chuyển đổi
 * @param len Độ dài chuỗi
 * @param base 10: decimal, 16: hexadecimal
 * @return long int 
 */
long int Bits_String_ToInt(char *str, uint8_t len, uint8_t base) {
    long int ret = 0;
    uint8_t idx_digit = 0;
    bool isNeg = false;
    if(base == 16) {
        if((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
            str += 2;
            if(len >= 2) {
                len -= 2;
            }
        }
        if(len > 8) {
            return 0;
        }
    }
    else if(base == 10) {
        if(str[0] == '-') {
            isNeg = true;
            str++;
            if(len >= 1) {
                len -= 1;
            }
        }
    }
    for(idx_digit = 0; idx_digit < len; idx_digit++) {
        if(base == 10) {
            if(Bits_CharIsNum(*str)) {
                ret = (ret * 10) + Bits_CharToNum(*str);
            }
            else {
                if(isNeg == true) {
                    ret = 0 - ret;
                }
                return ret;
            }
        }
        else if(base == 16) {
            if(Bits_CharIsHex(str[0])) {
                ret <<= 4;
                ret |= Bits_Char_toNum(str[0], 16);
            }
            else {
                return ret;
            }
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

void Bits_String_fromInt(long int num, char *buf, uint8_t size_buf, uint8_t specChar) {
    long int temp_div = 0;
    uint8_t count_digit = 0;
    switch(specChar) {
        case 'd' : {
            /* Đếm số digit trong num */
            count_digit = Bits_Int_CountDigit(num);    
            if(count_digit > size_buf) count_digit = size_buf;  /* Giới hạn số digit theo size_buf */    
            temp_div = Bits_Int_Pow(10, count_digit);
            for(uint8_t idx_digit = 0; idx_digit < count_digit; idx_digit++) {
                temp_div /= 10;
                buf[idx_digit] = ((num / temp_div) % 10) + '0';
            }
            break;
        }
        case 'x': case 'X' : {
            uint8_t countHex = 0;
            while((num >> (4 * countHex)) != 0) {
                countHex++;
            }
            for(uint8_t indexBuf = countHex; indexBuf > 0; indexBuf--) {
                uint8_t tempHex = num & 0x0F;
                if(tempHex >= 10) {
                    if(specChar == 'x') {
                        buf[indexBuf - 1] = tempHex + 87;
                    }
                    else {
                        buf[indexBuf - 1] = tempHex + 55;
                    }
                }
                else {
                    buf[indexBuf - 1] = tempHex + '0';
                }
                num >>= 4;
                if(num == 0) {
                    return;
                }
            }
            break;
        }
    }
}
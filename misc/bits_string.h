#ifndef __BITS_STRING_H
#define __BITS_STRING_H

#ifndef bool
#include <stdbool.h>
#endif

#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include "bits_math.h"

#define Bits_CharIsNum(n)       (((n) >= '0') && ((n) <= '9'))
#define Bits_CharToNum(n)       (n - '0')
#define Bits_CharIsHex(n)       (((n >= 'a') && (n <= 'f')) || ((n >= 'A') && (n <= 'F')) || ((n >= '0') && (n <= '9')))

void Bits_String_ToLower(char *c);
char Bits_Char_ToLower(char c);
long int Bits_String_ToInt(char *str, uint8_t len, uint8_t base);
char *Bits_String_FindString(const char *str, size_t str_len, const char *str_find, size_t str_find_len);
void Bits_String_fromInt(long int num, char *buf, uint8_t size_buf, uint8_t specChar);

#endif
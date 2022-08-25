#ifndef __BITS_STRING_H
#define __BITS_STRING_H

#ifndef bool
#include <stdbool.h>
#endif

#include <stdint.h>

#define Bits_CharIsNum(n)       (((n) >= '0') && ((n) <= '9'))
#define Bits_CharToNum(n)       (n - '0')

void Bits_String_ToLower(char *c);
char Bits_Char_ToLower(char c);
long int Bits_String_ToLongInt(char *str);

#endif
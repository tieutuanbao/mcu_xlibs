#ifndef __BITS_MATH_H__
#define __BITS_MATH_H__

#include <stdint.h>

uint32_t Bits_Int_Abs(long int num);
long int Bits_Int_Pow(long int num, uint8_t expo);
uint8_t Bits_Int_CountDigit(long int num);
double Bits_Float_Pow(double num, double expo);
double Bits_Float_Logarit(double base, double num);

#endif
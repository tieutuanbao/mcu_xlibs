#include "bits_math.h"
#include <stdint.h>

double Bits_Float_Pow(double num, double pow) {
    if(num == 0) {
        return 0;
    }
    if(pow == 0) {
        return 1;
    }
    double ret = num;
    for(uint16_t idx_pow = 1; idx_pow < pow; idx_pow++) {
        ret *= num;
    }
    return ret;
}

uint32_t Bits_Int_Abs(long int num) {
    if(num < 0) num = 0 - num;
    return num;
}

long int Bits_Int_Pow(long int num, uint8_t expo) {
    uint32_t ret = num;
    if(expo == 0) return 1;
    for(; --expo;) {
        ret = ret * num;
    }
    return ret;
}

uint8_t Bits_Int_CountDigit(long int num) {
    uint8_t idx_char = 0;
    if(num == 0) return 1;
    for(;idx_char < 12; idx_char++) {
        if((num / Bits_Int_Pow(10, idx_char)) == 0) {
            return idx_char;
        }
    }
    return 1;
}

double Bits_Float_Logarit(double base, double num) {
    double ret;
    if(base == 0) return 0;
    if(base == 1) return num;
    if(num == 1) return 0;
    for(uint32_t idx_expo = 0; idx_expo < 1000000; idx_expo++) {
        ret = Bits_Float_Pow(base, idx_expo);
        if(ret >= num) {
            return idx_expo;
        }
    }
    return 0;
}
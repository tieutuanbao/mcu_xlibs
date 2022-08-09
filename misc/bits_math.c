#include "bits_math.h"
#include <stdint.h>

double bits_math_pow(double val1, double val2) {
    if(val1 == 0) {
        return 0;
    }
    if(val2 == 0) {
        return 1;
    }
    double ret = val1;
    for(uint16_t idx_pow = 1; idx_pow < val2; idx_pow++) {
        ret *= val1;
    }
    return ret;
}
#ifndef __FFT_H
#define __FFT_H

#include <stdint.h>

#define FFT_N_SAMPLE                1024
#define FFT_SINCOS_SCALE        10000

extern const uint16_t hamming_window_table[];


extern inline void fft_radix_2_recursive_exec(int32_t *Re, int32_t *Im, uint16_t N_sample);

#endif

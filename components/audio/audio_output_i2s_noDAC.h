#ifndef __I2S_NO_DAC_H
#define __I2S_NO_DAC_H

#include "osapi.h"
#include "audio_output.h"
#include "i2s.h"


typedef struct{
    audio_output_t this;

    i2s_config_t i2s_config;

    int32_t last_sample;        // Last sample value
    int32_t cum_error;          // Running cumulative error since time began
    size_t byte_written;
    uint32_t index_sample;
    uint8_t gain;
} i2s_no_dac_t;

void i2s_no_dac_setGain(i2s_no_dac_t *dev, float fgain);

#endif
#ifndef __I2S_NO_DAC_H
#define __I2S_NO_DAC_H

#include "osapi.h"
#include "audio_output.h"
#include "i2s.h"


typedef struct{
    audio_output_t this;

    i2s_config_t i2s_config;

    int32_t last_sample;  // Last sample value
    int32_t cum_error;    // Running cumulative error since time began
    uint8_t oversample;
    uint16_t hertz;
    size_t byte_written;
    uint32_t index_sample;
} i2s_no_dac_t;

audio_output_stt_t i2s_no_dac_init(i2s_no_dac_t *dev);
audio_output_stt_t i2s_no_dac_config(i2s_no_dac_t *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample);
void i2s_no_dac_start(i2s_no_dac_t *dev);
void i2s_no_dac_stop(i2s_no_dac_t *dev);
int16_t i2s_no_dac_amplify(int32_t s);
audio_output_stt_t i2s_no_dac_consume_sample(i2s_no_dac_t *dev, int16_t *sample, uint16_t num_sample);

#endif
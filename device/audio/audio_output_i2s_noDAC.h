#ifndef __I2S_NO_DAC_H
#define __I2S_NO_DAC_H

#include "c_types.h"
#include "osapi.h"
#include "audio_output.h"
#include "esp8266_i2s.h"


typedef struct{
    audio_output_t instead;
    i2s_config_t i2s_config;

    int32_t last_sample;  // Last sample value
    int32_t cum_error;    // Running cumulative error since time began
    uint8_t oversample;
    uint16_t hertz;
    uint32_t byte_written;
    int index_sample;
} i2s_no_dac_t;

void FUNC_ON_FLASH i2s_no_dac_init(i2s_no_dac_t *dev);
void FUNC_ON_FLASH i2s_no_dac_config(i2s_no_dac_t *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample);
int16_t FUNC_ON_FLASH i2s_no_dac_amplify(int32_t s);
void FUNC_ON_FLASH i2s_no_dac_deltasigma(i2s_no_dac_t *dev, int16_t *sample, uint32_t *delta_buff);
bool FUNC_ON_FLASH i2s_no_dac_consume_sample(i2s_no_dac_t *dev, int16_t *sample);

#endif
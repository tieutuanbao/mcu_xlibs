#ifndef __AUDIO_OUTPUT_H
#define __AUDIO_OUTPUT_H

#include "port_macros.h"

typedef enum {
    audio_output_ok,
    audio_output_config_err,
    audio_output_sample_err,
} audio_output_stt_t;

typedef audio_output_stt_t (*driver_init_t)(void *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample);
typedef audio_output_stt_t (*driver_config_t)(void *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample);
typedef audio_output_stt_t (*consume_sample_t)(void *dev, int16_t *sample, uint16_t num_sample);
typedef void (*output_ctrl_t)(void *dev);

typedef struct {
    driver_init_t init;
    driver_config_t config;
    consume_sample_t consume;
    output_ctrl_t start;
    output_ctrl_t stop;
} audio_output_t;


#endif
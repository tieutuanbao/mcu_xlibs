#ifndef __AUDIO_OUTPUT_H
#define __AUDIO_OUTPUT_H

#include "port_macro.h"
#include "c_types.h"

typedef struct {
    void (*config)(void *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample);
    bool (*consume_sample)(void *dev, int16_t *sample);
} audio_output_t;


#endif
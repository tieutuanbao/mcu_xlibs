#ifndef __AUDIO_GEN_WAV_H
#define __AUDIO_GEN_WAV_H

#include <stdio.h>
#include <math.h>
#include "c_types.h"

#include "audio_output.h"

typedef struct {
    bool running;
    bool busy;
    uint32_t sample_rate;
    size_t file_size;
    uint8_t *file_ptr;
    uint8_t *read_curr_ptr;
    int16_t last_sample[256*2];
    uint8_t num_channel;
    uint8_t bit_per_sample;

    audio_output_t *driver;
} audio_gen_wav_t;


void FUNC_ON_FLASH audio_gen_wav_openfile(audio_gen_wav_t *dev, uint8_t *file_buf);
bool FUNC_ON_FLASH audio_gen_wav_is_running(audio_gen_wav_t *dev);
void FUNC_ON_FLASH audio_gen_wav_begin(audio_gen_wav_t *dev, void *driver);
void FUNC_ON_FLASH audio_gen_wav_loop(audio_gen_wav_t *dev);

#endif
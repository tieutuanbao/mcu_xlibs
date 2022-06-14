#ifndef __AUDIO_GEN_WAV_H
#define __AUDIO_GEN_WAV_H

#include <stdio.h>
#include <math.h>
#include "c_types.h"

#include "audio_output.h"
#include "audio_output_i2s_noDAC.h"

#define CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ   (8)

typedef enum {
    audio_gen_wav_ok,
    audio_gen_wav_running,
    audio_gen_wav_stopped,
    audio_gen_wav_file_error,
    audio_gen_wav_file_reading,
    audio_gen_wav_file_end
} audio_gen_wav_stt_t;

typedef struct {    
    uint32_t sample_rate;
    size_t file_size;
    uint16_t num_channel;
    uint8_t bits_per_sample;

    uint8_t *file_ptr;
    uint8_t *read_curr_ptr;
    
    /**
     * @brief Cờ báo dùng trong chương trình
     * 
     */
    audio_gen_wav_stt_t status;
    
    /**
     * @brief Mảng tạm lưu sample, mỗi phần tử tương ứng 1 kênh, tối đa 16 phần tử, tương ứng với tối đa 8 sample
     * 
     */
    int16_t last_sample[CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ * 2];
    /**
     * @brief Driver output cho wav
     * 
     */
    audio_output_t *driver;
} audio_gen_wav_t;


audio_gen_wav_stt_t FUNC_ON_FLASH audio_gen_wav_openfile(audio_gen_wav_t *dev, uint8_t *file_buf);
audio_gen_wav_stt_t FUNC_ON_FLASH audio_gen_wav_is_running(audio_gen_wav_t *dev);
audio_gen_wav_stt_t FUNC_ON_FLASH audio_gen_wav_regist_drv_output(audio_gen_wav_t *dev, void *driver);
audio_gen_wav_stt_t FUNC_ON_FLASH audio_gen_wav_loop(audio_gen_wav_t *dev);

#endif
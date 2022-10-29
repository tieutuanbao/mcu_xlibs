#ifndef __AUDIO_GEN_WAV_H
#define __AUDIO_GEN_WAV_H

#include <math.h>

#include "audio_output.h"
#include "audio_output_i2s_noDAC.h"

#define CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ   (DMA_BUFFER_SIZE)

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
    size_t data_size;
    uint16_t num_channel;
    uint16_t bits_per_sample;

    int16_t fd_file;
    size_t file_pos;

    uint8_t *buf_ptr;
    uint8_t *buf_pos;
    
    uint32_t num_sample_reading;
    /**
     * @brief Cờ báo dùng trong chương trình
     * 
     */
    audio_gen_wav_stt_t status;
    
    /**
     * @brief Mảng tạm lưu sample, mỗi phần tử tương ứng 1 kênh
     * 
     */
    int32_t last_sample[CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ * 2];
    /**
     * @brief Driver output cho wav
     * 
     */
    audio_output_t *driver;
} audio_gen_wav_t;


audio_gen_wav_stt_t audio_gen_wav_file(audio_gen_wav_t *dev, char *file_path);
audio_gen_wav_stt_t audio_gen_wav_buffer(audio_gen_wav_t *dev, uint8_t *file_buf);
audio_gen_wav_stt_t audio_gen_wav_is_running(audio_gen_wav_t *dev);
audio_gen_wav_stt_t audio_gen_wav_regist_drv_output(audio_gen_wav_t *dev, void *driver);
audio_gen_wav_stt_t audio_gen_wav_loop(audio_gen_wav_t *dev);

#endif
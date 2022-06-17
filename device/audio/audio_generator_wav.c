#include "audio_generator_wav.h"
#include "osapi.h"
#include <string.h>

#define TAG "audio_gen_wav: "
/**
 * @brief Hàm mở file WAV
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @param file_buf địa chỉ lưu file
 * @return audio_gen_wav_stt_t 
 */
FUNC_ON_FLASH audio_gen_wav_stt_t audio_gen_wav_openfile(audio_gen_wav_t *dev, uint8_t *file_buf) {
    dev->file_ptr = file_buf;
    /* Lấy dữ liệu từ file */
    dev->num_channel = (*(file_buf + 23) << 8) | *(file_buf + 22);          // Vị trí number channel
    dev->sample_rate = (*(file_buf + 27) << 24) | (*(file_buf + 26) << 16) | (*(file_buf + 25) << 8) | *(file_buf + 24);    // Vị trí Sample rate
    dev->bits_per_sample = ((*(file_buf + 35) << 8) | *(file_buf + 34));       // Bit per sample
    dev->file_size = (*(file_buf + 43) << 24) | (*(file_buf + 42) << 16) | (*(file_buf + 41) << 8) | *(file_buf + 40);      // Vị trí kích thước data
    dev->read_curr_ptr = (file_buf + 44);                                   // Vị trí data

    if((dev->bits_per_sample != 8) && (dev->bits_per_sample != 16) && (dev->bits_per_sample != 24)) return audio_gen_wav_file_error;
    
    memset(dev->last_sample, 0, sizeof(dev->last_sample));
    dev->num_sample_reading = 1;
    dev->status = audio_gen_wav_running;
    return audio_gen_wav_ok;
}

/**
 * @brief Cấu hình driver output 
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @param driver Driver output cho file
 * @return audio_gen_wav_stt_t 
 */
FUNC_ON_FLASH audio_gen_wav_stt_t audio_gen_wav_regist_drv_output(audio_gen_wav_t *dev, void *driver) {
    /* Đăng ký driver */
    dev->driver = driver;
    /* Cấu hình driver */
    return dev->driver->config(dev->driver, dev->num_channel, dev->sample_rate, dev->bits_per_sample);
}

/**
 * @brief Lấy dữ liệu wav
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @return audio_gen_wav_stt_t 
 */
FUNC_ON_FLASH audio_gen_wav_stt_t audio_get_next_data(audio_gen_wav_t *dev) {
    int16_t channel[2] = {0, 0};
    uint32_t r_l_number = 0;
    /* Tính số byte còn lại (Bytes chưa đọc) */
    uint32_t remaining = ((dev->file_ptr + 44) + dev->file_size) - dev->read_curr_ptr;
    if(dev->num_channel == 2) {
        r_l_number = (remaining / 2);
    }
    /* Giới hạn cặp sample (R+L) */
    if(r_l_number > CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ) r_l_number = CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ;
    else if(r_l_number == 0) return audio_gen_wav_file_end;
    // BITS_LOG("Sample can read: %d - %d\r\n", remaining, r_l_number);
    /* Lấy data sample từ buffer */
    for(uint16_t idx_RL = 0; idx_RL < r_l_number; idx_RL++) {
        /**
         * @brief Hiện tại chưa hỗ trợ 24bit
         * 
         */
        if(dev->bits_per_sample == 8) {
            if(dev->num_channel == 2) {
                channel[0] = dev->read_curr_ptr[0];
                channel[1] = dev->read_curr_ptr[1];
            }
            else if(dev->num_channel == 1) {
                channel[0] = dev->read_curr_ptr[0];
                channel[1] = dev->read_curr_ptr[0];
            }
        } else if(dev->bits_per_sample == 16) {
            if(dev->num_channel == 2) {
                channel[0] = dev->read_curr_ptr[0];
                channel[0] <<= 8;
                channel[0] |= dev->read_curr_ptr[1];

                channel[1] = dev->read_curr_ptr[0];
                channel[1] <<= 8;
                channel[1] |= dev->read_curr_ptr[1];
            }
            else if(dev->num_channel == 1) {
                channel[0] = dev->read_curr_ptr[0];
                channel[0] <<= 8;
                channel[0] |= dev->read_curr_ptr[1];

                channel[1] = dev->read_curr_ptr[0];
                channel[1] <<= 8;
                channel[1] |= dev->read_curr_ptr[1];
            }
        } else if(dev->bits_per_sample == 24){
            channel[0] = ((int16_t)(dev->read_curr_ptr[0]));
            channel[1] = ((int16_t)(dev->read_curr_ptr[1]));
        } else {
            channel[0] = 0;
            channel[1] = 0;
        }
        // BITS_LOG("Sample : %d - %d\r\n", channel[0], channel[1]);
        /* Get left data */
        dev->last_sample[idx_RL * 2] = channel[0];
        /* Get right data */
        dev->last_sample[idx_RL * 2 + 1] = channel[1];
        /* Tăng con trỏ dữ liệu */
        dev->read_curr_ptr += ((dev->bits_per_sample * dev->num_channel) / 8);
    }
    dev->num_sample_reading = r_l_number;
    return audio_gen_wav_file_reading;
}
/**
 * @brief Kiểm tra file đang đọc hay không
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @return audio_gen_wav_stt_t 
 */
FUNC_ON_FLASH audio_gen_wav_stt_t audio_gen_wav_is_running(audio_gen_wav_t *dev) {
    return dev->status;
}

/**
 * @brief Hàm thực thi đọc file
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @return audio_gen_wav_stt_t 
 */
FUNC_ON_FLASH audio_gen_wav_stt_t audio_gen_wav_loop(audio_gen_wav_t *dev) {
    if (dev->driver->consume(dev->driver, dev->last_sample, dev->num_sample_reading) != audio_output_ok) {
        return audio_gen_wav_stopped;
    }
    if (audio_get_next_data(dev) == audio_gen_wav_file_end) {
        dev->status = audio_gen_wav_stopped;
        return audio_gen_wav_stopped;
    }
    return audio_gen_wav_running;
}
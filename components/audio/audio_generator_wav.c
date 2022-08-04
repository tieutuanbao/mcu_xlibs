#include "audio_generator_wav.h"
#include "osapi.h"
#include <string.h>
#include "fs.h"

#define TAG "audio_gen_wav: "


FUNC_ON_FLASH audio_gen_wav_stt_t audio_gen_wav_file(audio_gen_wav_t *dev, char *file_path) {
    if(dev->fd_file > 0) {
        fclose(dev->fd_file);
    }
    dev->fd_file = fopen(file_path, "r");
    BITS_LOGD("open file wav: %s = %d\r\n", file_path, dev->fd_file);
    if(dev->fd_file > 0) {
        fseek(dev->fd_file, 22 ,SPIFFS_SEEK_SET);
        fread(dev->fd_file, (char *)(&dev->num_channel), 2);
        
        fseek(dev->fd_file, 24 ,SPIFFS_SEEK_SET);
        fread(dev->fd_file, (char *)(&dev->sample_rate), 4);

        fseek(dev->fd_file, 34 ,SPIFFS_SEEK_SET);
        fread(dev->fd_file, (char *)(&dev->bits_per_sample), 2);

        fseek(dev->fd_file, 40 ,SPIFFS_SEEK_SET);
        fread(dev->fd_file, (char *)(&dev->data_size), 4);
        
        fseek(dev->fd_file, 44 ,SPIFFS_SEEK_SET);

        dev->file_pos = 44;
        dev->buf_ptr = 0;
        dev->buf_pos = 0;

        memset(dev->last_sample, 0, sizeof(dev->last_sample));
        dev->num_sample_reading = 1;
        dev->status = audio_gen_wav_running;
    }
    else {
        return audio_gen_wav_file_error;
    }
    BITS_LOGD(" - num channel: %d\r\n", dev->num_channel);
    BITS_LOGD(" - sample rate: %d\r\n", dev->sample_rate);
    BITS_LOGD(" - bps: %d\r\n", dev->bits_per_sample);
    BITS_LOGD(" - data size: %d\r\n", dev->data_size);
    return audio_gen_wav_running;
}

/**
 * @brief Hàm mở file WAV
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @param file_buf địa chỉ lưu file
 * @return audio_gen_wav_stt_t 
 */
FUNC_ON_FLASH audio_gen_wav_stt_t audio_gen_wav_buffer(audio_gen_wav_t *dev, uint8_t *file_buf) {
    dev->buf_ptr = file_buf;
    /* Lấy dữ liệu từ file */
    dev->num_channel = (*(file_buf + 23) << 8) | *(file_buf + 22);          // Vị trí number channel
    dev->sample_rate = (*(file_buf + 27) << 24) | (*(file_buf + 26) << 16) | (*(file_buf + 25) << 8) | *(file_buf + 24);    // Vị trí Sample rate
    dev->bits_per_sample = ((*(file_buf + 35) << 8) | *(file_buf + 34));       // Bit per sample
    dev->data_size = (*(file_buf + 43) << 24) | (*(file_buf + 42) << 16) | (*(file_buf + 41) << 8) | *(file_buf + 40);      // Vị trí kích thước data
    dev->buf_pos = (file_buf + 44);                                   // Vị trí data

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
    dev->driver->config(dev->driver, dev->num_channel, dev->sample_rate, dev->bits_per_sample);
    dev->driver->start(dev->driver);
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
    uint32_t remaining = 0;
    if(dev->buf_ptr) {
        remaining = ((dev->buf_ptr + 44) + dev->data_size) - dev->buf_pos;
    }
    else if(dev->fd_file > 0) {
        remaining = favailable(dev->fd_file);
    }

    if(dev->num_channel == 2) {
        r_l_number = (remaining / 2);
    }
    /* Giới hạn cặp sample (R+L) */
    if(r_l_number > CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ) {
        r_l_number = CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ;
    }
    else if(r_l_number == 0) {
        return audio_gen_wav_file_end;
    }


    char *__wav_buf = (char *)malloc((r_l_number  + 1 ) * 2);
    fread(dev->fd_file, __wav_buf, r_l_number * 2);

    // BITS_LOG("Sample can read: %d - %d\r\n", remaining, r_l_number);
    /* Lấy data sample từ buffer */
    for(uint16_t idx_RL = 0; idx_RL < r_l_number; idx_RL++) {
        char r_val = 0;
        char l_val = 0;
        if(dev->buf_ptr) {
            r_val = dev->buf_pos[0];
            l_val = dev->buf_pos[1];
            /* Tăng con trỏ dữ liệu */
            dev->buf_pos += ((dev->bits_per_sample * dev->num_channel) / 8);
        }
        else {
            r_val = __wav_buf[idx_RL * ((dev->bits_per_sample * dev->num_channel) / 8)];
            l_val = __wav_buf[idx_RL * ((dev->bits_per_sample * dev->num_channel) / 8) + 1];
        }
        /**
         * @brief Hiện tại chưa hỗ trợ 24bit
         * 
         */
        if(dev->bits_per_sample == 8) {
            if(dev->num_channel == 2) {
                channel[0] = r_val;
                channel[1] = l_val;
            }
            else if(dev->num_channel == 1) {
                channel[0] = r_val;
                channel[1] = r_val;
            }
        } else if(dev->bits_per_sample == 16) {
            if(dev->num_channel == 2) {
                channel[0] = r_val;
                channel[0] <<= 8;
                channel[0] |= l_val;

                channel[1] = r_val;
                channel[1] <<= 8;
                channel[1] |= l_val;
            }
            else if(dev->num_channel == 1) {
                channel[0] = r_val;
                channel[0] <<= 8;
                channel[0] |= l_val;

                channel[1] = r_val;
                channel[1] <<= 8;
                channel[1] |= l_val;
            }
        } else if(dev->bits_per_sample == 24){
            channel[0] = ((int16_t)(r_val));
            channel[1] = ((int16_t)(l_val));
        } else {
            channel[0] = 0;
            channel[1] = 0;
        }
        // BITS_LOG("Sample : %d - %d\r\n", channel[0], channel[1]);
        /* Get left data */
        dev->last_sample[idx_RL * 2] = channel[0];
        /* Get right data */
        dev->last_sample[idx_RL * 2 + 1] = channel[1];
    }
    free(__wav_buf);
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
 * @brief Kiểm tra file đang đọc hay không
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @return audio_gen_wav_stt_t 
 */
FUNC_ON_FLASH void audio_gen_wav_stop(audio_gen_wav_t *dev) {
    if(dev->fd_file > 0) {
        fclose(dev->fd_file);
        dev->fd_file = -1;
    }
    dev->status = audio_gen_wav_stopped;
}


/**
 * @brief Hàm thực thi đọc file
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @return audio_gen_wav_stt_t 
 */
FUNC_ON_FLASH audio_gen_wav_stt_t audio_gen_wav_loop(audio_gen_wav_t *dev) {
    if (dev->driver->consume(dev->driver, dev->last_sample, dev->num_sample_reading) != audio_output_ok) {
        BITS_LOGD("Close file wav\r\n");
        if(dev->fd_file > 0) {
            fclose(dev->fd_file);
        }
        dev->status = audio_gen_wav_stopped;
        return audio_gen_wav_stopped;
    }
    if (audio_get_next_data(dev) == audio_gen_wav_file_end) {
        dev->status = audio_gen_wav_stopped;
        // dev->driver->stop(dev->driver);
        BITS_LOGD("Close file wav\r\n");
        if(dev->fd_file > 0) {
            fclose(dev->fd_file);
            dev->fd_file = -1;
        }
        return audio_gen_wav_stopped;
    }
    return audio_gen_wav_running;
}
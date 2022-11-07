#include "audio_generator_wav.h"
#include "osapi.h"
#include <string.h>
#include "fs.h"

#define TAG "audio_gen_wav: "


audio_gen_wav_stt_t audio_gen_wav_file(audio_gen_wav_t *dev, char *file_path) {
    if(dev->fd_file > 0) {
        fclose(dev->fd_file);
    }
    dev->fd_file = fopen(file_path, "r");
    // BITS_LOGD("open file wav: %s = %d\r\n", file_path, dev->fd_file);
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
    if(dev->driver) {
        dev->driver->config(dev->driver, dev->num_channel, dev->sample_rate, dev->bits_per_sample);
    }
    // BITS_LOGD(" - num channel: %d\r\n", dev->num_channel);
    // BITS_LOGD(" - sample rate: %d\r\n", dev->sample_rate);
    // BITS_LOGD(" - bps: %d\r\n", dev->bits_per_sample);
    // BITS_LOGD(" - data size: %d\r\n", dev->data_size);
    return audio_gen_wav_running;
}

/**
 * @brief Hàm mở file WAV
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @param file_buf địa chỉ lưu file
 * @return audio_gen_wav_stt_t 
 */
audio_gen_wav_stt_t audio_gen_wav_buffer(audio_gen_wav_t *dev, uint8_t *file_buf) {
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
audio_gen_wav_stt_t audio_gen_wav_regist_drv_output(audio_gen_wav_t *dev, void *driver) {
    /* Đăng ký driver */
    dev->driver = driver;
    /* Cấu hình driver */
    if((dev->num_channel != 0) && (dev->bits_per_sample >= 8)) dev->driver->init(dev->driver, dev->num_channel, dev->sample_rate, dev->bits_per_sample);
    dev->driver->start(dev->driver);
}

/**
 * @brief Lấy dữ liệu wav
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @return audio_gen_wav_stt_t 
 */
audio_gen_wav_stt_t audio_get_next_data(audio_gen_wav_t *dev) {
    uint32_t Couple_RL_Count = 0;
    /* Tính số byte còn lại (Bytes chưa đọc) */
    uint32_t ByteRemaining = 0;
    if(dev->fd_file > 0) {
        ByteRemaining = favailable(dev->fd_file);
    }
    else {
        ByteRemaining = ((dev->buf_ptr + 44) + dev->data_size) - dev->buf_pos;
    }
    if(dev->num_channel > 0) {
        Couple_RL_Count = (ByteRemaining / ((dev->bits_per_sample >> 3) * dev->num_channel));
    }
    else {
        Couple_RL_Count = dev->num_channel;
    }
    /* Giới hạn cặp sample (R+L) */
    if(Couple_RL_Count > CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ) {
        Couple_RL_Count = CONFIG_AUDIO_GEN_WAV_MAX_SAMPLE_READ;
    }
    else if(Couple_RL_Count == 0) {
        return audio_gen_wav_file_end;
    }
    /* Lấy dữ liệu FD file */
    if(dev->fd_file > 0) {
        dev->buf_ptr = (char *)malloc(Couple_RL_Count * dev->num_channel * (dev->bits_per_sample >> 3));
        fread(dev->fd_file, dev->buf_ptr, Couple_RL_Count * dev->num_channel * (dev->bits_per_sample >> 3));
    }
    if(dev->buf_ptr == 0) return audio_gen_wav_file_reading;

    // BITS_LOG("Sample can read: %d - %d\r\n", ByteRemaining, Couple_RL_Count);
    /* Lấy data sample từ buffer */
    uint8_t *posReadData_p = dev->buf_ptr;
    for(uint16_t idx_RL = 0; idx_RL < Couple_RL_Count; idx_RL++) {
        int32_t r_val = 0;
        int32_t l_val = 0;
        if(dev->bits_per_sample == 8) {         // Unsigned 8bit PCM
            r_val = (posReadData_p[0] - 128) << 8;
            l_val = (posReadData_p[dev->num_channel >> 1] - 128) << 8;
        }
        else if(dev->bits_per_sample == 16) {   // Signed 16Bit PCM
            r_val = posReadData_p[1];
            r_val <<= 8;
            r_val |= posReadData_p[0];
            r_val = (int32_t)((int16_t)r_val);
            l_val = posReadData_p[(dev->num_channel >> 1) + 1];
            l_val <<= 8;
            l_val |= posReadData_p[(dev->num_channel >> 1)];
            l_val = (int32_t)((int16_t)l_val);
        }
        else if(dev->bits_per_sample == 32) {   // Signed 32Bit PCM
            r_val = posReadData_p[3];
            r_val <<= 8;
            r_val |= posReadData_p[2];
            r_val <<= 8;
            r_val |= posReadData_p[1];
            r_val <<= 8;
            r_val |= posReadData_p[0];
            l_val = posReadData_p[(dev->num_channel >> 1) + 3];
            l_val <<= 8;
            l_val |= posReadData_p[(dev->num_channel >> 1) + 2];
            l_val <<= 8;
            l_val |= posReadData_p[(dev->num_channel >> 1) + 1];
            l_val <<= 8;
            l_val |= posReadData_p[(dev->num_channel >> 1)];
        }
        /* Tăng con trỏ dữ liệu */
        posReadData_p += (dev->bits_per_sample >> 3) * dev->num_channel;
        // BITS_LOG("Sample : %d - %d\r\n", r_val, l_val);
        /* Get left data */
        dev->last_sample[idx_RL * 2] = r_val;
        /* Get right data */
        dev->last_sample[idx_RL * 2 + 1] = l_val;
    }
    if(dev->fd_file > 0) {
        free(dev->buf_ptr);
    }
    dev->num_sample_reading = Couple_RL_Count;
    return audio_gen_wav_file_reading;
}

/**
 * @brief Kiểm tra file đang đọc hay không
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @return audio_gen_wav_stt_t 
 */
audio_gen_wav_stt_t audio_gen_wav_is_running(audio_gen_wav_t *dev) {
    return dev->status;
}

/**
 * @brief Kiểm tra file đang đọc hay không
 * 
 * @param dev địa chỉ lưu đối tượng đọc file
 * @return audio_gen_wav_stt_t 
 */
void audio_gen_wav_stop(audio_gen_wav_t *dev) {
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
audio_gen_wav_stt_t audio_gen_wav_loop(audio_gen_wav_t *dev) {
    if (dev->driver->consume(dev->driver, dev->last_sample, dev->num_sample_reading) != audio_output_ok) {
        // BITS_LOGD("Close file wav\r\n");
        if(dev->fd_file > 0) {
            fclose(dev->fd_file);
        }
        dev->status = audio_gen_wav_stopped;
        return audio_gen_wav_stopped;
    }
    if (audio_get_next_data(dev) == audio_gen_wav_file_end) {
        dev->status = audio_gen_wav_stopped;
        // dev->driver->stop(dev->driver);
        // BITS_LOGD("Close file wav\r\n");
        if(dev->fd_file > 0) {
            fclose(dev->fd_file);
            dev->fd_file = -1;
        }
        return audio_gen_wav_stopped;
    }
    return audio_gen_wav_running;
}
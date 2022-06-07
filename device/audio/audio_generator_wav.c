#include "audio_generator_wav.h"
#include "osapi.h"
#include <string.h>

void FUNC_ON_FLASH audio_gen_wav_openfile(audio_gen_wav_t *dev, uint8_t *file_buf) {
    dev->file_ptr = file_buf;
    /* Lấy dữ liệu từ file */
    dev->num_channel = *((uint16_t *)(file_buf + 22));      // Vị trí Sample rate
    dev->sample_rate = *((uint32_t *)(file_buf + 24));      // Vị trí Sample rate
    dev->bit_per_sample = *((uint16_t *)(file_buf + 34));   // Bit per sample
    dev->file_size = *((uint32_t *)(file_buf + 40));        // Vị trí kích thước data
    dev->read_curr_ptr = (file_buf + 44);        // Vị trí data
}

void FUNC_ON_FLASH audio_gen_wav_begin(audio_gen_wav_t *dev, void *driver) {
    dev->running = true;
    dev->busy = false;
    dev->read_curr_ptr = dev->file_ptr + 44;
    /* Đăng ký driver */
    dev->driver = driver;
    /* Cấu hình output */
    dev->driver->config(dev->driver, dev->num_channel, dev->sample_rate, dev->bit_per_sample);
}

bool FUNC_ON_FLASH audio_get_next_data(audio_gen_wav_t *dev) {
    uint32_t max_sample = (((dev->file_ptr + 44) + dev->file_size) - dev->read_curr_ptr) / (dev->num_channel * (dev->bit_per_sample / 8));
    if(max_sample > 256) max_sample = 256;
    else if(max_sample == 0) return false;

    /* Lấy data sample từ buffer, mỗi sample gồm dev->bit_per_sample (bit), mỗi kênh R/L gồm 2 Byte */
    for(uint16_t index_sample = 0; index_sample < max_sample; index_sample++) {
        /* Get left data */
        dev->last_sample[index_sample * 2] = (int16_t)dev->read_curr_ptr[0];
        /* Get right data */
        dev->last_sample[(index_sample * 2) + 1] = (int16_t)dev->read_curr_ptr[1];
        /* Tăng con trỏ dữ liệu */
        dev->read_curr_ptr += dev->num_channel * (dev->bit_per_sample / 8);
    }
    return true;
}

bool FUNC_ON_FLASH audio_gen_wav_is_running(audio_gen_wav_t *dev) {
    return dev->running;
}
void FUNC_ON_FLASH audio_gen_wav_loop(audio_gen_wav_t *dev) {
    if (dev->driver->consume_sample(dev->driver, dev->last_sample) == false) {
        dev->busy = true;
        return;
    }
    if(dev->busy == false) {
        if (audio_get_next_data(dev) == false) {
            BITS_LOG(__FILE__": End file\r\n");
            dev->running = false;
            dev->busy = false;
            return;
        }
    }
    dev->busy = false;
}
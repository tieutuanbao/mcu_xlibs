#include "audio_output_i2s_noDAC.h"
#include <string.h>


audio_output_stt_t i2s_drv_init(i2s_no_dac_t *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample) {
    dev->i2s_config = (i2s_config_t){
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate = sample_rate,
        .bits_per_sample = bit_per_sample,
        .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .dma_buf_count = 2,
        .dma_buf_len = 8
    };
    i2s_pin_config_t pin_config = {
        .bck_o_en = 0,
        .ws_o_en = 0,
        .data_out_en = 1,
        .data_in_en = 0
    };
    i2s_no_dac_setGain(dev, 1);
    i2s_dma_init(0, &dev->i2s_config, &pin_config);
}
/**
 * @brief Cấu hình Driver
 * 
 * @param dev 
 * @param num_channel 
 * @param sample_rate 
 * @param bit_per_sample 
 * @return 
 */
audio_output_stt_t i2s_drv_config(i2s_no_dac_t *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample) {
    i2s_set_rate(0, sample_rate, bit_per_sample);
    return audio_output_ok;
}

void i2s_no_dac_start(i2s_no_dac_t *dev){
    i2s_dma_start(0);
}
void i2s_no_dac_stop(i2s_no_dac_t *dev){
    i2s_dma_stop(0);
}

void i2s_no_dac_setGain(i2s_no_dac_t *dev, float fgain) {
    dev->gain = fgain * 64;
}
static inline void i2s_no_dac_deltasigma(i2s_no_dac_t *dev, int32_t *sample, uint32_t *delta_buff, uint16_t num_sample) {
    int32_t new_sample = 0;
    int32_t diffPerStep = 0;
    for(uint16_t index_sample = 0; index_sample < num_sample; index_sample++) {
        // BITS_LOG("Sample %d: %08X -- %08X, ", dev->index_sample, sample[index_sample * 2], sample[index_sample * 2 + 1]);
        /* Tính trung bình 2 giá trị LR */
        new_sample = ((sample[index_sample * 2]) + (sample[index_sample * 2 + 1])) >> 1;
        new_sample *= dev->gain;
        new_sample <<= 2;
        // printf("new %08X, ", new_sample);
        // How much the comparison signal changes each oversample step
        diffPerStep = (new_sample - dev->last_sample) >> 5;
        // Don't need last_sample anymore, store this one for next round
        dev->last_sample = new_sample;
        delta_buff[index_sample] = 0; // The bits we convert the sample into, MSB to go on the wire first
        for (uint8_t index_bit = 0; index_bit < 32; index_bit++) {
            delta_buff[index_sample] = delta_buff[index_sample] << 1;
            if (dev->cum_error < 0) {
                delta_buff[index_sample] |= 1ULL;
                dev->cum_error += 0x007FFF00 - new_sample;
            } else {
                // Bits[0] = 0 handled already by left shift
                dev->cum_error -= 0x007FFF00 + new_sample;
            }
            new_sample += diffPerStep; // Move the reference signal towards destination
        }
        // printf("dsbuff: %x\n", delta_buff[index_sample]);
        // dev->index_sample++;
    }
}

audio_output_stt_t i2s_no_dac_consume_sample(i2s_no_dac_t *dev, int32_t *sample, uint16_t num_sample) {
    uint32_t delta_buff[num_sample];
    if((sample == 0) || (num_sample == 0)) {
        BITS_LOGE("Sample buffer error!!\r\n");
        return audio_output_sample_err;
    }
    i2s_no_dac_deltasigma(dev, sample, delta_buff, num_sample);
    i2s_write_buffer((int16_t *)delta_buff, num_sample);
    return audio_output_ok;
}

/**
 * @brief Khởi tạo Driver
 * 
 * @param dev 
 * @return audio_output_stt_t 
 */
audio_output_stt_t i2s_no_dac_init(i2s_no_dac_t *dev) {
    dev->last_sample = 0;
    dev->cum_error = 0;
    dev->this.init = (driver_init_t)i2s_drv_init;
    dev->this.config = (driver_config_t)i2s_drv_config;
    dev->this.consume = (consume_sample_t)i2s_no_dac_consume_sample;
    dev->this.start = (output_ctrl_t)i2s_no_dac_start;
    dev->this.stop = (output_ctrl_t)i2s_no_dac_stop;
    return audio_output_ok;
}
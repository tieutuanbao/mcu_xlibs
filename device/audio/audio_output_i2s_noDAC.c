#include "audio_output_i2s_noDAC.h"
#include <string.h>


audio_output_stt_t FUNC_ON_FLASH i2s_no_dac_init(i2s_no_dac_t *dev) {
    dev->last_sample = 0;
    dev->cum_error = 0;
    dev->index_sample = 0;
    dev->this.config = (driver_config_t)i2s_no_dac_config;
    dev->this.consume = (consume_sample_t)i2s_no_dac_consume_sample;
    return audio_output_ok;
}

FUNC_ON_FLASH audio_output_stt_t i2s_no_dac_config(i2s_no_dac_t *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample) {
    os_printf("config: %d, %d, %d\n", num_channel, sample_rate, bit_per_sample);

    dev->i2s_config = (i2s_config_t){
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate = sample_rate,
        .bits_per_sample = bit_per_sample,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
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
    i2s_dma_init(0, &dev->i2s_config, &pin_config);
    i2s_dma_start(0);
    // i2s_driver_install(0, &dev->i2s_config, 0, NULL);
    // i2s_set_pin(0, &pin_config);
    BITS_LOG("Config I2S OK!\r\n");
    return audio_output_ok;
}

FUNC_ON_FLASH int16_t i2s_no_dac_amplify(int32_t s) {
    int32_t v = (s * 64) >> 6;
    if (v < -32767) return -32767;
    else if (v > 32767) return 32767;
    else return (int16_t)(v & 0xffff);
}

FUNC_ON_FLASH void i2s_no_dac_deltasigma(i2s_no_dac_t *dev, int16_t *sample, uint32_t *delta_buff, uint16_t num_sample) {
    int32_t sum;
    int32_t new_sample;
    int32_t diffPerStep;
    uint32_t bits = 0;
    for(uint16_t index_sample = 0; index_sample < num_sample; index_sample++) {
        // Tính trung bình 2 giá trị LR
        sum = (((int32_t)sample[index_sample * 2]) + ((int32_t)sample[index_sample * 2 + 1])) >> 1;
        BITS_LOG("Sample %d: %d -- %d, ", dev->index_sample, sample[index_sample * 2], sample[index_sample * 2 + 1]);
        new_sample = ( (int32_t)i2s_no_dac_amplify(sum) ) << 8;
        printf("New samp: %d, ", new_sample);
        // How much the comparison signal changes each oversample step
        diffPerStep = (new_sample - dev->last_sample) >> 5;
        // Don't need last_sample anymore, store this one for next round
        dev->last_sample = new_sample;
        bits = 0; // The bits we convert the sample into, MSB to go on the wire first
        for (uint8_t index_bit = 32; index_bit > 0; index_bit--) {
            bits = bits << 1;
            if (dev->cum_error < 0) {
                bits |= 1;
                dev->cum_error += 0x007fff00 - new_sample;
            } else {
                // Bits[0] = 0 handled already by left shift
                dev->cum_error -= 0x007fff00 + new_sample;
            }
            new_sample += diffPerStep; // Move the reference signal towards destination
        }
        delta_buff[index_sample] = bits;
        printf("dsbuff: %x\n", delta_buff[index_sample]);
        dev->index_sample++;
    }
}

FUNC_ON_FLASH void i2s_make_sample_stereo16(i2s_no_dac_t *dev, int16_t *sample){
    if (dev->i2s_config.channel_format >= I2S_CHANNEL_FMT_ONLY_RIGHT){
        sample[1] = sample[0];
    }
    if (dev->i2s_config.bits_per_sample == I2S_BITS_PER_SAMPLE_8BIT) {
        sample[0] = (((int16_t)(sample[0]&0xff)) - 128) << 8;
        sample[1] = (((int16_t)(sample[1]&0xff)) - 128) << 8;
    }

}

FUNC_ON_FLASH audio_output_stt_t i2s_no_dac_consume_sample(i2s_no_dac_t *dev, int16_t *sample, uint16_t num_sample) {
    uint32_t delta_buff[num_sample * 2];
    int16_t temp_sample[num_sample * 2];

    if(sample == ((void *)0)){
        BITS_LOGE("Sample buffer error!!\r\n");
        return audio_output_sample_err;
    }
    for(uint16_t index_sample = 0; index_sample < num_sample; index_sample++) {
        BITS_LOG("Pre sample: %d --- %d\r\n", sample[index_sample], sample[index_sample * 2 + 1]);
        if(dev->i2s_config.bits_per_sample == I2S_BITS_PER_SAMPLE_8BIT){
            temp_sample[index_sample * 2] = (sample[index_sample * 2] - 128);
            temp_sample[index_sample * 2 + 1] = (sample[index_sample * 2 + 1] - 128);
        }
        else if(dev->i2s_config.bits_per_sample == I2S_BITS_PER_SAMPLE_16BIT){
            temp_sample[index_sample * 2] = (sample[index_sample * 2] - 32768) << 16;
            temp_sample[index_sample * 2 + 1] = (sample[index_sample * 2 + 1] - 32768) << 16;
        }
    }

    i2s_no_dac_deltasigma(dev, sample, delta_buff, num_sample);

    i2s_write_buffer(delta_buff, num_sample);
    BITS_LOG("I2s Byte Writen: %d!!\r\n", dev->byte_written);
    return true;
}

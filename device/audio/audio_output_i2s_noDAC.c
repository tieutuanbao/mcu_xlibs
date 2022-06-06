#include "audio_output_i2s_noDAC.h"
#include <string.h>

void FUNC_ON_FLASH i2s_no_dac_init(i2s_no_dac_t *dev) {
    i2s_begin();
    dev->last_sample = 0;
    dev->cum_error = 0;
    dev->index_sample = 0;
    dev->instead.config = (void (*)(void *, uint8_t, uint32_t, uint8_t))i2s_no_dac_config;
}

void FUNC_ON_FLASH i2s_no_dac_config(i2s_no_dac_t *dev, uint8_t num_channel, uint32_t sample_rate, uint8_t bit_per_sample) {
    os_printf("config: %d, %d, %d\n", num_channel, sample_rate, bit_per_sample);

    dev->i2s_config = (i2s_config_t){
        .number_channel = num_channel,
        // .mode = I2S_MODE_MASTER | I2S_MODE_TX,                                  // Only TX
        .sample_rate = sample_rate,
        .bits_per_sample = bit_per_sample,
        // .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,                           // 2-channels
        // .communication_format = I2S_COMM_FORMAT_I2S,
        // .dma_buf_count = 2,
        // .dma_buf_len = 8
    };
    // i2s_pin_config_t pin_config = {
    //     .bck_o_en = 0,
    //     .ws_o_en = 0,
    //     .data_out_en = 1,
    //     .data_in_en = 0
    // };
    i2s_set_bits(bit_per_sample);
    i2s_set_rate(sample_rate);

    // i2s_driver_install(0, &dev->i2s_config, 0, NULL);
    // i2s_set_pin(0, &pin_config);

    dev->instead.consume_sample = (bool (*)(void *, int16_t *))i2s_no_dac_consume_sample;
}

int16_t FUNC_ON_FLASH i2s_no_dac_amplify(int32_t s) {
    int32_t v = (s * 64) >> 6;
    if (v < -32767) return -32767;
    else if (v > 32767) return 32767;
    else return (int16_t)(v & 0xffff);
}

void FUNC_ON_FLASH i2s_no_dac_deltasigma(i2s_no_dac_t *dev, int16_t *sample, uint32_t *delta_buff) {
    int32_t sum;
    int32_t new_sample;
    int32_t diffPerStep;
    uint32_t bits = 0;
    for(uint16_t index_sample = 0; index_sample < SLC_BUF_LEN; index_sample++) {
        // Not shift 8 because addition takes care of one mult x 2
        sum = (((int32_t)sample[index_sample * 2]) + ((int32_t)sample[index_sample * 2 + 1])) >> 1;
        // os_printf("sample %d: %x -- %x, ", dev->index_sample, sample[index_sample * 2], sample[index_sample * 2 + 1]);
        new_sample = ( (int32_t)i2s_no_dac_amplify(sum) ) << 8;
        // printf("new samp: %d, ", new_sample);
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
        // os_printf("dsbuff: %x\n", delta_buff[index_sample]);
        dev->index_sample++;
    }
}

void FUNC_ON_FLASH i2s_make_sample_stereo16(i2s_no_dac_t *dev, int16_t *sample){
    // Mono to "stereo" conversion
    if (dev->i2s_config.number_channel == 1){
        sample[1] = sample[0];
    }
    if (dev->i2s_config.bits_per_sample == 8) {
        // Upsample from unsigned 8 bits to signed 16 bits
        sample[0] = (((int16_t)(sample[0]&0xff)) - 128) << 8;
        sample[1] = (((int16_t)(sample[1]&0xff)) - 128) << 8;
    }

}

bool FUNC_ON_FLASH i2s_no_dac_consume_sample(i2s_no_dac_t *dev, int16_t *sample) {
    uint32_t delta_buff[SLC_BUF_LEN];

    for(uint16_t index_sample = 0; index_sample < SLC_BUF_LEN; index_sample++) {
        i2s_make_sample_stereo16(dev, (sample + index_sample * 2));
    }

    i2s_no_dac_deltasigma(dev, sample, delta_buff);

    if (i2s_write_buffer((const int16_t *)delta_buff, SLC_BUF_LEN) == 0){
        os_printf("false write\n");
        return false;
    }
    return true;
}

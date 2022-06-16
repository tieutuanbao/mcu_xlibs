/**
 * @file esp8266_I2S->c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "esp8266_i2s.h"
#include "esp8266_iomux.h"
#include "esp8266_sdk_function.h"
#include "esp8266_interrupt.h"
#include <math.h>

#define TAG     "I2S: "

#define I2S_BASE_CLK                        (2 * APB_CLK_FREQ)
#define I2S_ENTER_CRITICAL()                disable_all_interrupts()
#define I2S_EXIT_CRITICAL()                 allow_interrupts()

#define i2c_writeReg_Mask(block, host_id, reg_add, Msb, Lsb, indata) \
        rom_i2c_writeReg_Mask(block, host_id, reg_add, Msb, Lsb, indata)

#define i2c_writeReg_Mask_def(block, reg_add, indata) \
        i2c_writeReg_Mask(block, block##_hostid,  reg_add,  reg_add##_msb, reg_add##_lsb,  indata)


i2s_t *I2S[I2S_NUM_MAX] = {I2S0};

i2s_bits_per_sample_t past_bits = 0;
int past_rate = 0;

/**
 * @brief Hàm khởi tạo I2S
 * 
 * @param clock_div Tần số I2S
 * @param pins Cách chân dùng cho I2S
 */
ICACHE_FLASH_ATTR void i2s_init(i2s_port_t i2s_num, i2s_config_t *i2s_config, i2s_pin_config_t *pins) {
    i2s_config_io(i2s_num, pins);
    /* enable clock to i2s subsystem */
    i2c_writeReg_Mask_def(i2c_bbpll, i2c_bbpll_en_audio_clock_out, 1);

    /* Clear all interrupt */
    I2S[i2s_num]->int_clr.val = I2S_INT_CLEAR_MASK;
    /* Disable all interrupt I2S */
    I2S[i2s_num]->int_ena.val = 0;
    
    /* reset I2S subsystem */
    I2S[i2s_num]->conf.val &= ~0x0F;
    I2S[i2s_num]->conf.val |= 0x0F;
    I2S[i2s_num]->conf.val &= ~0x0F;

    /* select 16bits per channel (FIFO_MOD=0), no DMA access (FIFO only) */
    I2S[i2s_num]->fifo_conf.dscr_en = 0;
    I2S[i2s_num]->fifo_conf.tx_fifo_mod = 0;
    I2S[i2s_num]->fifo_conf.rx_fifo_mod = 0;

    if(i2s_config->bits_per_sample == 24) {
        I2S[i2s_num]->fifo_conf.tx_fifo_mod = 2;
        I2S[i2s_num]->fifo_conf.rx_fifo_mod = 2;
    }

    /* Dual channel mode */
    I2S[i2s_num]->conf_chan.tx_chan_mod = 0;
    I2S[i2s_num]->conf_chan.rx_chan_mod = 0;

    i2s_set_rate(i2s_num, i2s_config->sample_rate, i2s_config->bits_per_sample);
    // i2s_set_channel(i2s_num, i2s_config->channel_format, i2s_config->bits_per_sample);

    I2S[i2s_num]->conf.tx_start = 1;
    I2S[i2s_num]->conf.tx_reset = 0;
    // I2S[i2s_num]->conf.tx_reset = 1;
}

/**
 * @brief Tính bộ chia dựa vào clock I2S mong muốn
 * Sử dụng hàm này tính toán bộ chia clock I2S để đưa vào i2s_init
 * 
 * @param freq Tần số bộ I2S mong muốn
 * @return i2s_clock_div_t 
 */
ICACHE_FLASH_ATTR uint32_t abs(int32_t x){
    if(x < 0) return 0 - x;
    return x;
}
ICACHE_FLASH_ATTR i2s_clock_div_t i2s_freq_to_clock_div(int32_t freq) {
    i2s_clock_div_t div = {0, 0};
    int32_t best_freq = 0;
    int32_t curr_freq = 0;
    for (uint32_t bclk_div = 1; bclk_div < 64; bclk_div++) {
        for (uint32_t clkm_div = 1; clkm_div < 64; clkm_div++) {
            curr_freq = ets_get_cpu_frequency() / (bclk_div * clkm_div);
            if (abs(freq - curr_freq) < abs(freq - best_freq)) {
                best_freq = curr_freq;
                div.clkm_div = clkm_div;
                div.bclk_div = bclk_div;
            }
        }
    }

    BITS_LOG("Requested frequency: %d, set frequency: %d\n", freq, best_freq);
    BITS_LOG("clkm_div: %d, bclk_div: %d\n", div.clkm_div, div.bclk_div);

    return div;
}
ICACHE_FLASH_ATTR void i2s_config_io(i2s_port_t i2s_num, i2s_pin_config_t *pins) {
    if (pins->data_out_en) {
        iomux_set_function(gpio_2_iomux[3], IOMUX_GPIO3_FUNC_I2SO_DATA);
    }
    if (pins->bck_o_en) {
        iomux_set_function(gpio_2_iomux[15], IOMUX_GPIO15_FUNC_I2SO_BCK);
    }
    if (pins->ws_o_en) {
        iomux_set_function(gpio_2_iomux[2], IOMUX_GPIO2_FUNC_I2SO_WS);
    }
    if (pins->data_in_en) {
        iomux_set_function(gpio_2_iomux[12], IOMUX_GPIO12_FUNC_I2SI_DATA);
    }
    if (pins->bck_i_en) {
        iomux_set_function(gpio_2_iomux[13], IOMUX_GPIO13_FUNC_I2SI_BCK);
    }
    if (pins->ws_i_en) {
        iomux_set_function(gpio_2_iomux[14], IOMUX_GPIO14_FUNC_I2SI_WS);
    }
    BITS_LOGD(TAG "pin config: do=%d bck_o=%d ws_o=%d di=%d bck_i=%d ws_i=%d\r\n", pins->data_out_en, pins->bck_o_en, pins->ws_o_en, pins->data_in_en, pins->bck_i_en, pins->ws_i_en);
}

/**
 * @brief Cấu hình sample rate I2S, phải dừng I2S trước khi chạy func này
 * 
 * @param i2s_num i2s port
 * @param rate sample rate
 * @return void 
 */
ICACHE_FLASH_ATTR void i2s_set_rate(i2s_port_t i2s_num, uint32_t rate, uint8_t bits_per_samp) {
    uint8_t bck_div = 1;
    uint8_t mclk_div = 1;
    uint32_t scaled_base_freq = I2S_BASE_CLK / (bits_per_samp * 2);
    float delta_best = scaled_base_freq;

    for (uint8_t i = 1; i < 64; i++) {
        for (uint8_t j = i; j < 64; j++) {
            float new_delta = abs(((float)scaled_base_freq / i / j) - rate);

            if (new_delta < delta_best) {
                delta_best = new_delta;
                bck_div = i;
                mclk_div = j;
            }
        }
    }

    I2S_ENTER_CRITICAL();
    i2s_set_dividers(i2s_num, bck_div, mclk_div);
    I2S_EXIT_CRITICAL();
}

/**
 * @brief Cấu hình bộ chia clock I2S
 * 
 * @param i2s_num số port I2S
 * @param bck_div 
 * @param mclk_div 
 * @return ICACHE_FLASH_ATTR 
 */
ICACHE_FLASH_ATTR void i2s_set_dividers(i2s_port_t i2s_num, uint8_t bck_div, uint8_t mclk_div) {
    /* Kích thước divx không lớn hơn 0x3F */
    bck_div &= 0x3F;
    mclk_div &= 0x3F;

    /* Giữ trạng thái reset của Tx */
    I2S[i2s_num]->conf.tx_reset = 1;
    /* Trans_master (active low) */
    I2S[i2s_num]->conf.tx_slave_mod = 0;
    /* Recv_master (active low) */ 
    I2S[i2s_num]->conf.rx_slave_mod = 0;
    /* bits_mod (16bit / channel) */
    I2S[i2s_num]->conf.bits_mod = 0;
    /* clear clock div */
    I2S[i2s_num]->conf.bck_div_num = 0;
    I2S[i2s_num]->conf.clkm_div_num = 0;

    /* Send or recv right channel first */
    I2S[i2s_num]->conf.right_first = 1;
    /* MSB recv or transmit first */
    I2S[i2s_num]->conf.msb_right = 1;
    /* 1-bit delay from ws to MSB (I2S format) */
    I2S[i2s_num]->conf.rx_msb_shift = 1;
    I2S[i2s_num]->conf.tx_msb_shift = 1;
    /* Set div clock */
    I2S[i2s_num]->conf.bck_div_num = bck_div;
    I2S[i2s_num]->conf.clkm_div_num = mclk_div;
    /* Thoát reset */
    I2S[i2s_num]->conf.tx_reset = 0;
}
/**
 * @brief Cấu hình sample rate I2S, phải dừng I2S trước khi chạy func này
 * 
 * @param rate sample rate
 * @return void 
 */
ICACHE_FLASH_ATTR void i2s_set_channel(i2s_port_t i2s_num, i2s_channel_fmt_t ch_fmt, i2s_bits_per_sample_t bits) {    
    uint8_t ch = (ch_fmt < I2S_CHANNEL_FMT_ONLY_RIGHT)? I2S_CHANNEL_STEREO : I2S_CHANNEL_MONO;

    switch (bits) {
        case 8:{
            I2S[i2s_num]->fifo_conf.tx_fifo_mod = 0;
            I2S[i2s_num]->fifo_conf.rx_fifo_mod = 0;
            break;
        }
        case 16:{
            I2S[i2s_num]->fifo_conf.tx_fifo_mod = 2;
            I2S[i2s_num]->fifo_conf.rx_fifo_mod = 2;
            break;
        }
        case 24:{
            I2S[i2s_num]->fifo_conf.tx_fifo_mod = 4;
            I2S[i2s_num]->fifo_conf.rx_fifo_mod = 4;
            break;
        }
    }
    I2S[i2s_num]->conf.bits_mod = bits;

    if((ch == 2)) {
        I2S[i2s_num]->fifo_conf.tx_fifo_mod &= ~1;
        I2S[i2s_num]->fifo_conf.rx_fifo_mod &= ~1;
        I2S[i2s_num]->conf_chan.tx_chan_mod &= ~1;
        I2S[i2s_num]->conf_chan.rx_chan_mod &= ~1;
    }
    else {
        I2S[i2s_num]->fifo_conf.tx_fifo_mod |= 1;
        I2S[i2s_num]->fifo_conf.rx_fifo_mod |= 1;
        I2S[i2s_num]->conf_chan.tx_chan_mod |= 1;
        I2S[i2s_num]->conf_chan.rx_chan_mod |= 1;
    }
}

/**
 * @brief Bắt đầu truyền I2S
 * 
 */
ICACHE_FLASH_ATTR void i2s_start(i2s_port_t i2s_num) {
    /* enable DMA in i2s subsystem */
    I2S[i2s_num]->fifo_conf.val |= I2S_FIFO_CONF_DESCRIPTOR_ENABLE;
    /* Start transmission */
    I2S[i2s_num]->conf.val |= I2S_CONF_TX_START;
}

/**
 * @brief Dừng truyền I2S
 * 
 */
ICACHE_FLASH_ATTR void i2s_stop(i2s_port_t i2s_num) {
    I2S[i2s_num]->fifo_conf.val &= ~I2S_FIFO_CONF_DESCRIPTOR_ENABLE;
}

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

    I2S[i2s_num]->int_clr.val = I2S_INT_CLEAR_MASK;
    I2S[i2s_num]->int_ena.val = 0;
    
    /* reset I2S subsystem */
    I2S[i2s_num]->conf.val &= ~I2S_CONF_RESET_MASK;
    I2S[i2s_num]->conf.val |= I2S_CONF_RESET_MASK;
    I2S[i2s_num]->conf.val &= ~I2S_CONF_RESET_MASK;

    /* select 16bits per channel (FIFO_MOD=0), no DMA access (FIFO only) */
    I2S[i2s_num]->fifo_conf.val &= ~I2S_FIFO_CONF_DESCRIPTOR_ENABLE;
    I2S[i2s_num]->fifo_conf.val &= ~I2S_FIFO_CONF_RX_FIFO_MOD_MASK;
    I2S[i2s_num]->fifo_conf.val &= ~I2S_FIFO_CONF_TX_FIFO_MOD_MASK;

    /* Set Channel = 0 */
    I2S[i2s_num]->conf_chan.val &= ~(I2S_CONF_CHANNELS_RX_CHANNEL_MOD_MASK | I2S_CONF_CHANNELS_TX_CHANNEL_MOD_MASK);

    /* trans master and receiv slave, MSB shift, right_first, msb right */
    I2S[i2s_num]->conf.val &= ~I2S_CONF_TX_SLAVE_MOD;
    I2S[i2s_num]->conf.val &= ~I2S_CONF_BITS_MOD_MASK;
    I2S[i2s_num]->conf.val &= ~I2S_CONF_BCK_DIV_MASK;
    I2S[i2s_num]->conf.val &= ~I2S_CONF_CLKM_DIV_MASK;

    I2S[i2s_num]->conf.val |= I2S_CONF_RIGHT_FIRST | I2S_CONF_MSB_RIGHT | I2S_CONF_RX_SLAVE_MOD | I2S_CONF_RX_MSB_SHIFT | I2S_CONF_TX_MSB_SHIFT;
    i2s_set_rate(i2s_num, i2s_config->sample_rate);
    i2s_set_channel(i2s_num, i2s_config->channel_format, i2s_config->bits_per_sample);
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
ICACHE_FLASH_ATTR void i2s_set_rate(i2s_port_t i2s_num, uint32_t rate) {
    uint8_t bck_div = 1;
    uint8_t mclk_div = 1;

    uint32_t scaled_base_freq = I2S_BASE_CLK / (16 * 2);
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
    I2S[i2s_num]->conf.bck_div_num = bck_div & 0x3F;
    I2S[i2s_num]->conf.clkm_div_num = mclk_div & 0x3F;
    I2S_EXIT_CRITICAL();
}

/**
 * @brief Cấu hình sample rate I2S, phải dừng I2S trước khi chạy func này
 * 
 * @param rate sample rate
 * @return void 
 */
ICACHE_FLASH_ATTR void i2s_set_channel(i2s_port_t i2s_num, i2s_channel_fmt_t ch_fmt, i2s_bits_per_sample_t bits) {
    uint32_t cur_mode = I2S[0]->fifo_conf.tx_fifo_mod;
    
    uint8_t ch = (ch_fmt < I2S_CHANNEL_FMT_ONLY_RIGHT)? I2S_CHANNEL_STEREO : I2S_CHANNEL_MONO;

    I2S[i2s_num]->fifo_conf.tx_fifo_mod = (ch == 2) ? cur_mode - 1 : cur_mode + 1;
    cur_mode = I2S[i2s_num]->fifo_conf.rx_fifo_mod;
    I2S[i2s_num]->fifo_conf.rx_fifo_mod = (ch == 2) ? cur_mode - 1  : cur_mode + 1;
    I2S[i2s_num]->conf_chan.tx_chan_mod = (ch == 2) ? 0 : 1;
    I2S[i2s_num]->conf_chan.rx_chan_mod = (ch == 2) ? 0 : 1;

    if ((past_bits <= 16) && (bits > 16)) {
        I2S[i2s_num]->fifo_conf.tx_fifo_mod += 2;
        I2S[i2s_num]->fifo_conf.rx_fifo_mod += 2;
    } else if (past_bits > 16 && bits <= 16) {
        I2S[i2s_num]->fifo_conf.tx_fifo_mod -= 2;
        I2S[i2s_num]->fifo_conf.rx_fifo_mod -= 2;
    }
    past_bits = bits;
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

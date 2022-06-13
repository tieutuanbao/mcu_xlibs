/**
 * @file esp8266_i2s.c
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
#include <math.h>

#define i2c_writeReg_Mask(block, host_id, reg_add, Msb, Lsb, indata) \
        rom_i2c_writeReg_Mask(block, host_id, reg_add, Msb, Lsb, indata)

#define i2c_writeReg_Mask_def(block, reg_add, indata) \
        i2c_writeReg_Mask(block, block##_hostid,  reg_add,  reg_add##_msb, reg_add##_lsb,  indata)

/**
 * @brief Hàm khởi tạo I2S
 * 
 * @param clock_div Tần số I2S
 * @param pins Cách chân dùng cho I2S
 */
FUNC_ON_FLASH void i2s_init(i2s_clock_div_t clock_div, i2s_pins_t pins) {
    if (pins.data) {
        iomux_set_function(gpio_2_iomux[3], IOMUX_GPIO3_FUNC_I2SO_DATA);
        iomux_set_direction_flags(gpio_2_iomux[3], IOMUX_PIN_OUTPUT_ENABLE);
    }
    if (pins.clock) {
        iomux_set_function(gpio_2_iomux[15], IOMUX_GPIO15_FUNC_I2SO_BCK);
    }
    if (pins.ws) {
        iomux_set_function(gpio_2_iomux[2], IOMUX_GPIO2_FUNC_I2SO_WS);
    }
    BITS_LOG("Pin config: data=%d clock=%d ws=%d\r\n", pins.data, pins.clock, pins.ws);

    /* enable clock to i2s subsystem */
    i2c_writeReg_Mask_def(i2c_bbpll, i2c_bbpll_en_audio_clock_out, 1);

    I2S.int_clear = I2S_INT_CLEAR_MASK;
    I2S.int_enable = 0;
    
    /* reset I2S subsystem */
    I2S.conf &= ~I2S_CONF_RESET_MASK;
    I2S.conf |= I2S_CONF_RESET_MASK;
    I2S.conf &= ~I2S_CONF_RESET_MASK;

    /* select 16bits per channel (FIFO_MOD=0), no DMA access (FIFO only) */
    I2S.fifo_conf &= ~I2S_FIFO_CONF_DESCRIPTOR_ENABLE;
    I2S.fifo_conf &= ~I2S_FIFO_CONF_RX_FIFO_MOD_MASK;
    I2S.fifo_conf &= ~I2S_FIFO_CONF_TX_FIFO_MOD_MASK;

    /* Set Channel = 0 */
    I2S.conf_channels &= ~(I2S_CONF_CHANNELS_RX_CHANNEL_MOD_MASK | I2S_CONF_CHANNELS_TX_CHANNEL_MOD_MASK);

    /* trans master and receiv slave, MSB shift, right_first, msb right */
    I2S.conf &= ~I2S_CONF_TX_SLAVE_MOD;
    I2S.conf &= ~I2S_CONF_BITS_MOD_MASK;
    I2S.conf &= ~I2S_CONF_BCK_DIV_MASK;
    I2S.conf &= ~I2S_CONF_CLKM_DIV_MASK;

    I2S.conf |= I2S_CONF_RIGHT_FIRST | I2S_CONF_MSB_RIGHT | I2S_CONF_RX_SLAVE_MOD | I2S_CONF_RX_MSB_SHIFT | I2S_CONF_TX_MSB_SHIFT;
    I2S.conf = (I2S.conf & (~I2S_CONF_BCK_DIV_MASK)) | (((uint32_t)clock_div.bclk_div) << I2S_CONF_BCK_DIV_POS);
    I2S.conf = (I2S.conf & (~I2S_CONF_CLKM_DIV_MASK)) | (((uint32_t)clock_div.clkm_div) << I2S_CONF_CLKM_DIV_POS);
}

/**
 * @brief Tính bộ chia dựa vào clock I2S mong muốn
 * Sử dụng hàm này tính toán bộ chia clock I2S để đưa vào i2s_init
 * 
 * @param freq Tần số bộ I2S mong muốn
 * @return i2s_clock_div_t 
 */
FUNC_ON_FLASH uint32_t abs(int32_t x){
    if(x < 0) return 0 - x;
    return x;
}
FUNC_ON_FLASH i2s_clock_div_t i2s_freq_to_clock_div(int32_t freq) {
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

    printf("Requested frequency: %d, set frequency: %d\n", freq, best_freq);
    printf("clkm_div: %d, bclk_div: %d\n", div.clkm_div, div.bclk_div);

    return div;
}

/**
 * @brief Bắt đầu truyền I2S
 * 
 */
FUNC_ON_FLASH void i2s_start(void) {
    // enable DMA in i2s subsystem
    I2S.fifo_conf |= I2S_FIFO_CONF_DESCRIPTOR_ENABLE;
    //Start transmission
    I2S.conf |= I2S_CONF_TX_START;
}

/**
 * @brief Dừng truyền I2S
 * 
 */
FUNC_ON_FLASH void i2s_stop(void) {
    I2S.fifo_conf &= ~I2S_FIFO_CONF_DESCRIPTOR_ENABLE;
}

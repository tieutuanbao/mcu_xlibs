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
#include "esp8266_gpio.h"
#include "esp8266_iomux.h"
#include "esp8266_interrupt.h"
#include <math.h>

#define TAG     "I2S: "

#define I2S_BASE_CLK                        (2 * APB_CLK_FREQ)
#define I2S_ENTER_CRITICAL()                disable_all_interrupts()
#define I2S_EXIT_CRITICAL()                 allow_interrupts()

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

    /* Reset FIFO */
    I2S(i2s_num)->conf.rx_fifo_reset = 1;
    I2S(i2s_num)->conf.rx_fifo_reset = 0;
    I2S(i2s_num)->conf.tx_fifo_reset = 1;
    I2S(i2s_num)->conf.tx_fifo_reset = 0;

    /* Clear all interrupt */
    I2S(i2s_num)->int_clr.val = 0xFFFFFFFF;
    I2S(i2s_num)->int_clr.val = 0;
    /* Disable all interrupt I2S */
    I2S(i2s_num)->int_ena.val = 0;
    
    /* reset I2S subsystem */
    I2S(i2s_num)->conf.val &= ~0x0F;
    I2S(i2s_num)->conf.val |= 0x0F;
    I2S(i2s_num)->conf.val &= ~0x0F;

    /* select 16bits per channel (FIFO_MOD=0), no DMA access (FIFO only) */
    I2S(i2s_num)->fifo_conf.dscr_en = 0;

    I2S(i2s_num)->conf_chan.tx_chan_mod = i2s_config->channel_format < I2S_CHANNEL_FMT_ONLY_RIGHT ? i2s_config->channel_format : (i2s_config->channel_format >> 1); // 0-two channel;1-right;2-left;3-righ;4-left
    I2S(i2s_num)->fifo_conf.tx_fifo_mod = i2s_config->channel_format < I2S_CHANNEL_FMT_ONLY_RIGHT ? 0 : 1; // 0-right&left channel;1-one channel

    I2S(i2s_num)->conf_chan.rx_chan_mod = i2s_config->channel_format < I2S_CHANNEL_FMT_ONLY_RIGHT ? i2s_config->channel_format : (i2s_config->channel_format >> 1); // 0-two channel;1-right;2-left;3-righ;4-left
    I2S(i2s_num)->fifo_conf.rx_fifo_mod = i2s_config->channel_format < I2S_CHANNEL_FMT_ONLY_RIGHT ? 0 : 1; // 0-right&left channel;1-one channel

    /* Connect DMA to FIFO */
    I2S(i2s_num)->fifo_conf.dscr_en = 1;

    I2S(i2s_num)->conf.tx_start = 0;
    I2S(i2s_num)->conf.rx_start = 0;

    I2S(i2s_num)->conf.msb_right = 1;
    I2S(i2s_num)->conf.right_first = 1;

    if (i2s_config->mode & I2S_MODE_TX) {
        I2S(i2s_num)->conf.tx_slave_mod = 0; // Master

        if (i2s_config->mode & I2S_MODE_SLAVE) {
            I2S(i2s_num)->conf.tx_slave_mod = 1;// TX Slave
        }
    }

    if (i2s_config->mode & I2S_MODE_RX) {
        I2S(i2s_num)->conf.rx_slave_mod = 0; // Master

        if (i2s_config->mode & I2S_MODE_SLAVE) {
            I2S(i2s_num)->conf.rx_slave_mod = 1;// RX Slave
        }
    }

    if (i2s_config->communication_format & I2S_COMM_FORMAT_I2S) {
        I2S(i2s_num)->conf.tx_msb_shift = 1;
        I2S(i2s_num)->conf.rx_msb_shift = 1;

        if (i2s_config->communication_format & I2S_COMM_FORMAT_I2S_LSB) {
            if (i2s_config->mode & I2S_MODE_TX) {
                I2S(i2s_num)->conf.tx_msb_shift = 0;
            }

            if (i2s_config->mode & I2S_MODE_RX) {
                I2S(i2s_num)->conf.rx_msb_shift = 0;
            }
        }
    }

    if(i2s_config->bits_per_sample == 24) {
        I2S(i2s_num)->fifo_conf.tx_fifo_mod = 2;
        I2S(i2s_num)->fifo_conf.rx_fifo_mod = 2;
    }

    /* Dual channel mode */
    I2S(i2s_num)->conf_chan.tx_chan_mod = 0;
    I2S(i2s_num)->conf_chan.rx_chan_mod = 0;

    i2s_set_rate(i2s_num, i2s_config->sample_rate, i2s_config->bits_per_sample);

    I2S(i2s_num)->conf.tx_start = 1;
    I2S(i2s_num)->conf.tx_reset = 0;
}

ICACHE_FLASH_ATTR void i2s_config_io(i2s_port_t i2s_num, i2s_pin_config_t *pins) {
    if (pins->data_out_en) {
        iomux_set_function(gpio_2_iomux[3], IOMUX_GPIO3_FUNC_I2SO_DATA);
    } else {
        GPIO->pin[3].driver = 0;
        GPIO->enable_out_set = 1 << 3;
        IOMUX->pin[gpio_2_iomux[3]].pullup = 0;
        IOMUX->pin[gpio_2_iomux[3]].func_low_bit = 3;
        IOMUX->pin[gpio_2_iomux[3]].func_high_bit = 0;
        GPIO->out_clear = (1 << 3);
    }
    if (pins->bck_o_en) {
        iomux_set_function(gpio_2_iomux[15], IOMUX_GPIO15_FUNC_I2SO_BCK);
    } else {
        iomux_set_function(gpio_2_iomux[15], IOMUX_GPIO15_FUNC_GPIO);
    }
    if (pins->ws_o_en) {
        iomux_set_function(gpio_2_iomux[2], IOMUX_GPIO2_FUNC_I2SO_WS);
    } else {
        iomux_set_function(gpio_2_iomux[2], IOMUX_GPIO2_FUNC_GPIO);
    }
    if (pins->data_in_en) {
        iomux_set_function(gpio_2_iomux[12], IOMUX_GPIO12_FUNC_I2SI_DATA);
    } else {
        iomux_set_function(gpio_2_iomux[12], IOMUX_GPIO3_FUNC_GPIO);
    }
    if (pins->bck_i_en) {
        iomux_set_function(gpio_2_iomux[13], IOMUX_GPIO13_FUNC_I2SI_BCK);
    } else {
        iomux_set_function(gpio_2_iomux[13], IOMUX_GPIO13_FUNC_GPIO);
    }
    if (pins->ws_i_en) {
        iomux_set_function(gpio_2_iomux[14], IOMUX_GPIO14_FUNC_I2SI_WS);
    } else {
        iomux_set_function(gpio_2_iomux[14], IOMUX_GPIO14_FUNC_GPIO);
    }
    // BITS_LOGD(TAG "pin config: do=%d bck_o=%d ws_o=%d di=%d bck_i=%d ws_i=%d\r\n", pins->data_out_en, pins->bck_o_en, pins->ws_o_en, pins->data_in_en, pins->bck_i_en, pins->ws_i_en);
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

    if(bits_per_samp == 8) bits_per_samp = 16;
    
    uint32_t scaled_base_freq = 160000000L / (bits_per_samp * 2);

    float delta_best = scaled_base_freq;

    for (uint8_t i = 1; i < 64; i++) {
        for (uint8_t j = i; j < 64; j++) {
            float new_delta = fabs(((float)scaled_base_freq / i / j) - rate);

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
    I2S(i2s_num)->conf.tx_reset = 1;
    /* Trans_master (active low) */
    I2S(i2s_num)->conf.tx_slave_mod = 0;
    /* Recv_master (active low) */ 
    I2S(i2s_num)->conf.rx_slave_mod = 0;
    /* bits_mod (16bit / channel) */
    I2S(i2s_num)->conf.bits_mod = 0;
    /* clear clock div */
    I2S(i2s_num)->conf.bck_div_num = 0;
    I2S(i2s_num)->conf.clkm_div_num = 0;

    /* Send or recv right channel first */
    I2S(i2s_num)->conf.right_first = 1;
    /* MSB recv or transmit first */
    I2S(i2s_num)->conf.msb_right = 1;
    /* 1-bit delay from ws to MSB (I2S format) */
    I2S(i2s_num)->conf.rx_msb_shift = 1;
    I2S(i2s_num)->conf.tx_msb_shift = 1;
    /* Set div clock */
    I2S(i2s_num)->conf.bck_div_num = bck_div;
    I2S(i2s_num)->conf.clkm_div_num = mclk_div;
    /* Thoát reset */
    I2S(i2s_num)->conf.tx_reset = 0;
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
            I2S(i2s_num)->fifo_conf.tx_fifo_mod = 0;
            I2S(i2s_num)->fifo_conf.rx_fifo_mod = 0;
            break;
        }
        case 16:{
            I2S(i2s_num)->fifo_conf.tx_fifo_mod = 2;
            I2S(i2s_num)->fifo_conf.rx_fifo_mod = 2;
            break;
        }
        case 24:{
            I2S(i2s_num)->fifo_conf.tx_fifo_mod = 4;
            I2S(i2s_num)->fifo_conf.rx_fifo_mod = 4;
            break;
        }
    }
    I2S(i2s_num)->conf.bits_mod = bits;

    I2S(i2s_num)->fifo_conf.tx_fifo_mod &= ~1;
    I2S(i2s_num)->fifo_conf.rx_fifo_mod &= ~1;
    if((ch == 2)) {
        I2S(i2s_num)->conf_chan.tx_chan_mod &= ~1;
        I2S(i2s_num)->conf_chan.rx_chan_mod &= ~1;
    }
    else {
        // I2S(i2s_num)->fifo_conf.tx_fifo_mod |= 1;
        // I2S(i2s_num)->fifo_conf.rx_fifo_mod |= 1;
        I2S(i2s_num)->conf_chan.tx_chan_mod |= 1;
        I2S(i2s_num)->conf_chan.rx_chan_mod |= 1;
    }
}

/**
 * @brief Bắt đầu truyền I2S
 * 
 */
ICACHE_FLASH_ATTR void i2s_start(i2s_port_t i2s_num) {
    /* enable DMA in i2s subsystem */
    I2S(i2s_num)->fifo_conf.dscr_en = 1;
    /* Start transmission */
    I2S(i2s_num)->conf.tx_start = 1;
    // BITS_LOGD("I2S: conf=%X int_clr=%X int_ena=%X fifo_conf=%X conf_chan=%X rx_eof_num=%X\r\n", I2S(i2s_num)->conf.val, I2S(i2s_num)->int_clr.val, I2S(i2s_num)->int_ena.val, I2S(i2s_num)->fifo_conf.val, I2S(i2s_num)->conf_chan.val, I2S(i2s_num)->rx_eof_num);
}

/**
 * @brief Dừng truyền I2S
 * 
 */
ICACHE_FLASH_ATTR void i2s_stop(i2s_port_t i2s_num) {
    I2S(i2s_num)->conf.val &= ~I2S_CONF_RESET_MASK;
    I2S(i2s_num)->conf.val |= ~I2S_CONF_RESET_MASK;
    I2S(i2s_num)->conf.val &= ~I2S_CONF_RESET_MASK;

    I2S(i2s_num)->fifo_conf.val &= ~I2S_FIFO_CONF_DESCRIPTOR_ENABLE;
    i2s_pin_config_t pin_cfg = {0, 0, 0, 0, 0, 0};
    i2s_config_io(0, &pin_cfg);
}

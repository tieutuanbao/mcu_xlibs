/**
 * @file esp8266_i2s.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ESP8266_I2S_REGS_H
#define __ESP8266_I2S_REGS_H

#include "esp8266_regs.h"
#include "common_macros.h"
#include "c_types.h"


#define I2S     (*(i2s_t *)I2S_BASE)

/**
 * @brief Cấu trúc thanh ghi I2S ESP8266
 * 
 */
typedef struct struct_i2s {
    volatile uint32_t txfifo;           // 0x00
    volatile uint32_t rxfifo;           // 0x04
    volatile uint32_t conf;             // 0x08
    volatile uint32_t int_raw;          // 0x0c
    volatile uint32_t int_status;       // 0x10
    volatile uint32_t int_enable;       // 0x14
    volatile uint32_t int_clear;        // 0x18
    volatile uint32_t timing;           // 0x1c
    volatile uint32_t fifo_conf;        // 0x20
    volatile uint32_t rx_eof_num;       // 0x24
    volatile uint32_t conf_single_data; // 0x28
    volatile uint32_t conf_channels;    // 0x2c
} i2s_t;

typedef struct {
    uint8_t bclk_div;
    uint8_t clkm_div;
} i2s_clock_div_t;

typedef struct {
    bool data;
    bool clock;
    bool ws;
} i2s_pins_t;

#ifndef i2c_bbpll
    #define i2c_bbpll                               0x67
    #define i2c_bbpll_en_audio_clock_out            4
    #define i2c_bbpll_en_audio_clock_out_msb        7
    #define i2c_bbpll_en_audio_clock_out_lsb        7
    #define i2c_bbpll_hostid                        4
#endif

/* Details for CONF register */
#define I2S_CONF_BCK_DIV_POS                        22
#define I2S_CONF_BCK_DIV_MASK                       (0x0000003F << I2S_CONF_BCK_DIV_POS)
#define I2S_CONF_CLKM_DIV_POS                       16
#define I2S_CONF_CLKM_DIV_MASK                      (0x0000003F << I2S_CONF_CLKM_DIV_POS)
#define I2S_CONF_BITS_MOD_POS                       12
#define I2S_CONF_BITS_MOD_MASK                      (0x0000000F << I2S_CONF_BITS_MOD_POS)
#define I2S_CONF_RX_MSB_SHIFT                       (1U << 11)
#define I2S_CONF_TX_MSB_SHIFT                       (1U << 10)
#define I2S_CONF_RX_START                           (1U << 9)
#define I2S_CONF_TX_START                           (1U << 8)
#define I2S_CONF_MSB_RIGHT                          (1U << 7)
#define I2S_CONF_RIGHT_FIRST                        (1U << 6)
#define I2S_CONF_RX_SLAVE_MOD                       (1U << 5)
#define I2S_CONF_TX_SLAVE_MOD                       (1U << 4)
#define I2S_CONF_RX_FIFO_RESET                      (1U << 3)
#define I2S_CONF_TX_FIFO_RESET                      (1U << 2)
#define I2S_CONF_RX_RESET                           (1U << 1)
#define I2S_CONF_TX_RESET                           (1U << 0)
#define I2S_CONF_RESET_POS                          0
#define I2S_CONF_RESET_MASK                         (0x0000000F << I2S_CONF_RESET_POS)

/* Details for INT_RAW register */
#define I2S_INT_RAW_TX_REMPTY    (1U << 5)
#define I2S_INT_RAW_TX_WFULL     (1U << 4)
#define I2S_INT_RAW_RX_REMPTY    (1U << 3)
#define I2S_INT_RAW_RX_WFULL     (1U << 2)
#define I2S_INT_RAW_TX_PUT_DATA  (1U << 1)
#define I2S_INT_RAW_RX_TAKE_DATA (1U << 0)

/* Details for INT_STATUS register */
#define I2S_INT_STATUS_TX_REMPTY     (1U << 5)
#define I2S_INT_STATUS_TX_WFULL      (1U << 4)
#define I2S_INT_STATUS_RX_REMPTY     (1U << 3)
#define I2S_INT_STATUS_RX_WFULL      (1U << 2)
#define I2S_INT_STATUS_TX_PUT_DATA   (1U << 1)
#define I2S_INT_STATUS_RX_TAKE_DATA  (1U << 0)

/* Details for INT_ENABLE register */
#define I2S_INT_ENABLE_TX_REMPTY     (1U << 5)
#define I2S_INT_ENABLE_TX_WFULL      (1U << 4)
#define I2S_INT_ENABLE_RX_REMPTY     (1U << 3)
#define I2S_INT_ENABLE_RX_WFULL      (1U << 2)
#define I2S_INT_ENABLE_TX_PUT_DATA   (1U << 1)
#define I2S_INT_ENABLE_RX_TAKE_DATA  (1U << 0)

/* Details for INT_CLEAR register */
#define I2S_INT_CLEAR_MASK          0x3F
#define I2S_INT_CLEAR_TX_REMPTY     (1U << 5)
#define I2S_INT_CLEAR_TX_WFULL      (1U << 4)
#define I2S_INT_CLEAR_RX_REMPTY     (1U << 3)
#define I2S_INT_CLEAR_RX_WFULL      (1U << 2)
#define I2S_INT_CLEAR_TX_PUT_DATA   (1U << 1)
#define I2S_INT_CLEAR_RX_TAKE_DATA  (1U << 0)

/* Details for TIMING register */
#define I2S_TIMING_TX_BCK_IN_INV       (1U << 22)
#define I2S_TIMING_RX_DSYNC_SW         (1U << 21)
#define I2S_TIMING_TX_DSYNC_SW         (1U << 20)
#define I2S_TIMING_RX_BCK_OUT_DELAY_M  0x00000003
#define I2S_TIMING_RX_BCK_OUT_DELAY_S  18
#define I2S_TIMING_RX_WS_OUT_DELAY_M   0x00000003
#define I2S_TIMING_RX_WS_OUT_DELAY_S   16
#define I2S_TIMING_TX_SD_OUT_DELAY_M   0x00000003
#define I2S_TIMING_TX_SD_OUT_DELAY_S   14
#define I2S_TIMING_TX_WS_OUT_DELAY_M   0x00000003
#define I2S_TIMING_TX_WS_OUT_DELAY_S   12
#define I2S_TIMING_TX_BCK_OUT_DELAY_M  0x00000003
#define I2S_TIMING_TX_BCK_OUT_DELAY_S  10
#define I2S_TIMING_RX_SD_IN_DELAY_M    0x00000003
#define I2S_TIMING_RX_SD_IN_DELAY_S    8
#define I2S_TIMING_RX_WS_IN_DELAY      0x00000003
#define I2S_TIMING_RX_WS_IN_DELAY_S    6
#define I2S_TIMING_RX_BCK_IN_DELAY_M   0x00000003
#define I2S_TIMING_RX_BCK_IN_DELAY_S   4
#define I2S_TIMING_TX_WS_IN_DELAY_M    0x00000003
#define I2S_TIMING_TX_WS_IN_DELAY_S    2
#define I2S_TIMING_TX_BCK_IN_DELAY_M   0x00000003
#define I2S_TIMING_TX_BCK_IN_DELAY_S   0

/* Details for FIFO_CONF register */
#define I2S_FIFO_CONF_RX_FIFO_MOD_POS       16
#define I2S_FIFO_CONF_RX_FIFO_MOD_MASK      (0x00000007 << I2S_FIFO_CONF_RX_FIFO_MOD_POS)
#define I2S_FIFO_CONF_TX_FIFO_MOD_POS       13
#define I2S_FIFO_CONF_TX_FIFO_MOD_MASK      (0x00000007 << I2S_FIFO_CONF_TX_FIFO_MOD_POS)
#define I2S_FIFO_CONF_DESCRIPTOR_ENABLE     (1U << 12)
#define I2S_FIFO_CONF_TX_DATA_NUM_POS       6
#define I2S_FIFO_CONF_TX_DATA_NUM_MASK      (0x0000003f << I2S_FIFO_CONF_TX_DATA_NUM_POS)
#define I2S_FIFO_CONF_RX_DATA_NUM_POS       0
#define I2S_FIFO_CONF_RX_DATA_NUM_MASK      (0x0000003f << I2S_FIFO_CONF_RX_DATA_NUM_POS)

/* Details for CONF_CHANNEL register */
#define I2S_CONF_CHANNELS_RX_CHANNEL_MOD_POS    3
#define I2S_CONF_CHANNELS_RX_CHANNEL_MOD_MASK   (0x00000003 << I2S_CONF_CHANNELS_RX_CHANNEL_MOD_POS)
#define I2S_CONF_CHANNELS_TX_CHANNEL_MOD_POS    0
#define I2S_CONF_CHANNELS_TX_CHANNEL_MOD_MASK   (0x00000007 << I2S_CONF_CHANNELS_TX_CHANNEL_MOD_POS)


FUNC_ON_FLASH void i2s_init(i2s_clock_div_t clock_div, i2s_pins_t pins);
FUNC_ON_FLASH i2s_clock_div_t i2s_freq_to_clock_div(int32_t freq);
FUNC_ON_FLASH void i2s_start(void);
FUNC_ON_FLASH void i2s_stop(void);

#endif /* __ESP8266_I2S_REGS_H */
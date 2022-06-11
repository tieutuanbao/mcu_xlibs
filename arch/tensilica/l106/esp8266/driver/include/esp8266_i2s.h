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

#ifndef _ESP_I2S_REGS_H
#define _ESP_I2S_REGS_H

#include "esp8266_regs.h"

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

/* Details for CONF register */

#define I2S_CONF_BCK_DIV_M      0x0000003f
#define I2S_CONF_BCK_DIV_S      22
#define I2S_CONF_CLKM_DIV_M     0x0000003f
#define I2S_CONF_CLKM_DIV_S     16
#define I2S_CONF_BITS_MOD_M     0x0000000f
#define I2S_CONF_BITS_MOD_S     12
#define I2S_CONF_RX_MSB_SHIFT   BIT(11)
#define I2S_CONF_TX_MSB_SHIFT   BIT(10)
#define I2S_CONF_RX_START       BIT(9)
#define I2S_CONF_TX_START       BIT(8)
#define I2S_CONF_MSB_RIGHT      BIT(7)
#define I2S_CONF_RIGHT_FIRST    BIT(6)
#define I2S_CONF_RX_SLAVE_MOD   BIT(5)
#define I2S_CONF_TX_SLAVE_MOD   BIT(4)
#define I2S_CONF_RX_FIFO_RESET  BIT(3)
#define I2S_CONF_TX_FIFO_RESET  BIT(2)
#define I2S_CONF_RX_RESET       BIT(1)
#define I2S_CONF_TX_RESET       BIT(0)
#define I2S_CONF_RESET_MASK     0xf

/* Details for INT_RAW register */

#define I2S_INT_RAW_TX_REMPTY    BIT(5)
#define I2S_INT_RAW_TX_WFULL     BIT(4)
#define I2S_INT_RAW_RX_REMPTY    BIT(3)
#define I2S_INT_RAW_RX_WFULL     BIT(2)
#define I2S_INT_RAW_TX_PUT_DATA  BIT(1)
#define I2S_INT_RAW_RX_TAKE_DATA BIT(0)

/* Details for INT_STATUS register */

#define I2S_INT_STATUS_TX_REMPTY     BIT(5)
#define I2S_INT_STATUS_TX_WFULL      BIT(4)
#define I2S_INT_STATUS_RX_REMPTY     BIT(3)
#define I2S_INT_STATUS_RX_WFULL      BIT(2)
#define I2S_INT_STATUS_TX_PUT_DATA   BIT(1)
#define I2S_INT_STATUS_RX_TAKE_DATA  BIT(0)

/* Details for INT_ENABLE register */

#define I2S_INT_ENABLE_TX_REMPTY     BIT(5)
#define I2S_INT_ENABLE_TX_WFULL      BIT(4)
#define I2S_INT_ENABLE_RX_REMPTY     BIT(3)
#define I2S_INT_ENABLE_RX_WFULL      BIT(2)
#define I2S_INT_ENABLE_TX_PUT_DATA   BIT(1)
#define I2S_INT_ENABLE_RX_TAKE_DATA  BIT(0)

/* Details for INT_CLEAR register */

#define I2S_INT_CLEAR_TX_REMPTY     BIT(5)
#define I2S_INT_CLEAR_TX_WFULL      BIT(4)
#define I2S_INT_CLEAR_RX_REMPTY     BIT(3)
#define I2S_INT_CLEAR_RX_WFULL      BIT(2)
#define I2S_INT_CLEAR_TX_PUT_DATA   BIT(1)
#define I2S_INT_CLEAR_RX_TAKE_DATA  BIT(0)

/* Details for TIMING register */

#define I2S_TIMING_TX_BCK_IN_INV       BIT(22)
#define I2S_TIMING_RX_DSYNC_SW         BIT(21)
#define I2S_TIMING_TX_DSYNC_SW         BIT(20)
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

#define I2S_FIFO_CONF_RX_FIFO_MOD_M      0x00000007
#define I2S_FIFO_CONF_RX_FIFO_MOD_S      16
#define I2S_FIFO_CONF_TX_FIFO_MOD_M      0x00000007
#define I2S_FIFO_CONF_TX_FIFO_MOD_S      13
#define I2S_FIFO_CONF_DESCRIPTOR_ENABLE  BIT(12)
#define I2S_FIFO_CONF_TX_DATA_NUM_M      0x0000003f
#define I2S_FIFO_CONF_TX_DATA_NUM_S      6
#define I2S_FIFO_CONF_RX_DATA_NUM_M      0x0000003f
#define I2S_FIFO_CONF_RX_DATA_NUM_S      0

/* Details for CONF_CHANNEL register */

#define I2S_CONF_CHANNELS_RX_CHANNEL_MOD_M  0x00000003
#define I2S_CONF_CHANNELS_RX_CHANNEL_MOD_S  3
#define I2S_CONF_CHANNELS_TX_CHANNEL_MOD_M  0x00000007
#define I2S_CONF_CHANNELS_TX_CHANNEL_MOD_S  0

#endif /* _ESP_I2S_REGS_H */

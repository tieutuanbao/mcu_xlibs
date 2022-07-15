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
#include "esp8266_sdk_function.h"

#define I2S(n)      ((volatile i2s_t *)(I2S_BASE + (n) * 0x30))

/**
 * @brief Cấu trúc thanh ghi I2S ESP8266
 * 
 */
typedef volatile struct struct_i2s {
    volatile uint32_t txfifo;           // 0x00
    volatile uint32_t rxfifo;           // 0x04
    union {    // offset: 0x08
        volatile struct {
            uint32_t tx_reset:       1;     // bit 0
            uint32_t rx_reset:       1;     // bit 1
            uint32_t tx_fifo_reset:  1;     // bit 2
            uint32_t rx_fifo_reset:  1;     // bit 3
            uint32_t tx_slave_mod:   1;     // bit 4
            uint32_t rx_slave_mod:   1;     // bit 5
            uint32_t right_first:    1;     // bit 6
            uint32_t msb_right:      1;     // bit 7
            uint32_t tx_start:       1;     // bit 8
            uint32_t rx_start:       1;     // bit 9
            uint32_t tx_msb_shift:   1;     // bit 10
            uint32_t rx_msb_shift:   1;     // bit 11
            uint32_t bits_mod:       4;     // bit 12 : 15
            uint32_t clkm_div_num:   6;     // bit 16 : 21
            uint32_t bck_div_num:    6;     // bit 22 : 27
            uint32_t reserved28:     4;     // bit 28 : 31
        };
        volatile uint32_t val;
    } conf;
    union {    // offset: 0x0C
        volatile struct {
            uint32_t rx_take_data:  1;
            uint32_t tx_put_data:   1;
            uint32_t rx_wfull:      1;
            uint32_t rx_rempty:     1;
            uint32_t tx_wfull:      1;
            uint32_t tx_rempty:     1;
            uint32_t reserved6:    26;
        };
        volatile uint32_t val;
    } int_raw;
    union {    // offset: 0x10
        struct {
            uint32_t rx_take_data:  1;
            uint32_t tx_put_data:   1;
            uint32_t rx_wfull:      1;
            uint32_t rx_rempty:     1;
            uint32_t tx_wfull:      1;
            uint32_t tx_rempty:     1;
            uint32_t reserved6:    26;
        };
        uint32_t val;
    } int_st;
    union {    // offset: 0x14
        volatile struct {
            uint32_t rx_take_data:  1;
            uint32_t tx_put_data:   1;
            uint32_t rx_wfull:      1;
            uint32_t rx_rempty:     1;
            uint32_t tx_wfull:      1;
            uint32_t tx_rempty:     1;
            uint32_t reserved6:    26;
        };
        volatile uint32_t val;
    } int_ena;
    union {    // offset: 0x18
        volatile struct {
            uint32_t rx_take_data:  1;
            uint32_t tx_put_data:   1;
            uint32_t rx_wfull:      1;
            uint32_t rx_rempty:     1;
            uint32_t tx_wfull:      1;
            uint32_t tx_rempty:     1;
            uint32_t reserved6:    26;
        };
        volatile uint32_t val;
    } int_clr;
    union {    // offset: 0x1C
        volatile struct {
            uint32_t tx_bck_in_delay:   2;
            uint32_t tx_ws_in_delay:    2;
            uint32_t rx_bck_in_delay:   2;
            uint32_t rx_ws_in_delay:    2;
            uint32_t rx_sd_in_delay:    2;
            uint32_t tx_bck_out_delay:  2;
            uint32_t tx_ws_out_delay:   2;
            uint32_t tx_sd_out_delay:   2;
            uint32_t rx_ws_out_delay:   2;
            uint32_t rx_bck_out_delay:  2;
            uint32_t tx_dsync_sw:       1;
            uint32_t rx_dsync_sw:       1;
            uint32_t tx_bck_in_inv:     1;
            uint32_t reserved23:        9;
        };
        volatile uint32_t val;
    } timing;
    union {    // offset: 0x20
        volatile struct {
            uint32_t rx_data_num:          6;   // bit 0 : 5
            uint32_t tx_data_num:          6;   // bit 6 : 11
            uint32_t dscr_en:              1;   // bit 12
            uint32_t tx_fifo_mod:          3;   // bit 13 : 15
            uint32_t rx_fifo_mod:          3;   // bit 16 : 18
            uint32_t reserved19:          13;   // bit 19 : 31
        };
        volatile uint32_t val;
    } fifo_conf;
    volatile uint32_t rx_eof_num;    // offset: 0x24
    volatile uint32_t conf_single_data;    // offset: 0x28
    union {    // offset: 0x2C
        volatile struct {
            uint32_t tx_chan_mod: 3;   // bit 0 : 2
            uint32_t rx_chan_mod: 2;   // bit 3 : 4
            uint32_t reserved5:  27;   // bit 5 : 31
        };
        volatile uint32_t val;
    } conf_chan;
} i2s_t;

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


#define i2c_writeReg_Mask(block, host_id, reg_add, Msb, Lsb, indata) \
        rom_i2c_writeReg_Mask(block, host_id, reg_add, Msb, Lsb, indata)

#define i2c_writeReg_Mask_def(block, reg_add, indata) \
        i2c_writeReg_Mask(block, block##_hostid,  reg_add,  reg_add##_msb, reg_add##_lsb,  indata)


/**
 * @brief I2S Peripheral, 0
 */
typedef enum {
    I2S_NUM_0 = 0x0,  /*!< I2S 0*/
    I2S_NUM_MAX,
} i2s_port_t;

typedef struct {
    uint8_t bclk_div;
    uint8_t clkm_div;
} i2s_clock_div_t;

typedef struct {
    int bck_o_en;      /*!< BCK out pin*/
    int ws_o_en;       /*!< WS out pin*/
    int bck_i_en;      /*!< BCK in pin*/
    int ws_i_en;       /*!< WS in pin*/
    int data_out_en;   /*!< DATA out pin*/
    int data_in_en;    /*!< DATA in pin*/
} i2s_pin_config_t;

/**
 * @brief I2S bit width per sample.
 */
typedef enum {
    I2S_BITS_PER_SAMPLE_8BIT    = 8,        /*!< I2S bits per sample: 8-bits*/
    I2S_BITS_PER_SAMPLE_16BIT   = 16,       /*!< I2S bits per sample: 16-bits*/
    I2S_BITS_PER_SAMPLE_24BIT   = 24,       /*!< I2S bits per sample: 24-bits*/
} i2s_bits_per_sample_t;

/**
 * @brief I2S channel.
 */
typedef enum {
    I2S_CHANNEL_MONO        = 1,            /*!< I2S 1 channel (mono)*/
    I2S_CHANNEL_STEREO      = 2             /*!< I2S 2 channel (stereo)*/
} i2s_channel_t;

/**
 * @brief I2S communication standard format
 */
typedef enum {
    I2S_COMM_FORMAT_I2S         = 0x01, /*!< I2S communication format I2S*/
    I2S_COMM_FORMAT_I2S_MSB     = 0x02, /*!< I2S format MSB*/
    I2S_COMM_FORMAT_I2S_LSB     = 0x04, /*!< I2S format LSB*/
} i2s_comm_format_t;

/**
 * @brief I2S channel format type
 */
typedef enum {
    I2S_CHANNEL_FMT_RIGHT_LEFT  = 0x00,
    I2S_CHANNEL_FMT_ALL_RIGHT,
    I2S_CHANNEL_FMT_ALL_LEFT,
    I2S_CHANNEL_FMT_ONLY_RIGHT,
    I2S_CHANNEL_FMT_ONLY_LEFT,
} i2s_channel_fmt_t;

/**
 * @brief I2S Mode, defaut is I2S_MODE_MASTER | I2S_MODE_TX
 */
typedef enum {
    I2S_MODE_MASTER     = 1,
    I2S_MODE_SLAVE      = 2,
    I2S_MODE_TX         = 4,
    I2S_MODE_RX         = 8,
} i2s_mode_t;

typedef struct {
    i2s_mode_t              mode;                   /*!< I2S work mode*/
    int                     sample_rate;            /*!< I2S sample rate*/
    i2s_bits_per_sample_t   bits_per_sample;        /*!< I2S bits per sample*/
    i2s_channel_fmt_t       channel_format;         /*!< I2S channel format */
    i2s_comm_format_t       communication_format;   /*!< I2S communication format */
    int                     dma_buf_count;          /*!< I2S DMA Buffer Count */
    int                     dma_buf_len;            /*!< I2S DMA Buffer Length */
    bool                    tx_desc_auto_clear;     /*!< I2S auto clear tx descriptor if there is underflow condition (helps in avoiding noise in case of data unavailability) */
} i2s_config_t;

extern volatile i2s_t *I2S[I2S_NUM_MAX];

ICACHE_FLASH_ATTR void i2s_init(i2s_port_t i2s_num, i2s_config_t *i2s_config, i2s_pin_config_t *pins);
ICACHE_FLASH_ATTR void i2s_config_io(i2s_port_t i2s_num, i2s_pin_config_t *pins);
ICACHE_FLASH_ATTR i2s_clock_div_t i2s_freq_to_clock_div(int32_t freq);
ICACHE_FLASH_ATTR void i2s_set_channel(i2s_port_t i2s_num, i2s_channel_fmt_t ch_fmt, i2s_bits_per_sample_t bits);
ICACHE_FLASH_ATTR void i2s_set_rate(i2s_port_t i2s_num, uint32_t rate, uint8_t bits_per_samp);
ICACHE_FLASH_ATTR void i2s_set_dividers(i2s_port_t i2s_num, uint8_t bck_div, uint8_t mclk_div);
ICACHE_FLASH_ATTR void i2s_start(i2s_port_t i2s_num);
ICACHE_FLASH_ATTR void i2s_stop(i2s_port_t i2s_num);

#endif /* __ESP8266_I2S_REGS_H */
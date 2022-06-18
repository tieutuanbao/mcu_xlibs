/**
 * @file esp8266_slc.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ESP8266_SLC_H
#define __ESP8266_SLC_H

#include "esp8266_regs.h"
#include "common_macros.h"

#define SLC         ((volatile slc_t *)SLC_BASE)

typedef struct struct_slc {
    union {    // offset: 0x00
        struct {
            uint32_t tx_rst:            1;    // bit 0
            uint32_t rx_rst:            1;    // bit 1
            uint32_t ahbm_fifo_rst:     1;    // bit 2
            uint32_t ahbm_rst:          1;    // bit 3
            uint32_t tx_loop_test:      1;    // bit 4
            uint32_t rx_loop_test:      1;    // bit 5
            uint32_t rx_auto_wrback:    1;    // bit 6
            uint32_t rx_no_restart_clr: 1;    // bit 7
            uint32_t rxdscr_burst_en:   1;    // bit 8
            uint32_t rxdata_burst_en:   1;    // bit 9
            uint32_t rxlink_auto_ret:   1;    // bit 10
            uint32_t txlink_auto_ret:   1;    // bit 11
            uint32_t txdscr_burst_en:   1;    // bit 12
            uint32_t txdata_burst_en:   1;    // bit 13
            uint32_t reserved14:       18;    // bit 14 : 31
        };
        uint32_t val;
    } conf0;
    union {    // offset: 0x04
        struct {
            uint32_t frhost_bit0:             1;    // bit 0
            uint32_t frhost_bit1:             1;    // bit 1
            uint32_t frhost_bit2:             1;    // bit 2
            uint32_t frhost_bit3:             1;    // bit 3
            uint32_t frhost_bit4:             1;    // bit 4
            uint32_t frhost_bit5:             1;    // bit 5
            uint32_t frhost_bit6:             1;    // bit 6
            uint32_t frhost_bit7:             1;    // bit 7
            uint32_t rx_start:                1;    // bit 8
            uint32_t tx_start:                1;    // bit 9
            uint32_t rx_udf:                  1;    // bit 10
            uint32_t tx_ovf:                  1;    // bit 11
            uint32_t token0_1to0:             1;    // bit 12
            uint32_t token1_1to0:             1;    // bit 13
            uint32_t tx_done:                 1;    // bit 14
            uint32_t tx_suc_eof:              1;    // bit 15
            uint32_t rx_done:                 1;    // bit 16
            uint32_t rx_eof:                  1;    // bit 17
            uint32_t tohost:                  1;    // bit 18
            uint32_t tx_dscr_err:             1;    // bit 19
            uint32_t rx_dscr_err:             1;    // bit 20
            uint32_t tx_dscr_empty:           1;    // bit 21
            uint32_t reserved22:             10;    // bit 22 : 31
        };
        uint32_t val;
    } int_raw;
    union {    // offset: 0x08
        struct {
            uint32_t frhost_bit0:            1;    // bit 0
            uint32_t frhost_bit1:            1;    // bit 1
            uint32_t frhost_bit2:            1;    // bit 2
            uint32_t frhost_bit3:            1;    // bit 3
            uint32_t frhost_bit4:            1;    // bit 4
            uint32_t frhost_bit5:            1;    // bit 5
            uint32_t frhost_bit6:            1;    // bit 6
            uint32_t frhost_bit7:            1;    // bit 7
            uint32_t rx_start:               1;    // bit 8
            uint32_t tx_start:               1;    // bit 9
            uint32_t rx_udf:                 1;    // bit 10
            uint32_t tx_ovf:                 1;    // bit 11
            uint32_t token0_1to0:            1;    // bit 12
            uint32_t token1_1to0:            1;    // bit 13
            uint32_t tx_done:                1;    // bit 14
            uint32_t tx_suc_eof:             1;    // bit 15
            uint32_t rx_done:                1;    // bit 16
            uint32_t rx_eof:                 1;    // bit 17
            uint32_t tohost:                 1;    // bit 18
            uint32_t tx_dscr_err:            1;    // bit 19
            uint32_t rx_dscr_err:            1;    // bit 20
            uint32_t tx_dscr_empty:          1;    // bit 21
            uint32_t reserved22:            10;    // bit 22 : 31
        };
        uint32_t val;
    } int_st;
    union {    // offset: 0x0C
        struct {
            uint32_t frhost_bit0:             1;
            uint32_t frhost_bit1:             1;
            uint32_t frhost_bit2:             1;
            uint32_t frhost_bit3:             1;
            uint32_t frhost_bit4:             1;
            uint32_t frhost_bit5:             1;
            uint32_t frhost_bit6:             1;
            uint32_t frhost_bit7:             1;
            uint32_t rx_start:                1;
            uint32_t tx_start:                1;
            uint32_t rx_udf:                  1;
            uint32_t tx_ovf:                  1;
            uint32_t token0_1to0:             1;
            uint32_t token1_1to0:             1;
            uint32_t tx_done:                 1;
            uint32_t tx_suc_eof:              1;
            uint32_t rx_done:                 1;
            uint32_t rx_eof:                  1;
            uint32_t tohost:                  1;
            uint32_t tx_dscr_err:             1;
            uint32_t rx_dscr_err:             1;
            uint32_t tx_dscr_empty:           1;
            uint32_t reserved22:             10;
        };
        uint32_t val;
    } int_ena;
    union {    // offset: 0x10
        struct {
            uint32_t frhost_bit0:             1;
            uint32_t frhost_bit1:             1;
            uint32_t frhost_bit2:             1;
            uint32_t frhost_bit3:             1;
            uint32_t frhost_bit4:             1;
            uint32_t frhost_bit5:             1;
            uint32_t frhost_bit6:             1;
            uint32_t frhost_bit7:             1;
            uint32_t rx_start:                1;
            uint32_t tx_start:                1;
            uint32_t rx_udf:                  1;
            uint32_t tx_ovf:                  1;
            uint32_t token0_1to0:             1;
            uint32_t token1_1to0:             1;
            uint32_t tx_done:                 1;
            uint32_t tx_suc_eof:              1;
            uint32_t rx_done:                 1;
            uint32_t rx_eof:                  1;
            uint32_t tohost:                  1;
            uint32_t tx_dscr_err:             1;
            uint32_t rx_dscr_err:             1;
            uint32_t tx_dscr_empty:           1;
            uint32_t reserved22:             10;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t rx_full:     1;
            uint32_t rx_empty:    1;
            uint32_t reserved2:  30;
        };
        uint32_t val;
    } rx_status;    // 0x14
    union {
        struct {
            uint32_t rxfifo_wdata:   9;
            uint32_t reserved9:      7;
            uint32_t rxfifo_push:    1;
            uint32_t reserved17:    15;
        };
        uint32_t val;
    } rxfifo_push;    // 0x18
    union {
        struct {
            uint32_t tx_full:    1;
            uint32_t tx_empty:   1;
            uint32_t reserved2:  30;
        };
        uint32_t val;
    } tx_status;    // 0x1C
    union {
        struct {
            uint32_t txfifo_rdata:  11;
            uint32_t reserved11:     5;
            uint32_t txfifo_pop:     1;
            uint32_t reserved17:    15;
        };
        uint32_t val;
    } txfifo_pop;    // 0x20
    union {    // offset: 0x24
        struct {
            volatile uint32_t addr:            20;   // bit 0 : 19
            volatile uint32_t reserved20:       8;   // bit 20 : 27
            volatile uint32_t stop:             1;   // bit 28
            volatile uint32_t start:            1;   // bit 29
            volatile uint32_t restart:          1;   // bit 30
            volatile uint32_t park:             1;   // bit 31
        };
        volatile uint32_t val;
    } rx_link;
    union {    // offset: 0x28
        struct {
            uint32_t addr:            20;   // bit 0 : 19
            uint32_t reserved20:       8;   // bit 20 : 27
            uint32_t stop:             1;   // bit 28
            uint32_t start:            1;   // bit 29
            uint32_t restart:          1;   // bit 30
            uint32_t park:             1;   // bit 21
        };
        uint32_t val;
    } tx_link;
    union {
        struct {
            uint32_t intvec:      8;
            uint32_t reserved8:  24;
        };
        uint32_t val;
    } intvec_tohost;    // 0x2C
    union {
        struct {
            uint32_t wdata:            12;
            uint32_t wr:                1;
            uint32_t inc:               1;
            uint32_t inc_more:          1;
            uint32_t reserved15:        1;
            uint32_t token0:           12;
            uint32_t reserved28:        4;
        };
        uint32_t val;
    } token0;    // 0x30
    union {
        struct {
            uint32_t wdata:            12;
            uint32_t wr:                1;
            uint32_t inc:               1;
            uint32_t inc_more:          1;
            uint32_t reserved15:        1;
            uint32_t token1:           12;
            uint32_t reserved28:        4;
        };
        uint32_t val;
    } token1;    // 0x34
    uint32_t conf1;    // 0x38
    uint32_t state0;    // 0x3C
    uint32_t state1;    // 0x40
    union {
        struct {
            uint32_t txeof_ena:           6;
            uint32_t reserved6:           2;
            uint32_t fifo_map_ena:        4;
            uint32_t tx_dummy_mode:       1;
            uint32_t reserved13:          3;
            uint32_t tx_push_idle_num:   16;
        };
        uint32_t val;
    } bridge_conf;    // 0x44
    uint32_t rx_eof_des_addr;    // 0x48
    uint32_t tx_eof_des_addr;    // 0x4C
    uint32_t to_eof_bfr_des_addr;    // 0x50
    union {    // offset: 0x54
        struct {
            uint32_t mode:         3;
            uint32_t reserved3:    1;
            uint32_t addr:         2;
            uint32_t reserved6:   26;
        };
        uint32_t val;
    } ahb_test;
    union {    // offset: 0x58
        struct {
            uint32_t cmd_st:          3;
            uint32_t reserved3:       1;
            uint32_t func_st:         4;
            uint32_t sdio_wakeup:     1;
            uint32_t reserved9:       3;
            uint32_t bus_st:          3;
            uint32_t reserved15:     17;
        };
        uint32_t val;
    } sdio_st;
    union {    // offset: 0x5C
        struct {
            uint32_t pop_idle_cnt:     16;  // bit 0 : 15
            uint32_t token_no_replace:  1;  // bit 16
            uint32_t infor_no_replace:  1;  // bit 17
            uint32_t rx_fill_mode:      1;  // bit 18
            uint32_t rx_eof_mode:       1;  // bit 19
            uint32_t rx_fill_en:        1;  // bit 20
            uint32_t reserved21:       11;  // bit 21 : 31
        };
        uint32_t val;
    } rx_dscr_conf;
    uint32_t txlink_dscr;    // 0x60
    uint32_t txlink_dscr_bf0;    // 0x64
    uint32_t txlink_dscr_bf1;    // 0x68
    uint32_t rxlink_dscr;    // 0x6C
    uint32_t rxlink_dscr_bf0;    // 0x70
    uint32_t rxlink_dscr_bf1;    // 0x74
    uint32_t date;    // 0x78
    uint32_t id;    // 0x7C
    uint32_t reserved_80[2];
    union {
        struct {
            uint32_t reserved0:      23;
            uint32_t intr_ena:        1;
            uint32_t reserved24:      8;
        };
        uint32_t val;
    } host_intr_raw;    // 0x88
    uint32_t reserved_8C[2];
    uint32_t host_conf_w0;    // 0x94
    uint32_t host_conf_w1;    // 0x98
    uint32_t host_intr_status;    // 0x9C
    uint32_t host_conf_w2;    // 0xA0
    uint32_t host_conf_w3;    // 0xA4
    uint32_t host_conf_w4;    // 0xA8
    uint32_t reserved_AC[1];
    union {
        struct {
            uint32_t reserved0:       12;
            uint32_t sof_bit:          1;
            uint32_t reserved13:      19;
        };
        uint32_t val;
    } host_intr_clr;    // 0xB0
    union {
        struct {
            uint32_t tohost_bit0:     1;
            uint32_t reserved1:      22;
            uint32_t rx_new_packet:   1;
            uint32_t reserved24:      8;
        };
        uint32_t val;
    } host_intr_ena;    // 0xB4
    uint32_t reserved_BC[1];
    uint32_t host_conf_w5;    // 0xBC
} slc_t;

/* Details for CONF0 register */
#define SLC_CONF0_MODE_POS                  12
#define SLC_CONF0_MODE_MASK                 (0x00000003 << SLC_CONF0_MODE_POS)
#define SLC_CONF0_DATA_BURST_ENABLE         (1U << 9)
#define SLC_CONF0_DESCRIPTOR_BURST_ENABLE   (1U << 8)
#define SLC_CONF0_RX_NO_RESTART_CLEAR       (1U << 7)
#define SLC_CONF0_RX_AUTO_WRITE_BACK        (1U << 6)
#define SLC_CONF0_RX_LOOP_TEST              (1U << 5)
#define SLC_CONF0_TX_LOOP_TEST              (1U << 4)
#define SLC_CONF0_AHBM_RESET                (1U << 3)
#define SLC_CONF0_AHBM_FIFO_RESET           (1U << 2)
#define SLC_CONF0_RX_LINK_RESET             (1U << 1)
#define SLC_CONF0_TX_LINK_RESET             (1U)

/* Details for INT_RAW register */
#define SLC_INT_RAW_TX_DSCR_EMPTY   (1U << 21)
#define SLC_INT_RAW_RX_DSCR_ERROR   (1U << 20)
#define SLC_INT_RAW_TX_DSCR_ERROR   (1U << 19)
#define SLC_INT_RAW_TO_HOST         (1U << 18)
#define SLC_INT_RAW_RX_EOF          (1U << 17)
#define SLC_INT_RAW_RX_DONE         (1U << 16)
#define SLC_INT_RAW_TX_EOF          (1U << 15)
#define SLC_INT_RAW_TX_DONE         (1U << 14)
#define SLC_INT_RAW_TOKEN1_1TO0     (1U << 13)
#define SLC_INT_RAW_TOKEN0_1TO0     (1U << 12)
#define SLC_INT_RAW_TX_OVERFLOW     (1U << 11)
#define SLC_INT_RAW_RX_UNDEFLOW     (1U << 10)
#define SLC_INT_RAW_TX_START        (1U << 9)
#define SLC_INT_RAW_RX_START        (1U << 8)
#define SLC_INT_RAW_FROM_HOST_BIT7  (1U << 7)
#define SLC_INT_RAW_FROM_HOST_BIT6  (1U << 6)
#define SLC_INT_RAW_FROM_HOST_BIT5  (1U << 5)
#define SLC_INT_RAW_FROM_HOST_BIT4  (1U << 4)
#define SLC_INT_RAW_FROM_HOST_BIT3  (1U << 3)
#define SLC_INT_RAW_FROM_HOST_BIT2  (1U << 2)
#define SLC_INT_RAW_FROM_HOST_BIT1  (1U << 1)
#define SLC_INT_RAW_FROM_HOST_BIT0  (1U)

/* Details for INT_STATUS register */

#define SLC_INT_STATUS_TX_DSCR_EMPTY   (1U << 21)
#define SLC_INT_STATUS_RX_DSCR_ERROR   (1U << 20)
#define SLC_INT_STATUS_TX_DSCR_ERROR   (1U << 19)
#define SLC_INT_STATUS_TO_HOST         (1U << 18)
#define SLC_INT_STATUS_RX_EOF          (1U << 17)
#define SLC_INT_STATUS_RX_DONE         (1U << 16)
#define SLC_INT_STATUS_TX_EOF          (1U << 15)
#define SLC_INT_STATUS_TX_DONE         (1U << 14)
#define SLC_INT_STATUS_TOKEN1_1TO0     (1U << 13)
#define SLC_INT_STATUS_TOKEN0_1TO0     (1U << 12)
#define SLC_INT_STATUS_TX_OVERFLOW     (1U << 11)
#define SLC_INT_STATUS_RX_UNDEFLOW     (1U << 10)
#define SLC_INT_STATUS_TX_START        (1U << 9)
#define SLC_INT_STATUS_RX_START        (1U << 8)
#define SLC_INT_STATUS_FROM_HOST_BIT7  (1U << 7)
#define SLC_INT_STATUS_FROM_HOST_BIT6  (1U << 6)
#define SLC_INT_STATUS_FROM_HOST_BIT5  (1U << 5)
#define SLC_INT_STATUS_FROM_HOST_BIT4  (1U << 4)
#define SLC_INT_STATUS_FROM_HOST_BIT3  (1U << 3)
#define SLC_INT_STATUS_FROM_HOST_BIT2  (1U << 2)
#define SLC_INT_STATUS_FROM_HOST_BIT1  (1U << 1)
#define SLC_INT_STATUS_FROM_HOST_BIT0  (1U)

/* Details for INT_ENABLE register */
#define SLC_INT_ENABLE_TX_DSCR_EMPTY   (1U << 21)
#define SLC_INT_ENABLE_RX_DSCR_ERROR   (1U << 20)
#define SLC_INT_ENABLE_TX_DSCR_ERROR   (1U << 19)
#define SLC_INT_ENABLE_TO_HOST         (1U << 18)
#define SLC_INT_ENABLE_RX_EOF          (1U << 17)
#define SLC_INT_ENABLE_RX_DONE         (1U << 16)
#define SLC_INT_ENABLE_TX_EOF          (1U << 15)
#define SLC_INT_ENABLE_TX_DONE         (1U << 14)
#define SLC_INT_ENABLE_TOKEN1_1TO0     (1U << 13)
#define SLC_INT_ENABLE_TOKEN0_1TO0     (1U << 12)
#define SLC_INT_ENABLE_TX_OVERFLOW     (1U << 11)
#define SLC_INT_ENABLE_RX_UNDEFLOW     (1U << 10)
#define SLC_INT_ENABLE_TX_START        (1U << 9)
#define SLC_INT_ENABLE_RX_START        (1U << 8)
#define SLC_INT_ENABLE_FROM_HOST_BIT7  (1U << 7)
#define SLC_INT_ENABLE_FROM_HOST_BIT6  (1U << 6)
#define SLC_INT_ENABLE_FROM_HOST_BIT5  (1U << 5)
#define SLC_INT_ENABLE_FROM_HOST_BIT4  (1U << 4)
#define SLC_INT_ENABLE_FROM_HOST_BIT3  (1U << 3)
#define SLC_INT_ENABLE_FROM_HOST_BIT2  (1U << 2)
#define SLC_INT_ENABLE_FROM_HOST_BIT1  (1U << 1)
#define SLC_INT_ENABLE_FROM_HOST_BIT0  (1U)

#define SLC_INT_ENABLE_FROM_HOST_BIT_ALL  0xff

/* Details for INT_CLEAR register */
#define SLC_INT_CLEAR_TX_DSCR_EMPTY   (1U << 21)
#define SLC_INT_CLEAR_RX_DSCR_ERROR   (1U << 20)
#define SLC_INT_CLEAR_TX_DSCR_ERROR   (1U << 19)
#define SLC_INT_CLEAR_TO_HOST         (1U << 18)
#define SLC_INT_CLEAR_RX_EOF          (1U << 17)
#define SLC_INT_CLEAR_RX_DONE         (1U << 16)
#define SLC_INT_CLEAR_TX_EOF          (1U << 15)
#define SLC_INT_CLEAR_TX_DONE         (1U << 14)
#define SLC_INT_CLEAR_TOKEN1_1TO0     (1U << 13)
#define SLC_INT_CLEAR_TOKEN0_1TO0     (1U << 12)
#define SLC_INT_CLEAR_TX_OVERFLOW     (1U << 11)
#define SLC_INT_CLEAR_RX_UNDEFLOW     (1U << 10)
#define SLC_INT_CLEAR_TX_START        (1U << 9)
#define SLC_INT_CLEAR_RX_START        (1U << 8)
#define SLC_INT_CLEAR_FROM_HOST_BIT7  (1U << 7)
#define SLC_INT_CLEAR_FROM_HOST_BIT6  (1U << 6)
#define SLC_INT_CLEAR_FROM_HOST_BIT5  (1U << 5)
#define SLC_INT_CLEAR_FROM_HOST_BIT4  (1U << 4)
#define SLC_INT_CLEAR_FROM_HOST_BIT3  (1U << 3)
#define SLC_INT_CLEAR_FROM_HOST_BIT2  (1U << 2)
#define SLC_INT_CLEAR_FROM_HOST_BIT1  (1U << 1)
#define SLC_INT_CLEAR_FROM_HOST_BIT0  (1U)

/* Details for RX_STATUS register */
#define SLC_RX_STATUS_EMPTY  (1U << 1)
#define SLC_RX_STATUS_FULL   (1U)

/* Details for RX_FIFO_PUSH register */
#define SLC_RX_FIFO_PUSH_FLAG    (1U << 16)
#define SLC_RX_FIFO_PUSH_DATA_M  0x000001ff
#define SLC_RX_FIFO_PUSH_DATA_S  0

/* Details for TX_STATUS register */
#define SLC_TX_STATUS_EMPTY  (1U << 1)
#define SLC_TX_STATUS_FULL   (1U)

/* Details for TX_FIFO_POP register */
#define SLC_TX_FIFO_POP_FLAG    (1U << 16)
#define SLC_TX_FIFO_POP_DATA_M  0x000007ff
#define SLC_TX_FIFO_POP_DATA_S  0

/* Details for RX_LINK register */
#define SLC_RX_LINK_PARK                            (1U << 31)
#define SLC_RX_LINK_RESTART                         (1U << 30)
#define SLC_RX_LINK_START                           (1U << 29)
#define SLC_RX_LINK_STOP                            (1U << 28)
#define SLC_RX_LINK_DESCRIPTOR_ADDR_POS             0
#define SLC_RX_LINK_DESCRIPTOR_ADDR_MASK            (0x000Fffff << SLC_RX_LINK_DESCRIPTOR_ADDR_POS)

/* Details for TX_LINK register */
#define SLC_TX_LINK_PARK                            (1U << 31)
#define SLC_TX_LINK_RESTART                         (1U << 30)
#define SLC_TX_LINK_START                           (1U << 29)
#define SLC_TX_LINK_STOP                            (1U << 28)
#define SLC_TX_LINK_DESCRIPTOR_ADDR_POS             0
#define SLC_TX_LINK_DESCRIPTOR_ADDR_MASK            (0x000Fffff << SLC_TX_LINK_DESCRIPTOR_ADDR_POS)

/* Details for INTVEC_TO_HOST register */
#define SLC_INTVEC_TO_HOST_INTVEC_M                 0x000000ff
#define SLC_INTVEC_TO_HOST_INTVEC_S                 0

/* Details for TOKEN0 register */
#define SLC_TOKEN0_POS                              16
#define SLC_TOKEN0_MASK                             (0x00000fff << SLC_TOKEN0_POS)
#define SLC_TOKEN0_LOCAL_INC_MORE                   (1U << 14)
#define SLC_TOKEN0_LOCAL_INC                        (1U << 13)
#define SLC_TOKEN0_LOCAL_WRITE                      (1U << 12)
#define SLC_TOKEN0_LOCAL_DATA_MASK                  0x00000FFF

/* Details for TOKEN1 register */
#define SLC_TOKEN1_POS                              16
#define SLC_TOKEN1_MASK                             (0x00000fff << SLC_TOKEN1_POS)
#define SLC_TOKEN1_LOCAL_INC_MORE                   (1U << 14)
#define SLC_TOKEN1_LOCAL_INC                        (1U << 13)
#define SLC_TOKEN1_LOCAL_WRITE                      (1U << 12)
#define SLC_TOKEN1_LOCAL_DATA_MASK                  0x00000fff

/* Details for BRIDGE_CONF register */
#define SLC_BRIDGE_CONF_TX_PUSH_IDLE_POS            16
#define SLC_BRIDGE_CONF_TX_PUSH_IDLE_MASK           (0x0000ffff << SLC_BRIDGE_CONF_TX_PUSH_IDLE_POS)
#define SLC_BRIDGE_CONF_TX_DUMMY_MODE               (1U << 12)
#define SLC_BRIDGE_CONF_FIFO_MAP_ENABLE_POS         8
#define SLC_BRIDGE_CONF_FIFO_MAP_ENABLE_MASK        (0x0000000f << SLC_BRIDGE_CONF_FIFO_MAP_ENABLE_POS)
#define SLC_BRIDGE_CONF_TX_EOF_ENABLE_MASK          0x0000003f

/* Details for AHB_TEST register */
#define SLC_AHB_TEST_ADDR_POS                       4
#define SLC_AHB_TEST_ADDR_MASK                      (0x00000003 << SLC_AHB_TEST_ADDR_POS)
#define SLC_AHB_TEST_MODE_MASK                      0x00000007

/* Details for SDIO_STATUS register */
#define SLC_SDIO_STATUS_BUS_POS                     12
#define SLC_SDIO_STATUS_BUS_MASK                    (0x00000007 << 12)
#define SLC_SDIO_STATUS_WAKEUP                      (1U << 8)
#define SLC_SDIO_STATUS_FUNC_POS                    4
#define SLC_SDIO_STATUS_FUNC_MASK                   (0x0000000f << SLC_SDIO_STATUS_FUNC_POS)
#define SLC_SDIO_STATUS_COMMAND_MASK                0x00000007

/* Details for RX_DESCRIPTOR_CONF register */
#define SLC_RX_DESCRIPTOR_CONF_RX_FILL_ENABLE       (1U << 20)
#define SLC_RX_DESCRIPTOR_CONF_RX_EOF_MODE          (1U << 19)
#define SLC_RX_DESCRIPTOR_CONF_RX_FILL_MODE         (1U << 18)
#define SLC_RX_DESCRIPTOR_CONF_INFOR_NO_REPLACE     (1U << 17)
#define SLC_RX_DESCRIPTOR_CONF_TOKEN_NO_REPLACE     (1U << 16)
#define SLC_RX_DESCRIPTOR_CONF_POP_IDLE_COUNT_MASK  0x0000ffff

/**
 * @brief Cấu trúc Descriptor DMA
 * 
 */
typedef struct struct_dma_descriptor {
    uint32_t blocksize      : 12;
    uint32_t datalen        : 12;
    uint32_t unused         : 5;
    uint32_t sub_sof        : 1;
    uint32_t eof            : 1;
    uint32_t owner          : 1;    // giá trị này có thể bị thay đổi bởi DMA
    void* buf_ptr;
    volatile struct struct_dma_descriptor *next;
} dma_descriptor_t;

typedef void (*slc_handler_isr)(void *);

ICACHE_FLASH_ATTR void slc_init(slc_handler_isr slc_isr, void *arg);
ICACHE_FLASH_ATTR void slc_start(volatile dma_descriptor_t *descr);
ICACHE_FLASH_ATTR void slc_stop(void);


#endif /* __ESP8266_SLC_H */

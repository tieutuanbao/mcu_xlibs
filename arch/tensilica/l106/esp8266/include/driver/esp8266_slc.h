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

#define SLC         (*(slc_t *)SLC_BASE)

typedef struct struct_slc {
    volatile uint32_t conf0;                   // 0x00
    volatile uint32_t int_raw;                 // 0x04
    volatile uint32_t int_status;              // 0x08
    volatile uint32_t int_enable;              // 0x0c
    volatile uint32_t int_clear;               // 0x10
    volatile uint32_t rx_status;               // 0x14
    volatile uint32_t rx_fifo_push;            // 0x18
    volatile uint32_t tx_status;               // 0x1c
    volatile uint32_t tx_fifo_pop;             // 0x20
    volatile uint32_t rx_link;                 // 0x24
    volatile uint32_t tx_link;                 // 0x28
    volatile uint32_t intvec_to_host;          // 0x2c
    volatile uint32_t token0;                  // 0x30
    volatile uint32_t token1;                  // 0x34
    volatile uint32_t conf1;                   // 0x38
    volatile uint32_t state0;                  // 0x3c
    volatile uint32_t state1;                  // 0x40
    volatile uint32_t bridge_conf;             // 0x44
    volatile uint32_t rx_eof_descriptor_addr;  // 0x48
    volatile uint32_t tx_eof_descriptor_addr;  // 0x4c
    volatile uint32_t rx_eof_buffer_descriptor_addr; // 0x50 - naming uncertain
    volatile uint32_t ahb_test;                // 0x54
    volatile uint32_t sdio_status;             // 0x58
    volatile uint32_t rx_descriptor_conf;      // 0x5c
    volatile uint32_t tx_link_descriptor;      // 0x60
    volatile uint32_t tx_link_descriptor_bf0;  // 0x64
    volatile uint32_t tx_link_descriptor_bf1;  // 0x68
    volatile uint32_t rx_link_descriptor;      // 0x6c
    volatile uint32_t rx_link_descriptor_bf0;  // 0x70
    volatile uint32_t rx_link_descriptor_bf1;  // 0x74
    volatile uint32_t date;                    // 0x78
    volatile uint32_t id;                      // 0x7c
    volatile uint32_t unknown_80;              // 0x80
    volatile uint32_t unknown_84;              // 0x84
    volatile uint32_t host_int_raw;            // 0x88
    volatile uint32_t unknown_8c;              // 0x8c
    volatile uint32_t unknown_90;              // 0x90
    volatile uint32_t host_conf_w0;            // 0x94
    volatile uint32_t host_conf_w1;            // 0x98
    volatile uint32_t host_int_status;         // 0x9c
    volatile uint32_t host_conf_w2;            // 0xa0
    volatile uint32_t host_conf_w3;            // 0xa4
    volatile uint32_t host_conf_w4;            // 0xa8
    volatile uint32_t unknown_ac;              // 0xac
    volatile uint32_t host_int_clear;          // 0xb0
    volatile uint32_t host_int_enable;         // 0xb4
    volatile uint32_t unknown_b8;              // 0xb8
    volatile uint32_t host_conf_w5;            // 0xbc
} slc_t;

/* Details for CONF0 register */
#define SLC_CONF0_MODE_POS                  12
#define SLC_CONF0_MODE_MASK                 (0x00000003 << SLC_CONF0_MODE_POS)
#define SLC_CONF0_DATA_BURST_ENABLE        (1U << 9)
#define SLC_CONF0_DESCRIPTOR_BURST_ENABLE  (1U << 8)
#define SLC_CONF0_RX_NO_RESTART_CLEAR      (1U << 7)
#define SLC_CONF0_RX_AUTO_WRITE_BACK       (1U << 6)
#define SLC_CONF0_RX_LOOP_TEST             (1U << 5)
#define SLC_CONF0_TX_LOOP_TEST             (1U << 4)
#define SLC_CONF0_AHBM_RESET               (1U << 3)
#define SLC_CONF0_AHBM_FIFO_RESET          (1U << 2)
#define SLC_CONF0_RX_LINK_RESET            (1U << 1)
#define SLC_CONF0_TX_LINK_RESET            (1U)

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
#define SLC_RX_LINK_DESCRIPTOR_ADDR_MASK            (0x000fffff << SLC_RX_LINK_DESCRIPTOR_ADDR_POS)

/* Details for TX_LINK register */
#define SLC_TX_LINK_PARK                            (1U << 31)
#define SLC_TX_LINK_RESTART                         (1U << 30)
#define SLC_TX_LINK_START                           (1U << 29)
#define SLC_TX_LINK_STOP                            (1U << 28)
#define SLC_TX_LINK_DESCRIPTOR_ADDR_M               0x000fffff
#define SLC_TX_LINK_DESCRIPTOR_ADDR_S               0

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
    struct dma_descriptor *next;
} dma_descriptor_t;

typedef void (*slc_handler_isr)(void *);

void slc_init(void);
void slc_register_handler(slc_handler_isr slc_isr, void *arg);


#endif /* __ESP8266_SLC_H */

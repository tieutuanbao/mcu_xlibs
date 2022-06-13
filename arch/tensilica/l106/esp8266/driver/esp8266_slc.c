/**
 * @file esp8266_slc.c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "esp8266_slc.h"
#include "esp8266_interrupt.h"

/**
 * @brief Hàm khởi tạo DMA
 * 
 */
FUNC_ON_FLASH void slc_init(slc_handler_isr slc_isr, void *arg) {
    BITS_LOG("slc_init 1\r\n");

    /* Vô hiệu hóa ngắt DMA */
    disable_interrupts(INT_NUM_SLC);

    /* Reset Rx & Tx link DMA */
    SLC.conf0 |= SLC_CONF0_RX_LINK_RESET | SLC_CONF0_TX_LINK_RESET;
    SLC.conf0 &= ~(SLC_CONF0_RX_LINK_RESET | SLC_CONF0_TX_LINK_RESET);

    /* Xóa cờ ngắt DMA */
    SLC.int_clear = 0xFFFFFFFF;

    /* Enable DMA */
    SLC.conf0 &= ~(SLC_CONF0_MODE_MASK);
    SLC.conf0 |= (1U << SLC_CONF0_MODE_POS);    
    SLC.rx_descriptor_conf |= (SLC_RX_DESCRIPTOR_CONF_INFOR_NO_REPLACE | SLC_RX_DESCRIPTOR_CONF_TOKEN_NO_REPLACE);
    SLC.rx_descriptor_conf &= ~(SLC_RX_DESCRIPTOR_CONF_RX_FILL_ENABLE | SLC_RX_DESCRIPTOR_CONF_RX_EOF_MODE | SLC_RX_DESCRIPTOR_CONF_RX_FILL_MODE);
    
    /* Clear Descriptor */
    SLC.tx_link &= ~(SLC_TX_LINK_DESCRIPTOR_ADDR_MASK);
    SLC.rx_link &= ~(SLC_RX_LINK_DESCRIPTOR_ADDR_MASK);

    if(slc_isr) {
        register_interrupts(INT_NUM_SLC, slc_isr, arg);
        SLC.int_clear = 0xFFFFFFFF;
        SLC.int_enable |= SLC_INT_ENABLE_RX_EOF;
        enable_interrupts(INT_NUM_SLC);
    }
    /* Luôn luôn cho phép DMA Tx_link chạy */
    SLC.tx_link |= SLC_TX_LINK_START;
    /* Start RX */
    SLC.rx_link |= SLC_RX_LINK_START;
}

/**
 * @brief Hàm cho phép chạy DMA
 * 
 * @param descr Cấu trúc mô tả truyền DMA
 */
FUNC_ON_FLASH void slc_start(dma_descriptor_t *descr) {
    SLC.rx_link &= ~SLC_RX_LINK_DESCRIPTOR_ADDR_MASK;
    SLC.rx_link |= (((uint32_t)descr) << SLC_RX_LINK_DESCRIPTOR_ADDR_POS);
}

/**
 * @brief Hàm dừng truyền DMA
 * 
 */
FUNC_ON_FLASH void slc_stop(void) {
    SLC.rx_link &= ~SLC_RX_LINK_DESCRIPTOR_ADDR_MASK;
}

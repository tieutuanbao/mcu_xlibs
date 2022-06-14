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
ICACHE_FLASH_ATTR void slc_init(slc_handler_isr slc_isr, void *arg) {
    /* Vô hiệu hóa ngắt DMA */
    disable_interrupts(INT_NUM_SLC);

    /* Reset Rx & Tx link DMA */
    SLC->conf0.val |= SLC_CONF0_RX_LINK_RESET | SLC_CONF0_TX_LINK_RESET;
    SLC->conf0.val &= ~(SLC_CONF0_RX_LINK_RESET | SLC_CONF0_TX_LINK_RESET);

    /* Xóa cờ ngắt DMA */
    SLC->int_clr.val = 0xFFFFFFFF;
    SLC->int_clr.val = 0;

    /* Enable DMA */
    SLC->conf0.val &= ~(SLC_CONF0_MODE_MASK);
    SLC->conf0.val |= (1U << SLC_CONF0_MODE_POS);    
    SLC->rx_dscr_conf.val |= (SLC_RX_DESCRIPTOR_CONF_INFOR_NO_REPLACE | SLC_RX_DESCRIPTOR_CONF_TOKEN_NO_REPLACE);
    SLC->rx_dscr_conf.val &= ~(SLC_RX_DESCRIPTOR_CONF_RX_FILL_ENABLE | SLC_RX_DESCRIPTOR_CONF_RX_EOF_MODE | SLC_RX_DESCRIPTOR_CONF_RX_FILL_MODE);
    
    /* Clear Descriptor */
    SLC->tx_link.val &= ~(SLC_TX_LINK_DESCRIPTOR_ADDR_MASK);
    SLC->rx_link.val &= ~(SLC_RX_LINK_DESCRIPTOR_ADDR_MASK);

    if(slc_isr) {
        register_interrupts(INT_NUM_SLC, slc_isr, arg);
        SLC->int_ena.rx_eof = 1;
        SLC->int_clr.val = 0xFFFFFFFF;
        enable_interrupts(INT_NUM_SLC);
    }
    /* Luôn luôn cho phép DMA Tx_link chạy */
    SLC->tx_link.val |= SLC_TX_LINK_START;
    /* Start RX */
    SLC->rx_link.val |= SLC_RX_LINK_START;
}

/**
 * @brief Cho phép chạy DMA
 * 
 * @param descr Cấu trúc mô tả truyền DMA
 */
ICACHE_FLASH_ATTR void slc_start(dma_descriptor_t *descr) {
    SLC->rx_link.val &= ~SLC_RX_LINK_DESCRIPTOR_ADDR_MASK;
    SLC->rx_link.val |= (((uint32_t)descr) << SLC_RX_LINK_DESCRIPTOR_ADDR_POS);
}

/**
 * @brief Dừng truyền DMA
 * 
 */
ICACHE_FLASH_ATTR void slc_stop(void) {
    SLC->rx_link.val &= ~SLC_RX_LINK_DESCRIPTOR_ADDR_MASK;
}

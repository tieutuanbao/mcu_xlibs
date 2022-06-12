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
void slc_init(void) {
    /* Reset DMA */
    SLC.conf0 |= SLC_CONF0_RX_LINK_RESET;
    SLC.conf0 &= ~SLC_CONF0_RX_LINK_RESET;

    /* Xóa cờ ngắt DMA */
    SLC.int_clear = 0xFFFFFFFF;
    SLC.int_clear = 0;

    /* Enable DMA */
    SLC.conf0 &= ~(1U << SLC_CONF0_MODE_POS);
    SLC.conf0 |= (1U << SLC_CONF0_MODE_POS);
    
    SLC.rx_descriptor_conf |= (SLC_RX_DESCRIPTOR_CONF_INFOR_NO_REPLACE | SLC_RX_DESCRIPTOR_CONF_TOKEN_NO_REPLACE);
    SLC.rx_descriptor_conf &= ~(SLC_RX_DESCRIPTOR_CONF_RX_FILL_ENABLE | SLC_RX_DESCRIPTOR_CONF_RX_EOF_MODE | SLC_RX_DESCRIPTOR_CONF_RX_FILL_MODE);
    
    /* Start RX */
    SLC.rx_link |= SLC_RX_LINK_START;
}

/**
 * @brief Hàm đăng ký handler DMA
 * 
 * @param slc_isr hàm ngắt DMA
 * @param arg đối số bổ xung
 */
void slc_register_handler(slc_handler_isr slc_isr, void *arg) {
    if(slc_isr) {
        _xt_isr_attach(INT_NUM_SLC, slc_isr, arg);
        SLC.int_enable |= SLC_INT_ENABLE_RX_EOF;
        SLC.int_clear = 0xFFFFFFFF;
        _xt_isr_unmask(1 << INT_NUM_SLC);
    }
}

/**
 * @brief Hàm cho phép chạy DMA
 * 
 * @param descr Cấu trúc mô tả truyền DMA
 */
void slc_start(dma_descriptor_t *descr) {
    SLC.rx_link &= ~SLC_RX_LINK_DESCRIPTOR_ADDR_MASK;
    SLC.rx_link |= (((uint32_t)descr) << SLC_RX_LINK_DESCRIPTOR_ADDR_POS);
}

/**
 * @brief Hàm dừng truyền DMA
 * 
 */
void slc_stop(void) {
    SLC.rx_link &= ~SLC_RX_LINK_DESCRIPTOR_ADDR_MASK;
}

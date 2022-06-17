/**
 * @file i2s_dma.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "i2s_dma.h"
#include "common_macros.h"
#include "esp8266_interrupt.h"
#include "esp8266_i2s.h"
#include "esp8266_slc.h"

/* Descriptor Buffer vòng DMA */
static dma_descriptor_t dma_block_list[DMA_QUEUE_SIZE];

/* Buffer DMA */
static uint32_t dma_buffer[DMA_QUEUE_SIZE][DMA_BUFFER_SIZE];

/* Cấu trúc queue */
typedef struct struct_queue {
    void *queue[DMA_QUEUE_SIZE];
    volatile uint8_t queue_len;
} queue_t;

queue_t dma_queue;

/**
 * @brief Khởi tạo Deskcriptor
 * 
 * @return void 
 */
ICACHE_FLASH_ATTR void init_descriptors_list() {
    memset(dma_buffer, 0, DMA_QUEUE_SIZE * DMA_BUFFER_SIZE * 4);

    for (int i = 0; i < DMA_QUEUE_SIZE; i++) {
        dma_block_list[i].owner = 1;
        dma_block_list[i].eof = 1;
        dma_block_list[i].sub_sof = 0;
        dma_block_list[i].unused = 0;
        dma_block_list[i].buf_ptr = (uint32_t *)(&dma_buffer[i][0]);
        dma_block_list[i].datalen = DMA_BUFFER_SIZE * 4;
        dma_block_list[i].blocksize = DMA_BUFFER_SIZE * 4;
        if (i == (DMA_QUEUE_SIZE - 1)) {
            dma_block_list[i].next = &dma_block_list[0];
        } else {
            dma_block_list[i].next = &dma_block_list[i + 1];
        }
    }
}

/**
 * @brief Trả về con trỏ đến Buffer DMA đã xử lý xong
 * 
 * @return dma_descriptor_t* 
 */
inline dma_descriptor_t *i2s_dma_get_eof_descriptor()
{
    return (dma_descriptor_t*)SLC->rx_eof_des_addr;
}

/**
 * @brief Kiểm tra ngắt EOF
 * 
 * @return bool : true = Có ngắt EOF
 */
bool i2s_dma_is_eof_interrupt() {
    if(SLC->int_st.val & SLC_INT_STATUS_RX_EOF) return true;
    return false;
}

void dma_isr_handler(void *args) {
    /* Disable DMA interrupt */
    disable_interrupts(INT_NUM_SLC);
    if (i2s_dma_is_eof_interrupt()) {
        dma_descriptor_t *descr = i2s_dma_get_eof_descriptor();
        memset((void *)descr->buf_ptr, 0x00, DMA_BUFFER_SIZE * 4);
        if (dma_queue.queue_len >= (DMA_QUEUE_SIZE - 1)) {
            /* Lấy 1 phần tử đầu Queue */
            dma_queue.queue_len--;
            /* Dồn Queue lên đầu */
            for(uint16_t idx_queue = 0; idx_queue < dma_queue.queue_len; idx_queue++) {
                dma_queue.queue[idx_queue] = dma_queue.queue[idx_queue + 1];
            }
        }
        dma_queue.queue[dma_queue.queue_len++] = descr->buf_ptr;
    }
    /* Clear interrupt */
    SLC->int_clr.val = 0xFFFFFFFF;
    /* Enable DMA interrupt */
    enable_interrupts(INT_NUM_SLC);
}

/**
 * @brief Hàm khởi tạo i2s chạy DMA
 * 
 * @return void 
 */
ICACHE_FLASH_ATTR void i2s_dma_init(i2s_port_t i2s_num, i2s_config_t *i2s_config, i2s_pin_config_t *pins) {
    /* Khởi tạo DMA và I2S */
    slc_init(dma_isr_handler, 0);
    i2s_init(i2s_num, i2s_config, pins);
}

/**
 * @brief Hàm cho phép chạy I2S và DMA
 * 
 * @return void 
 */
ICACHE_FLASH_ATTR void i2s_dma_start(i2s_port_t i2s_num) {
    init_descriptors_list();
    slc_start(dma_block_list);
    i2s_start(i2s_num);
    BITS_LOGD("I2S: conf=%X int_clr=%X int_ena=%X fifo_conf=%X conf_chan=%X rx_eof_num=%X\r\n", I2S[0]->conf.val, I2S[0]->int_clr.val, I2S[0]->int_ena.val, I2S[0]->fifo_conf.val, I2S[0]->conf_chan.val, I2S[0]->rx_eof_num);
}

/**
 * @brief Hàm truyền I2S qua DMA
 * 
 * @param frames frame i2s, mỗi frame mono là (1 x int16_t), stereo là (2 x int16_t)
 * @param frames_len độ dài frame
 * @return void 
 */
ICACHE_FLASH_ATTR void i2s_dma_write(int16_t *frames, uint16_t frames_len) {
    uint32_t timeout_queue = 1000;
    while(timeout_queue--) {
        if(dma_queue.queue_len > 0) {
            /* Disable DMA interrupt */
            disable_interrupts(INT_NUM_SLC);
            /* Lấy ra phần tử đầu */
            uint32_t *item = dma_queue.queue[0];
            /* Enable DMA interrupt */
            enable_interrupts(INT_NUM_SLC);
            dma_queue.queue_len--;
            /* Dồn Queue lên đầu */
            for(uint16_t idx_queue = 0; idx_queue < dma_queue.queue_len; idx_queue++) {
                dma_queue.queue[idx_queue] = dma_queue.queue[idx_queue + 1];
            }
            /* Đưa dữ liệu vào buffer */
            for(uint16_t idx_data = 0; idx_data < frames_len; idx_data++) {
                uint16_t v1 = (uint16_t)(*frames++);
                uint16_t v2 = (uint16_t)(*frames++);
                item[idx_data] = (v1 << 16) | v2;
            }
            break;
        }
    }
}
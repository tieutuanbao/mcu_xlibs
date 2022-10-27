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

/* Cấu trúc queue */
typedef struct struct_queue {
    void *queue[DMA_QUEUE_SIZE];
    uint8_t queue_len;
} queue_t;

struct {
    /* Descriptor Buffer vòng DMA */
    volatile dma_descriptor_t dma_block_list[DMA_QUEUE_SIZE];
    /* Buffer DMA */
    volatile uint32_t dma_buffer[DMA_QUEUE_SIZE][DMA_BUFFER_SIZE];
    volatile queue_t dma_queue;
    
    uint32_t *curr_buf;
    uint32_t curr_buf_pos;               // Position in the current buffer
} i2s_dma;



/**
 * @brief Khởi tạo Deskcriptor
 * 
 * @return void 
 */
void init_descriptors_list() {
    memset((void *)i2s_dma.dma_buffer, 0, sizeof(i2s_dma.dma_buffer));
    for (int i = 0; i < DMA_QUEUE_SIZE; i++) {
        i2s_dma.dma_block_list[i].owner = 1;
        i2s_dma.dma_block_list[i].eof = 1;
        i2s_dma.dma_block_list[i].sub_sof = 0;
        i2s_dma.dma_block_list[i].unused = 0;
        i2s_dma.dma_block_list[i].buf_ptr = (uint32_t *)(&i2s_dma.dma_buffer[i][0]);
        i2s_dma.dma_block_list[i].datalen = DMA_BUFFER_SIZE * 4;
        i2s_dma.dma_block_list[i].blocksize = DMA_BUFFER_SIZE * 4;
        if (i == (DMA_QUEUE_SIZE - 1)) {
            i2s_dma.dma_block_list[i].next = &i2s_dma.dma_block_list[0];
        } else {
            i2s_dma.dma_block_list[i].next = &i2s_dma.dma_block_list[i + 1];
        }
    }
}

__attribute__((section(".text"))) void dma_isr_handler(void *args) {
    /* Disable DMA interrupt */
    disable_interrupts(INT_NUM_SLC);
    bool slc_rx_eof = SLC->int_st.rx_eof;
    /* Clear interrupt */
    SLC->int_clr.val = 0xFFFFFFFF;
    if (slc_rx_eof == true) {
        dma_descriptor_t *descr = (dma_descriptor_t *)(SLC->rx_eof_des_addr);
        memset((void *)descr->buf_ptr, 0x55, DMA_BUFFER_SIZE * 4);
        if (i2s_dma.dma_queue.queue_len >= (DMA_QUEUE_SIZE - 1)) {
            /* Lấy 1 phần tử đầu Queue */
            i2s_dma.dma_queue.queue_len--;
            /* Dồn Queue lên đầu */
            for(uint16_t idx_queue = 0; idx_queue < i2s_dma.dma_queue.queue_len; idx_queue++) {
                i2s_dma.dma_queue.queue[idx_queue] = i2s_dma.dma_queue.queue[idx_queue + 1];
            }
        }
        i2s_dma.dma_queue.queue[i2s_dma.dma_queue.queue_len++] = descr->buf_ptr;
    }
    /* Enable DMA interrupt */
    enable_interrupts(INT_NUM_SLC);
}

/**
 * @brief Hàm khởi tạo i2s chạy DMA
 * 
 * @return void 
 */
void i2s_dma_init(i2s_port_t i2s_num, i2s_config_t *i2s_config, i2s_pin_config_t *pins) {
    /* Khởi tạo DMA và I2S */
    slc_init(dma_isr_handler, 0);
    i2s_init(i2s_num, i2s_config, pins);
}

/**
 * @brief Hàm cho phép chạy I2S và DMA
 * 
 * @return void 
 */
void i2s_dma_start(i2s_port_t i2s_num) {
    init_descriptors_list();
    slc_start(i2s_dma.dma_block_list);
    i2s_start(i2s_num);
}

/**
 * @brief Hàm dừng I2S và DMA
 * 
 * @return void 
 */
void i2s_dma_stop(i2s_port_t i2s_num) {
    slc_stop();
    i2s_stop(i2s_num);
}
/**
 * @brief Hàm truyền I2S qua DMA
 * 
 * @param frames frame i2s, mỗi frame mono là (1 x int16_t), stereo là (2 x int16_t)
 * @param frames_len độ dài frame
 * @return void 
 */
__attribute__((section(".text"))) void i2s_dma_write(int16_t *frames, uint16_t frames_len) {
    uint32_t timeout_queue = 10000000;
    while(timeout_queue--) {
        if(i2s_dma.dma_queue.queue_len > 0) {
            timeout_queue = 10000000;
            while((frames_len > 0) && (timeout_queue--)){
                if((i2s_dma.curr_buf_pos == DMA_BUFFER_SIZE) || (i2s_dma.curr_buf == 0)){
                    /* Disable DMA interrupt */
                    disable_interrupts(INT_NUM_SLC);
                    /* Lấy ra phần tử đầu */
                    i2s_dma.curr_buf = i2s_dma.dma_queue.queue[0];
                    i2s_dma.dma_queue.queue_len--;
                    /* Dồn Queue lên đầu */
                    for(uint16_t idx_queue = 0; idx_queue < i2s_dma.dma_queue.queue_len; idx_queue++) {
                        i2s_dma.dma_queue.queue[idx_queue] = i2s_dma.dma_queue.queue[idx_queue + 1];
                    }
                    /* Enable DMA interrupt */
                    enable_interrupts(INT_NUM_SLC);
                    /* Reset vị trí in buf */
                    i2s_dma.curr_buf_pos = 0;
                }
                /* Đưa dữ liệu vào buffer */
                uint16_t available = (DMA_BUFFER_SIZE - i2s_dma.curr_buf_pos);
                if(available > frames_len) available = frames_len;
                for(; available > 0; available--) {
                    uint32_t v1 = (uint16_t)(*frames++);
                    uint32_t v2 = (uint16_t)(*frames++);
                    i2s_dma.curr_buf[i2s_dma.curr_buf_pos++] = ((v1 << 16) | v2);
                    frames_len--;
                }
            }
            return;
        }
    }
}
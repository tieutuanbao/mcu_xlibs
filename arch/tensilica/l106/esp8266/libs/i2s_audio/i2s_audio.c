#include "i2s_audio.h"
#include "common_macros.h"
#include "esp8266_interrupt.h"
#include "esp8266_i2s.h"
#include "esp8266_slc.h"

#define DMA_BUFFER_SIZE         512
#define DMA_QUEUE_SIZE          4

/* Descriptor Buffer vòng DMA */
static dma_descriptor_t dma_block_list[DMA_QUEUE_SIZE];

/* Buffer DMA */
static uint8_t dma_buffer[DMA_QUEUE_SIZE][DMA_BUFFER_SIZE];

/* Cấu trúc queue */
typedef struct struct_queue {
    void *queue[DMA_QUEUE_SIZE];
    volatile uint8_t queue_len;
} queue_t;

queue_t dma_queue;

/**
 * @brief Khởi tạo Deskcriptor
 * 
 * @return FUNC_ON_FLASH 
 */
FUNC_ON_FLASH void init_descriptors_list() {
    memset(dma_buffer, 0, DMA_QUEUE_SIZE * DMA_BUFFER_SIZE);

    for (int i = 0; i < DMA_QUEUE_SIZE; i++) {
        dma_block_list[i].owner = 1;
        dma_block_list[i].eof = 1;
        dma_block_list[i].sub_sof = 0;
        dma_block_list[i].unused = 0;
        dma_block_list[i].buf_ptr = dma_buffer[i];
        dma_block_list[i].datalen = DMA_BUFFER_SIZE;
        dma_block_list[i].blocksize = DMA_BUFFER_SIZE;
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
FUNC_ON_RAM inline dma_descriptor_t *i2s_dma_get_eof_descriptor()
{
    return (dma_descriptor_t*)SLC->rx_eof_des_addr;
}

/**
 * @brief Kiểm tra ngắt EOF
 * 
 * @return bool : true = Có ngắt EOF
 */
FUNC_ON_RAM bool i2s_dma_is_eof_interrupt() {
    if(SLC->int_st.val & SLC_INT_STATUS_RX_EOF) return true;
    return false;
}

FUNC_ON_RAM void dma_isr_handler(void *args) {
    /* Disable DMA interrupt */
    disable_interrupts(INT_NUM_SLC);
    if (i2s_dma_is_eof_interrupt()) {
        dma_descriptor_t *descr = i2s_dma_get_eof_descriptor();
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
FUNC_ON_FLASH void i2s_dma_init(i2s_dma_config_t *i2s_config) {
    /* Khởi tạo DMA và I2S */
    slc_init(dma_isr_handler, 0);
    i2s_init(i2s_freq_to_clock_div(11025 * 1 * 16), (i2s_pins_t){.clock = 1, .data = 1, .ws = 1});
    BITS_LOG("i2s_audio_init ok!\r\n");
}

/**
 * @brief Hàm cho phép chạy I2S và DMA
 * 
 * @return void 
 */
FUNC_ON_FLASH void i2s_dma_start() {
    init_descriptors_list();
    slc_start(dma_block_list);
    i2s_start();
}

/**
 * @brief Hàm truyền I2S qua DMA
 * 
 * @param file 
 * @return FUNC_ON_FLASH 
 */
FUNC_ON_FLASH void i2s_audio_loop(uint8_t *p_data, uint16_t data_len) {
    uint32_t timeout_queue = 1000;
    while(timeout_queue--) {
        if(dma_queue.queue_len != 0){
            /* Disable DMA interrupt */
            disable_interrupts(INT_NUM_SLC);
            /* Lấy ra phần tử đầu */
            uint8_t *item = dma_queue.queue[0];
            dma_queue.queue_len--;
            /* Dồn Queue lên đầu */
            for(uint16_t idx_queue = 0; idx_queue < dma_queue.queue_len; idx_queue++) {
                dma_queue.queue[idx_queue] = dma_queue.queue[idx_queue + 1];
            }
            /* Đưa dữ liệu vào buffer */
            for(uint16_t idx_data = 0; idx_data < data_len; idx_data++){
                if(item) item[idx_data] = p_data;
            }
            /* Enable DMA interrupt */
            enable_interrupts(INT_NUM_SLC);
            break;
        }
    }
}
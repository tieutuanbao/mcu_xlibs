/**
 * @file i2s_dma.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __I2S_DMA_H
#define __I2S_DMA_H

#include "common_macros.h"
#include "esp8266_i2s.h"
#include "c_types.h"

#define DMA_BUFFER_SIZE         128
#define DMA_QUEUE_SIZE          4

ICACHE_FLASH_ATTR void i2s_dma_init(i2s_port_t i2s_num, i2s_config_t *i2s_config, i2s_pin_config_t *pins);
ICACHE_FLASH_ATTR void i2s_dma_start(i2s_port_t i2s_num);
ICACHE_FLASH_ATTR void i2s_dma_write(int16_t *frames, uint16_t frames_len);


#endif /* __I2S_DMA_H */
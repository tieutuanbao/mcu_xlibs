/**
 * @file esp8266_regs.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ESP8266_REGS_H
#define __ESP8266_REGS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define UART0_BASE      0x60000000
#define SPI_BASE        0x60000200
#define GPIO_BASE       0x60000300
#define RTC_BASE        0x60000700
#define IOMUX_BASE      0x60000800
#define SLC_BASE        0x60000B00
#define I2S_BASE        0x60000E00
#define UART1_BASE      0x60000F00

#define MASK_BIT(n)     (1 << (n))

#define CACHE_FLASH_CTRL_REG    (*((volatile uint32_t *)(0x3ff00000 + 0x0c)))
#define CACHE_READ_EN           (8)

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif
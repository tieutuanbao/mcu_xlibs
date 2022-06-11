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


#define GPIO_BASE       0x60000300
#define RTC_BASE        0x60000700
#define IOMUX_BASE      0x60000800
#define I2S_BASE        0x60000e00

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif
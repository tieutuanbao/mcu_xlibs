/**
 * @file esp8266_rtc.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __ESP8266_RTC_H
#define __ESP8266_RTC_H

#include <stdint.h>
#include "esp8266_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTC ((volatile rtc_t *)(RTC_BASE))

typedef struct struct_rtc{
    volatile uint32_t ctrl0;            // 0x00
    volatile uint32_t counter_alarm;    // 0x04
    volatile uint32_t reset_reason0;    // 0x08       //fixme: need better name
    volatile uint32_t _unknownc;        // 0x0c
    volatile uint32_t _unknown10;       // 0x10
    volatile uint32_t reset_reason1;    // 0x14       //fixme: need better name
    volatile uint32_t reset_reason2;    // 0x18       //fixme: need better name
    volatile uint32_t counter;          // 0x1c
    volatile uint32_t int_set;          // 0x20
    volatile uint32_t int_clear;        // 0x24
    volatile uint32_t int_enable;       // 0x28
    volatile uint32_t _unknown2c;       // 0x2c
    volatile uint32_t scratch[4];       // 0x30 - 3c
    volatile uint32_t _unknown40;       // 0x40
    volatile uint32_t _unknown44;       // 0x44
    volatile uint32_t _unknown48;       // 0x48
    volatile uint32_t _unknown4c[7];    // 0x4c - 0x64
    volatile uint32_t gpio_out;         // 0x68
    volatile uint32_t _unknown6c[2];    // 0x6c - 0x70
    volatile uint32_t gpio_enable;      // 0x74
    volatile uint32_t _unknown80[5];    // 0x78 - 0x88
    volatile uint32_t gpio_in;          // 0x8c
    volatile uint32_t gpio_conf;        // 0x90
    volatile uint32_t gpio_cfg[6];      // 0x94 - 0xa8
} rtc_t;


#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* __ESP8266_RTC_H */
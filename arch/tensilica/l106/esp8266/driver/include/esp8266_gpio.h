#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>
#include "c_types.h"
#include "common.h"

#define GPIO_PIN_0        0
#define GPIO_PIN_1        1
#define GPIO_PIN_2        2
#define GPIO_PIN_3        3
#define GPIO_PIN_4        4
#define GPIO_PIN_5        5
#define GPIO_PIN_6        6
#define GPIO_PIN_7        7
#define GPIO_PIN_8        8
#define GPIO_PIN_9        9
#define GPIO_PIN_10       10
#define GPIO_PIN_11       11
#define GPIO_PIN_12       12
#define GPIO_PIN_13       13
#define GPIO_PIN_14       14
#define GPIO_PIN_15       15
#define GPIO_PIN_16       16

typedef enum {
    GPIO_MODE_IN            =   0,
    GPIO_MODE_IPU           =   2,
    GPIO_MODE_IPD16         =   4,      // only possible for pin16
    GPIO_MODE_OUT_OD        =   3,
    GPIO_MODE_OUT_PP        =   1,
    GPIO_MODE_F0            =   8,
    GPIO_MODE_F1            =   0x18,
    GPIO_MODE_F2            =   0x28,
    GPIO_MODE_F3            =   0x38,
    GPIO_MODE_F4            =   0x48,
    GPIO_MODE_SPECIAL       =   0xF8,      // defaults to the usable BUSes uart0rx/tx uart1tx and hspi
    GPIO_MODE_WPU           =   5,
    GPIO_MODE_WPD           =   7
} gpio_mode_t;

extern volatile uint32_t* const esp8266_gpioToFn[16];
void ICACHE_FLASH_ATTR esp_gpio_config(uint8_t gpio_pin, gpio_mode_t gpio_mode);

#endif
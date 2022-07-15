/**
 * @file esp8266_gpio.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ESP8266_GPIO_H
#define __ESP8266_GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include "esp8266_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO                        ((volatile gpio_t *)(GPIO_BASE))

/**
 * @brief Cấu trúc thanh ghi GPIO ESP8266
 * 
 */
typedef struct struct_gpio {
    volatile uint32_t out;              // offset: 0x00
    volatile uint32_t out_set;          // offset: 0x04
    volatile uint32_t out_clear;        // offset: 0x08
    volatile uint32_t enable_out;       // offset: 0x0c-enable w1ts
    volatile uint32_t enable_out_set;   // offset: 0x10-enable w1tc
    volatile uint32_t enable_out_clear; // offset: 0x14
    volatile uint32_t in;               // offset: 0x18
    volatile uint32_t status;           // offset: 0x1c
    volatile uint32_t status_set;       // offset: 0x20-status w1ts
    volatile uint32_t status_clear;     // offset: 0x24-status w1tc
    volatile union {                    // offset: 0x28 - 0x64
        struct {
            uint32_t source:        1;
            uint32_t reserved1:     1;
            uint32_t driver:        1;
            uint32_t reserved2:     4;
            uint32_t int_type:      3;
            uint32_t wakeup_enable: 1;
            uint32_t reserved3:     21;
        };
        uint32_t val;
    } pin[16];                          
    volatile uint32_t sigma_delta;      // offset: 0x68
    volatile uint32_t rtc_calib;        // offset: 0x6c
    volatile uint32_t rtc_calib_result; // offset: 0x70
} gpio_t;

typedef void (* gpio_int_handler_t)(uint8_t gpio_num);

#ifndef GPIO_PIN_COUNT
#define GPIO_PIN_COUNT              17
#endif

#define GPIO_PIN_DRIVER_MASK        (1U << 2)
#define GPIO_CONF_INTTYPE_POS       7
#define GPIO_CONF_INTTYPE_MASK      (7U << GPIO_CONF_INTTYPE_POS)
#define GPIO_CONF_WKUP_EN_MASK      (1U << 10)

#define RTC_GPIO_IS_VALID_GPIO(gpio_num)     ((gpio_num == 16))    /*!< Check whether it is a valid RTC GPIO number */

/**
 * @brief Typedef lỗi config GPIO
 * 
 */
typedef enum {
    GPIO_OK,
    GPIO_PIN_MASK_ERROR,
    GPIO_PIN_NUMBER_TO_LARGE
} gpio_err_t;
/**
 * @brief Typedef direction IO
 * 
 */
typedef enum {
    GPIO_DIR_DISABLE,
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT,                    // PUSH-PULL
    GPIO_DIR_OPEN_DRAIN                 // Open-Drain
} gpio_dir_t;

/**
 * @brief Typedef pullup control
 * 
 */
typedef enum {
    GPIO_PULLUP_DISABLE = 0x00,
    GPIO_PULLUP_ENABLE = 0x01,
} gpio_pullup_t;

/**
 * @brief Typedef pulldown control
 * 
 */
typedef enum {
    GPIO_PULLDOWN_DISABLE = 0x00,
    GPIO_PULLDOWN_ENABLE = 0x01,
} gpio_pulldown_t;

/**
 * @brief Typedef gpio interrupt type
 * 
 */
typedef enum {
    GPIO_INT_DISABLE       = 0,
    GPIO_INT_RISING        = 1,
    GPIO_INT_FALLING       = 2,
    GPIO_INT_BOTH          = 3,
    GPIO_INT_LOW_LEVEL     = 4,
    GPIO_INT_HIGH_LEVEL    = 5
} gpio_int_type_t;

/**
 * @brief Cấu trúc cấu hình cho gpio
 * 
 */
typedef struct {
    uint32_t pin_bit_mask;
    gpio_dir_t dir;
    gpio_pullup_t pull_up_en;
    gpio_pulldown_t pull_down_en;
    gpio_int_type_t intr_type;
} gpio_config_t;

ICACHE_FLASH_ATTR void gpio_set_interrupt(const uint8_t gpio_num, const gpio_int_type_t int_type, gpio_int_handler_t handler);
ICACHE_FLASH_ATTR void gpio_enable(const uint8_t gpio_num, const gpio_dir_t direction);
ICACHE_FLASH_ATTR void gpio_set_pullup(uint8_t gpio_num, bool enabled, bool enabled_during_sleep);
ICACHE_FLASH_ATTR gpio_err_t gpio_config(gpio_config_t *gpio_config);
ICACHE_FLASH_ATTR void gpio_set_iomux_function(const uint8_t gpio_num, uint32_t func);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* __ESP8266_GPIO_H */
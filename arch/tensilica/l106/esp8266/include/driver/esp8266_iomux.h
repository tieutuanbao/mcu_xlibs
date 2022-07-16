/**
 * @file esp8266_iomux.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ESP8266_IOMUX_H
#define __ESP8266_IOMUX_H

#include <stdint.h>
#include "esp8266_regs.h"
#include "common_macros.h"

#define IOMUX       ((volatile iomux_t*)(IOMUX_BASE))

typedef struct struct_iomux {
    volatile uint32_t conf;    // offset:  0x00
    union {    // offset:  0x04 - 40
        volatile struct {
            uint32_t sleep_oe       : 1;
            uint32_t sleep_sel      : 1;
            uint32_t reserved1      : 1;
            uint32_t sleep_pullup   : 1;
            uint32_t func_low_bit   : 2;
            uint32_t reserved2      : 1;
            uint32_t pullup         : 1;
            uint32_t func_high_bit  : 1;
        };
        volatile struct {
            uint32_t func_low_bit   : 2;
            uint32_t reserved1      : 1;
            uint32_t pulldown       : 1;
            uint32_t reserved2      : 1;
            uint32_t sleep_pulldown : 1;
            uint32_t func_high_bit  : 1;
        } rtc_pin;
        volatile uint32_t val;
    } pin[16];
} iomux_t;

/* Details for CONF register */
#define IOMUX_CONF_SPI0_CLOCK_EQU_SYS_CLOCK  8
#define IOMUX_CONF_SPI1_CLOCK_EQU_SYS_CLOCK  9

/* Details for pin registers */
#define IOMUX_PIN_OUTPUT_ENABLE             (1U << 0)
#define IOMUX_PIN_OUTPUT_ENABLE_SLEEP       (1U << 1)
#define IOMUX_PIN_PULLDOWN_SLEEP            (1U << 2)
#define IOMUX_PIN_PULLUP_SLEEP              (1U << 3)
#define IOMUX_PIN_FUNC_LOW_POS              4
#define IOMUX_PIN_FUNC_LOW_MASK             (3U << IOMUX_PIN_FUNC_LOW_POS)
#define IOMUX_PIN_FUNC_LOW                  IOMUX_PIN_FUNC_LOW_MASK
#define IOMUX_PIN_PULLDOWN                  (1U << 6)
#define IOMUX_PIN_PULLUP                    (1U << 7)
#define IOMUX_PIN_FUNC_HIGH                 (1U << 8)

#define IOMUX_PIN_FUNC_POS                  4
#define IOMUX_PIN_FUNC_MASK                 (0x00000013 << IOMUX_PIN_FUNC_POS)

#define IOMUX_FUNC(val)                     ((((val) & 0x04) << 2)|((val) & 0x03) << 4)

#define IOMUX_GPIO0                         IOMUX.pin[12]
#define IOMUX_GPIO1                         IOMUX.pin[5]
#define IOMUX_GPIO2                         IOMUX.pin[13]
#define IOMUX_GPIO3                         IOMUX.pin[4]
#define IOMUX_GPIO4                         IOMUX.pin[14]
#define IOMUX_GPIO5                         IOMUX.pin[15]
#define IOMUX_GPIO6                         IOMUX.pin[6]
#define IOMUX_GPIO7                         IOMUX.pin[7]
#define IOMUX_GPIO8                         IOMUX.pin[8]
#define IOMUX_GPIO9                         IOMUX.pin[9]
#define IOMUX_GPIO10                        IOMUX.pin[10]
#define IOMUX_GPIO11                        IOMUX.pin[11]
#define IOMUX_GPIO12                        IOMUX.pin[0]
#define IOMUX_GPIO13                        IOMUX.pin[1]
#define IOMUX_GPIO14                        IOMUX.pin[2]
#define IOMUX_GPIO15                        IOMUX.pin[3]

/**
 * @brief Danh sách function GPIO IOMUX
 * 
 */
#define IOMUX_GPIO0_FUNC_GPIO              IOMUX_FUNC(0)
#define IOMUX_GPIO0_FUNC_SPI0_CS2          IOMUX_FUNC(1)
#define IOMUX_GPIO0_FUNC_CLOCK_OUT         IOMUX_FUNC(4)

#define IOMUX_GPIO1_FUNC_UART0_TXD         IOMUX_FUNC(0)
#define IOMUX_GPIO1_FUNC_SPI0_CS1          IOMUX_FUNC(1)
#define IOMUX_GPIO1_FUNC_GPIO              IOMUX_FUNC(3)
#define IOMUX_GPIO1_FUNC_CLOCK_RTC_BLINK   IOMUX_FUNC(4)

#define IOMUX_GPIO2_FUNC_GPIO              IOMUX_FUNC(0)
#define IOMUX_GPIO2_FUNC_I2SO_WS           IOMUX_FUNC(1)
#define IOMUX_GPIO2_FUNC_UART1_TXD         IOMUX_FUNC(2)
#define IOMUX_GPIO2_FUNC_UART0_TXD         IOMUX_FUNC(4)

#define IOMUX_GPIO3_FUNC_UART0_RXD         IOMUX_FUNC(0)
#define IOMUX_GPIO3_FUNC_I2SO_DATA         IOMUX_FUNC(1)
#define IOMUX_GPIO3_FUNC_GPIO              IOMUX_FUNC(3)
#define IOMUX_GPIO3_FUNC_CLOCK_XTAL_BLINK  IOMUX_FUNC(4)

#define IOMUX_GPIO4_FUNC_GPIO              IOMUX_FUNC(0)
#define IOMUX_GPIO4_FUNC_CLOCK_XTAL        IOMUX_FUNC(1)

#define IOMUX_GPIO5_FUNC_GPIO              IOMUX_FUNC(0)
#define IOMUX_GPIO5_FUNC_CLOCK_RTC         IOMUX_FUNC(1)

#define IOMUX_GPIO6_FUNC_SD_CLK            IOMUX_FUNC(0)
#define IOMUX_GPIO6_FUNC_SPI0_CLK          IOMUX_FUNC(1)
#define IOMUX_GPIO6_FUNC_GPIO              IOMUX_FUNC(3)
#define IOMUX_GPIO6_FUNC_UART1_CTS         IOMUX_FUNC(4)

#define IOMUX_GPIO7_FUNC_SD_DATA0          IOMUX_FUNC(0)
#define IOMUX_GPIO7_FUNC_SPI0_Q_MISO       IOMUX_FUNC(1)
#define IOMUX_GPIO7_FUNC_GPIO              IOMUX_FUNC(3)
#define IOMUX_GPIO7_FUNC_UART1_TXD         IOMUX_FUNC(4)

#define IOMUX_GPIO8_FUNC_SD_DATA1          IOMUX_FUNC(0)
#define IOMUX_GPIO8_FUNC_SPI0_D_MOSI       IOMUX_FUNC(1)
#define IOMUX_GPIO8_FUNC_GPIO              IOMUX_FUNC(3)
#define IOMUX_GPIO8_FUNC_UART1_RXD         IOMUX_FUNC(4)

#define IOMUX_GPIO9_FUNC_SD_DATA2          IOMUX_FUNC(0)
#define IOMUX_GPIO9_FUNC_SPI0_HD           IOMUX_FUNC(1)
#define IOMUX_GPIO9_FUNC_GPIO              IOMUX_FUNC(3)
#define IOMUX_GPIO9_FUNC_SPI1_HD           IOMUX_FUNC(4)

#define IOMUX_GPIO10_FUNC_SD_DATA3         IOMUX_FUNC(0)
#define IOMUX_GPIO10_FUNC_SPI0_WP          IOMUX_FUNC(1)
#define IOMUX_GPIO10_FUNC_GPIO             IOMUX_FUNC(3)
#define IOMUX_GPIO10_FUNC_SPI1_WP          IOMUX_FUNC(4)

#define IOMUX_GPIO11_FUNC_SD_CMD           IOMUX_FUNC(0)
#define IOMUX_GPIO11_FUNC_SPI0_CS0         IOMUX_FUNC(1)
#define IOMUX_GPIO11_FUNC_GPIO             IOMUX_FUNC(3)
#define IOMUX_GPIO11_FUNC_UART1_RTS        IOMUX_FUNC(4)

#define IOMUX_GPIO12_FUNC_MTDI             IOMUX_FUNC(0)
#define IOMUX_GPIO12_FUNC_I2SI_DATA        IOMUX_FUNC(1)
#define IOMUX_GPIO12_FUNC_SPI1_Q_MISO      IOMUX_FUNC(2)
#define IOMUX_GPIO12_FUNC_GPIO             IOMUX_FUNC(3)
#define IOMUX_GPIO12_FUNC_UART0_DTR        IOMUX_FUNC(4)

#define IOMUX_GPIO13_FUNC_MTCK             IOMUX_FUNC(0)
#define IOMUX_GPIO13_FUNC_I2SI_BCK         IOMUX_FUNC(1)
#define IOMUX_GPIO13_FUNC_SPI1_D_MOSI      IOMUX_FUNC(2)
#define IOMUX_GPIO13_FUNC_GPIO             IOMUX_FUNC(3)
#define IOMUX_GPIO13_FUNC_UART0_CTS        IOMUX_FUNC(4)

#define IOMUX_GPIO14_FUNC_MTMS             IOMUX_FUNC(0)
#define IOMUX_GPIO14_FUNC_I2SI_WS          IOMUX_FUNC(1)
#define IOMUX_GPIO14_FUNC_SPI1_CLK         IOMUX_FUNC(2)
#define IOMUX_GPIO14_FUNC_GPIO             IOMUX_FUNC(3)
#define IOMUX_GPIO14_FUNC_UART0_DSR        IOMUX_FUNC(4)

#define IOMUX_GPIO15_FUNC_MTDO             IOMUX_FUNC(0)
#define IOMUX_GPIO15_FUNC_I2SO_BCK         IOMUX_FUNC(1)
#define IOMUX_GPIO15_FUNC_SPI1_CS0         IOMUX_FUNC(2)
#define IOMUX_GPIO15_FUNC_GPIO             IOMUX_FUNC(3)
#define IOMUX_GPIO15_FUNC_UART0_RTS        IOMUX_FUNC(4)

extern const uint8_t iomux_2_gpio[16];
extern const uint8_t gpio_2_iomux[16];


ICACHE_FLASH_ATTR volatile uint32_t * gpio_iomux_reg(const uint8_t idx_gpio);
ICACHE_FLASH_ATTR void iomux_set_pullup_flags(uint8_t iomux_num, uint32_t pullup_flags);
ICACHE_FLASH_ATTR void iomux_set_gpio_function(uint8_t idx_gpio, bool output_enable);
ICACHE_FLASH_ATTR void iomux_set_function(uint8_t iomux_num, uint32_t iomux_func);
ICACHE_FLASH_ATTR void iomux_set_direction_flags(uint8_t iomux_num, uint32_t dir_flags);

#endif /* __ESP8266_IOMUX_H */

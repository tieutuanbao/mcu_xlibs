#include "esp8266_gpio.h"
#include "esp8266_peri.h"

volatile uint32_t* const esp8266_gpioToFn[16] = { &GPF0, &GPF1, &GPF2, &GPF3, &GPF4, &GPF5, &GPF6, &GPF7, &GPF8, &GPF9, &GPF10, &GPF11, &GPF12, &GPF13, &GPF14, &GPF15 };

void ICACHE_FLASH_ATTR esp_gpio_config(uint8_t gpio_pin, gpio_mode_t gpio_mode) {
    if (gpio_pin < 16) {
        if (gpio_mode == GPIO_MODE_SPECIAL) {
            GPC(gpio_pin) = (GPC(gpio_pin) & (0xF << GPCI));    // SOURCE(GPIO) | DRIVER(NORMAL) | INT_TYPE(UNCHANGED) | WAKEUP_ENABLE(DISABLED)
            GPEC = (1 << gpio_pin);                             // Disable
            GPF(gpio_pin) = GPFFS(GPFFS_BUS(gpio_pin));         // Set gpio_mode to BUS (RX0, TX0, TX1, SPI, HSPI or CLK depending in the gpio_pin)
            if (gpio_pin == 3){
                GPF(gpio_pin) |= (1 << GPFPU);                  // enable pullup on RX
            }
        }
        else if (gpio_mode & GPIO_MODE_F0) {
            GPC(gpio_pin) = (GPC(gpio_pin) & (0xF << GPCI));    // SOURCE(GPIO) | DRIVER(NORMAL) | INT_TYPE(UNCHANGED) | WAKEUP_ENABLE(DISABLED)
            GPEC = (1 << gpio_pin);                             // Disable
            GPF(gpio_pin) = GPFFS((gpio_mode >> 4) & 0x07);
            if (gpio_pin == 13 && gpio_mode == GPIO_MODE_F4) {
                GPF(gpio_pin) |= (1 << GPFPU);                  // enable pullup on RX
            }
        }
        else if (gpio_mode == GPIO_MODE_OUT_PP || gpio_mode == GPIO_MODE_OUT_OD) {
            GPF(gpio_pin) = GPFFS(GPFFS_GPIO(gpio_pin));        // Set gpio_mode to GPIO
            GPC(gpio_pin) = (GPC(gpio_pin) & (0xF << GPCI));    // SOURCE(GPIO) | DRIVER(NORMAL) | INT_TYPE(UNCHANGED) | WAKEUP_ENABLE(DISABLED)
            if (gpio_mode == GPIO_MODE_OUT_OD) {
                GPC(gpio_pin) |= (1 << GPCD);
            }
            GPES = (1 << gpio_pin); // Enable
        }
        else if (gpio_mode == GPIO_MODE_IN || gpio_mode == GPIO_MODE_IPU) {
            GPF(gpio_pin) = GPFFS(GPFFS_GPIO(gpio_pin));                   // Set gpio_mode to GPIO
            GPEC = (1 << gpio_pin);                                        // Disable
            GPC(gpio_pin) = (GPC(gpio_pin) & (0xF << GPCI)) | (1 << GPCD); // SOURCE(GPIO) | DRIVER(OPEN_DRAIN) | INT_TYPE(UNCHANGED) | WAKEUP_ENABLE(DISABLED)
            if (gpio_mode == GPIO_MODE_IPU) {
                GPF(gpio_pin) |= (1 << GPFPU); // Enable  Pullup
            }
        }
        else if (gpio_mode == GPIO_MODE_WPU || gpio_mode == GPIO_MODE_WPD) {
            GPF(gpio_pin) = GPFFS(GPFFS_GPIO(gpio_pin)); // Set gpio_mode to GPIO
            GPEC = (1 << gpio_pin);                      // Disable
            if (gpio_mode == GPIO_MODE_WPU)
            {
                GPF(gpio_pin) |= (1 << GPFPU);                            // Enable  Pullup
                GPC(gpio_pin) = (1 << GPCD) | (4 << GPCI) | (1 << GPCWE); // SOURCE(GPIO) | DRIVER(OPEN_DRAIN) | INT_TYPE(LOW) | WAKEUP_ENABLE(ENABLED)
            }
            else
            {
                GPF(gpio_pin) |= (1 << GPFPD);                            // Enable  Pulldown
                GPC(gpio_pin) = (1 << GPCD) | (5 << GPCI) | (1 << GPCWE); // SOURCE(GPIO) | DRIVER(OPEN_DRAIN) | INT_TYPE(HIGH) | WAKEUP_ENABLE(ENABLED)
            }
        }
    }
    else if (gpio_pin == 16) {
        GPF16 = GP16FFS(GPFFS_GPIO(gpio_pin)); // Set gpio_mode to GPIO
        GPC16 = 0;
        if (gpio_mode == GPIO_MODE_IN || gpio_mode == GPIO_MODE_IPD16) {
            if (gpio_mode == GPIO_MODE_IPD16) {
                GPF16 |= (1 << GP16FPD); // Enable Pulldown
            }
            GP16E &= ~1;
        }
        else if (gpio_mode == GPIO_MODE_OUT_PP) {
            GP16E |= 1;
        }
    }
}
/**
 * @file esp8266_GPIO->c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "common_macros.h"
#include "esp8266_GPIO.h"
#include "esp8266_rtc.h"
#include "esp8266_iomux.h"
#include "esp8266_interrupt.h"

/**
 * @brief Mảng handler gpio
 * 
 */
static gpio_int_handler_t gpio_intr_handlers[16] = { 0 };

/**
 * @brief Hàm phục vụ ngắt GPIO
 * 
 */
void __attribute__((weak)) gpio_int_isr(void *arg) {
    gpio_int_handler_t handler;
    uint8_t idx_gpio;
    /* Lấy tín hiệu ngắt các IO */
    uint32_t status_reg = GPIO->status;
    GPIO->status_clear = status_reg;
    /* Kiểm tra tín hiệu ngắt từng GPIO */
    for(idx_gpio = 0; idx_gpio < 16; idx_gpio++){
        if((status_reg & (1U << idx_gpio)) != 0){
            /* reset cờ ngắt */
            status_reg &= ~(1U << idx_gpio);
            if (GPIO->pin[idx_gpio].val & GPIO_CONF_INTTYPE_MASK) {
                handler = gpio_intr_handlers[idx_gpio];
                if (handler) {
                    handler(idx_gpio);
                }
            }
        }
    }
}

/**
 * @brief Hàm cấu hình ngắt GPIO
 * 
 * @param gpio_num Index của GPIO
 * @param int_type Chọn kiểu ngắt GPIO
 * @param handler Handler khi có sự kiện ngắt
 */
ICACHE_FLASH_ATTR void gpio_set_interrupt(const uint8_t gpio_num, const gpio_int_type_t int_type, gpio_int_handler_t handler) {
    /* Config handler */
    gpio_intr_handlers[gpio_num] = handler;

    GPIO->pin[gpio_num].val = GPIO->pin[gpio_num].val | (int_type << GPIO_CONF_INTTYPE_POS);
    if (int_type != GPIO_INT_DISABLE) {
        register_interrupts(INT_NUM_GPIO, gpio_int_isr, NULL);
        enable_interrupts(1<<INT_NUM_GPIO);
    }
}

ICACHE_FLASH_ATTR void gpio_enable(const uint8_t gpio_num, const gpio_dir_t direction) {
    if (gpio_num == 16) {
        RTC->gpio_cfg[3] = (RTC->gpio_cfg[3] & 0xffffffbc) | 1;
        RTC->gpio_conf = (RTC->gpio_conf & 0xfffffffe) | 0;
        switch (direction) {
            case GPIO_DIR_INPUT:{
                RTC->gpio_enable = (RTC->gpio_out & 0xfffffffe);
                break;
            }
            case GPIO_DIR_OUTPUT:
            case GPIO_DIR_OPEN_DRAIN:{
                RTC->gpio_enable = (RTC->gpio_out & 0xfffffffe) | 1;
                break;
            }
        }
        return;
    }
    switch (direction) {
        case GPIO_DIR_INPUT:{
            GPIO->enable_out_clear = (1U << gpio_num);
            iomux_set_gpio_function(gpio_num, false);
            break;
        }
        case GPIO_DIR_OUTPUT:{
            GPIO->pin[gpio_num].driver = 0;
            GPIO->enable_out_set = (1U << gpio_num);
            iomux_set_gpio_function(gpio_num, true);
            break;
        }
        case GPIO_DIR_OPEN_DRAIN:{
            GPIO->pin[gpio_num].driver |= 1;
            GPIO->enable_out_set = (1U << gpio_num);
            iomux_set_gpio_function(gpio_num, true);
            break;
        }
    }
}

ICACHE_FLASH_ATTR void gpio_set_pullup(uint8_t gpio_num, bool enabled, bool enabled_during_sleep) {
    uint32_t flags = 0;

    if (enabled) {
        flags |= IOMUX_PIN_PULLUP;
    }
    if (enabled_during_sleep) {
        flags |= IOMUX_PIN_PULLUP_SLEEP;
    }
    iomux_set_pullup_flags(gpio_2_iomux[gpio_num], flags);
}

ICACHE_FLASH_ATTR gpio_err_t gpio_config(gpio_config_t *gpio_config) {
    uint32_t gpio_mask = gpio_config->pin_bit_mask;

    if (gpio_config->pin_bit_mask == 0) {
        return GPIO_PIN_MASK_ERROR;
    }
    if (gpio_config->pin_bit_mask >= (1U << GPIO_PIN_COUNT)) {
        return GPIO_PIN_NUMBER_TO_LARGE;
    }
    for(uint8_t idx_gpio = 0; idx_gpio < GPIO_PIN_COUNT; idx_gpio++){
        if((gpio_mask & (1U << idx_gpio))){
            if(RTC_GPIO_IS_VALID_GPIO(idx_gpio)){
                if(gpio_config->dir == GPIO_DIR_OUTPUT){
                    RTC->gpio_cfg[3] =  (((RTC->gpio_cfg[3] & (uint32_t)0xFFFFFFBC)) | 1U);
                }
                GPIO->pin[idx_gpio].driver = 0;
                /* Chỉ cấu hình pulldown với GPIO 16 */
                if (gpio_config->pull_down_en) {
                    IOMUX->pin[gpio_2_iomux[idx_gpio]].rtc_pin.pulldown = 1;
                } else {
                    IOMUX->pin[gpio_2_iomux[idx_gpio]].rtc_pin.pulldown = 0;
                }
            }
            else {
                /* Cấu hình in/out */
                if(gpio_config->dir == GPIO_DIR_OUTPUT) {
                    GPIO->enable_out_set = (1U << idx_gpio);
                }
                if ((gpio_config->dir == GPIO_DIR_OPEN_DRAIN) && !RTC_GPIO_IS_VALID_GPIO(idx_gpio)) {
                    GPIO->pin[idx_gpio].driver = 1;
                }
                else {
                    GPIO->pin[idx_gpio].driver = 0;
                }
                /* Chỉ cấu hình pullup khi không phải GPIO 16 */
                if (gpio_config->pull_up_en) {
                    IOMUX->pin[gpio_2_iomux[idx_gpio]].pullup = 1;
                } else {
                    IOMUX->pin[gpio_2_iomux[idx_gpio]].pullup = 0;
                }
                /* Cấu hình interrupt */
                GPIO->pin[idx_gpio].int_type = gpio_config->intr_type;
                /**
                 * @brief Những GPIO 0/2/4/5 cần phải đặt thanh ghi func trong iomux thành 0
                 *          Và những GPIO khác cần phải đặt thành 3 để sử dụng chức năng GPIO 
                 */
                if ((1U << idx_gpio) & ((1U) | (1U << 2) | (1U << 4) | (1U << 5))) {
                    IOMUX->pin[gpio_2_iomux[idx_gpio]].rtc_pin.func_low_bit = 0;
                    IOMUX->pin[gpio_2_iomux[idx_gpio]].rtc_pin.func_high_bit = 0;
                } else {
                    IOMUX->pin[gpio_2_iomux[idx_gpio]].func_low_bit = 3;
                    IOMUX->pin[gpio_2_iomux[idx_gpio]].func_high_bit = 0;
                }
            }
        }
    }
    return GPIO_OK;
}

ICACHE_FLASH_ATTR void gpio_set_iomux_function(const uint8_t gpio_num, uint32_t func) {
    uint8_t iomux_num = gpio_2_iomux[gpio_num];
    uint32_t prev = IOMUX->pin[iomux_num].val & ~IOMUX_PIN_FUNC_MASK;
    IOMUX->pin[iomux_num].val = func | prev;
}
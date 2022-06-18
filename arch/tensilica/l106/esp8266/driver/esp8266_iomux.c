/**
 * @file esp8266_iomux.c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "esp8266_iomux.h"

const uint8_t iomux_2_gpio[16] = { 12, 13, 14, 15, 3, 1, 6, 7, 8, 9, 10, 11, 0, 2, 4, 5 };
const uint8_t gpio_2_iomux[16] = { 12, 5, 13, 4, 14, 15, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3 };

uint8_t iomux_to_gpio(const uint8_t iomux_number)
{
    return iomux_2_gpio[iomux_number];
}

/**
 * @brief Lấy iomux cho số index của gpio
 * 
 * @param idx_gpio 0, 1, 2, 3, 4 ....
 * @return volatile* Con trỏ đến IOMUX->pin
 */
ICACHE_FLASH_ATTR volatile uint32_t * gpio_iomux_reg(const uint8_t idx_gpio) {
    return &(IOMUX->pin[gpio_2_iomux[idx_gpio]].val);
}

/**
 * @brief Thiết lập chức năng cho iomux
 * 
 * @param iomux_num Index của thanh ghi iomux, có thể dùng gpio_2_iomux[] để chuyển đổi index GPIO sang index IOMUX
 * @param iomux_func Chức năng GPIO được define dạng  IOMUX_GPIOn_FUNC_xxx (n là index GPIO và xxx là tên chức năng)
 */
ICACHE_FLASH_ATTR void iomux_set_function(uint8_t iomux_num, uint32_t iomux_func) {
    IOMUX->pin[iomux_num].val = iomux_func | (IOMUX->pin[iomux_num].val & (~IOMUX_PIN_FUNC_MASK));
}

ICACHE_FLASH_ATTR void iomux_set_direction_flags(uint8_t iomux_num, uint32_t dir_flags) {
    IOMUX->pin[iomux_num].val = dir_flags | (IOMUX->pin[iomux_num].val & ~(IOMUX_PIN_OUTPUT_ENABLE | IOMUX_PIN_OUTPUT_ENABLE_SLEEP));
}

ICACHE_FLASH_ATTR void iomux_set_pullup_flags(uint8_t iomux_num, uint32_t pullup_flags) {
    IOMUX->pin[iomux_num].val = pullup_flags | (IOMUX->pin[iomux_num].val & ~(IOMUX_PIN_PULLUP | IOMUX_PIN_PULLDOWN | IOMUX_PIN_PULLUP_SLEEP | IOMUX_PIN_PULLDOWN_SLEEP));
}

/**
 * @brief Set một pin cho chức năng GPIO không cần biết trước chính xác mask IOMUX
 *        Hàm này không ảnh hưởng đến cấu hình pullup/pulldown
 *  
 * @param idx_gpio index của gpio
 * @param output_enable Cho phép output
 */
ICACHE_FLASH_ATTR void iomux_set_gpio_function(uint8_t idx_gpio, bool output_enable) {
    const uint8_t iomux_num = gpio_2_iomux[idx_gpio];
    const uint32_t func = (iomux_num > 11) ? IOMUX_FUNC(0) : IOMUX_FUNC(3);
    iomux_set_function(iomux_num, func);
    iomux_set_direction_flags(iomux_num, output_enable ? IOMUX_PIN_OUTPUT_ENABLE : 0);
}

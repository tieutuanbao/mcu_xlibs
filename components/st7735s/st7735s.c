/**
 * @file st7735s.c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h> /* memcpy */
#include "st7735s.h"

st7735s_status_t st7735s_init(st7735s_t *st7735s_obj, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t)) {
    if((drv_spi_write == 0) || (drv_reset_output == 0) || (drv_rs_output == 0) || (drv_delay_ms == 0))return false;

    st7735s_obj->drv_reset_output(false);
    st7735s_obj->drv_delay_ms(100);
    st7735s_obj->drv_reset_output(true);
}

static inline st7735s_status_t st7735s_write_data(st7735s_t *st7735s_obj, uint8_t *data, size_t data_length) {
    st7735s_obj->drv_rs_output(ST7735S_DATA_MODE);
    return st7735s_obj->drv_spi_write(data, data_length);
}

static inline st7735s_status_t st7735s_write_byte_command(st7735s_t *st7735s_obj, s7735s_cmd_t cmd) {
    st7735s_obj->drv_rs_output(ST7735S_COMMAND_MODE);
    return st7735s_obj->drv_spi_write(&cmd, 1);
}

st7735s_status_t st7735s_set_sleep(st7735s_t *st7735s_obj, bool state) {
    st7735s_status_t ret = st7735s_write_byte_command(st7735s_obj, state ? ST7735S_CMD_SLPIN: ST7735S_CMD_SLPOUT);
    st7735s_obj->drv_delay_ms(100);
    return ret;
}

st7735s_status_t st7735s_set_sleep(st7735s_t *st7735s_obj, bool state) {
    st7735s_status_t ret = st7735s_write_byte_command(st7735s_obj, state ? ST7735S_CMD_SLPIN: ST7735S_CMD_SLPOUT);
    st7735s_obj->drv_delay_ms(100);
    return ret;
}

st7735s_status_t st7735s_mem_access(st7735s_t *st7735s_obj, uint8_t st7735s_mem_access_bit) {
    if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_MADCTL) == false) {
        return false;
    }
    if(st7735s_write_data(st7735s_obj, &st7735s_mem_access_bit, 1) == false) {
        return false;
    }
    return true;
}


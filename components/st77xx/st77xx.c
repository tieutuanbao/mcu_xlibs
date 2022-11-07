/**
 * @file st77xx.c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include "st77xx.h"

st77xx_status_t st77xx_write_data(st77xx_t *st77xx_obj, uint8_t *data, size_t data_length) {
    st77xx_obj->drv_rs_output(ST77XX_DATA_MODE);
    return st77xx_obj->drv_spi_write(data, data_length);
}

st77xx_status_t st77xx_write_byte_command(st77xx_t *st77xx_obj, st77xx_cmd_t cmd) {
    st77xx_obj->drv_rs_output(ST77XX_COMMAND_MODE);
    return st77xx_obj->drv_spi_write((uint8_t *)&cmd, 1);
}

void st77XX_execute_cmd_list(st77xx_t *st77xx_obj, const uint8_t *addr) {
    uint8_t numCommands = 0, numArgs = 0;
    uint16_t ms_delay = 0;
    numCommands = *addr++;
    while(numCommands--) {
        uint8_t cmd = *addr++;
        st77xx_write_byte_command(st77xx_obj, (st77xx_cmd_t)cmd);
        numArgs = *addr++;
        // If high bit set, delay follows args
        ms_delay = numArgs & ST77XX_DELAY_FLAG;
        numArgs &= ~ST77XX_DELAY_FLAG;
        if(numArgs) {
            st77xx_write_data(st77xx_obj, (uint8_t*)addr, numArgs);
            addr += numArgs;
        }
        if(ms_delay) {
            ms_delay = *addr++;
            if(ms_delay == 255) ms_delay = 500;
            st77xx_obj->drv_delay_ms(ms_delay);
        }
    }
}

st77xx_status_t st77xx_init(st77xx_t *st77xx_obj, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t)) {
    /* check driver */
    if((drv_spi_write == 0) || (drv_reset_output == 0) || (drv_rs_output == 0) || (drv_delay_ms == 0))return false;
    /* Đăng ký driver */
    st77xx_obj->drv_spi_write = drv_spi_write;
    st77xx_obj->drv_rs_output = drv_rs_output;
    st77xx_obj->drv_reset_output = drv_reset_output;
    st77xx_obj->drv_delay_ms = drv_delay_ms;
    /* Reset phần cứng */
    st77xx_obj->drv_reset_output(false);
    st77xx_obj->drv_delay_ms(150);
    st77xx_obj->drv_reset_output(true);
    return true;
}

st77xx_status_t st77xx_set_sleep(st77xx_t *st77xx_obj, bool state) {
    st77xx_status_t ret = st77xx_write_byte_command(st77xx_obj, state ? ST77XX_CMD_SLPIN: ST77XX_CMD_SLPOUT);
    st77xx_obj->drv_delay_ms(100);
    return ret;
}

st77xx_status_t st77xx_mem_access(st77xx_t *st77xx_obj, uint8_t st77xx_mem_access_bit) {
    if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_MADCTL) == false) {
        return false;
    }
    if(st77xx_write_data(st77xx_obj, &st77xx_mem_access_bit, 1) == false) {
        return false;
    }
    return true;
}

st77xx_status_t st77xx_interface_pixel_format(st77xx_t *st77xx_obj, uint8_t st77xx_interface_pixel_format_bit) {
    /* Kiểm tra giá trị đúng, chỉ một bit duy nhất được cho phép, không được kết hợp các bit */
    switch(st77xx_interface_pixel_format_bit) {
        /* Tham số cho phép */
        case ST77XX_PIXEL_FORMAT_444: break;
        case ST77XX_PIXEL_FORMAT_565: break;
        case ST77XX_PIXEL_FORMAT_666: break;
        /* Tham số không cho phép */
        default: return false;
    }
    if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_COLMOD) == false) {
        return false;
    }
    if(st77xx_write_data(st77xx_obj, &st77xx_interface_pixel_format_bit, 1) == false) {
        return false;
    }
    return true;
}

st77xx_status_t st77xx_gamma_predefined(st77xx_t *st77xx_obj, uint8_t st77xx_gamma_predefined_bit) {
    /* Kiểm tra giá trị đúng, chỉ một bit duy nhất được cho phép, không được kết hợp các bit */
    switch(st77xx_gamma_predefined_bit) {
        /* Tham số cho phép */
        case ST77XX_GAMMA_PREDEFINED_1: break;
        case ST77XX_GAMMA_PREDEFINED_2: break;
        case ST77XX_GAMMA_PREDEFINED_3: break;
        case ST77XX_GAMMA_PREDEFINED_4: break;
        /* Tham số không cho phép */
        default: return false;
    }
    if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_GAMSET) == false) {
        return false;
    }
    if(st77xx_write_data(st77xx_obj, &st77xx_gamma_predefined_bit, 1) == false) {
        return false;
    }
    return true;
}

st77xx_status_t st77xx_display_inversion(st77xx_t *st77xx_obj, st77xx_cmd_t st77xx_display_inversion_bit) {
    st77xx_status_t ret;

    /* This command turns ON or OFF display inversion. */
    ret = st77xx_write_byte_command(st77xx_obj, st77xx_display_inversion_bit ? ST77XX_CMD_INVON : ST77XX_CMD_INVOFF);
    return ret;
}

st77xx_status_t st77xx_tearing_effect_line(st77xx_t *st77xx_obj, uint8_t tearing) {
    /* Kiểm tra tham số đầu vào */
    if((tearing == ST77XX_TEARING_MODE_V) || (tearing == ST77XX_TEARING_MODE_VH)) {
        /* turn on tearing effect line */
        if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_TEON) == false) {
            return false;
        }
        if(st77xx_write_data(st77xx_obj, &tearing, 1) == false) {
            return false;
        }
    } else {
        /* turn off tearing effect line */
        if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_TEOFF) == false) {
            return false;
        }
    }
    return true;
}

st77xx_status_t st77xx_display_mode(st77xx_t *st77xx_obj, bool state_on_off) {
    st77xx_status_t ret;
    /* Lệnh này bật hoặc tắt hiển thị màn hình. */
    ret = st77xx_write_byte_command(st77xx_obj, state_on_off ? ST77XX_CMD_DISPON : ST77XX_CMD_DISPOFF);
    return ret;
}

st77xx_status_t st77xx_active_memory_write(st77xx_t *st77xx_obj) {
    if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_RAMWR) == false) {
        return false;
    }
    return true;
}

st77xx_status_t st77xx_window_position(st77xx_t *st77xx_obj,
    uint8_t x0,
    uint8_t y0,
    uint8_t x1,
    uint8_t y1
) {
    uint8_t buffer[4];
    /* Kiểm tra param */
    if(x0 > x1) {
        return false;
    }
    if(y0 > y1) {
        return false;
    }
    /* Ghi địa chỉ cột */
    x0 += st77xx_obj->_xstart;
    x1 += st77xx_obj->_xstart;
    memcpy(buffer, (uint8_t []){0x00, x0, 0x00, x1}, 4);

    if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_CASET) == false) {
        return false;
    }
    if(st77xx_write_data(st77xx_obj, buffer, 4) == false) {
        return false;
    }
    /* Ghi địa chỉ hàng */
    y0 += st77xx_obj->_ystart;
    y1 += st77xx_obj->_ystart;
    memcpy(buffer, (uint8_t []){0x00, y0, 0x00, y1}, 4);

    if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_RASET) == false) {
        return false;
    }
    if(st77xx_write_data(st77xx_obj, buffer, 4) == false) {
        return false;
    }
    /* Ghi vào Ram */
    if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_RAMWR) == false) {
        return false;
    }
    return true;
}

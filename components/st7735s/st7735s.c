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
#include <string.h>
#include "st7735s.h"

#define ST7735S_DELAY_FLAG  0x80

// Tap Lenh dieu khien: CMD, Delay or num of arg, time delay or arg 
static const uint8_t
  init_cmds1[] = {            // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    ST7735S_CMD_SWRESET,   ST7735S_DELAY_FLAG,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    ST7735S_CMD_SLPOUT ,   ST7735S_DELAY_FLAG,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    ST7735S_CMD_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735S_CMD_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735S_CMD_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    ST7735S_CMD_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    ST7735S_CMD_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,										//
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    ST7735S_CMD_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735S_CMD_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    ST7735S_CMD_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,  									//
    ST7735S_CMD_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,							//
    ST7735S_CMD_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,										//
    ST7735S_CMD_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735S_CMD_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
    ST7735S_CMD_ROTATION,           //     row addr/col addr, bottom to top refresh
    ST7735S_CMD_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 },                 //     16-bit color

#if (defined(ST7735_IS_128X128) || defined(ST7735_IS_160X128))
  init_cmds2[] = {            // Init for 7735R, part 2 (1.44" display)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F },           //     XEND = 127
#endif // ST7735_IS_128X128

#ifdef ST7735_IS_160X80
  init_cmds2[] = {                  // Init for 7735S, part 2 (160x80 display)
    3,                              //  3 commands in list:
    ST7735S_CMD_CASET  , 4,         // 1: Column addr set, 4 args, no delay:
      0x00, 0x00,                   // XSTART = 0
      0x00, 0x4F,                   // XEND = 79
    ST7735S_CMD_RASET  , 4,         // 2: Row addr set, 4 args, no delay:
      0x00, 0x00,                   // XSTART = 0
      0x00, 0x9F ,                  // XEND = 159
    ST7735S_CMD_INVON, 0 },         // 3: Invert colors
#endif

  init_cmds3[] = {                  // Init for 7735R, part 3 (red or green tab)
    4,                              //  4 commands in list:
    ST7735S_CMD_GMCTRP1, 16,        //  1: Magical unicorn dust, 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735S_CMD_GMCTRN1, 16,        //  2: Sparkles and rainbows, 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735S_CMD_NORON  ,    ST7735S_DELAY_FLAG, //  3: Normal display on, no args, w/delay
      10,                           //     10 ms delay
    ST7735S_CMD_DISPON ,    ST7735S_DELAY_FLAG, //  4: Main screen turn on, no args w/delay
      100                           //     100 ms delay
  };


static inline st7735s_status_t st7735s_write_data(st7735s_t *st7735s_obj, uint8_t *data, size_t data_length) {
    st7735s_obj->drv_rs_output(ST7735S_DATA_MODE);
    return st7735s_obj->drv_spi_write(data, data_length);
}

st7735s_status_t st7735s_write_byte_command(st7735s_t *st7735s_obj, s7735s_cmd_t cmd) {
    st7735s_obj->drv_rs_output(ST7735S_COMMAND_MODE);
    return st7735s_obj->drv_spi_write((uint8_t *)&cmd, 1);
}

void st7735_execute_cmd_list(st7735s_t *st7735s_obj, const uint8_t *addr) 
{
    uint8_t numCommands, numArgs;
    uint16_t ms;
    numCommands = *addr++;
    while(numCommands--) {
        uint8_t cmd = *addr++;
        st7735s_write_byte_command(st7735s_obj, cmd);
        numArgs = *addr++;
        // If high bit set, delay follows args
        ms = numArgs & ST7735S_DELAY_FLAG;
        numArgs &= ~ST7735S_DELAY_FLAG;
        if(numArgs) {
            st7735s_write_data(st7735s_obj, (uint8_t*)addr, numArgs);
            addr += numArgs;
        }
        if(ms) {
            ms = *addr++;
            if(ms == 255) ms = 500;
            st7735s_obj->drv_delay_ms(ms);
        }
    }
}

st7735s_status_t st7735s_init(st7735s_t *st7735s_obj, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t)) {
    if((drv_spi_write == 0) || (drv_reset_output == 0) || (drv_rs_output == 0) || (drv_delay_ms == 0))return false;
    
    st7735s_obj->drv_spi_write = drv_spi_write;
    st7735s_obj->drv_rs_output = drv_rs_output;
    st7735s_obj->drv_reset_output = drv_reset_output;
    st7735s_obj->drv_delay_ms = drv_delay_ms;
    
    st7735s_obj->drv_reset_output(false);
    st7735s_obj->drv_delay_ms(150);
    st7735s_obj->drv_reset_output(true);

    st7735_execute_cmd_list(st7735s_obj, init_cmds1);
    st7735_execute_cmd_list(st7735s_obj, init_cmds2);
    st7735_execute_cmd_list(st7735s_obj, init_cmds3);
    return true;
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

st7735s_status_t st7735s_interface_pixel_format(st7735s_t *st7735s_obj, uint8_t st7735s_interface_pixel_format_bit) {
    /* Kiểm tra giá trị đúng, chỉ một bit duy nhất được cho phép, không được kết hợp các bit */
    switch(st7735s_interface_pixel_format_bit) {
        /* Tham số cho phép */
        case ST7735S_PIXEL_FORMAT_444: break;
        case ST7735S_PIXEL_FORMAT_565: break;
        case ST7735S_PIXEL_FORMAT_666: break;
        /* Tham số không cho phép */
        default: return false;
    }
    if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_COLMOD) == false) {
        return false;
    }
    if(st7735s_write_data(st7735s_obj, &st7735s_interface_pixel_format_bit, 1) == false) {
        return false;
    }
    return true;
}

st7735s_status_t st7735s_gamma_predefined(st7735s_t *st7735s_obj, uint8_t st7735s_gamma_predefined_bit) {
    /* Kiểm tra giá trị đúng, chỉ một bit duy nhất được cho phép, không được kết hợp các bit */
    switch(st7735s_gamma_predefined_bit) {
        /* Tham số cho phép */
        case ST7735S_GAMMA_PREDEFINED_1: break;
        case ST7735S_GAMMA_PREDEFINED_2: break;
        case ST7735S_GAMMA_PREDEFINED_3: break;
        case ST7735S_GAMMA_PREDEFINED_4: break;
        /* Tham số không cho phép */
        default: return false;
    }
    if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_GAMSET) == false) {
        return false;
    }
    if(st7735s_write_data(st7735s_obj, &st7735s_gamma_predefined_bit, 1) == false) {
        return false;
    }
    return true;
}

st7735s_status_t st7735s_display_inversion(st7735s_t *st7735s_obj, s7735s_cmd_t st7735s_display_inversion_bit) {
    st7735s_status_t ret;

    /* This command turns ON or OFF display inversion. */
    ret = st7735s_write_byte_command(st7735s_obj, st7735s_display_inversion_bit ? ST7735S_CMD_INVON : ST7735S_CMD_INVOFF);
    return ret;
}

st7735s_status_t st7735s_tearing_effect_line(st7735s_t *st7735s_obj, uint8_t tearing) {
    /* Kiểm tra tham số đầu vào */
    if((tearing == ST7735S_TEARING_MODE_V) || (tearing == ST7735S_TEARING_MODE_VH)) {
        /* turn on tearing effect line */
        if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_TEON) == false) {
            return false;
        }
        if(st7735s_write_data(st7735s_obj, &tearing, 1) == false) {
            return false;
        }
    } else {
        /* turn off tearing effect line */
        if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_TEOFF) == false) {
            return false;
        }
    }
    return true;
}

st7735s_status_t st7735s_display_mode(st7735s_t *st7735s_obj, bool state_on_off) {
    st7735s_status_t ret;
    /* Lệnh này bật hoặc tắt hiển thị màn hình. */
    ret = st7735s_write_byte_command(st7735s_obj, state_on_off ? ST7735S_CMD_DISPON : ST7735S_CMD_DISPOFF);
    return ret;
}

st7735s_status_t st7735s_active_memory_write(st7735s_t *st7735s_obj) {
    if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_RAMWR) == false) {
        return false;
    }
    return true;
}

st7735s_status_t st7735s_window_position(st7735s_t *st7735s_obj,
    uint16_t x0,
    uint16_t y0,
    uint16_t x1,
    uint16_t y1
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
    memcpy(buffer, (uint8_t []){0x00, x0 + ST7735_XSTART, 0x00, x1 + ST7735_XSTART}, 4);

    if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_CASET) == false) {
        return false;
    }
    if(st7735s_write_data(st7735s_obj, buffer, 4) == false) {
        return false;
    }
    /* Ghi địa chỉ hàng */
    memcpy(buffer, (uint8_t []){0x00, y0 + ST7735_YSTART, 0x00, y1 + ST7735_YSTART}, 4);

    if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_RASET) == false) {
        return false;
    }
    if(st7735s_write_data(st7735s_obj, buffer, 4) == false) {
        return false;
    }
    /* Ghi vào Ram */
    if(st7735s_write_byte_command(st7735s_obj, ST7735S_CMD_RAMWR) == false) {
        return false;
    }
    return true;
}

st7735s_status_t st7735s_framebuffer_send(st7735s_t *st7735s_obj, 
    uint16_t x_pos_start,
    uint16_t y_pos_start,
    uint16_t x_pos_end,
    uint16_t y_pos_end,
    uint8_t *buffer,
    size_t length_buffer
) {
    if( st7735s_window_position(st7735s_obj, x_pos_start, y_pos_start, x_pos_end, y_pos_end) == false) {
        return false;
    }
    if( st7735s_write_data(st7735s_obj, buffer, length_buffer) == false) {
        return false;
    }
    return true;
}

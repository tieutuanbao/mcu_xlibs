#include "st7735.h"


// Tap Lenh dieu khien: CMD, Delay or num of arg, time delay or arg 
static const uint8_t
  Bcmd[] = {                        // Init commands for 7735B screens
    18,                             // 18 commands in list:
    ST77XX_CMD_SWRESET,   ST77XX_DELAY_FLAG, //  1: Software reset, no args, w/delay
      50,                           //     50 ms delay
    ST77XX_CMD_SLPOUT,    ST77XX_DELAY_FLAG, //  2: Out of sleep mode, no args, w/delay
      255,                          //     255 = max (500 ms) delay
    ST77XX_CMD_COLMOD,  1+ST77XX_DELAY_FLAG, //  3: Set color mode, 1 arg + delay:
      0x05,                         //     16-bit color
      10,                           //     10 ms delay
    ST7735_CMD_FRMCTR1, 3+ST77XX_DELAY_FLAG, //  4: Frame rate control, 3 args + delay:
      0x00,                         //     fastest refresh
      0x06,                         //     6 lines front porch
      0x03,                         //     3 lines back porch
      10,                           //     10 ms delay
    ST77XX_CMD_MADCTL,  1,              //  5: Mem access ctl (directions), 1 arg:
      0x08,                         //     Row/col addr, bottom-top refresh
    ST7735_CMD_DISSET5, 2,              //  6: Display settings #5, 2 args:
      0x15,                         //     1 clk cycle nonoverlap, 2 cycle gate
                                    //     rise, 3 cycle osc equalize
      0x02,                         //     Fix on VTL
    ST7735_CMD_INVCTR,  1,              //  7: Display inversion control, 1 arg:
      0x0,                          //     Line inversion
    ST7735_CMD_PWCTR1,  2+ST77XX_DELAY_FLAG, //  8: Power control, 2 args + delay:
      0x02,                         //     GVDD = 4.7V
      0x70,                         //     1.0uA
      10,                           //     10 ms delay
    ST7735_CMD_PWCTR2,  1,              //  9: Power control, 1 arg, no delay:
      0x05,                         //     VGH = 14.7V, VGL = -7.35V
    ST7735_CMD_PWCTR3,  2,              // 10: Power control, 2 args, no delay:
      0x01,                         //     Opamp current small
      0x02,                         //     Boost frequency
    ST7735_CMD_VMCTR1,  2+ST77XX_DELAY_FLAG, // 11: Power control, 2 args + delay:
      0x3C,                         //     VCOMH = 4V
      0x38,                         //     VCOML = -1.1V
      10,                           //     10 ms delay
    ST7735_CMD_PWCTR6,  2,              // 12: Power control, 2 args, no delay:
      0x11, 0x15,
    ST7735_CMD_GMCTRP1,16,              // 13: Gamma Adjustments (pos. polarity), 16 args + delay:
      0x09, 0x16, 0x09, 0x20,       //     (Not entirely necessary, but provides
      0x21, 0x1B, 0x13, 0x19,       //      accurate colors)
      0x17, 0x15, 0x1E, 0x2B,
      0x04, 0x05, 0x02, 0x0E,
    ST7735_CMD_GMCTRN1,16+ST77XX_DELAY_FLAG, // 14: Gamma Adjustments (neg. polarity), 16 args + delay:
      0x0B, 0x14, 0x08, 0x1E,       //     (Not entirely necessary, but provides
      0x22, 0x1D, 0x18, 0x1E,       //      accurate colors)
      0x1B, 0x1A, 0x24, 0x2B,
      0x06, 0x06, 0x02, 0x0F,
      10,                           //     10 ms delay
    ST77XX_CMD_CASET,   4,              // 15: Column addr set, 4 args, no delay:
      0x00, 0x02,                   //     XSTART = 2
      0x00, 0x81,                   //     XEND = 129
    ST77XX_CMD_RASET,   4,              // 16: Row addr set, 4 args, no delay:
      0x00, 0x02,                   //     XSTART = 1
      0x00, 0x81,                   //     XEND = 160
    ST77XX_CMD_NORON,     ST77XX_DELAY_FLAG, // 17: Normal display on, no args, w/delay
      10,                           //     10 ms delay
    ST77XX_CMD_DISPON,    ST77XX_DELAY_FLAG, // 18: Main screen turn on, no args, delay
      255 },                        //     255 = max (500 ms) delay

  Rcmd1[] = {                       // 7735R init, part 1 (red or green tab)
    15,                             // 15 commands in list:
    ST77XX_CMD_SWRESET,   ST77XX_DELAY_FLAG, //  1: Software reset, 0 args, w/delay
      150,                          //     150 ms delay
    ST77XX_CMD_SLPOUT,    ST77XX_DELAY_FLAG, //  2: Out of sleep mode, 0 args, w/delay
      255,                          //     500 ms delay
    ST7735_CMD_FRMCTR1, 3,              //  3: Framerate ctrl - normal mode, 3 arg:
      0x01, 0x2C, 0x2D,             //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_CMD_FRMCTR2, 3,              //  4: Framerate ctrl - idle mode, 3 args:
      0x01, 0x2C, 0x2D,             //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_CMD_FRMCTR3, 6,              //  5: Framerate - partial mode, 6 args:
      0x01, 0x2C, 0x2D,             //     Dot inversion mode
      0x01, 0x2C, 0x2D,             //     Line inversion mode
    ST7735_CMD_INVCTR,  1,              //  6: Display inversion ctrl, 1 arg:
      0x07,                         //     No inversion
    ST7735_CMD_PWCTR1,  3,              //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                         //     -4.6V
      0x84,                         //     AUTO mode
    ST7735_CMD_PWCTR2,  1,              //  8: Power control, 1 arg, no delay:
      0xC5,                         //     VGH25=2.4C VGSEL=-10 VGH=3 * AVDD
    ST7735_CMD_PWCTR3,  2,              //  9: Power control, 2 args, no delay:
      0x0A,                         //     Opamp current small
      0x00,                         //     Boost frequency
    ST7735_CMD_PWCTR4,  2,              // 10: Power control, 2 args, no delay:
      0x8A,                         //     BCLK/2,
      0x2A,                         //     opamp current small & medium low
    ST7735_CMD_PWCTR5,  2,              // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ST7735_CMD_VMCTR1,  1,              // 12: Power control, 1 arg, no delay:
      0x0E,
    ST77XX_CMD_INVOFF,  0,              // 13: Don't invert display, no args
    ST77XX_CMD_MADCTL,  1,              // 14: Mem access ctl (directions), 1 arg:
    (ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST7735_MADCTL_BGR),   //     row/col addr, bottom-top refresh
    ST77XX_CMD_COLMOD,  1,              // 15: set color mode, 1 arg, no delay:
      0x05 },                       //     16-bit color

  Rcmd2green[] = {                  // 7735R init, part 2 (green tab only)
    2,                              //  2 commands in list:
    ST77XX_CMD_CASET,   4,              //  1: Column addr set, 4 args, no delay:
      0x00, 0x02,                   //     XSTART = 0
      0x00, 0x7F+0x02,              //     XEND = 127
    ST77XX_CMD_RASET,   4,              //  2: Row addr set, 4 args, no delay:
      0x00, 0x01,                   //     XSTART = 0
      0x00, 0x9F+0x01 },            //     XEND = 159

  Rcmd2red[] = {                    // 7735R init, part 2 (red tab only)
    2,                              //  2 commands in list:
    ST77XX_CMD_CASET,   4,              //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x7F,                   //     XEND = 127
    ST77XX_CMD_RASET,   4,              //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x9F },                 //     XEND = 159

  Rcmd2green144[] = {               // 7735R init, part 2 (green 1.44 tab)
    2,                              //  2 commands in list:
    ST77XX_CMD_CASET,   4,              //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x7F,                   //     XEND = 127
    ST77XX_CMD_RASET,   4,              //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x7F },                 //     XEND = 127

  Rcmd2green160x80[] = {            // 7735R init, part 2 (mini 160x80)
    3,                              //  2 commands in list:
    ST77XX_CMD_CASET,   4,              //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x4F,                   //     XEND = 79
    ST77XX_CMD_RASET,   4,              //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x9F,                   //     XEND = 159
    ST77XX_CMD_INVON, 0 },          // 3: Invert colors

  Rcmd3[] = {                       // 7735R init, part 3 (red or green tab)
    4,                              //  4 commands in list:
    ST7735_CMD_GMCTRP1, 16      ,       //  1: Gamma Adjustments (pos. polarity), 16 args + delay:
      0x02, 0x1c, 0x07, 0x12,       //     (Not entirely necessary, but provides
      0x37, 0x32, 0x29, 0x2d,       //      accurate colors)
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_CMD_GMCTRN1, 16      ,       //  2: Gamma Adjustments (neg. polarity), 16 args + delay:
      0x03, 0x1d, 0x07, 0x06,       //     (Not entirely necessary, but provides
      0x2E, 0x2C, 0x29, 0x2D,       //      accurate colors)
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST77XX_CMD_NORON,     ST77XX_DELAY_FLAG, //  3: Normal display on, no args, w/delay
      10,                           //     10 ms delay
    ST77XX_CMD_DISPON,    ST77XX_DELAY_FLAG, //  4: Main screen turn on, no args w/delay
      100 };                        //     100 ms delay

st77xx_status_t ST7735R_init(st77xx_t *st77xx_obj, st77xx_init_opt_t options, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t)) {
    st77xx_init(st77xx_obj, drv_spi_write, drv_rs_output, drv_reset_output, drv_delay_ms);
    st77XX_execute_cmd_list(st77xx_obj, Rcmd1);
    /* Cấu hình ST77XX */
    if (options == ST77XX_INITR_GREENTAB) {
        st77XX_execute_cmd_list(st77xx_obj, Rcmd2green);
        st77xx_obj->_colstart = 2;
        st77xx_obj->_rowstart = 1; // For default index_rotation 0
    } else if ((options == ST77XX_INITR_144GREENTAB) || (options == ST77XX_INITR_HALLOWING)) {
        st77xx_obj->height = ST7735_TFTHEIGHT_128;
        st77xx_obj->width = ST7735_TFTWIDTH_128;
        st77XX_execute_cmd_list(st77xx_obj, Rcmd2green144);
        st77xx_obj->_colstart = 2;
        st77xx_obj->_rowstart = 3; // For default index_rotation 0
    } else if (options == ST77XX_INITR_MINI160x80) {
        st77xx_obj->height = ST7735_TFTWIDTH_80;
        st77xx_obj->width = ST7735_TFTHEIGHT_160;
        st77XX_execute_cmd_list(st77xx_obj, Rcmd2green160x80);
        st77xx_obj->_colstart = 26;
        st77xx_obj->_rowstart = 2;
    } else {
        // colstart, rowstart left at default '0' values
        st77XX_execute_cmd_list(st77xx_obj, Rcmd2red);
    }
    st77XX_execute_cmd_list(st77xx_obj, Rcmd3);

    // Black tab, change MADCTL color filter
    if ((options == ST77XX_INITR_BLACKTAB) || (options == ST77XX_INITR_MINI160x80)) {
        uint8_t data = 0xC0;
        if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_MADCTL) == false) {
            return false;
        }   
        if(st77xx_write_data(st77xx_obj, &data, 1) == false) {
            return false;
        }
    }

    if (options == ST77XX_INITR_HALLOWING) {
        // Hallowing is simply a 1.44" green tab upside-down:
        st77xx_obj->option = ST77XX_INITR_144GREENTAB;
        st7735_set_rotation(st77xx_obj, 2);
    } else {
        st77xx_obj->option = options;
        st7735_set_rotation(st77xx_obj, 0);
    }        
    return true;
}

st77xx_status_t ST7735B_init(st77xx_t *st77xx_obj, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t)) {
    st77xx_init(st77xx_obj, drv_spi_write, drv_rs_output, drv_reset_output, drv_delay_ms);
    st77XX_execute_cmd_list(st77xx_obj, Bcmd);
    return true;
}

st77xx_status_t st7735_set_rotation(st77xx_t *st77xx_obj, uint8_t index_rotation) {
    uint8_t madctl = 0;
    index_rotation = index_rotation & 3; // can't be higher than 3
    // For ST7735 with GREEN TAB (including HalloWing)...
    if ((st77xx_obj->option == ST77XX_INITR_144GREENTAB) || (st77xx_obj->option == ST77XX_INITR_HALLOWING)) {
        // ..._rowstart is 3 for index_rotations 0&1, 1 for index_rotations 2&3
        st77xx_obj->_rowstart = (index_rotation < 2) ? 3 : 1;
    }

    switch (index_rotation) {
        case 0:
            if ((st77xx_obj->option == ST77XX_INITR_BLACKTAB) || (st77xx_obj->option == ST77XX_INITR_MINI160x80)) {
                madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST77XX_MADCTL_RGB;
            } else {
                madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST7735_MADCTL_BGR;
            }

            if (st77xx_obj->option == ST77XX_INITR_144GREENTAB) {
                st77xx_obj->height = ST7735_TFTHEIGHT_128;
                st77xx_obj->width = ST7735_TFTWIDTH_128;
            } else if (st77xx_obj->option == ST77XX_INITR_MINI160x80) {
                st77xx_obj->height = ST7735_TFTHEIGHT_160;
                st77xx_obj->width = ST7735_TFTWIDTH_80;
            } else {
                st77xx_obj->height = ST7735_TFTHEIGHT_160;
                st77xx_obj->width = ST7735_TFTWIDTH_128;
            }
                st77xx_obj->_xstart = st77xx_obj->_colstart;
                st77xx_obj->_ystart = st77xx_obj->_rowstart;
            break;
        case 1:
            if ((st77xx_obj->option == ST77XX_INITR_BLACKTAB) || (st77xx_obj->option == ST77XX_INITR_MINI160x80)) {
                madctl = ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
            } else {
                madctl = ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST7735_MADCTL_BGR;
            }

            if (st77xx_obj->option == ST77XX_INITR_144GREENTAB) {
                st77xx_obj->width = ST7735_TFTHEIGHT_128;
                st77xx_obj->height = ST7735_TFTWIDTH_128;
            } else if (st77xx_obj->option == ST77XX_INITR_MINI160x80) {
                st77xx_obj->width = ST7735_TFTHEIGHT_160;
                st77xx_obj->height = ST7735_TFTWIDTH_80;
            } else {
                st77xx_obj->width = ST7735_TFTHEIGHT_160;
                st77xx_obj->height = ST7735_TFTWIDTH_128;
            }
            st77xx_obj->_ystart = st77xx_obj->_colstart;
            st77xx_obj->_xstart = st77xx_obj->_rowstart;
            break;
        case 2:
            if ((st77xx_obj->option == ST77XX_INITR_BLACKTAB) || (st77xx_obj->option == ST77XX_INITR_MINI160x80)) {
            madctl = ST77XX_MADCTL_RGB;
            } else {
            madctl = ST7735_MADCTL_BGR;
            }

            if (st77xx_obj->option == ST77XX_INITR_144GREENTAB) {
                st77xx_obj->height = ST7735_TFTHEIGHT_128;
                st77xx_obj->width = ST7735_TFTWIDTH_128;
            } else if (st77xx_obj->option == ST77XX_INITR_MINI160x80) {
                st77xx_obj->height = ST7735_TFTHEIGHT_160;
                st77xx_obj->width = ST7735_TFTWIDTH_80;
            } else {
                st77xx_obj->height = ST7735_TFTHEIGHT_160;
                st77xx_obj->width = ST7735_TFTWIDTH_128;
            }
            st77xx_obj->_xstart = st77xx_obj->_colstart;
            st77xx_obj->_ystart = st77xx_obj->_rowstart;
            break;
        case 3:
            if ((st77xx_obj->option == ST77XX_INITR_BLACKTAB) || (st77xx_obj->option == ST77XX_INITR_MINI160x80)) {
                madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
            } else {
                madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MV | ST7735_MADCTL_BGR;
            }

            if (st77xx_obj->option == ST77XX_INITR_144GREENTAB) {
                st77xx_obj->width = ST7735_TFTHEIGHT_128;
                st77xx_obj->height = ST7735_TFTWIDTH_128;
            } else if (st77xx_obj->option == ST77XX_INITR_MINI160x80) {
                st77xx_obj->width = ST7735_TFTHEIGHT_160;
                st77xx_obj->height = ST7735_TFTWIDTH_80;
            } else {
                st77xx_obj->width = ST7735_TFTHEIGHT_160;
                st77xx_obj->height = ST7735_TFTWIDTH_128;
            }
            st77xx_obj->_ystart = st77xx_obj->_colstart;
            st77xx_obj->_xstart = st77xx_obj->_rowstart;
            break;
    }
    if(st77xx_write_byte_command(st77xx_obj, ST77XX_CMD_MADCTL) == false) {
        return false;
    }   
    if(st77xx_write_data(st77xx_obj, &madctl, 1) == false) {
        return false;
    }
    return true;
}

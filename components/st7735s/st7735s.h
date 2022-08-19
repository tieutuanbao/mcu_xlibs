/**
 * @file st7735s.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ST7735S_H__
#define __ST7735S_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define ST7735_IS_160X80 1
#define ST7735_XSTART 26
#define ST7735_YSTART 1
#define ST7735_WIDTH  80
#define ST7735_HEIGHT 160 

#define ST7735S_COMMAND_MODE    false
#define ST7735S_DATA_MODE       true

/**
 * @brief Define bit: ST7735S Memmory access (pdf v1.4 p142)
 * Tham số cho st7735s_mem_access
 */
#define ST7735S_MADCTL_MY       (1<<7)    /* Row Address Order */
#define ST7735S_MADCTL_MX       (1<<6)    /* Column Address Order */
#define ST7735S_MADCTL_MV       (1<<5)    /* Row / Column Exchange */
#define ST7735S_MADCTL_ML       (1<<4)    /* Vertical Refresh Order */
#define ST7735S_MADCTL_BGR      (1<<3)    /* RGB or BGR Order */
#define ST7735S_MADCTL_MH       (1<<2)    /* Horizontal Refresh Order */
#define ST7735S_MADCTL_DEFAULT  0         /* Default state */

/**
 * @brief Define bit: ST7735S Interface Pixel Format (pdf v1.4 p150)
 * Tham số cho st7735s_mem_access
 */
#define ST7735S_PIXEL_FORMAT_444    3 /* 12-bit/pixel */
#define ST7735S_PIXEL_FORMAT_565    5 /* 16-bit/pixel */
#define ST7735S_PIXEL_FORMAT_666    6 /* 18-bit/pixel */

/**
 * @brief Define bit: ST7735S Gamma Predefined (pdf v1.4 p125)
 * Tham số cho st7735s_gamma_predefined
 */
#define ST7735S_GAMMA_PREDEFINED_1  (1<<0) /* Gamma Curve 1 */
#define ST7735S_GAMMA_PREDEFINED_2  (1<<1) /* Gamma Curve 2 */
#define ST7735S_GAMMA_PREDEFINED_3  (1<<2) /* Gamma Curve 3 */
#define ST7735S_GAMMA_PREDEFINED_4  (1<<3) /* Gamma Curve 4 */

/**
 * @brief Define bit: ST7735S Tearing Mode (pdf v1.4 p140)
 * Tham số cho st7735s_tearing_effect_line
 */
#define ST7735S_TEARING_MODE_V    0 /* turn on tearing with V-Blanking */
#define ST7735S_TEARING_MODE_VH   1 /* turn on tearing with V-Blanking H-Blanking */
#define ST7735S_TEARING_OFF     255 /* turn off tearing effect line */

#define ST7735S_CMD_ROTATION    (ST7735S_MADCTL_MX | ST7735S_MADCTL_MY | ST7735S_MADCTL_BGR)
/**
 * @brief Danh sách command st7735s 
 */
typedef enum {
    ST7735S_CMD_SWRESET     = 0x01,    /* Software Reset (pdf v1.4 p108) */
    ST7735S_CMD_RDDID       = 0x04,
    ST7735S_CMD_RDDST       = 0x09,
    ST7735S_CMD_SLPIN       = 0x10,    /* Sleep In (pdf v1.4 p119) */
    ST7735S_CMD_SLPOUT      = 0x11,    /* Sleep Out (pdf v1.4 p120) */
    ST7735S_CMD_PTLON       = 0x12,
    ST7735S_CMD_NORON       = 0x13,
    ST7735S_CMD_INVOFF      = 0x20,    /* Display Inversion Off (pdf v1.4 p123) */
    ST7735S_CMD_INVON       = 0x21,    /* Display Inversion On (pdf v1.4 p124) */
    ST7735S_CMD_GAMSET      = 0x26,    /* Gamma Set (pdf v1.4 p125) */
    ST7735S_CMD_DISPOFF     = 0x28,    /* Display Off (pdf v1.4 p126) */
    ST7735S_CMD_DISPON      = 0x29,    /* Display On (pdf v1.4 p127) */
    ST7735S_CMD_CASET       = 0x2A,    /* Column Address Set (pdf v1.4 p128-129) */
    ST7735S_CMD_RASET       = 0x2B,    /* Row Address Set (pdf v1.4 p130-131) */
    ST7735S_CMD_RAMWR       = 0x2C,    /* Memory Write (pdf v1.4 p132) */
    ST7735S_CMD_PTLAR       = 0x30,
    ST7735S_CMD_TEOFF       = 0x34,    /* Tearing Effect Line OFF (pdf v1.4 p139) */
    ST7735S_CMD_TEON        = 0x35,    /* Tearing Effect Line ON (pdf v1.4 p140) */
    ST7735S_CMD_MADCTL      = 0x36,    /* Memory Data Access Control (pdf v1.4 p142) */
    ST7735S_CMD_IDMOFF      = 0x38,    /* Idle Mode Off (pdf v1.4 p147) */
    ST7735S_CMD_IDMON       = 0x39,    /* Idle Mode On (pdf v1.4 p148) */
    ST7735S_CMD_COLMOD      = 0x3A,    /* Interface Pixel Format (pdf v1.4 p150) */
    ST7735S_CMD_FRMCTR1     = 0xB1,
    ST7735S_CMD_FRMCTR2     = 0xB2,
    ST7735S_CMD_FRMCTR3     = 0xB3,
    ST7735S_CMD_INVCTR      = 0xB4,
    ST7735S_CMD_DISSET5     = 0xB6,
    ST7735S_CMD_PWCTR1      = 0xC0,
    ST7735S_CMD_PWCTR2      = 0xC1,
    ST7735S_CMD_PWCTR3      = 0xC2,
    ST7735S_CMD_PWCTR4      = 0xC3,
    ST7735S_CMD_PWCTR5      = 0xC4,
    ST7735S_CMD_VMCTR1      = 0xC5,
    ST7735S_CMD_RDID1       = 0xDA,
    ST7735S_CMD_RDID2       = 0xDB,
    ST7735S_CMD_RDID3       = 0xDC,
    ST7735S_CMD_RDID4       = 0xDD,
    ST7735S_CMD_PWCTR6      = 0xFC,
    ST7735S_CMD_GMCTRP1     = 0xE0,
    ST7735S_CMD_GMCTRN1     = 0xE1,
    ST7735S_CMD_BLACK       = 0x0000,
    ST7735S_CMD_BLUE        = 0x001F,
    ST7735S_CMD_RED         = 0xF800,
    ST7735S_CMD_GREEN       = 0x07E0,
    ST7735S_CMD_CYAN        = 0x07FF,
    ST7735S_CMD_MAGENTA     = 0xF81F,
    ST7735S_CMD_YELLOW      = 0xFFE0,
    ST7735S_CMD_WHITE       = 0xFFFF
} s7735s_cmd_t;

typedef struct st7735s_struct {
    bool (*drv_spi_write)(uint8_t *data, size_t data_length);
    void (*drv_rs_output)(bool state);
    void (*drv_reset_output)(bool state);
    void (*drv_delay_ms)(uint32_t time_ms);
} st7735s_t;

typedef bool st7735s_status_t;

st7735s_status_t st7735s_init(st7735s_t *st7735s_obj, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t));
st7735s_status_t st7735s_write_byte_command(st7735s_t *st7735s_obj, s7735s_cmd_t cmd);
st7735s_status_t st7735s_set_sleep(st7735s_t *st7735s_obj, bool state);
st7735s_status_t st7735s_mem_access(st7735s_t *st7735s_obj, uint8_t st7735s_mem_access_bit);
st7735s_status_t st7735s_interface_pixel_format(st7735s_t *st7735s_obj, uint8_t st7735s_interface_pixel_format_bit);
st7735s_status_t st7735s_gamma_predefined(st7735s_t *st7735s_obj, uint8_t st7735s_gamma_predefined_bit);
st7735s_status_t st7735s_display_inversion(st7735s_t *st7735s_obj, s7735s_cmd_t st7735s_display_inversion_bit);
st7735s_status_t st7735s_tearing_effect_line(st7735s_t *st7735s_obj, uint8_t tearing);
st7735s_status_t st7735s_display_mode(st7735s_t *st7735s_obj, bool state_on_off);
st7735s_status_t st7735s_active_memory_write(st7735s_t *st7735s_obj);
st7735s_status_t st7735s_window_position(st7735s_t *st7735s_obj,
    uint16_t column_start,
    uint16_t row_start,
    uint16_t column_end,
    uint16_t row_end
);

st7735s_status_t st7735s_framebuffer_send(st7735s_t *st7735s_obj, 
    uint16_t x_pos_start,
    uint16_t y_pos_start,
    uint16_t x_pos_end,
    uint16_t y_pos_end,
    uint8_t *buffer,
    size_t length_buffer
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ST7735S_H__ */
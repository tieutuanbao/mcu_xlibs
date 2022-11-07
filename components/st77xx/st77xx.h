/**
 * @file st77xx.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ST77XX_H__
#define __ST77XX_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define ST77XX_COMMAND_MODE    false
#define ST77XX_DATA_MODE       true

/**
 * @brief Define bit: ST77XX Memmory access (pdf v1.4 p142)
 * Tham số cho st77xx_mem_access
 */
#define ST77XX_MADCTL_MY       (1<<7)   /* Row Address Order */
#define ST77XX_MADCTL_MX       (1<<6)   /* Column Address Order */
#define ST77XX_MADCTL_MV       (1<<5)   /* Row / Column Exchange */
#define ST77XX_MADCTL_ML       (1<<4)   /* Vertical Refresh Order */
#define ST77XX_MADCTL_RGB      (1<<3)   /* RGB or BRG Order */
#define ST77XX_MADCTL_MH       (1<<2)   /* Horizontal Refresh Order */
#define ST77XX_MADCTL_DEFAULT  0        /* Default state */

/**
 * @brief Define bit: ST77XX Interface Pixel Format (pdf v1.4 p150)
 * Tham số cho st77xx_mem_access
 */
#define ST77XX_PIXEL_FORMAT_444    3 /* 12-bit/pixel */
#define ST77XX_PIXEL_FORMAT_565    5 /* 16-bit/pixel */
#define ST77XX_PIXEL_FORMAT_666    6 /* 18-bit/pixel */

/**
 * @brief Define bit: ST77XX Gamma Predefined (pdf v1.4 p125)
 * Tham số cho st77xx_gamma_predefined
 */
#define ST77XX_GAMMA_PREDEFINED_1  (1<<0) /* Gamma Curve 1 */
#define ST77XX_GAMMA_PREDEFINED_2  (1<<1) /* Gamma Curve 2 */
#define ST77XX_GAMMA_PREDEFINED_3  (1<<2) /* Gamma Curve 3 */
#define ST77XX_GAMMA_PREDEFINED_4  (1<<3) /* Gamma Curve 4 */

/**
 * @brief Define bit: ST77XX Tearing Mode (pdf v1.4 p140)
 * Tham số cho st77xx_tearing_effect_line
 */
#define ST77XX_TEARING_MODE_V    0 /* turn on tearing with V-Blanking */
#define ST77XX_TEARING_MODE_VH   1 /* turn on tearing with V-Blanking H-Blanking */
#define ST77XX_TEARING_OFF     255 /* turn off tearing effect line */

#define ST77XX_CMD_ROTATION    (ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST77XX_MADCTL_BGR)

#define ST77XX_DELAY_FLAG  0x80
/**
 * @brief Danh sách command st77xx 
 */
typedef enum {
    ST77XX_CMD_SWRESET     = 0x01,    /* Software Reset (pdf v1.4 p108) */
    ST77XX_CMD_RDDID       = 0x04,
    ST77XX_CMD_RDDST       = 0x09,
    ST77XX_CMD_SLPIN       = 0x10,    /* Sleep In (pdf v1.4 p119) */
    ST77XX_CMD_SLPOUT      = 0x11,    /* Sleep Out (pdf v1.4 p120) */
    ST77XX_CMD_PTLON       = 0x12,
    ST77XX_CMD_NORON       = 0x13,
    ST77XX_CMD_INVOFF      = 0x20,    /* Display Inversion Off (pdf v1.4 p123) */
    ST77XX_CMD_INVON       = 0x21,    /* Display Inversion On (pdf v1.4 p124) */
    ST77XX_CMD_GAMSET      = 0x26,    /* Gamma Set (pdf v1.4 p125) */
    ST77XX_CMD_DISPOFF     = 0x28,    /* Display Off (pdf v1.4 p126) */
    ST77XX_CMD_DISPON      = 0x29,    /* Display On (pdf v1.4 p127) */
    ST77XX_CMD_CASET       = 0x2A,    /* Column Address Set (pdf v1.4 p128-129) */
    ST77XX_CMD_RASET       = 0x2B,    /* Row Address Set (pdf v1.4 p130-131) */
    ST77XX_CMD_RAMWR       = 0x2C,    /* Memory Write (pdf v1.4 p132) */
    ST77XX_CMD_PTLAR       = 0x30,
    ST77XX_CMD_TEOFF       = 0x34,    /* Tearing Effect Line OFF (pdf v1.4 p139) */
    ST77XX_CMD_TEON        = 0x35,    /* Tearing Effect Line ON (pdf v1.4 p140) */
    ST77XX_CMD_MADCTL      = 0x36,    /* Memory Data Access Control (pdf v1.4 p142) */
    ST77XX_CMD_IDMOFF      = 0x38,    /* Idle Mode Off (pdf v1.4 p147) */
    ST77XX_CMD_IDMON       = 0x39,    /* Idle Mode On (pdf v1.4 p148) */
    ST77XX_CMD_COLMOD      = 0x3A,    /* Interface Pixel Format (pdf v1.4 p150) */
    ST77XX_CMD_FRMCTR1     = 0xB1,
    ST77XX_CMD_FRMCTR2     = 0xB2,
    ST77XX_CMD_FRMCTR3     = 0xB3,
    ST77XX_CMD_INVCTR      = 0xB4,
    ST77XX_CMD_DISSET5     = 0xB6,
    ST77XX_CMD_PWCTR1      = 0xC0,
    ST77XX_CMD_PWCTR2      = 0xC1,
    ST77XX_CMD_PWCTR3      = 0xC2,
    ST77XX_CMD_PWCTR4      = 0xC3,
    ST77XX_CMD_PWCTR5      = 0xC4,
    ST77XX_CMD_VMCTR1      = 0xC5,
    ST77XX_CMD_RDID1       = 0xDA,
    ST77XX_CMD_RDID2       = 0xDB,
    ST77XX_CMD_RDID3       = 0xDC,
    ST77XX_CMD_RDID4       = 0xDD,
    ST77XX_CMD_PWCTR6      = 0xFC,
    ST77XX_CMD_GMCTRP1     = 0xE0,
    ST77XX_CMD_GMCTRN1     = 0xE1,
    ST77XX_CMD_BLACK       = 0x0000,
    ST77XX_CMD_BLUE        = 0x001F,
    ST77XX_CMD_RED         = 0xF800,
    ST77XX_CMD_GREEN       = 0x07E0,
    ST77XX_CMD_CYAN        = 0x07FF,
    ST77XX_CMD_MAGENTA     = 0xF81F,
    ST77XX_CMD_YELLOW      = 0xFFE0,
    ST77XX_CMD_WHITE       = 0xFFFF
} st77xx_cmd_t;

typedef enum {
    ST77XX_INITR_GREENTAB      = 0x00,
    ST77XX_INITR_REDTAB        = 0x01,
    ST77XX_INITR_BLACKTAB      = 0x02,
    ST77XX_INITR_18GREENTAB    = ST77XX_INITR_GREENTAB,
    ST77XX_INITR_18REDTAB      = ST77XX_INITR_REDTAB,
    ST77XX_INITR_18BLACKTAB    = ST77XX_INITR_BLACKTAB,
    ST77XX_INITR_144GREENTAB   = 0x01,
    ST77XX_INITR_MINI160x80    = 0x04,
    ST77XX_INITR_HALLOWING     = 0x05
} st77xx_init_opt_t;

typedef struct st77xx_struct {
    uint8_t width;
    uint8_t height;
    
    /* Private */
    st77xx_init_opt_t option;
    bool (*drv_spi_write)(uint8_t *data, size_t data_length);
    void (*drv_rs_output)(bool state);
    void (*drv_reset_output)(bool state);
    void (*drv_delay_ms)(uint32_t time_ms);
    uint8_t _colstart;
    uint8_t _rowstart;
    uint8_t _xstart;
    uint8_t _ystart;
} st77xx_t;

typedef bool st77xx_status_t;

st77xx_status_t st77xx_init(st77xx_t *st77xx_obj, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t));
void st77XX_execute_cmd_list(st77xx_t *st77xx_obj, const uint8_t *addr);
st77xx_status_t st77xx_write_byte_command(st77xx_t *st77xx_obj, st77xx_cmd_t cmd);
st77xx_status_t st77xx_write_data(st77xx_t *st77xx_obj, uint8_t *data, size_t data_length);
st77xx_status_t st77xx_set_sleep(st77xx_t *st77xx_obj, bool state);
st77xx_status_t st77xx_mem_access(st77xx_t *st77xx_obj, uint8_t st77xx_mem_access_bit);
st77xx_status_t st77xx_interface_pixel_format(st77xx_t *st77xx_obj, uint8_t st77xx_interface_pixel_format_bit);
st77xx_status_t st77xx_gamma_predefined(st77xx_t *st77xx_obj, uint8_t st77xx_gamma_predefined_bit);
st77xx_status_t st77xx_display_inversion(st77xx_t *st77xx_obj, st77xx_cmd_t st77xx_display_inversion_bit);
st77xx_status_t st77xx_display_rotation(st77xx_t *st77xx_obj, uint8_t index_rotation);
st77xx_status_t st77xx_tearing_effect_line(st77xx_t *st77xx_obj, uint8_t tearing);
st77xx_status_t st77xx_display_mode(st77xx_t *st77xx_obj, bool state_on_off);
st77xx_status_t st77xx_active_memory_write(st77xx_t *st77xx_obj);
st77xx_status_t st77xx_window_position(st77xx_t *st77xx_obj,
    uint8_t x0,
    uint8_t y0,
    uint8_t x1,
    uint8_t y1
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ST77XX_H__ */

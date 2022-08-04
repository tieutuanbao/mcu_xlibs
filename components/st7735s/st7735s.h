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

#define ST7735S_COMMAND_MODE    false
#define ST7735S_DATA_MODE       true

typedef bool st7735s_status_t;

/**
 * @brief Define bit: ST7735S Memmory access
 */
#define ST7735S_MADCTL_MY       (1<<7)    /* Row Address Order */
#define ST7735S_MADCTL_MX       (1<<6)    /* Column Address Order */
#define ST7735S_MADCTL_MV       (1<<5)    /* Row / Column Exchange */
#define ST7735S_MADCTL_ML       (1<<4)    /* Vertical Refresh Order */
#define ST7735S_MADCTL_BGR      (1<<3)    /* RGB or BGR Order */
#define ST7735S_MADCTL_MH       (1<<2)    /* Horizontal Refresh Order */
#define ST7735S_MADCTL_DEFAULT  0         /* Default state */

/**
 * @brief Danh sách command st7735s 
 */
typedef enum {
    ST7735S_CMD_SWRESET     = 0x01,    /* Software Reset (pdf v1.4 p108) */
    ST7735S_CMD_SLPIN       = 0x10,    /* Sleep In (pdf v1.4 p119) */
    ST7735S_CMD_SLPOUT      = 0x11,    /* Sleep Out (pdf v1.4 p120) */
    ST7735S_CMD_INVOFF      = 0x20,    /* Display Inversion Off (pdf v1.4 p123) */
    ST7735S_CMD_INVON       = 0x21,    /* Display Inversion On (pdf v1.4 p124) */
    ST7735S_CMD_GAMSET      = 0x26,    /* Gamma Set (pdf v1.4 p125) */
    ST7735S_CMD_DISPOFF     = 0x28,    /* Display Off (pdf v1.4 p126) */
    ST7735S_CMD_DISPON      = 0x29,    /* Display On (pdf v1.4 p127) */
    ST7735S_CMD_CASET       = 0x2A,    /* Column Address Set (pdf v1.4 p128-129) */
    ST7735S_CMD_RASET       = 0x2B,    /* Row Address Set (pdf v1.4 p130-131) */
    ST7735S_CMD_RAMWR       = 0x2C,    /* Memory Write (pdf v1.4 p132) */
    ST7735S_CMD_TEOFF       = 0x34,    /* Tearing Effect Line OFF (pdf v1.4 p139) */
    ST7735S_CMD_TEON        = 0x35,    /* Tearing Effect Line ON (pdf v1.4 p140) */
    ST7735S_CMD_MADCTL      = 0x36,    /* Memory Data Access Control (pdf v1.4 p142) */
    ST7735S_CMD_IDMOFF      = 0x38,    /* Idle Mode Off (pdf v1.4 p147) */
    ST7735S_CMD_IDMON       = 0x39,    /* Idle Mode On (pdf v1.4 p148) */
    ST7735S_CMD_COLMOD      = 0x3A,    /* Interface Pixel Format (pdf v1.4 p150) */
} s7735s_cmd_t;

typedef struct st7735s_struct {
    bool (*drv_spi_write)(uint8_t *data, size_t data_length);
    void (*drv_rs_output)(bool state);
    void (*drv_reset_output)(bool state);
    void (*drv_delay_ms)(uint32_t time_ms);
} st7735s_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ST7735S_H__ */
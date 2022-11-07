#ifndef __ST7735_H__
#define __ST7735_H__

#include "st77xx.h"
#include <stdint.h>
#include <stdbool.h>

#define ST7735_TFTWIDTH_128     128 // for 1.44 and mini
#define ST7735_TFTWIDTH_80      80  // for mini
#define ST7735_TFTHEIGHT_128    128 // for 1.44" display
#define ST7735_TFTHEIGHT_160    160 // for 1.8" and mini display

#define ST7735_MADCTL_BGR   0x08
#define ST7735_MADCTL_MH    0x04

typedef enum {
    ST7735_CMD_FRMCTR1      = 0xB1,
    ST7735_CMD_FRMCTR2      = 0xB2,
    ST7735_CMD_FRMCTR3      = 0xB3,
    ST7735_CMD_INVCTR       = 0xB4,
    ST7735_CMD_DISSET5      = 0xB6,

    ST7735_CMD_PWCTR1       = 0xC0,
    ST7735_CMD_PWCTR2       = 0xC1,
    ST7735_CMD_PWCTR3       = 0xC2,
    ST7735_CMD_PWCTR4       = 0xC3,
    ST7735_CMD_PWCTR5       = 0xC4,
    ST7735_CMD_VMCTR1       = 0xC5,

    ST7735_CMD_PWCTR6       = 0xFC,

    ST7735_CMD_GMCTRP1      = 0xE0,
    ST7735_CMD_GMCTRN1      = 0xE1
} ST7735_CMD_t;

st77xx_status_t ST7735R_init(st77xx_t *st77xx_obj, st77xx_init_opt_t options, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t));
st77xx_status_t ST7735B_init(st77xx_t *st77xx_obj, bool (*drv_spi_write)(uint8_t *, size_t), void (*drv_rs_output)(bool), void (*drv_reset_output)(bool), void (*drv_delay_ms)(uint32_t));
st77xx_status_t st7735_set_rotation(st77xx_t *st77xx_obj, uint8_t index_rotation);

#endif

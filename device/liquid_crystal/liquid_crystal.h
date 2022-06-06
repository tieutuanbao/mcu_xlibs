/**
 ******************************************************************************
 * @file            : liquid_crystal.h
 * @brief           : Thư viện điều khiển LCD.
 * @author          : Tiêu Tuấn Bảo
 ******************************************************************************
 * @attention
 *
 * Thư viện lập trình LCD
 ******************************************************************************
 */
#ifndef __LIQUID_CRYSTAL_H
#define __LIQUID_CRYSTAL_H

#include <stdint.h>


#define LCD_LINE0        0x00
#define LCD_LINE1        0x40
#define LCD_LINE2        0x14
#define LCD_LINE3        0x54

#define LIQUID_CRYSTAL_CMD_CLEAR_DISP                   0x01
#define LIQUID_CRYSTAL_CMD_RET_HOME                     0x02
#define LIQUID_CRYSTAL_CMD_CGRAM                        0x40
#define LIQUID_CRYSTAL_CMD_DDRAM                        0x80

typedef enum {
    liquid_crystal_cmd      =       0,
    liquid_crystal_data     =       1
} liquid_crystal_type_data_t;

typedef enum {
    liquid_crystal_interface_8b,
    liquid_crystal_interface_4b
} liquid_crystal_interface_t;

typedef struct {
    liquid_crystal_interface_t interface;
    void (*send)(uint8_t data, liquid_crystal_type_data_t cmd_or_data);
    void (*delay_us)(uint32_t us);
} liquid_crystal_t;

void liquid_crystal_init(liquid_crystal_t *dev,
                                                 void (*send)(uint8_t data, liquid_crystal_type_data_t cmd_or_data),
                                                 void (*delay_us)(uint32_t us),
                                                 liquid_crystal_interface_t interface);
void liquid_crystal_write(liquid_crystal_t *dev, uint8_t data, liquid_crystal_type_data_t cmd_or_data);

void liquid_crystal_clear(liquid_crystal_t *dev);
void liquid_crystal_set_cursor(liquid_crystal_t *dev, uint8_t x_pos, uint8_t y_pos);
void liquid_crystal_printf(liquid_crystal_t *dev_lcd, uint8_t x_pos, uint8_t y_pos, uint8_t *buf, uint8_t len);
void liquid_crystal_write_cgram(liquid_crystal_t *dev, uint8_t add, uint8_t *data);
void liquid_crystal_read_cgram(liquid_crystal_t *dev, uint8_t add);
void liquid_crystal_printf_special_char(liquid_crystal_t *dev, uint8_t x_pos, uint8_t y_pos, uint8_t *data);

#endif

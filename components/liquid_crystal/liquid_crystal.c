/**
 ******************************************************************************
 * @file             : liquid_crystal.c
 * @brief            : Thư viện điều khiển LCD.
 * @author           : Tiêu Tuấn Bảo
 ******************************************************************************
 * @attention
 *
 * Thư viện lập trình LCD
 ******************************************************************************
 */
#include "liquid_crystal.h"


void liquid_crystal_init(liquid_crystal_t *dev,
                        void (*send)(uint8_t data, liquid_crystal_type_data_t cmd_or_data),
                        void (*delay_us)(uint32_t us),
                        liquid_crystal_interface_t interface) {
    dev->send = send;
    dev->delay_us = delay_us;
    dev->interface = interface;
    if(dev->interface == liquid_crystal_interface_8b) {

    }
    else if(dev->interface == liquid_crystal_interface_4b) {
        dev->delay_us(20000);        // Chờ ít nhất 20ms
        dev->send(0x03, liquid_crystal_cmd);
        dev->delay_us(4500);        // Chờ ít nhất 4.1ms
        dev->send(0x03, liquid_crystal_cmd);
        dev->delay_us(150);            // Chờ ít nhất 100us
        dev->send(0x03, liquid_crystal_cmd);
        dev->send(0x02, liquid_crystal_cmd);
        /*0bXX1DNFXX where    D = Interface 4/8bit :    0 for 4bit interface
                                                                                                1 for 8bit interface
                                                N = Number of 'lines':    0 for 1/8 duty cycle -- 1 'line'
                                                                                                1 for 1/16 duty cycle -- 2 `lines'
                                                F = font:                                0 for 5x7 dot matrix
                                                                                                1 for 5x10 dot matrix
                                                X = don't care
        */
        liquid_crystal_write(dev, 0x28, liquid_crystal_cmd);
    }
    /* Display Off, Cursor Off, Blink Off */
    liquid_crystal_write(dev, 0x08, liquid_crystal_cmd);
    /* Entry Mode: Inc cursor to the right when writing and don’t shift screen */
    liquid_crystal_write(dev, 0x06, liquid_crystal_cmd);
    /* Display On, Cursor Off, Blink Off */
    liquid_crystal_write(dev, 0x0C, liquid_crystal_cmd);
    /* Clear Screen */
    liquid_crystal_clear(dev);
}

void liquid_crystal_write(liquid_crystal_t *dev, uint8_t data, liquid_crystal_type_data_t cmd_or_data) {
    /* Write data */
    if(dev->interface == liquid_crystal_interface_4b) {
        /* Send 4-bit MSB */
        dev->send(data >> 4, cmd_or_data);
        /* Send 4-bit LSB */
        dev->send(data, cmd_or_data);
        dev->delay_us(1000);
    }else {
        /* Send 8-bit */
        dev->send(data, cmd_or_data);
        dev->delay_us(40);
    }
}
void liquid_crystal_clear(liquid_crystal_t *dev) {
    liquid_crystal_write(dev, LIQUID_CRYSTAL_CMD_CLEAR_DISP, liquid_crystal_cmd);
    dev->delay_us(1600);        // Chờ ít nhất 1.52ms
}
void liquid_crystal_set_cursor(liquid_crystal_t *dev, uint8_t x_pos, uint8_t y_pos) {
    switch(y_pos) {
        case 0:
            liquid_crystal_write(dev, (LCD_LINE0|LIQUID_CRYSTAL_CMD_DDRAM) + x_pos, liquid_crystal_cmd);
            break;
        case 1:
            liquid_crystal_write(dev, (LCD_LINE1|LIQUID_CRYSTAL_CMD_DDRAM) + x_pos, liquid_crystal_cmd);
            break;
        case 2:
            liquid_crystal_write(dev, (LCD_LINE2|LIQUID_CRYSTAL_CMD_DDRAM) + x_pos, liquid_crystal_cmd);
            break;
        case 3:
            liquid_crystal_write(dev, (LCD_LINE3|LIQUID_CRYSTAL_CMD_DDRAM) + x_pos, liquid_crystal_cmd);
            break;
    }
    dev->delay_us(500);
}

void liquid_crystal_printf(liquid_crystal_t *dev, uint8_t x_pos, uint8_t y_pos, uint8_t *buf, uint8_t len) {
    liquid_crystal_set_cursor(dev, x_pos, y_pos);
    while(len--) {
        liquid_crystal_write(dev, *buf, liquid_crystal_data);
        buf++;
    }
}

void liquid_crystal_write_cgram(liquid_crystal_t *dev, uint8_t add, uint8_t *data) {
    liquid_crystal_write(dev, LIQUID_CRYSTAL_CMD_CGRAM, liquid_crystal_cmd);
    dev->delay_us(50);
    for(uint8_t index_byte = 0; index_byte < 8; index_byte++) {
        liquid_crystal_write(dev, data[index_byte], liquid_crystal_data);
    }
    dev->delay_us(100);
}

void liquid_crystal_read_cgram(liquid_crystal_t *dev, uint8_t add) {
    liquid_crystal_write(dev, add, liquid_crystal_data);
}

void liquid_crystal_printf_special_char(liquid_crystal_t *dev, uint8_t x_pos, uint8_t y_pos, uint8_t *data) {
    liquid_crystal_write_cgram(dev, 0, data);
    liquid_crystal_set_cursor(dev, x_pos, y_pos);
    liquid_crystal_read_cgram(dev, 0);
}

/**
  ******************************************************************************
  * @file           : gpio.h
  * @brief          : Thư viện driver io lập trình nuvoton ms51.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>
#include "reg_ms51.h"


typedef enum {
    GPIO_QUASI                =        0,
    GPIO_PUSHPULL            =        1,
    GPIO_INPUT                =        2,
    GPIO_OPEN_DRAIN        =        3
} gpio_mode_t;

void gpio0_config(uint8_t pin, gpio_mode_t mode);
void gpio1_config(uint8_t pin, gpio_mode_t mode);
void gpio3_config(uint8_t pin, gpio_mode_t mode);
void gpio_init(void);

#endif

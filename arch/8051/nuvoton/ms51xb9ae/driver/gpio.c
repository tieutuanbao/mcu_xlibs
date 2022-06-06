/**
  ******************************************************************************
  * @file           : gpio.c
  * @brief          : Thư viện driver io lập trình nuvoton ms51.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

#include "gpio.h"
#include "main.h"

void gpio0_config(uint8_t pin, gpio_mode_t mode) {
    if(mode & 0x01) P0M2 |= pin;
    else P0M2 &= ~pin;
    if(mode & 0x02) P0M1 |= pin;
    else P0M1 &= ~pin;
}
void gpio1_config(uint8_t pin, gpio_mode_t mode) {
    if(mode & 0x01) P1M2 |= pin;
    else P1M2 &= ~pin;
    if(mode & 0x02) P1M1 |= pin;
    else P1M1 &= ~pin;
}
void gpio3_config(uint8_t pin, gpio_mode_t mode) {
    if(mode & 0x01) P3M2 |= pin;
    else P3M2 &= ~pin;
    if(mode & 0x02) P3M1 |= pin;
    else P3M1 &= ~pin;
}

void gpio_init(void) {
    /* Output */
    gpio0_config(SET_BIT0|SET_BIT1|SET_BIT2|SET_BIT5|SET_BIT6, GPIO_PUSHPULL);
    gpio1_config(SET_BIT0|SET_BIT1|SET_BIT2|SET_BIT5|SET_BIT6, GPIO_PUSHPULL);
    /* Input */
    gpio0_config(SET_BIT3|SET_BIT4|SET_BIT7, GPIO_INPUT);
    gpio1_config(SET_BIT7, GPIO_INPUT);
    gpio3_config(SET_BIT0, GPIO_INPUT);
    gpio1_config(SET_BIT3|SET_BIT4, GPIO_QUASI);
}

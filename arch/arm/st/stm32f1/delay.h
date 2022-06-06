#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>
#include <stm32f1xx.h>


void delay_init(uint8_t SYSCLK);

void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);
void delay_250ns(uint32_t _ns);

#endif
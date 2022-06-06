#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>

void delay_fast_us(uint8_t us);
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);

#endif
#include "delay.h"

void delay_us(uint16_t us) {
    for(;us>0;us--) {
        asm("nop; nop; nop; nop; nop;");
    }
}

void delay_ms(uint16_t ms) {
    for(;ms>0;ms--) {
        delay_us(1000);
    }
}

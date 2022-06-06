#include "User_delay.h"

void delay_us(unsigned int us) {
    while(us--) {
        _nop_();
    }
}

void delay_ms(unsigned int ms) {
    while(ms--) {
        delay_us(1000);
    }
}

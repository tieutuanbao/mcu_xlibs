#ifndef __MILLIS_H
#define __MILLIS_H

#include <stdint.h>

void millis_init(uint8_t systick_clock);
uint32_t millis(void);

#endif
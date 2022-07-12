#ifndef __STRIP_LED_H
#define __STRIP_LED_H

#include "strip_led_misc.h"
#include "rainbow.h"
#include "meteor.h"

typedef struct  __attribute__((packed)) {
    draw_reg_t **effects;
    rgb_color_t *color_buf;
    uint16_t length;
    uint8_t current_effect;
} strip_led_t;

strip_led_t __attribute__((section(".irom0.text"))) new_strip_led(rgb_color_t *color_buf, uint16_t length);
draw_stt_t __attribute__((section(".irom0.text"))) strip_led_update(strip_led_t *dev, uint32_t current_time);
bool __attribute__((section(".irom0.text"))) strip_led_add_effect(strip_led_t *dev, void *effect);
bool __attribute__((section(".irom0.text"))) strip_led_remove_effect(strip_led_t *dev, void *effect);

#endif
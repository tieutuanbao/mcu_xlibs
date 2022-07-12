#include "strip_led.h"

#define DB_TAG     "strip_led.c"

strip_led_t ICACHE_FLASH_ATTR new_strip_led(rgb_color_t *color_buf, uint16_t length){
    strip_led_t ret;
    ret.color_buf = color_buf;
    ret.length = length;
    ret.current_effect = 0;
    ret.effects = 0;
    return ret;
}

draw_stt_t ICACHE_FLASH_ATTR strip_led_update(strip_led_t *dev, uint32_t current_time){
    draw_stt_t ret = effect_ending;
    if(((uint32_t **)dev->effects)[0] != 0){
        effect_draw_t p_func = (effect_draw_t)(*(((draw_reg_t **)dev->effects)[0]));
        return (p_func)(((draw_reg_t **)dev->effects)[0], dev->color_buf, dev->length, current_time);
    }
    return ret;
}

bool ICACHE_FLASH_ATTR strip_led_add_effect(strip_led_t *dev, void *effect){
    uint8_t count_effect = 0;
    if(dev->effects == 0){
        dev->effects = malloc(2 * sizeof(void*));
    }
    else {
        /* Đếm số lượng effect có sẵn */
        for(count_effect = 0; count_effect < 255; count_effect++){
            if(dev->effects[count_effect] == 0) break;
        }
        /* Cấp phát lại bộ nhớ */
        dev->effects = realloc(dev->effects, (count_effect + 2) * sizeof(void *));
    }
    if(dev->effects == 0){
        return false;
    }
    ((draw_reg_t **)dev->effects)[count_effect] = effect;
    ((draw_reg_t **)dev->effects)[count_effect + 1] = 0;
    return true;
}

bool ICACHE_FLASH_ATTR strip_led_remove_effect(strip_led_t *dev, void *effect){
    uint8_t count_effect = 0;
    if(effect == 0) return false;
    /* Đếm số lượng effect có sẵn */
    for(count_effect = 0; count_effect < 255; count_effect++){
        if(((draw_reg_t **)dev->effects)[count_effect] == 0) break;
    }
    for(uint8_t idx_effect = 0; idx_effect < count_effect; idx_effect++){
        if(effect == (dev->effects + idx_effect)){
            for(uint8_t idx_effect_2 = idx_effect; idx_effect_2 < (count_effect - 1); idx_effect_2++){
                dev->effects[idx_effect_2] = dev->effects[idx_effect_2 + 1];
            }
            idx_effect--;
            realloc(dev->effects, idx_effect);
            return true;
        }
    }
    return false;
}
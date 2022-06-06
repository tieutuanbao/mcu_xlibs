#ifndef __RAINBOW_H
#define __RAINBOW_H

#include "strip_led_misc.h"

typedef struct __attribute__((aligned(4))) __rainbow_t {
    effect_draw_t draw;
    uint32_t delay_frame;   // Khoảng thời gian delay mỗi frame
    uint32_t frames;        // Số lượng frames (animation) hiệu ứng thực hiện
    uint32_t frame_counter; // Bộ đếm số frame đã chạy
    uint32_t idx_frame;     // frame hiện tại, khác với frame_counter, biến này lưu lại vị trí frame hiện tại, không reset khi thay đổi trạng thái hiệu ứng
    uint32_t offset_time;
    effect_state_t state;
    bool enable;
    struct {
        rgb_color_t *p;
        uint8_t count;
    } colors;
    uint16_t len_per_color; // Độ dài mỗi màu sắc trong hiệu ứng rainbow
} rainbow_t;

draw_stt_t ICACHE_FLASH_ATTR rainbow_draw(struct __rainbow_t *dev, rgb_color_t *color_buf, uint16_t color_buf_len, uint32_t current_time);
rainbow_t ICACHE_FLASH_ATTR new_rainbow(uint16_t steps, uint32_t delay_step, uint16_t len_per_color, effect_state_t state);
rgb_color_t ICACHE_FLASH_ATTR *rainbow_add_new_color(rainbow_t *dev, rgb_color_t color);
bool ICACHE_FLASH_ATTR rainbow_remove_color(rainbow_t *dev, rgb_color_t *color);

#endif
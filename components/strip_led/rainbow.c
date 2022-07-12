#include "rainbow.h"

#define DB_TAG  "rainbow.c"

/**
 * @brief Hàm vẽ hiệu ứng Cầu vồng ra mảng color
 * 
 * @param dev : Con trỏ đến hiệu ứng cần thêm màu
 * @param color_buf : Con trỏ đến buffer color cần vẽ
 * @param color_buf_len : Kích thước của buffer
 * @param current_time : Thời gian hiện tại, sử dụng thời gian này để cập nhật animation hiệu ứng
 * @return draw_stt_t : Trạng thái của hiệu ứng
 */
draw_stt_t ICACHE_FLASH_ATTR rainbow_draw(struct __rainbow_t *dev, rgb_color_t *color_buf, uint16_t color_buf_len, uint32_t current_time){
    /* Check enable */
    if(dev->enable == false) return effect_ending;
    /* Delay step effect */
    if((current_time - dev->offset_time) < dev->delay_frame) return effect_waiting;
    else {
        dev->offset_time = current_time;
    }
    rgb_color_t src_color;
    rgb_color_t dest_color;
    uint32_t __idx_node = 0;

    for(uint16_t idx_node = 0; idx_node < color_buf_len; idx_node++){
        __idx_node = (idx_node + dev->idx_frame) % dev->frames;
        /* Lấy màu source và dest theo idx_frame */
        uint16_t pos_color = ((__idx_node / dev->len_per_color) % dev->colors.count);
        /* Lấy màu source */
        src_color = dev->colors.p[pos_color];
        /* Lấy màu destination */
        dest_color = dev->colors.p[(pos_color + 1) % dev->colors.count];
        /* Chuyển đổi màu sắc từ src sang dest theo vị trí từng LED */
        {
            if(src_color.r < dest_color.r){
                color_buf[idx_node].r = ((float)(__idx_node % dev->len_per_color) / (float)dev->len_per_color) * (dest_color.r - src_color.r);
            }
            else if(src_color.r > dest_color.r){
                color_buf[idx_node].r = src_color.r - ((float)(__idx_node % dev->len_per_color) / (float)dev->len_per_color) * (src_color.r - dest_color.r);
            }
            if(src_color.g < dest_color.g){
                color_buf[idx_node].g = ((float)(__idx_node % dev->len_per_color) / (float)dev->len_per_color) * (dest_color.g - src_color.g);
            }
            else if(src_color.g > dest_color.g){
                color_buf[idx_node].g = src_color.g - ((float)(__idx_node % dev->len_per_color) / (float)dev->len_per_color) * (src_color.g - dest_color.g);
            }
            if(src_color.b < dest_color.b){
                color_buf[idx_node].b = ((float)(__idx_node % dev->len_per_color) / (float)dev->len_per_color) * (dest_color.b - src_color.b);
            }
            else if(src_color.b > dest_color.b){
                color_buf[idx_node].b = src_color.b - ((float)(__idx_node % dev->len_per_color) / (float)dev->len_per_color) * (src_color.b - dest_color.b);
            }
            // BITS_LOGD("buf: {%d, %d, %d}, src: {%d, %d, %d}, dest: {%d, %d, %d}, __idx_node: %d, lpc: %d\n", color_buf[idx_node].r, color_buf[idx_node].g , color_buf[idx_node].b, src_color.r, src_color.g, src_color.b, dest_color.r, dest_color.g, dest_color.b, __idx_node, dev->len_per_color);
        }
    }

    /* Đếm số Frame đã chạy */
    dev->frame_counter++;
    if(dev->frame_counter >= dev->frames){
        dev->frame_counter = 0;
        return effect_ending;
    }
    /* Frame đang chạy */
    if(dev->state == effect_dir_left) {
        dev->idx_frame++;
        dev->idx_frame %= dev->frames;
    } else if(dev->state == effect_dir_right) {
        if(dev->idx_frame == 0) dev->idx_frame = dev->frames;
        else dev->idx_frame--;
    }

    return effect_updating;
}

/**
 * @brief Hàm tạo mới hiệu ứng rainbow
 * 
 * @param frames : Số animation trong một hiệu ứng, nên để = (len_per_color * (số lượng màu))
 * @param delay_frame : Delay mỗi animation
 * @param len_per_color : Độ dài mỗi màu trong animation
 * @param state : Trạng thái hoạt động của hiệu ứng
 * @return rainbow_t 
 */
rainbow_t ICACHE_FLASH_ATTR new_rainbow(uint16_t frames, uint32_t delay_frame, uint16_t len_per_color, effect_state_t state){
    rainbow_t ret;
    ret.draw = (effect_draw_t)rainbow_draw;
    ret.state = state;
    ret.delay_frame = delay_frame;
    ret.frames = frames;
    ret.frame_counter = 0;
    ret.idx_frame = 0;
    ret.offset_time = 0;
    ret.len_per_color = len_per_color;
    ret.colors.p = 0;
    ret.colors.count = 0;
    ret.enable = true;
    return ret;
}

/**
 * @brief Hàm tạo mới một màu cho hiệu ứng
 * 
 * @param dev : Con trỏ đến hiệu ứng cần thêm màu
 * @param color : Màu sắc cần thêm
 * @return rgb_color_t* : Trả về con trỏ được cấp phát động, dùng con trỏ này cho hàm remove color để xóa màu.
 */
rgb_color_t ICACHE_FLASH_ATTR *rainbow_add_new_color(rainbow_t *dev, rgb_color_t color){
    if(dev->colors.count == 0){
        dev->colors.p = malloc(sizeof(rgb_color_t));
        if(dev->colors.p == 0){
            return 0;
        }
    }
    else {
        dev->colors.p = realloc(dev->colors.p, (dev->colors.count + 1) * sizeof(rgb_color_t));
        if(dev->colors.p == 0){
            return 0;
        }
    }
    dev->colors.p[dev->colors.count] = color;
    dev->colors.count++;
    return (dev->colors.p + dev->colors.count - 1);
}
/**
 * @brief Hàm xóa màu trong hiệu ứng
 * 
 * @param dev : Con trỏ đến hiệu ứng cần thêm màu
 * @param color : Con trỏ đến màu cần xóa
 * @return true : Xóa thành công
 * @return false : Xóa không thành công
 */
bool ICACHE_FLASH_ATTR rainbow_remove_color(rainbow_t *dev, rgb_color_t *color){
    if(color == 0) return false;
    for(uint8_t idx_color = 0; idx_color < dev->colors.count; idx_color++){
        if(color == (dev->colors.p + idx_color)){
            for(uint8_t idx_color_2 = idx_color; idx_color_2 < (dev->colors.count - 1); idx_color_2++){
                dev->colors.p[idx_color_2] = dev->colors.p[idx_color_2 + 1];
            }
            dev->colors.count--;
            dev->colors.p = realloc(dev->colors.p, dev->colors.count);
            return true;
        }
    }
    return false;
}
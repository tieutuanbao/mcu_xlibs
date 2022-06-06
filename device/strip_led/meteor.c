#include "meteor.h"

/**
 * @brief Hàm vẽ hiệu ứng Sao băng ra mảng color
 * 
 * @param dev           : Con trỏ đến hiệu ứng cần thêm màu
 * @param color_buf     : Con trỏ đến buffer color cần vẽ
 * @param color_buf_len : Kích thước của buffer
 * @param current_time  : Thời gian hiện tại, sử dụng thời gian này để cập nhật animation hiệu ứng
 * @param offset_pos    : Offset vị trí in hiệu ứng
 * @return draw_stt_t   : Trạng thái của hiệu ứng
 */
void ICACHE_FLASH_ATTR meteor_draw(rgb_color_t *color_buf, uint16_t color_buf_len, int32_t offset_pos, strip_color_t *colors, uint8_t colors_size) {
    uint16_t strip_colors_len = 0;
    int32_t idx_effect_node = 0;
    int32_t idx_node_full_strip = 0;

    /* Tính độ dài tổng các dải màu */
    for(uint8_t idx_color_list = 0; idx_color_list < colors_size; idx_color_list++) {
        strip_colors_len += colors[idx_color_list].len;
    }
    /* In từng dải màu */
    for(uint8_t idx_color_list = 0; idx_color_list < colors_size; idx_color_list++) {
        /* In ra giải màu theo offset */
        for(idx_effect_node = 0; idx_effect_node < colors[idx_color_list].len; idx_effect_node++){
            /* Lấy màu source và dest */
            strip_color_t source_color = colors[idx_color_list];
            strip_color_t dest_color = (idx_color_list + 1) == colors_size? (strip_color_t){{0, 0, 0}, 1} : colors[idx_color_list + 1];
            if((offset_pos + idx_node_full_strip) >= 0){
                color_buf[offset_pos + idx_node_full_strip] = source_color.value;
                /* In màu */
                if(source_color.value.r < dest_color.value.r){
                    color_buf[offset_pos + idx_node_full_strip].r = source_color.value.r + (idx_effect_node * (dest_color.value.r - source_color.value.r)) / source_color.len;
                }
                else if(source_color.value.r > dest_color.value.r){
                    color_buf[offset_pos + idx_node_full_strip].r = source_color.value.r - (idx_effect_node * (source_color.value.r - dest_color.value.r)) / source_color.len;
                }
                if(source_color.value.g < dest_color.value.g){
                    color_buf[offset_pos + idx_node_full_strip].g = source_color.value.g + (idx_effect_node * (dest_color.value.g - source_color.value.g)) / source_color.len;
                }
                else if(source_color.value.g > dest_color.value.g){
                    color_buf[offset_pos + idx_node_full_strip].g = source_color.value.g - (idx_effect_node * (source_color.value.g - dest_color.value.g)) / source_color.len;
                }
                if(source_color.value.b < dest_color.value.b){
                    color_buf[offset_pos + idx_node_full_strip].b = source_color.value.b + (idx_effect_node * (dest_color.value.b - source_color.value.b)) / source_color.len;
                }
                else if(source_color.value.b > dest_color.value.b){
                    color_buf[offset_pos + idx_node_full_strip].b = source_color.value.b - (idx_effect_node * (source_color.value.b - dest_color.value.b)) / source_color.len;
                }
                /* Hiệu ứng phân rã */
                if(idx_color_list == 0){
                    if(rand() % 2) {
                        color_buf[offset_pos + idx_node_full_strip] = (rgb_color_t){0, 0, 0};
                    }
                }
            }
            // BITS_LOGD("buf: {%d, %d, %d}, src: {%d, %d, %d}, dest: {%d, %d, %d}, idx_pos_node: %d, pos_show: %d\n", color_buf[offset_pos + idx_node_full_strip].r, color_buf[offset_pos + idx_node_full_strip].g , color_buf[offset_pos + idx_node_full_strip].b, source_color.value.r, source_color.value.g, source_color.value.b, dest_color.value.r, dest_color.value.g, dest_color.value.b, idx_effect_node, offset_pos + idx_node_full_strip);
            /* Vị trí in ra nhỏ hơn 0 thì bỏ qua */
            idx_node_full_strip++;
        }
    }
}
#include "st7920.h"

static inline void st7920_send_byte_data(st7920_t *obj, uint8_t data_byte) {
	obj->drv_send((uint8_t []){0xFA, data_byte & 0xF0, ((data_byte << 4) & 0xF0)}, 3);
}

static inline void st7920_send_byte_command(st7920_t *obj, uint8_t cmd_byte) {
	obj->drv_send((uint8_t []){0xF8, cmd_byte & 0xF0, ((cmd_byte << 4) & 0xF0)}, 3);
}

void st7920_init(st7920_t *obj, bool (*drv_send)(uint8_t *, size_t), void (*drv_delay_ms)(uint32_t)) {
	obj->drv_send = drv_send;
	obj->drv_delay_ms = drv_delay_ms;

	obj->drv_delay_ms(50);

	st7920_send_byte_command(obj, 0x30);
	obj->drv_delay_ms(1);
	st7920_send_byte_command(obj, 0x01);
	obj->drv_delay_ms(10);
    st7920_send_byte_command(obj, 0x06); 
	obj->drv_delay_ms(1);
    st7920_send_byte_command(obj, 0x0C);

    st7920_set_graphicsmode(obj);
}

void st7920_set_graphicsmode(st7920_t *obj) {
    st7920_send_byte_command(obj, 0x20);
	obj->drv_delay_ms(5);
    st7920_send_byte_command(obj, 0x24);
	obj->drv_delay_ms(5);
    st7920_send_byte_command(obj, 0x26);
	obj->drv_delay_ms(5);
}

void st7920_set_textmode(st7920_t *obj) {
    st7920_send_byte_command(obj, 0x20);
	obj->drv_delay_ms(5);
}

void st7920_draw(st7920_t *obj, uint8_t *bitmap){
	uint8_t idx_y, idx_byte_x;
	for(idx_y = 0; idx_y < 64; idx_y++){
		if(idx_y < 32){
			st7920_send_byte_command(obj, 0x80 | idx_y);
			st7920_send_byte_command(obj, 0x80);
		}
		else{
			st7920_send_byte_command(obj, 0x80 | (idx_y - 32));
			st7920_send_byte_command(obj, 0x88);
		}        
		for(idx_byte_x = 0; idx_byte_x < 16; idx_byte_x++){
            st7920_send_byte_data(obj, (bitmap + idx_y * 16)[idx_byte_x]);
        }
	}
}

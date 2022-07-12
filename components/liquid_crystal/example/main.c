/**
 * @brief file example cho thư viện liquid_crystal
 * 
 * */

#include "liquid_crystal.h"


liquid_crystal_t lcd;
/* Ký tự người dùng tạo - Dấu gạch thẳng | */
const uint8_t ver_separator[] = {0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04};

/**
 * @brief lcd_send_4bit_mode
 * 				Hàm driver truyền dữ liệu LCD
 * @param data: dữ liệu truyền cho LCD
 * @param cmd_or_data: dữ liệu là command hay data
 * @return void
 * */
void lcd_send_4bit_mode(uint8_t data, liquid_crystal_type_data_t cmd_or_data){
	LCD_RS = (uint8_t)cmd_or_data;
	LCD_EN = 1;
	delay_us(10);
	LCD_D7 = (data&0x08)?1:0;
	LCD_D6 = (data&0x04)?1:0;
	LCD_D5 = (data&0x02)?1:0;
	LCD_D4 = (data&0x01)?1:0;
	delay_us(10);
	LCD_EN = 0;
	delay_us(5);
	LCD_EN = 1;
}

void main(){
    /* 1 - Cấu hình IO dùng cho LCD */
    
    /* 2 - Khởi tạo LCD */
	liquid_crystal_init(&lcd, lcd_send_4bit_mode, delay_us, liquid_crystal_interface_4b);
    for(;;){
		liquid_crystal_printf(&lcd, 0, 0, "Hello world!", sizeof("Hello world!"));
        liquid_crystal_printf_special_char(&lcd, 6, 1, ver_separator);
    }
}
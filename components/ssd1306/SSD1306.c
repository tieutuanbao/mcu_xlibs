#include "SSD1306.h"

void ssd1306_init(ssd1306_t *module, ssd1306_interfacing_t SSD1306_Intf){
	if((module->delay_ms == 0) ||
		 (module->write == 0) ||
		 (module->set_cs_level == 0) ||
		 (module->set_reset_level == 0) ||
		 (module->height == 0) ||
		 (module->width == 0)){
			 return;
		 }
	
	/* Reset SSD1306 */
	module->set_reset_level(1);
	module->delay_ms(50);
	module->set_reset_level(0);
	module->delay_ms(50);
	module->set_reset_level(1);
	module->delay_ms(50);
	
	module->set_cs_level(false);

	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_DISPLAYOFF}, 1, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETDISPLAYCLOCKDIV, 0x80}, 2, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETMULTIPLEX, module->height - 1}, 2, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETDISPLAYOFFSET, 0x00}, 2, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETSTARTLINE}, 1, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_CHARGEPUMP, module->vddstate == SSD1306_EXTERNALVCC ? 0x10: 0x14}, 2, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SEGREMAP | 0x1}, 1, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_COMSCANDEC}, 1, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETCOMPINS, 0x12}, 2, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETCONTRAST, 0xAF}, 2, 100);
	
	// if((module->Width == 128) && (module->Height == 32)) {
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETCOMPINS}, 1, 100);
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){0x02}, 1, 100);
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETCONTRAST}, 1, 100);
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){0x8F}, 1, 100);
	// } else if((module->Width == 128) && (module->Height == 64)) {
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETCOMPINS}, 1, 100);
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){0x12}, 1, 100);		
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETCONTRAST}, 1, 100);
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){0xCF}, 1, 100);
	// } else if((module->Width == 96) && (module->Height == 16)) {
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETCOMPINS}, 1, 100);
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){0x02}, 1, 100);
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETCONTRAST}, 1, 100);
	// 	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){0xAF}, 1, 100);
	// } else {
	// // Other screen varieties -- TBD
	// }
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETPRECHARGE, module->vddstate == SSD1306_EXTERNALVCC ? 0xF1: 0x22}, 2, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_SETVCOMDETECT, 0x20}, 2, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_NORMALDISPLAY}, 1, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_DISPLAYALLON_RESUME}, 1, 100);
	// module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_DEACTIVATE_SCROLL}, 1, 100);
	module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, (uint8_t []){SSD1306_DISPLAYON}, 1, 100);
	module->set_cs_level(true);
}

/**
 * @brief Hàm output pixel màn hình
 * Mỗi Byte ghi vào sẽ tương ứng 8 hàng điểm ảnh theo thứ tự LSB từ trên xuống dưới
 * Kích thước Height Graphic là bội của 8
 * @param module 
 * @param graph Khối graphic cần vẽ
 * @param Area Khu vực vẽ trên màn hình
 */
void ssd1306_draw(ssd1306_t *module, uint8_t *Buf, Size_t BufSize, Area_t Area) {
	uint8_t idx_line = 0, tempByte = 0;
	Size_t DrawSize;
	DrawSize.Height = (Area.Stop.Y - Area.Start.Y) + 1;
	DrawSize.Width = (Area.Stop.X - Area.Start.X) + 1;
	if(BufSize.Height < DrawSize.Height) {
		DrawSize.Height = BufSize.Height;
	}
	if(BufSize.Width < DrawSize.Width) {
		DrawSize.Width = BufSize.Width;
	}
	DrawSize.Height >>= 3; 
	module->set_cs_level(false);
	for(idx_line = 0; idx_line < DrawSize.Height; idx_line++) {
		tempByte = SSD1306_PAGEADDR + idx_line + (Area.Start.Y >> 3);
		module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, &tempByte, 1, 100);
		tempByte = SSD1306_SETLOWCOLUMN + (Area.Start.X & 0xFF);
		module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, &tempByte, 1, 100);
		tempByte = SSD1306_SETHIGHCOLUMN + (Area.Start.X >> 4);
		module->write(SSD1306_I2S_ADDRESS, SSD1306_COMMAND, &tempByte, 1, 100);
		module->write(SSD1306_I2S_ADDRESS, SSD1306_DATA, Buf + idx_line * BufSize.Width, DrawSize.Width, 100);
	}
	module->set_cs_level(true);
}

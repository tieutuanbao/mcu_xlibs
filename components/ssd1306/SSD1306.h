#ifndef __SSD1306_H
#define __SSD1306_H

#include <stdint.h>
#include <stdbool.h>
#include "graphic.h"

/******************************************************************************
 SSD1306 ID and Command List
 ******************************************************************************/
#define SSD1306_I2S_ADDRESS			0x78
#define SSD1306_DATA                0x40
#define SSD1306_COMMAND             0x00

#define SSD1306_MEMORYMODE          0x20 ///< See datasheet
#define SSD1306_COLUMNADDR          0x21 ///< See datasheet
#define SSD1306_PAGEADDR            0xB0 ///< See datasheet
#define SSD1306_SETCONTRAST         0x81 ///< See datasheet
#define SSD1306_CHARGEPUMP          0x8D ///< See datasheet
#define SSD1306_SEGREMAP            0xA0 ///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SSD1306_DISPLAYALLON        0xA5 ///< Not currently used
#define SSD1306_NORMALDISPLAY       0xA6 ///< See datasheet
#define SSD1306_INVERTDISPLAY       0xA7 ///< See datasheet
#define SSD1306_SETMULTIPLEX        0xA8 ///< See datasheet
#define SSD1306_DISPLAYOFF          0xAE ///< See datasheet
#define SSD1306_DISPLAYON           0xAF ///< See datasheet
#define SSD1306_COMSCANINC          0xC0 ///< Not currently used
#define SSD1306_COMSCANDEC          0xC8 ///< See datasheet
#define SSD1306_SETDISPLAYOFFSET    0xD3 ///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5 ///< See datasheet
#define SSD1306_SETPRECHARGE        0xD9 ///< See datasheet
#define SSD1306_SETCOMPINS          0xDA ///< See datasheet
#define SSD1306_SETVCOMDETECT       0xDB ///< See datasheet

#define SSD1306_SETLOWCOLUMN        0x0C ///< Not currently used
#define SSD1306_SETHIGHCOLUMN       0x11 ///< Not currently used
#define SSD1306_SETSTARTLINE        0x40 ///< See datasheet

#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26 ///< Init rt scroll
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27 ///< Init left scroll
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A ///< Init diag scroll
#define SSD1306_DEACTIVATE_SCROLL                    0x2E ///< Stop scroll
#define SSD1306_ACTIVATE_SCROLL                      0x2F ///< Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 ///< Set scroll range

#define SSD1306_invertDisplay(module)		SSD1306_write(SSD1306_INVERTDISPLAY,SSD1306_COMMAND)
#define SSD1306_normalDisplay(module)		SSD1306_write(SSD1306_NORMALDISPLAY,SSD1306_COMMAND)

typedef enum{
	SSD1306_SPI_4_WIRE,
	SSD1306_PARALLEL_6080,
	SSD1306_I2C,
	SSD1306_PARALLEL_8080,
	SSD1306_SPI_3_WIRE
} ssd1306_interfacing_t;

typedef enum {
	SSD1306_EXTERNALVCC		= 0x01,	///< External display voltage source
	SSD1306_SWITCHCAPVCC	= 0x02	///< Gen. display voltage from 3.3V
} ssd1306_VddState_t;

typedef struct{
	void (*set_reset_level)(bool level);
	void (*set_cs_level)(bool level);
	void (*write)(uint8_t address, uint8_t memReg, uint8_t *pData, uint32_t dataLen, uint32_t timeout);
	void (*delay_ms)(uint32_t time);
	ssd1306_VddState_t vddstate;
	uint16_t width;
	uint16_t height;
} ssd1306_t;
/****************************************************************************/

void ssd1306_init(ssd1306_t *module, ssd1306_interfacing_t SSD1306_Intf);
void ssd1306_draw(ssd1306_t *module, uint8_t *Buf, Size_t BufSize, Area_t area);

#endif

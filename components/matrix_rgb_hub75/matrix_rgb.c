/**
  ******************************************************************************
  * @file           : Matrix_LED.c
  * @brief          : Thư viện điều khiển LED ma trận.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    * Thư viện lập trình LED ma trận RGB chế độ quét 1/2 (2 line RGB) cho STM32.
    *    Các chân điều khiển Data và Row phải sắp xếp nối tiếp trong cùng một Port.
    * Định nghĩa các GPIO sử dụng trong thư viện:
    *
    *    |---------------|
    *    |    R1    -->    PIN0    |
    *    |    G1    -->    PIN1    |
    *    |    B1    -->    PIN2    |
    *    |    R2    -->    PIN3    |
    *    |    G2    -->    PIN4    |
    *    |    B2    -->    PIN5    |
    *    |    CLK    -->    PIN6    |
    *    |---------------|
    *    |    A        -->    B0        |
    *    |    B        -->    B1        |
    *    |    C        -->    B2        |
    *    |    D        -->    B3        |
    *    |---------------|
  *
  ******************************************************************************
  */

#include "matrix_rgb.h"

uint8_t _Matrix_BufferGPIO[MATRIX_BIT_PER_PIXCEL][MATRIX_HEIGHT/2][MATRIX_WIDTH];

const uint16_t timerPSC[] = {18,36,72,144,288,576,1152,2304,4608};

_MATRIX_matrixDriverParam MATRIX_matrixDriverParam;

static uint16_t bit_pos = 0;
static uint16_t _h=0;
static uint16_t _w=0;
static uint8_t _bittmp;

void MATRIX_Update(uint8_t _MATRIX_BufferRGB[3][MATRIX_HEIGHT][MATRIX_WIDTH]) {
    for(bit_pos=0;bit_pos<MATRIX_BIT_PER_PIXCEL;bit_pos++) {
        for(_h=0;_h<MATRIX_HEIGHT/2;_h++) {
            for(_w=0;_w<MATRIX_WIDTH;_w++) {
                _bittmp = ((_MATRIX_BufferRGB[0][_h]          [_w] & (1<<bit_pos)) != 0 )?0x20:0; //ghi bit B2
                _bittmp |= ((_MATRIX_BufferRGB[1][_h]          [_w] & (1<<bit_pos)) != 0 )?0x10:0; //ghi bit G2
                _bittmp |= ((_MATRIX_BufferRGB[2][_h]          [_w] & (1<<bit_pos)) != 0 )?0x08:0; //ghi bit R2

                _bittmp |= ((_MATRIX_BufferRGB[0][_h+16]  [_w] & (1<<bit_pos)) != 0 )?0x04:0; //ghi bit B1
                _bittmp |= ((_MATRIX_BufferRGB[1][_h+16]  [_w] & (1<<bit_pos)) != 0 )?0x02:0; //ghi bit G1
                _bittmp |= ((_MATRIX_BufferRGB[2][_h+16]  [_w] & (1<<bit_pos)) != 0 )?0x01:0; //ghi bit R1
                _Matrix_BufferGPIO[bit_pos][_h][_w] = _bittmp;
            }
        }
    }
}


void MATRIX_draw_point(uint16_t x_pos, uint16_t y_pos, argb_color_t color) {
    if(y_pos<16) {
        for(bit_pos=0;bit_pos<MATRIX_BIT_PER_PIXCEL;bit_pos++) {
            _bittmp = color.b & (1<<bit_pos)?0x20:0;
            _bittmp |= color.g & (1<<bit_pos)?0x10:0;
            _bittmp |= color.r & (1<<bit_pos)?0x08:0;
            _Matrix_BufferGPIO[bit_pos][y_pos][x_pos] = (_Matrix_BufferGPIO[bit_pos][y_pos][x_pos]&0x07)|_bittmp;
        }
    }else {
        y_pos%=16;
        for(bit_pos=0;bit_pos<MATRIX_BIT_PER_PIXCEL;bit_pos++) {
            _bittmp = color.b & (1<<bit_pos)?0x04:0;
            _bittmp |= color.g & (1<<bit_pos)?0x02:0;
            _bittmp |= color.r & (1<<bit_pos)?0x01:0;
            _Matrix_BufferGPIO[bit_pos][y_pos%16][x_pos] = (_Matrix_BufferGPIO[bit_pos][y_pos][x_pos]&0x38)|_bittmp;
        }
    }
}

/**
  ******************************************************************************
  * @file           : adc.h
  * @brief          : Thư viện driver adc lập trình nuvoton ms51.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */
#include "adc.h"

void adc_init(void) {
    /* Enable all input */
    AINDIDS = 0x00;
    /* Clear flag conversion complete */
    ADCF = 0;
}

void adc_select_channel(uint8_t channel) {
    /* Chọn kênh adc ADCHS[3:0] */
    ADCCON0 &= 0xF0;
    ADCCON0 |= channel;
}

uint16_t adc_read(void) {
    uint16_t timeout = 0;
    uint16_t ret;
    /* Clear flag conversion complete */
    ADCF = 0;
    /* Enable adc */
    ADCCON1 |= 0x01;
    /* Bắt đầu chuyển đổi */
    ADCS = 1;
    /* Chờ chuyển đổi hòa thành */
    while((!ADCF) && (timeout++ < 0xFFFF));
    ret = (ADCRH << 4);
    ret += ADCRL;
    return ret;
}

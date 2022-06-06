/**
  ******************************************************************************
  * File Name          : User_ADC.c
  * Description        : File cấu hình ADC.
    * Author                         : Tieu Tuan Bao
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "user_ADC.h"


/*******************************************************
---->        Cấu hình ADC
*******************************************************/
void ADC_Config() {
  /* ADC Low speed initial */
    ADCCON1|=0X30;            /* clock divider */
    ADCCON2|=0X0E;            /* AQT time */
}

/*******************************************************
---->        Hàm ADC
*******************************************************/
uint16_t ADC_read(uint8_t _ADCchannel) {
    uint16_t _timeoutADC = 0;
    ADCCON0&=0xF0;
    ADCCON0|=_ADCchannel;
    AINDIDS=0x00;
    AINDIDS |= (0x01<<_ADCchannel);
    ADCCON1 |= 0x01;

    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;
    while(!ADCF || _timeoutADC++>3000);
    return (((uint16_t)ADCRL & 0x00ff) | ((uint16_t)ADCRH << 4));
}

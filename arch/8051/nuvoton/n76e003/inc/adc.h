/**
  ******************************************************************************
  * File Name          : User_ADC.h
  * Description        : File cấu hình ADC.
    * Author                         : Tieu Tuan Bao
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#ifndef __ADC_H
#define __ADC_H

#include "main.h"

void ADC_Config();
uint16_t ADC_read(uint8_t _ADCchannel);

#endif

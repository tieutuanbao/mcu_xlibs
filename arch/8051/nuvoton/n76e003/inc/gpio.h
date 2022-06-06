/**
  ******************************************************************************
  * @file           : gpio.h
  * @brief          : Thư viện lập trình chip N76E003.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "main.h"

typedef struct {
  unsigned char Value : 3;
} TypeGPIOMode;

#define PIN0                    0x01
#define PIN1                    0x02
#define PIN2                    0x04
#define PIN3                    0x08
#define PIN4                    0x10
#define PIN5                    0x20
#define PIN6                    0x40
#define PIN7                    0x80

//---------------------------------------------------------------------------
//            GPIO Project Initialize
//---------------------------------------------------------------------------
void GPIO_Init(void);

#endif

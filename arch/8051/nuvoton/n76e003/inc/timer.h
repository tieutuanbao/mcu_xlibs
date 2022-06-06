/**
  ******************************************************************************
  * File Name          : User_Timer.c
  * Description        : File cấu hình và khởi tạo Timer.
    * Author                         : Tieu Tuan Bao
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#ifndef __TIMER_H__
#define __TIMER_H__

#include "main.h"

#define Interrupt_Enable    set_EA
#define Interrupt_Disable    clr_EA
void T0M0_Config(uint16_t VALUE);
void T0M0_Reset_Reg();

void T1M0_Config(uint16_t VALUE);
void TIM2_Config(uint16_t _timer2_counter_value);

void PWM_Init();
void PWM5_Config(float _PWM3_Freq, uint8_t _PWM3_Duty);

#endif

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

#include "User_Timer.h"

extern uint8_t BIT_TMP;

unsigned char TL0_Val=0;
unsigned char TH0_Val=0;

void T0M0_Config(uint16_t VALUE) {
    TMOD = 0XFF;
    TIMER0_MODE0_ENABLE;
    set_T0M;
    TL0_Val = (VALUE&0x001F);
    TL0 = (VALUE&0x001F);
    TH0_Val = ((VALUE>>5)&0x00FF);
    TH0 = ((VALUE>>5)&0x00FF);
    set_ET0;
    set_EA;
    set_TR0;
}

void T0M0_Reset_Reg() {
    TL0 = TL0_Val;
    TH0 = TH0_Val;
}

void T1M0_Config(uint16_t VALUE) {
    TMOD = 0XFF;
    TIMER1_MODE0_ENABLE;
    clr_T1M;
    TL1 = (VALUE&0x00ff);
    TH1 = ((VALUE&0xff00)>>8)<<3;
    set_ET1;
    set_EA;
    set_TR1;
}


void TIM2_Config(uint16_t _timer2_counter_value) {
    TIMER2_Auto_Reload_Delay_Mode;
    TIMER2_DIV_16;

    RCMP2L = 65536-(_timer2_counter_value);
    RCMP2H = (65536-(_timer2_counter_value))>>8;
    TL2 = 0;
    TH2 = 0;

    set_ET2;                                    // Enable Timer2 interrupt
    set_TR2;                                    // Timer2 run
}

void PWM_Init() {
    PWM5_P15_OUTPUT_ENABLE;
    PWM_IMDEPENDENT_MODE;
    PWM_CLOCK_FSYS;
    /**********************************************************************
        PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV>
                                    = (16MHz/8)/(0x7CF + 1)
                                    = 1KHz (1ms)
    ***********************************************************************/
    //-------- PWM start run--------------
    set_PWMCON0_PWMRUN;
}


void PWM5_Config(float _PWM3_Freq, uint8_t _PWM3_Duty) {
    uint16_t _duty=0;
    _PWM3_Duty++;
    PWMPH = (((uint16_t)(((24000000.0/1.0)/_PWM3_Freq)-1)>>8)&0xff);
    PWMPL = (uint16_t)(((24000000.0/1.0)/_PWM3_Freq)-1)&0xff;
    _duty=((((uint16_t)PWMPH&0xFFFF)<<8)|PWMPL);
    set_SFRPAGE;
    PWM5H = (((uint32_t)_PWM3_Duty*(uint32_t)_duty)/100)>>8;
    PWM5L = (((uint32_t)_PWM3_Duty*(uint32_t)_duty)/100);
    clr_SFRPAGE;
    PWM5_OUTPUT_INVERSE;
    set_PWMCON0_LOAD;
}

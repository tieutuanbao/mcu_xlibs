/**
  ******************************************************************************
  * File Name          : User_Interrupts.c
  * Description        : File khai báo chương trình ngắt.
    * Author                         : Tieu Tuan Bao
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "User_Interrupts.h"
#include "user_ADC.h"
#include "User_UART.h"

/*******************************************************
---->        Fault_Break Interrupt function
*******************************************************/
#pragma vector = Fault_Break_Interrupt_Vector
__interrupt void Fault_Brack_ISR(void) {
    while(1);
}

/*******************************************************
---->        Timer 0 Overflow Interrupt function
*******************************************************/
#pragma vector = Timer_0_Interrupt_Vector
__interrupt void TIM0_OV_ISR(void) {
//    T0M0_Reset_Reg();
}

/*******************************************************
---->        Timer 2 Overflow Interrupt function
*******************************************************/
#pragma vector = Timer_2_Interrupt_Vector
__interrupt void TIM2_OV_ISR(void) {
    if(Tx_NM.Button[3] == 0 || Tx_BV.Button[3] == 0) {
        if(CounterForReset <= 1000) {
            CounterForReset++;
        }
    }else {
        CounterForReset = 0;
    }
    clr_TF2;
}

/*******************************************************
---->        Pin Interrupt function
*******************************************************/
#pragma vector = Pin_Interrupt_Vector
__interrupt void PIN_Interrupt_ISR(void) {
    if(PIF == 0x20) {
        PIF = 0;

    }
}

/*******************************************************
---->        UART0 Interrupt function
*******************************************************/
#pragma vector = Serial_0_Interrupt_Vector
__interrupt void UART0_Interrupt_ISR(void) {
    if(TI==1) {
        clr_TI;
        UART0.Tx_Cmplt=1;
    }
    if(RI==1) {
        clr_RI;
        if(UART0.Char_Counter<UART_BUFFER_SIZE) {
            if(UART0.Char_Counter == 0) memset(UART0.Data_Buffer,0,UART_BUFFER_SIZE);
            UART0.Data_Buffer[UART0.Char_Counter]=SBUF;
            if(SBUF == '\n') {
                UART0.Rx_Cmplt = 1;
                UART0.Char_Counter = 0;
            }else {
                UART0.Rx_Cmplt = 0;
                UART0.Char_Counter++;
            }
        }
    }
}

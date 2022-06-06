/**
  ******************************************************************************
  * File Name          : interrupt.c
  * Description        : File khai báo chương trình ngắt.
    * Author                         : Tieu Tuan Bao
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "interrupt.h"
#include "reg_ms51.h"
#include "uart.h"

/*******************************************************
---->        Fault_Break Interrupt function
*******************************************************/
#pragma vector = fault_break_interrupt_vector
__interrupt void fault_brack_isr(void) {
    while(1);
}

/*******************************************************
---->        Timer 0 Overflow Interrupt function
*******************************************************/
#pragma vector = timer_0_interrupt_vector
__interrupt void tim0_ovf_interrupt_isr(void) {
//    T0M0_Reset_Reg();
}

/*******************************************************
---->        Timer 2 Overflow Interrupt function
*******************************************************/
#pragma vector = timer_2_interrupt_vector
__interrupt void tim2_ovf_interrupt_isr(void) {
    clr_TF2;
}

/*******************************************************
---->        Pin Interrupt function
*******************************************************/
#pragma vector = pin_interrupt_vector
__interrupt void pin_interrupt_isr(void) {

}

/*******************************************************
---->        UART0 Interrupt function
*******************************************************/
#pragma vector = serial_0_interrupt_vector
__interrupt void uart0_interrupt_isr(void) {
    uart_handler_isr(&uart0);
}

/*******************************************************
---->        UART1 Interrupt function
*******************************************************/
#pragma vector = serial_1_interrupt_vector
__interrupt void uart1_interrupt_isr(void) {
    _push_(SFRS);

    _pop_(SFRS);
}

#ifndef __USER_UART_H
#define __USER_UART_H

#include "main.h"

#define UART_BUFFER_SIZE    50

typedef struct {
    uint8_t Data_Buffer[UART_BUFFER_SIZE];
    uint8_t Char_Counter;
    volatile uint8_t Rx_Cmplt;
    volatile uint8_t Tx_Cmplt;
}UART_Structure;


extern UART_Structure UART0;
extern UART_Structure UART1;


void InitialUART0_Timer1(uint32_t u32Baudrate); //T1M = 1, SMOD = 1
void InitialUART0_Timer3(uint32_t u32Baudrate); //Timer3 as Baudrate, SMOD=1, Prescale=0
void InitialUART1_Timer3(uint32_t u32Baudrate);

void UART0_Send_Char(uint8_t c);
void UART0_Send_String(uint8_t *str, uint16_t length);

void UART1_Send_Char(uint8_t c);
void UART1_Send_String(uint8_t *str);

#endif

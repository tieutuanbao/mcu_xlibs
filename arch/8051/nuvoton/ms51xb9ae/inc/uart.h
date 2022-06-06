/**
    ******************************************************************************
    * @file                        : uart.h
    * @brief                    : Thư viện driver uart lập trình nuvoton ms51.
    * @author                    :    Tiêu Tuấn Bảo
    ******************************************************************************
    * @attention
    *
    *
    ******************************************************************************
    */

#ifndef __UART_H
#define __UART_H

#include <stdint.h>

typedef enum {
    uart0_timer1,
    uart0_timer3,
    uart1_timer3
} uart_select_t;

typedef struct {
    uart_select_t channel;
    uint8_t *rx_buffer;
    uint16_t rx_buffer_size;
    volatile uint8_t rx_count;
    volatile uint8_t rx_cmplt;
    volatile uint8_t tx_cmplt;
} uart_t;

extern uart_t uart0;

void uart_init(uart_t *uart, uint32_t sys_clk, uint32_t baudrate);
void uart_handler_isr(uart_t *uart);
void uart_transmit(uart_t *uart, uint8_t __generic *data_buf, uint16_t len, uint16_t timeout);

#endif

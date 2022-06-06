/**
 ******************************************************************************
 * @file                        : uart.c
 * @brief                    : Thư viện driver uart lập trình nuvoton ms51.
 *    @author                    :    Tiêu Tuấn Bảo
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#include "uart.h"
#include "reg_ms51.h"
#include "delay.h"

void uart_init(uart_t *uart, uint32_t sys_clk, uint32_t baudrate)
{
    switch (uart->channel)
    {
        case uart0_timer1: {
            SCON = 0x50;            //UART0 Mode1,REN=1,TI=1
            TMOD |= 0x20;           //Timer1 Mode1
            set_PCON_SMOD;          //UART0 Double Rate Enable
            set_CKCON_T1M;
            clr_T3CON_BRCK;          //Serial port 0 baud rate clock source = Timer1
            TH1 = 256 - ((sys_clk / 16) / (baudrate + 1));
            set_TCON_TR1;
            set_IE_ES;
            break;
        }
        case uart0_timer3: {
            SCON = 0x50;        // UART0 Mode1,REN=1,TI=1
            set_PCON_SMOD;    // UART0 Double Rate Enable
            T3CON &= 0xF8;    // T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
            set_T3CON_BRCK; // UART0 baud rate clock source = Timer3
            RH3 = HIBYTE(65536 - ((sys_clk / 16) / (baudrate + 1)));
            RL3 = LOBYTE(65536 - ((sys_clk / 16) / (baudrate + 1)));
            set_T3CON_TR3;    // Trigger Timer3
            set_IE_ES;
            break;
        }
        case uart1_timer3: {
            SCON_1 = 0x50;    // UART1 Mode1,REN_1=1,TI_1=1
            T3CON = 0x80;        // T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1
            RH3 = HIBYTE(65536 - (sys_clk / 16 / baudrate));
            RL3 = LOBYTE(65536 - (sys_clk / 16 / baudrate));
            set_T3CON_TR3; // Trigger Timer3
            set_EIE1_ES_1;
            break;
        }
    }
}

void uart_handler_isr(__generic uart_t *uart) {
    _push_(SFRS);
    if ((uart->channel == uart0_timer1) || (uart->channel == uart0_timer3)) {
        if(TI) {
            TI = 0;
            uart->tx_cmplt = 1;
        }
        if(RI) {
            uart->rx_buffer[uart->rx_count] = SBUF;
            if (uart->rx_buffer[uart->rx_count] == 0) {
                uart->rx_buffer[uart->rx_count] = 0;
            }
            if (uart->rx_buffer[uart->rx_count] == '\n') {
                uart->rx_count = 0;
                uart->rx_cmplt = 1;
            }else {
                uart->rx_count++;
            }
            if(uart->rx_count == uart->rx_buffer_size) {
                uart->rx_count = 0;
            }
            RI = 0;
        }
    }else {
        if(TI_1) {
            TI_1 = 0;
            uart->tx_cmplt = 1;
        }
        if(RI_1) {
            uart->rx_buffer[uart->rx_count] = SBUF_1;
            if (uart->rx_buffer[uart->rx_count] == 0) {
                uart->rx_buffer[uart->rx_count] = 0;
            }
            if (uart->rx_buffer[uart->rx_count] == '\n') {
                uart->rx_count = 0;
                uart->rx_cmplt = 1;
            }else {
                uart->rx_count++;
            }
            if(uart->rx_count == uart->rx_buffer_size) {
                uart->rx_count = 0;
            }
            RI_1 = 0;
        }
    }
    _pop_(SFRS);
}

void uart_transmit(uart_t *uart, uint8_t __generic *data_buf, uint16_t len, uint16_t timeout) {
    switch (uart->channel) {
        case uart0_timer1: case uart0_timer3: {
            for(;len && timeout;len--) {
                TI = 0;
                uart->tx_cmplt = 0;
                SBUF = *(data_buf++);
                while((!uart->tx_cmplt) && (--timeout)) delay_ms(1);
            }
            break;
        }
        case uart1_timer3: {
            SCON_1_bit.BIT0 = 0;
            for(;len && timeout;len--) {
                TI_1 = 0;
                uart->tx_cmplt = 0;
                SBUF_1 = *(data_buf++);
                while((!uart->tx_cmplt) && (--timeout)) delay_ms(1);
            }
            SCON_1_bit.BIT0 = 1;
            break;
        }
    }
}

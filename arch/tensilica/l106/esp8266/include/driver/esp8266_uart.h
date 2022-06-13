/**
 * @file esp8266_uart.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ESP_UART_H
#define __ESP_UART_H

#include "driver/esp8266_regs.h"
#include "driver/esp8266_clocks.h"

#define UART_FIFO_MAX       127

#define UART0     ((uart_t *)UART0_BASE)
#define UART1     ((uart_t *)UART1_BASE)

typedef struct struct_uart {
    union {
        struct {
            uint8_t rw_byte;                 /*This register stores one byte data  read by rx fifo.*/
            uint8_t reserved[3];
        };
        volatile const uint32_t val;
    } fifo;
    union {
        struct {
            uint32_t rxfifo_full:      1;           /*This interrupt raw bit turns to high level when receiver receives more data than (rx_flow_thrhd_h3 rx_flow_thrhd).*/
            uint32_t txfifo_empty:     1;           /*This interrupt raw bit turns to high level when the amount of data in transmitter's fifo is less than ((tx_mem_cnttxfifo_cnt) .*/
            uint32_t parity_err:       1;           /*This interrupt raw bit turns to high level when receiver detects the parity error of data.*/
            uint32_t frm_err:          1;           /*This interrupt raw bit turns to high level when receiver detects data's frame error .*/
            uint32_t rxfifo_ovf:       1;           /*This interrupt raw bit turns to high level when receiver receives more data than the fifo can store.*/
            uint32_t dsr_chg:          1;           /*This interrupt raw bit turns to high level when receiver detects the edge change of dsrn signal.*/
            uint32_t cts_chg:          1;           /*This interrupt raw bit turns to high level when receiver detects the edge change of ctsn signal.*/
            uint32_t brk_det:          1;           /*This interrupt raw bit turns to high level when receiver detects the 0 after the stop bit.*/
            uint32_t rxfifo_tout:      1;           /*This interrupt raw bit turns to high level when receiver takes more time than rx_tout_thrhd to receive a byte.*/
            uint32_t reserved9:       23;
        };
        volatile const uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t rxfifo_full:      1;            /*This is the status bit for rxfifo_full_int_raw when rxfifo_full_int_ena is set to 1.*/
            uint32_t txfifo_empty:     1;            /*This is the status bit for  txfifo_empty_int_raw  when txfifo_empty_int_ena is set to 1.*/
            uint32_t parity_err:       1;            /*This is the status bit for parity_err_int_raw when parity_err_int_ena is set to 1.*/
            uint32_t frm_err:          1;            /*This is the status bit for frm_err_int_raw when fm_err_int_ena is set to 1.*/
            uint32_t rxfifo_ovf:       1;            /*This is the status bit for rxfifo_ovf_int_raw when rxfifo_ovf_int_ena is set to 1.*/
            uint32_t dsr_chg:          1;            /*This is the status bit for dsr_chg_int_raw when dsr_chg_int_ena is set to 1.*/
            uint32_t cts_chg:          1;            /*This is the status bit for cts_chg_int_raw when cts_chg_int_ena is set to 1.*/
            uint32_t brk_det:          1;            /*This is the status bit for brk_det_int_raw when brk_det_int_ena is set to 1.*/
            uint32_t rxfifo_tout:      1;            /*This is the status bit for rxfifo_tout_int_raw when rxfifo_tout_int_ena is set to 1.*/
            uint32_t reserved9:       23;
        };
        volatile const uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t rxfifo_full:      1;           /*This is the enable bit for rxfifo_full_int_st register.*/
            uint32_t txfifo_empty:     1;           /*This is the enable bit for rxfifo_full_int_st register.*/
            uint32_t parity_err:       1;           /*This is the enable bit for parity_err_int_st register.*/
            uint32_t frm_err:          1;           /*This is the enable bit for frm_err_int_st register.*/
            uint32_t rxfifo_ovf:       1;           /*This is the enable bit for rxfifo_ovf_int_st register.*/
            uint32_t dsr_chg:          1;           /*This is the enable bit for dsr_chg_int_st register.*/
            uint32_t cts_chg:          1;           /*This is the enable bit for cts_chg_int_st register.*/
            uint32_t brk_det:          1;           /*This is the enable bit for brk_det_int_st register.*/
            uint32_t rxfifo_tout:      1;           /*This is the enable bit for rxfifo_tout_int_st register.*/
            uint32_t reserved9:       23;
        };
        volatile uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t rxfifo_full:      1;           /*Set this bit to clear the rxfifo_full_int_raw interrupt.*/
            uint32_t txfifo_empty:     1;           /*Set this bit to clear txfifo_empty_int_raw interrupt.*/
            uint32_t parity_err:       1;           /*Set this bit to clear parity_err_int_raw interrupt.*/
            uint32_t frm_err:          1;           /*Set this bit to clear frm_err_int_raw interrupt.*/
            uint32_t rxfifo_ovf:       1;           /*Set this bit to clear rxfifo_ovf_int_raw interrupt.*/
            uint32_t dsr_chg:          1;           /*Set this bit to clear the dsr_chg_int_raw interrupt.*/
            uint32_t cts_chg:          1;           /*Set this bit to clear the cts_chg_int_raw interrupt.*/
            uint32_t brk_det:          1;           /*Set this bit to clear the brk_det_int_raw interrupt.*/
            uint32_t rxfifo_tout:      1;           /*Set this bit to clear the rxfifo_tout_int_raw interrupt.*/
            uint32_t reserved9:       23;
        };
        volatile uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t div_int:    20;                /*The register value is  the  integer part of the frequency divider's factor.*/
            uint32_t reserved20: 12;
        };
        volatile uint32_t val;
    } clk_div;
    union {
        struct {
            uint32_t en: 1;                         /*This is the enable bit for detecting baudrate.*/
            uint32_t reserved1:   7;
            uint32_t glitch_filt: 8;                /*when input pulse width is lower then this value ignore this pulse.this register is used in auto-baud detect process.*/
            uint32_t reserved16: 16;
        };
        volatile uint32_t val;
    } auto_baud;
    union {
        struct {
            uint32_t rxfifo_cnt: 8;                 /*(rx_mem_cnt rxfifo_cnt) stores the byte number of valid data in receiver's fifo. rx_mem_cnt register stores the 3 most significant bits  rxfifo_cnt stores the 8 least significant bits.*/
            uint32_t reserved8:  5;
            uint32_t dsrn:       1;                 /*This register stores the level value of the internal uart dsr signal.*/
            uint32_t ctsn:       1;                 /*This register stores the level value of the internal uart cts signal.*/
            uint32_t rxd:        1;                 /*This register stores the level value of the internal uart rxd signal.*/
            uint32_t txfifo_cnt: 8;                 /*(tx_mem_cnt txfifo_cnt) stores the byte number of valid data in transmitter's fifo.tx_mem_cnt stores the 3 most significant bits  txfifo_cnt stores the 8 least significant bits.*/
            uint32_t reserved24: 5;
            uint32_t dtrn:       1;                 /*The register represent the level value of the internal uart dsr signal.*/
            uint32_t rtsn:       1;                 /*This register represent the level value of the internal uart cts signal.*/
            uint32_t txd:        1;                 /*This register represent the  level value of the internal uart rxd signal.*/
        };
        volatile const uint32_t val;
    } status;
    union {
        struct {
            uint32_t parity:             1;         /*This register is used to configure the parity check mode.  0:even 1:odd*/
            uint32_t parity_en:          1;         /*Set this bit to enable uart parity check.*/
            uint32_t bit_num:            2;         /*This register is used to set the length of data:  0:5bits 1:6bits 2:7bits 3:8bits*/
            uint32_t stop_bit_num:       2;         /*This register is used to set the length of  stop bit. 1:1bit  2:1.5bits  3:2bits*/
            uint32_t sw_rts:             1;         /*This register is used to configure the software rts signal which is used in software flow control.*/
            uint32_t sw_dtr:             1;         /*This register is used to configure the software dtr signal which is used in software flow control..*/
            uint32_t txd_brk:            1;         /*Set this bit to enable transmitter to  send 0 when the process of sending data is done.*/
            uint32_t irda_dplx:          1;         /*Set this bit to enable irda loop-back mode.*/
            uint32_t irda_tx_en:         1;         /*This is the start enable bit for irda transmitter.*/
            uint32_t irda_wctl:          1;         /*1：the irda transmitter's 11th bit is the same to the 10th bit. 0：set irda transmitter's 11th bit to 0.*/
            uint32_t irda_tx_inv:        1;         /*Set this bit to inverse the level value of  irda transmitter's level.*/
            uint32_t irda_rx_inv:        1;         /*Set this bit to inverse the level value of irda receiver's level.*/
            uint32_t loopback:           1;         /*Set this bit to enable uart loop-back test mode.*/
            uint32_t tx_flow_en:         1;         /*Set this bit to enable transmitter's flow control function.*/
            uint32_t irda_en:            1;         /*Set this bit to enable irda protocol.*/
            uint32_t rxfifo_rst:         1;         /*Set this bit to reset uart receiver's fifo.*/
            uint32_t txfifo_rst:         1;         /*Set this bit to reset uart transmitter's fifo.*/
            uint32_t rxd_inv:            1;         /*Set this bit to inverse the level value of uart rxd signal.*/
            uint32_t cts_inv:            1;         /*Set this bit to inverse the level value of uart cts signal.*/
            uint32_t dsr_inv:            1;         /*Set this bit to inverse the level value of uart dsr signal.*/
            uint32_t txd_inv:            1;         /*Set this bit to inverse the level value of uart txd signal.*/
            uint32_t rts_inv:            1;         /*Set this bit to inverse the level value of uart rts signal.*/
            uint32_t dtr_inv:            1;         /*Set this bit to inverse the level value of uart dtr signal.*/
            uint32_t reserved25:         7;
        };
        volatile uint32_t val;
    } conf0;
    union {
        struct {
            uint32_t rxfifo_full_thrhd:  7;         /*When receiver receives more data than its threshold value，receiver will produce rxfifo_full_int_raw interrupt.the threshold value is (rx_flow_thrhd_h3 rxfifo_full_thrhd).*/
            uint32_t reserved7:           1;
            uint32_t txfifo_empty_thrhd: 7;         /*when the data amount in transmitter fifo is less than its threshold value， it will produce txfifo_empty_int_raw interrupt. the threshold value is (tx_mem_empty_thresh txfifo_empty_thrhd)*/
            uint32_t reserved15:          1;
            uint32_t rx_flow_thrhd:      7;         /*when receiver receives more data than its threshold value， receiver produce signal to tell the transmitter stop transferring data. the threshold value is (rx_flow_thrhd_h3 rx_flow_thrhd).*/
            uint32_t rx_flow_en:          1;         /*This is the flow enable bit for uart receiver. 1:choose software flow control with configuring sw_rts signal*/
            uint32_t rx_tout_thrhd:      7;         /*This register is used to configure the timeout value for uart receiver receiving a byte.*/
            uint32_t rx_tout_en:          1;         /*This is the enable bit for uart receiver's timeout function.*/
        };
        volatile uint32_t val;
    } conf1;
    union {
        struct {
            uint32_t min_cnt:     20;               /*This register stores the value of the minimum duration time for the low level pulse， it is used in baudrate-detect process.*/
            uint32_t reserved20:  12;
        };
        volatile const uint32_t val;
    } lowpulse;
    union {
        struct {
            uint32_t min_cnt:     20;               /*This register stores  the value of the maximum duration time for the high level pulse， it is used in baudrate-detect process.*/
            uint32_t reserved20:  12;
        };
        volatile const uint32_t val;
    } highpulse;
    union {
        struct {
            uint32_t edge_cnt:    10;               /*This register stores the count of rxd edge change， it is used in baudrate-detect process.*/
            uint32_t reserved10:  22;
        };
        volatile const uint32_t val;
    } rxd_cnt;
    uint32_t  reserved[18];
    volatile uint32_t date;                           /**/
    volatile uint32_t id;                             /**/
} uart_t;

/* Wait for at least `min_count` bytes of data to be available in the UART's
 * receive FIFO
 *
 * Returns the number of bytes actually available for reading.
 */
static inline int uart_rxfifo_wait(int uart_num, int min_count) {
    int count;
    do {
        count = FIELD2VAL(UART_STATUS_RXFIFO_COUNT, UART(uart_num).status);
    } while (count < min_count);
    return count;
}

/* Wait for at least `min_count` bytes of space to be available in the UART's
 * transmit FIFO
 *
 * Returns the number of bytes actually available in the write buffer.
 */
static inline int uart_txfifo_wait(int uart_num, int min_count) {
    int count;
    do {
        count = UART_FIFO_MAX - FIELD2VAL(UART_STATUS_TXFIFO_COUNT, UART(uart_num).STATUS);
    } while (count < min_count);
    return count;
}

/* Read a character from the UART.  Block until a character is available for
 * reading.
 *
 * Returns the character read.
 */
static inline int uart_getc(int uart_num) {
    uart_rxfifo_wait(uart_num, 1);
    return UART(uart_num).FIFO;
}

/* Read a character from the UART.  Does not block.
 *
 * Returns the read character on success.  If the RX FIFO is currently empty
 * (nothing to read), returns -1.
 */
static inline int uart_getc_nowait(int uart_num) {
    if (FIELD2VAL(UART_STATUS_RXFIFO_COUNT, UART(uart_num).STATUS)) {
        return UART(uart_num).FIFO;
    }
    return -1;
}

/* Write a character to the UART.  Blocks if necessary until there is space in
 * the TX FIFO.
 */
static inline void uart_putc(int uart_num, char c) {
    uart_txfifo_wait(uart_num, 1);
    UART(uart_num).FIFO = c;
}

/* Write a character to the UART.  Does not block.
 *
 * Returns 0 on success.  If there is no space currently in the TX FIFO,
 * returns -1.
 */
static inline int uart_putc_nowait(int uart_num, char c) {
    if (FIELD2VAL(UART_STATUS_TXFIFO_COUNT, UART(uart_num).STATUS) < UART_FIFO_MAX) {
        UART(uart_num).FIFO = c;
        return 0;
    }
    return -1;
}

/* Clear (discard) all pending write data in the TX FIFO */
static inline void uart_clear_txfifo(int uart_num) {
    uint32_t conf = UART(uart_num).CONF0;
    UART(uart_num).CONF0 = conf | UART_CONF0_TXFIFO_RESET;
    UART(uart_num).CONF0 = conf & ~UART_CONF0_TXFIFO_RESET;
}

/* Clear (discard) all pending read data in the RX FIFO */
static inline void uart_clear_rxfifo(int uart_num) {
    uint32_t conf = UART(uart_num).CONF0;
    UART(uart_num).CONF0 = conf | UART_CONF0_RXFIFO_RESET;
    UART(uart_num).CONF0 = conf & ~UART_CONF0_RXFIFO_RESET;
}

/* Wait until all pending output in the UART's TX FIFO has been sent out the
 * serial port. */
static inline void uart_flush_txfifo(int uart_num) {
    while (FIELD2VAL(UART_STATUS_TXFIFO_COUNT, UART(uart_num).STATUS) != 0) {}
}

/* Flush all pending input in the UART's RX FIFO
 * (this is just another name for uart_clear_rxfifo)
 */
static inline void uart_flush_rxfifo(int uart_num) {
    uart_clear_rxfifo(uart_num);
}

/* Set uart baud rate to the desired value */
static inline void uart_set_baud(int uart_num, int bps)
{
    uint32_t divider = APB_CLK_FREQ / bps;
    UART(uart_num).CLOCK_DIVIDER = divider;
}

/* Returns the current baud rate for the UART */
static inline int uart_get_baud(int uart_num)
{
    return APB_CLK_FREQ / FIELD2VAL(UART_CLOCK_DIVIDER_VALUE, UART(uart_num).CLOCK_DIVIDER);
}

/* Set uart stop bit count to the desired value */
static inline void uart_set_stopbits(int uart_num, UART_StopBits stop_bits) {
    UART(uart_num).CONF0 = SET_FIELD(UART(uart_num).CONF0, UART_CONF0_STOP_BITS, stop_bits);
}

/* Returns the current stopbit count for the UART */
static inline UART_StopBits uart_get_stopbits(int uart_num) {
    return (UART_StopBits)(FIELD2VAL(UART_CONF0_STOP_BITS, UART(uart_num).CONF0));
}

/* Set if uart parity bit should be enabled */
static inline void uart_set_parity_enabled(int uart_num, bool enable) {
    if(enable)
        UART(uart_num).CONF0 = SET_MASK_BITS(UART(uart_num).CONF0, UART_CONF0_PARITY_ENABLE);
    else
        UART(uart_num).CONF0 = CLEAR_MASK_BITS(UART(uart_num).CONF0, UART_CONF0_PARITY_ENABLE);
}

/* Set uart parity bit type */
static inline void uart_set_parity(int uart_num, UART_Parity parity) {
    if(parity == UART_PARITY_EVEN)
        UART(uart_num).CONF0 = CLEAR_MASK_BITS(UART(uart_num).CONF0, UART_CONF0_PARITY);
    else
        UART(uart_num).CONF0 = SET_MASK_BITS(UART(uart_num).CONF0, UART_CONF0_PARITY);
}

/* Returns if parity bit is currently enabled for UART uart_num */
static inline bool uart_get_parity_enabled(int uart_num) {
    return ((UART(uart_num).CONF0 & UART_CONF0_PARITY_ENABLE) != 0);
}

/* Returns the current parity bit type for UART uart_num (also if parity bit is not enabled) */
static inline UART_Parity uart_get_parity(int uart_num) {
    return (UART_Parity)((UART(uart_num).CONF0 & UART_CONF0_PARITY) != 0);
}

/* Set uart data bits length to the desired value */
static inline void uart_set_byte_length(int uart_num, UART_ByteLength byte_length) {
    UART(uart_num).CONF0 = SET_FIELD(UART(uart_num).CONF0, UART_CONF0_BYTE_LEN, byte_length);
}

/* Returns the current data bits length for the UART */
static inline UART_ByteLength uart_get_byte_length(int uart_num) {
    return (UART_ByteLength)(FIELD2VAL(UART_CONF0_BYTE_LEN, UART(uart_num).CONF0));
}

#endif /* _ESP_UART_H */

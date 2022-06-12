/**
 * @file esp8266_interrupt.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ESP8266_INTERRUPT_H
#define __ESP8266_INTERRUPT_H

/* Interrupt numbers for level 1 exception handler. */
typedef enum {
    INT_NUM_WDEV_FIQ        = 0,
    INT_NUM_SLC             = 1,
    INT_NUM_SPI             = 2,
    INT_NUM_RTC             = 3,
    INT_NUM_GPIO            = 4,
    INT_NUM_UART            = 5,
    INT_NUM_TICK            = 6, /* RTOS timer tick, possibly xtensa CPU CCOMPARE0(?) */
    INT_NUM_SOFT            = 7,
    INT_NUM_WDT             = 8,
    INT_NUM_TIMER_FRC1      = 9,
    /* FRC2 default handler. Configured by sdk_ets_timer_init, which
       runs as part of default libmain.a startup code, assigns
       interrupt handler to sdk_vApplicationTickHook+0x68
     */
    INT_NUM_TIMER_FRC2      = 10,
} int_num_t;

#endif /* __ESP8266_INTERRUPT_H */
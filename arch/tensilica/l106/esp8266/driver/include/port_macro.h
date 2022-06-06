#ifndef __PORT_H
#define __PORT_H

#include "stdlib.h"
#include "c_types.h"
#include "ets_sys.h"
#include "osapi.h"
#include "bits_string.h"
#include <mem.h>
#include "esp8266_serial_debug.h"

#define ETS_SLC_INUM        1

#define FUNC_ON_FLASH       ICACHE_FLASH_ATTR
#define VAR_ON_FLASH        ICACHE_RODATA_ATTR
#define ON_RAM              

#define printf              os_printf
#define malloc              os_zalloc
#define realloc             os_realloc
#define free                os_free

#define sprintf             os_sprintf
#define strcpy              os_strcpy
#define memcpy              os_memcpy

#define disable_interrupts()    ETS_INTR_LOCK()
#define enable_interrupts()     ETS_INTR_UNLOCK()

#define rand()  os_random()

#define PERIPHS_IO_MUX_MTCK_U           (PERIPHS_IO_MUX + 0x08)
#define FUNC_MTCK                           0
#define FUNC_I2SI_BCK                       1
#define FUNC_HSPID_MOSI                     2
#define FUNC_GPIO13                         3
#define FUNC_UART0_CTS                      4

#define PERIPHS_IO_MUX_MTMS_U           (PERIPHS_IO_MUX + 0x0C)
#define FUNC_MTMS                           0
#define FUNC_I2SI_WS                        1
#define FUNC_HSPI_CLK                       2
#define FUNC_GPIO14                         3
#define FUNC_UART0_DSR                      4

#define PERIPHS_IO_MUX_MTDI_U           (PERIPHS_IO_MUX + 0x04)
#define FUNC_MTDI                           0
#define FUNC_I2SI_DATA                      1
#define FUNC_HSPIQ_MISO                     2
#define FUNC_GPIO12                         3
#define FUNC_UART0_DTR                      4

#define ETS_SLC_INTR_ATTACH(func, arg) \
    ets_isr_attach(ETS_SLC_INUM, (ets_isr_t)(func), (void *)(arg))

#define ETS_SLC_INTR_ENABLE() \
    ETS_INTR_ENABLE(ETS_SLC_INUM)

#define ETS_SLC_INTR_DISABLE() \
    ETS_INTR_DISABLE(ETS_SLC_INUM)

#define tolower char_to_lower

#endif
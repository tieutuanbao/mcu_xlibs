#ifndef __PORT_H
#define __PORT_H

#include "osapi.h"
#include "ets_sys.h"
#include "bits_string.h"
#include "mem.h"

/* Define debug logger */
#define ANSI_COLOR_LOG      "[LOG: ]"
#define ANSI_COLOR_ERROR    "\x1b[31m[ERROR: ]"
#define ANSI_COLOR_DEBUG    "\x1b[33m[DEBUG: ]"

#define BITS_LOG( ... )     printf(ANSI_COLOR_LOG __VA_ARGS__);
#define BITS_LOGD( ... )    printf(ANSI_COLOR_DEBUG __VA_ARGS__); \
                            printf("\033[0m");
#define BITS_LOGE( ... )    printf(ANSI_COLOR_ERROR __VA_ARGS__); \
                            printf("\033[0m");

#define FUNC_ON_FLASH       ICACHE_FLASH_ATTR
#define FUNC_ON_RAM         
#define VAR_ON_FLASH        ICACHE_RODATA_ATTR
#define VAR_ON_IRAM         

#define printf              os_printf
#define malloc              os_zalloc
#define realloc             os_realloc
#define free                os_free

#define sprintf             os_sprintf
#define strcpy              os_strcpy
#define memcpy              os_memcpy

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
    ets_isr_attach(INT_NUM_SLC, (ets_isr_t)(func), (void *)(arg))

#define ETS_SLC_INTR_ENABLE() \
    ETS_INTR_ENABLE(INT_NUM_SLC)

#define ETS_SLC_INTR_DISABLE() \
    ETS_INTR_DISABLE(INT_NUM_SLC)

#define tolower char_to_lower

#endif
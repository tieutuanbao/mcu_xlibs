#ifndef __PORT_H
#define __PORT_H

#include "osapi.h"
#include "ets_sys.h"
#include "bits_string.h"
#include "mem.h"

/* Define debug logger */
#define ANSI_COLOR_LOG      "I "
#define ANSI_COLOR_WARN     "W "
#define ANSI_COLOR_ERROR    "\x1b[31mE "
#define ANSI_COLOR_DEBUG    "\x1b[33mD "

#define BITS_LOG( ... )     printf(ANSI_COLOR_LOG __VA_ARGS__);
#define BITS_LOGW( ... )    printf(ANSI_COLOR_LOG __VA_ARGS__);
#define BITS_LOGD( ... )    printf(ANSI_COLOR_DEBUG __VA_ARGS__); \
                            printf("\033[0m");
#define BITS_LOGE( ... )    printf(ANSI_COLOR_ERROR __VA_ARGS__); \
                            printf("\033[0m");

#define printf              os_printf
#define malloc              os_zalloc
#define realloc             os_realloc
#define free                os_free

#define sprintf             os_sprintf
#define strcpy              os_strcpy
#define memcpy              os_memcpy

#define rand()  os_random()

#define ETS_SLC_INTR_ATTACH(func, arg) \
    ets_isr_attach(INT_NUM_SLC, (ets_isr_t)(func), (void *)(arg))

#define ETS_SLC_INTR_ENABLE() \
    ETS_INTR_ENABLE(INT_NUM_SLC)

#define ETS_SLC_INTR_DISABLE() \
    ETS_INTR_DISABLE(INT_NUM_SLC)


#define tolower Bits_Char_ToLower
#define rand()  os_random()

#define IRAM_FUNC           __attribute__((section(".text")))

#endif
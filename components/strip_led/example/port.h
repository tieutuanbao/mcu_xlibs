#ifndef __PORT_H
#define __PORT_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BITS_LOGD(...)    printf(ANSI_COLOR_YELLOW        __VA_ARGS__ ); \
                            printf("\033[0m");
#define BITS_LOGE(...)    printf(ANSI_COLOR_RED           __VA_ARGS__ ); \
                            printf("\033[0m");


#ifndef bool
    #define bool    uint8_t
    #define true    1
    #define false   0
#endif

#define ICACHE_FLASH_ATTR

#endif
#ifndef __ESP8266_SERIAL_DEBUG_H
#define __ESP8266_SERIAL_DEBUG_H



#define ANSI_COLOR_LOG      "[LOG: ]"
#define ANSI_COLOR_ERROR    "\x1b[31m[ERROR: ]"
#define ANSI_COLOR_DEBUG    "\x1b[33m[DEBUG: ]"

#define BITS_LOG( ... )     printf(ANSI_COLOR_LOG __VA_ARGS__);
#define BITS_LOGD( ... )    printf(ANSI_COLOR_DEBUG __VA_ARGS__); \
                            printf("\033[0m");
#define BITS_LOGE( ... )    printf(ANSI_COLOR_ERROR __VA_ARGS__); \
                            printf("\033[0m");


#endif
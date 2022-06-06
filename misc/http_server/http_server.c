/**
 * @file http_server.c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "mbedtls/sys/socket.h"

#include "http_server.h"
#include "port_macro.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <mem.h>

http_server_t *http_server(){
    http_server_t *dev = malloc(sizeof(http_server_t));

    return dev;
}

/**
 * @file esp8266_sdk_function.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief Danh sách những hàm đóng gói của SDK
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __ESP8266_SDK_FUNCTION_H
#define __ESP8266_SDK_FUNCTION_H

#include <stdint.h>

void rom_i2c_writeReg_Mask(int, int, int, int, int, int);
uint32_t ets_get_cpu_frequency();

#endif
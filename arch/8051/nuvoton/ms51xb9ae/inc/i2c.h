/**
  ******************************************************************************
  * @file           : i2c.h
  * @brief          : Thư viện driver i2c lập trình nuvoton ms51.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

#ifndef __I2C_H
#define __I2C_H

#include <stdint.h>
#include "reg_ms51.h"

void i2c_init(void);
uint8_t i2c_mem_read(uint16_t dev_addr, uint8_t mem_addr, uint8_t* data, uint16_t size, uint32_t timeout);
uint8_t i2c_mem_write(uint16_t dev_addr, uint8_t mem_addr, uint8_t* data, uint16_t size, uint32_t timeout);

#endif

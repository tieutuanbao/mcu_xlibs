/**
  ******************************************************************************
  * @file           : SHTC3.c
  * @brief          : Thư viện lập trình SHTC3.
  * @author         : Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "SHTC3.h"


SHTC3_t new_SHTC3(uint8_t (*driverRecvI2C)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength), uint8_t (*driverSendI2C)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength)) {
    SHTC3_t SHTC3;
    SHTC3.read = driverRecvI2C;
    SHTC3.write = driverSendI2C;
}
void SHTC3_init(SHTC3_t *SHTC3, uint8_t (*driverRecvI2C)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength), uint8_t (*driverSendI2C)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength)) {
    SHTC3->read = driverRecvI2C;
    SHTC3->write = driverSendI2C;
}


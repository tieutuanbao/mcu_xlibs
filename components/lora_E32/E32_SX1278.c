/**
  ******************************************************************************
  * @file           : E32_SX1278.c
  * @brief          : Thư viện giao tiếp Lora E32.
  * @author			: Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "E32_SX1278.h"

void E32_SX1276_init(E32_SX1278_t *dev,
                    void (*transmitDriver)(uint8_t *,uint32_t ),
                    void (*setM0_driver)(bool level),
                    void (*setM1_driver)(bool level)
                    ){
    dev->transmit_driver = transmitDriver;
    dev->setM0_driver = setM0_driver;
    dev->setM1_driver = setM1_driver;
}

void E32_SX1276_enterMode(E32_SX1278_t *dev, E32_Operating_Mode_t opMode) {
	dev->setM0_driver(opMode & 0x01);
	dev->setM1_driver(opMode & 0x02 ? 1 : 0);
}

void E32_SX1276_paramConfig(E32_SX1278_t *dev) {
    uint8_t __E32_SX1276_Buffer[8];
    memcpy(__E32_SX1276_Buffer, dev->param, 6);
    dev->transmit_driver(__E32_SX1276_Buffer, 6);
}

void E32_SX1276_transmit(E32_SX1278_t *dev, uint8_t *data, uint32_t dataLength) {
    dev->transmit_driver(data, dataLength);
}

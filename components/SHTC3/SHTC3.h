/**
  ******************************************************************************
  * @file           : SHTC3.h
  * @brief          : Thư viện lập trình SHTC3.
  * @author         : Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __SHTC3_H__
#define __SHTC3_H__

#include <stdint.h>
#include <stdbool.h>

/* Địa chỉ I2C giao tiếp DS1307 */
#define SHTC3_I2C_ADDR          0xE0


#define SHTC3_MAX_CLOCK_FREQ 1000000
/* Danh sách thanh ghi DS1307 */
#define DS1307_REG_SECONDS      0x00
#define DS1307_REG_MINUTE       0x01
#define DS1307_REG_HOUR         0x02
#define DS1307_REG_DAY          0x03
#define DS1307_REG_DATE         0x04
#define DS1307_REG_MONTH        0x05
#define DS1307_REG_YEAR         0x06
#define DS1307_REG_CONTROL      0x07
#define DS1307_REG_RAM          0x08

enum SHTC3_Commands {
    wake            = 0x3517,
    sleep           = 0xB098,
    softwareReset   = 0x805D,
    readId          = 0xEFC8
};

enum SHTC3_MeasurementModes {
    clkStrNomalModeReadRHFirst      = 0x5C24,   // Clock stretching, RH first, Normal power mode
    clkStrLowPowerModeReadRHFirst   = 0x44DE,   // Clock stretching, RH first, Low power mode
    clkStrNomalModeReadTFirst       = 0x7CA2,   // Clock stretching, T first, Normal power mode
    clkStrLowPowerModeReadTFirst    = 0x6458,   // Clock stretching, T first, Low power mode

    pollNomalModeReadRHFirst        = 0x58E0,   // Polling, RH first, Normal power mode
    pollLowPowerModeReadRHFirst     = 0x401A,   // Polling, RH first, Low power mode
    pollNomalModeReadTFirst         = 0x7866,   // Polling, T first, Normal power mode
    pollLowPowerModeReadTFirst      = 0x609C    // Polling, T first, Low power mode
};

enum SHTC3_Status{
	nominal = 0,    // The one and only "all is good" return value
	error,          // The most general of error values - can mean anything depending on the context
	CRCFail,        // This return value means the computed checksum did not match the provided value
	IDFail          // This status means that the ID of the device did not match the format for SHTC3
};

typedef struct {
    uint8_t (*read)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength);
    uint8_t (*write)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength);
    bool busy
} SHTC3_t;

SHTC3_t new_SHTC3(uint8_t (*driverRecvI2C)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength), uint8_t (*driverSendI2C)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength));
void SHTC3_init(SHTC3_t *SHTC3, uint8_t (*driverRecvI2C)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength), uint8_t (*driverSendI2C)(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t dataLength));
enum SHTC3_Status SHTC3_startProcess(void);

#endif

/**
  ******************************************************************************
  * @file           : ds3231.h
  * @brief          : Thư viện lập trình ds3231.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __DS3231_H
#define __DS3231_H

#include <stdint.h>

/* Địa chỉ I2C giao tiếp DS3231 */
#define DS3231_I2C_ADDR             0xD0

/* Danh sách thanh ghi DS3231 */
#define DS3231_REG_SECONDS                0x00
#define DS3231_REG_MINUTE                        0x01
#define DS3231_REG_HOUR                            0x02
#define DS3231_REG_DAY                            0x03
#define DS3231_REG_DATE                            0x04
#define DS3231_REG_MONTH                        0x05
#define DS3231_REG_YEAR                            0x06
#define DS3231_REG_ALARM1_SEC                0x07
#define DS3231_REG_ALARM1_MIN                0x08
#define DS3231_REG_ALARM1_HOUR            0x09
#define DS3231_REG_ALARM1_DATE            0x0A
#define DS3231_REG_ALARM2_MIN                0x0B
#define DS3231_REG_ALARM1_HOUR            0x0C
#define DS3231_REG_ALARM1_DATE            0x0D
#define DS3231_REG_CONTROL                    0x0E
#define DS3231_REG_STATUS                        0x0F
#define DS3231_REG_AGE_OFFSET                0x10
#define DS3231_REG_TEMP_MSB                    0x11
#define DS3231_REG_TEMP_LSB                    0x12

#define DS3231_HOUR_AM        0
#define DS3231_HOUR_PM        1

typedef enum {
    ds3231_hour_am,
    ds3231_hour_pm
} ds3231_hour_aop_t;

typedef enum {
    ds3231_time_format_24h,
    ds3231_time_format_12h
} ds3231_time_format_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t seconds;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
    ds3231_hour_aop_t am_or_pm;
    ds3231_time_format_t time_format;
}    ds3231_time_t;

typedef struct {
    uint8_t (*read)(uint8_t addr, uint8_t reg, uint8_t *val);
    uint8_t (*write)(uint8_t addr, uint8_t reg, uint8_t val);

    ds3231_time_t time;
    float temp;
} ds3231_t;

uint8_t ds3231_init(ds3231_t *dev, uint8_t (*read)(uint8_t addr, uint8_t reg, uint8_t *val), uint8_t (*write)(uint8_t addr, uint8_t reg, uint8_t val));

uint8_t ds3231_get_time(ds3231_t *dev);
uint8_t ds3231_get_date(ds3231_t *dev);
uint8_t ds3231_set_time(ds3231_t *dev, uint8_t hour, uint8_t minute, uint8_t seconds, ds3231_hour_aop_t am_or_pm, ds3231_time_format_t time_format);
uint8_t ds3231_set_date(ds3231_t *dev, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
uint8_t ds3231_get_temp(ds3231_t *dev);

#endif

/**
  ******************************************************************************
  * @file           : ds1307.h
  * @brief          : Thư viện lập trình ds1307.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __DS1307_H
#define __DS1307_H

#include <stdint.h>

/* Địa chỉ I2C giao tiếp DS1307 */
#define DS1307_I2C_ADDR         0xD0

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

typedef enum {
    ds1307_hour_am  = 0,
    ds1307_hour_pm  = 1
} ds1307_hour_aop_t;

typedef enum {
    ds1307_time_format_24h  = 0,
    ds1307_time_format_12h  = 1
} ds1307_time_format_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t seconds;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
    ds1307_hour_aop_t am_or_pm;
    ds1307_time_format_t format;
}    ds1307_time_t;

typedef struct {
    uint8_t (*read)(uint8_t addr, uint8_t reg, uint8_t *val);
    uint8_t (*write)(uint8_t addr, uint8_t reg, uint8_t val);

    ds1307_time_t time;
} ds1307_t;

uint8_t ds1307_init(ds1307_t *dev, uint8_t (*read)(uint8_t addr, uint8_t reg, uint8_t *val), uint8_t (*write)(uint8_t addr, uint8_t reg, uint8_t val));

uint8_t ds1307_get_clock(ds1307_t *dev);
uint8_t ds1307_get_calendar(ds1307_t *dev);
uint8_t ds1307_set_clock(ds1307_t *dev, uint8_t hour, uint8_t minute, uint8_t seconds, ds1307_hour_aop_t am_or_pm, ds1307_time_format_t format);
uint8_t ds1307_set_calendar(ds1307_t *dev, uint8_t day, uint8_t date, uint8_t month, uint8_t year);

#endif

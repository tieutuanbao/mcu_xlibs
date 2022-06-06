/**
  ******************************************************************************
  * @file           : ds1307.c
  * @brief          : Thư viện lập trình ds1307.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "ds1307.h"

/* ---------------------- Support Function ------------------------ */
static uint8_t ds1307_decode(uint8_t bcd) {
    return ((bcd & 0x0F) + (((bcd & 0xF0) >> 4) * 10));
}


static uint8_t ds1307_encode(uint8_t dec) {
    return (((dec / 10) << 4) & 0xF0) | ((dec % 10) & 0x0F);
}


uint8_t ds1307_init(ds1307_t *dev, uint8_t (*read)(uint8_t addr, uint8_t reg, uint8_t *val), uint8_t (*write)(uint8_t addr, uint8_t reg, uint8_t val)) {
    dev->read = read;
    dev->write = write;
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_CONTROL, 0x00)) return 1;
    return 0;
}

uint8_t ds1307_get_clock(ds1307_t *dev) {
    uint8_t temp_val = 0;
    /* Lấy dữ liệu giây */
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_SECONDS, &temp_val)) return 1;
    dev->time.seconds = ds1307_decode(temp_val);
    /* Lấy dữ liệu phút */
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_MINUTE, &temp_val)) return 1;
    dev->time.minute = ds1307_decode(temp_val);
    /* Lấy dữ liệu giờ */
    switch(dev->time.format) {
        case ds1307_time_format_12h:
            if(dev->read(DS1307_I2C_ADDR, DS1307_REG_HOUR, &temp_val)) return 1;
            dev->time.am_or_pm = (ds1307_hour_aop_t)(temp_val >> 5);
            dev->time.hour = ds1307_decode(0x1F & temp_val);
            break;
        default:
            if(dev->read(DS1307_I2C_ADDR, DS1307_REG_HOUR, &temp_val)) return 1;
            dev->time.hour = ds1307_decode(0x3F & temp_val);
            break;
    }
    return 0;
}

uint8_t ds1307_get_calendar(ds1307_t *dev) {
    uint8_t temp_val = 0;
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_YEAR, &temp_val)) return 1;
    dev->time.year = ds1307_decode(temp_val);
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_MONTH, &temp_val)) return 1;
    temp_val = (0x1F & temp_val);
    dev->time.month = ds1307_decode(temp_val);
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_DATE, &temp_val)) return 1;
    temp_val = (0x3F & temp_val);
    dev->time.date = ds1307_decode(temp_val);
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_DAY, &temp_val)) return 1;
    temp_val = (0x07 & temp_val);
    dev->time.day = ds1307_decode(temp_val);
    return 0;
}

uint8_t ds1307_set_clock(ds1307_t *dev, uint8_t hour, uint8_t minute, uint8_t seconds, ds1307_hour_aop_t am_or_pm, ds1307_time_format_t format) {
    uint8_t temp_val = 0;
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_SECONDS, ds1307_encode(seconds))) return 1;
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_MINUTE, ds1307_encode(minute))) return 1;
    switch(format) {
        case ds1307_time_format_12h: {
            switch(am_or_pm) {
                case ds1307_hour_pm: {
                    temp_val = 0x60;
                    break;
                }
                default: {
                    temp_val = 0x40;
                    break;
                }
            }
            if(dev->write(DS1307_I2C_ADDR, DS1307_REG_HOUR, ((temp_val | (0x1F & (ds1307_encode(hour))))))) return 1;
            break;
        }
        default: {
            if(dev->write(DS1307_I2C_ADDR, DS1307_REG_HOUR, (0x3F & (ds1307_encode(hour))))) return 1;
            break;
        }
    }
    return 0;
}

uint8_t ds1307_set_calendar(ds1307_t *dev, uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_DAY, ds1307_encode(day))) return 1;
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_DATE, ds1307_encode(date))) return 1;
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_MONTH, ds1307_encode(month))) return 1;
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_YEAR, ds1307_encode(year))) return 1;
    return 0;
}

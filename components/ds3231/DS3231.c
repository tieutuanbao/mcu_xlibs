/**
  ******************************************************************************
  * @file           : ds3231.c
  * @brief          : Thư viện lập trình ds3231.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "ds3231.h"

/* ---------------------- Support Function ------------------------ */
static uint8_t ds3231_decode(uint8_t bcd) {
    return ((bcd & 0x0F) + (((bcd & 0xF0) >> 4) * 10));
}


static uint8_t ds3231_encode(uint8_t dec) {
    return (((dec / 10) << 4) & 0xF0) | ((dec % 10) & 0x0F);
}


uint8_t ds3231_init(ds3231_t *dev, uint8_t (*read)(uint8_t addr, uint8_t reg, uint8_t *val), uint8_t (*write)(uint8_t addr, uint8_t reg, uint8_t val)) {
    dev->read = read;
    dev->write = write;
    if(dev->write(DS3231_I2C_ADDR, DS3231_REG_CONTROL, 0x00)) return 1;
    if(dev->write(DS3231_I2C_ADDR, DS3231_REG_STATUS, 0x08)) return 1;
    return 0;
}

uint8_t ds3231_get_clock(ds3231_t *dev) {
    uint8_t temp_val = 0;
    /* Lấy dữ liệu giây */
    if(dev->read(DS3231_I2C_ADDR, DS3231_REG_SECONDS, &temp_val)) return 1;
    dev->seconds = ds3231_decode(temp_val);
    /* Lấy dữ liệu phút */
    if(dev->read(DS3231_I2C_ADDR, DS3231_REG_MINUTE, &temp_val)) return 1;
    dev->minute = ds3231_decode(temp_val);
    /* Lấy dữ liệu giờ */
    switch(dev->time_format) {
        case ds3231_time_format_12h:
            if(dev->read(DS3231_I2C_ADDR, DS3231_REG_HOUR, &temp_val)) return 1;
            dev->am_or_pm = temp_val >> 5;
            dev->hour = ds3231_decode(0x1F & temp_val);
            break;
        default:
            if(dev->read(DS3231_I2C_ADDR, DS3231_REG_HOUR, &temp_val)) return 1;
            dev->hour = ds3231_decode(0x3F & temp_val);
            break;
    }
    return 0;
}

uint8_t ds3231_get_calendar(ds3231_t *dev) {
    uint8_t temp_val = 0;
    if(dev->read(DS3231_I2C_ADDR, DS3231_REG_YEAR, &temp_val)) return 1;
    dev->year = ds3231_decode(temp_val);
    if(dev->read(DS3231_I2C_ADDR, DS3231_REG_MONTH, &temp_val)) return 1;
    temp_val = (0x1F & temp_val);
    dev->month = ds3231_decode(temp_val);
    if(dev->read(DS3231_I2C_ADDR, DS3231_REG_DATE, &temp_val)) return 1;
    temp_val = (0x3F & temp_val);
    dev->date = ds3231_decode(temp_val);
    if(dev->read(DS3231_I2C_ADDR, DS3231_REG_DAY, &temp_val)) return 1;
    temp_val = (0x07 & temp_val);
    dev->day = ds3231_decode(temp_val);
    return 0;
}

uint8_t ds3231_set_clock(ds3231_t *dev, uint8_t hour, uint8_t minute, uint8_t seconds, ds3231_hour_aop_t am_or_pm, ds3231_time_format_t time_format) {
    uint8_t temp_val = 0;
    if(dev->write(DS3231_I2C_ADDR, DS3231_REG_SECONDS, ds3231_encode(seconds))) return 1;
    if(dev->write(DS3231_I2C_ADDR, DS3231_REG_MINUTE, ds3231_encode(minute))) return 1;
    switch(ds3231_time_format_12h) {
        case 1: {
            switch(am_or_pm) {
                case ds3231_hour_pm: {
                    temp_val = 0x60;
                    break;
                }
                default: {
                    temp_val = 0x40;
                    break;
                }
            }
            if(dev->write(DS3231_I2C_ADDR, DS3231_REG_HOUR, ((temp_val | (0x1F & (ds3231_encode(hour))))))) return 1;
            break;
        }
        default: {
            if(dev->write(DS3231_I2C_ADDR, DS3231_REG_HOUR, (0x3F & (ds3231_encode(hSet))))) return 1;
            break;
        }
    }
    return 0;
}

uint8_t ds3231_set_calendar(ds3231_t *dev, uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
    if(dev->write(DS3231_I2C_ADDR, DS3231_REG_DAY, ds3231_encode(day))) return 1;
    if(dev->write(DS3231_I2C_ADDR, DS3231_REG_DATE, ds3231_encode(date))) return 1;
    if(dev->write(DS3231_I2C_ADDR, DS3231_REG_MONTH, ds3231_encode(month))) return 1;
    if(dev->write(DS3231_I2C_ADDR, DS3231_REG_YEAR, ds3231_encode(year))) return 1;
    return 0;
}

uint8_t ds3231_get_temp(ds3231_t *dev) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    if(dev->read(DS3231_I2C_ADDR, DS3231_REG_TEMP_LSB, &lsb)) return 1;
    if(dev->read(DS3231_I2C_ADDR, DS3231_REG_TEMP_MSB, &msb)) return 1;
    lsb >>= 6;
    lsb &= 0x03;
    dev->temp = ((float)lsb);
    dev->temp *= 0.25;
    dev->temp += ((float)msb);
    return 0;
}

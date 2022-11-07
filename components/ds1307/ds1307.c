/**
  ******************************************************************************
  * @file           : ds1307.c
  * @brief          : Thư viện lập trình ds1307.
  * @author         : Tiêu Tuấn Bảo
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


bool ds1307_init(ds1307_t *dev, uint8_t (*read)(uint8_t addr, uint8_t reg, uint8_t *Data, uint8_t DataLength), uint8_t (*write)(uint8_t addr, uint8_t reg, uint8_t *Data, uint8_t DataLength)) {
    dev->read = read;
    dev->write = write;
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_CONTROL, (uint8_t []){0x00}, 1)) return false;
    return true;
}

bool ds1307_get_clock(ds1307_t *dev) {
    uint8_t temp_val[3];
    /* Lấy dữ liệu */
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_SECONDS, temp_val, 3)) return false;
    /* Decode dữ liệu giây */
    dev->time.seconds = ds1307_decode(temp_val[0]);
    /* Decode dữ liệu phút */
    dev->time.minute = ds1307_decode(temp_val[1]);
    /* Decode dữ liệu giờ */
    if(temp_val[2] & 0x40) {
        dev->time.format = ds1307_time_format_12h;
        dev->time.am_or_pm = (ds1307_hour_aop_t)(temp_val[2] >> 5);
        dev->time.hour = ds1307_decode(0x1F & temp_val[2]);
    }
    else {
        dev->time.format = ds1307_time_format_24h;
        dev->time.hour = ds1307_decode(0x3F & temp_val[2]);
    }
    return true;
}

bool ds1307_get_calendar(ds1307_t *dev) {
    uint8_t temp_val[4];
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_DAY, temp_val, 4)) return false;
    temp_val[0] = (0x07 & temp_val[0]);
    dev->time.day = ds1307_decode(temp_val[0]);
    temp_val[1] = (0x3F & temp_val[1]);
    dev->time.date = ds1307_decode(temp_val[1]);
    temp_val[2] = (0x1F & temp_val[2]);
    dev->time.month = ds1307_decode(temp_val[2]);
    dev->time.year = ds1307_decode(temp_val[3]);
    return true;
}

bool ds1307_set_clock(ds1307_t *dev, uint8_t hour, uint8_t minute, uint8_t seconds, ds1307_hour_aop_t am_or_pm, ds1307_time_format_t format) {
    uint8_t temp_val[3];
    temp_val[0] = ds1307_encode(seconds);
    temp_val[1] = ds1307_encode(minute);
    switch(format) {
        case ds1307_time_format_12h: {
            switch(am_or_pm) {
                case ds1307_hour_pm: {
                    temp_val[2] = 0x60;
                    break;
                }
                default: {
                    temp_val[2] = 0x40;
                    break;
                }
            }
            temp_val[2] |= (0x1F & (ds1307_encode(hour)));
            break;
        }
        default: {
            temp_val[2] = (0x3F & (ds1307_encode(hour)));
            break;
        }
    }
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_SECONDS, temp_val, 3)) return false;
    return true;
}

bool ds1307_set_calendar(ds1307_t *dev, uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
    uint8_t temp_val[4];
    temp_val[0] = ds1307_encode(day);
    temp_val[1] = ds1307_encode(date);
    temp_val[2] = ds1307_encode(month);
    temp_val[3] = ds1307_encode(year);
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_DAY, temp_val, 4)) return false;
    return true;
}

bool ds1307_set_SQW(ds1307_t *dev, ds1307_sqw_t sqw_mode) {
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_CONTROL, (uint8_t []){0x10}, 1)) return false;
    return true;
}

bool ds1307_write_Ram(ds1307_t *dev, uint8_t *Offset, uint8_t *Data, uint8_t DataLength) {
    if(DataLength == 0) return false;
    if(dev->write(DS1307_I2C_ADDR, DS1307_REG_RAM, Data, DataLength)) return false;
    return true;
}

bool ds1307_read_Ram(ds1307_t *dev, uint8_t *Offset, uint8_t *Data, uint8_t DataLength) {
    if(DataLength == 0) return false;
    if(dev->read(DS1307_I2C_ADDR, DS1307_REG_RAM, Data, DataLength)) return false;
    return true;
}
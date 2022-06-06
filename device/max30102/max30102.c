/**
  ******************************************************************************
  * @file           : max30102.c
  * @brief          : Thư viện driver max30102.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    * Thư viện lập trình max30102
    *
  ******************************************************************************
  */

#include "max30102.h"

max30102_stt_t max30102_init(max30102_t *dev, max30102_stt_t (*i2c_read)(uint8_t reg_addr, uint8_t *data, uint8_t size), max30102_stt_t (*i2c_write)(uint8_t reg_addr, uint8_t *data, uint8_t size)) {
    dev->drv_read = i2c_read;
    dev->drv_write = i2c_write;

    dev->ir_led_cur_low = 0x01;
    dev->ir_led_cur_high = 0x0F;
    dev->red_led_cur_low = 0x00;
    dev->red_led_cur_high = 0x0F;
    dev->ir_val_on_sensor = 1600;
    dev->ir_val_out_sensor = 50000;

    uint8_t dummy = 0;
    if(max30102_reset(dev) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(dev->drv_read(0, &dummy, 1) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_FIFO_wr_ptr(dev, 0) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_ovf_counter(dev, 0) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_FIFO_rd_ptr(dev, 0) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_FIFO_sample_avr(dev, 2) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_FIFO_rollover_en(dev, 0) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_FIFO_almost_full(dev, 17) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_MODE(dev, 3) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_SPO2_ADC_range(dev, 3) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_SPO2_sample_rate(dev, 1) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_SPO2_LED_pulse_width(dev, 3) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_LED1_PA(dev, 0) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_LED2_PA(dev, 1) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_int_almost_full_en(dev, 1) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    if(max30102_set_int_FIFO_data_ready(dev, 1) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}

max30102_stt_t max30102_set_FIFO_wr_ptr(max30102_t *dev, uint8_t val) {
    if(dev->drv_write(MAX30102_REG_FIFO_WR_PTR, &val, 1) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_ovf_counter(max30102_t *dev, uint8_t val) {
    if(dev->drv_write(MAX30102_REG_OVF_COUNTER, &val, 1) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_FIFO_rd_ptr(max30102_t *dev, uint8_t val) {
    if(dev->drv_write(MAX30102_REG_FIFO_RD_PTR, &val, 1) != MAX30102_OK) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_read_FIFO_data(max30102_t *dev, uint8_t *buf) {
    return dev->drv_read(MAX30102_REG_FIFO_DATA, buf, 6);
}
max30102_stt_t max30102_set_FIFO_sample_avr(max30102_t *dev, uint8_t val) {
    uint8_t tmp = 0xFF;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_FIFO_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(0x07<<5);
    tmp |= (val&0x07)<<5;
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_FIFO_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_FIFO_rollover_en(max30102_t *dev, uint8_t val) {
    uint8_t tmp = 0;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_FIFO_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(1<<4);
    tmp |= (val&0x01)<<4;
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_FIFO_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_FIFO_almost_full(max30102_t *dev, uint8_t val) {
    uint8_t tmp = 0;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_FIFO_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(0x07);
    tmp |= (val & 0x07);
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_FIFO_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_reset(max30102_t *dev) {
    uint8_t tmp = 0xFF;
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_MODE_CONFIG, "\x40", 1))
            return MAX30102_ERROR;
    do
    {
        if(MAX30102_OK != dev->drv_read(MAX30102_REG_MODE_CONFIG, &tmp, 1))
            return MAX30102_ERROR;
    } while(tmp & (1<<6));
    return MAX30102_OK;
}
max30102_stt_t max30102_set_MODE(max30102_t *dev, uint8_t val) {
    uint8_t tmp = 0;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_MODE_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(0x07);
    tmp |= (val & 0x07);
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_MODE_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_SPO2_ADC_range(max30102_t *dev, uint8_t val) {
    uint8_t tmp = 0;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_SPO2_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(0x03 << 5);
    tmp |= (val & 0x03) << 5;
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_SPO2_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_SPO2_sample_rate(max30102_t *dev, uint8_t val) {
    uint8_t tmp = 0;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_SPO2_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(0x07 << 2);
    tmp |= (val & 0x07) << 2;
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_SPO2_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_SPO2_LED_pulse_width(max30102_t *dev, uint8_t val) {
    uint8_t tmp = 0;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_SPO2_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(0x03);
    tmp |= (val & 0x03);
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_SPO2_CONFIG, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_LED1_PA(max30102_t *dev, uint8_t val) {
    return dev->drv_write(MAX30102_REG_LED1_PA, &val, 1);
}
max30102_stt_t max30102_set_LED2_PA(max30102_t *dev, uint8_t val) {
    return dev->drv_write(MAX30102_REG_LED2_PA, &val, 1);
}
max30102_stt_t max30102_set_int_almost_full_en(max30102_t *dev, uint8_t en) {
    uint8_t tmp = 0;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_INTR_ENABLE_1, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(0x01 << 7);
    tmp |= (en & 0x01) << 7;
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_INTR_ENABLE_1, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}
max30102_stt_t max30102_set_int_FIFO_data_ready(max30102_t *dev, uint8_t en) {
    uint8_t tmp = 0;
    if(MAX30102_OK != dev->drv_read(MAX30102_REG_INTR_ENABLE_1, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    tmp &= ~(0x01 << 6);
    tmp |= (en & 0x01) << 6;
    if(MAX30102_OK != dev->drv_write(MAX30102_REG_INTR_ENABLE_1, &tmp, 1)) {
        return MAX30102_ERROR;
    }
    return MAX30102_OK;
}

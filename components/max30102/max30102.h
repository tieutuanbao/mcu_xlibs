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

#ifndef __MAX30102_H
#define __MAX30102_H

#include <stdint.h>
#include "algorithm.h"

/**
 * I2C addresses
 */
#define MAX30102_ADDRESS 0xAE

/**
 * Register addresses
 */
#define MAX30102_REG_INTR_STATUS_1        0x00
#define MAX30102_REG_INTR_STATUS_2        0x01
#define MAX30102_REG_INTR_ENABLE_1        0x02
#define MAX30102_REG_INTR_ENABLE_2        0x03
#define MAX30102_REG_FIFO_WR_PTR            0x04
#define MAX30102_REG_OVF_COUNTER            0x05
#define MAX30102_REG_FIFO_RD_PTR            0x06
#define MAX30102_REG_FIFO_DATA                0x07
#define MAX30102_REG_FIFO_CONFIG            0x08
#define MAX30102_REG_MODE_CONFIG            0x09
#define MAX30102_REG_SPO2_CONFIG            0x0A
#define MAX30102_REG_LED1_PA                    0x0C
#define MAX30102_REG_LED2_PA                    0x0D
#define MAX30102_REG_PILOT_PA                    0x10
#define MAX30102_REG_MULTI_LED_CTRL1     0x11
#define MAX30102_REG_MULTI_LED_CTRL2     0x12
#define MAX30102_REG_TEMP_INTR                0x1F
#define MAX30102_REG_TEMP_FRAC                0x20
#define MAX30102_REG_TEMP_CONFIG            0x21
#define MAX30102_REG_PROX_INT_THRESH    0x30
#define MAX30102_REG_REV_ID                        0xFE
#define MAX30102_REG_PART_ID                    0xFF

typedef enum {
    MAX30102_ERROR    = 0,
    MAX30102_OK            = 1
} max30102_stt_t;

typedef enum {
    PULSE_IDLE,
    PULSE_TRACE_UP,
    PULSE_TRACE_DOWN
} max30102_pulse_state_t;

typedef struct {
    uint8_t ir_led_cur_low;
    uint8_t red_led_cur_low;
    uint8_t ir_led_cur_high;
    uint8_t red_led_cur_high;
    uint16_t ir_val_on_sensor;
    uint16_t ir_val_out_sensor;

    dc_filter_t dc_filter_ir;
    dc_filter_t dc_filter_red;
    mean_diff_filter_t mean_diff_ir;
    butter_worth_filter_t btrworth_filter_ir;

    struct {
        max30102_pulse_state_t state;
        float prev_val;
    } detect_pulse;

    max30102_stt_t (*drv_write)(uint8_t reg_addr, uint8_t *data, uint8_t size);
    max30102_stt_t (*drv_read)(uint8_t reg_addr, uint8_t *data, uint8_t size);
} max30102_t;

max30102_stt_t max30102_init(max30102_t *dev,
                                                            max30102_stt_t (*i2c_read)(uint8_t reg_addr, uint8_t *data, uint8_t size),
                                                            max30102_stt_t (*i2c_write)(uint8_t reg_addr, uint8_t *data, uint8_t size));

max30102_stt_t max30102_set_FIFO_wr_ptr(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_ovf_counter(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_FIFO_rd_ptr(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_read_FIFO_data(max30102_t *dev, uint8_t *buf);
max30102_stt_t max30102_set_FIFO_sample_avr(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_FIFO_rollover_en(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_FIFO_almost_full(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_reset(max30102_t *dev);
max30102_stt_t max30102_set_MODE(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_SPO2_ADC_range(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_SPO2_sample_rate(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_SPO2_LED_pulse_width(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_LED1_PA(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_LED2_PA(max30102_t *dev, uint8_t val);
max30102_stt_t max30102_set_int_almost_full_en(max30102_t *dev, uint8_t en);
max30102_stt_t max30102_set_int_FIFO_data_ready(max30102_t *dev, uint8_t en);

#endif

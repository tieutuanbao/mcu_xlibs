/**
  ******************************************************************************
  * @file           : adc.h
  * @brief          : Thư viện driver adc lập trình nuvoton ms51.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */
#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>
#include "reg_ms51.h"

typedef enum {
    adc_trigger_start_pin_P04    =    0,
    adc_trigger_start_pin_P13
} adc_trigger_start_pin_t;

typedef enum {
    adc_trigger_falling    =    0,
    adc_trigger_rising,
    adc_trigger_central_pwm_period,
    adc_trigger_end_pwm_period
} adc_trigger_type_t;

typedef enum {
    adc_trigger_ex_conv_only_adcs_bit    =    0,
    adc_trigger_ex_conv_adcs_or_trig_source
} adc_trigger_ex_conversion_t;

typedef struct {
    adc_trigger_start_pin_t pin;
    adc_trigger_type_t type;
    adc_trigger_ex_conversion_t external_conversion;
} adc_trigger_t;


void adc_init(void);
void adc_select_channel(uint8_t channel);
uint16_t adc_read(void);

#endif

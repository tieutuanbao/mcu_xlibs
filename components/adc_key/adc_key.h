/**
 ******************************************************************************
 * @file           : adc_key.h
 * @brief          : Thư viện lập trình adc key
 *    @author                    :    Tiêu Tuấn Bảo
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef __ADC_KEY_H
#define __ADC_KEY_H

#include <stdint.h>

typedef struct
{
    uint16_t min_val;
    uint16_t max_val;
} adc_key_t;

void adc_key_init(adc_key_t *dev, uint16_t adc_max_val, uint32_t pull_up_res, uint32_t pull_down_res, uint8_t mean_error);
uint8_t adc_key_get(adc_key_t *dev, uint16_t adc_val_in);

#endif

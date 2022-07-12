/**
 ******************************************************************************
 * @file           : adc_key.c
 * @brief          : Thư viện lập trình adc key
 *    @author                    :    Tiêu Tuấn Bảo
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#include "adc_key.h"

void adc_key_init(adc_key_t *dev, uint16_t adc_max_val, uint32_t pull_up_res, uint32_t pull_down_res, uint8_t mean_error)
{
    /* Lấy giá trị chia chuẩn */
    dev->max_val = (adc_max_val * pull_down_res) / (pull_up_res + pull_down_res);
    /* Lấy giá trị tương đối nhỏ nhất theo sai số */
    if (dev->max_val >= mean_error)
        dev->min_val = dev->max_val - mean_error;
    /* Lấy giá trị tương đối lớn nhất theo sai số */
    dev->max_val = dev->max_val + mean_error;
}

uint8_t adc_key_get(adc_key_t *dev, uint16_t adc_val_in)
{
    if ((adc_val_in >= dev->min_val) && (adc_val_in <= dev->max_val))
        return 1;
    else
        return 0;
}

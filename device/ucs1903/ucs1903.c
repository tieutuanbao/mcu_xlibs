/**
  ******************************************************************************
  * @file           : ucs1903.c
  * @brief          : Thư viện điều khiển ucs1903.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "ucs1903.h"
#include <stdio.h>
#include <string.h>

#if UCS1903_IO_SUPPORT_CLR_SET == 1
void ucs1903_init(ucs1903_t *dev, volatile uint32_t *port_set_reg, volatile uint32_t *port_clr_reg, uint32_t pin_mask,
                                                                    uint16_t max_chip_serial,
                                                                  ucs1903_color_t *color_buf,
                                                                    uint32_t t1h_single_task_delay,
                                                                    uint32_t t1l_single_task_delay,
                                                                    uint32_t t0h_single_task_delay,
                                                                    uint32_t t0l_single_task_delay,
                                                                    uint32_t th_mt_task_delay,
                                                                    uint32_t thl_mt_task_delay,
                                                                    uint32_t tl_mt_task_delay) {
    dev->port_clr_reg = port_clr_reg;
    dev->port_set_reg = port_set_reg;
#else
void ucs1903_init(ucs1903_t *dev, uint32_t *port_reg, uint32_t pin_mask,
                                                                    uint16_t max_chip_serial,
                                                                  ucs1903_color_t *color_buf,
                                                                    uint32_t t1h_single_task_delay,
                                                                    uint32_t t1l_single_task_delay,
                                                                    uint32_t t0h_single_task_delay,
                                                                    uint32_t t0l_single_task_delay,
                                                                    uint32_t th_mt_task_delay,
                                                                    uint32_t tl_mt_task_delay) {
    dev->port_reg = port_reg;
#endif
    dev->color_buf = color_buf;
    dev->pin_mask = pin_mask;
    dev->max_chip_serial = max_chip_serial;
    dev->t0h_sg_task_delay = t0h_single_task_delay;
    dev->t0l_sg_task_delay = t0l_single_task_delay;
    dev->t1h_sg_task_delay = t1h_single_task_delay;
    dev->t1l_sg_task_delay = t1l_single_task_delay;
    dev->th_mt_task_delay = th_mt_task_delay;
    dev->thl_mt_task_delay = thl_mt_task_delay;
    dev->tl_mt_task_delay = tl_mt_task_delay;
}

void ucs1903_single_update(ucs1903_t *dev) {
    /* Gửi 24Bit dữ liệu [R;G;B] mỗi chip */
    for(uint16_t index_chip = 0; index_chip < dev->max_chip_serial; index_chip++) {
        for(uint8_t index_bit = 0; index_bit < 8; index_bit++) {
            if((dev->color_buf[index_chip].r >> index_bit)&0x01) {
                for(uint32_t delay_count = 0; delay_count < dev->t1h_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_set_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) |= (dev->pin_mask);
                    #endif
                }
                for(uint32_t delay_count = 0; delay_count < dev->t1l_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_clr_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) &= ~(dev->pin_mask);
                    #endif
                }
            }else {
                for(uint32_t delay_count = 0; delay_count < dev->t0h_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_set_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) |= (dev->pin_mask);
                    #endif
                }
                for(uint32_t delay_count = 0; delay_count < dev->t0l_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_clr_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) &= ~(dev->pin_mask);
                    #endif
                }
            }
            if((dev->color_buf[index_chip].g >> index_bit)&0x01) {
                for(uint32_t delay_count = 0; delay_count < dev->t1h_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_set_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) |= (dev->pin_mask);
                    #endif
                }
                for(uint32_t delay_count = 0; delay_count < dev->t1l_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_clr_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) &= ~(dev->pin_mask);
                    #endif
                }
            }else {
                for(uint32_t delay_count = 0; delay_count < dev->t0h_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_set_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) |= (dev->pin_mask);
                    #endif
                }
                for(uint32_t delay_count = 0; delay_count < dev->t0l_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_clr_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) &= ~(dev->pin_mask);
                    #endif
                }
            }
            if((dev->color_buf[index_chip].b >> index_bit)&0x01) {
                for(uint32_t delay_count = 0; delay_count < dev->t1h_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_set_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) |= (dev->pin_mask);
                    #endif
                }
                for(uint32_t delay_count = 0; delay_count < dev->t1l_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_clr_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) &= ~(dev->pin_mask);
                    #endif
                }
            }else {
                for(uint32_t delay_count = 0; delay_count < dev->t0h_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_set_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) |= (dev->pin_mask);
                    #endif
                }
                for(uint32_t delay_count = 0; delay_count < dev->t0l_sg_task_delay; delay_count++) {
                    #if UCS1903_IO_SUPPORT_CLR_SET
                    *((uint32_t *)(dev->port_clr_reg)) = (dev->pin_mask);
                    #else
                    *((uint32_t *)(dev->port_reg)) &= ~(dev->pin_mask);
                    #endif
                }
            }
        }
    }
}

void ucs1903_multi_update(ucs1903_t *list_dev, uint16_t num_dev_parallel) {
    uint16_t max_dev_serial = 0;
    uint32_t pin_mask_all_set = 0;
    uint16_t index_dev_parallel = 0;
    uint8_t index_bit = 0;
    uint32_t delay_count = 0;
    uint32_t color_bit_to_io[8][3];

    for(index_dev_parallel = 0; index_dev_parallel < num_dev_parallel; index_dev_parallel++) {
        if(max_dev_serial < list_dev[index_dev_parallel].max_chip_serial) {
            max_dev_serial = list_dev[index_dev_parallel].max_chip_serial;
        }
    }
    for(index_dev_parallel = 0; index_dev_parallel < num_dev_parallel; index_dev_parallel++) {
        pin_mask_all_set |= (list_dev[index_dev_parallel].pin_mask);
    }
    for(uint16_t index_dev_serial = 0; index_dev_serial < max_dev_serial; index_dev_serial++) {
        /* Clear dữ liệu IO */
        color_bit_to_io[0][0] = 0;
        color_bit_to_io[1][0] = 0;
        color_bit_to_io[2][0] = 0;
        color_bit_to_io[3][0] = 0;
        color_bit_to_io[4][0] = 0;
        color_bit_to_io[5][0] = 0;
        color_bit_to_io[6][0] = 0;
        color_bit_to_io[7][0] = 0;
        color_bit_to_io[0][1] = 0;
        color_bit_to_io[1][1] = 0;
        color_bit_to_io[2][1] = 0;
        color_bit_to_io[3][1] = 0;
        color_bit_to_io[4][1] = 0;
        color_bit_to_io[5][1] = 0;
        color_bit_to_io[6][1] = 0;
        color_bit_to_io[7][1] = 0;
        color_bit_to_io[0][2] = 0;
        color_bit_to_io[1][2] = 0;
        color_bit_to_io[2][2] = 0;
        color_bit_to_io[3][2] = 0;
        color_bit_to_io[4][2] = 0;
        color_bit_to_io[5][2] = 0;
        color_bit_to_io[6][2] = 0;
        color_bit_to_io[7][2] = 0;
        /* Convert color sang IO*/
        for(index_dev_parallel = 0; index_dev_parallel < num_dev_parallel; index_dev_parallel++) {
            {
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].r & 0x01) == 0) {
                    color_bit_to_io[0][0] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].r & 0x02) == 0) {
                    color_bit_to_io[1][0] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].r & 0x04) == 0) {
                    color_bit_to_io[2][0] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].r & 0x08) == 0) {
                    color_bit_to_io[3][0] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].r & 0x10) == 0) {
                    color_bit_to_io[4][0] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].r & 0x20) == 0) {
                    color_bit_to_io[5][0] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].r & 0x40) == 0) {
                    color_bit_to_io[6][0] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].r & 0x80) == 0) {
                    color_bit_to_io[7][0] |= (list_dev[index_dev_parallel].pin_mask);
                }
            }
            {
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].g & 0x01) == 0) {
                    color_bit_to_io[0][1] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].g & 0x02) == 0) {
                    color_bit_to_io[1][1] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].g & 0x04) == 0) {
                    color_bit_to_io[2][1] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].g & 0x08) == 0) {
                    color_bit_to_io[3][1] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].g & 0x10) == 0) {
                    color_bit_to_io[4][1] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].g & 0x20) == 0) {
                    color_bit_to_io[5][1] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].g & 0x40) == 0) {
                    color_bit_to_io[6][1] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].g & 0x80) == 0) {
                    color_bit_to_io[7][1] |= (list_dev[index_dev_parallel].pin_mask);
                }
            }
            {
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].b & 0x01) == 0) {
                    color_bit_to_io[0][2] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].b & 0x02) == 0) {
                    color_bit_to_io[1][2] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].b & 0x04) == 0) {
                    color_bit_to_io[2][2] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].b & 0x08) == 0) {
                    color_bit_to_io[3][2] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].b & 0x10) == 0) {
                    color_bit_to_io[4][2] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].b & 0x20) == 0) {
                    color_bit_to_io[5][2] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].b & 0x40) == 0) {
                    color_bit_to_io[6][2] |= (list_dev[index_dev_parallel].pin_mask);
                }
                if((list_dev[index_dev_parallel].color_buf[index_dev_serial].b & 0x80) == 0) {
                    color_bit_to_io[7][2] |= (list_dev[index_dev_parallel].pin_mask);
                }
            }
        }
        /* -------- Gửi Byte màu Red -------- */
        for(index_bit = 0; index_bit < 8; index_bit++) {
            /* Set cả bus lên 1 */
            for(delay_count = 0; delay_count < list_dev[0].th_mt_task_delay; delay_count++) {
                #if UCS1903_IO_SUPPORT_CLR_SET
                *(list_dev[0].port_set_reg) = pin_mask_all_set;
                #else
                *(list_dev[0].port_reg) |= pin_mask_all_set;
                #endif
            }
            /* Đưa các chân bit màu = 0 xuống 0 */
            for(delay_count = 0; delay_count < list_dev[0].thl_mt_task_delay; delay_count++) {
                #if UCS1903_IO_SUPPORT_CLR_SET
                *(list_dev[0].port_clr_reg) = color_bit_to_io[index_bit][0];
                #else
                *(list_dev[0].port_reg) &= ~color_bit_to_io[index_bit][0];
                #endif
            }
            /* Đưa cả bus xuống 0 */
            for(delay_count = 0; delay_count < list_dev[0].tl_mt_task_delay; delay_count++) {
                *(list_dev[0].port_clr_reg) = pin_mask_all_set;
            }
        }
        /* -------- Gửi Byte màu Green -------- */
        for(index_bit = 0; index_bit < 8; index_bit++) {
            /* Set cả bus lên 1 */
            for(delay_count = 0; delay_count < list_dev[0].th_mt_task_delay; delay_count++) {
                #if UCS1903_IO_SUPPORT_CLR_SET
                *(list_dev[0].port_set_reg) = pin_mask_all_set;
                #else
                *(list_dev[0].port_reg) |= pin_mask_all_set;
                #endif
            }
            /* Đưa các chân bit màu = 0 xuống 0 */
            for(delay_count = 0; delay_count < list_dev[0].thl_mt_task_delay; delay_count++) {
                #if UCS1903_IO_SUPPORT_CLR_SET
                *(list_dev[0].port_clr_reg) = color_bit_to_io[index_bit][1];
                #else
                *(list_dev[0].port_reg) &= ~color_bit_to_io[index_bit][1];
                #endif
            }
            /* Đưa cả bus xuống 0 */
            for(delay_count = 0; delay_count < list_dev[0].tl_mt_task_delay; delay_count++) {
                *(list_dev[0].port_clr_reg) = pin_mask_all_set;
            }
        }
        /* -------- Gửi Byte màu Blue -------- */
        for(index_bit = 0; index_bit < 8; index_bit++) {
            /* Set cả bus lên 1 */
            for(delay_count = 0; delay_count < list_dev[0].th_mt_task_delay; delay_count++) {
                #if UCS1903_IO_SUPPORT_CLR_SET
                *(list_dev[0].port_set_reg) = pin_mask_all_set;
                #else
                *(list_dev[0].port_reg) |= pin_mask_all_set;
                #endif
            }
            /* Đưa các chân bit màu = 0 xuống 0 */
            for(delay_count = 0; delay_count < list_dev[0].thl_mt_task_delay; delay_count++) {
                #if UCS1903_IO_SUPPORT_CLR_SET
                *(list_dev[0].port_clr_reg) = color_bit_to_io[index_bit][2];
                #else
                *(list_dev[0].port_reg) &= ~color_bit_to_io[index_bit][2];
                #endif
            }
            /* Đưa cả bus xuống 0 */
            for(delay_count = 0; delay_count < list_dev[0].tl_mt_task_delay; delay_count++) {
                *(list_dev[0].port_clr_reg) = pin_mask_all_set;
            }
        }
    }
}

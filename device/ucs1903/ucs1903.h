/**
  ******************************************************************************
  * @file           : ucs1903.h
  * @brief          : Thư viện điều khiển ucs1903.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    * Thư viện lập trình LED full color ucs1903
  ******************************************************************************
  */

#ifndef __UCS1903_H
#define __UCS1903_H

#include <stdint.h>

/**
 * @brief Cấu hình kiểu IO
 * Nếu chip hỗ trợ thanh ghi set và clear IO:
 * #define UCS1903_IO_SUPPORT_CLR_SET 1
 * Nếu không hỗ trợ:
 * #define UCS1903_IO_SUPPORT_CLR_SET 0
 *
 */
#define UCS1903_IO_SUPPORT_CLR_SET    1

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ucs1903_color_t;

typedef struct {
  #if UCS1903_IO_SUPPORT_CLR_SET
  volatile uint32_t *port_clr_reg;
  volatile uint32_t *port_set_reg;
  #else
    volatile uint32_t *port_reg;
  #endif
    uint32_t pin_mask;
  uint16_t max_chip_serial;
  ucs1903_color_t *color_buf;

  uint32_t t0h_sg_task_delay;
  uint32_t t0l_sg_task_delay;
  uint32_t t1h_sg_task_delay;
  uint32_t t1l_sg_task_delay;

  uint32_t th_mt_task_delay;
  uint32_t thl_mt_task_delay;
  uint32_t tl_mt_task_delay;
} ucs1903_t;


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
                                                                    uint32_t tl_mt_task_delay);
#else
void ucs1903_init(ucs1903_t *dev, uint32_t *port_reg, uint8_t pin_mask,
                                                                    uint16_t max_chip_serial,
                                                                  ucs1903_color_t *color_buf,
                                                                    uint32_t t1h_single_task_delay,
                                                                    uint32_t t1l_single_task_delay,
                                                                    uint32_t t0h_single_task_delay,
                                                                    uint32_t t0l_single_task_delay,
                                                                    uint32_t th_mt_task_delay,
                                                                    uint32_t tl_mt_task_delay);
#endif

void ucs1903_single_update(ucs1903_t *dev);
void ucs1903_multi_update(ucs1903_t *list_dev, uint16_t num_dev_parallel);

#endif

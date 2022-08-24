#ifndef __ST7920_H__
#define __ST7920_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct st7920_struct {
    bool (*drv_send)(uint8_t *data, size_t data_length);
    void (*drv_delay_ms)(uint32_t time_ms);
} st7920_t;

void st7920_init(st7920_t *obj, bool (*drv_send)(uint8_t *, size_t), void (*drv_delay_ms)(uint32_t));
void st7920_set_graphicsmode(st7920_t *obj);
void st7920_set_textmode(st7920_t *obj);
void st7920_draw(st7920_t *obj, uint8_t *bitmap);

#endif

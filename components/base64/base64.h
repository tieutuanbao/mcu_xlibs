#ifndef __BASE64_H__
#define __BASE64_H__

#include <stdint.h>

uint16_t base64_encode(uint8_t *input_p, uint8_t *output_buf, uint16_t input_size);

#endif
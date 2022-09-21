#ifndef __STREAM_H__
#define __STREAM_H__

#include <stdint.h>
#include <c_types.h>
#include <common_macros.h>

#define MAX_NUM_BUF_STEAM   5
#define MAX_SIZE_BUF_STEAM  255

typedef struct _stream_t{
    uint8_t *data;
    size_t len;
    struct _stream_t *next;
} stream_t;

#endif
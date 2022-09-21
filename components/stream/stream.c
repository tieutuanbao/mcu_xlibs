#include "stream.h"

stream_t *stream_init(stream_t **obj) {
    if(obj == 0) {
        obj = malloc(sizeof(void(*)));
        obj[0]->data = 0;
        obj[0]->len = 0;
        obj[0]->next = 0;
    }
}

int32_t stream_write(stream_t **obj, uint8_t * buf_in, uint32_t len) {
    uint16_t buf_remaining = 0;
    /* Đi đến Head của stream */
    for(uint8_t idx_buf = 0; idx_buf < MAX_NUM_BUF_STEAM; idx_buf++) {
        if(obj->next) {
            obj = obj->next;
        }
        else {
            if(obj->data) {
                if(obj->len < MAX_SIZE_BUF_STEAM) {
                    buf_remaining = MAX_SIZE_BUF_STEAM - obj->len;
                }
                if(buf_remaining > len) buf_remaining = obj->len + len;
                obj->data = realloc(obj->data, buf_remaining);
                if(obj->data) {
                    memcpy(obj->data + obj->len, buf_in, len);
                    obj->len = buf_remaining;
                    if(buf_remaining == MAX_SIZE_BUF_STEAM) {
                        obj->next = malloc(sizeof(stream_t));
                        if(obj->next) return -1;
                        obj = obj->next;
                        obj->data = 0;
                        obj->len = 0;
                        obj->next = 0;
                    }
                }
                else {
                    return -1;
                }
            }
            else {
                obj->data = malloc(len);
                if(obj->data) {
                    memcpy(obj->data, buf_in, len);
                }
                obj->len = len;
                if(obj->len == MAX_SIZE_BUF_STEAM) {
                    obj->next = malloc(sizeof(stream_t));
                    if(obj->next) return -1;
                    obj = obj->next;
                    obj->data = 0;
                    obj->len = 0;
                    obj->next = 0;
                }
            }
            break;
        }
    }
}

uint32_t stream_read(stream_t * obj, uint8_t * buf_out, uint32_t len) {
    if(obj->data) {
        /* Số Byte đọc nhiều hơn số Byte có trong Buffer hiện tại */
        if(len > obj->len) {
            memcpy(buf_out, obj->data, obj->len);
            if(obj->next) {
                obj->next
            }
        }
        obj->len -= len;
    }
}
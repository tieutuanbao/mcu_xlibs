/**
  ******************************************************************************
  * @file           : w25qxxx.c
  * @brief          : Thư viện lập trình flash w25qxx.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    * Thư viện lập trình w25qxxx
    *
  ******************************************************************************
  */
#ifndef __W25QXXX_H
#define __W25QXXX_H

#include <stdint.h>

#define W25QXXX_PAGE_SIZE       0x100
#define W25QXXX_SECTOR_SIZE     0x1000
#define W25QXXX_BLOCK_SIZE      0x10000

#define FLASH_ID(n, re, qr, pp, es, ces, id, psize, ssize, size) \
{                                   \
    .name = n,                      \
    .read_cmd = re,                 \
    .qread_cmd = qr,                \
    .pprog_cmd = pp,                \
    .erase_cmd = es,                \
    .chip_erase_cmd = ces,          \
    .device_id = id,                \
    .pagesize = psize,              \
    .sectorsize = ssize,            \
    .size_in_bytes = size,          \
}

#define FRAM_ID(n, re, qr, pp, id, size) \
{                                   \
    .name = n,                      \
    .read_cmd = re,                 \
    .qread_cmd = qr,                \
    .pprog_cmd = pp,                \
    .erase_cmd = 0x00,              \
    .chip_erase_cmd = 0x00,         \
    .device_id = id,                \
    .pagesize = 0,                  \
    .sectorsize = 0,                \
    .size_in_bytes = size,          \
}

typedef struct flash_device {
    const char *name;
    uint8_t read_cmd;
    uint8_t qread_cmd;
    uint8_t pprog_cmd;
    uint8_t erase_cmd;
    uint8_t chip_erase_cmd;
    uint32_t device_id;
    uint32_t pagesize;
    uint32_t sectorsize;
    uint32_t size_in_bytes;
} flash_device_t;

typedef enum {
    W25Q10        = 0XEF10,
    W25Q20        = 0XEF11,
    W25Q40        = 0XEF12,
    W25Q80        = 0XEF13,
    W25Q16        = 0XEF14,
    W25Q32        = 0XEF15,
    W25Q64        = 0XEF16,
    W25Q128        = 0XEF17,
    W25Q256        = 0XEF18,
    W25Q512        = 0XEF19
} w25qxxx_id_t;

typedef enum
{
  W25QXXX_OK = 0,
  W25QXXX_ERROR_PROTOCOL = 1,
  W25QXXX_ERROR_TIME_OUT,
  W25QXXX_ERROR_STATUS,
  W25QXXX_ERROR_OUT_MEMORY,
  W25QXXX_ERROR_NO_BUFFER,
} w25qxxx_stt_t;

typedef enum
{
  W25QXXX_READ_DATA = 0x03,
  W25QXXX_WRITE_DISABLE = 0x04,
  W25QXXX_READ_STATUS_REG1 = 0x05,
  W25QXXX_WRITE_ENABLE = 0x06,
  W25QXXX_READ_STATUS_REG2 = 0x35,
  W25QXXX_READ_STATUS_REG3 = 0x15,
  W25QXXX_WRITE_STATUS_REG1 = 0x01,
  W25QXXX_WRITE_STATUS_REG2 = 0x31,
  W25QXXX_WRITE_STATUS_REG3 = 0x11,
  W25QXXX_FAST_READ_DATA = 0x0B,
  W25QXXX_PAGE_PROGRAM = 0x02,
  W25QXXX_BLOCK_ERASE_32 = 0x52,
  W25QXXX_BLOCK_ERASE_64 = 0xD8,
  W25QXXX_SECTOR_ERASE = 0x20,
  W25QXXX_CHIP_ERASE = 0xC7,
  W25QXXX_POWER_DOWN = 0xB9,
  W25QXXX_RELEASE_POWER_DOWN = 0xAB,
  W25QXXX_DEVICE_ID = 0xAB,
  W25QXXX_MANUFACT_DEVICE_ID = 0x90,
  W25QXXX_BLOCK_LOCK = 0x36,
  W25QXXX_BLOCK_UNLOCK = 0x39,
  W25QXXX_GBLOCK_LOCK = 0x7E,
  W25QXXX_GBLOCK_UNLOCK = 0x98,
} w25qxxx_command_t;

typedef struct {
    w25qxxx_id_t id;
    uint8_t uniq_id[8];
    uint32_t page_count;
    uint32_t sector_count;
    uint32_t block_count;
    uint32_t capacity_in_kb;
    union {
        volatile uint8_t val;
        volatile struct {
            uint8_t BUSY    :   1;
            uint8_t WEL     :   1;
            uint8_t BP0     :   1;
            uint8_t BP1     :   1;
            uint8_t BP2     :   1;
            uint8_t TB      :   1;
            uint8_t SEC     :   1;
            uint8_t SPR0    :   1;
        } bit;
    } stt_reg_1;
    union {
        volatile uint8_t val;
        volatile struct {
            uint8_t BUSY    :   1;
            uint8_t WEL     :   1;
            uint8_t BP0     :   1;
            uint8_t BP1     :   1;
            uint8_t BP2     :   1;
            uint8_t TB      :   1;
            uint8_t SEC     :   1;
            uint8_t SPR0    :   1;
        } bit;
    } stt_reg_2;
    union {
        volatile uint8_t val;
        volatile struct {
            uint8_t BUSY    :   1;
            uint8_t WEL     :   1;
            uint8_t BP0     :   1;
            uint8_t BP1     :   1;
            uint8_t BP2     :   1;
            uint8_t TB      :   1;
            uint8_t SEC     :   1;
            uint8_t SPR0    :   1;
        } bit;
    } stt_reg_3;
    volatile uint8_t lock;

    w25qxxx_stt_t (*write)(uint8_t *buff_to_write, uint32_t size);
    w25qxxx_stt_t (*read)(uint8_t *buff_to_read, uint32_t size);
    void (*cs_control)(uint8_t level);
    void (*delay)(uint32_t ms);
} w25qxxx_t;

w25qxxx_stt_t w25qxxx_init(w25qxxx_t *dev,
                                        w25qxxx_stt_t (*drv_rd)(uint8_t *buff_to_write, uint32_t size),
                                        w25qxxx_stt_t (*drv_wr)(uint8_t *buff_to_write, uint32_t size),
                                        void (*drv_cs_ctrl)(uint8_t level),
                                        void (*drv_delay)(uint32_t ms));

w25qxxx_stt_t w25qxx_get_id(w25qxxx_t *dev);
w25qxxx_stt_t w25qxx_get_status_reg(w25qxxx_t *dev, uint8_t num_reg);
w25qxxx_stt_t w25qxx_set_status_reg(w25qxxx_t *dev, uint8_t num_reg, uint8_t val);
w25qxxx_stt_t w25qxx_set_en_or_dis_write(w25qxxx_t *dev, uint8_t en_or_dis);
w25qxxx_stt_t w25qxx_wait_busy(w25qxxx_t *dev, uint32_t timeout_ms);

w25qxxx_stt_t w25qxx_read_mem(w25qxxx_t *dev, uint32_t read_addr, uint8_t *buf_to_read, uint32_t size_to_read);
w25qxxx_stt_t w25qxx_fast_read_mem(w25qxxx_t *dev, uint32_t read_addr, uint8_t *buf_to_read, uint32_t size_to_read);

w25qxxx_stt_t w25qxx_write_one_page(w25qxxx_t *dev, uint32_t write_addr, uint8_t *buf_to_write, uint32_t size_to_write);
w25qxxx_stt_t w25qxx_write_mem(w25qxxx_t *dev, uint32_t write_addr, uint8_t *buf_to_write, uint32_t size_to_write);

w25qxxx_stt_t w25q_erase_sector(w25qxxx_t *dev, uint32_t index_sector);
w25qxxx_stt_t w25q_erase_block(w25qxxx_t *dev, uint32_t index_block);
w25qxxx_stt_t w25q_erase_chip(w25qxxx_t *dev);

#endif

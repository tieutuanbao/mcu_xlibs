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

#include "w25qxxx.h"
#include "stdio.h"

w25qxxx_stt_t w25qxxx_init(w25qxxx_t *dev,
                                        w25qxxx_stt_t (*drv_rd)(uint8_t *buff_to_read, uint32_t size),
                                        w25qxxx_stt_t (*drv_wr)(uint8_t *buff_to_write, uint32_t size),
                                        void (*drv_cs_ctrl)(uint8_t level),
                                        void (*drv_delay)(uint32_t ms)) {
    /* Đăng ký driver */
    dev->delay = drv_delay;
    dev->read = drv_rd;
    dev->write = drv_wr;
    dev->cs_control = drv_cs_ctrl;

    dev->delay(100);
    /* Kiểm tra ID */
    dev->lock = 1;
    w25qxx_get_id(dev);
    switch (dev->id) {
        case W25Q512:
            dev->block_count = 1024;
            break;
        case W25Q256:
            dev->block_count = 512;
            break;
        case W25Q128:
            dev->block_count = 256;
            break;
        case W25Q64:
            dev->block_count = 128;
            break;
        case W25Q32:
            dev->block_count = 64;
            break;
        case W25Q16:
            dev->block_count = 32;
            break;
        case W25Q80:
            dev->block_count = 16;
            break;
        case W25Q40:
            dev->block_count = 8;
            break;
        case W25Q20:
            dev->block_count = 4;
            break;
        case W25Q10:
            dev->block_count = 2;
            break;
        default:
            dev->lock = 0;
            return W25QXXX_ERROR_PROTOCOL;
    }
    dev->sector_count = dev->block_count * 16;
    dev->page_count = (dev->sector_count * W25QXXX_SECTOR_SIZE) / W25QXXX_PAGE_SIZE;
    dev->capacity_in_kb = (dev->sector_count * W25QXXX_SECTOR_SIZE) / 1024;
    dev->lock = 0;
    return W25QXXX_OK;
}

w25qxxx_stt_t w25qxx_get_id(w25qxxx_t *dev) {
    uint8_t temp_buf[2] = {0,0};
    w25qxxx_stt_t ret = W25QXXX_OK;
    uint8_t cmd_temp;

    dev->cs_control(0);
    cmd_temp = W25QXXX_MANUFACT_DEVICE_ID;
    ret = dev->write(&cmd_temp, 1);
    cmd_temp = 0;
    ret = dev->write(&cmd_temp, 1);
    ret = dev->write(&cmd_temp, 1);
    ret = dev->write(&cmd_temp, 1);
    ret = dev->read(temp_buf, 2);
    dev->cs_control(1);

    dev->id = (w25qxxx_id_t)((temp_buf[0] << 8) | temp_buf[1]);
    return ret;
}

w25qxxx_stt_t w25qxx_get_status_reg(w25qxxx_t *dev, uint8_t num_reg) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp;
    dev->cs_control(0);
    switch(num_reg) {
        default: {
            cmd_temp = W25QXXX_READ_STATUS_REG1;
            ret = dev->write(&cmd_temp, 1);
            ret = dev->read((uint8_t *)&dev->stt_reg_1.val, 1);
            break;
        }
        case 2: {
            cmd_temp = W25QXXX_READ_STATUS_REG2;
            ret = dev->write(&cmd_temp, 1);
            ret = dev->read((uint8_t *)&dev->stt_reg_2.val, 1);
            break;
        }
        case 3: {
            cmd_temp = W25QXXX_READ_STATUS_REG3;
            ret = dev->write(&cmd_temp, 1);
            ret = dev->read((uint8_t *)&dev->stt_reg_3.val, 1);
            break;
        }
    }
    dev->cs_control(1);
    return ret;
}

w25qxxx_stt_t w25qxx_set_status_reg(w25qxxx_t *dev, uint8_t num_reg, uint8_t val) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp;
    dev->cs_control(0);
    switch(num_reg) {
        default: {
            dev->stt_reg_1.val = val;
            cmd_temp = W25QXXX_WRITE_STATUS_REG1;
            ret = dev->write((uint8_t *)&cmd_temp, 1);
            ret = dev->write((uint8_t *)&dev->stt_reg_1.val, 1);
            break;
        }
        case 2: {
            dev->stt_reg_2.val = val;
            cmd_temp = W25QXXX_WRITE_STATUS_REG2;
            ret = dev->write(&cmd_temp, 1);
            ret = dev->write((uint8_t *)&dev->stt_reg_2.val, 1);
            break;
        }
        case 3: {
            dev->stt_reg_3.val = val;
            cmd_temp = W25QXXX_WRITE_STATUS_REG3;
            ret = dev->write(&cmd_temp, 1);
            ret = dev->write((uint8_t *)&dev->stt_reg_3.val, 1);
            break;
        }
    }
    dev->cs_control(1);
    return ret;
}

w25qxxx_stt_t w25qxx_wait_busy(w25qxxx_t *dev, uint32_t timeout_ms) {
    w25qxxx_stt_t ret;
  do {
        ret = w25qxx_get_status_reg(dev, 1);
        if(ret != W25QXXX_OK) {
            return ret;
        }
        dev->delay(1);
    }while((dev->stt_reg_1.bit.BUSY) && (timeout_ms!=0));
    if(timeout_ms == 0) {
        return W25QXXX_ERROR_TIME_OUT;
    }
  return W25QXXX_OK;
}

w25qxxx_stt_t w25qxx_set_en_or_dis_write(w25qxxx_t *dev, uint8_t en_or_dis) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp = en_or_dis?W25QXXX_WRITE_ENABLE:W25QXXX_WRITE_DISABLE;
    dev->cs_control(0);
    ret = dev->write(&cmd_temp, 1);
    dev->cs_control(1);
    return ret;
}

w25qxxx_stt_t w25qxx_read_mem(w25qxxx_t *dev, uint32_t read_addr, uint8_t *buf_to_read, uint32_t size_to_read) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp = 0;
    w25qxx_set_en_or_dis_write(dev, 1);
    dev->cs_control(0);
    cmd_temp = W25QXXX_READ_DATA;
    dev->write(&cmd_temp, 1);
    cmd_temp = (read_addr>>16)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = (read_addr>>8)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = read_addr&0xFF;
    dev->write(&cmd_temp, 1);
    ret = dev->read(buf_to_read, size_to_read);
    dev->cs_control(1);
    return ret;
}

w25qxxx_stt_t w25qxx_fast_read_mem(w25qxxx_t *dev, uint32_t read_addr, uint8_t *buf_to_read, uint32_t size_to_read) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp = 0;
    w25qxx_wait_busy(dev, 5000);
    w25qxx_set_en_or_dis_write(dev, 1);
    dev->cs_control(0);
    cmd_temp = W25QXXX_FAST_READ_DATA;
    dev->write(&cmd_temp, 1);
    cmd_temp = (read_addr>>16)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = (read_addr>>8)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = read_addr&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = 0;
    dev->write(&cmd_temp, 1);
    ret = dev->read(buf_to_read, size_to_read);
    dev->cs_control(1);
    return ret;
}

w25qxxx_stt_t w25qxx_write_one_page(w25qxxx_t *dev, uint32_t write_addr, uint8_t *buf_to_write, uint32_t size_to_write) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp = 0;
    if(((write_addr % W25QXXX_PAGE_SIZE) + size_to_write) > W25QXXX_PAGE_SIZE) {
        ret = W25QXXX_ERROR_OUT_MEMORY;
        goto ret_func;
    }
    while(dev->lock) {
        dev->delay(1);
    }
    dev->lock = 1;
    ret = w25qxx_wait_busy(dev, 5000);
    if(ret != W25QXXX_OK) goto ret_func;
    if(w25qxx_set_en_or_dis_write(dev, 1) != W25QXXX_OK) goto ret_func;
    dev->cs_control(0);
    if(dev->id >= W25Q256) {
        cmd_temp = 0x12;
        dev->write(&cmd_temp, 1);
        cmd_temp = (write_addr & 0xFF000000) >> 24;
        dev->write(&cmd_temp, 1);
    } else {
        cmd_temp = W25QXXX_PAGE_PROGRAM;
        dev->write(&cmd_temp, 1);
    }
    cmd_temp = (write_addr>>16)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = (write_addr>>8)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = write_addr&0xFF;
    dev->write(&cmd_temp, 1);
    ret = dev->write(buf_to_write, size_to_write);
ret_func:
    dev->cs_control(1);
    dev->lock = 0;
    return ret;
}
w25qxxx_stt_t w25qxx_write_mem(w25qxxx_t *dev, uint32_t write_addr, uint8_t *buf_to_write, uint32_t size_to_write) {
    w25qxxx_stt_t ret = W25QXXX_OK;
    uint32_t max_size_to_write = 0;
    do {
        /* Ghi dữ liệu lên mỗi Page */
        max_size_to_write = W25QXXX_PAGE_SIZE - (write_addr % W25QXXX_PAGE_SIZE);
        if(max_size_to_write > size_to_write) max_size_to_write = size_to_write;
        ret = w25qxx_write_one_page(dev, write_addr, buf_to_write, max_size_to_write);
        if(ret != W25QXXX_OK) goto ret_func;
        write_addr += max_size_to_write;
        buf_to_write += max_size_to_write;
        size_to_write -= max_size_to_write;
    }while(size_to_write);
ret_func:
    return ret;
}
w25qxxx_stt_t w25q_erase_chip(w25qxxx_t *dev) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp = 0;

    while(dev->lock) {
        dev->delay(1);
    }
    dev->lock = 1;
    ret = w25qxx_wait_busy(dev, 5000);
    if(ret != W25QXXX_OK) goto ret_func;
    w25qxx_set_en_or_dis_write(dev, 1);
    dev->cs_control(0);
    cmd_temp = W25QXXX_CHIP_ERASE;
    ret = dev->write(&cmd_temp, 1);
    dev->cs_control(1);
ret_func:
    dev->lock = 0;
    return ret;
}
w25qxxx_stt_t w25q_erase_sector(w25qxxx_t *dev, uint32_t index_sector) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp = 0;

    ret = w25qxx_wait_busy(dev, 5000);
    if(ret != W25QXXX_OK) goto ret_func;
    w25qxx_set_en_or_dis_write(dev, 1);

    while(dev->lock) {
        dev->delay(1);
    }
    dev->lock = 1;
    index_sector = index_sector * W25QXXX_SECTOR_SIZE;
    dev->cs_control(0);
    cmd_temp = W25QXXX_SECTOR_ERASE;
    ret = dev->write(&cmd_temp, 1);
    cmd_temp = (index_sector>>16)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = (index_sector>>8)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = index_sector&0xFF;
    dev->write(&cmd_temp, 1);
    dev->cs_control(1);
ret_func:
    dev->lock = 0;
    ret = w25qxx_wait_busy(dev, 5000);
    return ret;
}
w25qxxx_stt_t w25q_erase_block(w25qxxx_t *dev, uint32_t index_block) {
    w25qxxx_stt_t ret;
    uint8_t cmd_temp = 0;

    while(dev->lock) {
        dev->delay(1);
    }
    dev->lock = 1;
    ret = w25qxx_wait_busy(dev, 5000);
    if(ret != W25QXXX_OK) goto ret_func;
    w25qxx_set_en_or_dis_write(dev, 1);
    index_block = index_block * W25QXXX_BLOCK_SIZE;
    dev->cs_control(0);
    cmd_temp = W25QXXX_BLOCK_ERASE_64;
    ret = dev->write(&cmd_temp, 1);
    cmd_temp = (index_block>>16)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = (index_block>>8)&0xFF;
    dev->write(&cmd_temp, 1);
    cmd_temp = index_block&0xFF;
    dev->write(&cmd_temp, 1);
    dev->cs_control(1);
    ret = w25qxx_wait_busy(dev, 5000);
ret_func:
    dev->lock = 0;
    return ret;
}

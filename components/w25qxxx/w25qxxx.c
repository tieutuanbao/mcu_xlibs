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


/* name, read_cmd, qread_cmd, pprog_cmd, erase_cmd, chip_erase_cmd, device_id, pagesize, sectorsize, size_in_bytes */
const flash_device_t flash_devices[] = {
     FLASH_ID("st m25p05",           0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00102020, 0x80,  0x8000,  0x10000),
     FLASH_ID("st m25p10",           0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00112020, 0x80,  0x8000,  0x20000),
     FLASH_ID("st m25p20",           0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00122020, 0x100, 0x10000, 0x40000),
     FLASH_ID("st m25p40",           0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00132020, 0x100, 0x10000, 0x80000),
     FLASH_ID("st m25p80",           0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00142020, 0x100, 0x10000, 0x100000),
     FLASH_ID("st m25p16",           0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00152020, 0x100, 0x10000, 0x200000),
     FLASH_ID("st m25p32",           0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00162020, 0x100, 0x10000, 0x400000),
     FLASH_ID("st m25p64",           0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00172020, 0x100, 0x10000, 0x800000),
     FLASH_ID("st m25p128",          0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00182020, 0x100, 0x40000, 0x1000000),
     FLASH_ID("st m45pe10",          0x03, 0x00, 0x02, 0xd8, 0xd8, 0x00114020, 0x100, 0x10000, 0x20000),
     FLASH_ID("st m45pe20",          0x03, 0x00, 0x02, 0xd8, 0xd8, 0x00124020, 0x100, 0x10000, 0x40000),
     FLASH_ID("st m45pe40",          0x03, 0x00, 0x02, 0xd8, 0xd8, 0x00134020, 0x100, 0x10000, 0x80000),
     FLASH_ID("st m45pe80",          0x03, 0x00, 0x02, 0xd8, 0xd8, 0x00144020, 0x100, 0x10000, 0x100000),
     FLASH_ID("sp s25fl004",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00120201, 0x100, 0x10000, 0x80000),
     FLASH_ID("sp s25fl008",         0x03, 0x08, 0x02, 0xd8, 0xc7, 0x00130201, 0x100, 0x10000, 0x100000),
     FLASH_ID("sp s25fl016",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00140201, 0x100, 0x10000, 0x200000),
     FLASH_ID("sp s25fl116k",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00154001, 0x100, 0x10000, 0x200000),
     FLASH_ID("sp s25fl032",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00150201, 0x100, 0x10000, 0x400000),
     FLASH_ID("sp s25fl132k",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00164001, 0x100, 0x10000, 0x400000),
     FLASH_ID("sp s25fl064",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00160201, 0x100, 0x10000, 0x800000),
     FLASH_ID("sp s25fl164k",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00174001, 0x100, 0x10000, 0x800000),
     FLASH_ID("sp s25fl128s",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00182001, 0x100, 0x10000, 0x1000000),
     FLASH_ID("sp s25fl256s",        0x13, 0x00, 0x12, 0xdc, 0xc7, 0x00190201, 0x100, 0x10000, 0x2000000),
     FLASH_ID("sp s25fl512s",        0x13, 0x00, 0x12, 0xdc, 0xc7, 0x00200201, 0x200, 0x40000, 0x4000000),
     FLASH_ID("cyp s25fl064l",       0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00176001, 0x100, 0x10000, 0x800000),
     FLASH_ID("cyp s25fl128l",       0x03, 0x00, 0x02, 0xd8, 0xc7, 0x00186001, 0x100, 0x10000, 0x1000000),
     FLASH_ID("cyp s25fl256l",       0x13, 0x00, 0x12, 0xdc, 0xc7, 0x00196001, 0x100, 0x10000, 0x2000000),
     FLASH_ID("atmel 25f512",        0x03, 0x00, 0x02, 0x52, 0xc7, 0x0065001f, 0x80,  0x8000,  0x10000),
     FLASH_ID("atmel 25f1024",       0x03, 0x00, 0x02, 0x52, 0x62, 0x0060001f, 0x100, 0x8000,  0x20000),
     FLASH_ID("atmel 25f2048",       0x03, 0x00, 0x02, 0x52, 0x62, 0x0063001f, 0x100, 0x10000, 0x40000),
     FLASH_ID("atmel 25f4096",       0x03, 0x00, 0x02, 0x52, 0x62, 0x0064001f, 0x100, 0x10000, 0x80000),
     FLASH_ID("atmel 25fs040",       0x03, 0x00, 0x02, 0xd7, 0xc7, 0x0004661f, 0x100, 0x10000, 0x80000),
     FLASH_ID("adesto 25df081a",     0x03, 0x00, 0x02, 0xd8, 0xc7, 0x0001451f, 0x100, 0x10000, 0x100000),
     FLASH_ID("mac 25l512",          0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001020c2, 0x010, 0x10000, 0x10000),
     FLASH_ID("mac 25l1005",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001120c2, 0x010, 0x10000, 0x20000),
     FLASH_ID("mac 25l2005",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001220c2, 0x010, 0x10000, 0x40000),
     FLASH_ID("mac 25l4005",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001320c2, 0x010, 0x10000, 0x80000),
     FLASH_ID("mac 25l8005",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001420c2, 0x010, 0x10000, 0x100000),
     FLASH_ID("mac 25l1605",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001520c2, 0x100, 0x10000, 0x200000),
     FLASH_ID("mac 25l3205",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001620c2, 0x100, 0x10000, 0x400000),
     FLASH_ID("mac 25l6405",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001720c2, 0x100, 0x10000, 0x800000),
     FLASH_ID("mac 25l12845",        0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001820c2, 0x100, 0x10000, 0x1000000),
     FLASH_ID("mac 25l25645",        0x13, 0xec, 0x12, 0xdc, 0xc7, 0x001920c2, 0x100, 0x10000, 0x2000000),
     FLASH_ID("mac 25l51245",        0x13, 0xec, 0x12, 0xdc, 0xc7, 0x001a20c2, 0x100, 0x10000, 0x4000000),
     FLASH_ID("mac 25lm51245",       0x13, 0xec, 0x12, 0xdc, 0xc7, 0x003a85c2, 0x100, 0x10000, 0x4000000),
     FLASH_ID("mac 25r512f",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001028c2, 0x100, 0x10000, 0x10000),
     FLASH_ID("mac 25r1035f",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001128c2, 0x100, 0x10000, 0x20000),
     FLASH_ID("mac 25r2035f",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001228c2, 0x100, 0x10000, 0x40000),
     FLASH_ID("mac 25r4035f",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001328c2, 0x100, 0x10000, 0x80000),
     FLASH_ID("mac 25r8035f",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001428c2, 0x100, 0x10000, 0x100000),
     FLASH_ID("mac 25r1635f",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001528c2, 0x100, 0x10000, 0x200000),
     FLASH_ID("mac 25r3235f",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001628c2, 0x100, 0x10000, 0x400000),
     FLASH_ID("mac 25r6435f",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001728c2, 0x100, 0x10000, 0x800000),
     FLASH_ID("mac 25u1635e",        0x03, 0xeb, 0x02, 0x20, 0xc7, 0x003525c2, 0x100, 0x1000,  0x100000),
     FLASH_ID("micron n25q032",      0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x0016ba20, 0x100, 0x10000, 0x400000),
     FLASH_ID("micron n25q064",      0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x0017ba20, 0x100, 0x10000, 0x800000),
     FLASH_ID("micron n25q128",      0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x0018ba20, 0x100, 0x10000, 0x1000000),
     FLASH_ID("micron n25q256 3v",   0x13, 0xec, 0x12, 0xdc, 0xc7, 0x0019ba20, 0x100, 0x10000, 0x2000000),
     FLASH_ID("micron n25q256 1.8v", 0x13, 0xec, 0x12, 0xdc, 0xc7, 0x0019bb20, 0x100, 0x10000, 0x2000000),
     FLASH_ID("micron mt25ql512",    0x13, 0xec, 0x12, 0xdc, 0xc7, 0x0020ba20, 0x100, 0x10000, 0x4000000),
     FLASH_ID("micron mt25ql01",     0x13, 0xec, 0x12, 0xdc, 0xc7, 0x0021ba20, 0x100, 0x10000, 0x8000000),
     FLASH_ID("micron mt25ql02",     0x13, 0xec, 0x12, 0xdc, 0xc7, 0x0022ba20, 0x100, 0x10000, 0x10000000),
     FLASH_ID("win w25q80bv",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001440ef, 0x100, 0x10000, 0x100000),
     FLASH_ID("win w25q16jv",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001540ef, 0x100, 0x10000, 0x200000),
     FLASH_ID("win w25q16jv",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001570ef, 0x100, 0x10000, 0x200000), /* QPI / DTR */
     FLASH_ID("win w25q32fv/jv",     0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001640ef, 0x100, 0x10000, 0x400000),
     FLASH_ID("win w25q32fv",        0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001660ef, 0x100, 0x10000, 0x400000), /* QPI mode */
     FLASH_ID("win w25q32jv",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001670ef, 0x100, 0x10000, 0x400000),
     FLASH_ID("win w25q64fv/jv",     0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001740ef, 0x100, 0x10000, 0x800000),
     FLASH_ID("win w25q64fv",        0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001760ef, 0x100, 0x10000, 0x800000), /* QPI mode */
     FLASH_ID("win w25q64jv",        0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001770ef, 0x100, 0x10000, 0x800000),
     FLASH_ID("win w25q128fv/jv",    0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001840ef, 0x100, 0x10000, 0x1000000),
     FLASH_ID("win w25q128fv",       0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001860ef, 0x100, 0x10000, 0x1000000), /* QPI mode */
     FLASH_ID("win w25q128jv",       0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001870ef, 0x100, 0x10000, 0x1000000),
     FLASH_ID("win w25q256fv/jv",    0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001940ef, 0x100, 0x10000, 0x2000000),
     FLASH_ID("win w25q256fv",       0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001960ef, 0x100, 0x10000, 0x2000000), /* QPI mode */
     FLASH_ID("win w25q256jv",       0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001970ef, 0x100, 0x10000, 0x2000000),
     FLASH_ID("gd gd25q512",         0x03, 0x00, 0x02, 0x20, 0xc7, 0x001040c8, 0x100, 0x1000,  0x10000),
     FLASH_ID("gd gd25q10",          0x03, 0x00, 0x02, 0x20, 0xc7, 0x001140c8, 0x100, 0x1000,  0x20000),
     FLASH_ID("gd gd25q20",          0x03, 0x00, 0x02, 0x20, 0xc7, 0x001240c8, 0x100, 0x1000,  0x40000),
     FLASH_ID("gd gd25q40",          0x03, 0x00, 0x02, 0x20, 0xc7, 0x001340c8, 0x100, 0x1000,  0x80000),
     FLASH_ID("gd gd25q16c",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001540c8, 0x100, 0x10000, 0x200000),
     FLASH_ID("gd gd25q32c",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001640c8, 0x100, 0x10000, 0x400000),
     FLASH_ID("gd gd25q64c",         0x03, 0x00, 0x02, 0xd8, 0xc7, 0x001740c8, 0x100, 0x10000, 0x800000),
     FLASH_ID("gd gd25q128c",        0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x001840c8, 0x100, 0x10000, 0x1000000),
     FLASH_ID("gd gd25q256c",        0x13, 0x00, 0x12, 0xdc, 0xc7, 0x001940c8, 0x100, 0x10000, 0x2000000),
     FLASH_ID("gd gd25q512mc",       0x13, 0x00, 0x12, 0xdc, 0xc7, 0x002040c8, 0x100, 0x10000, 0x4000000),
     FLASH_ID("issi is25lp032",      0x03, 0x00, 0x02, 0xd8, 0xc7, 0x0016609d, 0x100, 0x10000, 0x400000),
     FLASH_ID("issi is25lp064",      0x03, 0x00, 0x02, 0xd8, 0xc7, 0x0017609d, 0x100, 0x10000, 0x800000),
     FLASH_ID("issi is25lp128d",     0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x0018609d, 0x100, 0x10000, 0x1000000),
     FLASH_ID("issi is25wp128d",     0x03, 0xeb, 0x02, 0xd8, 0xc7, 0x0018709d, 0x100, 0x10000, 0x1000000),
     FLASH_ID("issi is25lp256d",     0x13, 0xec, 0x12, 0xdc, 0xc7, 0x0019609d, 0x100, 0x10000, 0x2000000),
     FLASH_ID("issi is25wp256d",     0x13, 0xec, 0x12, 0xdc, 0xc7, 0x0019709d, 0x100, 0x10000, 0x2000000),
     FLASH_ID("issi is25lp512m",     0x13, 0xec, 0x12, 0xdc, 0xc7, 0x001a609d, 0x100, 0x10000, 0x4000000),
     FLASH_ID("issi is25wp512m",     0x13, 0xec, 0x12, 0xdc, 0xc7, 0x001a709d, 0x100, 0x10000, 0x4000000),
 
     /* FRAM, no erase commands, no write page or sectors */
     FRAM_ID("fu mb85rs16n",         0x03, 0,    0x02, 0x00010104, 0x800),
     FRAM_ID("fu mb85rs32v",         0x03, 0,    0x02, 0x00010204, 0x1000), /* exists ? */
     FRAM_ID("fu mb85rs64v",         0x03, 0,    0x02, 0x00020304, 0x2000),
     FRAM_ID("fu mb85rs128b",        0x03, 0,    0x02, 0x00090404, 0x4000),
     FRAM_ID("fu mb85rs256b",        0x03, 0,    0x02, 0x00090504, 0x8000),
     FRAM_ID("fu mb85rs512t",        0x03, 0,    0x02, 0x00032604, 0x10000),
     FRAM_ID("fu mb85rs1mt",         0x03, 0,    0x02, 0x00032704, 0x20000),
     FRAM_ID("fu mb85rs2mta",        0x03, 0,    0x02, 0x00034804, 0x40000),
     FRAM_ID("cyp fm25v01a",         0x03, 0,    0x02, 0x000821c2, 0x4000),
     FRAM_ID("cyp fm25v02",          0x03, 0,    0x02, 0x000022c2, 0x8000),
     FRAM_ID("cyp fm25v02a",         0x03, 0,    0x02, 0x000822c2, 0x8000),
     FRAM_ID("cyp fm25v05",          0x03, 0,    0x02, 0x000023c2, 0x10000),
     FRAM_ID("cyp fm25v10",          0x03, 0,    0x02, 0x000024c2, 0x20000),
     FRAM_ID("cyp fm25v20a",         0x03, 0,    0x02, 0x000825c2, 0x40000),
     FRAM_ID("cyp fm25v40",          0x03, 0,    0x02, 0x004026c2, 0x80000),
 
     FLASH_ID(NULL,                  0,    0,    0,    0,    0,    0,          0,     0,       0)
};

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

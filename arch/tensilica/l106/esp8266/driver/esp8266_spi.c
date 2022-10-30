/**
 * @file esp8266_spi.c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>
#include "esp8266_iomux.h"
#include "esp8266_gpio.h"
#include "esp8266_spi.h"

#define _SPI0_SCK_GPIO  6
#define _SPI0_MISO_GPIO 7
#define _SPI0_MOSI_GPIO 8
#define _SPI0_HD_GPIO   9
#define _SPI0_WP_GPIO   10
#define _SPI0_CS0_GPIO  11

#define _SPI1_MISO_GPIO 12
#define _SPI1_MOSI_GPIO 13
#define _SPI1_SCK_GPIO  14
#define _SPI1_CS0_GPIO  15

#define _SPI0_FUNC IOMUX_FUNC(1)
#define _SPI1_FUNC IOMUX_FUNC(2)

#define _SPI_BUF_SIZE 64
#define __min(a,b) ((a > b) ? (b):(a))


#define SPI_WRITE_MAX_SIZE  64
#define SPI_READ_MAX_SIZE   60

static bool _minimal_pins[2] = {false, false};

flashchip_t sys_flashchip = {
    .device_id = 0x001640ef,        // device_id
    .chip_size = 4 * 1024 * 1024,   // chip_size
    .block_size = 65536,            // block_size
    .sector_size = 4096,            // sector_size
    .page_size = 256,               // page_size
    .status_mask = 0x0000ffff       // status_mask
};

/**
 * @brief Khởi tạo bus SPI
 * Bus 0:
 *   - MISO = GPIO 7
 *   - MOSI = GPIO 8
 *   - SCK  = GPIO 6
 *   - CS0  = GPIO 11 (if minimal_pins is false)
 *   - HD   = GPIO 9  (if minimal_pins is false)
 *   - WP   = GPIO 10 (if minimal_pins is false)
 * Bus 1:
 *   - MISO = GPIO 12
 *   - MOSI = GPIO 13
 *   - SCK  = GPIO 14
 *   - CS0  = GPIO 15 (if minimal_pins is false)
 * Lưu ý: Bộ nhớ flash hệ thống đang ở trên Bus 0!
 * 
 * @param bus Bus ID: 0 - system, 1 - user
 * @param mode 
 * @param freq_divider Bộ chia tần số SPI, có thể sử dụng SPI_GET_FREQ_DIV()
 * @param msb 
 * @param endianness 
 * @param minimal_pins true : chỉ dùng các chân MISO, MOSI và SCK.
 * @return true 
 * @return false 
 */
ICACHE_FLASH_ATTR bool spi_init(uint8_t bus, spi_mode_t mode, uint32_t freq_divider, bool msb, spi_endianness_t endianness, bool minimal_pins) {
    switch (bus)
    {
        case 0:
            gpio_set_iomux_function(_SPI0_MISO_GPIO, _SPI0_FUNC);
            gpio_set_iomux_function(_SPI0_MOSI_GPIO, _SPI0_FUNC);
            gpio_set_iomux_function(_SPI0_SCK_GPIO, _SPI0_FUNC);
            if (!minimal_pins)
            {
                gpio_set_iomux_function(_SPI0_HD_GPIO, _SPI0_FUNC);
                gpio_set_iomux_function(_SPI0_WP_GPIO, _SPI0_FUNC);
                gpio_set_iomux_function(_SPI0_CS0_GPIO, _SPI0_FUNC);
            }
            break;
        case 1:
            gpio_set_iomux_function(_SPI1_MISO_GPIO, _SPI1_FUNC);
            gpio_set_iomux_function(_SPI1_MOSI_GPIO, _SPI1_FUNC);
            gpio_set_iomux_function(_SPI1_SCK_GPIO, _SPI1_FUNC);
            if (!minimal_pins)
                gpio_set_iomux_function(_SPI1_CS0_GPIO, _SPI1_FUNC);
            break;
        default:
            return false;
    }

    _minimal_pins[bus] = minimal_pins;
    SPI(bus)->user0.val = MASK_BIT(SPI_USER0_MOSI) | MASK_BIT(SPI_USER0_CLOCK_IN_EDGE) | MASK_BIT(SPI_USER0_DUPLEX) | 
                            (minimal_pins ? 0 : (MASK_BIT(SPI_USER0_CS_HOLD) | MASK_BIT(SPI_USER0_CS_SETUP)));

    spi_set_frequency_div(bus, freq_divider);
    spi_set_mode(bus, mode);
    spi_set_msb(bus, msb);
    spi_set_endianness(bus, endianness);

    return true;
}

/**
 * @brief Khởi tạo spi bằng cấu trúc spi_settings_t
 * 
 * @param bus Bus ID: 0 - system, 1 - user
 * @param s Con trỏ đến cấu trúc setting
 * @return true 
 * @return false 
 */
ICACHE_FLASH_ATTR static inline bool spi_set_settings(uint8_t bus, const spi_settings_t *s)
{
    return spi_init(bus, s->mode, s->freq_divider, s->msb, s->endianness, s->minimal_pins);
}

ICACHE_FLASH_ATTR void spi_set_mode(uint8_t bus, spi_mode_t mode)
{
    bool cpha = (uint8_t)mode & 1;
    bool cpol = (uint8_t)mode & 2;
    if (cpol)
        cpha = !cpha;  // CPHA must be inverted when CPOL = 1, I have no idea why

    // CPHA
    if (cpha)
        SPI(bus)->user0.val |= MASK_BIT(SPI_USER0_CLOCK_OUT_EDGE);
    else
        SPI(bus)->user0.val &= ~MASK_BIT(SPI_USER0_CLOCK_OUT_EDGE);

    // CPOL - see http://bbs.espressif.com/viewtopic.php?t=342#p5384
    if (cpol)
        SPI(bus)->pin.val |= MASK_BIT(SPI_PIN_IDLE_EDGE);
    else
        SPI(bus)->pin.val &= ~MASK_BIT(SPI_PIN_IDLE_EDGE);
}

ICACHE_FLASH_ATTR spi_mode_t spi_get_mode(uint8_t bus)
{
    uint8_t cpha = SPI(bus)->user0.val & SPI_USER0_CLOCK_OUT_EDGE ? 1 : 0;
    uint8_t cpol = SPI(bus)->pin.val & SPI_PIN_IDLE_EDGE ? 2 : 0;

    return (spi_mode_t)(cpol | (cpol ? 1 - cpha : cpha)); // see spi_set_mode
}

/**
 * @brief Cấu hình thứ tự sắp xếp bit bus SPI
 * 
 * @param msb true: MSB ; false: LSB
 * @param endianness 
 */
ICACHE_FLASH_ATTR void spi_set_msb(uint8_t bus, bool msb)
{
    if (msb)
        SPI(bus)->ctrl0.val &= ~(MASK_BIT(SPI_CTRL0_WR_BIT_ORDER) | MASK_BIT(SPI_CTRL0_RD_BIT_ORDER));
    else
        SPI(bus)->ctrl0.val |= (MASK_BIT(SPI_CTRL0_WR_BIT_ORDER) | MASK_BIT(SPI_CTRL0_RD_BIT_ORDER));
}

/**
 * @brief Cấu hình thứ tự sắp xếp Byte bus SPI
 * 
 * @param bus 
 * @param endianness 
 */
ICACHE_FLASH_ATTR void spi_set_endianness(uint8_t bus, spi_endianness_t endianness)
{
    if (endianness == SPI_BIG_ENDIAN)
        SPI(bus)->user0.val |= (MASK_BIT(SPI_USER0_WR_BYTE_ORDER) | MASK_BIT(SPI_USER0_RD_BYTE_ORDER));
    else
        SPI(bus)->user0.val &= ~(MASK_BIT(SPI_USER0_WR_BYTE_ORDER) | MASK_BIT(SPI_USER0_RD_BYTE_ORDER));
}

/**
 * @brief Cấu hình tần số spi
 * 
 * @param bus 
 * @param divider 
 */
ICACHE_FLASH_ATTR void spi_set_frequency_div(uint8_t bus, uint32_t divider) {
    uint32_t predivider = (divider & 0xffff) - 1;
    uint32_t count = (divider >> 16) - 1;
    if (count || predivider) {
        IOMUX->conf &= ~(bus == 0 ? MASK_BIT(IOMUX_CONF_SPI0_CLOCK_EQU_SYS_CLOCK) : MASK_BIT(IOMUX_CONF_SPI1_CLOCK_EQU_SYS_CLOCK));
        SPI(bus)->clock.val =   ((predivider << SPI_CLOCK_DIV_PRE_POS) & SPI_CLOCK_DIV_PRE_MASK) |
                                ((count << SPI_CLOCK_COUNT_NUM_POS) & SPI_CLOCK_COUNT_NUM_MASK) |
                                (((count / 2) << SPI_CLOCK_COUNT_HIGH_POS) & SPI_CLOCK_COUNT_HIGH_MASK) |
                                ((count << SPI_CLOCK_COUNT_LOW_POS) & SPI_CLOCK_COUNT_LOW_MASK);
    }
    else {
        IOMUX->conf |= bus == 0 ? MASK_BIT(IOMUX_CONF_SPI0_CLOCK_EQU_SYS_CLOCK) : MASK_BIT(IOMUX_CONF_SPI1_CLOCK_EQU_SYS_CLOCK);
        SPI(bus)->clock.val = SPI_CLOCK_EQU_SYS_CLOCK;
    }
}

__attribute__((section(".text"))) inline static void spi_wait_ready(void) {
    /* Wait for SPI state machine ready */
    while(SPI(0)->ext2 & 0x07);
}

__attribute__((section(".text"))) static bool spi_is_ready(void) {
    spi_wait_ready();
    SPI(0)->rd_status.val = 0;
    /* Issue read status command */
    SPI(0)->cmd.flash_rdsr = 1;
    while(SPI(0)->cmd.val != 0);
    uint32_t status_value = SPI(0)->rd_status.val;
    return (status_value & 0x01) == 0;
}

__attribute__((section(".text"))) static void spi_write_enable(void) {
    while(!spi_is_ready());
    SPI(0)->cmd.flash_wren = 1;
    while(SPI(0)->cmd.val != 0);
}

__attribute__((section(".text"))) static inline void spi_write_data(flashchip_t *chip, uint32_t addr, uint8_t *buf, uint32_t size)
{
    uint32_t words = size >> 2;
    if (size & 0b11) {
        words++;
    }

    while(!spi_is_ready());
    SPI(0)->addr = (addr & 0x00FFFFFF) | (size << 24);
    memcpy((void*)SPI(0)->data_buf, buf, words << 2);
    __asm__ volatile("memw");
    spi_write_enable();
    SPI(0)->cmd.flash_pp = 1;
    while (SPI(0)->cmd.val);
}

__attribute__((section(".text"))) void test_write_page(uint32_t addr, uint8_t *buf, uint32_t size) {
    /**
     * @brief Vô hiệu hóa các ngắt 
     */
    ETS_INTR_LOCK();
    Cache_Read_Disable();

    spi_write_data(&sys_flashchip, addr, buf, size);
    
spi_write_byte_err:
    Cache_Read_Enable(0, 0, 1);
    ETS_INTR_UNLOCK();
}

__attribute__((section(".text"))) static bool spi_write_page(flashchip_t *flashchip, uint32_t dest_addr, uint8_t *buf, uint32_t size) {
    if (flashchip->page_size < size + (dest_addr % flashchip->page_size)) {
        return false;
    }
    if (size < 1) {
        return true;
    }
    while (size >= SPI_WRITE_MAX_SIZE) {
        spi_write_data(flashchip, dest_addr, buf, SPI_WRITE_MAX_SIZE);

        size -= SPI_WRITE_MAX_SIZE;
        dest_addr += SPI_WRITE_MAX_SIZE;
        buf += SPI_WRITE_MAX_SIZE;

        if (size < 1) {
            return true;
        }
    }

    spi_write_data(flashchip, dest_addr, buf, size);

    return true;
}

/**
 * @brief Hàm ghi flash spi theo Byte
 * 
 * @param addr 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
__attribute__((section(".text"))) bool spi_write_align_byte(uint32_t addr, uint8_t *buf, uint32_t size) {
    if (buf) {
        /**
         * @brief Vô hiệu hóa các ngắt 
         */
        ETS_INTR_LOCK();
        Cache_Read_Disable();
        /**
         * @brief Bắt đầu ghi
         */
        if (sys_flashchip.chip_size < (addr + size)) {
            Cache_Read_Enable(0, 0, 1);
            ETS_INTR_UNLOCK();
            return false;
        }
        uint32_t write_bytes_to_page = sys_flashchip.page_size - (addr % sys_flashchip.page_size);  // TODO: place for optimization
        if (size < write_bytes_to_page) {
            if (!spi_write_page(&sys_flashchip, addr, buf, size)) {
                Cache_Read_Enable(0, 0, 1);
                ETS_INTR_UNLOCK();
                return false;
            }
        }
        else {
            if (!spi_write_page(&sys_flashchip, addr, buf, write_bytes_to_page)) {
                Cache_Read_Enable(0, 0, 1);
                ETS_INTR_UNLOCK();
                return false;
            }

            uint32_t offset = write_bytes_to_page;
            uint32_t pages_to_write = (size - offset) / sys_flashchip.page_size;
            for (uint32_t i = 0; i < pages_to_write; i++) {
                if (!spi_write_page(&sys_flashchip, addr + offset, buf + offset, sys_flashchip.page_size)) {
                    Cache_Read_Enable(0, 0, 1);
                    ETS_INTR_UNLOCK();
                    return false;
                }
                offset += sys_flashchip.page_size;
            }

            if (!spi_write_page(&sys_flashchip, addr + offset,
                        buf + offset, size - offset)) {
                Cache_Read_Enable(0, 0, 1);
                ETS_INTR_UNLOCK();
                return false;
            }
        }
        while(!spi_is_ready());
        Cache_Read_Enable(0, 0, 1);
        ETS_INTR_UNLOCK();
    }
    return true;
}

__attribute__((section(".text"))) static inline void read_block(flashchip_t *chip, uint32_t addr, uint8_t *buf, uint32_t size){
    SPI(0)->addr = (addr & 0x00FFFFFF) | (size << 24);
    SPI(0)->cmd.val = MASK_BIT(SPI_CMD_READ);
    while(SPI(0)->cmd.val) {};
    __asm__ volatile("memw");
    memcpy(buf, (const void*)SPI(0)->data_buf, size);
}
/**
 * @brief Hàm đọc SPI theo Byte
 * 
 * @param dest_addr 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
__attribute__((section(".text"))) bool spi_read_align_byte(uint32_t addr, uint8_t *buf, uint32_t size) {
    bool result = true;
    if (buf) {
        /**
         * @brief Vô hiệu hóa các ngắt 
         */
        ETS_INTR_LOCK();
        Cache_Read_Disable();
        /**
         * @brief Bắt đầu Đọc
         */
        if (size < 1) {
            result = false;
            goto spi_read_byte_err;
        }
        if ((addr + size) > sys_flashchip.chip_size) {
            BITS_LOGE("Flash size out of mem!\r\n");
            result = false;
            goto spi_read_byte_err;
        }
        while (size >= SPI_READ_MAX_SIZE) {
            read_block(&sys_flashchip, addr, buf, SPI_READ_MAX_SIZE);
            buf += SPI_READ_MAX_SIZE;
            size -= SPI_READ_MAX_SIZE;
            addr += SPI_READ_MAX_SIZE;
        }
        if (size > 0) {
            read_block(&sys_flashchip, addr, buf, size);
        }
spi_read_byte_err:
        Cache_Read_Enable(0, 0, 1);
        ETS_INTR_UNLOCK();
    }
    return result;
}
__attribute__((section(".text"))) bool spi_erase_sector(uint32_t addr) {
    if ((addr + sys_flashchip.sector_size) > sys_flashchip.chip_size) {
        return false;
    }
    if (addr & 0xFFF) {
        return false;
    }
    /**
     * @brief Vô hiệu hóa các ngắt 
     */
    ETS_INTR_LOCK();
    Cache_Read_Disable();
    /**
     * @brief Cho phép ghi flash 
     */
    spi_write_enable();
    /**
     * @brief Xóa sector 
     */
    SPI(0)->addr = addr & 0x00FFFFFF;
    SPI(0)->cmd.flash_se = 1;
    while (SPI(0)->cmd.val);
    /**
     * @brief Chờ xóa xong
     */
    while(spi_is_ready() == false);
    /**
     * @brief Cho phép ngắt
     */
    Cache_Read_Enable(0, 0, 1);
    ETS_INTR_UNLOCK();

    return true;
}
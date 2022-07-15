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

#include "esp8266_spi.h"

#include "esp8266_iomux.h"
#include "esp8266_gpio.h"
#include <string.h>

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

static bool _minimal_pins[2] = {false, false};

flashchip_t sys_flashchip = {
    0x001640ef,      // device_id
    4 * 1024 * 1024, // chip_size
    65536,           // block_size
    4096,            // sector_size
    256,             // page_size
    0x0000ffff,      // status_mask
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
bool spi_init(uint8_t bus, spi_mode_t mode, uint32_t freq_divider, bool msb, spi_endianness_t endianness, bool minimal_pins)
{
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
static inline bool spi_set_settings(uint8_t bus, const spi_settings_t *s)
{
    return spi_init(bus, s->mode, s->freq_divider, s->msb, s->endianness, s->minimal_pins);
}

void spi_set_mode(uint8_t bus, spi_mode_t mode)
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

spi_mode_t spi_get_mode(uint8_t bus)
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
void spi_set_msb(uint8_t bus, bool msb)
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
void spi_set_endianness(uint8_t bus, spi_endianness_t endianness)
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
void spi_set_frequency_div(uint8_t bus, uint32_t divider) {
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

/**
 * @brief Hàm ghi flash spi theo Byte
 * 
 * @param addr 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
bool spi_write_align_byte(uint32_t addr, uint8_t *buf, uint32_t size) {
    uint32_t first_page_portion;
    uint32_t pos;
    uint32_t full_pages;
    uint32_t bytes_remaining;

    bool result = false;

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
                result = false;
                goto spi_write_byte_err;
        }
        uint32_t write_bytes_to_page = sys_flashchip.page_size - (addr % sys_flashchip.page_size);  // TODO: place for optimization
        if (size < write_bytes_to_page) {
            if (!spi_write_page(&sys_flashchip, addr, buf, size)) {
                result = false;
                goto spi_write_byte_err;
            }
        } else {
            if (!spi_write_page(&sys_flashchip, addr, buf, write_bytes_to_page)) {
                result = false;
                goto spi_write_byte_err;
            }

            uint32_t offset = write_bytes_to_page;
            uint32_t pages_to_write = (size - offset) / sys_flashchip.page_size;
            for (uint32_t i = 0; i < pages_to_write; i++) {
                if (!spi_write_page(&sys_flashchip, addr + offset,
                            buf + offset, sys_flashchip.page_size)) {
                    result = false;
                    goto spi_write_byte_err;
                }
                offset += sys_flashchip.page_size;
            }

            if (!spi_write_page(&sys_flashchip, addr + offset,
                        buf + offset, size - offset)) {
                result = false;
                goto spi_write_byte_err;
            }
        }

spi_write_byte_err:
        Cache_Read_Enable(0, 0, 1);
        ETS_INTR_UNLOCK();
    }
    return result;
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
bool spi_read_align_byte(uint32_t dest_addr, uint8_t *buf, uint32_t size)
{
    bool result = false;

    if (buf) {
        vPortEnterCritical();
        Cache_Read_Disable();

        result = read_data(&sys_flashchip, dest_addr, buf, size);

        Cache_Read_Enable(0, 0, 1);
        vPortExitCritical();
    }

    return result;
}
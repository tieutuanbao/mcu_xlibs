/**
 * @file esp8266_slc.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ESP8266_SLC_H
#define __ESP8266_SLC_H

#include "esp8266_regs.h"

/* Register definitions for the SPI peripherals on the ESP8266.
 *
 * There are twp SPI devices built into the ESP8266:
 *   SPI(0) is at 0x60000200
 *   SPI(1) is at 0x60000100
 * (note that the device number order is reversed in memory)
 *
 * Each device is allocated a block of 64 32-bit registers (256 bytes of
 * address space) to communicate with application code.
 */

#define SPI(i) (*(struct SPI_REGS *)(SPI_BASE - (i)*0x100))

#define SPI0_BASE SPI_BASE
#define SPI1_BASE (SPI_BASE - 0x100)

struct struct_i2s {
    volatile uint32_t cmd;          // 0x00
    volatile uint32_t addr;         // 0x04
    volatile uint32_t ctrl0;        // 0x08
    volatile uint32_t ctrl1;        // 0x0c
    volatile uint32_t rstatus;      // 0x10
    volatile uint32_t ctrl2;        // 0x14
    volatile uint32_t clock;        // 0x18
    volatile uint32_t user0;        // 0x1c
    volatile uint32_t user1;        // 0x20
    volatile uint32_t user2;        // 0x24
    volatile uint32_t wstatus;      // 0x28
    volatile uint32_t pin;          // 0x2c
    volatile uint32_t slave0;       // 0x30
    volatile uint32_t slave1;       // 0x34
    volatile uint32_t slave2;       // 0x38
    volatile uint32_t slave3;       // 0x3c
    volatile uint32_t w[16];        // 0x40 - 0x7c
    volatile uint32_t _unused[28];  // 0x80 - 0xec
    volatile uint32_t ext0;         // 0xf0
    volatile uint32_t ext1;         // 0xf4
    volatile uint32_t ext2;         // 0xf8
    volatile uint32_t ext3;         // 0xfc
} i2s_t;

/* Details for CMD register */

#define SPI_CMD_READ                       BIT(31)
#define SPI_CMD_WRITE_ENABLE               BIT(30)
#define SPI_CMD_WRITE_DISABLE              BIT(29)
#define SPI_CMD_READ_ID                    BIT(28)
#define SPI_CMD_READ_SR                    BIT(27)
#define SPI_CMD_WRITE_SR                   BIT(26)
#define SPI_CMD_PP                         BIT(25)
#define SPI_CMD_SE                         BIT(24)
#define SPI_CMD_BE                         BIT(23)
#define SPI_CMD_CE                         BIT(22)
#define SPI_CMD_DP                         BIT(21)
#define SPI_CMD_RES                        BIT(20)
#define SPI_CMD_HPM                        BIT(19)
#define SPI_CMD_USR                        BIT(18)

/* Details for CTRL0 register */

#define SPI_CTRL0_WR_BIT_ORDER             BIT(26)
#define SPI_CTRL0_RD_BIT_ORDER             BIT(25)
#define SPI_CTRL0_QIO_MODE                 BIT(24)
#define SPI_CTRL0_DIO_MODE                 BIT(23)
#define SPI_CTRL0_QOUT_MODE                BIT(20)
#define SPI_CTRL0_DOUT_MODE                BIT(14)
#define SPI_CTRL0_FASTRD_MODE              BIT(13)
#define SPI_CTRL0_CLOCK_EQU_SYS_CLOCK      BIT(12)
#define SPI_CTRL0_CLOCK_NUM_M              0x0000000F
#define SPI_CTRL0_CLOCK_NUM_S              8
#define SPI_CTRL0_CLOCK_HIGH_M             0x0000000F
#define SPI_CTRL0_CLOCK_HIGH_S             4
#define SPI_CTRL0_CLOCK_LOW_M              0x0000000F
#define SPI_CTRL0_CLOCK_LOW_S              0

/* Mask for the CLOCK_NUM/CLOCK_HIGH/CLOCK_LOW combined, in case one wants
 * to set them all as a single value.
 */
#define SPI_CTRL0_CLOCK_M                  0x00000FFF
#define SPI_CTRL0_CLOCK_S                  0

/* Details for CTRL2 register */

#define SPI_CTRL2_CS_DELAY_NUM_M           0x0000000F
#define SPI_CTRL2_CS_DELAY_NUM_S           28
#define SPI_CTRL2_CS_DELAY_MODE_M          0x00000003
#define SPI_CTRL2_CS_DELAY_MODE_S          26
#define SPI_CTRL2_MOSI_DELAY_NUM_M         0x00000007
#define SPI_CTRL2_MOSI_DELAY_NUM_S         23
#define SPI_CTRL2_MOSI_DELAY_MODE_M        0x00000003
#define SPI_CTRL2_MOSI_DELAY_MODE_S        21
#define SPI_CTRL2_MISO_DELAY_NUM_M         0x00000007
#define SPI_CTRL2_MISO_DELAY_NUM_S         18
#define SPI_CTRL2_MISO_DELAY_MODE_M        0x00000003
#define SPI_CTRL2_MISO_DELAY_MODE_S        16

/* Details for CLOCK register */

#define SPI_CLOCK_EQU_SYS_CLOCK            BIT(31)
#define SPI_CLOCK_DIV_PRE_M                0x00001FFF
#define SPI_CLOCK_DIV_PRE_S                18
#define SPI_CLOCK_COUNT_NUM_M              0x0000003F
#define SPI_CLOCK_COUNT_NUM_S              12
#define SPI_CLOCK_COUNT_HIGH_M             0x0000003F
#define SPI_CLOCK_COUNT_HIGH_S             6
#define SPI_CLOCK_COUNT_LOW_M              0x0000003F
#define SPI_CLOCK_COUNT_LOW_S              0

/* Mask for the COUNT_NUM/COUNT_HIGH/COUNT_LOW combined, in case one wants
 * to set them all as a single value.
 */
#define SPI_CTRL0_COUNT_M                  0x0003FFFF
#define SPI_CTRL0_COUNT_S                  0

/* Details for USER0 register */

#define SPI_USER0_COMMAND                  BIT(31)
#define SPI_USER0_ADDR                     BIT(30)
#define SPI_USER0_DUMMY                    BIT(29)
#define SPI_USER0_MISO                     BIT(28)
#define SPI_USER0_MOSI                     BIT(27)
#define SPI_USER0_MOSI_HIGHPART            BIT(25)
#define SPI_USER0_MISO_HIGHPART            BIT(24)
#define SPI_USER0_SIO                      BIT(16)
#define SPI_USER0_FWRITE_QIO               BIT(15)
#define SPI_USER0_FWRITE_DIO               BIT(14)
#define SPI_USER0_FWRITE_QUAD              BIT(13)
#define SPI_USER0_FWRITE_DUAL              BIT(12)
#define SPI_USER0_WR_BYTE_ORDER            BIT(11)
#define SPI_USER0_RD_BYTE_ORDER            BIT(10)
#define SPI_USER0_CLOCK_OUT_EDGE           BIT(7)
#define SPI_USER0_CLOCK_IN_EDGE            BIT(6)
#define SPI_USER0_CS_SETUP                 BIT(5)
#define SPI_USER0_CS_HOLD                  BIT(4)
#define SPI_USER0_FLASH_MODE               BIT(2)
#define SPI_USER0_DUPLEX                   BIT(0)

/* Details for USER1 register */

#define SPI_USER1_ADDR_BITLEN_M            0x0000003F
#define SPI_USER1_ADDR_BITLEN_S            26
#define SPI_USER1_MOSI_BITLEN_M            0x000001FF
#define SPI_USER1_MOSI_BITLEN_S            17
#define SPI_USER1_MISO_BITLEN_M            0x000001FF
#define SPI_USER1_MISO_BITLEN_S            8
#define SPI_USER1_DUMMY_CYCLELEN_M         0x000000FF
#define SPI_USER1_DUMMY_CYCLELEN_S         0

/* Details for USER2 register */

#define SPI_USER2_COMMAND_BITLEN_M         0x0000000F
#define SPI_USER2_COMMAND_BITLEN_S         28
#define SPI_USER2_COMMAND_VALUE_M          0x0000FFFF
#define SPI_USER2_COMMAND_VALUE_S          0

/* Details for PIN register */

#define SPI_PIN_IDLE_EDGE                  BIT(29)  ///< CPOL
#define SPI_PIN_CS2_DISABLE                BIT(2)
#define SPI_PIN_CS1_DISABLE                BIT(1)
#define SPI_PIN_CS0_DISABLE                BIT(0)

/* Details for SLAVE0 register */

#define SPI_SLAVE0_SYNC_RESET              BIT(31)
#define SPI_SLAVE0_MODE                    BIT(30)
#define SPI_SLAVE0_WR_RD_BUF_EN            BIT(29)
#define SPI_SLAVE0_WR_RD_STA_EN            BIT(28)
#define SPI_SLAVE0_CMD_DEFINE              BIT(27)
#define SPI_SLAVE0_TRANS_COUNT_M           0x0000000F
#define SPI_SLAVE0_TRANS_COUNT_S           23
#define SPI_SLAVE0_TRANS_DONE_EN           BIT(9)
#define SPI_SLAVE0_WR_STA_DONE_EN          BIT(8)
#define SPI_SLAVE0_RD_STA_DONE_EN          BIT(7)
#define SPI_SLAVE0_WR_BUF_DONE_EN          BIT(6)
#define SPI_SLAVE0_RD_BUF_DONE_EN          BIT(5)
#define SPI_SLAVE0_INT_EN_M                0x0000001f
#define SPI_SLAVE0_INT_EN_S                5
#define SPI_SLAVE0_TRANS_DONE              BIT(4)
#define SPI_SLAVE0_WR_STA_DONE             BIT(3)
#define SPI_SLAVE0_RD_STA_DONE             BIT(2)
#define SPI_SLAVE0_WR_BUF_DONE             BIT(1)
#define SPI_SLAVE0_RD_BUF_DONE             BIT(0)

/* Details for SLAVE1 register */

#define SPI_SLAVE1_STATUS_BITLEN_M         0x0000001F
#define SPI_SLAVE1_STATUS_BITLEN_S         27
#define SPI_SLAVE1_BUF_BITLEN_M            0x000001FF
#define SPI_SLAVE1_BUF_BITLEN_S            16
#define SPI_SLAVE1_RD_ADDR_BITLEN_M        0x0000003F
#define SPI_SLAVE1_RD_ADDR_BITLEN_S        10
#define SPI_SLAVE1_WR_ADDR_BITLEN_M        0x0000003F
#define SPI_SLAVE1_WR_ADDR_BITLEN_S        4
#define SPI_SLAVE1_WRSTA_DUMMY_ENABLE      BIT(3)
#define SPI_SLAVE1_RDSTA_DUMMY_ENABLE      BIT(2)
#define SPI_SLAVE1_WRBUF_DUMMY_ENABLE      BIT(1)
#define SPI_SLAVE1_RDBUF_DUMMY_ENABLE      BIT(0)

/* Details for SLAVE2 register */

#define SPI_SLAVE2_WRBUF_DUMMY_CYCLELEN_M  0x000000FF
#define SPI_SLAVE2_WRBUF_DUMMY_CYCLELEN_S  24
#define SPI_SLAVE2_RDBUF_DUMMY_CYCLELEN_M  0x000000FF
#define SPI_SLAVE2_RDBUF_DUMMY_CYCLELEN_S  16
#define SPI_SLAVE2_WRSTR_DUMMY_CYCLELEN_M  0x000000FF
#define SPI_SLAVE2_WRSTR_DUMMY_CYCLELEN_S  8
#define SPI_SLAVE2_RDSTR_DUMMY_CYCLELEN_M  0x000000FF
#define SPI_SLAVE2_RDSTR_DUMMY_CYCLELEN_S  0

/* Details for SLAVE3 register */

#define SPI_SLAVE3_WRSTA_CMD_VALUE_M       0x000000FF
#define SPI_SLAVE3_WRSTA_CMD_VALUE_S       24
#define SPI_SLAVE3_RDSTA_CMD_VALUE_M       0x000000FF
#define SPI_SLAVE3_RDSTA_CMD_VALUE_S       16
#define SPI_SLAVE3_WRBUF_CMD_VALUE_M       0x000000FF
#define SPI_SLAVE3_WRBUF_CMD_VALUE_S       8
#define SPI_SLAVE3_RDBUF_CMD_VALUE_M       0x000000FF
#define SPI_SLAVE3_RDBUF_CMD_VALUE_S       0

/* Details for EXT3 register */

#define SPI_EXT3_INT_HOLD_ENABLE_M         0x00000003
#define SPI_EXT3_INT_HOLD_ENABLE_S         0

/* Memory layout for DMA transfer descriptors. */
struct SLCDescriptor {
	uint32_t flags;
	uint32_t buf_ptr;
	uint32_t next_link_ptr;
};

#define SLC_DESCRIPTOR_FLAGS_BLOCKSIZE_M		0x00000fff
#define SLC_DESCRIPTOR_FLAGS_BLOCKSIZE_S		0
#define SLC_DESCRIPTOR_FLAGS_DATA_LENGTH_M		0x00000fff
#define SLC_DESCRIPTOR_FLAGS_DATA_LENGTH_S		12
#define SLC_DESCRIPTOR_FLAGS_SUB_SOF			BIT(29)
#define SLC_DESCRIPTOR_FLAGS_EOF				BIT(30)
#define SLC_DESCRIPTOR_FLAGS_OWNER				BIT(31)

#define SLC_DESCRIPTOR_FLAGS(blocksize,datalen,sub_sof,eof,owner) ( \
	VAL2FIELD_M(SLC_DESCRIPTOR_FLAGS_BLOCKSIZE,blocksize)| \
	VAL2FIELD_M(SLC_DESCRIPTOR_FLAGS_DATA_LENGTH,datalen)| \
	((sub_sof)?SLC_DESCRIPTOR_FLAGS_SUB_SOF:0)| \
	((eof)?SLC_DESCRIPTOR_FLAGS_EOF:0)| \
	((owner)?SLC_DESCRIPTOR_FLAGS_OWNER:0) \
)


#endif /* __ESP8266_SLC_H */

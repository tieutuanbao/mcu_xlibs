#ifndef __MAIN_H
#define __MAIN_H

#include "port_macro.h"
#include "color.h"

#if ((SPI_FLASH_SIZE_MAP == 0) || (SPI_FLASH_SIZE_MAP == 1))
    #error "The flash map is not supported"
#elif (SPI_FLASH_SIZE_MAP == 2)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000
#define SYSTEM_PARTITION_OTA_2_ADDR							0x81000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0xfb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0xfc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0xfd000
#elif (SPI_FLASH_SIZE_MAP == 3)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000
#define SYSTEM_PARTITION_OTA_2_ADDR							0x81000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0x1fb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0x1fc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0x1fd000
#elif (SPI_FLASH_SIZE_MAP == 4)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000
#define SYSTEM_PARTITION_OTA_2_ADDR							0x81000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0x3fb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0x3fc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0x3fd000
#elif (SPI_FLASH_SIZE_MAP == 5)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000
#define SYSTEM_PARTITION_OTA_2_ADDR							0x101000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0x1fb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0x1fc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0x1fd000
#elif (SPI_FLASH_SIZE_MAP == 6)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000
#define SYSTEM_PARTITION_OTA_2_ADDR							0x101000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0x3fb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0x3fc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0x3fd000
#else
#error "The flash map is not supported"
#endif


/* ------------ Define 1903 ------------ */
#define GPIO_1903_PORT_SET    (&GPOS)
#define GPIO_1903_PORT_CLR    (&GPOC)

#define GPIO_1903_DI_CH0        12
#define GPIO_1903_DI_CH1        13
#define GPIO_1903_DI_CH2        14
#define GPIO_1903_DI_CH3        15

#define GPIO1903_DI_CH0_BIT_MASK        (1ULL << GPIO_1903_DI_CH0)
#define GPIO1903_DI_CH1_BIT_MASK        (1ULL << GPIO_1903_DI_CH1)
#define GPIO1903_DI_CH2_BIT_MASK        (1ULL << GPIO_1903_DI_CH2)
#define GPIO1903_DI_CH3_BIT_MASK        (1ULL << GPIO_1903_DI_CH3)

#define USC_ALL_MASK    (GPIO1903_DI_CH0_BIT_MASK|GPIO1903_DI_CH1_BIT_MASK|GPIO1903_DI_CH2_BIT_MASK|GPIO1903_DI_CH3_BIT_MASK)

/* Define số cổng - chạy song song */
#define MAX_CHIP_PARA        4
/* Define số lượng chip nối tiếp mỗi cổng */
#define MAX_CHIP_SERI        256

extern rgb_color_t *color_buf;
static uint8_t *color_buf_p;

#endif
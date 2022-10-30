/*!
 * @file        apm32f00x_spi.h
 *
 * @brief       This file contains all functions prototype,enumeration and macros for the SPI peripheral
 *
 * @version     V1.0.1
 *
 * @date        2022-04-11
 *
 * @attention
 *
 *  Copyright (C) 2018-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __APM32F00X_SPI_H
#define __APM32F00X_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup SPI_Driver SPI Driver
  @{
*/

/** @addtogroup SPI_Enumerations Enumerations
  @{
*/

/**
 * @brief   SPI data direction mode
 */
typedef enum
{
    SPI_DIRECTION_2LINES_FULLDUPLEX     = ((uint8_t)0x00),  //!< Full duplex mode,in 2-line unidirectional data mode
    SPI_DIRECTION_2LINES_RXONLY         = ((uint8_t)0x04),  //!< Receiver only, in 2-line unidirectional data mode
    SPI_DIRECTION_1LINE_RX              = ((uint8_t)0x80),  //!< Receiver mode, in 1 line bidirectional data mode
    SPI_DIRECTION_1LINE_TX              = ((uint8_t)0xC0),  //!< Transmit mode, in 1 line bidirectional data mode
} SPI_DIRECTION_T;

/**
 * @brief   Software slave control
 */
typedef enum
{
    SPI_SSC_DISABLE     = ((uint8_t)0),     //!< Disable software select slave
    SPI_SSC_ENABLE      = ((uint8_t)1),     //!< Enable software select slave
} SPI_SSC_T;

typedef enum
{
    SPI_MODE_SLAVE      = ((uint8_t)0),     //!< Slave mode
    SPI_MODE_MASTER     = ((uint8_t)1),     //!< Master mode

} SPI_MODE_T;

/**
 * @brief   SPI BaudRate divider
 */
typedef enum
{
    SPI_BAUDRATE_DIV_2      = ((uint8_t)0),
    SPI_BAUDRATE_DIV_4      = ((uint8_t)1),
    SPI_BAUDRATE_DIV_8      = ((uint8_t)2),
    SPI_BAUDRATE_DIV_16     = ((uint8_t)3),
    SPI_BAUDRATE_DIV_32     = ((uint8_t)4),
    SPI_BAUDRATE_DIV_64     = ((uint8_t)5),
    SPI_BAUDRATE_DIV_128    = ((uint8_t)6),
    SPI_BAUDRATE_DIV_256    = ((uint8_t)7),
} SPI_BAUDRATE_DIV_T;

/**
 * @brief   SPI Clock Polarity
 */
typedef enum
{
    SPI_CLKPOL_LOW          = ((uint8_t)0),
    SPI_CLKPOL_HIGH         = ((uint8_t)1),
} SPI_CLKPOL_T;

/**
 * @brief   SPI Clock Phase
 */
typedef enum
{
    SPI_CLKPHA_1EDGE        = ((uint8_t)0),
    SPI_CLKPHA_2EDGE        = ((uint8_t)1),
} SPI_CLKPHA_T;

/**
 * @brief   MSB or LSB is transmitted first
 */
typedef enum
{
    SPI_FIRST_BIT_MSB       = ((uint8_t)0),
    SPI_FIRST_BIT_LSB       = ((uint8_t)1),
} SPI_FIRST_BIT_T;

/**
 * @brief   SPI flags definition
 */
typedef enum
{
    SPI_FLAG_RXBNE      = ((uint8_t)0x01),  //!< Receive buffer not empty flag
    SPI_FLAG_TXBE       = ((uint8_t)0x02),  //!< Transmit buffer empty flag
    SPI_FLAG_WAKEUP     = ((uint8_t)0x08),  //!< Wakeup flag
    SPI_FLAG_CRCE       = ((uint8_t)0x10),  //!< CRC error flag
    SPI_FLAG_MME        = ((uint8_t)0x20),  //!< Master mode error flag
    SPI_FLAG_RXO        = ((uint8_t)0x40),  //!< Receive Overrun flag
    SPI_FLAG_BUSY       = ((uint8_t)0x80),  //!< Busy flag
} SPI_FLAG_T;

/**
 * @brief   SPI interrupt source
 */
typedef enum
{
    SPI_INT_NONE        = ((uint8_t)0x00),  //!< No interrupt
    SPI_INT_WAKEUP      = ((uint8_t)0x10),  //!< Wakeup interrupt
    SPI_INT_ERROR       = ((uint8_t)0x20),  //!< Error interrupt
    SPI_INT_RXBNE       = ((uint8_t)0x40),  //!< Receive buffer not empty interrupt
    SPI_INT_TXE         = ((uint8_t)0x80),  //!< Transmit buffer empty interrupt
} SPI_INT_T;

/**
 * @brief   SPI interrupt flag
 */
typedef enum
{
    SPI_INT_FLAG_RXBNE      = ((uint16_t)0x4001),  //!< Receive buffer not empty flag
    SPI_INT_FLAG_TXBE       = ((uint16_t)0x8002),  //!< Transmit buffer empty flag
    SPI_INT_FLAG_WAKEUP     = ((uint16_t)0x1008),  //!< Wakeup flag
    SPI_INT_FLAG_CRCE       = ((uint16_t)0x2010),  //!< CRC error flag
    SPI_INT_FLAG_MME        = ((uint16_t)0x2020),  //!< Master mode error flag
    SPI_INT_FLAG_RXO        = ((uint16_t)0x2040),  //!< Receive Overrun flag
} SPI_INT_FLAG_T;

/**@} end of group SPI_Enumerations*/

/** @addtogroup SPI_Structure Data Structure
  @{
*/

/**
 * @brief   SPI Config struct definition
 */
typedef struct
{
    SPI_MODE_T mode;                    //!< Specifies the SPI mode
    SPI_CLKPHA_T phase;                 //!< Specifies the Clock phase
    uint8_t interrupt;                  //!< Interrupt source.Can be combination of the values @ref SPI_INT_T
    SPI_CLKPOL_T polarity;              //!< Specifies the Clock polarity
    SPI_SSC_T slaveSelect;              //!< Specifies the slave select mode.
    SPI_FIRST_BIT_T firstBit;           //!< Specifies the Frame format
    SPI_DIRECTION_T direction;          //!< Specifies the data direction mode
    SPI_BAUDRATE_DIV_T baudrateDiv;     //!< Specifies the baud rate divider
} SPI_Config_T;

/**@} end of group SPI_Structure*/

/** @addtogroup SPI_Macros Macros
  @{
*/

/** Control Register 1 reset value */
#define SPI_CTRL1_RESET_VALUE       ((uint32_t)0x00)
/** Control Register 2 reset value */
#define SPI_CTRL2_RESET_VALUE       ((uint32_t)0x00)
/** Interrupt Control Register reset value */
#define SPI_INTCTRL_RESET_VALUE     ((uint32_t)0x00)
/** Status Register reset value */
#define SPI_STS_RESET_VALUE         ((uint32_t)0x02)
/**Data Register reset value  */
#define SPI_DATA_RESET_VALUE        ((uint32_t)0x00)
/** CRC Polynomial Register reset value */
#define SPI_CRCPOLY_RESET_VALUE     ((uint32_t)0x07)
/** RX CRC Register reset value */
#define SPI_RXCRC_RESET_VALUE       ((uint32_t)0x00)
/** TX CRC Register reset value */
#define SPI_TXCRC_RESET_VALUE       ((uint32_t)0x00)

/**@} end of group SPI_Macros*/

/** @addtogroup SPI_Fuctions Fuctions
  @{
*/

/** Reset and configuration */
void SPI_Reset(void);
void SPI_Config(SPI_Config_T *spiConfig);
void SPI_ConfigStructInit(SPI_Config_T *spiConfig);
void SPI_Enable(void);
void SPI_Disable(void);
void SPI_ConfigMode(SPI_MODE_T mode);

/** interrupt */
void SPI_EnableInterrupt(uint8_t interrupt);
void SPI_DisableInterrupt(uint8_t interrupt);
uint8_t SPI_ReadIntFlag(SPI_INT_FLAG_T flag);
void SPI_ClearIntFlag(SPI_INT_FLAG_T flag);

/** Transmits and received */
void SPI_TxData(uint8_t data);
uint8_t SPI_RxData(void);

/** Slave software control */
void SPI_EnableSlaveSoftwareControl(void);
void SPI_DisableSlaveSoftwareControl(void);

/** CRC */
void SPI_TxCRC(void);
void SPI_EnableCRC(void);
void SPI_DisableCRC(void);
uint8_t SPI_ReadRxCRC(void);
uint8_t SPI_ReadTxCRC(void);
void SPI_SetCRCPolynomial(uint8_t polynomial);
uint8_t SPI_ReadCRCPolynomial(void);

/** Flag */
uint8_t SPI_ReadStatusFlag(uint8_t flag);
void SPI_ClearStatusFlag(uint8_t flag);

/**@} end of group SPI_Fuctions*/
/**@} end of group SPI_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_SPI_H */

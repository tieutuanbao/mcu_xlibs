/*!
 * @file        apm32f00x_usart.h
 *
 * @brief       This file contains all functions prototypes,enumeration and macros for the USART peripheral
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

#ifndef __APM32F00X_USART_H
#define __APM32F00X_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup USART_Driver  USART Driver
  @{
*/

/** @addtogroup  USART_Enumerations Enumerations
  @{
*/

/**
 * @brief   USART Word Length definition
 */
typedef enum
{
    USART_WORD_LEN_8B       = ((uint8_t)0),
    USART_WORD_LEN_9B       = ((uint8_t)BIT4)
} USART_WORD_LEN_T;

/**
 * @brief   USART Stop bits definition
 */
typedef enum
{
    USART_STOP_BIT_1    = ((uint8_t)0),             //!<   One stop bit
    USART_STOP_BIT_2    = ((uint8_t)BIT5),          //!<   Two stop bits
    USART_STOP_BIT_1_5  = ((uint8_t)(BIT4 | BIT5))  //!<   One and half stop bits
} USART_STOP_BITS_T;

/**
 * @brief    USART Parity definition
 */
typedef enum
{
    USART_PARITY_NONE       = ((uint8_t)0),
    USART_PARITY_EVEN       = ((uint8_t)BIT2),
    USART_PARITY_ODD        = ((uint8_t)BIT2 | BIT1)
} USART_PARITY_T;

/**
 * @brief    USART mode definition
 */
typedef enum
{
    USART_MODE_RX           = ((uint8_t)BIT2),
    USART_MODE_TX           = ((uint8_t)BIT3),
    USART_MODE_TX_RX        = ((uint8_t)BIT2 | BIT3)
} USART_MODE_T;

/**
 * @brief    USART synchronization clock enable/disable
 */
typedef enum
{
    USART_CLKEN_DISABLE     = ((uint8_t)0),
    USART_CLKEN_ENABLE      = ((uint8_t)1)
} USART_CLKEN_T;

/**
 * @brief    USART Clock polarity define
 */
typedef enum
{
    USART_CLKPOL_LOW        = ((uint8_t)0),
    USART_CLKPOL_HIGH       = ((uint8_t)1)
} USART_CLKPOL_T;

/**
 * @brief    USART Clock phase define
 */
typedef enum
{
    USART_CLKPHA_1EDGE      = ((uint8_t)0),
    USART_CLKPHA_2EDGE      = ((uint8_t)1)
} USART_CLKPHA_T;

/**
 * @brief    USART Last bit clock pulse enable
 */
typedef enum
{
    USART_LBCP_DISABLE      = ((uint8_t)0),
    USART_LBCP_ENABLE       = ((uint8_t)1),
} USART_LBCP_T;

/**
 * @brief    USART Wakeup method
 */
typedef enum
{
    USART_WAKEUP_IDLE_LINE      = ((uint8_t)0),
    USART_WAKEUP_ADDRESS_MARK   = ((uint8_t)1)
} USART_WAKEUP_T;

/**
 * @brief    USART LIN break detection length
 */
typedef enum
{
    USART_LBDL_10B          = ((uint8_t)0),
    USART_LBDL_11B          = ((uint8_t)1)
} USART_LBDL_T;

/**
 * @brief    USART IrDA low-power
 */
typedef enum
{
    USART_IRDA_LP_NORMAL    = ((uint8_t)0),
    USART_IRDA_LP_LOWPOWER  = ((uint8_t)1)
} USART_IRDA_LP_T;

/**
 * @brief    USART Interrupt Source
 */
typedef enum
{
    USART_INT_NONE      = ((uint32_t)0x000000),
    USART_INT_PE        = ((uint32_t)0x000001),
    USART_INT_TX        = ((uint32_t)0x008000),
    USART_INT_TXC       = ((uint32_t)0x004000),
    USART_INT_RX        = ((uint32_t)0x002000),
    USART_INT_IDLE      = ((uint32_t)0x001000),
    USART_INT_LBD       = ((uint32_t)0x400000),
} USART_INT_T;

/**
 * @brief   USART Interrupt flag definition
 */
typedef enum
{
    USART_INT_FLAG_PE       = ((uint32_t)0X010101),
    USART_INT_FLAG_IDLE     = ((uint32_t)0X100210),
    USART_INT_FLAG_RX       = ((uint32_t)0X200220),
    USART_INT_FLAG_TXC      = ((uint32_t)0X400240),
    USART_INT_FLAG_TX       = ((uint32_t)0X800280),
    USART_INT_FLAG_LBD      = ((uint32_t)0X400410),
} USART_INT_FLAG_T;

/**
 * @brief    USART flag definition
 */
typedef enum
{
    USART_FLAG_TXBE         = ((uint16_t)0X0080),
    USART_FLAG_TXC          = ((uint16_t)0X0040),
    USART_FLAG_RXBNE        = ((uint16_t)0X0020),
    USART_FLAG_IDLEE        = ((uint16_t)0X0010),
    USART_FLAG_OVREE        = ((uint16_t)0X0008),
    USART_FLAG_NE           = ((uint16_t)0X0004),
    USART_FLAG_FE           = ((uint16_t)0X0002),
    USART_FLAG_PE           = ((uint16_t)0X0001),
    USART_FLAG_LBD          = ((uint16_t)0X1000),
} USART_FLAG_T;

/**@} end of group USART_Enumerations*/

/** @addtogroup USART_Macros Macros
  @{
*/

/** status register reset value */
#define USART_STS_RESET_VALUE               ((uint32_t)0xC0)
/** Baud rate register0 reset value */
#define USART_BR0_RESET_VALUE               ((uint32_t)0x00)
/** Baud rate register1 reset value */
#define USART_BR1_RESET_VALUE               ((uint32_t)0x00)
/** Control register1 reset value */
#define USART_CTRL1_RESET_VALUE             ((uint32_t)0x00)
/** Control register2 reset value */
#define USART_CTRL2_RESET_VALUE             ((uint32_t)0x00)
/** Control register3 reset value */
#define USART_CTRL3_RESET_VALUE             ((uint32_t)0x00)
/** Control register4 reset value */
#define USART_CTRL4_RESET_VALUE             ((uint32_t)0x00)
/** Control register5 reset value */
#define USART_CTRL5_RESET_VALUE             ((uint32_t)0x00)
/** Guard time register reset value */
#define USART_GT_RESET_VALUE                ((uint32_t)0x00)
/** divider number register reset value */
#define USART_DIV_RESET_VALUE               ((uint32_t)0x00)

/**@} end of group USART_Macros*/

/** @addtogroup USART_Structure Data Structure
  @{
*/

/**
 * @brief    USART Config struct definition
 */
typedef struct
{
    uint32_t baudRate;              //!< Specifies the baud rate
    USART_MODE_T mode;              //!< Specifies the mode
    uint32_t interrupt;             //!< Interrupt source.Can be combination of the values @ref USART_INT_T
    USART_PARITY_T parity;          //!< Specifies the parity
    USART_STOP_BITS_T stopBits;     //!< Specifies the stop bits
    USART_WORD_LEN_T wordLength;
} USART_Config_T;

/**
 * @brief   USART synchronous communication clock config struct definition
 */
typedef struct
{
    USART_CLKEN_T enable;           //!< Enable or Disable Clock
    USART_CLKPOL_T polarity;        //!< Specifies the clock polarity
    USART_CLKPHA_T phase;           //!< Specifies the clock phase
    USART_LBCP_T lastBitClock;      //!< Enable or Disable last bit clock
} USART_SyncClockConfig_T;

/**@} end of group USART_Structure*/

/** @addtogroup USART_Fuctions Fuctions
  @{
*/

/** USART peripheral Reset and Configuration */
void USART_Reset(USART_T *usart);
void USART_Config(USART_T* usart, USART_Config_T *usartConfig);
void USART_ConfigStructInit(USART_Config_T* usartConfig);
void USART_Enable(USART_T* usart);
void USART_Disable(USART_T* usart);

/** Interrupt */
void USART_DisableInterrupt(USART_T *usart, uint32_t interrupt);
void USART_EnableInterrupt(USART_T *usart, uint32_t interrupt);
uint8_t USART_ReadIntFlag(USART_T* usart, USART_INT_FLAG_T flag);
void USART_ClearIntFlag(USART_T* usart, USART_INT_FLAG_T flag);

/** Half Duplex */
void USART_EnableHalfDuplex(USART_T* usart);
void USART_DisableHalfDuplex(USART_T* usart);

/** IRDA */
void USART_ConfigIrDA(USART_T* usart, USART_IRDA_LP_T IrDAMode);
void USART_EnableIrDA(USART_T* usart);
void USART_DisableIrDA(USART_T* usart);

/** LIN */
void USART_ConfigLINBreakDetectLength(USART_T* usart, USART_LBDL_T lbdl);
void USART_EnableLIN(USART_T* usart);
void USART_DisableLIN(USART_T* usart);
void USART_TxBreak(USART_T* usart);

/** Smart card */
void USART_EnableSmartCard(USART_T* usart);
void USART_DisableSmartCard(USART_T* usart);
void USART_EnableSmartCardNACK(USART_T* usart);
void USART_DisableSmartCardNACK(USART_T* usart);
void USART_ConfigGuardTime(USART_T* usart, uint8_t guardTime);
void USART_ConfigDivNumber(USART_T* usart, uint8_t div);

/** Multi-processor communication */
void USART_EnableMuteMode(USART_T* usart);
void USART_DisableMuteMode(USART_T* usart);
void USART_ConfigMuteModeWakeUp(USART_T* usart, USART_WAKEUP_T wakeup);
void USART_Address(USART_T* usart, uint8_t address);

/** Transmit and receive*/
uint8_t USART_RxData8(USART_T* usart);
uint16_t USART_RxData9(USART_T* usart);
void USART_TxData8(USART_T* usart, uint8_t data);
void USART_TxData9(USART_T* usart, uint16_t data);

/** Flag */
uint8_t USART_ReadStatusFlag(USART_T* usart, uint16_t flag);
void USART_ClearStatusFlag(USART_T* usart, uint16_t flag);

/** synchronous communication */
void USART_ConfigSyncClock(USART_T* usart, USART_SyncClockConfig_T *SyncClockConfig);
void USART_ConfigSyncClockStructInit(USART_SyncClockConfig_T *SyncClockConfig);

/**@} end of group USART_Fuctions*/
/**@} end of group USART_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_USART_H */

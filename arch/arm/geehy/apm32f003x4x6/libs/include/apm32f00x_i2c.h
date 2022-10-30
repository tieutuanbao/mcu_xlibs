/*!
 * @file        apm32f00x_i2c.h
 *
 * @brief       This file contains all functions prototype,enumeration and macros for the I2C peripheral
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

#ifndef __APM32F00X_I2C_H
#define __APM32F00X_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup I2C_Driver I2C Driver
  @{
*/

/** @addtogroup I2C_Enumerations Enumerations
  @{
*/

/**
 * @brief   I2C duty cycle (fast mode only)
 */
typedef enum
{
    I2C_DUTYCYCLE_2         = ((uint8_t)0x00),
    I2C_DUTYCYCLE_16_9      = ((uint8_t)0x01)
} I2C_DUTY_CYCLE_T;

/**
 * @brief   I2C Acknowledgement configuration
 */
typedef enum
{
    I2C_ACK_NONE        = ((uint8_t)0X00),      //!<   No acknowledge
    I2C_ACK_CURRENT     = ((uint8_t)0X10),      //!<   Acknowledge on the current byte
    I2C_ACK_NEXT        = ((uint8_t)0X11)       //!<   Acknowledge on the next byte
} I2C_ACK_T;

/**
 * @brief   Address mode
 */
typedef enum
{
    I2C_ADDR_7_BIT      = ((uint8_t)0x00),      //!<   7-bit slave address
    I2C_ADDR_10_BIT     = ((uint8_t)0x01),      //!<   10-bit slave address
} I2C_ADDR_T;

/**
 * @brief   I2C Interrupt source
 */
typedef enum
{
    I2C_INT_NONE        = ((uint8_t)0X00),      //!<   No interruption
    I2C_INT_ERROR       = ((uint8_t)0X01),      //!<   Error interruption
    I2C_INT_EVENT       = ((uint8_t)0X02),      //!<   Event interruption
    I2C_INT_BUFFER      = ((uint8_t)0X04)       //!<   Buffer interruption
} I2C_INT_T;

/**
 * @brief   I2C Interrupt flag
 */
typedef enum
{
    /** Buffer Interruption */
    I2C_INT_FLAG_TXBE           = 0x40180,
    I2C_INT_FLAG_RXBNE          = 0x40140,

    /** Event Interruption */
    I2C_INT_FLAG_STOP           = 0x20110,
    I2C_INT_FLAG_ADDR10         = 0x20108,
    I2C_INT_FLAG_BTC            = 0x20104,
    I2C_INT_FLAG_ADDR           = 0x20102,
    I2C_INT_FLAG_START          = 0x20101,
    I2C_INT_FLAG_WAKEUP         = 0x20220,

    /** Error Interruption */
    I2C_INT_FLAG_OUF            = 0x10208,
    I2C_INT_FLAG_ACKERR         = 0x10204,
    I2C_INT_FLAG_ARBLOST        = 0x10202,
    I2C_INT_FLAG_BUSERR         = 0x10201,
} I2C_INT_FLAG_T;


/**
 * @brief   I2C transfer direction
 */
typedef enum
{
    I2C_DIRECTION_TX        = ((uint8_t)0x00),     //!<    Transmission direction
    I2C_DIRECTION_RX        = ((uint8_t)0x01)      //!<    Reception direction
} I2C_DIRECTION_T;

/**
 * @brief   I2C Flags
 */
typedef enum
{
    /** STS1 register flag */
    I2C_FLAG_TXBE           = ((uint32_t)0x0080),       //!<    Transmit Buffer Data Register Empty flag
    I2C_FLAG_RXBNE          = ((uint32_t)0x0040),       //!<    Read Buffer Data Register Not Empty flag
    I2C_FLAG_STOP           = ((uint32_t)0x0010),       //!<    Stop detected flag
    I2C_FLAG_ADDR10         = ((uint32_t)0x0008),       //!<    10-bit Header sent flag
    I2C_FLAG_BTC            = ((uint32_t)0x0004),       //!<    Data Byte Transfer complete flag
    I2C_FLAG_ADDR           = ((uint32_t)0x0002),       //!<    Address Sent/Matched (master/slave) flag
    I2C_FLAG_START          = ((uint32_t)0x0001),       //!<    Start bit sent flag

    /** STS2 register flag */
    I2C_FLAG_WAKEUP         = ((uint32_t)0x2000),       //!<    Wake Up From Halt Flag
    I2C_FLAG_OUF            = ((uint32_t)0x0800),       //!<    Overrun/Underrun Flag
    I2C_FLAG_ACKERR         = ((uint32_t)0x0400),       //!<    Acknowledge Error Flag
    I2C_FLAG_ARBLOST        = ((uint32_t)0x0200),       //!<    Arbitration Loss Flag
    I2C_FLAG_BUSERR         = ((uint32_t)0x0100),       //!<    Bus Error Flag

    /** STS3 register flag */
    I2C_FLAG_BROADCAST      = ((uint32_t)0x100000),     //!<    Broadcast header received Flag
    I2C_FLAG_RWMF           = ((uint32_t)0x040000),     //!<    Transmitter/Receiver data flag
    I2C_FLAG_BUSBUSY        = ((uint32_t)0x020000),     //!<    Bus Busy Flag
    I2C_FLAG_MMF            = ((uint32_t)0x010000),     //!<    Master/Slave mode flag
} I2C_FLAG_T;

/**@} end of group I2C_Enumerations*/

/** @addtogroup I2C_Structure Data Structure
  @{
*/

/**
 * @brief   I2C Config struct definition
 */
typedef struct
{
    I2C_ACK_T ack;                      //!<    Specifies the acknowledge mode to apply
    uint16_t addr;                      //!<    Specifies the slave address
    uint8_t interrupt;                  //!<    Interrupt source.Can be combination of the values @ref I2C_INT_T
    I2C_ADDR_T addrMode;                //!<    Specifies the Addressing mode
    uint8_t inputClkFreqMhz;            //!<    Specifies the output clock frequency in MHz
    uint32_t outputClkFreqHz;           //!<    Specifies the input clock frequency in Hz
    I2C_DUTY_CYCLE_T dutyCycle;         //!<    Specifies the duty cycle to apply in fast mode
} I2C_Config_T;

/**@} end of group I2C_Structure*/

/** @addtogroup I2C_Macros Macros
  @{
*/

/** I2C maximum frequency in standard mode */
#define I2C_STANDARD_MODE_MAX_FREQ      ((uint32_t)100000)
/** I2C maximum frequency in fast mode */
#define I2C_FAST_MODE_MAX_FREQ          ((uint32_t)400000)
/** I2C maximum clock frequency(MHZ) */
#define I2C_INPUT_MAX_FREQ              ((uint8_t)48)

/** CTRL1 register reset value */
#define I2C_CTRL1_RESET_VALUE           ((uint32_t)0x00)
/** CTRL2 register reset value */
#define I2C_CTRL2_RESET_VALUE           ((uint32_t)0x00)
/** CLKFREQ register reset value */
#define I2C_CLKFREQ_RESET_VALUE         ((uint32_t)0x00)
/** ADDR0 register reset value */
#define I2C_ADDR0_RESET_VALUE           ((uint32_t)0x00)
/** ADDR1 register reset value */
#define I2C_ADDR1_RESET_VALUE           ((uint32_t)0x00)
/** DATA register reset value */
#define I2C_DATA_RESET_VALUE            ((uint32_t)0x00)
/** STS1 register reset value */
#define I2C_STS1_RESET_VALUE            ((uint32_t)0x00)
/** STS2 register reset value */
#define I2C_STS2_RESET_VALUE            ((uint32_t)0x00)
/** STS3 register reset value */
#define I2C_STS3_RESET_VALUE            ((uint32_t)0x00)
/** INT register reset value */
#define I2C_INTCTRL_RESET_VALUE         ((uint32_t)0x00)
/** CLKCTRL1 register reset value */
#define I2C_CLKCTRL1_RESET_VALUE        ((uint32_t)0x00)
/** CLKCTRL2 register reset value */
#define I2C_CLKCTRL2_RESET_VALUE        ((uint32_t)0x00)
/** MRT register reset value */
#define I2C_MRT_RESET_VALUE             ((uint32_t)0x02)

/**@} end of group I2C_Macros*/

/** @addtogroup I2C_Fuctions Fuctions
  @{
*/

/** I2C peripheral Reset and Configuration*/
void I2C_Reset(void);
void I2C_Config(I2C_Config_T *i2cConfig);
void I2C_ConfigStructInit(I2C_Config_T *i2cConfig);
void I2C_Enable(void);
void I2C_Disable(void);

/** Broadcast */
void I2C_DisableBroadcastCall(void);
void I2C_EnableBroadcastCall(void);

/** Generate Start/Stop */
void I2C_EnableGenerateStart(void);
void I2C_DisableGenerateStart(void);
void I2C_EnableGenerateStop(void);
void I2C_DisableGenerateStop(void);

/** Software Reset */
void I2C_EnableSoftwareReset(void);
void I2C_DisableSoftwareReset(void);

/** Clock Stretch */
void I2C_EnableStretchClock(void);
void I2C_DisableStretchClock(void);

/** Interrupt */
void I2C_EnableInterrupt(uint8_t interrupt);
void I2C_DisableInterrupt(uint8_t interrupt);
uint8_t I2C_ReadIntFlag(I2C_INT_FLAG_T flag);
void I2C_ClearIntFlag(I2C_INT_FLAG_T flag);

/** Acknowledge */
void I2C_ConfigAcknowledge(I2C_ACK_T ack);

/** Duty Cycle */
void I2C_ConfigDutyCycle(I2C_DUTY_CYCLE_T dutyCycle);

/** Transmit and receive*/
uint8_t I2C_RxData(void);
void I2C_TxAddress7Bit(uint8_t address, I2C_DIRECTION_T direction);
void I2C_TxData(uint8_t data);

/** flag */
uint8_t I2C_ReadStatusFlag(uint32_t flag);
void I2C_ClearStatusFlag(uint32_t flag);

/**@} end of group I2C_Fuctions*/
/**@} end of group I2C_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_I2C_H */

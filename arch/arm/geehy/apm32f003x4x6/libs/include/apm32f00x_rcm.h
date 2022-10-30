/*!
 * @file        apm32f00x_rcm.h
 *
 * @brief       This file contains all the functions prototypes,enumeration and macro for the RCM firmware library
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

#ifndef __APM32F00X_RCM_H
#define __APM32F00X_RCM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup RCM_Driver RCM Driver
  @{
*/

/** @addtogroup RCM_Enumerations Enumerations
  @{
*/

/**
 * @brief   Definition clock switching mode
 */
typedef enum
{
    RCM_SWITCH_MODE_MANUAL      = (uint8_t)0X00,    //!<   Enable the manual clock switching mode
    RCM_SWITCH_MODE_AUTO        = (uint8_t)0x01     //!<   Enable the automatic clock switching mode
} RCM_SWITCH_MODE_T;

/**
   * @brief Master Clock Source
   */
typedef enum
{
    RCM_MCLKSRC_HIRC            = (uint8_t)0xE1,    //!<   Clock Source HIRC
    RCM_MCLKSRC_LIRC            = (uint8_t)0xD2,    //!<   Clock Source LIRC
    RCM_MCLKSRC_HXT             = (uint8_t)0xB4     //!<   Clock Source HXT
} RCM_MCLKSRC_T;

/**
   * @brief     Clock Output clock source
   */
typedef enum
{
    RCM_COCCLK_HIRCDIV          = (uint8_t)0x00,     //!<    Clock Output HIRC divider
    RCM_COCCLK_LIRC             = (uint8_t)0x01,     //!<    Clock Output LIRC
    RCM_COCCLK_HXT              = (uint8_t)0x02,     //!<    Clock Output HXT
    RCM_COCCLK_CPU              = (uint8_t)0x04,     //!<    Clock Output CPU
    RCM_COCCLK_CPUDIV2          = (uint8_t)0x05,     //!<    Clock Output CPU/2
    RCM_COCCLK_CPUDIV4          = (uint8_t)0x06,     //!<    Clock Output CPU/4
    RCM_COCCLK_CPUDIV8          = (uint8_t)0x07,     //!<    Clock Output CPU/8
    RCM_COCCLK_CPUDIV16         = (uint8_t)0x08,     //!<    Clock Output CPU/16
    RCM_COCCLK_CPUDIV32         = (uint8_t)0x09,     //!<    Clock Output CPU/32
    RCM_COCCLK_CPUDIV64         = (uint8_t)0x0A,     //!<    Clock Output CPU/64
    RCM_COCCLK_HIRC             = (uint8_t)0x0B,     //!<    Clock Output HIRC
    RCM_COCCLK_MASTER           = (uint8_t)0x0C,     //!<    Clock Output Master
} RCM_COCCLK_T;

/**
   * @brief     Definition peripheral
   */
typedef enum
{
    RCM_PERIPH_I2C              = ((uint16_t)0x101),
    RCM_PERIPH_SPI              = ((uint16_t)0x102),
    RCM_PERIPH_USART1           = ((uint16_t)0x108),
    RCM_PERIPH_TMR4             = ((uint16_t)0x110),
    RCM_PERIPH_TMR2             = ((uint16_t)0x120),
    RCM_PERIPH_TMR1             = ((uint16_t)0x180),
    RCM_PERIPH_WAKEUP           = ((uint16_t)0x204),
    RCM_PERIPH_ADC              = ((uint16_t)0x208),
    RCM_PERIPH_TMR1A            = ((uint16_t)0x401),
    RCM_PERIPH_USART2           = ((uint16_t)0x402),
    RCM_PERIPH_USART3           = ((uint16_t)0x404),
} RCM_PERIPH_T;

/**
 * @brief   RCM Clock flag definition
 */
typedef enum
{

    RCM_CLOCK_FLAG_LIRCRDY      = ((uint16_t)0x0110),       //!<   Low speed internal oscillator ready Flag
    RCM_CLOCK_FLAG_HIRCRDY      = ((uint16_t)0x0102),       //!<   High speed internal oscillator ready Flag
    RCM_CLOCK_FLAG_HXTRDY       = ((uint16_t)0x0202),       //!<   High speed external oscillator ready Flag
    RCM_CLOCK_FLAG_CSIF         = ((uint16_t)0x0408),       //!<   Clock switch interrupt Flag
    RCM_CLOCK_FLAG_CSBSY        = ((uint16_t)0x0401),       //!<   Switch busy Flag
    RCM_CLOCK_FLAG_CSSFD        = ((uint16_t)0x0808),       //!<   Clock security system fault detection Flag
    RCM_CLOCK_FLAG_BCEN         = ((uint16_t)0x0802),       //!<   Backup clock enable flag
    RCM_CLOCK_FLAG_COCBSY       = ((uint16_t)0x1040),       //!<   Configurable clock output busy
    RCM_CLOCK_FLAG_COCRDY       = ((uint16_t)0x1020),       //!<   Configurable clock output ready
} RCM_CLOCK_FLAG_T;

/**
 * @brief   RCM Interrupt Source
 */
typedef enum
{
    RCM_INT_CSSFD               = ((uint8_t)0x01),          //!<   Clock security system fault detection interrupt
    RCM_INT_CS                  = ((uint8_t)0x02),          //!<   Clock switch interrupt
} RCM_INT_T;

/**
 * @brief   RCM Interrupt flag definition
 */
typedef enum
{
    RCM_INT_FLAG_CSSFD          = ((uint8_t)0x01),          //!<   Clock security system fault detection interrupt flag
    RCM_INT_FLAG_CS             = ((uint8_t)0x02),          //!<   Clock switch interrupt flag
} RCM_INT_FLAG_T;

/**
 * @brief   HIRC divider number
 */
typedef enum
{
    RCM_HIRC_DIV_1              = ((uint8_t)0x10),
    RCM_HIRC_DIV_2              = ((uint8_t)0x11),
    RCM_HIRC_DIV_3              = ((uint8_t)0x00),
    RCM_HIRC_DIV_4              = ((uint8_t)0x12),
    RCM_HIRC_DIV_6              = ((uint8_t)0x01),
    RCM_HIRC_DIV_8              = ((uint8_t)0x13),
    RCM_HIRC_DIV_12             = ((uint8_t)0x02),
    RCM_HIRC_DIV_24             = ((uint8_t)0x03),
} RCM_HIRC_DIV_T;

/**
 * @brief   CPU Clock divider number
 */
typedef enum
{
    RCM_CPUCLK_DIV_1            = ((uint8_t)0x00),
    RCM_CPUCLK_DIV_2            = ((uint8_t)0x01),
    RCM_CPUCLK_DIV_4            = ((uint8_t)0x02),
    RCM_CPUCLK_DIV_8            = ((uint8_t)0x03),
    RCM_CPUCLK_DIV_16           = ((uint8_t)0x04),
    RCM_CPUCLK_DIV_32           = ((uint8_t)0x05),
    RCM_CPUCLK_DIV_64           = ((uint8_t)0x06),
    RCM_CPUCLK_DIV_128          = ((uint8_t)0x07),
} RCM_CPUCLK_DIV_T;

/**
 * @brief   Clock State definition
 */
typedef enum
{
    RCM_CLOCK_STATE_OFF         = ((uint8_t)0X00),
    RCM_CLOCK_STATE_ON          = ((uint8_t)0X01),
} RCM_CLOCK_STATE_T;

/**
 * @brief   Regulator power state in Active-halt mode
 */
typedef enum
{
    RCM_REGULATOR_POWER_ON      = ((uint8_t)0x00),
    RCM_REGULATOR_POWER_OFF     = ((uint8_t)0x01),
} RCM_REGULATOR_POWER_T;

/**
 * @brief   Reset flag
 */
typedef enum
{
    RCM_RTS_FLAG_WWDTRST        = ((uint8_t)0x01),      //!<    Window watch dog timer reset flag
    RCM_RTS_FLAG_IWDTRST        = ((uint8_t)0x02),      //!<    Independent Watchdog timer reset flag
    RCM_RTS_FLAG_SWRST          = ((uint8_t)0x04),      //!<    CPU software reset flag
    RCM_RTS_FLAG_ECMRST         = ((uint8_t)0x10),      //!<    EMC reset flag
} RCM_RTS_FLAG_T;

/**@} end of group RCM_Enumerations*/

/** @addtogroup RCM_Structure Data Structure
  @{
*/

/**
 * @brief   Switch Clock Struct
 */
typedef struct
{
    uint8_t intEnable;                      //!<   Enable or Disable Clock switch interrupt.The value Can be Enable or Disable
    RCM_SWITCH_MODE_T mode;                 //!<   Select the clock switch mode
    RCM_MCLKSRC_T     clockSource;          //!<   Select the Clock Source.
    RCM_CLOCK_STATE_T currentClkState;      //!<   Current clock to switch OFF or to keep ON
} RCM_SwitchClockStruct_T;

/** @addtogroup RCM_Macros Macros
  @{
*/

/** Internal clock control register reset value */
#define RCM_ICC_RESET_VALUE             ((uint32_t)0X01)
/** External clock control register reset value */
#define RCM_ECC_RESET_VALUE             ((uint32_t)0X00)
/** Master clock status register reset value */
#define RCM_MCS_RESET_VALUE             ((uint32_t)0xE1)
/** Master clock configuration register reset value */
#define RCM_MCC_RESET_VALUE             ((uint32_t)0xE1)
/** Clock switch control register reset value */
#define RCM_CSC_RESET_VALUE             ((uint32_t)0x00)
/** Clock divider number register reset value */
#define RCM_CLKDIV_RESET_VALUE          ((uint32_t)0x18)
/** APB clock register 1 reset value */
#define RCM_APBEN1_RESET_VALUE          ((uint32_t)0xFF)
/** Clock output control register reset value */
#define RCM_COC_RESET_VALUE             ((uint32_t)0x00)
/** APB clock register 2 reset value  */
#define RCM_APBEN2_RESET_VALUE          ((uint32_t)0xFF)
/** HIRC trimming register reset value */
#define RCM_HIRCTRIM_RESET_VALUE        ((uint32_t)0x00)
/** APB clock register 3 reset value */
#define RCM_APBEN3_RESET_VALUE          ((uint32_t)0x07)
/** Clock security system register register reset value */
#define RCM_CSS_RESET_VALUE             ((uint32_t)0x00)

/** @addtogroup RCM_Fuctions Fuctions
  @{
*/

/** RCM Peripheral Reset */
void RCM_Reset(void);

/** Enable/Disable Fast wakeup */
void RCM_EnableFastWakeup(void);
void RCM_DisableFastWakeup(void);

/** HXT Configuration */
void RCM_EnableHXT(void);
void RCM_DisableHXT(void);

/** HIRC Configuration */
void RCM_EnableHIRC(void);
void RCM_DisableHIRC(void);
void RCM_ConfigHIRCDiv(RCM_HIRC_DIV_T div);
void RCM_SetHIRCTrim(uint8_t trim);

/** LIRC Configuration */
void RCM_EnableLIRC(void);
void RCM_DisableLIRC(void);

/** Clock Output  */
void RCM_EnableClockOutput(void);
void RCM_DisableClockOutput(void);
void RCM_ConfigClockOutput(RCM_COCCLK_T clock);

/** Clock Switch */
void RCM_EnableClockSwitch(void);
void RCM_DisableClockSwitch(void);
uint8_t RCM_ConfigClockSwitch(RCM_SwitchClockStruct_T *switchClockStruct);
void RCM_ResetClockSwitch(void);

/** Peripheral Clock */
void RCM_EnableAPBPeriphClock(uint16_t periph);
void RCM_DisableAPBPeriphClock(uint16_t periph);

/** Regulator Power */
void RCM_ConfigRegulatorPower(RCM_REGULATOR_POWER_T mode);

/** CPU Clock */
void RCM_ConfigCPUClkDiv(RCM_CPUCLK_DIV_T div);

/** Interrupt */
void RCM_EnableInterrupt(uint8_t interrupt);
void RCM_DisableInterrupt(uint8_t interrupt);
uint8_t RCM_ReadIntFlag(uint8_t flag);
void RCM_ClearIntFlag(uint8_t flag);

/** Clock Security System */
void RCM_EnableClockSecuritySystem(void);

/** Master Clock */
RCM_MCLKSRC_T RCM_GetMasterClockSource(void);
uint32_t RCM_GetMasterClockFreq(void);

/** Clock Flag and Reset Flag */
uint8_t RCM_ReadClockFlag(RCM_CLOCK_FLAG_T flag);
uint8_t RCM_ReadResetFlag(uint8_t flag);
void RCM_ClearResetFlag(uint8_t flag);

/**@} end of group RCM_Fuctions*/
/**@} end of group RCM_Driver*/
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_RCM_H */

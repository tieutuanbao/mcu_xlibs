/*!
 * @file        apm32f00x_tmr4.h
 *
 * @brief       This file contains all functions prototype, enumeration and macro for the Timer4 peripheral
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
#ifndef __APM32F00X_TMR4_H
#define __APM32F00X_TMR4_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup TMR4_Driver TMR4 Driver
  @{
*/

/** @addtogroup TMR4_Enumerations Enumerations
  @{
*/

/**
 * @brief   TMR4 interrupt sources
 */
typedef enum
{
    TMR4_INT_UPDATE                 = ((uint8_t)0X01),
    TMR4_INT_TRIGGER                = ((uint8_t)0X40),
} TMR4_INT_T;

/**
 * @brief   TMR4 Input Trigger configuration
 */
typedef enum
{
    TMR4_ITC_TMR1                   = ((uint8_t)0x01),
    TMR4_ITC_TMR1A                  = ((uint8_t)0x02),
    TMR4_ITC_TMR2                   = ((uint8_t)0x03),
} TMR4_ITC_T;

/**
 * @brief   TMR4 Event Source
 */
typedef enum
{
    TMR4_EVENT_UPDATE           = ((uint8_t)0x01),
    TMR4_EVENT_TRIGGER          = ((uint8_t)0x40),
} TMR4_EVENT_T;

/**
 * @brief   TMR4 Update Source
 */
typedef enum
{
    TMR4_UPDATE_SOURCE_NONE     = ((uint8_t)0x10),
    TMR4_UPDATE_SOURCE_GLOBAL   = ((uint8_t)0x00),
    TMR4_UPDATE_SOURCE_REGULAR  = ((uint8_t)0x01),
} TMR4_UPDATE_SOURCE_T;

/**
 * @brief   TMR4 Slave Mode
 */
typedef enum
{
    TMR4_SLAVE_MODE_RESET           = ((uint8_t)0x04),
    TMR4_SLAVE_MODE_GATED           = ((uint8_t)0x05),
    TMR4_SLAVE_MODE_TRIGGER         = ((uint8_t)0x06),
    TMR4_SLAVE_MODE_EXTERNAL1       = ((uint8_t)0x07)
} TMR4_SLAVE_MODE_T;

/**
 * @brief   TMR2 Master Mode
 */
typedef enum
{
    TMR4_MASTER_MODE_RESET              = ((uint8_t)0x00),
    TMR4_MASTER_MODE_ENABLE             = ((uint8_t)0x01),
    TMR4_MASTER_MODE_UPDATE             = ((uint8_t)0x02),
} TMR4_MASTER_MODE_T;

/**
 * @brief   TMR4 Flags
 */
typedef enum
{
    TMR4_FLAG_UPDATE            = ((uint16_t)0x001),
    TMR4_FLAG_TRIGGER           = ((uint16_t)0x040),
} TMR4_FLAG_T;

/**@} end of group TMR4_Enumerations*/

/** @addtogroup TMR4_Macros Macros
  @{
*/

/** Timer4 Registers Reset Value */
#define TMR4_CTRL1_RESET_VALUE              (0x00)
#define TMR4_CTRL2_RESET_VALUE              (0x00)
#define TMR4_SMC_RESET_VALUE                (0x00)
#define TMR4_INTCTRL_RESET_VALUE            (0x00)
#define TMR4_STS_RESET_VALUE                (0x00)
#define TMR4_SCEG_RESET_VALUE               (0x00)
#define TMR4_CNT_RESET_VALUE                (0x00)
#define TMR4_DIV_RESET_VALUE                (0x00)
#define TMR4_AURLD_RESET_VALUE              (0xFF)

/**@} end of group TMR4_Macros*/

/** @addtogroup TMR4_Fuctions Fuctions
  @{
*/

/** Timer reset and configuration */
void TMR4_Reset(void);
void TMR4_ConfigTimerBase(uint8_t divider, uint8_t count);
void TMR4_Enable(void);
void TMR4_Disable(void);

/** divider */
void TMR4_SetDivider(uint8_t divider);
uint8_t TMR4_ReadDivider(void);

/** Auto reload */
void TMR4_SetAutoReloadVaue(uint8_t reload);
void TMR4_EnableAutoReloadBuffer(void);
void TMR4_DisableAutoReloadBuffer(void);

/** Update and update source */
void TMR4_ConfigUpdate(TMR4_UPDATE_SOURCE_T source);

/** Single Pulse Mode */
void TMR4_EnableSinglePulseMode(void);
void TMR4_DisableSinglePulseMode(void);

/** Counter */
uint8_t TMR4_ReadCounter(void);
void TMR4_SetCounter(uint8_t count);

/** Interrupt and flag */
void TMR4_EnableInterrupt(uint8_t interrupt);
void TMR4_DisableInterrupt(uint8_t interrupt);
uint8_t TMR4_ReadIntFlag(uint8_t interrupt);
void TMR4_ClearIntFlag(uint8_t interrupt);
uint8_t TMR4_ReadStatusFlag(uint8_t flag);
void TMR4_ClearStatusFlag(uint8_t flag);

/** Event */
void TMR4_GenerateEvent(uint8_t event);

/** Slave and Master mode */
void TMR4_ConfigSlaveMode(TMR4_SLAVE_MODE_T mode);
void TMR4_ConfigMasterMode(TMR4_MASTER_MODE_T mode);
void TMR4_EnableMasterMode(void);
void TMR4_DisableMasterMode(void);

/**@} end of group TMR4_Fuctions*/
/**@} end of group TMR4_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_TMR4_H */

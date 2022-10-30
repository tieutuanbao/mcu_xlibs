/*!
 * @file        apm32f00x_tmr2.h
 *
 * @brief       This file contains all functions prototype,enumeration and macro for the Timer2 peripheral
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
#ifndef __APM32F00X_TMR2_H
#define __APM32F00X_TMR2_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup TMR2_Driver TMR2 Driver
  @{
*/

/** @addtogroup TMR2_Enumerations Enumerations
  @{
*/

/**
 * @brief   TMR2 Output Compare mode
 */
typedef enum
{
    TMR2_OC_MODE_TIMING             = ((uint8_t)0),     //!<   Output compare frozen
    TMR2_OC_MODE_ACTIVE             = ((uint8_t)1),     //!<   Set active level on match
    TMR2_OC_MODE_INACTIVE           = ((uint8_t)2),     //!<   Set inactive level on match
    TMR2_OC_MODE_TOGGLE             = ((uint8_t)3),     //!<   CH1OCREF toggles
    TMR2_OC_MODE_FORCE_INACTIVE     = ((uint8_t)4),     //!<   Force inactive level
    TMR2_OC_MODE_FORCE_ACTIVE       = ((uint8_t)5),     //!<   Force active level
    TMR2_OC_MODE_PWM1               = ((uint8_t)6),     //!<   PWM mode 1
    TMR2_OC_MODE_PWM2               = ((uint8_t)7)      //!<   PWM mode 2
} TMR2_OC_MODE_T;

/**
 * @brief   TMR2 Channel
 */
typedef enum
{
    TMR2_CHANNEL_1                  = ((uint8_t)0x01),
    TMR2_CHANNEL_2                  = ((uint8_t)0x02),
    TMR2_CHANNEL_3                  = ((uint8_t)0x04),
    TMR2_CHANNEL_ALL                = ((uint8_t)0x07),
} TMR2_CHANNEL_T;

/**
 * @brief   TMR2 Output Compare Polarity
 */
typedef enum
{
    TMR2_OC_POLARITY_HIGH           = ((uint8_t)0),
    TMR2_OC_POLARITY_LOW            = ((uint8_t)1)
} TMR2_OC_POLARITY_T;

/**
 * @brief   TMR2 Input Capture porarity
 */
typedef enum
{
    TMR2_IC_POLARITY_RISING         = ((uint8_t)0),
    TMR2_IC_POLARITY_FALLING        = ((uint8_t)1)
} TMR2_IC_POLARITY_T;

/**
 * @brief   TMR2 Input Capture Selection
 */
typedef enum
{
    TMR2_IC_SELECT_DIRECTTI         = ((uint8_t)1),     //!<   Channel x Input capture mapped on CHxINFP1
    TMR2_IC_SELECT_INDIRECTTI       = ((uint8_t)2),     //!<   Channel x Input capture mapped on CHnINFP1
} TMR2_IC_SELECT_T;

/**
 * @brief   TMR2 Input Capture divider
 */
typedef enum
{
    TMR2_IC_DIV_1                   = ((uint8_t)0),     //!<   Capture is made once every 1 event
    TMR2_IC_DIV_2                   = ((uint8_t)1),     //!<   Capture is made once every 2 events
    TMR2_IC_DIV_4                   = ((uint8_t)2),     //!<   Capture is made once every 4 events
    TMR2_IC_DIV_8                   = ((uint8_t)3),     //!<   Capture is made once every 8 events
} TMR2_IC_DIV_T;

/**
 * @brief   TMR2 interrupt sources
 */
typedef enum
{
    TMR2_INT_UPDATE                 = ((uint8_t)0X01),
    TMR2_INT_CH1CC                  = ((uint8_t)0X02),
    TMR2_INT_CH2CC                  = ((uint8_t)0X04),
    TMR2_INT_CH3CC                  = ((uint8_t)0X08),
    TMR2_INT_TRIGGER                = ((uint8_t)0X40),
} TMR2_INT_T;


/**
 * @brief   TMR2 Input Trigger configuration
 */
typedef enum
{
    TMR2_ITC_TMR4                   = ((uint8_t)0x00),
    TMR2_ITC_TMR1                   = ((uint8_t)0x01),
    TMR2_ITC_TMR1A                  = ((uint8_t)0x02),
} TMR2_ITC_T;

/**
 * @brief   TMR2 Event Source
 */
typedef enum
{
    TMR2_EVENT_UPDATE           = ((uint8_t)0x01),
    TMR2_EVENT_CH1CC            = ((uint8_t)0x02),
    TMR2_EVENT_CH2CC            = ((uint8_t)0x04),
    TMR2_EVENT_CH3CC            = ((uint8_t)0x08),
    TMR2_EVENT_TRIGGER          = ((uint8_t)0x40),
} TMR2_EVENT_T;

/**
 * @brief   TMR2 Update Source
 */
typedef enum
{
    TMR2_UPDATE_SOURCE_NONE     = ((uint8_t)0x10),
    TMR2_UPDATE_SOURCE_GLOBAL   = ((uint8_t)0x00),
    TMR2_UPDATE_SOURCE_REGULAR  = ((uint8_t)0x01),
} TMR2_UPDATE_SOURCE_T;

/**
 * @brief   TMR2 Slave Mode
 */
typedef enum
{
    TMR2_SLAVE_MODE_RESET           = ((uint8_t)0x04),
    TMR2_SLAVE_MODE_GATED           = ((uint8_t)0x05),
    TMR2_SLAVE_MODE_TRIGGER         = ((uint8_t)0x06),
    TMR2_SLAVE_MODE_EXTERNAL1       = ((uint8_t)0x07)
} TMR2_SLAVE_MODE_T;

/**
 * @brief   TMR2 Master Mode
 */
typedef enum
{
    TMR2_MASTER_MODE_RESET              = ((uint8_t)0x00),
    TMR2_MASTER_MODE_ENABLE             = ((uint8_t)0x01),
    TMR2_MASTER_MODE_UPDATE             = ((uint8_t)0x02),
} TMR2_MASTER_MODE_T;

/**
 * @brief   TMR2 Flags
 */
typedef enum
{
    TMR2_FLAG_UPDATE            = ((uint16_t)0x001),
    TMR2_FLAG_CH1CC             = ((uint16_t)0x002),
    TMR2_FLAG_CH2CC             = ((uint16_t)0x004),
    TMR2_FLAG_CH3CC             = ((uint16_t)0x008),
    TMR2_FLAG_TRIGGER           = ((uint16_t)0x040),
    TMR2_FLAG_CH1RCF            = ((uint16_t)0x200),
    TMR2_FLAG_CH2RCF            = ((uint16_t)0x400),
    TMR2_FLAG_CH3RCF            = ((uint16_t)0x800),
} TMR2_FLAG_T;

/**
 * @brief   Enable/Disable compare output
 */
typedef enum
{
    TMR2_OC_OUTPUT_DISABLE,
    TMR2_OC_OUTPUT_ENABLE,
} TMR2_OC_OUTPUT_STATE_T;

/**@} end of group TMR2_Enumerations*/

/** @addtogroup TMR2_Structure Data Structure
  @{
*/

/**
 * @brief    Timer2 Output Compare Config structure definition
 */
typedef struct
{
    uint16_t count;                             //!< Specifies the counter
    TMR2_OC_MODE_T mode;                        //!< Specifies the Output Compare mode
    uint8_t channel;                            //!< Timer Channel.Can be combination of the values @ref TMR2_CHANNEL_T
    TMR2_OC_OUTPUT_STATE_T OCxOutputState;      //!< Enable/Disable Compare output
    TMR2_OC_POLARITY_T OCxPolarity;             //!< Compare polarity
} TMR2_OCConfig_T;

/**
 * @brief   Timer2 Input capture Config structure definition
 */
typedef struct
{
    uint8_t channel;                //!< Timer Channel.Can be combination of the values @ref TMR2_CHANNEL_T
    uint8_t filter;                 //!< Specifies Input Capture filter
    TMR2_IC_DIV_T div;              //!< Specifies Input Capture divider
    TMR2_IC_SELECT_T selection;     //!< Specifies Input Capture selection
    TMR2_IC_POLARITY_T polarity;    //!< Specifies Input Capture polarity
} TMR2_ICConfig_T;

/**@} end of group TMR2_Structure*/

/** @addtogroup TMR2_Macros Macros
  @{
*/

/** TIMER2 Registers Reset Value */
#define TMR2_CTRL1_RESET_VALUE              (0x00)
#define TMR2_CTRL2_RESET_VALUE              (0x00)
#define TMR2_SMC_RESET_VALUE                (0x00)
#define TMR2_INTCTRL_RESET_VALUE            (0x00)
#define TMR2_STS1_RESET_VALUE               (0x00)
#define TMR2_STS2_RESET_VALUE               (0x00)
#define TMR2_SCEG_RESET_VALUE               (0x00)
#define TMR2_CH1CCM_RESET_VALUE             (0x00)
#define TMR2_CH2CCM_RESET_VALUE             (0x00)
#define TMR2_CH3CCM_RESET_VALUE             (0x00)
#define TMR2_CHCTRL1_RESET_VALUE            (0x00)
#define TMR2_CHCTRL2_RESET_VALUE            (0x00)
#define TMR2_CNT1_RESET_VALUE               (0x00)
#define TMR2_CNT0_RESET_VALUE               (0x00)
#define TMR2_DIV_RESET_VALUE                (0x00)
#define TMR2_AURLD1_RESET_VALUE             (0xFF)
#define TMR2_AURLD0_RESET_VALUE             (0xFF)
#define TMR2_CH1CC1_RESET_VALUE             (0x00)
#define TMR2_CH1CC0_RESET_VALUE             (0x00)
#define TMR2_CH2CC1_RESET_VALUE             (0x00)
#define TMR2_CH2CC0_RESET_VALUE             (0x00)
#define TMR2_CH3CC1_RESET_VALUE             (0x00)
#define TMR2_CH3CC0_RESET_VALUE             (0x00)

/**@} end of group TMR2_Macros*/

/** @addtogroup TMR2_Fuctions Fuctions
  @{
*/

/** Timer reset and configuration */
void TMR2_Reset(void);
void TMR2_ConfigTimerBase(uint8_t divider, uint16_t count);
void TMR2_Enable(void);
void TMR2_Disable(void);

/** divider */
void TMR2_SetDivider(uint8_t divider);
uint8_t TMR2_ReadDivider(void);

/** Auto reload */
void TMR2_SetAutoReloadVaue(uint16_t reload);
void TMR2_EnableAutoReloadBuffer(void);
void TMR2_DisableAutoReloadBuffer(void);

/** Couter */
uint16_t TMR2_ReadCounter(void);
void TMR2_SetCounter(uint16_t count);

/** Update and update source */
void TMR2_ConfigUpdate(TMR2_UPDATE_SOURCE_T source);

/** Single Pulse Mode */
void TMR2_EnableSinglePulseMode(void);
void TMR2_DisableSinglePulseMode(void);

/** Interrupt and flag */
void TMR2_EnableInterrupt(uint8_t interrupt);
void TMR2_DisableInterrupt(uint8_t interrupt);
uint8_t TMR2_ReadIntFlag(uint8_t interrupt);
void TMR2_ClearIntFlag(uint8_t interrupt);
uint8_t TMR2_ReadStatusFlag(uint16_t flag);
void TMR2_ClearStatusFlag(uint16_t flag);

/** Output Compare */
void TMR2_ConfigOutputCompare(TMR2_OCConfig_T * ocConfigStruct);
void TMR2_OCStructInit(TMR2_OCConfig_T *ocConfigStruct);
void TMR2_ConfigOutputCompareMode(uint8_t channel, TMR2_OC_MODE_T mode);
void TMR2_EnableOutputCompareBuffer(uint8_t channel);
void TMR2_DisableOutputCompareBuffer(uint8_t channel);
void TMR2_ConfigOutputComparePolarity(uint8_t channel, TMR2_OC_POLARITY_T polarity);

/** Input Capture function list */
void TMR2_ConfigInputCapture(TMR2_ICConfig_T *icConfigStruct);
void TMR2_ICStructInit(TMR2_ICConfig_T *icConfigStruct);
void TMR2_ConfigInputPWM(TMR2_ICConfig_T *pwmInputConfig);
void TMR2_ConfigInputTrigger(TMR2_ITC_T trigger);
void TMR2_SetInputCaptureDivider(uint8_t channel, TMR2_IC_DIV_T divider);

/** Input Capture/Output Compare */
void TMR2_EnableCompareCapture(uint8_t channel);
void TMR2_DisableCompareCapture(uint8_t channel);
void TMR2_SetCompareCapture(uint8_t channel, uint16_t compare);
uint16_t TMR2_ReadCompareCapture(TMR2_CHANNEL_T channel);

/** Event */
void TMR2_GenerateEvent(uint8_t event);

/** Slave and Master mode */
void TMR2_ConfigSlaveMode(TMR2_SLAVE_MODE_T mode);
void TMR2_ConfigMasterMode(TMR2_MASTER_MODE_T mode);
void TMR2_EnableMasterMode(void);
void TMR2_DisableMasterMode(void);

/**@} end of group TMR2_Fuctions*/
/**@} end of group TMR2_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_TMR2_H */

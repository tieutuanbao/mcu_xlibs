/*!
 * @file        apm32f00x_tmr1.h
 *
 * @brief       This file contains all functions prototype, enumeration and macro for the Timer1/Timer1A peripheral
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
#ifndef __APM32F00X_TMR1_H
#define __APM32F00X_TMR1_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup TMR1_Driver TMR1 Driver
  @{
*/

/** @addtogroup TMR1_Enumerations Enumerations
  @{
*/

/**
 * @brief   TMR1/TMR1A Output Compare mode
 */
typedef enum
{
    TMR1_OC_MODE_TIMING             = ((uint8_t)0),     //!<   Output compare frozen
    TMR1_OC_MODE_ACTIVE             = ((uint8_t)1),     //!<   Set active level on match
    TMR1_OC_MODE_INACTIVE           = ((uint8_t)2),     //!<   Set inactive level on match
    TMR1_OC_MODE_TOGGLE             = ((uint8_t)3),     //!<   CH1OCREF toggles
    TMR1_OC_MODE_FORCE_INACTIVE     = ((uint8_t)4),     //!<   Force inactive level
    TMR1_OC_MODE_FORCE_ACTIVE       = ((uint8_t)5),     //!<   Force active level
    TMR1_OC_MODE_PWM1               = ((uint8_t)6),     //!<   PWM mode 1
    TMR1_OC_MODE_PWM2               = ((uint8_t)7)      //!<   PWM mode 2
} TMR1_OC_MODE_T;

/**
 * @brief   TMR1/TMR1A Channel
 */
typedef enum
{
    TMR1_CHANNEL_1                  = ((uint8_t)0x01),
    TMR1_CHANNEL_2                  = ((uint8_t)0x02),
    TMR1_CHANNEL_3                  = ((uint8_t)0x04),
    TMR1_CHANNEL_4                  = ((uint8_t)0x08),
    TMR1_CHANNEL_ALL                = ((uint8_t)0x0F),
} TMR1_CHANNEL_T;

/**
 * @brief   TMR1/TMR1A Counter Mode
 */
typedef enum
{
    TMR1_CNT_MODE_UP                = ((uint8_t)0x00),
    TMR1_CNT_MODE_DOWN              = ((uint8_t)0x10),
    TMR1_CNT_MODE_CENTER_ALIGNED1   = ((uint8_t)0x01),
    TMR1_CNT_MODE_CENTER_ALIGNED2   = ((uint8_t)0x02),
    TMR1_CNT_MODE_CENTER_ALIGNED3   = ((uint8_t)0x03)
} TMR1_CNT_MODE_T;

/**
 * @brief   TMR1/TMR1A Output Compare Polarity
 */
typedef enum
{
    TMR1_OC_POLARITY_HIGH           = ((uint8_t)0),
    TMR1_OC_POLARITY_LOW            = ((uint8_t)1)
} TMR1_OC_POLARITY_T;

/**
 * @brief   TMR1/TMR1A Break Polarity
 */
typedef enum
{
    TMR1_BREAK_POL_LOW              = ((uint8_t)0),
    TMR1_BREAK_POL_HIGH             = ((uint8_t)1)
} TMR1_BREAK_POL_T;

/**
 * @brief   TMR1/TMR1A Protection level
 */
typedef enum
{
    TMR1_PROTECTION_LEVEL_OFF       = ((uint8_t)0),
    TMR1_PROTECTION_LEVEL_1         = ((uint8_t)1),
    TMR1_PROTECTION_LEVEL_2         = ((uint8_t)2),
    TMR1_PROTECTION_LEVEL_3         = ((uint8_t)3)
} TMR1_PROTECTION_LEVEL_T;

/**
 * @brief   TMR1/TMR1A off-state in idle mode
 */
typedef enum
{
    TMR1_OSIM_DISABLE               = ((uint8_t)0),
    TMR1_OSIM_ENABLE                = ((uint8_t)1),
} TMR1_OSIM_T;

/**
 * @brief   TMR1/TMR1A off-state in run mode
 */
typedef enum
{
    TMR1_OSRM_DISABLE               = ((uint8_t)0),
    TMR1_OSRM_ENABLE                = ((uint8_t)1),
} TMR1_OSRM_T;

/**
 * @brief   TMR1/TMR1A Output Compare Idle State
 */
typedef enum
{
    TMR1_OC_IDLE_RESET              = ((uint8_t)0),
    TMR1_OC_IDLE_SET                = ((uint8_t)1)
} TMR1_OC_IDLE_T;

/**
 * @brief   TMR1/TMR1A Input Capture porarity
 */
typedef enum
{
    TMR1_IC_POLARITY_RISING         = ((uint8_t)0),
    TMR1_IC_POLARITY_FALLING        = ((uint8_t)1)
} TMR1_IC_POLARITY_T;

/**
 * @brief   TMR1/TMR1A Input Capture Selection
 */
typedef enum
{
    TMR1_IC_SELECT_DIRECTTI         = ((uint8_t)1),     //!<   Channel x Input capture mapped on CHxINFP1
    TMR1_IC_SELECT_INDIRECTTI       = ((uint8_t)2),     //!<   Channel x Input capture mapped on CHnINFP1
    TMR1_IC_SELECT_TRGCAP           = ((uint8_t)3)      //!<   Channel x Input capture mapped on TRGCAP
} TMR1_IC_SELECT_T;

/**
 * @brief   TMR1/TMR1A Input Capture divider
 */
typedef enum
{
    TMR1_IC_DIV_1                   = ((uint8_t)0),     //!<   Capture is made once every 1 event
    TMR1_IC_DIV_2                   = ((uint8_t)1),     //!<   Capture is made once every 2 events
    TMR1_IC_DIV_4                   = ((uint8_t)2),     //!<   Capture is made once every 4 events
    TMR1_IC_DIV_8                   = ((uint8_t)3),     //!<   Capture is made once every 8 events
} TMR1_IC_DIV_T;

/**
 * @brief   TMR1/TMR1A interrupt sources
 */
typedef enum
{
    TMR1_INT_UPDATE                 = ((uint8_t)0X01),
    TMR1_INT_CH1CC                  = ((uint8_t)0X02),
    TMR1_INT_CH2CC                  = ((uint8_t)0X04),
    TMR1_INT_CH3CC                  = ((uint8_t)0X08),
    TMR1_INT_CH4CC                  = ((uint8_t)0X10),
    TMR1_INT_CC_UPDATE              = ((uint8_t)0X20),
    TMR1_INT_TRIGGER                = ((uint8_t)0X40),
    TMR1_INT_BREAK                  = ((uint8_t)0X80),
} TMR1_INT_T;

/**
 * @brief   TMR1/TMR1A External Trigger divider
 */
typedef enum
{
    TMR1_ETRG_DIV_OFF               = ((uint8_t)0),
    TMR1_ETRG_DIV_2                 = ((uint8_t)1),
    TMR1_ETRG_DIV_4                 = ((uint8_t)2),
    TMR1_ETRG_DIV_8                 = ((uint8_t)3),
} TMR1_ETRG_DIV_T;

/**
 * @brief   TMR1/TMR1A Input Trigger configuration
 */
typedef enum
{
    TMR1_ITC_TMR4                   = ((uint8_t)0x00),
    TMR1_ITC_TMR1_TMR1A             = ((uint8_t)0x01),
    TMR1_ITC_TMR2                   = ((uint8_t)0x03),
    TMR1_ITC_CH1INFED               = ((uint8_t)0x04),
    TMR1_ITC_CH1INFP1               = ((uint8_t)0x05),
    TMR1_ITC_CH2INFP2               = ((uint8_t)0x06),
    TMR1_ITC_ETRGF                  = ((uint8_t)0x07)
} TMR1_ITC_T;

/**
 * @brief   TMR1/TMR1A External clock source
 */
typedef enum
{
    TMR1_EXT_CLK_SOURCE_INFED       = ((uint8_t)0x04),
    TMR1_EXT_CLK_SOURCE_CH1INFP1    = ((uint8_t)0x05),
    TMR1_EXT_CLK_SOURCE_CH2INFP2    = ((uint8_t)0x06),
} TMR1_EXT_CLK_SOURCE_T;

/**
 * @brief   TMR1/TMR1A External Trigger Polarity
 */
typedef enum
{
    TMR1_EXT_TRG_POLARITY_NONINVERTED   = ((uint8_t)0x00),
    TMR1_EXT_TRG_POLARITY_INVERTED      = ((uint8_t)0x01),
} TMR1_EXT_TRG_POLARITY_T;

/**
 * @brief   TMR1/TMR1A Encoder Mode
 */
typedef enum
{
    TMR1_ENCODER_MODE_CH1INFP1      = ((uint8_t)0x01),
    TMR1_ENCODER_MODE_CH1INFP2      = ((uint8_t)0x02),
    TMR1_ENCODER_MODE_CH1INFP12     = ((uint8_t)0x03),
} TMR1_ENCODER_MODE_T;

/**
 * @brief   TMR1/TMR1A Event Source
 */
typedef enum
{
    TMR1_EVENT_UPDATE           = ((uint8_t)0x01),
    TMR1_EVENT_CH1CC            = ((uint8_t)0x02),
    TMR1_EVENT_CH2CC            = ((uint8_t)0x04),
    TMR1_EVENT_CH3CC            = ((uint8_t)0x08),
    TMR1_EVENT_CH4CC            = ((uint8_t)0x10),
    TMR1_EVENT_CC_UPDATE        = ((uint8_t)0x20),
    TMR1_EVENT_TRIGGER          = ((uint8_t)0x40),
    TMR1_EVENT_BREAK            = ((uint8_t)0x80),
} TMR1_EVENT_T;

/**
 * @brief   TMR1/TMR1A Update Source
 */
typedef enum
{
    TMR1_UPDATE_SOURCE_NONE     = ((uint8_t)0x10),
    TMR1_UPDATE_SOURCE_GLOBAL   = ((uint8_t)0x00),
    TMR1_UPDATE_SOURCE_REGULAR  = ((uint8_t)0x01),
} TMR1_UPDATE_SOURCE_T;

/**
 * @brief   TMR1/TMR1A Slave Mode
 */
typedef enum
{
    TMR1_SLAVE_MODE_RESET           = ((uint8_t)0x04),
    TMR1_SLAVE_MODE_GATED           = ((uint8_t)0x05),
    TMR1_SLAVE_MODE_TRIGGER         = ((uint8_t)0x06),
    TMR1_SLAVE_MODE_EXTERNAL1       = ((uint8_t)0x07)
} TMR1_SLAVE_MODE_T;

/**
 * @brief   TMR1/TMR1A Master Mode
 */
typedef enum
{
    TMR1_MASTER_MODE_RESET              = ((uint8_t)0x00),
    TMR1_MASTER_MODE_ENABLE             = ((uint8_t)0x01),
    TMR1_MASTER_MODE_UPDATE             = ((uint8_t)0x02),
    TMR1_MASTER_MODE_COMPARE_PULSE      = ((uint8_t)0x03),
    TMR1_MASTER_MODE_CH1OCREF           = ((uint8_t)0x04),
    TMR1_MASTER_MODE_CH2OCREF           = ((uint8_t)0x05),
    TMR1_MASTER_MODE_CH3OCREF           = ((uint8_t)0x06),
    TMR1_MASTER_MODE_CH4OCREF           = ((uint8_t)0x07),
} TMR1_MASTER_MODE_T;

/**
 * @brief   TMR1/TMR1A Flags
 */
typedef enum
{
    TMR1_FLAG_UPDATE            = ((uint16_t)0x001),
    TMR1_FLAG_CH1CC             = ((uint16_t)0x002),
    TMR1_FLAG_CH2CC             = ((uint16_t)0x004),
    TMR1_FLAG_CH3CC             = ((uint16_t)0x008),
    TMR1_FLAG_CH4CC             = ((uint16_t)0x010),
    TMR1_FLAG_CC_UPDATE         = ((uint16_t)0x020),
    TMR1_FLAG_TRIGGER           = ((uint16_t)0x040),
    TMR1_FLAG_BREAK             = ((uint16_t)0x080),
    TMR1_FLAG_CH1RCF            = ((uint16_t)0x200),
    TMR1_FLAG_CH2RCF            = ((uint16_t)0x400),
    TMR1_FLAG_CH3RCF            = ((uint16_t)0x800),
    TMR1_FLAG_CH4RCF            = ((uint16_t)0x1000)
} TMR1_FLAG_T;

/**
 * @brief   TMR1/TMR1A Capture/Compare update source
 */
typedef enum
{
    TMR1_CCUS_0     = ((uint8_t)0),     //!<   Update by setting SCEG_CCUEG = 1
    TMR1_CCUS_1     = ((uint8_t)1)      //!<   Update by setting SCEG_CCUEG = 1 or when an rising edge occurs on tirgger input
} TMR1_CCUS_T;

/**
 * @brief   Enable/Disable compare output
 */
typedef enum
{
    TMR1_OC_OUTPUT_DISABLE,
    TMR1_OC_OUTPUT_ENABLE,
} TMR1_OC_OUTPUT_STATE_T;

/**@} end of group TMR1_Enumerations*/

/** @addtogroup TMR1_Structure Data Structure
  @{
*/

/**
 * @brief   TMR1/TMR1AA Time Base Config structure definition
 */
typedef struct
{
    uint16_t divider;               //!<   clock divider value
    uint16_t count;                 //!<   specifies the counter
    uint8_t repetitionCount;        //!<   specifies the Repetition counter value
    TMR1_CNT_MODE_T cntMode;        //!<   specifies the counter mode
} TMR1_TimeBaseConfig_T;

/**
 * @brief    Timer1/A Output Compare Config structure definition
 */
typedef struct
{
    uint16_t count;                             //!< specifies the counter
    TMR1_OC_MODE_T mode;                        //!< specifies the Output Compare mode
    uint8_t channel;                            //!< Timer Channel.Can be combination of the values @ref TMR1_CHANNEL_T
    TMR1_OC_OUTPUT_STATE_T OCxOutputState;      //!< Enable/Disable Compare output
    TMR1_OC_OUTPUT_STATE_T OCxNOutputState;     //!< Enable/Disable Compare complementary output
    TMR1_OC_POLARITY_T OCxPolarity;             //!< Compare polarity
    TMR1_OC_POLARITY_T OCxNPolarity;            //!< Compare complementary polarity
    TMR1_OC_IDLE_T OCxIdleState;                //!< Compare output idle state
    TMR1_OC_IDLE_T OCxNIdleState;               //!< Compare output complementary idle state
} TMR1_OCConfig_T;

/**
 * @brief   Timer1/A Input capture Config structure definition
 */
typedef struct
{
    uint8_t channel;                //!< Timer Channel.Can be combination of the values @ref TMR1_CHANNEL_T
    uint8_t filter;                 //!< specifies Input Capture filter
    TMR1_IC_DIV_T div;              //!< specifies Input Capture divider
    TMR1_IC_SELECT_T selection;     //!< specifies Input Capture selection
    TMR1_IC_POLARITY_T polarity;    //!< specifies Input Capture polarity
} TMR1_ICConfig_T;

/**
 * @brief   Timer1/A External trigger Config structure definition
 */
typedef struct
{
    uint8_t filter;                     //!< specifies the External Trigger filter
    TMR1_ETRG_DIV_T div;                //!< specifies the External Trigger divider
    TMR1_EXT_TRG_POLARITY_T polarity;   //!< specifies the External Trigger polarity
} TMR1_ExtTrigConfig_T;

/**
 * @brief   Timer1/A Encoder Config structure definition
 */
typedef struct
{
    TMR1_ENCODER_MODE_T mode;           //!< Encoder mode
    TMR1_IC_POLARITY_T polarityIC1;     //!< Channel 1 input capture polarity
    TMR1_IC_POLARITY_T polarityIC2;     //!< Channel 2 input capture polarity
} TMR1_EncoderConfig_T;

/**@} end of group TMR1_Structure*/

/** @addtogroup TMR1_Macros Macros
  @{
*/

/** TIMER1 Registers Reset Value */
#define TMR1_CTRL1_RESET_VALUE              (0x00)
#define TMR1_CTRL2_RESET_VALUE              (0x00)
#define TMR1_SMC_RESET_VALUE                (0x00)
#define TMR1_ETC_RESET_VALUE                (0x00)
#define TMR1_INTCTRL_RESET_VALUE            (0x00)
#define TMR1_STS1_RESET_VALUE               (0x00)
#define TMR1_STS2_RESET_VALUE               (0x00)
#define TMR1_SCEG_RESET_VALUE               (0x00)
#define TMR1_CH1CCM_RESET_VALUE             (0x00)
#define TMR1_CH2CCM_RESET_VALUE             (0x00)
#define TMR1_CH3CCM_RESET_VALUE             (0x00)
#define TMR1_CH4CCM_RESET_VALUE             (0x00)
#define TMR1_CHCTRL1_RESET_VALUE            (0x00)
#define TMR1_CHCTRL2_RESET_VALUE            (0x00)
#define TMR1_CNT1_RESET_VALUE               (0x00)
#define TMR1_CNT0_RESET_VALUE               (0x00)
#define TMR1_DIV1_RESET_VALUE               (0x00)
#define TMR1_DIV0_RESET_VALUE               (0x00)
#define TMR1_AUTORLD1_RESET_VALUE           (0xFF)
#define TMR1_AUTORLD0_RESET_VALUE           (0xFF)
#define TMR1_REPCNT_RESET_VALUE             (0x00)
#define TMR1_CH1CC1_RESET_VALUE             (0x00)
#define TMR1_CH1CC0_RESET_VALUE             (0x00)
#define TMR1_CH2CC1_RESET_VALUE             (0x00)
#define TMR1_CH2CC0_RESET_VALUE             (0x00)
#define TMR1_CH3CC1_RESET_VALUE             (0x00)
#define TMR1_CH3CC0_RESET_VALUE             (0x00)
#define TMR1_CH4CC1_RESET_VALUE             (0x00)
#define TMR1_CH4CC0_RESET_VALUE             (0x00)
#define TMR1_BRKCTRL_RESET_VALUE            (0x00)
#define TMR1_DTS_RESET_VALUE                (0x00)
#define TMR1_ISO_RESET_VALUE                (0x00)
#define TMR1_CHEN_RESET_VALUE               (0x00)

/**@} end of group TMR1_Macros*/

/** @addtogroup TMR1_Fuctions Fuctions
  @{
*/

/** Timer Reset and configuration*/
void TMR1_Reset(TMR1_T *tmr);
void TMR1_ConfigTimerBase(TMR1_T *tmr, TMR1_TimeBaseConfig_T *timeBaseConfigStruct);
void TMR1_ConfigTimeBaseStructInit(TMR1_TimeBaseConfig_T *timeBaseConfigStruct);
void TMR1_Enable(TMR1_T *tmr);
void TMR1_Disable(TMR1_T *tmr);
void TMR1_EnableChannel(TMR1_T *tmr, uint8_t channel);
void TMR1_DisableChannel(TMR1_T *tmr, uint8_t channel);

/** counter */
void TMR1_ConfigCountMode(TMR1_T *tmr, TMR1_CNT_MODE_T mode);
void TMR1_SetCounter(TMR1_T *tmr, uint16_t count);
uint16_t TMR1_ReadCounter(TMR1_T *tmr);

/** divider */
void TMR1_SetDivider(TMR1_T *tmr, uint16_t divider);
uint16_t TMR1_ReadDivider(TMR1_T *tmr);

/** Auto reload */
void TMR1_SetAutoReloadVaue(TMR1_T *tmr, uint16_t reload);
void TMR1_EnableAutoReloadBuffer(TMR1_T *tmr);
void TMR1_DisableAutoReloadBuffer(TMR1_T *tmr);

/** update and update source */
void TMR1_ConfigUpdate(TMR1_T *tmr, TMR1_UPDATE_SOURCE_T source);

/** Single Pulse Mode */
void TMR1_EnableSinglePulseMode(TMR1_T *tmr);
void TMR1_DisableSinglePulseMode(TMR1_T *tmr);

/** interrupt and flag */
void TMR1_EnableInterrupt(TMR1_T *tmr, uint8_t interrupt);
void TMR1_DisableInterrupt(TMR1_T *tmr, uint8_t interrupt);
uint8_t TMR1_ReadIntFlag(TMR1_T *tmr, uint8_t interrupt);
void TMR1_ClearIntFlag(TMR1_T *tmr, uint8_t interrupt);
uint8_t TMR1_ReadStatusFlag(TMR1_T *tmr, uint16_t flag);
void TMR1_ClearStatusFlag(TMR1_T *tmr, uint16_t flag);

/** Output Compare */
void TMR1_ConfigOutputCompare(TMR1_T *tmr, TMR1_OCConfig_T *ocConfigStruct);
void TMR1_OCStructInit(TMR1_OCConfig_T *ocConfigStruct);
void TMR1_ConfigOutputCompareMode(TMR1_T * tmr, uint8_t channel, TMR1_OC_MODE_T mode);
void TMR1_ConfigCCUpdateSource(TMR1_T *tmr, TMR1_CCUS_T mode);
void TMR1_EnableOutputCompareBuffer(TMR1_T *tmr, uint8_t channel);
void TMR1_DisableOutputCompareBuffer(TMR1_T *tmr, uint8_t channel);
void TMR1_EnableOutputCompareFastMode(TMR1_T *tmr, uint8_t channel);
void TMR1_DisableOutputCompareFastMode(TMR1_T *tmr, uint8_t channel);
void TMR1_ConfigOutputComparePolarity(TMR1_T *tmr, uint8_t channel, TMR1_OC_POLARITY_T polarity);
void TMR1_ConfigOutputCompareComplementPolarity(TMR1_T *tmr, uint8_t channel, TMR1_OC_POLARITY_T polarity);

/** Input Capture */
void TMR1_ConfigInputCapture(TMR1_T *tmr, TMR1_ICConfig_T *icConfigStruct);
void TMR1_ICStructInit(TMR1_ICConfig_T *icConfigStruct);
void TMR1_ConfigInputPWM(TMR1_T *tmr, TMR1_ICConfig_T *pwmInputConfig);
void TMR1_ConfigInputTrigger(TMR1_T *tmr, TMR1_ITC_T trigger);
void TMR1_SetInputCaptureDivider(TMR1_T *tmr, uint8_t channel, TMR1_IC_DIV_T divider);

/** Input Capture/Output Compare */
void TMR1_EnableCompareCapture(TMR1_T *tmr, uint8_t channel);
void TMR1_DisableCompareCapture(TMR1_T *tmr, uint8_t channel);
void TMR1_EnableCompareCaptureComplement(TMR1_T *tmr, uint8_t channel);
void TMR1_DisableCompareCaptureComplement(TMR1_T *tmr, uint8_t channel);
void TMR1_SetCompareCapture(TMR1_T *tmr, uint8_t channel, uint16_t compare);
uint16_t TMR1_ReadCompareCapture(TMR1_T *tmr, TMR1_CHANNEL_T channel);
void TMR1_EnableCompareCaptureBuffer(TMR1_T *tmr);
void TMR1_DisableCompareCaptureBuffer(TMR1_T *tmr);

/** break feature */
void TMR1_SetDeadTime(TMR1_T *tmr, uint8_t deadTime);
void TMR1_ConfigProtectionLevel(TMR1_T *tmr, TMR1_PROTECTION_LEVEL_T level);
void TMR1_SelectOffStateInRunMode(TMR1_T *tmr, TMR1_OSRM_T state);
void TMR1_SelectOffStateInIdleMode(TMR1_T *tmr, TMR1_OSIM_T state);
void TMR1_ConfigBreakPolarity(TMR1_T *tmr, TMR1_BREAK_POL_T polarity);
void TMR1_EnableBreak(TMR1_T *tmr);
void TMR1_DisableBreak(TMR1_T *tmr);
void TMR1_EnableAutomaticOutput(TMR1_T *tmr);
void TMR1_DisableAutomaticOutput(TMR1_T *tmr);
void TMR1_EnableOutputPWM(TMR1_T *tmr);
void TMR1_DisableOutputPWM(TMR1_T *tmr);

/** External Trigger function list */
void TMR1_ConfigExternalTrigger(TMR1_T *tmr, TMR1_EXT_TRG_POLARITY_T polarity,
                                        TMR1_ETRG_DIV_T div, uint8_t filter);

/** External Clock mode */
void TMR1_ConfigExternalClockMode2(TMR1_T *tmr, TMR1_EXT_TRG_POLARITY_T polarity,
                                            TMR1_ETRG_DIV_T div, uint8_t filter);
void TMR1_ConfigExternalClockMode1(TMR1_T *tmr, TMR1_EXT_CLK_SOURCE_T clock,
                                            TMR1_IC_POLARITY_T polarity, uint8_t filter);

/** Encoder Interface */
void TMR1_ConfigEncodeInterface(TMR1_T *tmr, TMR1_EncoderConfig_T *encoderConfigStruct);

/** Event */
void TMR1_GenerateEvent(TMR1_T *tmr, uint8_t event);

/** Slave and Master mode */
void TMR1_ConfigSlaveMode(TMR1_T *tmr, TMR1_SLAVE_MODE_T mode);
void TMR1_ConfigMasterMode(TMR1_T *tmr, TMR1_MASTER_MODE_T mode);
void TMR1_EnableMasterMode(TMR1_T *tmr);
void TMR1_DisableMasterMode(TMR1_T *tmr);

#ifdef __cplusplus
}
#endif

/**@} end of group TMR1_Fuctions*/
/**@} end of group TMR1_Driver */
/**@} end of group Peripherals_Library*/

#endif /* __APM32F00X_TMR1_H */

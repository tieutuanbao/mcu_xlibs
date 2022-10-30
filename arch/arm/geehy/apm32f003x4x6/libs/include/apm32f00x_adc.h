/*!
 * @file        apm32f00x_adc.h
 *
 * @brief       This file contains all the prototypes,enumeration and macros for the ADC1 peripheral
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

#ifndef __APM32F00X_ADC_H
#define __APM32F00X_ADC_H

#include "apm32f00x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/

/** @addtogroup ADC_Enumerations Enumerations
  @{
*/

/**
 * @brief   ADC clock divider
 */
typedef enum
{
    ADC_DIV_2       = ((uint8_t)00),
    ADC_DIV_3       = ((uint8_t)01),
    ADC_DIV_4       = ((uint8_t)02),
    ADC_DIV_6       = ((uint8_t)03),
    ADC_DIV_8       = ((uint8_t)04),
    ADC_DIV_10      = ((uint8_t)05),
    ADC_DIV_12      = ((uint8_t)06),
    ADC_DIV_18      = ((uint8_t)07),
} ADC_DIV_T;

/**
 * @brief   ADC External conversion trigger event selection
 */
typedef enum
{
    ADC_EXTTRG_NONE     = ((uint8_t)0x00),  //!< Disable external trigger
    ADC_EXTTRG_TIMER    = ((uint8_t)0x10),  //!< Conversion from Internal Timer1 TRGOUT event
    ADC_EXTTRG_ETR      = ((uint8_t)0x11),  //!< Conversion from External interrupt on ADC_ETR pin
} ADC_EXTTRG_T;

/**
 * @brief   ADC data alignment
 */
typedef enum
{
    ADC_DATA_ALIGN_LEFT     = ((uint8_t)0), //!< Data alignment left
    ADC_DATA_ALIGN_RIGHT    = ((uint8_t)1), //!< Data alignment right
} ADC_DATA_ALIGN_T;

/**
 * @brief   ADC Interrupt source
 */
typedef enum
{
    ADC_INT_NONE    = ((uint8_t)0x00),      //!< No interrupt
    ADC_INT_AWD     = ((uint8_t)0x10),      //!< Analog watch dog interrupt
    ADC_INT_CC      = ((uint8_t)0x20),      //!< Conversion completed interrupt
} ADC_INT_T;

/**
 * @brief   ADC Interrupt flag
 */
typedef enum
{
    ADC_INT_FLAG_AWD    = ((uint8_t)0x50), //!< Analog watch dog flag
    ADC_INT_FLAG_CC     = ((uint8_t)0xa0), //!< Conversion completed flag
} ADC_INT_FLAG_T;

/**
 * @brief   ADC flag
 */
typedef enum
{
    ADC_FLAG_AWD    = ((uint16_t)0x000140), //!< Analog watch dog flag
    ADC_FLAG_CC     = ((uint16_t)0x000180), //!< Conversion completed flag
    ADC_FLAG_OVR    = ((uint16_t)0x000240), //!< Overrun flag
} ADC_FLAG_T;

/**
 * @brief   ADC channel
 */
typedef enum
{
    ADC_CHANNEL_0   = ((uint16_t)BIT0),
    ADC_CHANNEL_1   = ((uint16_t)BIT1),
    ADC_CHANNEL_2   = ((uint16_t)BIT2),
    ADC_CHANNEL_3   = ((uint16_t)BIT3),
    ADC_CHANNEL_4   = ((uint16_t)BIT4),
    ADC_CHANNEL_5   = ((uint16_t)BIT5),
    ADC_CHANNEL_6   = ((uint16_t)BIT6),
    ADC_CHANNEL_7   = ((uint16_t)BIT7),
    ADC_CHANNEL_8   = ((uint16_t)BIT8),
} ADC_CHANNEL_T;

/**
 * @brief   ADC buffer index
 */
typedef enum
{
    ADC_BUFFER_IDX_0    = ((uint8_t)0),
    ADC_BUFFER_IDX_1    = ((uint8_t)1),
    ADC_BUFFER_IDX_2    = ((uint8_t)2),
    ADC_BUFFER_IDX_3    = ((uint8_t)3),
    ADC_BUFFER_IDX_4    = ((uint8_t)4),
    ADC_BUFFER_IDX_5    = ((uint8_t)5),
    ADC_BUFFER_IDX_6    = ((uint8_t)6),
    ADC_BUFFER_IDX_7    = ((uint8_t)7),
    ADC_BUFFER_IDX_8    = ((uint8_t)8),
    ADC_BUFFER_IDX_9    = ((uint8_t)9),
} ADC_BUFFER_IDX_T;

/**
 * @brief   ADC conversion mode
 */
typedef enum
{
    ADC_CONV_MODE_SINGLE        = ((uint8_t)0), //!< Single conversion mode
    ADC_CONV_MODE_CONTINUOUS    = ((uint8_t)1), //!< Continuous conversion mode
} ADC_CONV_MODE_T;

/**
 * @brief   ADC Scan mode
 */
typedef enum
{
    ADC_SCAN_MODE_DISABLE       = ((uint8_t)0), //!< Scan mode disable
    ADC_SCAN_MODE_ENABLE        = ((uint8_t)1), //!< Scan mode enable
} ADC_SCAN_MODE_T;

/**
 * @brief   ADC mode
 */
typedef enum
{
    ADC_MODE_SINGLE_END,
    ADC_MODE_DIFF_INPUT,
} ADC_MODE_T;

/**
 * @brief   Differential input channel
 */
typedef enum
{
    ADC_DIFF_CHANNEL_VAIN0      = ((uint8_t)0x00),
    ADC_DIFF_CHANNEL_VAIN1      = ((uint8_t)0x40),
    ADC_DIFF_CHANNEL_VAIN2      = ((uint8_t)0x80),
    ADC_DIFF_CHANNEL_VAIN3      = ((uint8_t)0xC0),
} ADC_DIFF_CHANNEL_T;

/**@} end of group ADC_Enumerations*/


/** @addtogroup ADC_Macros Macros
  @{
*/

/** ADC Register reset value */
#define  ADC_CSTS_RESET_VALUE      ((uint32_t)0x00)
#define  ADC_CTRL1_RESET_VALUE     ((uint32_t)0x00)
#define  ADC_CTRL2_RESET_VALUE     ((uint32_t)0x00)
#define  ADC_CTRL3_RESET_VALUE     ((uint32_t)0x00)
#define  ADC_CTRL4_RESET_VALUE     ((uint32_t)0x00)
#define  ADC_STD1_RESET_VALUE      ((uint32_t)0x00)
#define  ADC_STD0_RESET_VALUE      ((uint32_t)0x00)
#define  ADC_AWDHT1_RESET_VALUE    ((uint32_t)0xFF)
#define  ADC_AWDHT0_RESET_VALUE    ((uint32_t)0x0F)
#define  ADC_AWDLT1_RESET_VALUE    ((uint32_t)0x00)
#define  ADC_AWDLT0_RESET_VALUE    ((uint32_t)0x00)
#define  ADC_AWDEN1_RESET_VALUE    ((uint32_t)0x00)
#define  ADC_AWDEN0_RESET_VALUE    ((uint32_t)0x00)
#define  ADC_OFFSET_RESET_VALUE    ((uint32_t)0x00)

/**@} end of group ADC_Macros*/

/** @addtogroup ADC_Structure Data Structure
  @{
*/

/**
 * @brief   ADC Config struct definition
 */
typedef struct
{
    ADC_DIV_T div;                  //!< Specifies the ADC clock divider
    uint8_t interrupt;              //!< Specifies the interrupt source.Can be combination of the values @ref ADC_INT_T
    ADC_EXTTRG_T extTrig;           //!< Specifies the external conversion trigger event selection
    ADC_CHANNEL_T channel;          //!< Specifies the channel
    ADC_CONV_MODE_T convMode;       //!< Specifies the conversion mode
    ADC_SCAN_MODE_T scanMode;       //!< Specifies the scan mode
    ADC_DATA_ALIGN_T dataAlign;     //!< Specifies the data alignment mode
} ADC_Config_T;

/**@} end of group ADC_Structure*/

/** @addtogroup ADC_Fuctions Fuctions
  @{
*/

/** ADC reset and configuration */
void ADC_Reset(void);
void ADC_Config(ADC_Config_T *adcConfig);
void ADC_ConfigStructInit(ADC_Config_T *adcConfig);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_SetMode(ADC_MODE_T mode);
void ADC_ConfigConversionMode(ADC_CONV_MODE_T convMode);
void ADC_ConfigScanMode(ADC_SCAN_MODE_T scanMode);
void ADC_ConfigDivider(ADC_DIV_T div);
void ADC_StartConversion(void);
uint16_t ADC_ReadData(void);
void ADC_ConfigDataAlign(ADC_DATA_ALIGN_T dataAlign);
void ADC_SetChannel(ADC_CHANNEL_T channel);
void ADC_SetDiffInputChannel(ADC_DIFF_CHANNEL_T channel);
void ADC_ConfigExternalTrigger(ADC_EXTTRG_T trigger);

/** Delay */
void ADC_EnableDelay(void);
void ADC_DisableDelay(void);

/** Data buffer */
void ADC_EnableDataBuf(void);
void ADC_DisableDataBuf(void);
uint16_t ADC_ReadBufferData(ADC_BUFFER_IDX_T index);

/** Interrupt and flag */
void ADC_EnableInterrupt(uint8_t interrupt);
void ADC_DisableInterrupt(uint8_t interrupt);
uint8_t ADC_ReadStatusFlag(ADC_FLAG_T flag);
void ADC_ClearStatusFlag(ADC_FLAG_T flag);
uint8_t ADC_ReadIntFlag(ADC_INT_FLAG_T flag);
void ADC_ClearIntFlag(ADC_INT_FLAG_T flag);

/** Schmitt trigger */
void ADC_EnableSchmittTrigger(uint16_t channel);
void ADC_DisableSchmittTrigger(uint16_t channel);

/** Analog Watchdog */
void ADC_EnableAnalogWatchdog(uint16_t channel);
void ADC_DisableAnalogWatchdog(uint16_t channel);
void ADC_SetAWDThresholdHigh(uint16_t threshold);
void ADC_SetAWDThresholdLow(uint16_t threshold);
uint8_t ADC_ReadAnalogWatchdogStatus(ADC_CHANNEL_T channel);

/** Compensation */
void ADC_EnableCompensation(void);
void ADC_DisableCompensation(void);
int8_t ADC_ReadOffset(void);
void ADC_SetOffset(int8_t value);

/**@} end of group ADC_Fuctions*/
/**@} end of group ADC_Driver*/
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_ADC_H */

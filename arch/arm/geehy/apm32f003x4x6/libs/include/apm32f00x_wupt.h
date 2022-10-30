/*!
 * @file        apm32f00x_wupt.h
 *
 * @brief       This file contains all functions prototype , enumeration and macros for the Wakeup timer peripheral
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

#ifndef __APM32F00X_WUPT_H
#define __APM32F00X_WUPT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup WUPT_Driver  WUPT Driver
  @{
*/

/** @addtogroup  WUPT_Enumerations Enumerations
  @{
*/

/**
 * @brief   Wakeup timer Timer base definition
 */
typedef enum
{
    AWU_TIMEBASE_NONE,
    AWU_TIMEBASE_250US,
    AWU_TIMEBASE_500US,
    AWU_TIMEBASE_1MS,
    AWU_TIMEBASE_2MS,
    AWU_TIMEBASE_4MS,
    AWU_TIMEBASE_8MS,
    AWU_TIMEBASE_16MS,
    AWU_TIMEBASE_32MS,
    AWU_TIMEBASE_64MS,
    AWU_TIMEBASE_128MS,
    AWU_TIMEBASE_256MS,
    AWU_TIMEBASE_512MS,
    AWU_TIMEBASE_1S,
    AWU_TIMEBASE_2S,
    AWU_TIMEBASE_12S,
    AWU_TIMEBASE_30S,
} WUPT_TIMEBASE_T;

/**@} end of group WUPT_Enumerations*/

/** @addtogroup WUPT_Macros Macros
  @{
*/

/** Wakeup timer reset value */
#define WUPT_CSTS_RESET_VALUE   ((uint32_t)0x00)
#define WUPT_DIV_RESET_VALUE    ((uint32_t)0x3F)
#define WUPT_TBC_RESET_VALUE    ((uint32_t)0x00)

/**@} end of group WUPT_Macros*/

/** @addtogroup WUPT_Fuctions Fuctions
  @{
*/

/** Reset */
void WUPT_Reset(void);

/** Enable or Disable */
void WUPT_Enable(void);
void WUPT_Disable(void);

/** Configuration */
void WUPT_Config(WUPT_TIMEBASE_T timeBase);

/** LIRC Calibration and Measurement */
void WUPT_EnableLIRCMeasurement(void);
void WUPT_DisableLIRCMeasurement(void);
void WUPT_CalibrationLIRC(uint32_t LIRCFreqHz);

/** Idle mode */
void WUPT_EnterIdleMode(void);

/** flag */
uint8_t WUPT_ReadIntFlag(void);

/**@} end of group WUPT_Fuctions*/
/**@} end of group WUPT_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_WUPT_H */

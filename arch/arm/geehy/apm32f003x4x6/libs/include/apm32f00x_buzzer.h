/*!
 * @file        apm32f00x_buzzer.h
 *
 * @brief       This file contains all functions prototype and macros for the BUZZER peripheral
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

#ifndef __APM32F00X_BUZZER_H
#define __APM32F00X_BUZZER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup BUZZER_Driver BUZZER Driver
  @{
*/

/** @addtogroup BUZZER_Enumerations Enumerations
  @{
*/

/**
 * @brief   Output frequency definition
 */
typedef enum
{
    BUZZER_FREQUENCY_1KHZ,
    BUZZER_FREQUENCY_2KHZ,
    BUZZER_FREQUENCY_4KHZ,
} BUZZER_FREQUENCY_T;

/**@} end of group BUZZER_Enumerations*/


/** @addtogroup BUZZER_Macros Macros
  @{
*/

/** Default divider value */
#define BUZZER_DIVIDER_DEFAULT_VALUE    ((uint32_t)0x0B)

/** BUZZER CSTS register reset value */
#define BUZZER_CSTS_RESET_VALUE         ((uint32_t)0x1F)

/**@} end of group BUZZER_Macros*/

/** @addtogroup BUZZER_Fuctions Fuctions
  @{
*/

/** Reset */
void BUZZER_Reset(void);

/** Configuration */
void BUZZER_Config(BUZZER_FREQUENCY_T freq);

/** Enable or Disable */
void BUZZER_Enable(void);
void BUZZER_Disable(void);

/** Calibration */
void BUZZER_CalibrationLIRC(uint32_t LIRCFreqHZ);

/**@} end of group BUZZER_Fuctions*/
/**@} end of group BUZZER_Driver */
/**@} end of group Peripherals_Library */


#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_BUZZER_H */

/*!
 * @file        apm32f00x_misc.h
 *
 * @brief       This file provides all the miscellaneous firmware functions prototype
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

#ifndef __APM32F00X_MISC_H
#define __APM32F00X_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup MISC_Driver MISC Driver
  @{
*/

/** @addtogroup MISC_Enumerations Enumerations
  @{
*/

/**
 * @brief    System low power mode
 */
typedef enum
{
    NVIC_LOWPOER_SEVONPEND          = 0x10,     //!<    Low Power SEV on Pend
    NVIC_LOWPOER_SLEEPDEEP          = 0x04,     //!<    Low Power DEEPSLEEP request
    NVIC_LOWPOER_SLEEPONEXIT        = 0x02      //!<    Low Power Sleep on Exit
} NVIC_LOWPOER_T;

/**@} end of group MISC_Enumerations*/

/** @addtogroup MISC_Fuctions Fuctions
  @{
*/

/** NVIC */
void NVIC_EnableIRQRequest(IRQn_Type irq, uint8_t priority);
void NVIC_DisableIRQRequest(IRQn_Type irq);

/** PMU */
void PMU_EnterWaitMode(void);
void PMU_EnterHaltModeWFI(void);
void PMU_EnterHaltModeWFE(void);

/**@} end of group MISC_Fuctions*/
/**@} end of group MISC_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0X_MISC_H */

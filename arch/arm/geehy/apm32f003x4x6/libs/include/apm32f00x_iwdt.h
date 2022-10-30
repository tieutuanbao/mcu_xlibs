/*!
 * @file        apm32f00x_iwdt.h
 *
 * @brief       This file contains all functions prototypes, enumeration and macros for the IWDT peripheral
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
#ifndef __APM32F00X_IWDG_H
#define __APM32F00X_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup IWDT_Driver IWDT Driver
  @{
*/

/** @addtogroup IWDT_Enumerations Enumerations
  @{
*/

/**
 * @brief   IWDT key definition
 */
typedef enum
{
    IWDT_KEY_REFRESH        = ((uint8_t)0xAA),
    IWDT_KEY_ENABLE         = ((uint8_t)0xCC),
    IWDT_KEY_ACCESS         = ((uint8_t)0x55),
} IWDT_KEY_T;

/**
 * @brief   IWDT divider
 */
typedef enum
{
   IWDT_DIV_4,
   IWDT_DIV_8,
   IWDT_DIV_16,
   IWDT_DIV_32,
   IWDT_DIV_64,
   IWDT_DIV_128,
   IWDT_DIV_256,
} IWDT_DIV_T;

/**@} end of group IWDT_Enumerations*/

/** @addtogroup IWDT_Fuctions Fuctions
  @{
*/

/** Enable IWDT */
void IWDT_Enable(void);

/** Reload Counter IWDT */
void IWDT_ReloadCounter(void);

/** Set reload Counter*/
void IWDT_SetReloadCounter(uint8_t reload);

/** Write Access */
void IWDT_EnableWriteAccess(void);
void IWDT_DisableWriteAccess(void);

/** divider */
void IWDT_SetDivider(IWDT_DIV_T div);

/**@} end of group IWDT_Fuctions*/
/**@} end of group IWDT_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_IWDG_H */

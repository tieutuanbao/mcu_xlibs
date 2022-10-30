/*!
 * @file        apm32f00x_wwdt.h
 *
 * @brief       This file contains all functions prototype and macros for the WWDT peripheral
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

#ifndef __APM32F00X_WWDG_H
#define __APM32F00X_WWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup WWDT_Driver  WWDT Driver
  @{
*/

/** @addtogroup  WWDT_Macros Macros
  @{
*/

/** WWDTEN bit definition */
#define WWDT_WWDTEN_BIT             (BIT7)

/** WWDT Register reset value */
#define WWDT_CTRL_RESET_VALUE       ((uint32_t)0X7F)
#define WWDT_WDDATA_RESET_VALUE     ((uint32_t)0X7F)

/**@} end of group WWDT_Macros*/

/** @addtogroup  WWDT_Fuctions Fuctions
  @{
*/

/** Configuration */
void WWDT_Config(uint8_t couter, uint8_t window);

/** Set and Read Couter */
void WWDT_SetCounter(uint8_t couter);
uint8_t WWDT_ReadCounter(void);

/** Software Reset */
void WWDT_SoftwareReset(void);

/** Set Widow Data */
void WWDT_SetWidowData(uint8_t data);

/**@} end of group WWDT_Fuctions*/
/**@} end of group WWDT_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_WWDG_H */

/*!
 * @file        apm32f00x_wwdt.c
 *
 * @brief       This file contains all the functions for the WWDT peripheral
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

#include "apm32f00x_wwdt.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup WWDT_Driver  WWDT Driver
  @{
*/

/** @addtogroup  WWDT_Fuctions Fuctions
  @{
*/

/*!
 * @brief       WWDT Configuration
 *
 * @param       couter: Specifies the counter
 *
 * @param       window: Specifies the Window Data register value
 *
 * @retval      None
 *
 * @note
 */
void WWDT_Config(uint8_t couter, uint8_t window)
{
    uint32_t reg;

    WWDT->WDDATA = WWDT_WDDATA_RESET_VALUE;

    reg = (uint32_t)(couter | BIT6 | WWDT_WWDTEN_BIT);
    WWDT->CTRL = reg;

    reg = (window | BIT6) & 0x7f;;
    WWDT->WDDATA = reg;
}

/*!
 * @brief       Set counter
 *
 * @param       couter: Specifies the counter to be set
 *
 * @retval      None
 *
 * @note
 */
void WWDT_SetCounter(uint8_t couter)
{
    WWDT->CTRL = (uint32_t)(couter & 0x7f);
}

/*!
 * @brief       Read Counter value
 *
 * @param       None
 *
 * @retval      Retrun Counter value
 *
 * @note
 */
uint8_t WWDT_ReadCounter(void)
{
    return (uint8_t)(WWDT->CTRL & 0x7f);
}

/*!
 * @brief       Generates WWDT reset by software
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WWDT_SoftwareReset(void)
{
    WWDT->CTRL = (uint32_t)(WWDT_WWDTEN_BIT);
}

/*!
 * @brief       Set the Window data
 *
 * @param       data:   Specifies the window data to be set
 *
 * @retval      None
 *
 * @note
 */
void WWDT_SetWidowData(uint8_t data)
{
    uint32_t reg;

    reg = (data | BIT6) & 0x7f;

    WWDT->WDDATA = reg;
}

/**@} end of group WWDT_Fuctions*/
/**@} end of group WWDT_Driver */
/**@} end of group Peripherals_Library*/

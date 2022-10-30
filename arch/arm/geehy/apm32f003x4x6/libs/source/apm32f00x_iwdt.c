/*!
 * @file        apm32f00x_iwdt.c
 *
 * @brief       This file contains all the functions for the IWDT peripheral
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

#include "apm32f00x_iwdt.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup IWDT_Driver IWDT Driver
  @{
*/

/** @addtogroup IWDT_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Enable write access to Divider and Counter Reload registers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void IWDT_EnableWriteAccess(void)
{
    IWDT->KEYWORD = IWDT_KEY_ACCESS;
}

/*!
 * @brief       Disable write access to Divider and Counter Reload registers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void IWDT_DisableWriteAccess(void)
{
    IWDT->KEYWORD = 0;
}

/*!
 * @brief       Divider configuration
 *
 * @param       div: Specifies the divider
 *                    @arg IWDT_DIV_4:    Prescaler divider 4
 *                    @arg IWDT_DIV_8:    Prescaler divider 8
 *                    @arg IWDT_DIV_16:   Prescaler divider 16
 *                    @arg IWDT_DIV_32:   Prescaler divider 32
 *                    @arg IWDT_DIV_64:   Prescaler divider 64
 *                    @arg IWDT_DIV_128:  Prescaler divider 128
 *                    @arg IWDT_DIV_256:  Prescaler divider 256
 *
 * @retval      None
 *
 * @note
 */
void IWDT_SetDivider(IWDT_DIV_T div)
{
    IWDT->PSC = (uint32_t)div;
}


/*!
 * @brief       Set reload counter value
 *
 * @param       reload: Specifies the reload value
 *
 * @retval      None
 *
 * @note
 */
void IWDT_SetReloadCounter(uint8_t reload)
{
    IWDT->CNTRLD = (uint32_t)reload;
}

/*!
 * @brief       Reload Counter IWDT
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void IWDT_ReloadCounter(void)
{
    IWDT->KEYWORD = IWDT_KEY_REFRESH;
}

/*!
 * @brief       Enable IWDT
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void IWDT_Enable(void)
{
    IWDT->KEYWORD = IWDT_KEY_ENABLE;
}

/**@} end of group IWDT_Fuctions*/
/**@} end of group IWDT_Driver */
/**@} end of group Peripherals_Library*/

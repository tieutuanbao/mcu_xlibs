/*!
 * @file        apm32f00x_misc.c
 *
 * @brief       This file provides all the miscellaneous firmware functions.
 *              Include NVIC,SystemTick and Power management
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

#include "apm32f00x_misc.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup MISC_Driver MISC Driver
  @{
*/

/** @addtogroup MISC_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Enable NVIC request
 *
 * @param       irq:        The NVIC interrupt request, detailed in IRQn_Type
 *
 * @param       priority:   Specifies the priority needed to set
 *
 * @retval      None
 *
 * @note
 */
void NVIC_EnableIRQRequest(IRQn_Type irq, uint8_t priority)
{
    NVIC_SetPriority(irq, priority);

    NVIC_EnableIRQ(irq);
}

/*!
 * @brief       Disable NVIC request
 *
 * @param       irq:    The NVIC interrupt request, detailed in IRQn_Type
 *
 * @retval      None
 *
 * @note
 */
void NVIC_DisableIRQRequest(IRQn_Type irq)
{
    NVIC_DisableIRQ(irq);
}

/*!
 * @brief       Enter Wait Mode
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void PMU_EnterWaitMode(void)
{
    SCB->SCR &= (uint32_t)(~(uint32_t)NVIC_LOWPOER_SLEEPDEEP);
    __WFI();
}

/*!
 * @brief       Enter Stop Mode with WFI instruction
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void PMU_EnterHaltModeWFI(void)
{
    SCB->SCR |= NVIC_LOWPOER_SLEEPDEEP;
    __DSB();
    __WFI();
}

/*!
 * @brief       Enter Stop Mode with WFE instruction
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void PMU_EnterHaltModeWFE(void)
{
    SCB->SCR |= NVIC_LOWPOER_SLEEPDEEP;
    __DSB();
    __WFE();
}

/**@} end of group MISC_Fuctions*/
/**@} end of group MISC_Driver */
/**@} end of group Peripherals_Library*/

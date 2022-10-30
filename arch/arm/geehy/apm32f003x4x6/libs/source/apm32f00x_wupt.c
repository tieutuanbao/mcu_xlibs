/*!
 * @file        apm32f00x_wupt.c
 *
 * @brief       This file contains all the functions for the Wakeup timer peripheral
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

#include "apm32f00x_wupt.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup WUPT_Driver  WUPT Driver
  @{
*/

/** @addtogroup WUPT_Variables Variables
  @{
*/

/** Contains the different values to write in the DIV register */
const uint8_t g_dividerTab[17] =
{
    0, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 61, 23, 23, 62
};

/** Contains the different values to write in the TBC register */
const uint8_t g_timeBaseTab[17] =
{
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 12, 14, 15, 15
};

/**@} end of group WUPT_Constant*/

/** @addtogroup  WUPT_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set Wakeup timer peripheral registers to their default reset
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WUPT_Reset(void)
{
    WUPT->CSTS = WUPT_CSTS_RESET_VALUE;
    WUPT->DIV = WUPT_DIV_RESET_VALUE;
    WUPT->TBC = WUPT_TBC_RESET_VALUE;
}

/*!
 * @brief       Config the Wakeup timer peripheral according to the specified parameters.
 *
 * @param       timeBase:   Specifies the time base.
 *                          It can be one of the values of @ref WUPT_TIMEBASE_T
 * @retval      None
 *
 * @note
 */
void WUPT_Config(WUPT_TIMEBASE_T timeBase)
{
    WUPT->TBC = (uint32_t)g_timeBaseTab[(uint32_t)timeBase];

    WUPT->DIV = (uint32_t)g_dividerTab[(uint32_t)timeBase];

    WUPT->CSTS_B.WUPTEN = BIT_SET;
}

/*!
 * @brief       Enable Wakeup timer peripheral
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WUPT_Enable(void)
{
    WUPT->CSTS_B.WUPTEN = BIT_SET;
}

/*!
 * @brief       Disable Wakeup timer peripheral
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WUPT_Disable(void)
{
    WUPT->CSTS_B.WUPTEN = BIT_RESET;
}

/*!
 * @brief       Update DIV register according to the specified LIRC frequency
 *
 * @param       LIRCFreqHz: LIRC frequency
 *
 * @retval      None
 *
 * @note
 */
void WUPT_CalibrationLIRC(uint32_t LIRCFreqHz)
{
    uint16_t freqKhz;
    uint16_t tmp1;
    uint16_t tmp2;
    uint16_t tmp3;

    freqKhz = (uint16_t)(LIRCFreqHz / 1000);

    tmp1 = freqKhz >> 2;

    tmp2 = tmp1 << 2;

    tmp3 = (freqKhz - tmp2) * (1 + (tmp1 << 1));
    if(tmp2 >= tmp3)
    {
        WUPT->DIV = (uint32_t)((tmp1 - 2) & 0x3f);
    }
    else
    {
        WUPT->DIV = (uint32_t)((tmp1 - 1) & 0x3f);
    }
}

/*!
 * @brief       Set wakeup timer in idle mode
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WUPT_EnterIdleMode(void)
{
    WUPT->CSTS_B.WUPTEN = BIT_RESET;

    WUPT->TBC = 0;
}

/*!
 * @brief       Checks whether the Wakeup interrupt has occurred or not
 *
 * @param       None
 *
 * @retval      Status of interrupt flag(SET or RESET)
 *
 * @note
 */
uint8_t WUPT_ReadIntFlag(void)
{
    if(WUPT->CSTS_B.WUPIF)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Enable LIRC frequency Measurement
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WUPT_EnableLIRCMeasurement(void)
{
    WUPT->CSTS_B.CFMEN = BIT_SET;
}

/*!
 * @brief       Disable LIRC frequency Measurement
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WUPT_DisableLIRCMeasurement(void)
{
    WUPT->CSTS_B.CFMEN = BIT_RESET;
}

/**@} end of group WUPT_Fuctions*/
/**@} end of group WUPT_Driver */
/**@} end of group Peripherals_Library*/

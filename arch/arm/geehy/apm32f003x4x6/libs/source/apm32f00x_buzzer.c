/*!
 * @file        apm32f00x_buzzer.c
 *
 * @brief       This file contains all the functions for the BUZZER peripheral
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

#include "apm32f00x_buzzer.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup BUZZER_Driver BUZZER Driver
  @{
*/

/** @addtogroup BUZZER_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the BUZZER peripheral registers to their default reset
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void BUZZER_Reset(void)
{
    BUZZER->CSTS = BUZZER_CSTS_RESET_VALUE;
}

/*!
 * @brief       Config the BUZZER function according to the specified parameters
 *
 * @param       freq:   Specifies the buzzer output frequency
 *
 * @retval      None
 *
 * @note
 */
void BUZZER_Config(BUZZER_FREQUENCY_T freq)
{
    /** Set a default divider value if no calibration is done */
    if(BUZZER->CSTS_B.DIV == 0x1F)
    {
        BUZZER->CSTS_B.DIV = BUZZER_DIVIDER_DEFAULT_VALUE;
    }

    BUZZER->CSTS_B.BOFS = freq;
}

/*!
 * @brief       Enable BUZZER function
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void BUZZER_Enable(void)
{
    BUZZER->CSTS_B.BUZEN = BIT_SET;
}

/*!
 * @brief       Disable BUZZER function
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void BUZZER_Disable(void)
{
    BUZZER->CSTS_B.BUZEN = BIT_RESET;
}

/*!
 * @brief       BUZZER LIRC calibration
 *
 * @param       LIRCFreqHZ: LIRC frequency in HZ
 *
 * @retval      None
 *
 * @note
 */
void BUZZER_CalibrationLIRC(uint32_t LIRCFreqHZ)
{
    uint16_t freqKhz;
    uint16_t tmp1;
    uint16_t tmp2;
    uint16_t tmp3;

    freqKhz = (uint16_t)(LIRCFreqHZ / 1000);

    tmp1 = freqKhz >> 3;

    tmp2 = tmp1 << 3;

    tmp3 = (freqKhz - tmp2) * (1 + (tmp1 << 1));
    if(tmp2 >= tmp3)
    {
        BUZZER->CSTS_B.DIV = (tmp1 - 2) & 0x1f;
    }
    else
    {
        BUZZER->CSTS_B.DIV = (tmp1 - 1) & 0x1f;
    }
}

/**@} end of group BUZZER_Fuctions*/
/**@} end of group BUZZER_Driver */
/**@} end of group Peripherals_Library */

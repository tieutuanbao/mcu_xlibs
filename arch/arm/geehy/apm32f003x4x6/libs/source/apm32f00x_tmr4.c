/*!
 * @file        apm32f00x_tmr4.c
 *
 * @brief       This file contains all the functions for the Timer4 peripheral
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
#include "apm32f00x_tmr4.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup TMR4_Driver TMR4 Driver
  @{
*/

/** @addtogroup TMR4_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the timer4 peripheral registers to their default reset values.
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR4_Reset(void)
{
    TMR4->CTRL1 = TMR4_CTRL1_RESET_VALUE;
    TMR4->CTRL2 = TMR4_CTRL2_RESET_VALUE;
    TMR4->SMC = TMR4_SMC_RESET_VALUE;
    TMR4->INTCTRL = TMR4_INTCTRL_RESET_VALUE;
    TMR4->CNT = TMR4_CNT_RESET_VALUE;
    TMR4->PSC = TMR4_DIV_RESET_VALUE;
    TMR4->AUTORLD = TMR4_AURLD_RESET_VALUE;
    TMR4->STS = TMR4_STS_RESET_VALUE;
}

/*!
 * @brief       Initializes the Timer4 Time Base Unit according to the specified parameters
 *
 * @param       divider:    clock divider value
 *
 * @param       count:      specifies the counter
 *
 * @retval      None
 *
 * @note
 */
void TMR4_ConfigTimerBase(uint8_t divider, uint8_t count)
{
    /** Set the auto reload value */
    TMR4->AUTORLD = (uint32_t)count;

    /** set divide number */
    TMR4->PSC = (uint32_t)divider;
}

/*!
 * @brief       Enable Timer4
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR4_Enable(void)
{
    TMR4->CTRL1_B.CNTEN = BIT_SET;
}

/*!
 * @brief       Disable Timer4
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR4_Disable(void)
{
    TMR4->CTRL1_B.CNTEN = BIT_RESET;
}

/*!
 * @brief       Enable interrupt
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR4_INT_UPDATE:   Update interrupt
 *                          @arg TMR4_INT_TRIGGER:  Trigger interrupt
 * @retval      None
 *
 * @note
 */
void TMR4_EnableInterrupt(uint8_t interrupt)
{
    TMR4->INTCTRL |= (uint32_t)interrupt;
}

/*!
 * @brief       Disable interrupt
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR4_INT_UPDATE:   Update interrupt
 *                          @arg TMR4_INT_TRIGGER:  Trigger interrupt
 * @retval      None
 *
 * @note
 */
void TMR4_DisableInterrupt(uint8_t interrupt)
{
    TMR4->INTCTRL &= (uint32_t)~interrupt;
}


/*!
 * @brief       Set divider
 *
 * @param       divider:   divider
 *
 * @retval      None
 *
 * @note
 */
void TMR4_SetDivider(uint8_t divider)
{
    TMR4->PSC = (uint32_t)(divider & 0x07);
}

/*!
 * @brief       Input Trigger Configuration
 *
 * @param       trigger:    Input Trigger selection
 *
 * @retval      None
 *
 * @note
 */
void TMR4_ConfigInputTrigger(TMR4_ITC_T trigger)
{
    TMR4->SMC_B.ITC = trigger;
}

/*!
 * @brief       Enable Auto-reload buffer(preloaded)
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR4_EnableAutoReloadBuffer(void)
{
    TMR4->CTRL1_B.ARBEN = BIT_SET;
}

/*!
 * @brief       Update source configuration
 *
 * @param       source: Specifies the update source.
 *
 * @retval      None
 *
 * @note
 */
void TMR4_ConfigUpdate(TMR4_UPDATE_SOURCE_T source)
{
    TMR4->CTRL1_B.UES = source & 0x01;
    TMR4->CTRL1_B.NGUE = (source >> 4) & 0x01;
}

/*!
 * @brief       Enable Single pulse mode
 *
 * @retval      None
 *
 * @note
 */
void TMR4_EnableSinglePulseMode(void)
{
    TMR4->CTRL1_B.SPMEN = BIT_SET;
}

/*!
 * @brief       Disable Single pulse mode
 *
 * @retval      None
 *
 * @note
 */
void TMR4_DisableSinglePulseMode(void)
{
    TMR4->CTRL1_B.SPMEN = BIT_RESET;
}

/*!
 * @brief       Disable Auto-reload buffer(preloaded)
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR4_DisableAutoReloadBuffer(void)
{
    TMR4->CTRL1_B.ARBEN = BIT_RESET;
}

/*!
 * @brief       Generating Event by software
 *
 * @param       event:  Event source specified
 *              This parameter can be any combination of the following values:
 *              @arg TMR4_EVENT_UPDATE:     Update evnet
 *              @arg TMR4_EVENT_TRIGGER:    Trigger evnet
 *
 * @retval      None
 *
 * @note
 */
void TMR4_GenerateEvent(uint8_t event)
{
    TMR4->SCEG = (uint32_t)event;
}

/*!
 * @brief       Set counter register value
 *
 * @param       count:  specifies the counter register new value
 *
 * @retval      None
 *
 * @note
 */
void TMR4_SetCounter(uint8_t count)
{
    TMR4->CNT = (uint32_t)count;
}

/*!
 * @brief       Set Auto-Reload register value
 *
 * @param       reload: specifies the Auto-Reload register new value
 *
 * @retval      None
 *
 * @note
 */
void TMR4_SetAutoReloadVaue(uint8_t reload)
{
    TMR4->AUTORLD = (uint32_t)reload;
}

/*!
 * @brief       Read counter register value
 *
 * @param       None
 *
 * @retval      Counter register value
 *
 * @note
 */
uint8_t TMR4_ReadCounter(void)
{
    return (uint8_t)TMR4->CNT;
}

/*!
 * @brief       Read Divider register value
 *
 * @param       None
 *
 * @retval      Divider register value
 *
 * @note
 */
uint8_t TMR4_ReadDivider(void)
{
    return(uint8_t)TMR4->PSC;
}

/*!
 * @brief       Read specifies the flag
 *
 * @param       flag:   specifies the flag
 *                      The parameter can be any combination of the following values:
 *                      @arg TMR4_FLAG_UPDATE:      update flag
 *                      @arg TMR4_FLAG_TRIGGER:     Trigger flag
 *
 * @retval      specifies the flag status.It can be SET or RESET
 *
 * @note
 */
uint8_t TMR4_ReadStatusFlag(uint8_t flag)
{
    uint8_t status;

    status = (uint8_t)(TMR4->STS & flag);

    if(status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear specifies the flag
 *
 * @param       flag:   specifies the flag
 *                      The parameter can be any combination of the following values:
 *                      @arg TMR4_FLAG_UPDATE:      update flag
 *                      @arg TMR4_FLAG_TRIGGER:     Trigger flag
 *
 * @retval      specifies the flag status.It can be SET or RESET
 *
 * @note
 */
void TMR4_ClearStatusFlag(uint8_t flag)
{
    TMR4->STS &= (uint32_t)~flag;
}

/*!
 * @brief       Read interrupt flag
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR4_INT_UPDATE:   Update interrupt
 *                          @arg TMR4_INT_TRIGGER:  Trigger interrupt
 *
 * @retval      Specifies Interrupt source flag status.It Can be SET or RESET
 *
 * @note
 */
uint8_t TMR4_ReadIntFlag(uint8_t interrupt)
{
    uint8_t intEnable;
    uint8_t intStatus;

    intStatus = (uint8_t)(TMR4->STS & interrupt);
    intEnable = (uint8_t)(TMR4->INTCTRL & interrupt);

    if((intStatus == interrupt) && (intEnable == interrupt))
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear interrupt flag
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR4_INT_UPDATE:   Update interrupt
 *                          @arg TMR4_INT_TRIGGER:  Trigger interrupt
 *
 * @retval      None
 *
 * @note
 */
void TMR4_ClearIntFlag(uint8_t interrupt)
{
    TMR4->STS &= (uint32_t)~interrupt;
}

/*!
 * @brief       Slave mode Configuration
 *
 * @param       mode:   Specifies the slave mode
 *
 * @retval      None
 *
 * @note
 */
void TMR4_ConfigSlaveMode(TMR4_SLAVE_MODE_T mode)
{
    TMR4->SMC_B.SMFC = mode;
}

/*!
 * @brief       Master mode Configuration
 *
 * @param       mode:   Specifies the master mode
 *
 * @retval      None
 *
 * @note
 */
void TMR4_ConfigMasterMode(TMR4_MASTER_MODE_T mode)
{
    TMR4->CTRL2_B.MMFC = mode;
}

/*!
 * @brief       Enable master mode
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR4_EnableMasterMode(void)
{
    TMR4->SMC_B.MSMEN = BIT_SET;
}

/*!
 * @brief       Disable master mode
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR4_DisableMasterMode(void)
{
    TMR4->SMC_B.MSMEN = BIT_RESET;
}

/**@} end of group TMR4_Fuctions*/
/**@} end of group TMR4_Driver */
/**@} end of group Peripherals_Library*/

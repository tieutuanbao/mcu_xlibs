/*!
 * @file        apm32f00x_tmr2.c
 *
 * @brief       This file contains all the functions for the Timer2 peripheral
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
#include "apm32f00x_tmr2.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup TMR2_Driver TMR2 Driver
  @{
*/

/** @addtogroup TMR2_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the timer2 peripheral registers to their default reset values.
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR2_Reset(void)
{
    TMR2->CTRL1 = TMR2_CTRL1_RESET_VALUE;
    TMR2->CTRL2 = TMR2_CTRL2_RESET_VALUE;

    TMR2->SMC = TMR2_SMC_RESET_VALUE;
    TMR2->INTCTRL = TMR2_INTCTRL_RESET_VALUE;
    TMR2->STS2 = TMR2_STS2_RESET_VALUE;

    /* Disable channels */
    TMR2->CHCTRL1 = TMR2_CHCTRL1_RESET_VALUE;
    TMR2->CHCTRL2 = TMR2_CHCTRL2_RESET_VALUE;

    /* Configure channels as inputs: it is necessary if lock level is equal to 2 or 3 */
    TMR2->CH1CCM = 1;
    TMR2->CH2CCM = 1;
    TMR2->CH3CCM = 1;

    /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
    TMR2->CHCTRL1 = TMR2_CHCTRL1_RESET_VALUE;
    TMR2->CHCTRL2 = TMR2_CHCTRL2_RESET_VALUE;
    TMR2->CH1CCM = TMR2_CH1CCM_RESET_VALUE;
    TMR2->CH2CCM = TMR2_CH2CCM_RESET_VALUE;
    TMR2->CH3CCM = TMR2_CH3CCM_RESET_VALUE;
    TMR2->CNT1 = TMR2_CNT1_RESET_VALUE;
    TMR2->CNT0 = TMR2_CNT0_RESET_VALUE;
    TMR2->PSC = TMR2_DIV_RESET_VALUE;
    TMR2->AUTORLD1 = TMR2_AURLD1_RESET_VALUE;
    TMR2->AUTORLD0 = TMR2_AURLD0_RESET_VALUE;
    TMR2->CH1CC1 = TMR2_CH1CC1_RESET_VALUE;
    TMR2->CH1CC0 = TMR2_CH1CC0_RESET_VALUE;
    TMR2->CH2CC1 = TMR2_CH2CC1_RESET_VALUE;
    TMR2->CH2CC0 = TMR2_CH2CC0_RESET_VALUE;
    TMR2->CH3CC1 = TMR2_CH3CC1_RESET_VALUE;
    TMR2->CH3CC0 = TMR2_CH3CC0_RESET_VALUE;

    TMR2->STS1 = TMR2_STS1_RESET_VALUE;
}

/*!
 * @brief       Initializes the Timer2 Time Base Unit according to the specified parameters
 *
 * @param       divider:    clock divider value
 *
 * @param       count:      specifies the counter
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ConfigTimerBase(uint8_t divider, uint16_t count)
{
    /** Set the auto reload value */
    TMR2->AUTORLD1 = (uint32_t)(count >> 8) & 0xff;
    TMR2->AUTORLD0 = (uint32_t)(count & 0xff);

    /** set divide number */
    TMR2->PSC = (uint32_t)divider;

    TMR2->SCEG_B.UEG = BIT_SET;
}

/*!
 * @brief       Initializes the Timer2 Channel1 Output Compare according to the specified parameters
 *
 * @param       ocConfigStruct: pointer to a TMR2_OCConfig_T structure that
 *                              contains the configuration information for Timer2 peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ConfigOutputComare1(TMR2_OCConfig_T * ocConfigStruct)
{
    /** OCx ploarity */
    TMR2->CHCTRL1_B.CH1CCP = ocConfigStruct->OCxPolarity;

    /** OCx output Enable/Disable */
    TMR2->CHCTRL1_B.CH1CCEN = ocConfigStruct->OCxOutputState;

    /** compare mode */
    TMR2->CH1OC_B.OCMS = ocConfigStruct->mode;

    /** compare data */
    TMR2->CH1CC1 = (uint32_t)(ocConfigStruct->count >> 8) & 0xff;
    TMR2->CH1CC0 = (uint32_t)(ocConfigStruct->count) & 0xff;
}

/*!
 * @brief       Initializes the Timer2 Channel2 Output Compare according to the specified parameters
 *
 * @param       ocConfigStruct: pointer to a TMR2_OCConfig_T structure that
 *                              contains the configuration information for Timer2 peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ConfigOutputComare2(TMR2_OCConfig_T * ocConfigStruct)
{
    /** OCx ploarity */
    TMR2->CHCTRL1_B.CH2CCP = ocConfigStruct->OCxPolarity;

    /** OCx output Enable/Disable */
    TMR2->CHCTRL1_B.CH2CCEN = ocConfigStruct->OCxOutputState;

    /** compare mode */
    TMR2->CH2OC_B.OCMS = ocConfigStruct->mode;

    /** compare data */
    TMR2->CH2CC1 = (uint32_t)(ocConfigStruct->count >> 8) & 0xff;
    TMR2->CH2CC0 = (uint32_t)(ocConfigStruct->count) & 0xff;
}

/*!
 * @brief       Initializes the Timer2 Channel3 Output Compare according to the specified parameters
 *
 * @param       ocConfigStruct: pointer to a TMR2_OCConfig_T structure that
 *                              contains the configuration information for Timer2 peripheral
 *
 * @retval      None
 *
 * @note
 */

void TMR2_ConfigOutputComare3(TMR2_OCConfig_T * ocConfigStruct)
{
    /** OCx ploarity */
    TMR2->CHCTRL2_B.CH3CCP = ocConfigStruct->OCxPolarity;

    /** OCx output Enable/Disable */
    TMR2->CHCTRL2_B.CH3CCEN = ocConfigStruct->OCxOutputState;

    /** compare mode */
    TMR2->CH3OC_B.OCMS = ocConfigStruct->mode;

    /** compare data */
    TMR2->CH3CC1 = (uint32_t)(ocConfigStruct->count >> 8) & 0xff;
    TMR2->CH3CC0 = (uint32_t)(ocConfigStruct->count) & 0xff;
}

/*!
 * @brief       Initializes the Timer2 Output Compare according to the specified parameters
 *
 * @param       ocConfigStruct: pointer to a TMR2_OCConfig_T structure that
 *                              contains the configuration information for Timer2 peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ConfigOutputCompare(TMR2_OCConfig_T * ocConfigStruct)
{
    if(ocConfigStruct->channel & TMR2_CHANNEL_1)
    {
        TMR2_ConfigOutputComare1(ocConfigStruct);
    }

    if(ocConfigStruct->channel & TMR2_CHANNEL_2)
    {
        TMR2_ConfigOutputComare2(ocConfigStruct);
    }

    if(ocConfigStruct->channel & TMR2_CHANNEL_3)
    {
        TMR2_ConfigOutputComare3(ocConfigStruct);
    }
}

/*!
 * @brief       Fills each ocConfigStruct member with its default value
 *
 * @param       ocConfigStruct: Pointer to a TMR2_OCConfig_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void TMR2_OCStructInit(TMR2_OCConfig_T *ocConfigStruct)
{
    ocConfigStruct->channel = TMR2_CHANNEL_1;
    ocConfigStruct->count = 0xffff;
    ocConfigStruct->mode = TMR2_OC_MODE_TIMING;
    ocConfigStruct->OCxOutputState = TMR2_OC_OUTPUT_DISABLE;
    ocConfigStruct->OCxPolarity = TMR2_OC_POLARITY_HIGH;
}

/*!
 * @brief       Output compare mode configuration
 *
 * @param       channel:    Timer channel.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR2_CHANNEL_1: Channel 1
 *                          @arg TMR2_CHANNEL_2: Channel 2
 *                          @arg TMR2_CHANNEL_3: Channel 3
 *
 * @param       mode:       Output compare mode.
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ConfigOutputCompareMode(uint8_t channel, TMR2_OC_MODE_T mode)
{
    if(channel & TMR2_CHANNEL_1)
    {
        TMR2->CH1OC_B.OCMS = mode;
    }

    if(channel & TMR2_CHANNEL_2)
    {
        TMR2->CH2OC_B.OCMS = mode;
    }

    if(channel & TMR2_CHANNEL_3)
    {
        TMR2->CH3OC_B.OCMS = mode;
    }
}

/*!
 * @brief        Initializes the Timer2 Channel 1 Input Capture according to the specified parameters
 *
 * @param        polarity:  Input capture polarity.
 *
 * @param        selection: Input capture source selection.
 *
 * @param        div:       Input capture divider number.
 *
 * @param        filter:    Input capture filter.
 *
 * @retval       None
 *
 * @note
 */
void TMR2_ConfigInputCapture1(TMR2_IC_POLARITY_T polarity, TMR2_IC_SELECT_T selection,
                                        TMR2_IC_DIV_T div, uint8_t filter)
{
    /** input capture selection */
    TMR2->CH1IC_B.MODESEL = selection;

    /** filter set */
    TMR2->CH1IC_B.ICFC = filter & 0X0F;

    /** input capture divider */
    TMR2->CH1IC_B.IC1PSC = div;

    /** input polarity */
    TMR2->CHCTRL1_B.CH1CCP = polarity;

    /** Enable input */
    TMR2->CHCTRL1_B.CH1CCEN = ENABLE;
}

/*!
 * @brief        Initializes the Timer2 Channel 2 Input Capture according to the specified parameters
 *
 * @param        polarity:  Input capture polarity.
 *
 * @param        selection: Input capture source selection.
 *
 * @param        div:       Input capture divider number.
 *
 * @param        filter:    Input capture filter.
 *
 * @retval       None
 *
 * @note
 */
void TMR2_ConfigInputCapture2(TMR2_IC_POLARITY_T polarity, TMR2_IC_SELECT_T selection,
                                        TMR2_IC_DIV_T div, uint8_t filter)
{
    /** input capture selection */
    TMR2->CH2IC_B.MODESEL = selection;

    /** filter set */
    TMR2->CH2IC_B.ICFC = filter;

    /** input capture divider */
    TMR2->CH2IC_B.IC2PSC = div;

    /** input polarity */
    TMR2->CHCTRL1_B.CH2CCP = polarity;

    /** Enable input */
    TMR2->CHCTRL1_B.CH2CCEN = ENABLE;
}

/*!
 * @brief        Initializes the Timer2 Channel 3 Input Capture according to the specified parameters
 *
 * @param        polarity:  Input capture polarity.
 *
 * @param        selection: Input capture source selection.
 *
 * @param        div:       Input capture divider number.
 *
 * @param        filter:    Input capture filter.
 *
 * @retval       None
 *
 * @note
 */
void TMR2_ConfigInputCapture3(TMR2_IC_POLARITY_T polarity, TMR2_IC_SELECT_T selection,
                                        TMR2_IC_DIV_T div, uint8_t filter)
{
    /** input capture selection */
    TMR2->CH3IC_B.MODESEL = selection;

    /** filter set */
    TMR2->CH3IC_B.ICFC = filter;

    /** input capture divider */
    TMR2->CH3IC_B.IC3PSC = div;

    /** input polarity */
    TMR2->CHCTRL2_B.CH3CCP = polarity;

    /** Enable input */
    TMR2->CHCTRL2_B.CH3CCEN = ENABLE;
}

/*!
 * @brief       Initializes the Timer2  peripheral according to the specified parameters
 *
 * @param       icConfigStruct: pointer to a TMR2_ICConfig_T structure that
 *                              contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ConfigInputCapture(TMR2_ICConfig_T *icConfigStruct)
{
    if(icConfigStruct->channel & TMR2_CHANNEL_1)
    {
        TMR2_ConfigInputCapture1(icConfigStruct->polarity, icConfigStruct->selection,
                                icConfigStruct->div, icConfigStruct->filter);
    }

    if(icConfigStruct->channel & TMR2_CHANNEL_2)
    {
        TMR2_ConfigInputCapture2(icConfigStruct->polarity, icConfigStruct->selection,
                                icConfigStruct->div, icConfigStruct->filter);
    }

    if(icConfigStruct->channel & TMR2_CHANNEL_3)
    {
        TMR2_ConfigInputCapture3(icConfigStruct->polarity, icConfigStruct->selection,
                                icConfigStruct->div, icConfigStruct->filter);
    }
}

/*!
 * @brief       Fills each icConfigStruct member with its default value
 *
 * @param       icConfigStruct: Pointer to a TMR2_ICConfig_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ICStructInit(TMR2_ICConfig_T *icConfigStruct)
{
    icConfigStruct->channel = TMR2_CHANNEL_1;
    icConfigStruct->div = TMR2_IC_DIV_1;
    icConfigStruct->filter = 0;
    icConfigStruct->polarity = TMR2_IC_POLARITY_RISING;
    icConfigStruct->selection = TMR2_IC_SELECT_DIRECTTI;
}

/*!
 * @brief       Configures the TIM1 peripheral PWM Input Mode according to the specified parameters
 *
 * @param       pwmInputConfig: pointer to a TMR2_ICConfig_T structure that
 *                              contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ConfigInputPWM(TMR2_ICConfig_T *pwmInputConfig)
{
    TMR2_IC_POLARITY_T polarityCHxN = TMR2_IC_POLARITY_RISING;
    TMR2_IC_SELECT_T selectionCHxN = TMR2_IC_SELECT_DIRECTTI;

    if(pwmInputConfig->polarity == TMR2_IC_POLARITY_RISING)
    {
        polarityCHxN = TMR2_IC_POLARITY_FALLING;
    }

    if(pwmInputConfig->selection == TMR2_IC_SELECT_DIRECTTI)
    {
        selectionCHxN = TMR2_IC_SELECT_INDIRECTTI;
    }

    if(pwmInputConfig->channel == TMR2_CHANNEL_1)
    {
        TMR2_ConfigInputCapture1(pwmInputConfig->polarity, pwmInputConfig->selection,
                                pwmInputConfig->div, pwmInputConfig->filter);

        TMR2_ConfigInputCapture2(polarityCHxN, selectionCHxN,
                                pwmInputConfig->div, pwmInputConfig->filter);
    }
    else if(pwmInputConfig->channel == TMR2_CHANNEL_2)
    {
        TMR2_ConfigInputCapture2(pwmInputConfig->polarity, pwmInputConfig->selection,
                                pwmInputConfig->div, pwmInputConfig->filter);

        TMR2_ConfigInputCapture1(polarityCHxN, selectionCHxN,
                                pwmInputConfig->div, pwmInputConfig->filter);
    }
}

/*!
 * @brief       Enable Timer2
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR2_Enable(void)
{
    TMR2->CTRL1_B.CNTEN = BIT_SET;
}

/*!
 * @brief       Disable Timer2
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR2_Disable(void)
{
    TMR2->CTRL1_B.CNTEN = BIT_RESET;
}

/*!
 * @brief       Enable interrupt
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR2_INT_UPDATE:   Update interrupt
 *                          @arg TMR2_INT_CH1CC:    Channel 1 Compare/Capture interrupt
 *                          @arg TMR2_INT_CH2CC:    Channel 2 Compare/Capture interrupt
 *                          @arg TMR2_INT_CH3CC:    Channel 3 Compare/Capture interrupt
 *                          @arg TMR2_INT_TRIGGER:  Trigger interrupt
 * @retval      None
 *
 * @note
 */
void TMR2_EnableInterrupt(uint8_t interrupt)
{
    TMR2->INTCTRL |= (uint32_t)interrupt;
}

/*!
 * @brief       Disable interrupt
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR2_INT_UPDATE:   Update interrupt
 *                          @arg TMR2_INT_CH1CC:    Channel 1 Compare/Capture interrupt
 *                          @arg TMR2_INT_CH2CC:    Channel 2 Compare/Capture interrupt
 *                          @arg TMR2_INT_CH3CC:    Channel 3 Compare/Capture interrupt
 *                          @arg TMR2_INT_TRIGGER:  Trigger interrupt
 * @retval      None
 *
 * @note
 */
void TMR2_DisableInterrupt(uint8_t interrupt)
{
    TMR2->INTCTRL &= (uint32_t)~interrupt;
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
void TMR2_SetDivider(uint8_t divider)
{
    TMR2->PSC = (uint32_t)(divider & 0x0f);
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
void TMR2_ConfigInputTrigger(TMR2_ITC_T trigger)
{
    TMR2->SMC_B.ITC = trigger;
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
void TMR2_EnableAutoReloadBuffer(void)
{
    TMR2->CTRL1_B.ARBEN = BIT_SET;
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
void TMR2_DisableAutoReloadBuffer(void)
{
    TMR2->CTRL1_B.ARBEN = BIT_RESET;
}

/*!
 * @brief       Enable Specified Channel output compare buffer(preload)
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR2_CHANNEL_1:    Channel 1
 *                          @arg TMR2_CHANNEL_2:    Channel 2
 *                          @arg TMR2_CHANNEL_3:    Channel 3
 *
 * @retval      None
 *
 * @note
 */
void TMR2_EnableOutputCompareBuffer(uint8_t channel)
{
    if(channel & TMR2_CHANNEL_1)
    {
        TMR2->CH1OC_B.OCBEN = BIT_SET;
    }

    if(channel & TMR2_CHANNEL_2)
    {
        TMR2->CH2OC_B.OCBEN = BIT_SET;
    }

    if(channel & TMR2_CHANNEL_3)
    {
        TMR2->CH3OC_B.OCBEN = BIT_SET;
    }
}

/*!
 * @brief       Disable Specified Channel output compare buffer(preload)
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR2_CHANNEL_1:    Channel 1
 *                          @arg TMR2_CHANNEL_2:    Channel 2
 *                          @arg TMR2_CHANNEL_3:    Channel 3
 *
 * @retval      None
 *
 * @note
 */
void TMR2_DisableOutputCompareBuffer(uint8_t channel)
{
    if(channel & TMR2_CHANNEL_1)
    {
        TMR2->CH1OC_B.OCBEN = BIT_RESET;
    }

    if(channel & TMR2_CHANNEL_2)
    {
        TMR2->CH2OC_B.OCBEN = BIT_RESET;
    }

    if(channel & TMR2_CHANNEL_3)
    {
        TMR2->CH3OC_B.OCBEN = BIT_RESET;
    }
}

/*!
 * @brief       Generating Event by software
 *
 * @param       event:  Event source specified
 *              This parameter can be any combination of the following values:
 *              @arg TMR2_EVENT_UPDATE:     Update evnet
 *              @arg TMR2_EVENT_CH1CC:      Channel 1 Compare/Capture evnet
 *              @arg TMR2_EVENT_CH2CC:      Channel 2 Compare/Capture evnet
 *              @arg TMR2_EVENT_CH3CC:      Channel 3 Compare/Capture evnet
 *              @arg TMR2_EVENT_TRIGGER:    Trigger evnet
 *
 * @retval      None
 *
 * @note
 */
void TMR2_GenerateEvent(uint8_t event)
{
    TMR2->SCEG = (uint32_t)event;
}

/*!
 * @brief       Specified Channel output compare polarity configuration
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR2_CHANNEL_1:    Channel 1
 *                          @arg TMR2_CHANNEL_2:    Channel 2
 *                          @arg TMR2_CHANNEL_3:    Channel 3
 *
 * @param       polarity:   Specifies the polarity
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ConfigOutputComparePolarity(uint8_t channel, TMR2_OC_POLARITY_T polarity)
{
    if(channel & TMR2_CHANNEL_1)
    {
        TMR2->CHCTRL1_B.CH1CCP = polarity;
    }

    if(channel & TMR2_CHANNEL_2)
    {
        TMR2->CHCTRL1_B.CH2CCP = polarity;
    }

    if(channel & TMR2_CHANNEL_3)
    {
        TMR2->CHCTRL2_B.CH3CCP = polarity;
    }
}

/*!
 * @brief       Enable specified Channel Compare/Capture output
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR2_CHANNEL_1:    Channel 1
 *                          @arg TMR2_CHANNEL_2:    Channel 2
 *                          @arg TMR2_CHANNEL_3:    Channel 3
 *
 * @retval      None
 *
 * @note
 */
void TMR2_EnableCompareCapture( uint8_t channel)
{
    if(channel & TMR2_CHANNEL_1)
    {
        TMR2->CHCTRL1_B.CH1CCEN = ENABLE;
    }

    if(channel & TMR2_CHANNEL_2)
    {
        TMR2->CHCTRL1_B.CH2CCEN = ENABLE;
    }

    if(channel & TMR2_CHANNEL_3)
    {
        TMR2->CHCTRL2_B.CH3CCEN = ENABLE;
    }
}

/*!
 * @brief       Disable specified Channel Compare/Capture output
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR2_CHANNEL_1:    Channel 1
 *                          @arg TMR2_CHANNEL_2:    Channel 2
 *                          @arg TMR2_CHANNEL_3:    Channel 3
 *
 * @retval      None
 *
 * @note
 */
void TMR2_DisableCompareCapture(uint8_t channel)
{
    if(channel & TMR2_CHANNEL_1)
    {
        TMR2->CHCTRL1_B.CH1CCEN = DISABLE;
    }

    if(channel & TMR2_CHANNEL_2)
    {
        TMR2->CHCTRL1_B.CH2CCEN = DISABLE;
    }

    if(channel & TMR2_CHANNEL_3)
    {
        TMR2->CHCTRL2_B.CH3CCEN = DISABLE;
    }
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
void TMR2_SetCounter(uint16_t count)
{
    TMR2->CNT1 = (uint32_t)((count >> 8) & 0xff);
    TMR2->CNT0 = (uint32_t)(count & 0xff);
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
void TMR2_ConfigUpdate(TMR2_UPDATE_SOURCE_T source)
{
    TMR2->CTRL1_B.UES = source & 0x01;
    TMR2->CTRL1_B.NGUE = (source >> 4) & 0x01;
}

/*!
 * @brief       Enable Single pulse mode
 *
 * @retval      None
 *
 * @note
 */
void TMR2_EnableSinglePulseMode(void)
{
    TMR2->CTRL1_B.SPMEN = BIT_SET;
}

/*!
 * @brief       Disable Single pulse mode
 *
 * @retval      None
 *
 * @note
 */
void TMR2_DisableSinglePulseMode(void)
{
    TMR2->CTRL1_B.SPMEN = BIT_RESET;
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
void TMR2_SetAutoReloadVaue(uint16_t reload)
{
    TMR2->AUTORLD1 = (uint32_t)((reload >> 8) & 0xff);
    TMR2->AUTORLD0 = (uint32_t)(reload & 0xff);
}

/*!
 * @brief       Set specified Channel Compare/Capture register value
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR2_CHANNEL_1:    Channel 1
 *                          @arg TMR2_CHANNEL_2:    Channel 2
 *                          @arg TMR2_CHANNEL_3:    Channel 3
 *
 * @param       compare:    specifies the Channel Capture Compare register value
 *
 * @retval      None
 *
 * @note
 */
void TMR2_SetCompareCapture(uint8_t channel, uint16_t compare)
{
    if(channel & TMR2_CHANNEL_1)
    {
        TMR2->CH1CC1 = (uint32_t)((compare >> 8) & 0xff);
        TMR2->CH1CC0 = (uint32_t)(compare & 0xff);
    }

    if(channel & TMR2_CHANNEL_2)
    {
        TMR2->CH2CC1 = (uint32_t)((compare >> 8) & 0xff);
        TMR2->CH2CC0 = (uint32_t)(compare & 0xff);
    }

    if(channel & TMR2_CHANNEL_3)
    {
        TMR2->CH3CC1 = (uint32_t)((compare >> 8) & 0xff);
        TMR2->CH3CC0 = (uint32_t)(compare & 0xff);
    }
}

/*!
 * @brief       Read Channel 1 Capture Compare register value
 *
 * @param       None
 *
 * @retval      Channel 1 Capture Compare register value
 *
 * @note
 */
uint16_t TMR2_ReadCapture1(void)
{
    uint16_t capture = 0;

    capture = (uint16_t)TMR2->CH1CC1;
    capture <<= 8;
    capture |= (uint16_t)TMR2->CH1CC0;

    return capture;
}

/*!
 * @brief       Read Channel 2 Capture Compare register value
 *
 * @param       None
 *
 * @retval      Channel 2 Capture Compare register value
 *
 * @note
 */
uint16_t TMR2_ReadCapture2(void)
{
    uint16_t capture = 0;

    capture = (uint16_t)TMR2->CH2CC1;
    capture <<= 8;
    capture |= (uint16_t)TMR2->CH2CC0;

    return capture;
}

/*!
 * @brief       Read Channel 3 Capture Compare register value
 *
 * @param       None
 *
 * @retval      Channel 3 Capture Compare register value
 *
 * @note
 */
uint16_t TMR2_ReadCapture3(void)
{
    uint16_t capture = 0;

    capture = (uint16_t)TMR2->CH3CC1;
    capture <<= 8;
    capture |= (uint16_t)TMR2->CH3CC0;

    return capture;
}

/*!
 * @brief       Read specified Channel Compare/Capture register value
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be one of the following values:
 *                          @arg TMR2_CHANNEL_1:    Channel 1
 *                          @arg TMR2_CHANNEL_2:    Channel 2
 *                          @arg TMR2_CHANNEL_3:    Channel 3
 *
 * @retval      Capture Compare register value
 *
 * @note
 */
uint16_t TMR2_ReadCompareCapture(TMR2_CHANNEL_T channel)
{
    if(channel & TMR2_CHANNEL_1)
    {
        return TMR2_ReadCapture1();
    }

    else if(channel & TMR2_CHANNEL_2)
    {
        return TMR2_ReadCapture2();
    }

    else
    {
        return TMR2_ReadCapture3();
    }
}

/*!
 * @brief       Set specified Channel Input Capture divider
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR2_CHANNEL_1:    Channel 1
 *                          @arg TMR2_CHANNEL_2:    Channel 2
 *                          @arg TMR2_CHANNEL_3:    Channel 3
 *
 * @param       divider:    specifies the channel Input Capture divider
 *
 * @retval      None
 *
 * @note
 */
void TMR2_SetInputCaptureDivider(uint8_t channel, TMR2_IC_DIV_T divider)
{
    if(channel & TMR2_CHANNEL_1)
    {
        TMR2->CH1IC_B.IC1PSC = divider;
    }

    if(channel & TMR2_CHANNEL_2)
    {
        TMR2->CH2IC_B.IC2PSC= divider;
    }

    if(channel & TMR2_CHANNEL_3)
    {
        TMR2->CH3IC_B.IC3PSC = divider;
    }
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
uint16_t TMR2_ReadCounter(void)
{
    uint16_t capture = 0;

    capture = (uint16_t)TMR2->CNT1;
    capture <<= 8;
    capture |= (uint16_t)TMR2->CNT0;

    return capture;
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
uint8_t TMR2_ReadDivider(void)
{
    return(uint8_t)TMR2->PSC;
}

/*!
 * @brief       Read specifies the flag
 *
 * @param       flag:   specifies the flag
 *                      The parameter can be any combination of the following values:
 *                      @arg TMR2_FLAG_UPDATE:      update flag
 *                      @arg TMR2_FLAG_CH1CC:       Channel 1 Compare/Capture flag
 *                      @arg TMR2_FLAG_CH2CC:       Channel 2 Compare/Capture
 *                      @arg TMR2_FLAG_CH3CC:       Channel 3 Compare/Capture
 *                      @arg TMR2_FLAG_TRIGGER:     Trigger flag
 *                      @arg TMR2_FLAG_CH1RCF:      Channel 1 repetition capture flag
 *                      @arg TMR2_FLAG_CH2RCF:      Channel 2 repetition capture flag
 *                      @arg TMR2_FLAG_CH3RCF:      Channel 3 repetition capture flag
 *
 * @retval      specifies the flag status.It can be SET or RESET
 *
 * @note
 */
uint8_t TMR2_ReadStatusFlag(uint16_t flag)
{
    uint8_t flag1;
    uint8_t flag2;
    uint8_t status1 = 0;
    uint8_t status2 = 0;

    flag1 = (uint8_t)(flag & 0XFF);
    flag2 = (uint8_t)((flag >> 8) & 0xff);

    if(flag1)
    {
        status1 = (uint8_t)(TMR2->STS1 & flag1);
    }

    if(flag2)
    {
        status2 = (uint8_t)(TMR2->STS2 & flag2);
    }

    if((flag1 == status1) && (flag2 == status2))
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
 *                      @arg TMR2_FLAG_UPDATE:      update flag
 *                      @arg TMR2_FLAG_CH1CC:       Channel 1 Compare/Capture flag
 *                      @arg TMR2_FLAG_CH2CC:       Channel 2 Compare/Capture
 *                      @arg TMR2_FLAG_CH3CC:       Channel 3 Compare/Capture
 *                      @arg TMR2_FLAG_TRIGGER:     Trigger flag
 *                      @arg TMR2_FLAG_CH1RCF:      Channel 1 repetition capture flag
 *                      @arg TMR2_FLAG_CH2RCF:      Channel 2 repetition capture flag
 *                      @arg TMR2_FLAG_CH3RCF:      Channel 3 repetition capture flag
 *
 * @retval      specifies the flag status.It can be SET or RESET
 *
 * @note
 */
void TMR2_ClearStatusFlag(uint16_t flag)
{
    uint8_t flag1;
    uint8_t flag2;

    flag1 = (uint8_t)(flag & 0XFF);
    flag2 = (uint8_t)((flag >> 8) & 0xff);

    if(flag1)
    {
        TMR2->STS1 &= (uint32_t)~flag1;
    }

    if(flag2)
    {
        TMR2->STS2 &= (uint32_t)~flag2;
    }
}

/*!
 * @brief       Read interrupt flag
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR2_INT_UPDATE:   Update interrupt
 *                          @arg TMR2_INT_CH1CC:    Channel 1 Compare/Capture interrupt
 *                          @arg TMR2_INT_CH2CC:    Channel 2 Compare/Capture interrupt
 *                          @arg TMR2_INT_CH3CC:    Channel 3 Compare/Capture interrupt
 *                          @arg TMR2_INT_TRIGGER:  Trigger interrupt
 *
 * @retval      Specifies Interrupt source flag status.It Can be SET or RESET
 *
 * @note
 */
uint8_t TMR2_ReadIntFlag(uint8_t interrupt)
{
    uint8_t intEnable;
    uint8_t intStatus;

    intStatus = (uint8_t)(TMR2->STS1 & interrupt);
    intEnable = (uint8_t)(TMR2->INTCTRL & interrupt);

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
 *                          @arg TMR2_INT_UPDATE:   Update interrupt
 *                          @arg TMR2_INT_CH1CC:    Channel 1 Compare/Capture interrupt
 *                          @arg TMR2_INT_CH2CC:    Channel 2 Compare/Capture interrupt
 *                          @arg TMR2_INT_CH3CC:    Channel 3 Compare/Capture interrupt
 *                          @arg TMR2_INT_TRIGGER:  Trigger interrupt
 *
 * @retval      None
 *
 * @note
 */
void TMR2_ClearIntFlag(uint8_t interrupt)
{
    TMR2->STS1 &= (uint32_t)~interrupt;
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
void TMR2_ConfigSlaveMode(TMR2_SLAVE_MODE_T mode)
{
    TMR2->SMC_B.SMFC = mode;
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
void TMR2_ConfigMasterMode(TMR2_MASTER_MODE_T mode)
{
    TMR2->CTRL2_B.MMFC = mode;
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
void TMR2_EnableMasterMode(void)
{
    TMR2->SMC_B.MSMEN = BIT_SET;
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
void TMR2_DisableMasterMode(void)
{
    TMR2->SMC_B.MSMEN = BIT_RESET;
}

/**@} end of group TMR2_Fuctions*/
/**@} end of group TMR2_Driver */
/**@} end of group Peripherals_Library*/

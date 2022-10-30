/*!
 * @file        apm32f00x_tmr1.c
 *
 * @brief       This file contains all the functions for the Timer1 peripheral
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
#include "apm32f00x_tmr1.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup TMR1_Driver TMR1 Driver
  @{
*/

/** @addtogroup TMR1_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the timer1 peripheral registers to their default reset values.
 *
 * @param       tmr:  timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_Reset(TMR1_T *tmr)
{
    tmr->CTRL1 = TMR1_CTRL1_RESET_VALUE;
    tmr->CTRL2 = TMR1_CTRL2_RESET_VALUE;

    tmr->SMC = TMR1_SMC_RESET_VALUE;
    tmr->ETC = TMR1_ETC_RESET_VALUE;
    tmr->INTCTRL = TMR1_INTCTRL_RESET_VALUE;
    tmr->STS2 = TMR1_STS1_RESET_VALUE;

    /* Disable channels */
    tmr->CHCTRL1 = TMR1_CHCTRL1_RESET_VALUE;
    tmr->CHCTRL2 = TMR1_CHCTRL2_RESET_VALUE;

    /* Configure channels as inputs: it is necessary if lock level is equal to 2 or 3 */
    tmr->CH1CCM = 1;
    tmr->CH2CCM = 1;
    tmr->CH3CCM = 1;
    tmr->CH4CCM = 1;

    /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
    tmr->CHCTRL1 = TMR1_CHCTRL1_RESET_VALUE;
    tmr->CHCTRL2 = TMR1_CHCTRL2_RESET_VALUE;
    tmr->CH1CCM = TMR1_CH1CCM_RESET_VALUE;
    tmr->CH2CCM = TMR1_CH2CCM_RESET_VALUE;
    tmr->CH3CCM = TMR1_CH3CCM_RESET_VALUE;
    tmr->CH4CCM = TMR1_CH4CCM_RESET_VALUE;
    tmr->CNT1 = TMR1_CNT1_RESET_VALUE;
    tmr->CNT0 = TMR1_CNT0_RESET_VALUE;
    tmr->PSC1 = TMR1_DIV1_RESET_VALUE;
    tmr->PSC0 = TMR1_DIV0_RESET_VALUE;
    tmr->AUTORLD1 = TMR1_AUTORLD1_RESET_VALUE;
    tmr->AUTORLD0 = TMR1_AUTORLD0_RESET_VALUE;
    tmr->CH1CC1 = TMR1_CH1CC1_RESET_VALUE;
    tmr->CH1CC0 = TMR1_CH1CC0_RESET_VALUE;
    tmr->CH2CC1 = TMR1_CH2CC1_RESET_VALUE;
    tmr->CH2CC0 = TMR1_CH2CC0_RESET_VALUE;
    tmr->CH3CC1 = TMR1_CH3CC1_RESET_VALUE;
    tmr->CH3CC0 = TMR1_CH3CC0_RESET_VALUE;
    tmr->CH4CC1 = TMR1_CH4CC1_RESET_VALUE;
    tmr->CH4CC0 = TMR1_CH4CC0_RESET_VALUE;
    tmr->ISO = TMR1_ISO_RESET_VALUE;
    tmr->SCEG = 1;
    tmr->DTS = TMR1_DTS_RESET_VALUE;
    tmr->BRKCTRL = TMR1_BRKCTRL_RESET_VALUE;
    tmr->REPCNT = TMR1_REPCNT_RESET_VALUE;
    tmr->STS1 = TMR1_STS1_RESET_VALUE;

    if(tmr == TMR1A)
    {
        tmr->CHEN = TMR1_CHEN_RESET_VALUE;
    }
}

/*!
 * @brief       Initializes the Timer1 Time Base Unit according to the specified parameters
 *
 * @param       tmr:                    timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       timeBaseConfigStruct:   pointer to a TMR1_TimeBaseConfig_T structure that
 *                                      contains the configuration information for the
 *                                      specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigTimerBase(TMR1_T *tmr, TMR1_TimeBaseConfig_T *timeBaseConfigStruct)
{
    /** Set the auto reload value */
    tmr->AUTORLD1 = (uint32_t)(timeBaseConfigStruct->count >> 8) & 0xff;
    tmr->AUTORLD0 = (uint32_t)timeBaseConfigStruct->count & 0xff;

    /** set divide number */
    tmr->PSC1 = (uint32_t)(timeBaseConfigStruct->divider >> 8) & 0xff;
    tmr->PSC0 = (uint32_t)timeBaseConfigStruct->divider & 0xff;

    /** set coute mode */
    tmr->CTRL1_B.CNTMODE = timeBaseConfigStruct->cntMode & 0X0F;
    /** set count direction */
    tmr->CTRL1_B.CNTDIR = (timeBaseConfigStruct->cntMode >> 4) & 0XF;

    /** set Repetition Counter */
    tmr->REPCNT = (uint32_t)timeBaseConfigStruct->repetitionCount;

    /** Generate an update event to reload the Prescaler and the divide counter values immediately */
    tmr->SCEG_B.UEG = BIT_SET;
}

/*!
 * @brief       Fills each timeBaseConfigStruct member with its default value
 *
 * @param       timeBaseConfigStruct:   Pointer to a TMR1_TimeBaseConfig_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigTimeBaseStructInit(TMR1_TimeBaseConfig_T *timeBaseConfigStruct)
{
    timeBaseConfigStruct->cntMode = TMR1_CNT_MODE_UP;
    timeBaseConfigStruct->divider = 0;
    timeBaseConfigStruct->count = 0xffff;
    timeBaseConfigStruct->repetitionCount = 0;
}

/*!
 * @brief       Enable timer channel
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      None
 *
 * @note        Only TMR1A can Enable or Disable channel
 */
void TMR1_EnableChannel(TMR1_T *tmr, uint8_t channel)
{
    if(tmr == TMR1A)
    {
        tmr->CHEN |= channel;
    }
}

/*!
 * @brief       Disable timer channel
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      None
 *
 * @note        Only TMR1A can Enable or Disable channel
 */
void TMR1_DisableChannel(TMR1_T *tmr, uint8_t channel)
{
    if(tmr == TMR1A)
    {
        tmr->CHEN &= (uint32_t)~channel;
    }
}

/*!
 * @brief       Initializes the TIMER1/TIMER1A Channel1 Output Compare according to the specified parameters
 *
 * @param       tmr:            Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       ocConfigStruct: pointer to a TMR1_OCConfig_T structure that
 *                              contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigOutputComare1(TMR1_T *tmr, TMR1_OCConfig_T * ocConfigStruct)
{
    /** OCx ploarity */
    tmr->CHCTRL1_B.CH1CCP = ocConfigStruct->OCxPolarity;
    /** OCxN ploarity */
    tmr->CHCTRL1_B.CH1OCNP = ocConfigStruct->OCxNPolarity;

    /** OCx output Enable/Disable */
    tmr->CHCTRL1_B.CH1CCEN = ocConfigStruct->OCxOutputState;
    /** OCxN output Enable/Disable */
    tmr->CHCTRL1_B.CH1OCNEN = ocConfigStruct->OCxNOutputState;

    /** compare mode */
    tmr->CH1OC_B.OCMS = ocConfigStruct->mode;

    /** OCx idle state */
    tmr->ISO_B.CH1ISO = ocConfigStruct->OCxIdleState;
    /** OCxN idle state */
    tmr->ISO_B.CH1NISO = ocConfigStruct->OCxNIdleState;

    /** compare data */
    tmr->CH1CC1 = (uint32_t)(ocConfigStruct->count >> 8) & 0xff;
    tmr->CH1CC0 = (uint32_t)(ocConfigStruct->count) & 0xff;
}

/*!
 * @brief       Initializes the TIMER1/TIMER1A Channel2 Output Compare according to the specified parameters
 *
 * @param       tmr:            Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       ocConfigStruct: pointer to a TMR1_OCConfig_T structure that
 *                              contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigOutputComare2(TMR1_T *tmr, TMR1_OCConfig_T * ocConfigStruct)
{
    /** OCx ploarity */
    tmr->CHCTRL1_B.CH2CCP = ocConfigStruct->OCxPolarity;
    /** OCxN ploarity */
    tmr->CHCTRL1_B.CH2OCNP = ocConfigStruct->OCxNPolarity;

    /** OCx output Enable/Disable */
    tmr->CHCTRL1_B.CH2CCEN = ocConfigStruct->OCxOutputState;
    /** OCxN output Enable/Disable */
    tmr->CHCTRL1_B.CH2OCNEN = ocConfigStruct->OCxNOutputState;

    /** compare mode */
    tmr->CH2OC_B.OCMS = ocConfigStruct->mode;

    /** OCx idle state */
    tmr->ISO_B.CH2ISO = ocConfigStruct->OCxIdleState;
    /** OCxN idle state */
    tmr->ISO_B.CH2NISO = ocConfigStruct->OCxNIdleState;

    /** compare data */
    tmr->CH2CC1 = (uint32_t)(ocConfigStruct->count >> 8) & 0xff;
    tmr->CH2CC0 = (uint32_t)(ocConfigStruct->count) & 0xff;
}

/*!
 * @brief       Initializes the TIMER1/TIMER1A Channel3 Output Compare according to the specified parameters
 *
 * @param       tmr:            Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       ocConfigStruct: pointer to a TMR1_OCConfig_T structure that
 *                              contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigOutputComare3(TMR1_T *tmr, TMR1_OCConfig_T * ocConfigStruct)
{
    /** OCx ploarity */
    tmr->CHCTRL2_B.CH3CCP = ocConfigStruct->OCxPolarity;

    /** OCx output Enable/Disable */
    tmr->CHCTRL2_B.CH3CCEN = ocConfigStruct->OCxOutputState;

    /** compare mode */
    tmr->CH3OC_B.OCMS = ocConfigStruct->mode;

    /** OCx idle state */
    tmr->ISO_B.CH3ISO = ocConfigStruct->OCxIdleState;

    /** compare data */
    tmr->CH3CC1 = (uint32_t)(ocConfigStruct->count >> 8) & 0xff;
    tmr->CH3CC0 = (uint32_t)(ocConfigStruct->count) & 0xff;
}

/*!
 * @brief       Initializes the TIMER1/TIMER1A Channel4 Output Compare according to the specified parameters
 *
 * @param       tmr:                Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       ocConfigStruct:     pointer to a TMR1_OCConfig_T structure that
 *                                  contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @see
 *
 * @note
 */
void TMR1_ConfigOutputComare4(TMR1_T *tmr, TMR1_OCConfig_T * ocConfigStruct)
{
    /** OCx ploarity */
    tmr->CHCTRL2_B.CH4CCP = ocConfigStruct->OCxPolarity;

    /** OCx output Enable/Disable */
    tmr->CHCTRL2_B.CH4CCEN = ocConfigStruct->OCxOutputState;

    /** compare mode */
    tmr->CH4OC_B.OCMS = ocConfigStruct->mode;

    /** OCx idle state */
    tmr->ISO_B.CH4ISO = ocConfigStruct->OCxIdleState;

    /** compare data */
    tmr->CH4CC1 = (uint32_t)(ocConfigStruct->count >> 8) & 0xff;
    tmr->CH4CC0 = (uint32_t)(ocConfigStruct->count) & 0xff;
}

/*!
 * @brief       Initializes the TIMER1/TIMER1A Output Compare according to the specified parameters
 *
 * @param       tmr:            Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       ocConfigStruct: pointer to a TMR1_OCConfig_T structure that
 *                              contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigOutputCompare(TMR1_T *tmr, TMR1_OCConfig_T * ocConfigStruct)
{
    TMR1_EnableChannel(tmr, ocConfigStruct->channel);

    if(ocConfigStruct->channel & TMR1_CHANNEL_1)
    {
        TMR1_ConfigOutputComare1(tmr, ocConfigStruct);
    }

    if(ocConfigStruct->channel & TMR1_CHANNEL_2)
    {
        TMR1_ConfigOutputComare2(tmr, ocConfigStruct);
    }

    if(ocConfigStruct->channel & TMR1_CHANNEL_3)
    {
        TMR1_ConfigOutputComare3(tmr, ocConfigStruct);
    }

    if(ocConfigStruct->channel & TMR1_CHANNEL_4)
    {
        TMR1_ConfigOutputComare4(tmr, ocConfigStruct);
    }
}

/*!
 * @brief       Fills each ocConfigStruct member with its default value
 *
 * @param       ocConfigStruct: Pointer to a TMR1_OCConfig_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void TMR1_OCStructInit(TMR1_OCConfig_T *ocConfigStruct)
{
    ocConfigStruct->channel = TMR1_CHANNEL_1;
    ocConfigStruct->count = 0xffff;
    ocConfigStruct->mode = TMR1_OC_MODE_TIMING;
    ocConfigStruct->OCxIdleState = TMR1_OC_IDLE_RESET;
    ocConfigStruct->OCxNIdleState = TMR1_OC_IDLE_RESET;
    ocConfigStruct->OCxNOutputState = TMR1_OC_OUTPUT_DISABLE;
    ocConfigStruct->OCxOutputState = TMR1_OC_OUTPUT_DISABLE;
    ocConfigStruct->OCxNPolarity = TMR1_OC_POLARITY_HIGH;
    ocConfigStruct->OCxPolarity = TMR1_OC_POLARITY_HIGH;
}

/*!
 * @brief       Output compare mode configuration
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer channel.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR1_CHANNEL_1: Channel 1
 *                          @arg TMR1_CHANNEL_2: Channel 2
 *                          @arg TMR1_CHANNEL_3: Channel 3
 *                          @arg TMR1_CHANNEL_4: Channel 4
 *
 * @param       mode:       Output compare mode.
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigOutputCompareMode(TMR1_T * tmr, uint8_t channel, TMR1_OC_MODE_T mode)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CH1OC_B.OCMS = mode;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CH2OC_B.OCMS = mode;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CH3OC_B.OCMS = mode;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CH4OC_B.OCMS = mode;
    }
}

/*!
 * @brief        Initializes the TMR1/TMR1A Channel 1 Input Capture according to the specified parameters
 *
 * @param        tmr:       Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param        polarity:  Input capture polarity.
 *
 * @param        selection: Input capture source selection.
 *
 * @param        div:       Input capture divider number.
 *
 * @param        filter:    Input capture filter.
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigInputCapture1(TMR1_T *tmr, TMR1_IC_POLARITY_T polarity, TMR1_IC_SELECT_T selection,
                                        TMR1_IC_DIV_T div, uint8_t filter)
{
    /** input capture selection */
    tmr->CH1IC_B.MODESEL = selection;

    /** filter set */
    tmr->CH1IC_B.ICFC = filter & 0X0F;

    /** input capture divider */
    tmr->CH1IC_B.IC1PSC = div;

    /** input polarity */
    tmr->CHCTRL1_B.CH1CCP = polarity;

    /** Enable input */
    tmr->CHCTRL1_B.CH1CCEN = BIT_SET;
}

/*!
 * @brief       Initializes the TMR1/TMR1A Channel 2 Input Capture according to the specified parameters
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       polarity:   Input capture polarity.
 *
 * @param       selection:  Input capture source selection.
 *
 * @param       div:        Input capture divider number.
 *
 * @param       filter:     Input capture filter.
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigInputCapture2(TMR1_T *tmr, TMR1_IC_POLARITY_T polarity, TMR1_IC_SELECT_T selection,
                                        TMR1_IC_DIV_T div, uint8_t filter)
{
    /** input capture selection */
    tmr->CH2IC_B.MODESEL = selection;

    /** filter set */
    tmr->CH2IC_B.ICFC = filter;

    /** input capture divider */
    tmr->CH2IC_B.IC2PSC = div;

    /** input polarity */
    tmr->CHCTRL1_B.CH2CCP = polarity;

    /** Enable input */
    tmr->CHCTRL1_B.CH2CCEN = BIT_SET;
}

/*!
 * @brief       Initializes the TMR1/TMR1A Channel 3 Input Capture according to the specified parameters
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       polarity:   Input capture polarity.
 *
 * @param       selection:  Input capture source selection.
 *
 * @param       div:        Input capture divider number.
 *
 * @param       filter:     Input capture filter.
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigInputCapture3(TMR1_T *tmr, TMR1_IC_POLARITY_T polarity, TMR1_IC_SELECT_T selection,
                                        TMR1_IC_DIV_T div, uint8_t filter)
{
    /** input capture selection */
    tmr->CH3IC_B.MODESEL = selection;

    /** filter set */
    tmr->CH3IC_B.ICFC = filter;

    /** input capture divider */
    tmr->CH3IC_B.IC3PSC = div;

    /** input polarity */
    tmr->CHCTRL2_B.CH3CCP = polarity;

    /** Enable input */
    tmr->CHCTRL2_B.CH3CCEN = BIT_SET;
}

/*!
 * @brief       Initializes the TMR1/TMR1A Channel 4 Input Capture according to the specified parameters
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       polarity:   Input capture polarity.
 *
 * @param       selection:  Input capture source selection.
 *
 * @param       div:        Input capture divider number.
 *
 * @param       filter:     Input capture filter.
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigInputCapture4(TMR1_T *tmr, TMR1_IC_POLARITY_T polarity, TMR1_IC_SELECT_T selection,
                                        TMR1_IC_DIV_T div, uint8_t filter)
{
    /** input capture selection */
    tmr->CH4IC_B.MODESEL = selection;

    /** filter set */
    tmr->CH4IC_B.ICFC = filter;

    /** input capture divider */
    tmr->CH4IC_B.IC4PSC = div;

    /** input polarity */
    tmr->CHCTRL2_B.CH4CCP = polarity;

    /** Enable input */
    tmr->CHCTRL2_B.CH4CCEN = BIT_SET;
}

/*!
 * @brief       Initializes the TMR1/TMR1A  peripheral according to the specified parameters
 *
 * @param       tmr:            Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       icConfigStruct: pointer to a TMR1_ICConfig_T structure that
 *                              contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigInputCapture(TMR1_T *tmr, TMR1_ICConfig_T *icConfigStruct)
{
    TMR1_EnableChannel(tmr, icConfigStruct->channel);

    if(icConfigStruct->channel & TMR1_CHANNEL_1)
    {
        TMR1_ConfigInputCapture1(tmr, icConfigStruct->polarity, icConfigStruct->selection,
                                icConfigStruct->div, icConfigStruct->filter);
    }

    if(icConfigStruct->channel & TMR1_CHANNEL_2)
    {
        TMR1_ConfigInputCapture2(tmr, icConfigStruct->polarity, icConfigStruct->selection,
                                icConfigStruct->div, icConfigStruct->filter);
    }

    if(icConfigStruct->channel & TMR1_CHANNEL_3)
    {
        TMR1_ConfigInputCapture3(tmr, icConfigStruct->polarity, icConfigStruct->selection,
                                icConfigStruct->div, icConfigStruct->filter);
    }

    if(icConfigStruct->channel & TMR1_CHANNEL_4)
    {
        TMR1_ConfigInputCapture4(tmr, icConfigStruct->polarity, icConfigStruct->selection,
                                icConfigStruct->div, icConfigStruct->filter);
    }
}

/*!
 * @brief       Fills each icConfigStruct member with its default value
 *
 * @param       icConfigStruct: Pointer to a TMR1_ICConfig_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ICStructInit(TMR1_ICConfig_T *icConfigStruct)
{
    icConfigStruct->channel = TMR1_CHANNEL_1;
    icConfigStruct->div = TMR1_IC_DIV_1;
    icConfigStruct->filter = 0;
    icConfigStruct->polarity = TMR1_IC_POLARITY_RISING;
    icConfigStruct->selection = TMR1_IC_SELECT_DIRECTTI;
}

/*!
 * @brief       Dead time setting
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       deadTime:   dead time value
 *
 * @retval      None
 *
 * @note
 */
void TMR1_SetDeadTime(TMR1_T *tmr, uint8_t deadTime)
{
    tmr->DTS = (uint32_t)deadTime;
}

/*!
 * @brief       Configuration protection level
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       level:  protection level
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigProtectionLevel(TMR1_T *tmr, TMR1_PROTECTION_LEVEL_T level)
{
    tmr->BRKCTRL_B.PROTCFG = level;
}

/*!
 * @brief       Off-state in run mode selection
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       state:  Off-state Specified
 *
 * @retval      None
 *
 * @note
 */
void TMR1_SelectOffStateInRunMode(TMR1_T *tmr, TMR1_OSRM_T state)
{
    tmr->BRKCTRL_B.RMOS = state;
}

/*!
 * @brief       Off-state in idle mode selection
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       state:  Off-state Specified
 *
 * @retval      None
 *
 * @note
 */
void TMR1_SelectOffStateInIdleMode(TMR1_T *tmr, TMR1_OSIM_T state)
{
    tmr->BRKCTRL_B.IMOS = state;
}

/*!
 * @brief       Break polarity configuration
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       polarity:   Break polarity
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigBreakPolarity(TMR1_T *tmr, TMR1_BREAK_POL_T polarity)
{
    tmr->BRKCTRL_B.BRKPOL = polarity;
}

/*!
 * @brief       Enable break
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableBreak(TMR1_T *tmr)
{
    tmr->BRKCTRL_B.BRKEN = BIT_SET;
}

/*!
 * @brief       Disable break
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableBreak(TMR1_T *tmr)
{
    tmr->BRKCTRL_B.BRKEN = BIT_RESET;
}

/*!
 * @brief       Enable Automatic Output
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableAutomaticOutput(TMR1_T *tmr)
{
    tmr->BRKCTRL_B.AOEN = BIT_SET;
}

/*!
 * @brief       Disable Automatic Output
 *
 * @param       tmr:   Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableAutomaticOutput(TMR1_T *tmr)
{
    tmr->BRKCTRL_B.AOEN = BIT_RESET;
}

/*!
 * @brief       Configures the TIM1 peripheral PWM Input Mode according to the specified parameters
 *
 * @param       tmr:            Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       pwmInputConfig: pointer to a TMR1_ICConfig_T structure that
 *                              contains the configuration information for the specified Timer peripheral
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigInputPWM(TMR1_T *tmr, TMR1_ICConfig_T *pwmInputConfig)
{
    TMR1_IC_POLARITY_T polarityCHxN = TMR1_IC_POLARITY_RISING;
    TMR1_IC_SELECT_T selectionCHxN = TMR1_IC_SELECT_DIRECTTI;

    if(pwmInputConfig->polarity == TMR1_IC_POLARITY_RISING)
    {
        polarityCHxN = TMR1_IC_POLARITY_FALLING;
    }

    if(pwmInputConfig->selection == TMR1_IC_SELECT_DIRECTTI)
    {
        selectionCHxN = TMR1_IC_SELECT_INDIRECTTI;
    }

    if(pwmInputConfig->channel == TMR1_CHANNEL_1)
    {
        TMR1_ConfigInputCapture1(tmr, pwmInputConfig->polarity, pwmInputConfig->selection,
                                pwmInputConfig->div, pwmInputConfig->filter);

        TMR1_ConfigInputCapture2(tmr, polarityCHxN, selectionCHxN,
                                pwmInputConfig->div, pwmInputConfig->filter);
    }
    else if(pwmInputConfig->channel == TMR1_CHANNEL_2)
    {
        TMR1_ConfigInputCapture2(tmr, pwmInputConfig->polarity, pwmInputConfig->selection,
                                pwmInputConfig->div, pwmInputConfig->filter);

        TMR1_ConfigInputCapture1(tmr, polarityCHxN, selectionCHxN,
                                pwmInputConfig->div, pwmInputConfig->filter);
    }

    TMR1_EnableChannel(tmr, TMR1_CHANNEL_1 | TMR1_CHANNEL_2);
}

/*!
 * @brief       Enable Timer1 or Timer1A
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_Enable(TMR1_T *tmr)
{
    tmr->CTRL1_B.CNTEN = BIT_SET;
}

/*!
 * @brief       Disable Timer1 or Timer1A
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_Disable(TMR1_T *tmr)
{
    tmr->CTRL1_B.CNTEN = BIT_RESET;
}

/*!
 * @brief       Enable Specifies timer PWM output(whole output)
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableOutputPWM(TMR1_T *tmr)
{
    tmr->BRKCTRL_B.WOEN = BIT_SET;
}

/*!
 * @brief       Disable Specifies timer PWM output(main output)
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableOutputPWM(TMR1_T *tmr)
{
    tmr->BRKCTRL_B.WOEN = BIT_RESET;
}

/*!
 * @brief       Enable interrupt
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR1_INT_UPDATE:   Update interrupt
 *                          @arg TMR1_INT_CH1CC:    Channel 1 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH2CC:    Channel 2 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH3CC:    Channel 3 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH4CC:    Channel 4 Compare/Capture interrupt
 *                          @arg TMR1_INT_CC_UPDATE:Compare/Capture Update interrupt
 *                          @arg TMR1_INT_TRIGGER:  Trigger interrupt
 *                          @arg TMR1_INT_BREAK:    Break interrupt
 * @retval      None
 *
 * @note
 */
void TMR1_EnableInterrupt(TMR1_T *tmr, uint8_t interrupt)
{
    tmr->INTCTRL |= (uint32_t)interrupt;
}

/*!
 * @brief        Disable interrupt
 *
 * @param        tmr:       Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param        interrupt: Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR1_INT_UPDATE:   Update interrupt
 *                          @arg TMR1_INT_CH1CC:    Channel 1 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH2CC:    Channel 2 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH3CC:    Channel 3 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH4CC:    Channel 4 Compare/Capture interrupt
 *                          @arg TMR1_INT_CC_UPDATE:Compare/Capture Update interrupt
 *                          @arg TMR1_INT_TRIGGER:  Trigger interrupt
 *                          @arg TMR1_INT_BREAK:    Break interrupt
 *
 * @retval        None
 *
 * @note
 */
void TMR1_DisableInterrupt(TMR1_T *tmr, uint8_t interrupt)
{
    tmr->INTCTRL &= (uint32_t)~interrupt;
}

/*!
 * @brief       External trigger configuration
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       polarity:   External Trigger polarity.
 *
 * @param       div:        External Trigger divider number.
 *
 * @param       filter:     External Trigger filter
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigExternalTrigger(TMR1_T *tmr, TMR1_EXT_TRG_POLARITY_T polarity,
                                        TMR1_ETRG_DIV_T div, uint8_t filter)
{
    tmr->ETC_B.ETFC = filter & 0X0F;

    tmr->ETC_B.ETRC = div;

    tmr->ETC_B.ETPC = polarity;
}

/*!
 * @brief       External Clock mode 2 Enable
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       polarity:   External Trigger polarity.
 *
 * @param       div:        External Trigger divider number.
 *
 * @param       filter:     External Trigger filter
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigExternalClockMode2(TMR1_T *tmr, TMR1_EXT_TRG_POLARITY_T polarity,
                                            TMR1_ETRG_DIV_T div, uint8_t filter)
{
    TMR1_ConfigExternalTrigger(tmr, polarity, div, filter);

    tmr->ETC_B.ECM2EN = BIT_SET;
}

/*!
 * @brief       External Clock mode 1 Enable
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       clock:      External clock source.
 *
 * @param       polarity:   Clock Polarity
 *
 * @param       filter:     Clock filter
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigExternalClockMode1(TMR1_T *tmr, TMR1_EXT_CLK_SOURCE_T clock,
                                            TMR1_IC_POLARITY_T polarity, uint8_t filter)
{
    if(clock == TMR1_EXT_CLK_SOURCE_CH2INFP2)
    {
        TMR1_ConfigInputCapture2(tmr, polarity, TMR1_IC_SELECT_DIRECTTI, TMR1_IC_DIV_1, filter);
    }
    else
    {
        TMR1_ConfigInputCapture1(tmr, polarity, TMR1_IC_SELECT_DIRECTTI, TMR1_IC_DIV_1, filter);
    }

    tmr->SMC_B.ITC = clock;

    tmr->SMC_B.SMFC = TMR1_SLAVE_MODE_EXTERNAL1;
}

/*!
 * @brief       Counter mode configuration
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       mode:   Counter mode
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigCountMode(TMR1_T *tmr, TMR1_CNT_MODE_T mode)
{
    tmr->CTRL1_B.CNTDIR = (mode >> 4) & 0x01;
    tmr->CTRL1_B.CNTMODE = mode & 0X03;
}

/*!
 * @brief       Set divider
 *
 * @param       tmr:       Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       divider:   divider
 *
 * @retval      None
 *
 * @note
 */
void TMR1_SetDivider(TMR1_T *tmr, uint16_t divider)
{
    tmr->PSC1 = (uint32_t)((divider >> 8) & 0xff);

    tmr->PSC0 = (uint32_t)(divider & 0xff);
}

/*!
 * @brief       Enable Single pulse mode
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableSinglePulseMode(TMR1_T *tmr)
{
    tmr->CTRL1_B.SPMEN = BIT_SET;
}

/*!
 * @brief       Disable Single pulse mode
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableSinglePulseMode(TMR1_T *tmr)
{
    tmr->CTRL1_B.SPMEN = BIT_RESET;
}

/*!
 * @brief       Update source configuration
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       source: Specifies the update source.
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigUpdate(TMR1_T *tmr, TMR1_UPDATE_SOURCE_T source)
{
    tmr->CTRL1_B.UES = source & 0x01;
    tmr->CTRL1_B.NGUE = (source >> 4) & 0x01;
}

/*!
 * @brief       Input Trigger Configuration
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       trigger:    Input Trigger selection
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigInputTrigger(TMR1_T *tmr, TMR1_ITC_T trigger)
{
    tmr->SMC_B.ITC = trigger;
}

/*!
 * @brief       Encoder Interface configuraion
 *
 * @param       tmr:                    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       encoderConfigStruct:    pointer to a TMR1_EncoderConfig_T structure that
 *                                      contains the configuration information
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigEncodeInterface(TMR1_T *tmr, TMR1_EncoderConfig_T *encoderConfigStruct)
{
    tmr->SMC_B.SMFC = encoderConfigStruct->mode;

    tmr->CH1IC_B.MODESEL = TMR1_IC_SELECT_DIRECTTI;

    tmr->CH2IC_B.MODESEL = TMR1_IC_SELECT_DIRECTTI;

    tmr->CHCTRL1_B.CH1CCP = encoderConfigStruct->polarityIC1;

    tmr->CHCTRL1_B.CH2CCP = encoderConfigStruct->polarityIC2;
}

/*!
 * @brief       Compare/Capture update source configuration
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       mode:   Compare/Capture update source
 *                      This parameter can be one of following values:
 *                      @TMR1_CCUS_0:   Update by setting SCEG_CCUEG = 1
 *                      @TMR1_CCUS_1:   Update by setting SCEG_CCUEG = 1 or when an rising edge occurs on tirgger input.
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigCCUpdateSource(TMR1_T *tmr, TMR1_CCUS_T mode)
{
    tmr->CTRL2_B.CCUS = mode;
}

/*!
 * @brief       Enable Capture/Compare buffer(preloaded)
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableCompareCaptureBuffer(TMR1_T *tmr)
{
    tmr->CTRL2_B.CCBEN = BIT_SET;
}

/*!
 * @brief       Disable Capture/Compare buffer(preloaded)
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableCompareCaptureBuffer(TMR1_T *tmr)
{
    tmr->CTRL2_B.CCBEN = BIT_RESET;
}

/*!
 * @brief       Enable Auto-reload buffer(preloaded)
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableAutoReloadBuffer(TMR1_T *tmr)
{
    tmr->CTRL1_B.ARBEN = BIT_SET;
}

/*!
 * @brief       Disable Auto-reload buffer(preloaded)
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableAutoReloadBuffer(TMR1_T *tmr)
{
    tmr->CTRL1_B.ARBEN = BIT_RESET;
}

/*!
 * @brief       Enable Specified Channel output compare buffer(preload)
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableOutputCompareBuffer(TMR1_T *tmr, uint8_t channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CH1OC_B.OCBEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CH2OC_B.OCBEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CH3OC_B.OCBEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CH4OC_B.OCBEN = BIT_SET;
    }
}

/*!
 * @brief       Disable Specified Channel output compare buffer(preload)
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableOutputCompareBuffer(TMR1_T *tmr, uint8_t channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CH1OC_B.OCBEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CH2OC_B.OCBEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CH3OC_B.OCBEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CH4OC_B.OCBEN = BIT_RESET;
    }
}

/*!
 * @brief       Enable Specified Channel output compare fast mode
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableOutputCompareFastMode(TMR1_T *tmr, uint8_t channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CH1OC_B.OCFEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CH2OC_B.OCFEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CH3OC_B.OCFEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CH4OC_B.OCFEN = BIT_SET;
    }
}

/*!
 * @brief       Disable Specified Channel output compare fast mode
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableOutputCompareFastMode(TMR1_T *tmr, uint8_t channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CH1OC_B.OCFEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CH2OC_B.OCFEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CH3OC_B.OCFEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CH4OC_B.OCFEN = BIT_RESET;
    }
}

/*!
 * @brief       Generating Event by software
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       event:  Event source specified
 *              This parameter can be any combination of the following values:
 *              @arg TMR1_EVENT_UPDATE:     Update evnet
 *              @arg TMR1_EVENT_CH1CC:      Channel 1 Compare/Capture evnet
 *              @arg TMR1_EVENT_CH2CC:      Channel 2 Compare/Capture evnet
 *              @arg TMR1_EVENT_CH3CC:      Channel 3 Compare/Capture evnet
 *              @arg TMR1_EVENT_CH4CC:      Channel 4 Compare/Capture evnet
 *              @arg TMR1_EVENT_CC_UPDATE:  Compare/Capture Update evnet
 *              @arg TMR1_EVENT_TRIGGER:    Trigger evnet
 *              @arg TMR1_EVENT_BREAK:      Break evnet
 *
 * @retval      None
 *
 * @note
 */
void TMR1_GenerateEvent(TMR1_T *tmr, uint8_t event)
{
    tmr->SCEG = (uint32_t)event;
}

/*!
 * @brief       Specified Channel output compare polarity configuration
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @param       polarity:   Specifies the polarity
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigOutputComparePolarity(TMR1_T *tmr, uint8_t channel, TMR1_OC_POLARITY_T polarity)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CHCTRL1_B.CH1CCP = polarity;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CHCTRL1_B.CH2CCP = polarity;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CHCTRL2_B.CH3CCP = polarity;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CHCTRL2_B.CH4CCP = polarity;
    }
}

/*!
 * @brief       Specified Channel output compare complementary polarity configuration
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A

 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *
 * @param       polarity:   Specifies the polarity
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigOutputCompareComplementPolarity(TMR1_T *tmr, uint8_t channel, TMR1_OC_POLARITY_T polarity)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CHCTRL1_B.CH1OCNP = polarity;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CHCTRL1_B.CH2OCNP = polarity;
    }

}

/*!
 * @brief       Enable specified Channel Compare/Capture output
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableCompareCapture(TMR1_T *tmr, uint8_t channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CHCTRL1_B.CH1CCEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CHCTRL1_B.CH2CCEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CHCTRL2_B.CH3CCEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CHCTRL2_B.CH4CCEN = BIT_SET;
    }
}

/*!
 * @brief       Disable specified Channel Compare/Capture output
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableCompareCapture(TMR1_T *tmr, uint8_t channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CHCTRL1_B.CH1CCEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CHCTRL1_B.CH2CCEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CHCTRL2_B.CH3CCEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CHCTRL2_B.CH4CCEN = BIT_RESET;
    }
}

/*!
 * @brief       Enable specified Channel Compare/Capture complementary output
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableCompareCaptureComplement(TMR1_T *tmr, uint8_t channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CHCTRL1_B.CH1OCNEN = BIT_SET;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CHCTRL1_B.CH2OCNEN = BIT_SET;
    }
}

/*!
 * @brief       Disable specified Channel Compare/Capture complementary output
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableCompareCaptureComplement(TMR1_T *tmr, uint8_t channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CHCTRL1_B.CH1OCNEN = BIT_RESET;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CHCTRL1_B.CH2OCNEN = BIT_RESET;
    }
}

/*!
 * @brief       Set counter register value
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       count:  specifies the counter register new value
 *
 * @retval      None
 *
 * @note
 */
void TMR1_SetCounter(TMR1_T *tmr, uint16_t count)
{
    tmr->CNT1 = (uint32_t)((count >> 8) & 0xff);
    tmr->CNT0 = (uint32_t)(count & 0xff);
}

/*!
 * @brief       Set Auto-Reload register value
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       reload: specifies the Auto-Reload register new value
 *
 * @retval      None
 *
 * @note
 */
void TMR1_SetAutoReloadVaue(TMR1_T *tmr, uint16_t reload)
{
    tmr->AUTORLD1 = (uint32_t)((reload >> 8) & 0xff);
    tmr->AUTORLD0 = (uint32_t)(reload & 0xff);
}

/*!
 * @brief       Set specified Channel Compare/Capture register value
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @param       compare:    specifies the Channel Capture Compare register value
 *
 * @retval      None
 *
 * @note
 */
void TMR1_SetCompareCapture(TMR1_T *tmr, uint8_t channel, uint16_t compare)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CH1CC1 = (uint32_t)((compare >> 8) & 0xff);
        tmr->CH1CC0 = (uint32_t)(compare & 0xff);
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CH2CC1 = (uint32_t)((compare >> 8) & 0xff);
        tmr->CH2CC0 = (uint32_t)(compare & 0xff);
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CH3CC1 = (uint32_t)((compare >> 8) & 0xff);
        tmr->CH3CC0 = (uint32_t)(compare & 0xff);
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CH4CC1 = (uint32_t)((compare >> 8) & 0xff);
        tmr->CH4CC0 = (uint32_t)(compare & 0xff);
    }
}

/*!
 * @brief       Read Channel 1 Capture Compare register value
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      Channel 1 Capture Compare register value
 *
 * @note
 */
uint16_t TMR1_ReadCapture1(TMR1_T *tmr)
{
    uint16_t capture = 0;

    capture = (uint16_t)tmr->CH1CC1;
    capture <<= 8;
    capture |= (uint16_t)tmr->CH1CC0;

    return capture;
}

/*!
 * @brief       Read Channel 2 Capture Compare register value
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      Channel 2 Capture Compare register value
 *
 * @note
 */
uint16_t TMR1_ReadCapture2(TMR1_T *tmr)
{
    uint16_t capture = 0;

    capture = (uint16_t)tmr->CH2CC1;
    capture <<= 8;
    capture |= (uint16_t)tmr->CH2CC0;

    return capture;
}

/*!
 * @brief       Read Channel 3 Capture Compare register value
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      Channel 3 Capture Compare register value
 *
 * @note
 */
uint16_t TMR1_ReadCapture3(TMR1_T *tmr)
{
    uint16_t capture = 0;

    capture = (uint16_t)tmr->CH3CC1;
    capture <<= 8;
    capture |= (uint16_t)tmr->CH3CC0;

    return capture;
}

/*!
 * @brief       Read Channel 4 Capture Compare register value
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      Channel 4 Capture Compare register value
 *
 * @note
 */
uint16_t TMR1_ReadCapture4(TMR1_T *tmr)
{
    uint16_t capture = 0;

    capture = (uint16_t)tmr->CH4CC1;
    capture <<= 8;
    capture |= (uint16_t)tmr->CH4CC0;

    return capture;
}

/*!
 * @brief       Read specified Channel Compare/Capture register value
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be one of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @retval      Capture Compare register value
 *
 * @note
 */
uint16_t TMR1_ReadCompareCapture(TMR1_T *tmr, TMR1_CHANNEL_T channel)
{
    if(channel & TMR1_CHANNEL_1)
    {
        return TMR1_ReadCapture1(tmr);
    }

    if(channel & TMR1_CHANNEL_2)
    {
        return TMR1_ReadCapture2(tmr);
    }

    else if(channel & TMR1_CHANNEL_3)
    {
        return TMR1_ReadCapture3(tmr);
    }

    else
    {
        return TMR1_ReadCapture4(tmr);
    }
}

/*!
 * @brief       Set specified Channel Input Capture divider
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       channel:    Timer Channel
 *                          The Parameter can be combination of the following values:
 *                          @arg TMR1_CHANNEL_1:    Channel 1
 *                          @arg TMR1_CHANNEL_2:    Channel 2
 *                          @arg TMR1_CHANNEL_3:    Channel 3
 *                          @arg TMR1_CHANNEL_4:    Channel 4
 *
 * @param       divider:    specifies the channel Input Capture divider
 *
 * @retval      None
 *
 * @note
 */
void TMR1_SetInputCaptureDivider(TMR1_T *tmr, uint8_t channel, TMR1_IC_DIV_T divider)
{
    if(channel & TMR1_CHANNEL_1)
    {
        tmr->CH1IC_B.IC1PSC = divider;
    }

    if(channel & TMR1_CHANNEL_2)
    {
        tmr->CH2IC_B.IC2PSC = divider;
    }

    if(channel & TMR1_CHANNEL_3)
    {
        tmr->CH3IC_B.IC3PSC = divider;
    }

    if(channel & TMR1_CHANNEL_4)
    {
        tmr->CH4IC_B.IC4PSC = divider;
    }
}


/*!
 * @brief       Read counter register value
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      Counter register value
 *
 * @note
 */
uint16_t TMR1_ReadCounter(TMR1_T *tmr)
{
    uint16_t capture = 0;

    capture = (uint16_t)tmr->CNT1;
    capture <<= 8;
    capture |= (uint16_t)tmr->CNT0;

    return capture;
}

/*!
 * @brief       Read Divider register value
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      Divider register value
 *
 * @note
 */
uint16_t TMR1_ReadDivider(TMR1_T *tmr)
{
    uint16_t capture = 0;

    capture = (uint16_t)tmr->PSC1;
    capture <<= 8;
    capture |= (uint16_t)tmr->PSC0;

    return capture;
}

/*!
 * @brief       Read specifies the flag
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       flag:   specifies the flag
 *                      The parameter can be any combination of the following values:
 *                      @arg TMR1_FLAG_UPDATE:      update flag
 *                      @arg TMR1_FLAG_CH1CC:       Channel 1 Compare/Capture flag
 *                      @arg TMR1_FLAG_CH2CC:       Channel 2 Compare/Capture
 *                      @arg TMR1_FLAG_CH3CC:       Channel 3 Compare/Capture
 *                      @arg TMR1_FLAG_CH4CC:       Channel 4 Compare/Capture
 *                      @arg TMR1_FLAG_CC_UPDATE:   Compare/Capture Update flag
 *                      @arg TMR1_FLAG_TRIGGER:     Trigger flag
 *                      @arg TMR1_FLAG_BREAK:       Break flag
 *                      @arg TMR1_FLAG_CH1RCF:      Channel 1 repetition capture flag
 *                      @arg TMR1_FLAG_CH2RCF:      Channel 2 repetition capture flag
 *                      @arg TMR1_FLAG_CH3RCF:      Channel 3 repetition capture flag
 *                      @arg TMR1_FLAG_CH4RCF:      Channel 4 repetition capture flag
 *
 * @retval      specifies the flag status.It can be SET or RESET
 *
 * @note
 */
uint8_t TMR1_ReadStatusFlag(TMR1_T *tmr, uint16_t flag)
{
    uint8_t flag1;
    uint8_t flag2;
    uint8_t status1 = 0;
    uint8_t status2 = 0;

    flag1 = (uint8_t)(flag & 0XFF);
    flag2 = (uint8_t)((flag >> 8) & 0xff);

    if(flag1)
    {
        status1 = (uint8_t)(tmr->STS1 & flag1);
    }

    if(flag2)
    {
        status2 = (uint8_t)(tmr->STS2 & flag2);
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
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       flag:   specifies the flag
 *                      The parameter can be any combination of the following values:
 *                      @arg TMR1_FLAG_UPDATE:      update flag
 *                      @arg TMR1_FLAG_CH1CC:       Channel 1 Compare/Capture flag
 *                      @arg TMR1_FLAG_CH2CC:       Channel 2 Compare/Capture
 *                      @arg TMR1_FLAG_CH3CC:       Channel 3 Compare/Capture
 *                      @arg TMR1_FLAG_CH4CC:       Channel 4 Compare/Capture
 *                      @arg TMR1_FLAG_CC_UPDATE:   Compare/Capture Update flag
 *                      @arg TMR1_FLAG_TRIGGER:     Trigger flag
 *                      @arg TMR1_FLAG_BREAK:       Break flag
 *                      @arg TMR1_FLAG_CH1RCF:      Channel 1 repetition capture flag
 *                      @arg TMR1_FLAG_CH2RCF:      Channel 2 repetition capture flag
 *                      @arg TMR1_FLAG_CH3RCF:      Channel 3 repetition capture flag
 *                      @arg TMR1_FLAG_CH4RCF:      Channel 4 repetition capture flag
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ClearStatusFlag(TMR1_T *tmr, uint16_t flag)
{
    uint8_t flag1;
    uint8_t flag2;

    flag1 = (uint8_t)(flag & 0XFF);
    flag2 = (uint8_t)((flag >> 8) & 0xff);

    if(flag1)
    {
        tmr->STS1 &= (uint32_t)~flag1;
    }

    if(flag2)
    {
        tmr->STS2 &= (uint32_t)~flag2;
    }
}

/*!
 * @brief       Read interrupt flag
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR1_INT_UPDATE:   Update interrupt
 *                          @arg TMR1_INT_CH1CC:    Channel 1 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH2CC:    Channel 2 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH3CC:    Channel 3 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH4CC:    Channel 4 Compare/Capture interrupt
 *                          @arg TMR1_INT_CC_UPDATE:Compare/Capture Update interrupt
 *                          @arg TMR1_INT_TRIGGER:  Trigger interrupt
 *                          @arg TMR1_INT_BREAK:    Break interrupt
 *
 * @retval      Specifies Interrupt source flag status.It Can be SET or RESET
 *
 * @note
 */
uint8_t TMR1_ReadIntFlag(TMR1_T *tmr, uint8_t interrupt)
{
    uint8_t intEnable;
    uint8_t intStatus;

    intStatus = (uint8_t)(tmr->STS1 & interrupt);
    intEnable = (uint8_t)(tmr->INTCTRL & interrupt);

    if((intStatus == interrupt) && (intEnable == interrupt))
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear interrupt flag
 *
 * @param       tmr:        Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       interrupt:  Interrupt source.
 *                          This parameter can be any combination of the following values:
 *                          @arg TMR1_INT_UPDATE:   Update interrupt
 *                          @arg TMR1_INT_CH1CC:    Channel 1 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH2CC:    Channel 2 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH3CC:    Channel 3 Compare/Capture interrupt
 *                          @arg TMR1_INT_CH4CC:    Channel 4 Compare/Capture interrupt
 *                          @arg TMR1_INT_CC_UPDATE:Compare/Capture Update interrupt
 *                          @arg TMR1_INT_TRIGGER:  Trigger interrupt
 *                          @arg TMR1_INT_BREAK:    Break interrupt
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ClearIntFlag(TMR1_T *tmr, uint8_t interrupt)
{
    tmr->STS1 &= (uint32_t)~interrupt;
}

/*!
 * @brief       Slave mode Configuration
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       mode:   Specifies the slave mode
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigSlaveMode(TMR1_T *tmr, TMR1_SLAVE_MODE_T mode)
{
    tmr->SMC_B.SMFC = mode;
}

/*!
 * @brief       Master mode Configuration
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @param       mode:   Specifies the master mode
 *
 * @retval      None
 *
 * @note
 */
void TMR1_ConfigMasterMode(TMR1_T *tmr, TMR1_MASTER_MODE_T mode)
{
    tmr->CTRL2_B.MMFC = mode;
}

/*!
 * @brief       Enable master mode
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_EnableMasterMode(TMR1_T *tmr)
{
    tmr->SMC_B.MSMEN = BIT_SET;
}

/*!
 * @brief       Disable master mode
 *
 * @param       tmr:    Timer peripheral. It can be TMR1 or TMR1A
 *
 * @retval      None
 *
 * @note
 */
void TMR1_DisableMasterMode(TMR1_T *tmr)
{
    tmr->SMC_B.MSMEN = BIT_RESET;
}

/**@} end of group TMR1_Fuctions*/
/**@} end of group TMR1_Driver */
/**@} end of group Peripherals_Library*/

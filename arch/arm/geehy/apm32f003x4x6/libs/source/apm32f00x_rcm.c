/*!
 * @file        apm32f00x_rcm.c
 *
 * @brief       This file contains all the functions for the RCM peripheral
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

#include "apm32f00x_rcm.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup RCM_Driver RCM Driver
  @{
*/

/** @addtogroup RCM_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the RCM peripheral registers to their default reset
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_Reset(void)
{
    RCM->ICC = RCM_ICC_RESET_VALUE;
    RCM->ECC = RCM_ECC_RESET_VALUE;
    RCM->MCC = RCM_MCC_RESET_VALUE;
    RCM->CSC = RCM_CSC_RESET_VALUE;
    RCM->CLKDIV = RCM_CLKDIV_RESET_VALUE;
    RCM->APBEN1 = RCM_APBEN1_RESET_VALUE;
    RCM->APBEN2 = RCM_APBEN2_RESET_VALUE;
    RCM->APBEN3 = RCM_APBEN3_RESET_VALUE;
    RCM->CSS = RCM_CSS_RESET_VALUE;

    RCM->COC = RCM_COC_RESET_VALUE;
    while(RCM->COC_B.COEN == BIT_SET)
    {}
    RCM->COC = RCM_COC_RESET_VALUE;

    RCM->HIRCTRIM = RCM_HIRCTRIM_RESET_VALUE;
}

/*!
 * @brief       Enable Fast wakeup
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableFastWakeup(void)
{
    RCM->ICC_B.FWFHEN = BIT_SET;
}

/*!
 * @brief       Disable Fast wakeup
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableFastWakeup(void)
{
    RCM->ICC_B.FWFHEN = BIT_RESET;
}

/*!
 * @brief       Enable External High Speed oscillator (HXT)
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableHXT(void)
{
    RCM->ECC_B.HXTEN = BIT_SET;
}

 /*!
 * @brief       Disable External High Speed oscillator (HXT)
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableHXT(void)
{
    RCM->ECC_B.HXTEN = BIT_RESET;
}

/*!
 * @brief       Enable High Speed Internal oscillator (HIRC)
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableHIRC(void)
{
    RCM->ICC_B.HIRCEN = BIT_SET;
}

/*!
 * @brief       Disable High Speed Internal oscillator (HIRC)
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableHIRC(void)
{
    RCM->ICC_B.HIRCEN = BIT_RESET;
}

/*!
 * @brief       Enable Low Speed Internal oscillator (LSI)
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableLIRC(void)
{
    RCM->ICC_B.LIRCEN = BIT_SET;
}

/*!
 * @brief       Disable Low Speed Internal oscillator (LSI)
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableLIRC(void)
{
    RCM->ICC_B.LIRCEN = BIT_RESET;
}

/*!
 * @brief       Enable clock output
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableClockOutput(void)
{
    RCM->COC_B.COEN = BIT_SET;
}

/*!
 * @brief       Disable clock output
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableClockOutput(void)
{
    RCM->COC_B.COEN = BIT_RESET;
}

/*!
 * @brief       Starts manually the clock switch execution
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableClockSwitch(void)
{
    RCM->CSC_B.CSEN = BIT_SET;
}

/*!
 * @brief       Stops manually the clock switch execution
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableClockSwitch(void)
{
    RCM->CSC_B.CSEN = BIT_RESET;
}

/*!
 * @brief       Configure Regulator power state when in Active-halt mode
 *
 * @param       mode:   Regulator power state
 *
 * @retval      None
 *
 * @note
 */
void RCM_ConfigRegulatorPower(RCM_REGULATOR_POWER_T mode)
{
    RCM->ICC_B.RPOEN = mode;
}

/*!
 * @brief       Enable specified peripheral clock
 *
 * @param       periph: Specifies the peripheral.
 *              The parameter can be combination of following values:
 *              @arg RCM_PERIPH_I2C:    I2C peripheral
 *              @arg RCM_PERIPH_SPI:    SPI peripheral
 *              @arg RCM_PERIPH_USART1: USART1 peripheral
 *              @arg RCM_PERIPH_TMR4:   Timer4 peripheral
 *              @arg RCM_PERIPH_TMR2:   Timer2 peripheral
 *              @arg RCM_PERIPH_TMR1:   Timer1 peripheral
 *              @arg RCM_PERIPH_WUPT:   Wakeup Timer peripheral
 *              @arg RCM_PERIPH_ADC:    ADC peripheral
 *              @arg RCM_PERIPH_TMR1A:  Timer1A peripheral
 *              @arg RCM_PERIPH_USART2: USART2 peripheral
 *              @arg RCM_PERIPH_USART3: USART3 peripheral
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableAPBPeriphClock(uint16_t periph)
{
    if(periph & 0x100)
    {
        RCM->APBEN1 |= periph & 0XFF;
    }

    else if(periph & 0x200)
    {
        RCM->APBEN2 |= periph & 0XFF;
    }

    else if(periph & 0x400)
    {
        RCM->APBEN3 |= periph & 0XFF;
    }
}

/*!
 * @brief       Disable specified peripheral clock
 *
 * @param       periph: Specifies the peripheral.
 *              The parameter can be combination of following values:
 *              @arg RCM_PERIPH_I2C:    I2C peripheral
 *              @arg RCM_PERIPH_SPI:    SPI peripheral
 *              @arg RCM_PERIPH_USART1: USART1 peripheral
 *              @arg RCM_PERIPH_TMR4:   Timer4 peripheral
 *              @arg RCM_PERIPH_TMR2:   Timer2 peripheral
 *              @arg RCM_PERIPH_TMR1:   Timer1 peripheral
 *              @arg RCM_PERIPH_WUPT:   Wakeup Timer peripheral
 *              @arg RCM_PERIPH_ADC:    ADC peripheral
 *              @arg RCM_PERIPH_TMR1A:  Timer1A peripheral
 *              @arg RCM_PERIPH_USART2: USART2 peripheral
 *              @arg RCM_PERIPH_USART3: USART3 peripheral
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableAPBPeriphClock(uint16_t periph)
{
    if(periph & 0x100)
    {
        RCM->APBEN1 &= (uint32_t)~(periph & 0XFF);
    }

    else if(periph & 0x200)
    {
        RCM->APBEN2 &= (uint32_t)~(periph & 0XFF);
    }

    else if(periph & 0x400)
    {
        RCM->APBEN3 &= (uint32_t)~(periph & 0XFF);
    }
}

/*!
 * @brief       Configures the Switch from one clock to another
 *
 * @param       switchClockStruct:  Pointer to a RCM_SwitchClockStruct_T structure that
 *                                  contains the configuration information
 * @retval      None
 *
 * @note
 */
uint8_t RCM_ConfigClockSwitch(RCM_SwitchClockStruct_T *switchClockStruct)
{
    uint16_t counter = 0xffff;
    RCM_MCLKSRC_T curMclkSrc;

    curMclkSrc = (RCM_MCLKSRC_T)RCM->MCS;

    if(switchClockStruct->mode == RCM_SWITCH_MODE_AUTO)
    {
        RCM->CSC_B.CSEN = BIT_SET;
        RCM->CSC_B.CSIE = switchClockStruct->intEnable;
        RCM->MCC = switchClockStruct->clockSource;

        while((RCM->CSC_B.CSBF == SET) && counter)
        {
            counter--;
        }
    }
    else
    {
        RCM->CSC_B.CSEN = BIT_RESET;
        RCM->CSC_B.CSIE = switchClockStruct->intEnable;
        RCM->MCC = switchClockStruct->clockSource;

        while((RCM->CSC_B.CSIF == RESET) && counter)
        {
            counter--;
        }

        if(RCM->CSC_B.CSIF == SET)
        {
            RCM->CSC_B.CSEN = BIT_SET;
        }
    }

    if((switchClockStruct->currentClkState == RCM_CLOCK_STATE_OFF) && (counter))
    {
        if(curMclkSrc == RCM_MCLKSRC_HIRC)
        {
            RCM->ICC_B.HIRCEN = BIT_RESET;
        }
        else if(curMclkSrc == RCM_MCLKSRC_LIRC)
        {
            RCM->ICC_B.LIRCEN = BIT_RESET;
        }
        else if(curMclkSrc == RCM_MCLKSRC_HXT)
        {
            RCM->ECC_B.HXTEN = BIT_RESET;
        }
    }

    if(counter)
    {
        return SUCCESS;
    }

    return ERROR;
}

/*!
 * @brief       Configures the HIRC clock dividers
 *
 * @param       div:    Specifies the HIRC clock divider to apply
 *
 * @retval      None
 *
 * @note
 */
void RCM_ConfigHIRCDiv(RCM_HIRC_DIV_T div)
{
    RCM->CLKDIV_B.HIRCDIV = div & 0X0F;
    RCM->CLKDIV_B.HDS = (div >> 4) & 0X0F;
}

/*!
 * @brief       Configures the CPU clock dividers
 *
 * @param       div:    Specifies the CPU clock divider to apply
 *
 * @retval      None
 *
 * @note
 */
void RCM_ConfigCPUClkDiv(RCM_CPUCLK_DIV_T div)
{
    RCM->CLKDIV_B.CPUDIV = div;
}

/*!
 * @brief       Configures clock output source
 *
 * @param       clock:  Specifies the clock source
 *
 * @retval      None
 *
 * @note
 */
void RCM_ConfigClockOutput(RCM_COCCLK_T clock)
{
    RCM->COC_B.COS = clock;
}

/*!
 * @brief       Enables the specified clock interrupts
 *
 * @param       interrupt:  Specifies the interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg RCM_INT_CSSFD:  Clock security system fault detection interrupt
 *                          @arg RCM_INT_CS:    Clock switch interrupt
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableInterrupt(uint8_t interrupt)
{
    if(interrupt & 0x01)
    {
        RCM->CSS_B.CSSFDIE = BIT_SET;
    }

    if(interrupt & 0x02)
    {
        RCM->CSC_B.CSIE = BIT_SET;
    }
}

/*!
 * @brief       Disable the specified clock interrupts
 *
 * @param       interrupt:  Specifies the interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg RCM_INT_CSSFD:  Clock security system fault detection interrupt
 *                          @arg RCM_INT_CS:    Clock switch interrupt
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableInterrupt(uint8_t interrupt)
{
    if(interrupt & 0x01)
    {
        RCM->CSS_B.CSSFDIE = BIT_RESET;
    }

    if(interrupt & 0x02)
    {
        RCM->CSC_B.CSIE = BIT_RESET;
    }

}

/*!
 * @brief       Enables the Clock Security System
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        Once CSS is enabled it cannot be disabled until the next reset
 */
void RCM_EnableClockSecuritySystem(void)
{
    RCM->CSS_B.CSSEN = BIT_SET;
}

/*!
 * @brief       Returns the master clock source
 *
 * @param       None
 *
 * @retval      Returns the master clock source
 *
 * @note
 */
RCM_MCLKSRC_T RCM_GetMasterClockSource(void)
{
    return (RCM_MCLKSRC_T)RCM->MCS;
}

/*!
 * @brief       Get the master clock frequency
 *
 * @param       None
 *
 * @retval      Returns the master clock frequency
 *
 * @note
 */
uint32_t RCM_GetMasterClockFreq(void)
{
    uint32_t div = 0;
    uint32_t freq = 0;
    RCM_MCLKSRC_T masterClkSource;

    masterClkSource = (RCM_MCLKSRC_T)RCM->MCS;

    if(masterClkSource == RCM_MCLKSRC_HIRC)
    {
        div = RCM->CLKDIV_B.HIRCDIV;

        freq = HIRC_VALUE / (1 << div);
        if(!RCM->CLKDIV_B.HDS)
        {
            freq /= 3;
        }
    }
    else if(masterClkSource == RCM_MCLKSRC_HXT)
    {
        freq = HXT_VALUE;
    }
    else if(masterClkSource == RCM_MCLKSRC_LIRC)
    {
        freq = LIRC_VALUE;
    }

    return freq;
}

/*!
 * @brief       Set the High Speed Internal oscillator (HIRC) Trimming value
 *
 * @param       trim:   Specifies the trimming value
 *
 * @retval      None
 *
 * @note
 */
void RCM_SetHIRCTrim(uint8_t trim)
{
    RCM->HIRCTRIM = trim & 0X0F;
}

/*!
 * @brief       Reset clock switch operations
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_ResetClockSwitch(void)
{
    RCM->CSC_B.CSBF = BIT_RESET;
}

/*!
 * @brief       Read the specified Clock flag status
 *
 * @param       flag:   Specified Clock flag
 *              The parameter can be one of following values:
 *              @arg RCM_CLOCK_FLAG_LIRCRDY:    Low speed internal oscillator ready Flag
 *              @arg RCM_CLOCK_FLAG_HIRCRDY:    High speed internal oscillator ready Flag
 *              @arg RCM_CLOCK_FLAG_HXTRDY:     High speed external oscillator ready Flag
 *              @arg RCM_CLOCK_FLAG_CSIF:       Clock switch interrupt Flag
 *              @arg RCM_CLOCK_FLAG_CSBSY:      Switch busy Flag
 *              @arg RCM_CLOCK_FLAG_CSSFD:      Clock security system fault detection Flag
 *              @arg RCM_CLOCK_FLAG_BCEN:       Backup clock enable flag
 *              @arg RCM_CLOCK_FLAG_COCBSY:     Configurable clock output busy
 *              @arg RCM_CLOCK_FLAG_COCRDY:     Configurable clock output ready
 *
 * @retval      None
 *
 * @note
 */
uint8_t RCM_ReadClockFlag(RCM_CLOCK_FLAG_T flag)
{
    uint8_t status;

    if(flag & 0x100)
    {
        status = (uint8_t)(RCM->ICC & flag & 0xff);
    }

    else if(flag & 0x200)
    {
        status = (uint8_t)(RCM->ECC & flag & 0xff);
    }

    else if(flag & 0x400)
    {
        status = (uint8_t)(RCM->CSC & flag & 0xff);
    }
    else if(flag & 0x800)
    {
        status = (uint8_t)(RCM->CSS & flag & 0xff);
    }
    else if(flag & 0x1000)
    {
        status = (uint8_t)(RCM->COC & flag & 0xff);
    }

    if(status)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Checks whether the specified interrupt has occurred or not
 *
 * @param       interrupt:  Specifies the interrupt source
 *                          The parameter can be combination of following values:
 *                          @arg RCM_INT_FLAG_CSSFD: Clock security system fault detection interrupt flag
 *                          @arg RCM_INT_FLAG_CS:    Clock switch interrupt flag
 * @retval      None
 *
 * @note
 */
uint8_t RCM_ReadIntFlag(uint8_t flag)
{
    uint8_t flag1 = SET;
    uint8_t flag2 = SET;

    if(flag & 0x01)
    {
        flag1 = (uint8_t)RCM->CSS_B.CSSFDIF;
    }

    if(flag & 0x02)
    {
        flag2 = (uint8_t)RCM->CSC_B.CSIF;
    }

    if(flag1 && flag2)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clears the clock interrupt pending bits
 *
 * @param       interrupt:  Specifies the interrupt source
 *                          The parameter can be combination of following values:
 *                          @arg RCM_INT_FLAG_CSSFD: Clock security system fault detection interrupt flag
 *                          @arg RCM_INT_FLAG_CS:    Clock switch interrupt flag
 * @retval      None
 *
 * @note
 */

void RCM_ClearIntFlag(uint8_t flag)
{
    if(flag & 0x01)
    {
        RCM->CSS_B.CSSFDIF = BIT_RESET;
    }

    if(flag & 0x02)
    {
        RCM->CSC_B.CSIF = BIT_RESET;
    }
}

/*!
 * @brief       Read specified Reset Flag status
 *
 * @param       flag:   Specified Reset Flag
 *                      The parameter can be combination of following values:
 *                      @arg RCM_RTS_FLAG_WWDTRST:  Window watch dog timer reset flag
 *                      @arg RCM_RTS_FLAG_IWDTRST:  Independent Watchdog timer reset flag
 *                      @arg RCM_RTS_FLAG_SWRST:    CPU software reset flag
 *                      @arg RCM_RTS_FLAG_ECMRST:   EMC reset flag
 *
 * @retval      None
 *
 * @note
 */
uint8_t RCM_ReadResetFlag(uint8_t flag)
{
    uint8_t status;

    status = (uint8_t)(RCM->RSTSTS & flag);

    if(status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear specified Reset Flag
 *
 * @param       flag:   Specified Reset Flag
 *                      The parameter can be combination of following values:
 *                      @arg RCM_RTS_FLAG_WWDTRST:  Window watch dog timer reset flag
 *                      @arg RCM_RTS_FLAG_WWDTRST:  Independent Watchdog timer reset flag
 *                      @arg RCM_RTS_FLAG_WWDTRST:  EMC reset flag
 *
 * @retval      None
 *
 * @note
 */
void RCM_ClearResetFlag(uint8_t flag)
{
    RCM->RSTSTS |= flag;
}

/**@} end of group RCM_Fuctions*/
/**@} end of group RCM_Driver */
/**@} end of group Peripherals_Library*/

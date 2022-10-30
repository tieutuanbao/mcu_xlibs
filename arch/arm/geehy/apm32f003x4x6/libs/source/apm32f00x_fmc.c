/*!
 * @file        apm32f00x_fmc.c
 *
 * @brief       This file provides all the FMC firmware functions
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

#include "apm32f00x_fmc.h"

/** Flash Read protection key */
#define FMC_RP_KEY            ((uint32_t)0XA5)

/** Flash key definition */
#define FMC_KEY_1             ((uint32_t)0x45670123)
#define FMC_KEY_2             ((uint32_t)0xCDEF89AB)

/** Delay definition */
#define FMC_DELAY_ERASE       ((uint32_t)0x000B0000)
#define FMC_DELAY_PROGRAM     ((uint32_t)0x00002000)

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup FMC_Driver FMC Driver
  @{
*/

/** @addtogroup FMC_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set latency
 *
 * @param       latency:    Specifies the FMC Latency value
 *
 * @retval      None
 *
 * @note
 */
void FMC_SetLatency(FMC_LATENCY_T latency)
{
    FMC->CTRL1_B.LATENCY = latency;
}

/*!
 * @brief       Enable the Half cycle flash access
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_EnableHlafCycleAccess(void)
{
    FMC->CTRL1_B.HCAEN = BIT_SET;
}

/*!
 * @brief       Disable the Half cycle flash access
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_DisableHlafCycleAccess(void)
{
    FMC->CTRL1_B.HCAEN = BIT_RESET;
}

/*!
 * @brief       Enable the Prefetch Buffer
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_EnablePrefetchBuffer(void)
{
    FMC->CTRL1_B.PBEN = BIT_SET;
}

/*!
 * @brief       Disable the Prefetch Buffer
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_DisablePrefetchBuffer(void)
{
    FMC->CTRL1_B.PBEN = BIT_RESET;
}

/*!
 * @brief       Unlocks the flash Program Erase Controller
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_Unlock(void)
{
    FMC->KEY = FMC_KEY_1;
    FMC->KEY = FMC_KEY_2;
}

/*!
 * @brief       Locks the flash Program Erase Controller
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_Lock(void)
{
    FMC->CTRL2_B.LOCK = BIT_SET;
}

/*!
 * @brief       Read flash state
 *
 * @param       None
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ReadState(void)
{
    uint32_t status;
    FMC_STATE_T state = FMC_STATE_COMPLETE;

    status = FMC->STS;

    if(status & FMC_FLAG_PE)
    {
        state = FMC_STATE_PG_ERR;
    }
    else if(status & FMC_FLAG_WPE)
    {
        state = FMC_STATE_WRP_ERR;
    }
    else if(status == FMC_FLAG_BUSY)
    {
        state = FMC_STATE_BUSY;
    }

    return state;
}

/*!
 * @brief       Wait for flash controler ready
 *
 * @param       timeOut:    Specifies the time to wait
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_WaitForReady(uint32_t timeOut)
{
    FMC_STATE_T state;

    do
    {
        state = FMC_ReadState();
        timeOut--;
    }while((state == FMC_STATE_BUSY) && (timeOut));

    if(!timeOut)
    {
        state = FMC_STATE_TIMEOUT;
    }

    return state;
}

/*!
 * @brief       Erases a specified flash page
 *
 * @param       pageAddr:   Specifies the page address
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ErasePage(uint32_t pageAddr)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.PAGEERA = BIT_SET;

        FMC->ADDR = pageAddr;

        FMC->CTRL2_B.STA = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        FMC->CTRL2_B.PAGEERA = BIT_RESET;
    }

    return state;
}

/*!
 * @brief       Erases all flash pages
 *
 * @param       None
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_EraseAllPages(void)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.MASSERA = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        FMC->CTRL2_B.MASSERA = BIT_RESET;
    }

    return state;
}

/*!
 * @brief       Erase the flash option bytes
 *
 * @param       None
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_EraseOptionByte(void)
{
    uint16_t rpKey;
    FMC_STATE_T state;

    rpKey = FMC->OBCS_B.READPROT ? 0 : FMC_RP_KEY;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBE = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if(state == FMC_STATE_COMPLETE)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;

            FMC->CTRL2_B.OBP = BIT_SET;

            OB->READPROT = rpKey;

            state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

            if(state != FMC_STATE_TIMEOUT)
            {
                FMC->CTRL2_B.OBP = BIT_RESET;
            }
        }
        else if(state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Program a word at a specified address
 *
 * @param       addr:   Specifies the address to be programmed
 *
 * @param       data:   Specifies the data to be programmed
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ProgramWord(uint32_t addr, uint32_t data)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.PG = BIT_SET;

        *(__IO uint16_t *)addr = (uint16_t)data;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        if(state == FMC_STATE_COMPLETE)
        {
            *(__IO uint16_t *)(addr + 2) = (uint16_t)(data >> 16);

            state = FMC_WaitForReady(FMC_DELAY_PROGRAM);
        }

        FMC->CTRL2_B.PG = BIT_RESET;
    }

    return state;
}

/*!
 * @brief       Programs a half word at a specified address
 *
 * @param       addr:   Specifies the address to be programmed
 *
 * @param       data:   Specifies the data to be programmed
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ProgramHalfWord(uint32_t addr, uint16_t data)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.PG = BIT_SET;

        *(__IO uint16_t*)addr = data;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        FMC->CTRL2_B.PG = BIT_RESET;
    }

    return state;
}

/*!
 * @brief       Programs a half word at a specified Option Byte Data address
 *
 * @param       addr:   Specifies the address to be programmed
 *
 * @param       data:   Specifies the data to be programmed
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ProgramOptionByte(uint32_t addr, uint16_t data)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBP = BIT_SET;

        *(__IO uint16_t*)addr = data;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        if(state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Enable the specified page write protection
 *
 * @param       page:   Specifies the address of the pages to be write protected
 *                      This parameter can be any combination of the flowing values:
 *                      @arg FMC_WRP_PAGE_0
 *                      @arg FMC_WRP_PAGE_1
 *                      @arg FMC_WRP_PAGE_2
 *                      @arg FMC_WRP_PAGE_3
 *                      @arg FMC_WRP_PAGE_4
 *                      @arg FMC_WRP_PAGE_5
 *                      @arg FMC_WRP_PAGE_6
 *                      @arg FMC_WRP_PAGE_7
 *                      @arg FMC_WRP_PAGE_8
 *                      @arg FMC_WRP_PAGE_9
 *                      @arg FMC_WRP_PAGE_10
 *                      @arg FMC_WRP_PAGE_11
 *                      @arg FMC_WRP_PAGE_12
 *                      @arg FMC_WRP_PAGE_13
 *                      @arg FMC_WRP_PAGE_14
 *                      @arg FMC_WRP_PAGE_15
 *                      @arg FMC_WRP_PAGE_16
 *                      @arg FMC_WRP_PAGE_17
 *                      @arg FMC_WRP_PAGE_18
 *                      @arg FMC_WRP_PAGE_19
 *                      @arg FMC_WRP_PAGE_20
 *                      @arg FMC_WRP_PAGE_21
 *                      @arg FMC_WRP_PAGE_22
 *                      @arg FMC_WRP_PAGE_23
 *                      @arg FMC_WRP_PAGE_24
 *                      @arg FMC_WRP_PAGE_25
 *                      @arg FMC_WRP_PAGE_26
 *                      @arg FMC_WRP_PAGE_27
 *                      @arg FMC_WRP_PAGE_28
 *                      @arg FMC_WRP_PAGE_29
 *                      @arg FMC_WRP_PAGE_30
 *                      @arg FMC_WRP_PAGE_31
 *                      @arg FMC_WRP_PAGE_ALL
 *
 * @retval      Returns the FMC state.It can be combination of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_EnableWriteProtection(uint32_t page)
{
    uint8_t i;
    uint16_t temp;
    __IO uint16_t *WRPT;
    FMC_STATE_T state;

    WRPT = &OB->WRTPROT0;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_1;

        FMC->CTRL2_B.OBP = BIT_SET;

        for(i = 0; i < 4; i++)
        {
            temp = (uint16_t)~(page & 0xff);

            if((temp != 0xff) && (state == FMC_STATE_COMPLETE))
            {
                WRPT[i] = temp;

                state = FMC_WaitForReady(FMC_DELAY_PROGRAM);
            }

            page >>= 8;
        }

        if(state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Read out protection configuration.
 *
 * @param       state:  Specifies the state.
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ConfigReadOutProtection(FMC_RDP_T rdp)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBE = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if(state == FMC_STATE_COMPLETE)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;

            FMC->CTRL2_B.OBP = BIT_SET;

            OB->READPROT = rdp;

            state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

            if(state != FMC_STATE_TIMEOUT)
            {
                FMC->CTRL2_B.OBP = BIT_RESET;
            }
        }
        else if(state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBE = BIT_SET;
        }
    }

    return state;
}

/*!
 * @brief       User option byte configuration
 *
 * @param       userConfig: Pointer to a FMC_UserConfig_T structure that
 *                          contains the configuration information for User option byte
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ConfigOptionByteUser(FMC_UserConfig_T *userConfig)
{
    FMC_STATE_T state;
    uint16_t temp;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBP = BIT_SET;

        temp = (uint32_t)userConfig->iwdtSw | \
               (uint32_t)userConfig->LIRCen | \
               (uint32_t)userConfig->trimHIRC |
               (uint32_t)userConfig->wwdtHalt | \
               (uint32_t)userConfig->wwdtSw | 0xe0;

        OB->USER = temp;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        if(state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       AFR Option byte configuration
 *
 * @param       AFRConfig:  Pointer to a FMC_AFRConfig_T structure that
 *                          contains the configuration information for AFR Option byte
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ConfigOptionByteAFR(FMC_AFRConfig_T *AFRConfig)
{
    FMC_STATE_T state;
    uint16_t temp = 0;

    if(AFRConfig->AFR0 == FMC_OB_AFR_DISABLE)
    {
        temp |= BIT0;
    }

    if(AFRConfig->AFR1 == FMC_OB_AFR_DISABLE)
    {
        temp |= BIT1;
    }
    if(AFRConfig->AFR3 == FMC_OB_AFR_DISABLE)
    {
        temp |= BIT3;
    }

    if(AFRConfig->AFR4 == FMC_OB_AFR_DISABLE)
    {
        temp |= BIT4;
    }
    if(AFRConfig->AFR5 == FMC_OB_AFR_DISABLE)
    {
        temp |= BIT5;
    }
    if(AFRConfig->AFR7 == FMC_OB_AFR_DISABLE)
    {
        temp |= BIT7;
    }

    temp |= 0x44;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBP = BIT_SET;

        OB->AFR = temp;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);
        if(state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Clock Option byte configuration
 *
 * @param       extClk:     Specifies the external clock selection
 *
 * @param       wuptClk:    Specifies the Wakeup timer clock source
 *
 * @param       wuptDiv:    Specifies the Wakeup timer divider
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ConfigOptionByteClk(FMC_OB_EXTCLK_T extClk, FMC_OB_WUPT_CLKSRC_T wuptClk,
                                                    FMC_OB_WUPT_DIV_T wuptDiv)
{
    FMC_STATE_T state;
    uint16_t temp;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBP = BIT_SET;

        temp = (uint32_t)extClk | \
               (uint32_t)wuptClk | \
               (uint32_t)wuptDiv | 0xf0;

        OB->CLKOPT = temp;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        if(state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       HXTCNT Option byte configuration
 *
 * @param       counter:    Specifies the stabilization time
 *
 * @retval      Returns the FMC state.It can be one of value @ref FMC_STATE_T
 *
 * @note
 */
FMC_STATE_T FMC_ConfigOptionByteHXTCNT(FMC_OB_HXTCNT_T counter)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if(state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBP = BIT_SET;

        OB->HXTCNT = counter;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        if(state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Read the Flash User Option Bytes values
 *
 * @param       None
 *
 * @retval      The Flash User Option Bytes value
 *
 * @note
 */
uint32_t FMC_ReadOptionByteUser(void)
{
    return (uint32_t)(FMC->OBCS >> 2);
}

/*!
 * @brief       Read the flash Write Protection Option Bytes Register value
 *
 * @param       None
 *
 * @retval      The flash Write Protection Option Bytes Register value
 *
 * @note
 */
uint32_t FMC_ReadOptionByteWriteProtection(void)
{
    return (uint32_t)(FMC->WRTPROT);
}

/*!
 * @brief       Checks whether the flash Read Protection Status is set or not
 *
 * @param       None
 *
 * @retval      Flash ReadOut Protection Status(SET or RESET)
 *
 * @note
 */
uint8_t FMC_ReadProtectionStatus(void)
{
    if(FMC->OBCS_B.READPROT)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Checks whether the flash Prefetch Buffer status is set or not
 *
 * @param       None
 *
 * @retval      FMC Prefetch Buffer Status (SET or RESET)
 *
 * @note
 */
uint8_t FMC_ReadPrefetchBufferStatus(void)
{
    if(FMC->CTRL1_B.PBSF)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Enable the specified flash interrupts
 *
 * @param       interrupt:  Specifies the FMC interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg FMC_INT_ERROR:       Error interruption
 *                          @arg FMC_INT_COMPLETE:    operation complete interruption
 *
 * @retval      None
 *
 * @note
 */
void FMC_EnableInterrupt(uint32_t interrupt)
{
    FMC->CTRL2 |= interrupt;
}

/*!
 * @brief       Disable the specified flash interrupts
 *
 * @param       interrupt:  Specifies the flash interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg FMC_INT_ERROR:       Error interruption
 *                          @arg FMC_INT_COMPLETE:    operation complete interruption
 *
 * @retval      None
 *
 * @note
 */
void FMC_DisableInterrupt(uint32_t interrupt)
{
    FMC->CTRL2 &= ~interrupt;
}

/*!
 * @brief       Checks whether the specified flash flag is set or not
 *
 * @param       flag:   Specifies the flash flag to check
 *                      This parameter can be one of the values @ref FMC_FLAG_T
 * @retval      None
 *
 * @note
 */
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag)
{
    uint8_t status;

    if(flag & 0xff)
    {
        status = FMC->STS & flag;
    }
    else
    {
        status = FMC->OBCS & flag;
    }

    if(status)
    {
        return SET;
    }

    return RESET;
}


/*!
 * @brief       Clear the specified flash flag
 *
 * @param       flag:   Specifies the flash flag to clear
 *              This parameter can be one of the following values:
 *              @arg FMC_FLAG_BUSY:   Busy flag
 *              @arg FMC_FLAG_PE:     Program error flag
 *              @arg FMC_FLAG_WPE:    Write protection error flag
 *              @arg FMC_FLAG_OC:     Operation complete flag
 *
 * @retval      None
 *
 * @note
 */
void FMC_ClearStatusFlag(uint32_t flag)
{
    if(flag & 0xff)
    {
        FMC->STS = flag;
    }
}

/*!
 * @brief       Enable low power down mode in halt mode
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_EnablePowerDownHaltMode(void)
{
    FMC->LPM_B.HALT = BIT_SET;
}

/*!
 * @brief       Disable low power down mode in halt mode
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_DisablePowerDownHaltMode(void)
{
    FMC->LPM_B.HALT = BIT_RESET;
}

/*!
 * @brief       Enable low power down mode in active halt mode
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_EnablePowerDownActHaltMode(void)
{
    FMC->LPM_B.AHALT = BIT_SET;
}

/*!
 * @brief       Disable low power down mode in active halt mode
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void FMC_DisablePowerDownActHaltMode(void)
{
    FMC->LPM_B.AHALT = BIT_RESET;
}

/*!
 * @brief       Set power on time from lower power mode
 *
 * @param       time
 *
 * @retval      None
 *
 * @note
 */
void FMC_SetPowerOnTime(uint8_t time)
{
    FMC->TPO = time;
}

/**@} end of group FMC_Fuctions*/
/**@} end of group FMC_Driver */
/**@} end of group Peripherals_Library*/

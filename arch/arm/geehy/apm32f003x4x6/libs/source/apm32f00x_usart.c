/*!
 * @file        apm32f00x_usart.c
 *
 * @brief       This file contains all the functions for the USART peripheral
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

#include "apm32f00x_usart.h"
#include "apm32f00x_rcm.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup USART_Driver  USART Driver
  @{
*/

/** @addtogroup  USART_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the USART peripheral registers to their default reset values
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_Reset(USART_T *usart)
{
    volatile uint32_t dummy = 0;

    if(usart != USART1)
    {
        usart->SW = SET;
    }

    dummy = usart->STS;
    dummy = usart->DATA;

    usart->BR0 = USART_BR0_RESET_VALUE;
    usart->BR1 = USART_BR1_RESET_VALUE;

    usart->CTRL1 = USART_CTRL1_RESET_VALUE;
    usart->CTRL2 = USART_CTRL2_RESET_VALUE;
    usart->CTRL3 = USART_CTRL3_RESET_VALUE;
    usart->CTRL4 = USART_CTRL4_RESET_VALUE;
    usart->CTRL5 = USART_CTRL5_RESET_VALUE;

    usart->GTS = USART_GT_RESET_VALUE;

    usart->PSC = USART_DIV_RESET_VALUE;
}

/*!
 * @brief       Config the USART peripheral according to the specified parameters in the usartConfig
 *
 * @param       usart:          Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       usartConfig:    Pointer to a USART_Config_T structure that
 *                              contains the configuration information for the specified specifies USART peripheral
 *
 * @retval      None
 *
 * @note
 */
void USART_Config(USART_T* usart, USART_Config_T *usartConfig)
{
    uint32_t reg;
    uint32_t baudRateMantissa;
    uint32_t baudRateMantissaMod;

    if(usart != USART1)
    {
        usart->SW = SET;
        if(usart == USART3)
        {
            usart->IOSW = SET;
        }
    }

    /** parity and wordLength */
    reg = usart->CTRL1;
    reg &= 0xffffffe9;
    reg |= (uint32_t)usartConfig->parity | \
           (uint32_t)usartConfig->wordLength;
    usart->CTRL1 = reg;

    /** Stop bits */
    reg = usart->CTRL3;
    reg &= 0xffffffCF;
    reg |= usartConfig->stopBits;
    usart->CTRL3 = reg;

    /** Enable Tx/RX */
    reg = usart->CTRL2;
    reg &= 0xfffffff3;
    reg |= usartConfig->mode;
    usart->CTRL2 = reg;

    /** baud rate */
    baudRateMantissa = (RCM_GetMasterClockFreq() * 10 ) / usartConfig->baudRate;
    baudRateMantissaMod = baudRateMantissa % 10;
    baudRateMantissa /= 10;
    if(baudRateMantissaMod >= 5 )
    {
        baudRateMantissa += 1;
    }

    usart->BR0_B.DIV3_0 = baudRateMantissa & 0X0F;
    usart->BR0_B.DIV15_12 = (baudRateMantissa >> 12) & 0xff;
    usart->BR1_B.DIV11_4 = (baudRateMantissa >> 4) & 0xff;

    usart->CTRL1 &= 0XFE;
    usart->CTRL2 &= 0X0F;
    usart->CTRL4 &= 0XBF;
    USART_EnableInterrupt(usart, usartConfig->interrupt);
}

/*!
 * @brief       Fills each usartConfig member with its default value
 *
 * @param       usartConfig:    Pointer to a USART_Config_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void USART_ConfigStructInit(USART_Config_T* usartConfig)
{
    usartConfig->baudRate = 9600;
    usartConfig->wordLength = USART_WORD_LEN_8B;
    usartConfig->stopBits = USART_STOP_BIT_1;
    usartConfig->parity = USART_PARITY_NONE ;
    usartConfig->mode = USART_MODE_TX_RX;
    usartConfig->interrupt = USART_INT_NONE;
}

/*!
 * @brief       Enables the specified USART peripheral
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_Enable(USART_T* usart)
{
    usart->CTRL1_B.USARTDIS = BIT_RESET;

}

/*!
 * @brief       Disable the specified USART peripheral
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_Disable(USART_T* usart)
{
    usart->CTRL1_B.USARTDIS = BIT_SET;
}

/*!
 * @brief       Disables the specified USART interrupts
 *
 * @param       usart:      Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       interrupt:  Specifies the USART interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg USART_INT_PE:      Parity error interrupt
 *                          @arg USART_INT_TX:      Transmitter interrupt
 *                          @arg USART_INT_TXC:     Transmission complete interrupt
 *                          @arg USART_INT_RX:      Receiver interrupt
 *                          @arg USART_INT_IDLE:    IDLE Line interrupt
 *                          @arg USART_INT_LBD:     LIN Break Detection Interrupt
 *
 * @retval      None
 *
 * @note
 */
void USART_DisableInterrupt(USART_T *usart, uint32_t interrupt)
{
    /** PE */
    if(interrupt & 0xff)
    {
        usart->CTRL1 &= ~(interrupt & 0xff);
    }

    /** TX/TXC/RX/IDLE */
    if(interrupt & 0Xff00)
    {
        usart->CTRL2 &= ~((interrupt >> 8) & 0xff);
    }

    /** LBD */
    if(interrupt & 0Xff0000)
    {
        usart->CTRL4 &= ~((interrupt >> 16) & 0xff);
    }
}

/*!
 * @brief       Enable the specified USART interrupts
 *
 * @param       usart:      Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       interrupt:  Specifies the USART interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg USART_INT_PE:      Parity error interrupt
 *                          @arg USART_INT_TX:      Transmitter interrupt
 *                          @arg USART_INT_TXC:     Transmission complete interrupt
 *                          @arg USART_INT_RX:      Receiver interrupt
 *                          @arg USART_INT_IDLE:    IDLE Line interrupt
 *                          @arg USART_INT_LBD:     LIN Break Detection Interrupt
 *
 * @retval      None
 *
 * @note
 */
void USART_EnableInterrupt(USART_T *usart, uint32_t interrupt)
{
    /** PE */
    if(interrupt & 0xff)
    {
        usart->CTRL1 |= (interrupt & 0xff);
    }

    /** TX/TXC/RX/IDLE */
    if(interrupt & 0Xff00)
    {
        usart->CTRL2 |= ((interrupt >> 8) & 0xff);
    }

    /** LBD */
    if(interrupt & 0Xff0000)
    {
        usart->CTRL4 |= ((interrupt >> 16) & 0xff);
    }
}

/*!
 * @brief       Enables USART Half Duplex communication
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_EnableHalfDuplex(USART_T* usart)
{
    usart->CTRL5_B.HDMEN = BIT_SET;
}

/*!
 * @brief       Disable USART Half Duplex communication
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_DisableHalfDuplex(USART_T* usart)
{
    usart->CTRL5_B.HDMEN = BIT_RESET;
}

/*!
 * @brief       IrDA interface Configuration
 *
 * @param       usart:      Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       IrDAMode:   Specifies the IrDA lower power mode
 *
 * @retval      None
 *
 * @note
 */
void USART_ConfigIrDA(USART_T* usart, USART_IRDA_LP_T IrDAMode)
{
    usart->CTRL5_B.ILPM = IrDAMode;
}

/*!
 * @brief       Enable IrDA interface
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_EnableIrDA(USART_T* usart)
{
    usart->CTRL5_B.IRDAEN = BIT_SET;
}

/*!
 * @brief       Disable IrDA interface
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_DisableIrDA(USART_T* usart)
{
    usart->CTRL5_B.IRDAEN = BIT_RESET;
}

/*!
 * @brief       Sets the USART LIN Break detection length
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       lbdl:   LIN Break detection length
 *
 * @retval      None
 *
 * @note
 */
void USART_ConfigLINBreakDetectLength(USART_T* usart, USART_LBDL_T lbdl)
{
    usart->CTRL4_B.LMBDL = lbdl;
}

/*!
 * @brief       Enables the USART LIN mode
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_EnableLIN(USART_T* usart)
{
    usart->CTRL3_B.LINEN = BIT_SET;
}

/*!
 * @brief       Disable the USART LIN mode
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_DisableLIN(USART_T* usart)
{
    usart->CTRL3_B.LINEN = BIT_RESET;
}

/*!
 * @brief       Enables the USART Smart Card mode
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_EnableSmartCard(USART_T* usart)
{
    usart->CTRL5_B.SMEN = BIT_SET;
}

/*!
 * @brief       Disable the USART Smart Card mode
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_DisableSmartCard(USART_T* usart)
{
    usart->CTRL5_B.SMEN = BIT_RESET;
}

/*!
 * @brief       Enables NACK transmission
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_EnableSmartCardNACK(USART_T* usart)
{
    usart->CTRL5_B.NACKEN = BIT_SET;
}

/*!
 * @brief       Disable NACK transmission
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_DisableSmartCardNACK(USART_T* usart)
{
    usart->CTRL5_B.NACKEN = BIT_RESET;
}

/*!
 * @brief       Set USART Receiver in mute mode
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_EnableMuteMode(USART_T* usart)
{
    usart->CTRL2_B.RMM = BIT_SET;
}

/*!
 * @brief       Set USART Receiver in mute mode
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_DisableMuteMode(USART_T* usart)
{
    usart->CTRL2_B.RMM = BIT_RESET;
}

/*!
 * @brief       Selects the USART WakeUp method
 *
 * @param       usart:    Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       wakeup:   Specifies the USART wakeup method
 *
 * @retval      None
 *
 * @note
 */
void USART_ConfigMuteModeWakeUp(USART_T* usart, USART_WAKEUP_T wakeup)
{
    usart->CTRL1_B.WMS = wakeup;
}

/*!
 * @brief       Returns the most recent received data(8 bit) by the USART peripheral
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      The received 8 bit data
 *
 * @note
 */
uint8_t USART_RxData8(USART_T* usart)
{
  return ((uint8_t)usart->DATA);
}

/*!
 * @brief       Returns the most recent received data(9 bit) by the USART peripheral
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      The received 9 bit data
 *
 * @note
 */
uint16_t USART_RxData9(USART_T* usart)
{
  uint16_t temp = 0;

  temp = (uint16_t)(usart->CTRL1_B.RDB8 << 8);
  temp |= usart->DATA_B.DATA;

  return temp;
}

/*!
 * @brief       Transmits 8 bit data through the USART peripheral
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       data:   The data(8 bit) to transmit
 *
 * @retval      None
 *
 * @note
 */
void USART_TxData8(USART_T* usart, uint8_t data)
{
  usart->DATA_B.DATA = data;
}

/*!
 * @brief       Transmits 9 bit data through the USART peripheral
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       data:   The data(9 bit) to transmit
 *
 * @retval      None
 *
 * @note
 */
void USART_TxData9(USART_T* usart, uint16_t data)
{
    usart->CTRL1_B.TDB8 = (data >> 8) & 0X01;
    usart->DATA_B.DATA = (uint8_t)data;
}

/*!
 * @brief       Transmits break characters
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @retval      None
 *
 * @note
 */
void USART_TxBreak(USART_T* usart)
{
    usart->CTRL2_B.TXBRK = BIT_SET;
}

/*!
 * @brief       Sets the address of the USART node
 *
 * @param       usart:      Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       address:    Indicates the address of the USART node
 *
 * @retval      None
 *
 * @note
 */
void USART_Address(USART_T* usart, uint8_t address)
{
    usart->CTRL4_B.ADDR = address;
}

/*!
 * @brief       Sets the specified USART guard time
 *
 * @param       usart:      Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       guardTime:  Specifies the guard time
 *
 * @retval      None
 *
 * @note
 */
void USART_ConfigGuardTime(USART_T* usart, uint8_t guardTime)
{
    usart->GTS_B.GTS = guardTime;
}

/*!
 * @brief       Sets the system clock divider number
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       div:    Specifies the divider number
 *
 * @retval      None
 *
 * @note
 */
void USART_ConfigDivNumber(USART_T* usart, uint8_t div)
{
    usart->DIV_B.PSC = div;
}

/*!
 * @brief       Synchronous communication clock configuration
 *
 * @param       usart:              Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       SyncClockConfig:    Pointer to a USART_SyncClockConfig_T structure that
 *                                  contains the configuration information for the clock
 *
 * @retval      None
 *
 * @note
 */
void USART_ConfigSyncClock(USART_T* usart, USART_SyncClockConfig_T *SyncClockConfig)
{
    usart->CTRL3_B.CLKEN = SyncClockConfig->enable;
    usart->CTRL3_B.CLKPHA = SyncClockConfig->phase;
    usart->CTRL3_B.CLKPOL = SyncClockConfig->polarity;
    usart->CTRL3_B.LBCP = SyncClockConfig->lastBitClock;
}

/*!
 * @brief       Fills each SyncClockConfig member with its default value
 *
 * @param       SyncClockConfig:    Pointer to a USART_SyncClockConfig_T structure
 *
 * @retval      None
 *
 * @note
 */
void USART_ConfigSyncClockStructInit(USART_SyncClockConfig_T *SyncClockConfig)
{
    SyncClockConfig->enable = USART_CLKEN_DISABLE;
    SyncClockConfig->phase = USART_CLKPHA_1EDGE;
    SyncClockConfig->polarity = USART_CLKPOL_HIGH;
    SyncClockConfig->lastBitClock = USART_LBCP_ENABLE;
}

/*!
 * @brief       Read the specified USART flag
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       flag:   Specifies the flag to check
 *                      The parameter can be combination of following values:
 *                      @arg USART_FLAG_TXBE:   Transmit buffer data register empty flag
 *                      @arg USART_FLAG_TXC:    Transmission complete flag
 *                      @arg USART_FLAG_RXBNE:  Read buffer data register not empty flag
 *                      @arg USART_FLAG_IDLEE:  IDLE line detected flag
 *                      @arg USART_FLAG_OVREE:  Overrun error flag
 *                      @arg USART_FLAG_NE:     Noise error flag
 *                      @arg USART_FLAG_FE:     Framing error flag
 *                      @arg USART_FLAG_PE:     Parity error flag
 *                      @arg USART_FLAG_LBD:    LIN Break Detection Flag
 *
 * @retval      The new state of flag (SET or RESET)
 *
 * @note
 */
uint8_t USART_ReadStatusFlag(USART_T* usart, uint16_t flag)
{
    uint8_t flag1;
    uint8_t flag2;
    uint8_t status1 = 0;
    uint8_t status2 = 0;

    flag1 = (uint8_t)(flag & 0xff);
    flag2 = (uint8_t)((flag >> 8) & 0xff);

    /** TXBE/TXC/RXBNE/IDLE/OVRE/NE/FE/PE */
    if(flag1)
    {
        status1 = (uint8_t)(usart->STS & (uint32_t)flag1);
    }

    /** LBD */
    if(flag2)
    {
        status2 = (uint8_t)(usart->CTRL4 & (uint32_t)flag2);
    }

    if((flag1 == status1) && flag2 == status2)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear the specified USART flag
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       flag:   Specifies the flag to check
 *                      The parameter can be combination of following values:
 *                      @arg USART_FLAG_RXBNE:  Read buffer data register not empty flag
 *                      @arg USART_FLAG_LBD:    LIN Break Detection Flag
 *
 * @retval      None
 *
 * @note
 */
void USART_ClearStatusFlag(USART_T* usart, uint16_t flag)
{
    if(flag & 0xff)
    {
        usart->STS &= (uint32_t)~(flag & 0XFF);
    }

    if(flag & 0xff00)
    {
        usart->CTRL4 &= (uint32_t)~((flag >> 8) & 0XFF);
    }
}

/*!
 * @brief       Read the specified USART interrupt flag
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       flag:   Specifies the USART interrupt flag to check
 *                      The parameter can be one of following values:
 *                      @arg USART_INT_FLAG_PE:     Parity error interrupt flag
 *                      @arg USART_INT_FLAG_IDLE:   IDLE line interrupt flag
 *                      @arg USART_INT_FLAG_RX:     Receiver interrupt flag
 *                      @arg USART_INT_FLAG_TXC:    Transmission complete interrupt flag
 *                      @arg USART_INT_FLAG_TX:     Transmitter interrupt flag
 *                      @arg USART_INT_FLAG_LBD:    LIN Break Detection Interrupt flag
 *
 * @retval      None
 *
 * @note
 */
uint8_t USART_ReadIntFlag(USART_T* usart, USART_INT_FLAG_T flag)
{
    uint32_t intEnable;
    uint32_t intFlag;

    if(flag & 0x100)
    {
        intEnable = usart->CTRL1;
        intFlag = usart->STS;
    }
    else if(flag & 0x200)
    {
        intEnable = usart->CTRL2;
        intFlag = usart->STS;
    }
    else if(flag & 0x400)
    {
        intEnable = usart->CTRL4;
        intFlag = usart->CTRL4;
    }

    intFlag &= flag & 0xff;
    intEnable &= (flag >> 16) & 0xff;

    if(intFlag && intEnable)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clears the USART interrupt pending bits
 *
 * @param       usart:  Select the the USART peripheral.It can be USART1/USART2
 *
 * @param       flag:   Specifies the USART interrupt flag to check
 *                      The parameter can be one of following values:
 *                      @arg USART_INT_FLAG_RX:     Receiver interrupt flag
 *                      @arg USART_INT_FLAG_LBD:    LIN Break Detection Interrupt flag
 *
 * @retval      None
 *
 * @note
 */
void USART_ClearIntFlag(USART_T* usart, USART_INT_FLAG_T flag)
{
    if(flag & 0x400)
    {
        usart->CTRL4 &= (uint32_t) ~(flag);
    }
    else if(flag & 0x200)
    {
        usart->STS &= (uint32_t) ~(flag);
    }
}

/**@} end of group USART_Fuctions*/
/**@} end of group USART_Driver */
/**@} end of group Peripherals_Library*/

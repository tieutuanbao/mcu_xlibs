/*!
 * @file        apm32f00x_spi.c
 *
 * @brief       This file contains all the functions for the SPI peripheral
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

#include "apm32f00x_spi.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup SPI_Driver SPI Driver
  @{
*/

/** @addtogroup SPI_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the SPI peripheral registers to their default reset values
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_Reset(void)
{
    SPI->CTRL1 = SPI_CTRL1_RESET_VALUE;
    SPI->CTRL2 = SPI_CTRL2_RESET_VALUE;
    SPI->INTCTRL = SPI_INTCTRL_RESET_VALUE;
    SPI->STS = SPI_STS_RESET_VALUE;
    SPI->CRCPOLY = SPI_CRCPOLY_RESET_VALUE;
}

/*!
 * @brief       Config the I2C peripheral according to the specified parameters in the spiConfig
 *
 * @param       spiConfig:  Pointer to a SPI_Config_T structure that
 *                          contains the configuration information for the SPI peripheral
 *
 * @retval      None
 *
 * @note
 */
void SPI_Config(SPI_Config_T *spiConfig)
{
    SPI->CTRL1_B.CLKPHA = spiConfig->phase;
    SPI->CTRL1_B.CLKPOL = spiConfig->polarity;
    SPI->CTRL1_B.BRC = spiConfig->baudrateDiv;
    SPI->CTRL1_B.LSBF = spiConfig->firstBit;

    SPI->CTRL2 &= 0xffffff3b;
    SPI->CTRL2 |= (uint32_t)spiConfig->direction;

    SPI->CTRL2_B.SSC = spiConfig->slaveSelect;
    SPI->CTRL2_B.ISS = spiConfig->mode;

    SPI->CTRL1_B.MSTMODE = spiConfig->mode;

    SPI->INTCTRL = (uint32_t)spiConfig->interrupt;
}

/*!
 * @brief       Fills each spiConfig member with its default value
 *
 * @param       spiConfig:  Pointer to a SPI_Config_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void SPI_ConfigStructInit(SPI_Config_T *spiConfig)
{
    spiConfig->mode = SPI_MODE_SLAVE;
    spiConfig->phase = SPI_CLKPHA_1EDGE;
    spiConfig->polarity = SPI_CLKPOL_HIGH;
    spiConfig->slaveSelect = SPI_SSC_DISABLE;
    spiConfig->interrupt = SPI_INT_NONE;
    spiConfig->firstBit = SPI_FIRST_BIT_MSB;
    spiConfig->direction = SPI_DIRECTION_2LINES_FULLDUPLEX;
    spiConfig->baudrateDiv = SPI_BAUDRATE_DIV_2;
}

/*!
 * @brief       Enable the SPI peripheral
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_Enable(void)
{
    SPI->CTRL1_B.SPIEN = ENABLE;
}

/*!
 * @brief       Disable the SPI peripheral
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_Disable(void)
{
    SPI->CTRL1_B.SPIEN = DISABLE;
}

/*!
 * @brief       Mode configuration
 *
 * @param       mode:   Specifies the mode
 *
 * @retval      None
 *
 * @note
 */
void SPI_ConfigMode(SPI_MODE_T mode)
{
    SPI->CTRL2_B.ISS = mode;

    SPI->CTRL1_B.MSTMODE = mode;
}

/*!
 * @brief       Enables the specified interrupts
 *
 * @param       interrupt:  Specifies the SPI interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg SPI_INT_WAKEUP:    Wakeup interrupt
 *                          @arg SPI_INT_ERROR:     Error interrupt
 *                          @arg SPI_INT_RXBNE:     Receive buffer not empty interrupt
 *                          @arg SPI_INT_TXE:       Transmit buffer empty interrupt
 *
 * @retval      None
 *
 * @note
 */
void SPI_EnableInterrupt(uint8_t interrupt)
{
    SPI->INTCTRL |= (uint32_t)interrupt;
}

/*!
 * @brief       Disable the specified interrupts
 *
 * @param       interrupt:  Specifies the SPI interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg SPI_INT_WAKEUP:    Wakeup interrupt
 *                          @arg SPI_INT_ERROR:     Error interrupt
 *                          @arg SPI_INT_RXBNE:     Receive buffer not empty interrupt
 *                          @arg SPI_INT_TXE:       Transmit buffer empty interrupt
 *
 * @retval      None
 *
 * @note
 */
void SPI_DisableInterrupt(uint8_t interrupt)
{
    SPI->INTCTRL &= (uint32_t)~interrupt;
}

/*!
 * @brief       Transmits a Data
 *
 * @param       data:   Byte to be transmitted
 *
 * @retval      None
 *
 * @note
 */
void SPI_TxData(uint8_t data)
{
    SPI->DATA = (uint32_t)data;
}

/*!
 * @brief       Returns the most recent received data by the SPI peripheral
 *
 * @param       None
 *
 * @retval      The value of the received data
 *
 * @note
 */
uint8_t SPI_RxData(void)
{
   return ((uint8_t)SPI->DATA);
}

/*!
 * @brief       Enable Software Select Slave
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_EnableSlaveSoftwareControl(void)
{
    SPI->CTRL2_B.SSC = BIT_SET;
}

/*!
 * @brief       Disable Software Select Slave
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_DisableSlaveSoftwareControl(void)
{
    SPI->CTRL2_B.SSC = BIT_RESET;
}


/*!
 * @brief       Transmit CRC value
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_TxCRC(void)
{
    SPI->CTRL2_B.CRCNXT = BIT_SET;
}

/*!
 * @brief       Enables the CRC value calculation of the transferred bytes
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_EnableCRC(void)
{
    SPI->CTRL2_B.CRCEN = BIT_SET;
}

/*!
 * @brief       Disable the CRC value calculation of the transferred bytes
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_DisableCRC(void)
{
    SPI->CTRL2_B.CRCEN = BIT_RESET;
}

/*!
 * @brief       Returns the receive CRC register value
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
uint8_t SPI_ReadRxCRC(void)
{
    return(uint8_t)SPI->RXCRC;
}

/*!
 * @brief       Returns the transmit CRC register value
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
uint8_t SPI_ReadTxCRC(void)
{
    return(uint8_t)SPI->TXCRC;
}

/*!
 * @brief       Set the CRC polynomial
 *
 * @param       polynomial: Specifies the CRC polynomial
 *
 * @retval      None
 *
 * @note
 */
void SPI_SetCRCPolynomial(uint8_t polynomial)
{
    SPI->CRCPOLY = (uint32_t)polynomial;
}

/*!
 * @brief       Returns the CRC Polynomial register value
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
uint8_t SPI_ReadCRCPolynomial(void)
{
    return(uint8_t)SPI->CRCPOLY;
}


/*!
 * @brief       Checks whether the specified SPI flag is set or not
 *
 * @param       flag:   Specifies the flag to check
 *                      This parameter can be any combination of the following values:
 *                      @arg SPI_FLAG_RXBNE:    Receive buffer not empty flag
 *                      @arg SPI_FLAG_TXBE:     Transmit buffer empty flag
 *                      @arg SPI_FLAG_WAKEUP:   Wakeup flag
 *                      @arg SPI_FLAG_CRCE:     CRC error flag
 *                      @arg SPI_FLAG_MME:      Master mode error flag
 *                      @arg SPI_FLAG_RXO:      Receive Overrun flag
 *                      @arg SPI_FLAG_BUSY:     Busy flag
 *
 * @retval      The new state of flag (SET or RESET)
 *
 * @note
 */
uint8_t SPI_ReadStatusFlag(uint8_t flag)
{
    uint8_t status;

    status = (uint8_t)(SPI->STS & flag);

    if(status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear the specified SPI flag
 *
 * @param       flag:   Specifies the flag to clear
 *                      This parameter can be any combination of the following values:
 *                      @arg SPI_FLAG_CRCE:     CRC error flag
 *                      @arg SPI_FLAG_WAKEUP:   Wakeup flag
 *
 * @retval      None
 *
 * @note
 */
void SPI_ClearStatusFlag(uint8_t flag)
{
    SPI->STS &= (uint32_t)~flag;
}


/*!
 * @brief       Checks whether the specified interrupt has occurred or not
 *
 * @param       flag:   Specifies the SPI interrupt pending bit to check
 *                      This parameter can be one of the following values:
 *                      @arg SPI_INT_FLAG_RXBNE:    Receive buffer not empty flag
 *                      @arg SPI_INT_FLAG_TXBE:     Transmit buffer empty flag
 *                      @arg SPI_INT_FLAG_WAKEUP:   Wakeup flag
 *                      @arg SPI_INT_FLAG_CRCE:     CRC error flag
 *                      @arg SPI_INT_FLAG_MME:      Master mode error flag
 *                      @arg SPI_INT_FLAG_RXO:      Receive Overrun flag
 *
 * @retval      None
 *
 * @note
 */
uint8_t SPI_ReadIntFlag(SPI_INT_FLAG_T flag)
{
    uint8_t intEnable;
    uint8_t intStatus;

    intEnable = (uint8_t)(SPI->INTCTRL & (uint32_t)(flag >> 8));

    intStatus = (uint8_t)(SPI->STS & (uint32_t)(flag & 0xff));

    if(intEnable && intStatus)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clears the specified interrupt pending bits
 *
 * @param       flag:   Specifies the SPI interrupt pending bit to check
 *                      This parameter can be one of the following values:
 *                      @arg SPI_INT_FLAG_WAKEUP:   Wakeup flag
 *                      @arg SPI_INT_FLAG_CRCE:     CRC error flag
 *
 * @retval      None
 *
 * @note
 */

void SPI_ClearIntFlag(SPI_INT_FLAG_T flag)
{
    SPI->STS &= (uint32_t)~(flag & 0xff);
}

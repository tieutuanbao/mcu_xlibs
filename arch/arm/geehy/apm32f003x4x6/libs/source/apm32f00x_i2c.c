/*!
 * @file        apm32f00x_i2c.c
 *
 * @brief       This file contains all the functions for the I2C peripheral
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

#include "apm32f00x_i2c.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup I2C_Driver I2C Driver
  @{
*/

/** @addtogroup I2C_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the I2C peripheral registers to their default reset values
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_Reset(void)
{
    I2C->CTRL1 = I2C_CTRL1_RESET_VALUE;
    I2C->CTRL2 = I2C_CTRL2_RESET_VALUE;
    I2C->CLKFREQ = I2C_CLKFREQ_RESET_VALUE;
    I2C->ADDR0 = I2C_ADDR0_RESET_VALUE;
    I2C->ADDR1 = I2C_ADDR1_RESET_VALUE;
    I2C->INTCTRL = I2C_INTCTRL_RESET_VALUE;
    I2C->CLKCTRL1 = I2C_CLKCTRL1_RESET_VALUE;
    I2C->CLKCTRL2 = I2C_CLKCTRL2_RESET_VALUE;
    I2C->MRT = I2C_MRT_RESET_VALUE;
}

/*!
 * @brief       Config the I2C peripheral according to the specified parameters in the i2cConfig
 *
 * @param       i2cConfig:  Pointer to a I2C_Config_T structure that
 *                          contains the configuration information for the I2C peripheral
 * @retval      None
 *
 * @note
 */
void I2C_Config(I2C_Config_T *i2cConfig)
{
    uint32_t temp = 1;

    /** Disable I2C */
    I2C->CTRL1_B.I2CEN = BIT_RESET;

    I2C->CLKFREQ_B.FREQ = i2cConfig->inputClkFreqMhz & 0x3f;

    /** fast mode */
    if(i2cConfig->outputClkFreqHz > I2C_STANDARD_MODE_MAX_FREQ)
    {
        I2C->CLKCTRL2_B.FASTMODE = BIT_SET;

        if(i2cConfig->dutyCycle == I2C_DUTYCYCLE_16_9)
        {
            temp = (uint32_t) ((uint32_t)(i2cConfig->inputClkFreqMhz * 1000000) / (i2cConfig->outputClkFreqHz * 25));
        }
        else
        {
            temp = (uint32_t) ((uint32_t)(i2cConfig->inputClkFreqMhz * 1000000) / (i2cConfig->outputClkFreqHz * 3));
        }

        if(temp < 1)
        {
            temp = 1;
        }

        /** Set Maximum Rise Time: 300ns max in Fast Mode */
        I2C->MRT = (uint8_t)(((i2cConfig->inputClkFreqMhz * 3) / 10) + 1);
    }

    /** standard mode */
    else
    {
        temp = (uint32_t) ((uint32_t)(i2cConfig->inputClkFreqMhz * 1000000) / (i2cConfig->outputClkFreqHz * 2));
        if(temp < 4)
        {
            temp = 4;
        }

        /** Set Maximum Rise Time: 1000ns max in Standard Mode */
        I2C->MRT = (i2cConfig->inputClkFreqMhz + 1);
    }

    /** clock Configuration */
    I2C->CLKCTRL1 = temp & 0XFF;
    I2C->CLKCTRL2_B.CLKCTRL = (temp >> 8) & 0X0F;
    I2C->CLKCTRL2_B.FMDC = i2cConfig->dutyCycle;

    /** Enable I2C */
    I2C->CTRL1_B.I2CEN = BIT_SET;

    /** Addreess Configuration */
    I2C->ADDR0 = i2cConfig->addr & 0XFF;
    I2C->ADDR1_B.ADDR = i2cConfig->addr >> 8;
    I2C->ADDR1_B.ADDRMODE = i2cConfig->addrMode;
    I2C->ADDR1_B.ADDRCFG = BIT_SET;

    /** acknowledge Configuration */
    I2C->CTRL2_B.ACKEN = (i2cConfig->ack >> 4) & 0x01;
    I2C->CTRL2_B.ACKPOS = i2cConfig->ack & 0X01;

    I2C->INTCTRL = (uint32_t)i2cConfig->interrupt;
}

/*!
 * @brief       Fills each i2cConfig member with its default value
 *
 * @param       i2cConfig:    Pointer to a I2C_Config_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void I2C_ConfigStructInit(I2C_Config_T *i2cConfig)
{
    i2cConfig->ack = I2C_ACK_CURRENT;
    i2cConfig->addr = 0;
    i2cConfig->addrMode = I2C_ADDR_7_BIT;
    i2cConfig->dutyCycle = I2C_DUTYCYCLE_2;
    i2cConfig->inputClkFreqMhz = 48;
    i2cConfig->interrupt = I2C_INT_NONE;
    i2cConfig->outputClkFreqHz = 100000;
}

/*!
 * @brief       Enables the I2C peripheral
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_Enable(void)
{
    I2C->CTRL1_B.I2CEN = BIT_SET;
}

/*!
 * @brief       Disable the I2C peripheral
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_Disable(void)
{
    I2C->CTRL1_B.I2CEN = BIT_RESET;
}

/*!
 * @brief       Disable the I2C response broadcast
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_DisableBroadcastCall(void)
{
    I2C->CTRL1_B.BCEN = BIT_RESET;
}

/*!
 * @brief       Enable the I2C response broadcast
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_EnableBroadcastCall(void)
{
    I2C->CTRL1_B.BCEN = BIT_SET;
}

/*!
 * @brief       Enable Generates I2C communication START condition
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_EnableGenerateStart(void)
{
    I2C->CTRL2_B.START = BIT_SET;
}

/*!
 * @brief       Disable Generates I2C communication START condition
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_DisableGenerateStart(void)
{
    I2C->CTRL2_B.START = BIT_RESET;
}

/*!
 * @brief       Enable Generates I2C communication STOP condition
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_EnableGenerateStop(void)
{
    I2C->CTRL2_B.STOP = BIT_SET;
}

/*!
 * @brief       Disable Generates I2C communication STOP condition
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_DisableGenerateStop(void)
{
    I2C->CTRL2_B.STOP = BIT_RESET;
}

/*!
 * @brief       Enables I2C software reset
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_EnableSoftwareReset(void)
{
    I2C->CTRL2_B.SWRST = BIT_SET;
}

/*!
 * @brief       Disables I2C software reset
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_DisableSoftwareReset(void)
{
    I2C->CTRL2_B.SWRST = BIT_RESET;
}

/*!
 * @brief       Enables the I2C clock stretching
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_EnableStretchClock(void)
{
    I2C->CTRL1_B.STRDIS = BIT_RESET;
}

/*!
 * @brief       Disables the I2C clock stretching
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2C_DisableStretchClock(void)
{
    I2C->CTRL1_B.STRDIS = BIT_SET;
}

/*!
 * @brief       Enable or Disable the I2C acknowledge and position acknowledge feature
 *
 * @param       ack:    Specifies the acknowledge mode to apply
 *
 * @retval      None
 *
 * @note
 */
void I2C_ConfigAcknowledge(I2C_ACK_T ack)
{
    I2C->CTRL2_B.ACKEN = (ack >> 4) & 0X01;
    I2C->CTRL2_B.ACKPOS = ack & 0X01;
}

/*!
 * @brief       Enables the specified I2C interrupt
 *
 * @param       interrupt:  Specifies the I2C interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg I2C_INT_ERROR:     Error interruption
 *                          @arg I2C_INT_EVENT:     Event interruption
 *                          @arg I2C_INT_BUFFER:    Buffer interruption
 *
 * @retval      None
 *
 * @note
 */
void I2C_EnableInterrupt(uint8_t interrupt)
{
    I2C->INTCTRL |= interrupt;
}

/*!
 * @brief       Disable the specified I2C interrupt
 *
 * @param       interrupt:  Specifies the I2C interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg I2C_INT_ERROR:     Error interruption
 *                          @arg I2C_INT_EVENT:     Event interruption
 *                          @arg I2C_INT_BUFFER:    Buffer interruption
 *
 * @retval      None
 *
 * @note
 */
void I2C_DisableInterrupt(uint8_t interrupt)
{
    I2C->INTCTRL &= (uint32_t)~interrupt;
}

/*!
 * @brief       Selects the specified I2C fast mode duty cycle
 *
 * @param       dutyCycle:  Specifies the duty cycle to apply
 *
 * @retval      None
 *
 * @note
 */
void I2C_ConfigDutyCycle(I2C_DUTY_CYCLE_T dutyCycle)
{
    I2C->CLKCTRL2_B.FMDC = dutyCycle;
}

/*!
 * @brief       Returns the most recent received data
 *
 * @param       None
 *
 * @retval      The value of the received byte data
 *
 * @note
 */
uint8_t I2C_RxData(void)
{
    return(uint8_t)I2C->DATA;
}

/*!
 * @brief       Transmits the 7-bit address (to select the) slave device
 *
 * @param       address:    Specifies the slave address which will be transmitted
 *
 * @param       direction:  Specifies whether the I2C device will be a Transmitter or a Receiver
 *
 * @retval      None
 *
 * @note
 */
void I2C_TxAddress7Bit(uint8_t address, I2C_DIRECTION_T direction)
{
    I2C->DATA = (uint32_t)((address & 0XFE) | direction);
}


/*!
 * @brief       Send a byte by writing in the DR register
 *
 * @param       data:   Byte to be sent
 *
 * @retval      None
 *
 * @note
 */
void I2C_TxData(uint8_t data)
{
    I2C->DATA = (uint32_t)data;
}

/*!
 * @brief       Checks whether the specified I2C flag is set or not
 *
 * @param       flag:   Specifies the flag to check
 *                      This parameter can be any combination of the following values:
 *                      @arg I2C_FLAG_TXBE:         Transmit Buffer Data Register Empty flag
 *                      @arg I2C_FLAG_RXBNE:        Read Buffer Data Register Not Empty flag
 *                      @arg I2C_FLAG_STOP:         Stop detected flag
 *                      @arg I2C_FLAG_ADDR10:       10-bit Header sent flag
 *                      @arg I2C_FLAG_BTC:          Data Byte Transfer complete flag
 *                      @arg I2C_FLAG_ADDR:         Address Sent/Matched (master/slave) flag
 *                      @arg I2C_FLAG_START:        Start bit sent flag
 *                      @arg I2C_FLAG_WAKEUP:       Wake Up From Halt Flag
 *                      @arg I2C_FLAG_OUF:          Overrun/Underrun Flag
 *                      @arg I2C_FLAG_ACKERR:       Acknowledge Error Flag
 *                      @arg I2C_FLAG_ARBLOST:      Arbitration Loss Flag
 *                      @arg I2C_FLAG_BUSERR:       Bus Error Flag
 *                      @arg I2C_FLAG_BROADCAST:    Broadcast header received Flag
 *                      @arg I2C_FLAG_RWMF:         Transmitter/Receiver data flag
 *                      @arg I2C_FLAG_BUSBUSY:      Bus Busy Flag
 *                      @arg I2C_FLAG_MMF:          Master/Slave mode flag
 *
 * @retval      None
 *
 * @note
 */
uint8_t I2C_ReadStatusFlag(uint32_t flag)
{
    uint8_t flag1;
    uint8_t flag2;
    uint8_t flag3;
    uint8_t status1 = 0;
    uint8_t status2 = 0;
    uint8_t status3 = 0;

    flag1 = (uint8_t)(flag & 0xff);
    flag2 = (uint8_t)(flag >> 8) & 0xff;
    flag3 = (uint8_t)(flag >> 16) & 0xff;

    if(flag1)
    {
        status1 = (uint8_t)(I2C->STS1 & flag1);
    }

    if(flag2)
    {
        status2 = (uint8_t)(I2C->STS2 & flag2);
    }

    if(flag3)
    {
        status3 = (uint8_t)(I2C->STS3 & flag3);
    }

    if((status1 == flag1) && (status2 == flag2) && (status3 == flag3))
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear flags
 *
 * @param       flag:   Specifies the flag to clear
 *                      This parameter can be any combination of the following values:
 *                      @arg I2C_FLAG_WAKEUP:   Wakeup from Halt
 *                      @arg I2C_FLAG_OUF:      Overrun/Underrun Flag
 *                      @arg I2C_FLAG_ACKERR:   Acknowledge Error Flag
 *                      @arg I2C_FLAG_ARBLOST:  Arbitration Loss Flag
 *                      @arg I2C_FLAG_BUSERR:   Bus Error Flag
 * @retval      None
 *
 * @note
 */
void I2C_ClearStatusFlag(uint32_t flag)
{
    if(flag & 0xff00)
    {
        I2C->STS2 &= (uint32_t)~((flag >> 8) & 0xff);
    }
}

/*!
 * @brief       Checks whether the specified I2C interrupt has occurred or not
 *
 * @param       flag:   Specifies the interrupt source to check
 *                      This parameter can be one of the following values:
 *                      @arg I2C_INT_FLAG_TXBE:     Transmit Buffer Data Register Empty flag
 *                      @arg I2C_INT_FLAG_RXBNE:    Read Buffer Data Register Not Empty flag
 *                      @arg I2C_INT_FLAG_STOP:     Stop detected flag
 *                      @arg I2C_INT_FLAG_ADDR10:   10-bit Header sent flag
 *                      @arg I2C_INT_FLAG_BTC:      Data Byte Transfer complete flag
 *                      @arg I2C_INT_FLAG_ADDR:     Address Sent/Matched (master/slave) flag
 *                      @arg I2C_INT_FLAG_START:    Start bit sent flag
 *                      @arg I2C_INT_FLAG_WAKEUP:   Wake Up From Halt Flag
 *                      @arg I2C_INT_FLAG_OUF:      Overrun/Underrun Flag
 *                      @arg I2C_INT_FLAG_ACKERR:   Acknowledge Error Flag
 *                      @arg I2C_INT_FLAG_ARBLOST:  Arbitration Loss Flag
 *                      @arg I2C_INT_FLAG_BUSERR:   Bus Error Flag
 *
 * @retval      Status of interrupt flag(SET or RESET)
 *
 * @note
 */
uint8_t I2C_ReadIntFlag(I2C_INT_FLAG_T flag)
{
    uint32_t intEnable;
    uint32_t status;

    intEnable = flag >> 16;

    intEnable = I2C->INTCTRL & intEnable;

    if(flag & 0x100)
    {
        status = (uint32_t)I2C->STS1 & flag & 0XFF;
    }
    else if(flag & 0x200)
    {
        status = (uint32_t)I2C->STS2 & flag & 0XFF;
    }

    if(status && intEnable)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear interrupt pending bit
 *
 * @param       flag:   Specifies the interrupt pending bit to clear
 *                      This parameter can be one of the following values:
 *                      @arg I2C_INT_FLAG_WAKEUP:   Wake Up From Halt Flag
 *                      @arg I2C_INT_FLAG_OUF:      Overrun/Underrun Flag
 *                      @arg I2C_INT_FLAG_ACKERR:   Acknowledge Error Flag
 *                      @arg I2C_INT_FLAG_ARBLOST:  Arbitration Loss Flag
 *                      @arg I2C_INT_FLAG_BUSERR:   Bus Error Flag
 * @retval      None
 *
 * @note
 */
void I2C_ClearIntFlag(I2C_INT_FLAG_T flag)
{
    if(flag & 0x200)
    {
        I2C->STS2 &= (uint32_t)~(flag & 0xff);
    }
}

/**@} end of group I2C_Fuctions*/
/**@} end of group I2C_Driver */
/**@} end of group Peripherals_Library*/

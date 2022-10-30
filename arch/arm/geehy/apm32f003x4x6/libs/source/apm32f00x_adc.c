/*!
 * @file        apm32f00x_adc.c
 *
 * @brief       This file contains all the functions for the ADC peripheral
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

#include "apm32f00x_adc.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/

/** @addtogroup ADC_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the ADC peripheral registers to their default reset values
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_Reset(void)
{
    ADC->CSTS = ADC_CSTS_RESET_VALUE;

    ADC->CTRL1 = ADC_CTRL1_RESET_VALUE;
    ADC->CTRL2 = ADC_CTRL2_RESET_VALUE;
    ADC->CTRL3 = ADC_CTRL3_RESET_VALUE;
    ADC->CTRL4 = ADC_CTRL4_RESET_VALUE;

    ADC->STD1 = ADC_STD1_RESET_VALUE;
    ADC->STD0 = ADC_STD0_RESET_VALUE;

    ADC->AWDHT1 = ADC_AWDHT1_RESET_VALUE;
    ADC->AWDHT0 = ADC_AWDHT0_RESET_VALUE;

    ADC->AWDLT1 = ADC_AWDLT1_RESET_VALUE;
    ADC->AWDLT0 = ADC_AWDLT0_RESET_VALUE;

    ADC->AWDEN1 = ADC_AWDEN1_RESET_VALUE;
    ADC->AWDEN0 = ADC_AWDEN0_RESET_VALUE;

    ADC->OFFSET = ADC_OFFSET_RESET_VALUE;
}

/*!
 * @brief       Config the ADC peripheral according to the specified parameters in the adcConfig
 *
 * @param       adcConfig:  Pointer to a ADC_Config_T structure that
 *                          contains the configuration information for the ADC peripheral
 *
 * @retval      None
 *
 * @note
 */
void ADC_Config(ADC_Config_T *adcConfig)
{
    ADC->CTRL1_B.ADCON = BIT_RESET;
    ADC->CTRL1_B.DIVSEL = adcConfig->div;
    ADC->CTRL1_B.CCM = adcConfig->convMode;

    ADC->CTRL2_B.DAM = adcConfig->dataAlign;
    ADC->CTRL2_B.ETS = adcConfig->extTrig & 0x01;
    ADC->CTRL2_B.ETEN = (adcConfig->extTrig >> 4) & 0x01;

    ADC_SetChannel(adcConfig->channel);
    ADC->CTRL2_B.SMEN = adcConfig->scanMode;

    ADC->CSTS &= (uint32_t)~(ADC_INT_AWD | ADC_INT_CC);
    ADC->CSTS |= (uint32_t)adcConfig->interrupt;
}

/*!
 * @brief       Fills each adcConfig member with its default value
 *
 * @param       adcConfig:  Pointer to a ADC_Config_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void ADC_ConfigStructInit(ADC_Config_T *adcConfig)
{
    adcConfig->channel = ADC_CHANNEL_0;
    adcConfig->convMode = ADC_CONV_MODE_SINGLE;
    adcConfig->dataAlign = ADC_DATA_ALIGN_RIGHT;
    adcConfig->div = ADC_DIV_2;
    adcConfig->extTrig = ADC_EXTTRG_NONE;
    adcConfig->interrupt = ADC_INT_NONE;
    adcConfig->scanMode = ADC_SCAN_MODE_DISABLE;
}

/*!
 * @brief       ADC Delay Enable
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        if ADC clock frequency less than 14MHZ.ADC shoud be delayed
 */
void ADC_EnableDelay(void)
{
    ADC->CTRL4_B.GCMP = BIT_SET;
}

/*!
 * @brief       ADC Delay Disable
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        if ADC clock frequency less than 14MHZ.ADC shoud be delayed
 */
void ADC_DisableDelay(void)
{
    ADC->CTRL4_B.GCMP = BIT_RESET;
}

/*!
 * @brief       Enable the ADC peripheral
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_Enable(void)
{
    ADC->CTRL1_B.ADCON = BIT_SET;
}

/*!
 * @brief       Disable the ADC peripheral
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_Disable(void)
{
    ADC->CTRL1_B.ADCON = BIT_RESET;
}

/*!
 * @brief       Set ADC mode
 *
 * @param       mode:   ADC mode
 *
 * @retval      None
 *
 * @note
 */
void ADC_SetMode(ADC_MODE_T mode)
{
    ADC->CTRL4_B.DFS = mode;
}

/*!
 * @brief       Scan mode configuration
 *
 * @param       scanMode:   Specifies the scan mode
 *
 * @retval      None
 *
 * @note
 */
void ADC_ConfigScanMode(ADC_SCAN_MODE_T scanMode)
{
    ADC->CTRL2_B.SMEN = scanMode;
}

/*!
 * @brief       Enable the ADC data store into the Data Buffer registers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_EnableDataBuf(void)
{
    ADC->CTRL3_B.DBEN = BIT_SET;
}

/*!
 * @brief       Disable the ADC data store into the Data Buffer registers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_DisableDataBuf(void)
{
    ADC->CTRL3_B.DBEN = BIT_RESET;
}

/*!
 * @brief       Enable ADC interrupt
 *
 * @param       interrupt:  Specifies the I2C interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg ADC_INT_AWD: Analog watch dog interrupt
 *                          @arg ADC_INT_CC: Conversion completed interrupt
 *
 * @retval      None
 *
 * @note
 */
void ADC_EnableInterrupt(uint8_t interrupt)
{
    ADC->CSTS |= (uint32_t)interrupt;
}

/*!
 * @brief       Disable ADC interrupt
 *
 * @param       interrupt:  Specifies the I2C interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg ADC_INT_AWD: Analog watch dog interrupt
 *                          @arg ADC_INT_CC: Conversion completed interrupt
 *
 * @retval      None
 *
 * @note
 */
void ADC_DisableInterrupt(uint8_t interrupt)
{
    ADC->CSTS &= (uint32_t)~interrupt;
}

/*!
 * @brief       Configure the ADC divider selection
 *
 * @param       div:    Specifies the divider
 *
 * @retval      None
 *
 * @note
 */
void ADC_ConfigDivider(ADC_DIV_T div)
{
    ADC->CTRL1_B.DIVSEL = div;
}

/*!
 * @brief       Enable schmitt trigger
 *
 * @param       channel:    Specifies the channel that enable schmitt trigger
 *                          The parameter can be combination of following values:
 *                          @arg ADC_CHANNEL_0: channel 0
 *                          @arg ADC_CHANNEL_1: channel 1
 *                          @arg ADC_CHANNEL_2: channel 2
 *                          @arg ADC_CHANNEL_3: channel 3
 *                          @arg ADC_CHANNEL_4: channel 4
 *                          @arg ADC_CHANNEL_5: channel 5
 *                          @arg ADC_CHANNEL_6: channel 6
 *                          @arg ADC_CHANNEL_7: channel 7
 *
 * @retval      None
 *
 * @note
 */
void ADC_EnableSchmittTrigger(uint16_t channel)
{
    ADC->STD0 &= (uint32_t)~(channel & 0xff);

    ADC->STD1 &= (uint32_t)~((channel >> 8) & 0xff);
}

/*!
 * @brief       Disable schmitt trigger
 *
 * @param       channel:    Specifies the channel that  disable chmitt trigger
 *                          The parameter can be combination of following values:
 *                          @arg ADC_CHANNEL_0: channel 0
 *                          @arg ADC_CHANNEL_1: channel 1
 *                          @arg ADC_CHANNEL_2: channel 2
 *                          @arg ADC_CHANNEL_3: channel 3
 *                          @arg ADC_CHANNEL_4: channel 4
 *                          @arg ADC_CHANNEL_5: channel 5
 *                          @arg ADC_CHANNEL_6: channel 6
 *                          @arg ADC_CHANNEL_7: channel 7

 * @retval      None
 *
 * @note
 */
void ADC_DisableSchmittTrigger(uint16_t channel)
{
    ADC->STD0 |= (uint32_t)(channel & 0xff);

    ADC->STD1 |= (uint32_t)((channel >> 8) & 0xff);
}

/*!
 * @brief       Conversion mode configuration
 *
 * @param       convMode:   Specifies the conversion mode
 *
 * @retval      None
 *
 * @note
 */
void ADC_ConfigConversionMode(ADC_CONV_MODE_T convMode)
{
    ADC->CTRL1_B.CCM = convMode;
}

/*!
 * @brief       Conversion data alignment
 *
 * @param       dataAlign:  Specifies the data alignment
 *
 * @retval      None
 *
 * @note
 */
void ADC_ConfigDataAlign(ADC_DATA_ALIGN_T dataAlign)
{
    ADC->CTRL2_B.DAM = dataAlign;
}

/*!
 * @brief       Set ADC channel
 *
 * @param       channel:    Specifies the channel
 *
 * @retval      None
 *
 * @note
 */
void ADC_SetChannel(ADC_CHANNEL_T channel)
{
    uint16_t i;

    for(i = 0; i < 9; i++)
    {
        if(channel & (1 << i))
        {
            break;
        }
    }
    ADC->CTRL2_B.SMEN = ENABLE;

    ADC->CSTS_B.CHSEL = i & 0x0F;

    ADC->CTRL2_B.SMEN = DISABLE;
}

/*!
 * @brief       Set ADC differential input channel
 *
 * @param       channel
 *
 * @retval      None
 *
 * @note
 */
void ADC_SetDiffInputChannel(ADC_DIFF_CHANNEL_T channel)
{
    ADC->CSTS_B.CHSEL = channel;
}

/*!
 * @brief       Configure the ADC conversion on external trigger event
 *
 * @param       trigger:    Specifies the external trigger event
 *
 * @retval      None
 *
 * @note
 */
void ADC_ConfigExternalTrigger(ADC_EXTTRG_T trigger)
{
    ADC->CTRL2_B.ETS = trigger & 0x01;

    ADC->CTRL2_B.ETEN = (trigger >> 4) & 0x01;
}

/*!
 * @brief       Start ADC conversion
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        Enable the ADC peripheral before calling this function
 */
void ADC_StartConversion(void)
{
    ADC->CTRL1_B.ADCON = BIT_SET;
}

/*!
 * @brief       Read one sample of measured signal value
 *
 * @param       None
 *
 * @retval      Return the measured signal value
 *
 * @note
 */
uint16_t ADC_ReadData(void)
{
    uint16_t dataL;
    uint16_t dataH;
    uint16_t value;

    /** Right alignment */
    if(ADC->CTRL2_B.DAM == BIT_SET)
    {
        dataL = (uint16_t)(ADC->DATA0 & 0xff);
        dataH = (uint16_t)(ADC->DATA1 & 0x0f);

        value = (dataH << 8) | dataL;
    }

    /** Left alignment */
    else
    {
        dataH = (uint16_t)(ADC->DATA1 & 0xff);
        dataL = (uint16_t)(ADC->DATA0 & 0x0f);

        value = (dataH << 4) | dataL;
    }

    return value;
}

/*!
 * @brief       Enable the analog watchdog for the given channel
 *
 * @param       channel:    Specifies the channel
 *                          @arg ADC_CHANNEL_0: channel 0
 *                          @arg ADC_CHANNEL_1: channel 1
 *                          @arg ADC_CHANNEL_2: channel 2
 *                          @arg ADC_CHANNEL_3: channel 3
 *                          @arg ADC_CHANNEL_4: channel 4
 *                          @arg ADC_CHANNEL_5: channel 5
 *                          @arg ADC_CHANNEL_6: channel 6
 *                          @arg ADC_CHANNEL_7: channel 7
 *                          @arg ADC_CHANNEL_8: channel 8
 * @retval      None
 *
 * @note
 */
void ADC_EnableAnalogWatchdog(uint16_t channel)
{
    ADC->AWDEN0 |= (uint32_t)(channel & 0xff);

    ADC->AWDEN1 |= (uint32_t)((channel >> 8) & 0xff);
}


/*!
 * @brief       Disable the analog watchdog for the given channel
 *
 * @param       channel:    Specifies the channel
 *                          @arg ADC_CHANNEL_0: channel 0
 *                          @arg ADC_CHANNEL_1: channel 1
 *                          @arg ADC_CHANNEL_2: channel 2
 *                          @arg ADC_CHANNEL_3: channel 3
 *                          @arg ADC_CHANNEL_4: channel 4
 *                          @arg ADC_CHANNEL_5: channel 5
 *                          @arg ADC_CHANNEL_6: channel 6
 *                          @arg ADC_CHANNEL_7: channel 7
 *                          @arg ADC_CHANNEL_8: channel 8
 * @retval      None
 *
 * @note
 */
void ADC_DisableAnalogWatchdog(uint16_t channel)
{
    ADC->AWDEN0 &= (uint32_t)~(channel & 0xff);

    ADC->AWDEN1 &= (uint32_t)~((channel >> 8) & 0xff);
}

/*!
 * @brief       Set analog watchdog high threshold
 *
 * @param       threshold:  Specifies the high threshold value
 *
 * @retval      None
 *
 * @note
 */
void ADC_SetAWDThresholdHigh(uint16_t threshold)
{
    ADC->AWDHT1 = (uint32_t)((threshold >> 4) & 0xff);
    ADC->AWDHT0 = (uint32_t)(threshold & 0x0f);
}

/*!
 * @brief       Set analog watchdog low threshold
 *
 * @param       threshold:  Specifies the Low threshold value
 *
 * @retval      None
 *
 * @note
 */
void ADC_SetAWDThresholdLow(uint16_t threshold)
{
    ADC->AWDLT1 = (uint32_t)((threshold >> 4) & 0xff);
    ADC->AWDLT0 = (uint32_t)(threshold & 0x0f);
}

/*!
 * @brief       Read Buffer data
 *
 * @param       index:  Specifies the buffer index
 *
 * @retval      Return buffer data
 *
 * @note
 */
uint16_t ADC_ReadBufferData(ADC_BUFFER_IDX_T index)
{
    uint8_t buffIndex;
    uint16_t dataL;
    uint16_t dataH;
    uint16_t value;

    buffIndex = index << 1;

    /** Right alignment */
    if(ADC->CTRL2_B.DAM == BIT_SET)
    {
        dataL = (uint16_t)(ADC->DATABUF[buffIndex + 1] & 0xff);
        dataH = (uint16_t)(ADC->DATABUF[buffIndex] & 0x0f);

        value = dataL | (dataH << 8);
    }

    /** Left alignment */
    else
    {
        dataH = (uint16_t)(ADC->DATABUF[buffIndex] & 0xff);
        dataL = (uint16_t)(ADC->DATABUF[buffIndex + 1] & 0x0f);

        value = (dataH << 4) | dataL;
    }

    return value;
}

/*!
 * @brief       Read the specified analog watchdog channel status
 *
 * @param       channel:    Specifies the channel
 *                          The parameter can be one of following values:
 *                          @arg ADC_CHANNEL_0: channel 0
 *                          @arg ADC_CHANNEL_1: channel 1
 *                          @arg ADC_CHANNEL_2: channel 2
 *                          @arg ADC_CHANNEL_3: channel 3
 *                          @arg ADC_CHANNEL_4: channel 4
 *                          @arg ADC_CHANNEL_5: channel 5
 *                          @arg ADC_CHANNEL_6: channel 6
 *                          @arg ADC_CHANNEL_7: channel 7
 *                          @arg ADC_CHANNEL_8: channel 8

 * @retval      Status of the analog watchdog(SET or RESET)
 *
 * @note
 */
uint8_t ADC_ReadAnalogWatchdogStatus(ADC_CHANNEL_T channel)
{
    uint8_t status;

    if(channel & 0xff)
    {
        status = (uint8_t)(ADC->AWDS0 & channel & 0xff);
    }
    else
    {
        status = (uint8_t)(ADC->AWDS1 & (channel >> 8) & 0xff);
    }

    if(status)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Checks whether the specified ADC flag is set or not
 *
 * @param       flag:   Specifies the flag to check
 *                      The parameter can be one of following values:
 *                      @arg ADC_FLAG_AWD: Analog watch dog flag
 *                      @arg ADC_FLAG_CC:  Conversion completed flag
 *                      @arg ADC_FLAG_OVR: Overrun flag
 *
 * @retval      None
 *
 * @note
 */
uint8_t ADC_ReadStatusFlag(ADC_FLAG_T flag)
{
    uint8_t status;

    if(flag & 0x100)
    {
        status = (uint8_t)(ADC->CSTS & flag & 0xff);
    }
    else
    {
        status = (uint8_t)(ADC->CTRL3 & flag & 0xff);
    }

    if(status)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear the specified flag
 *
 * @param       flag:   Specifies the flag to clear
 * *                    The parameter can be one of following values:
 *                      @arg ADC_FLAG_AWD: Analog watch dog flag
 *                      @arg ADC_FLAG_CC:  Conversion completed flag
 *                      @arg ADC_FLAG_OVR: Overrun flag
 *
 * @retval      None
 *
 * @note
 */
void ADC_ClearStatusFlag(ADC_FLAG_T flag)
{
    if(flag & 0x100)
    {
        ADC->CSTS &= (uint32_t)~(flag & 0xff);
    }
    else
    {
        ADC->CTRL3 &= (uint32_t)~(flag & 0xff);
    }
}

/*!
 * @brief       Checks whether the specified ADC interrupt has occurred or not
 *
 * @param       flag:   Specifies the interrupt flag to check
 *                      The parameter can be one of following values:
 *                      @arg ADC_INT_FLAG_AWD: Analog watch dog interrupt flag
 *                      @arg ADC_INT_FLAG_CC:  Conversion completed interrupt flag
 * @retval      None
 *
 * @note        Status specifies the interrupt flag(SET or RESET)
 */
uint8_t ADC_ReadIntFlag(ADC_INT_FLAG_T flag)
{
    if((ADC->CSTS & flag) == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear interrupt pending bit
 *
 * @param       flag:   Specifies the interrupt flag to clear
 *                      The parameter can be one of following values:
 *                      @arg ADC_INT_FLAG_AWD: Analog watch dog interrupt flag
 *                      @arg ADC_INT_FLAG_CC:  Conversion completed interrupt flag
 *
 * @retval      None
 *
 * @note
 */
void ADC_ClearIntFlag(ADC_INT_FLAG_T flag)
{
    ADC->CSTS &= (uint32_t)~(flag & 0xc0);
}

/*!
 * @brief       Enable compensation
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_EnableCompensation(void)
{
    ADC->CTRL4_B.DISH = BIT_SET;
}

/*!
 * @brief       Disable compensation
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_DisableCompensation(void)
{
    ADC->CTRL4_B.DISH = BIT_RESET;
}

/*!
 * @brief       Read Offset value
 *
 * @param       None
 *
 * @retval      Offset value
 *
 * @note
 */
int8_t ADC_ReadOffset(void)
{
    uint8_t value;

    value = (uint8_t)ADC->OFFSET;

    if(value & 0x20)
    {
        value |= 0xc0;
    }
    else
    {
        value &= 0x1f;
    }

    return (int8_t)value;
}

/*!
 * @brief       Set Offset value
 *
 * @param       value:  Offset value
 *
 * @retval      None
 *
 * @note
 */
void ADC_SetOffset(int8_t value)
{
    ADC->OFFSET = (uint32_t)value & 0x3f;
}

/**@} end of group ADC_Fuctions*/
/**@} end of group ADC_Driver*/
/**@} end of group Peripherals_Library*/

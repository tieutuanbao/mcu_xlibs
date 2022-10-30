/*!
 * @file        apm32f00x_gpio.c
 *
 * @brief       This file contains all the functions for the GPIO peripheral
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

#include "apm32f00x_gpio.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup GPIO_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Set the GPIO peripheral registers to their default reset values
 *
 * @param       port:   Select the GPIO peripheral
 *
 * @retval      None
 *
 * @note
 */
void GPIO_Reset(GPIO_T* port)
{
    port->DOUT = GPIO_DOUT_RESET_VALUE;
    port->DIN = GPIO_DIN_RESET_VALUE;
    port->MODE = GPIO_MODE_RESET_VALUE;
    port->CTRL1 = GPIO_CTRL1_RESET_VALUE;
    port->CTRL2 = GPIO_CTRL2_RESET_VALUE;
}

/*!
 * @brief       Config the GPIO peripheral according to the specified parameters in the gpioConfig
 *
 * @param       port:           GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD
 *
 * @param       gpioConfig:     Pointer to a GPIO_Config_T structure that
 *                              contains the configuration information for the specified GPIO peripheral
 *
 * @retval      None
 *
 * @note
 */
void GPIO_Config(GPIO_T *port, GPIO_Config_T *gpioConfig)
{
    uint8_t i;
    uint32_t bit;
    uint32_t CTRL1;
    uint32_t CTRL2;
    uint32_t MODE;

    CTRL1 = port->CTRL1;
    CTRL2 = port->CTRL2;
    MODE = port->MODE;

    for(i = 0; i < 8; i++)
    {
        bit = (uint32_t)1 << i;
        if(!(gpioConfig->pin & bit))
        {
            continue;
        }

        CTRL1 &= (uint32_t)~bit;
        CTRL2 &= (uint32_t)~bit;
        MODE &= (uint32_t)~bit;

        /** Open-drain/push-pull/Floating/pull-up */
        if(gpioConfig->mode & 0x01)
        {
            CTRL1 |= bit;
        }

        /** input/output mode */
        if(gpioConfig->mode & 0x10)
        {
            MODE |= bit;

            /** speed */
            if(gpioConfig->speed)
            {
                CTRL2 |= bit;
            }
        }
        else
        {
            /** External interrupt */
            if(gpioConfig->intEn)
            {
                CTRL2 |= bit;
            }
        }
    }

    port->CTRL1 = CTRL1;
    port->CTRL2 = CTRL2;
    port->MODE = MODE;
}

/*!
 * @brief       Fills each GPIO_Config_T member with its default value
 *
 * @param       gpioConfig: Pointer to a GPIO_Config_T structure which will be initialized
 *
 * @retval      None
 *
 * @note
 */
void GPIO_ConfigStructInit(GPIO_Config_T *gpioConfig)
{
    gpioConfig->pin = GPIO_PIN_ALL;
    gpioConfig->mode = GPIO_MODE_IN_PU;
    gpioConfig->intEn = GPIO_EINT_DISABLE;
}

/*!
 * @brief       Writes data to the specified GPIO data port
 *
 * @param       port:       GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD
 *
 * @param       portValue:  Specifies the value to be written to the port output data register
 *
 * @retval      None
 *
 * @note
 */
void GPIO_WriteOutputPort(GPIO_T* port, uint8_t portValue)
{
    port->DOUT = (uint32_t)portValue;
}

/*!
 * @brief       Sets the selected data port bits
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD
 *
 * @param       pin:    Specifies the port bits to be written
 *
 * @retval      None
 *
 * @note
 */
void GPIO_SetBit(GPIO_T* port, uint8_t pin)
{
    port->DOUT |= (uint32_t)pin;
}

/*!
 * @brief       Clears the selected data port bits
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD
 *
 * @param       pin:    Specifies the port bits to be written
 *
 * @retval      None
 *
 * @note
 */
void GPIO_ClearBit(GPIO_T* port, uint8_t pin)
{
    port->DOUT &= (uint32_t)~pin;
}

/*!
 * @brief       Reads the specified GPIO output data port
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD
 *
 * @retval      None
 *
 * @note
 */
uint8_t GPIO_ReadOutputPort(GPIO_T* port)
{
    return ((uint8_t)port->DOUT);
}

/*!
 * @brief       Reads the specified GPIO input data port
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD
 *
 * @retval      None
 *
 * @note
 */
uint8_t GPIO_ReadInputPort(GPIO_T* port)
{
  return ((uint16_t)port->DIN);
}


/*!
 * @brief       Reads the specified input port pin
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD
 *
 * @param       pin:    Specifies pin to be read
 *
 * @retval      None
 *
 * @note
 */
uint8_t GPIO_ReadInputBit(GPIO_T* port, uint8_t pin)
{
    uint8_t ret;

    ret = (port->DIN & pin) ?  BIT_SET : BIT_RESET;

    return ret;
}

/*!
 * @brief       Toggles the specified pin
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD
 *
 * @param       pin:    Specifies pin to be toggled
 *
 * @retval      None
 *
 * @note
 */
void GPIO_Toggle(GPIO_T *port, uint8_t pin)
{
    port->DOUT ^= pin;
}

/*!
 * @brief       Enable SWD
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void GPIO_EnableSWD(void)
{
    *(uint8_t *)(GPIOD_BASE + 0x100) = 0x00;
}

/*!
 * @brief       Disable SWD
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void GPIO_DisableSWD(void)
{
    *(uint8_t *)(GPIOD_BASE + 0x100) = 0x01;
}

/**@} end of group GPIO_Fuctions*/
/**@} end of group GPIO_Driver */
/**@} end of group Peripherals_Library*/

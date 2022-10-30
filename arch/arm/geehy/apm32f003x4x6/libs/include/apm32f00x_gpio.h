/*!
 * @file        apm32f00x_gpio.h
 *
 * @brief       This file contains all functions prototype, enumeration and macros for the GPIO peripheral
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
#ifndef __APM32F00x_GPIO_H
#define __APM32F00x_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup GPIO_Enumerations Enumerations
  @{
*/

/**
 * @brief   Configuration Mode enumeration
 */
typedef enum
{
    GPIO_MODE_IN_FLOATING   = ((uint8_t)0x00),      //!<   Floating input
    GPIO_MODE_IN_PU         = ((uint8_t)0x01),      //!<   Input with pull-up
    GPIO_MODE_OUT_OD        = ((uint8_t)0x10),      //!<   General purpose output Open-drain
    GPIO_MODE_OUT_PP        = ((uint8_t)0X11),      //!<   General purpose output push-pull
} GPIO_Mode_T;

/**
 * @brief   GPIO Output Maximum frequency selection
 */
typedef enum
{
    GPIO_SPEED_2MHz         = ((uint8_t)0x00),      //!<   Output speed up to 2 MHz
    GPIO_SPEED_10MHz        = ((uint8_t)0x01)       //!<   Output speed up to 10 MHz
} GPIO_SPEED_T;

/**
 * @brief   Enable/Disable GPIO External interrupt
 */
typedef enum
{
    GPIO_EINT_DISABLE       = ((uint8_t)0x00),      //!<   External interrupt disabled
    GPIO_EINT_ENABLE        = ((uint8_t)0x01)       //!<   External interrupt enabled
} GPIO_EINT_T;

/**
 * @brief    Definition of the GPIO pins
 */
typedef enum
{
    GPIO_PIN_0              = ((uint8_t)BIT0),
    GPIO_PIN_1              = ((uint8_t)BIT1),
    GPIO_PIN_2              = ((uint8_t)BIT2),
    GPIO_PIN_3              = ((uint8_t)BIT3),
    GPIO_PIN_4              = ((uint8_t)BIT4),
    GPIO_PIN_5              = ((uint8_t)BIT5),
    GPIO_PIN_6              = ((uint8_t)BIT6),
    GPIO_PIN_7              = ((uint8_t)BIT7),
    GPIO_PIN_ALL            = ((uint8_t)0XFF)
} GPIO_PIN_T;

/**@} end of group GPIO_Enumerations*/

/** @addtogroup GPIO_Macros Macros
  @{
*/

/** DOUT Register reset value */
#define GPIO_DOUT_RESET_VALUE           ((uint32_t)0X00)
/** DIN Register reset value */
#define GPIO_DIN_RESET_VALUE            ((uint32_t)0X00)
/** MOD Register reset value */
#define GPIO_MODE_RESET_VALUE           ((uint32_t)0X00)
/** CTRL0 Register reset value */
#define GPIO_CTRL1_RESET_VALUE          ((uint32_t)0X00)
/** CTRL1 Register reset value */
#define GPIO_CTRL2_RESET_VALUE          ((uint32_t)0X00)

/**@} end of group GPIO_Macros*/

/** @addtogroup GPIO_Structure Data Structure
  @{
*/

/**
 * @brief   GPIO Config structure definition
 */
typedef struct
{
    GPIO_Mode_T mode;           //!<   operating mode for the selected pins
    GPIO_SPEED_T speed;         //!<   speed for the selected pins
    GPIO_EINT_T intEn;          //!<   Enable/Disable External interrupt
    uint8_t pin;                //!<   Pins to be configured.Can be combination of the values @ref GPIO_PIN_T
} GPIO_Config_T;

/**@} end of group GPIO_Structure*/

/** @addtogroup GPIO_Fuctions Fuctions
  @{
*/

/** Reset and Configuration */
void GPIO_Reset(GPIO_T* port);
void GPIO_Config(GPIO_T *port, GPIO_Config_T *gpioConfig);
void GPIO_ConfigStructInit(GPIO_Config_T *gpioConfig);

/** Write */
void GPIO_WriteOutputPort(GPIO_T* port, uint8_t portValue);
void GPIO_SetBit(GPIO_T* port, uint8_t pin);
void GPIO_ClearBit(GPIO_T* port, uint8_t pin);

/** Read */
uint8_t GPIO_ReadOutputPort(GPIO_T* port);
uint8_t GPIO_ReadInputPort(GPIO_T* port);
uint8_t GPIO_ReadInputBit(GPIO_T* port, uint8_t pin);

/** Toggle */
void GPIO_Toggle(GPIO_T *port, uint8_t pin);

/** Enable/Disable SWD */
void GPIO_EnableSWD(void);
void GPIO_DisableSWD(void);

/**@} end of group GPIO_Fuctions*/
/**@} end of group GPIO_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_GPIO_H */

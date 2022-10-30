/*!
 * @file        apm32f00x.h
 *
 * @brief       CMSIS Cortex-M0+ Device Peripheral Access Layer Header File
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

#ifndef __APM32F0XX_H
#define __APM32F0XX_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup CMSIS_Device Device Definitions for CMSIS
  @{
*/

/** Define Value of the External oscillator in Hz */
#define HXT_VALUE           ((uint32_t)16000000)

/** Define Value of the High speed Internal oscillator in Hz */
#define HIRC_VALUE          ((uint32_t)48000000)

/** Define Value of the Low speed Internal oscillator in Hz */
#define LIRC_VALUE          ((uint32_t)128000)

/** Time out for HXT start up */
#if !defined  (HXT_STARTUP_TIMEOUT)
#define HXT_STARTUP_TIMEOUT        ((uint32_t)0x5000)
#endif


/*!< [31:16] APM32F00X Standard Peripheral Library main version V1.0.3*/
#define __APM32F00X_STDPERIPH_VERSION_MAIN   ((uint8_t)0x01) /*!< [31:24] main version */
#define __APM32F00X_STDPERIPH_VERSION_SUB1   ((uint8_t)0x00) /*!< [23:16] sub1 version */
#define __APM32F00X_STDPERIPH_VERSION_SUB2   ((uint8_t)0x03) /*!< [15:8]  sub2 version */
#define __APM32F00X_STDPERIPH_VERSION_RC     ((uint8_t)0x00) /*!< [7:0]  release candidate */
#define __APM32F00X_STDPERIPH_VERSION       ( (__APM32F00X_STDPERIPH_VERSION_MAIN << 24)\
                                          |(__APM32F00X_STDPERIPH_VERSION_SUB1 << 16)\
                                          |(__APM32F00X_STDPERIPH_VERSION_SUB2 << 8)\
                                          |(__APM32F00X_STDPERIPH_VERSION_RC))

/** Core Revision r0p1  */
#define __CM0_REV                 0
/** APM32F0xx do not provide MPU  */
#define __MPU_PRESENT             0
/** APM32F0xx uses 2 Bits for the Priority Levels */
#define __NVIC_PRIO_BITS          2
/** Set to 1 if different SysTick Config is used */
#define __Vendor_SysTickConfig    0
/** Set to 1 if different Vector Table Offset is used */
#define __VTOR_PRESENT            1

/** @addtogroup Device_IRQ IRQ Number
  @{
*/

/**
 * @brief    Interrupt Number Definition
 */
typedef enum IRQn
{
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                */
    HardFault_IRQn              = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                        */
    SVC_IRQn                    = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                          */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                          */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                      */

    /******  CHAOFENG specific Interrupt Numbers *************************************/

    WUPT_IRQn                   = 1,      /*!< Wakeup timer                                            */
    RCM_IRQn                    = 2,      /*!< Clock controller interrupt                              */
    EINTA_IRQn                  = 3,      /*!< Port A external interrupts                              */
    EINTB_IRQn                  = 4,      /*!< Port B external interrupts                              */
    EINTC_IRQn                  = 5,      /*!< Port C external interrupts                              */
    EINTD_IRQn                  = 6,      /*!< Port D external interrupts                              */
    SPI_IRQn                    = 10,     /*!< SPI Interrupt                                           */
    TMR1_UT_IRQn                = 11,     /*!< TIMER1 update/overflow/underflow/trigger/break interrupt */
    TMR1_CC_IRQn                = 12,     /*!< TIMER1 capture/compare interrupt                         */
    TMR2_UO_IRQn                = 13,     /*!< TIMER2 update /overflow interrupt                        */
    TMR2_CC_IRQn                = 14,     /*!< TIMER2 capture/compare interrupt                         */
    USART1_TX_IRQn              = 17,     /*!< USART1 TX interrupt                                      */
    USART1_RX_IRQn              = 18,     /*!< USART1 RX interrupt                                      */
    IIC_IRQn                    = 19,     /*!< I2C Interrupt                                            */
    ADC_IRQn                    = 22,     /*!< ADC interrupt                                            */
    TMR4_IRQn                   = 23,     /*!< TIMER4 interrupt                                         */
    FLASH_IRQn                  = 24,     /*!< Flash interrupt                                          */
    USART3_TX_IRQn              = 25,     /*!< USART3 TX interrupt                                      */
    USART3_RX_IRQn              = 26,     /*!< USART3 RX interrupt                                      */
    USART2_TX_IRQn              = 27,     /*!< USART2 TX interrupt                                      */
    USART2_RX_IRQn              = 28,     /*!< USART2 RX interrupt                                      */
    TMR1A_UT_IRQn               = 29,     /*!< TIMER1A update/overflow/underflow/trigger/break interrupt*/
    TMR1A_CC_IRQn               = 30,     /*!< TIMER1A capture/compare interrupt                        */
} IRQn_Type;

/**@} end of group Device_IRQ*/


#include "core_cm0plus.h"
#include <stdint.h>


typedef enum {FALSE, TRUE} BOOL;
enum {RESET = 0, SET = !RESET};
enum {BIT_RESET, BIT_SET};
enum {DISABLE = 0, ENABLE = !DISABLE};
enum {ERROR = 0, SUCCESS = !ERROR};

#ifndef __IM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __IM   __I
#endif
#ifndef __OM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __OM   __O
#endif
#ifndef __IOM                                   /*!< Fallback for older CMSIS versions                                         */
  #define __IOM  __IO
#endif

#ifndef NULL
#define NULL    ((void *)0)
#endif

#if defined (__CC_ARM )
#pragma anon_unions
#endif

/** @addtogroup Device_Register Register
  @{
*/

/**
  * @brief  General Purpose I/Os (GPIO)
  */
typedef struct
{
    /** Data output register */
    union
    {
        __IOM uint32_t DOUT;

        struct
        {
            __IOM uint32_t DOUT0            : 1;
            __IOM uint32_t DOUT1            : 1;
            __IOM uint32_t DOUT2            : 1;
            __IOM uint32_t DOUT3            : 1;
            __IOM uint32_t DOUT4            : 1;
            __IOM uint32_t DOUT5            : 1;
            __IOM uint32_t DOUT6            : 1;
            __IOM uint32_t DOUT7            : 1;
            __IM  uint32_t RESERVED         : 24;
        } DOUT_B;
    } ;

    /** Data input register */
    union
    {
        __IOM uint32_t DIN;

        struct
        {
            __IOM uint32_t DIN0             : 1;
            __IOM uint32_t DIN1             : 1;
            __IOM uint32_t DIN2             : 1;
            __IOM uint32_t DIN3             : 1;
            __IOM uint32_t DIN4             : 1;
            __IOM uint32_t DIN5             : 1;
            __IOM uint32_t DIN6             : 1;
            __IOM uint32_t DIN7             : 1;
            __IM  uint32_t RESERVED         : 24;
        } DIN_B;
    } ;

    /** input / ouput mode register */
    union
    {
        __IOM uint32_t MODE;

        struct
        {
            __IOM uint32_t MODE0            : 1;
            __IOM uint32_t MODE1            : 1;
            __IOM uint32_t MODE2            : 1;
            __IOM uint32_t MODE3            : 1;
            __IOM uint32_t MODE4            : 1;
            __IOM uint32_t MODE5            : 1;
            __IOM uint32_t MODE6            : 1;
            __IOM uint32_t MODE7            : 1;
            __IM  uint32_t RESERVED         : 24;
        } MODE_B;
    } ;

    /** Control Register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t CR0              : 1;
            __IOM uint32_t CR1              : 1;
            __IOM uint32_t CR2              : 1;
            __IOM uint32_t CR3              : 1;
            __IOM uint32_t CR4              : 1;
            __IOM uint32_t CR5              : 1;
            __IOM uint32_t CR6              : 1;
            __IOM uint32_t CR7              : 1;
            __IM  uint32_t RESERVED         : 24;
        } CTRL1_B;
    } ;

    /** Control Register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t CR0              : 1;
            __IOM uint32_t CR1              : 1;
            __IOM uint32_t CR2              : 1;
            __IOM uint32_t CR3              : 1;
            __IOM uint32_t CR4              : 1;
            __IOM uint32_t CR5              : 1;
            __IOM uint32_t CR6              : 1;
            __IOM uint32_t CR7              : 1;
            __IM  uint32_t RESERVED         : 24;
        } CTRL2_B;
    } ;
    
    __IM uint32_t RESERVED1;
    __IM uint32_t RESERVED2;
    __IM uint32_t RESERVED3;
    __IM uint32_t RESERVED4;
    __IM uint32_t RESERVED5;
    __IM uint32_t RESERVED6;
    __IM uint32_t RESERVED7;
    __IM uint32_t RESERVED8;
    __IM uint32_t RESERVED9;
    __IM uint32_t RESERVED10;
    __IM uint32_t RESERVED11;
    __IM uint32_t RESERVED12;
    __IM uint32_t RESERVED13;
    __IM uint32_t RESERVED14;
    __IM uint32_t RESERVED15;
    __IM uint32_t RESERVED16;
    __IM uint32_t RESERVED17;
    __IM uint32_t RESERVED18;
    __IM uint32_t RESERVED19;
    __IM uint32_t RESERVED20;
    __IM uint32_t RESERVED21;
    __IM uint32_t RESERVED22;
    __IM uint32_t RESERVED23;
    __IM uint32_t RESERVED24;
    __IM uint32_t RESERVED25;
    __IM uint32_t RESERVED26;
    __IM uint32_t RESERVED27;
    __IM uint32_t RESERVED28;
    __IM uint32_t RESERVED29;
    __IM uint32_t RESERVED30;
    __IM uint32_t RESERVED31;
    __IM uint32_t RESERVED32;
    __IM uint32_t RESERVED33;
    __IM uint32_t RESERVED34;
    __IM uint32_t RESERVED35;
    
    /** GPIO JTAGDIS Register */
    union
    {
        __IOM uint32_t GPIO_JTAGDIS;

        struct
        {
            __IOM uint32_t JTAGDIS          : 1;
            __IM  uint32_t RESERVED         : 31;
        } JTAGDIS_B;
    } ;
} GPIO_T;

/**
  * @brief  Reset and Clock Management (RCM)
  */
typedef struct
{
    /** Internal clock control register */
    union
    {
        __IOM uint32_t ICC;

        struct
        {
            __IOM uint32_t HIRCEN           : 1;
            __IM  uint32_t HIRCRF           : 1;
            __IOM uint32_t FWFHEN           : 1;
            __IOM uint32_t LIRCEN           : 1;
            __IM  uint32_t LIRCRF           : 1;
            __IOM uint32_t RPOEN            : 1;
            __IM  uint32_t RESERVED         : 26;
        } ICC_B;
    } ;

    /** External clock control register */
    union
    {
        __IOM uint32_t ECC;

        struct
        {
            __IOM uint32_t HXTEN            : 1;
            __IM  uint32_t HXTRF            : 1;
            __IM  uint32_t RESERVED         : 30;
        } ECC_B;
    } ;

    __IM uint32_t RESERVED1;

    /** Master Clock status register */
    union
    {
        __IOM uint32_t MCS;

        struct
        {
            __IOM uint32_t MCS              : 8;
            __IM  uint32_t RESERVED         : 24;
        } MCLKSTS_B;
    } ;

    /** Master Clock selection register */
    union
    {
        __IOM uint32_t MCC;

        struct
        {
            __IOM uint32_t MCC              : 8;
            __IM  uint32_t RESERVED         : 24;
        } MCC_B;
    } ;

    /** Master Clock switch control register */
    union
    {
        __IOM uint32_t CSC;

        struct
        {
            __IOM uint32_t CSBF             : 1;
            __IOM uint32_t CSEN             : 1;
            __IOM uint32_t CSIE             : 1;
            __IOM uint32_t CSIF             : 1;
            __IM  uint32_t RESERVED         : 28;
        } CSC_B;
    } ;

    /** Clock divider number register */
    union
    {
        __IOM uint32_t CLKDIV;

        struct
        {
            __IOM uint32_t CPUDIV           : 3;
            __IOM uint32_t HIRCDIV          : 2;
            __IOM uint32_t HDS              : 1;
            __IM  uint32_t RESERVED         : 26;
        } CLKDIV_B;
    } ;

    /** APB peripheral clock enable register1 */
    union
    {
        __IOM uint32_t APBEN1;

        struct
        {
            __IOM uint32_t I2CCEN           : 1;
            __IOM uint32_t SPICEN           : 1;
            __IOM uint32_t RESERVED1        : 1;
            __IOM uint32_t USART1CEN        : 1;
            __IOM uint32_t TMR4CEN          : 1;
            __IOM uint32_t TMR2CEN          : 1;
            __IOM uint32_t RESERVED2        : 1;
            __IOM uint32_t TMR1CEN          : 1;
            __IM  uint32_t RESERVED3        : 24;
        } APBEN1_B;
    } ;

    /** Clock security system register */
    union
    {
        __IOM uint32_t CSS;

        struct
        {
            __IOM uint32_t CSSEN            : 1;
            __IOM uint32_t BCEN             : 1;
            __IOM uint32_t CSSFDIE          : 1;
            __IOM uint32_t CSSFDIF          : 1;
            __IM  uint32_t RESERVED         : 28;
        } CSS_B;
    } ;

    /** clock output control register */
    union
    {
        __IOM uint32_t COC;

        struct
        {
            __IOM uint32_t COEN             : 1;
            __IOM uint32_t COS              : 4;
            __IM  uint32_t CORF             : 1;
            __IM  uint32_t COBF             : 1;
            __IM  uint32_t RESERVED         : 25;
        } COC_B;
    } ;

    /** APB peripheral clock enable register2 */
    union
    {
        __IOM uint32_t APBEN2;

        struct
        {
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t WUPTCEN          : 1;
            __IOM uint32_t ADCCEN           : 1;
            __IM  uint32_t RESERVED2        : 28;
        } APBEN2_B;
    } ;

    __IM  uint32_t RESERVED2;

    /** HIRC clock calibration trimming register */
    union
    {
        __IOM uint32_t HIRCTRIM;

        struct
        {
            __IOM uint32_t TRIM             : 4;
            __IM  uint32_t RESERVED         : 28;
        } HIRCTRIM_B;
    } ;

    __IM  uint32_t RESERVED3;

    /** Reset status register */
    union
    {
        __IOM uint32_t RSTSTS;

        struct
        {
            __IM  uint32_t WWDTRF           : 1;
            __IM  uint32_t IWDTRF           : 1;
            __IM  uint32_t CPURF            : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IM  uint32_t EMCRF            : 1;
            __IM  uint32_t RESERVED2        : 27;
        } RSTSTS_B;
    } ;

    /** APB peripheral clock enable register3 */
    union
    {
        __IOM uint32_t APBEN3;

        struct
        {
            __IOM uint32_t TMR1ACEN         : 1;
            __IOM uint32_t USART2CEN        : 1;
            __IOM uint32_t USART3CEN        : 1;
            __IM  uint32_t RESERVED         : 29;
        } APBEN3_B;
    } ;
} RCM_T;

/**
 * @brief    Universal synchronous asynchronous receiver transmitter (USART)
 */
typedef struct
{
    /** Status register */
    union
    {
        __IOM uint32_t STS;
        struct
        {
            __IM  uint32_t PEF              : 1;
            __IM  uint32_t FEF              : 1;
            __IM  uint32_t NEF              : 1;
            __IM  uint32_t OEF              : 1;
            __IM  uint32_t IDLEF            : 1;
            __IM  uint32_t RXBNEF           : 1;
            __IM  uint32_t TXCF             : 1;
            __IM  uint32_t TXBEF            : 1;
            __IM  uint32_t RESERVED         : 24;
        }STS_B;
    };

    /** DATA register */
    union
    {
        __IOM uint32_t DATA;
        struct
        {
            __IOM uint32_t DATA             : 8;
            __IM  uint32_t RESERVED         : 24;
        }DATA_B;
    };

    /** Baud rate register 1  */
    union
    {
        __IOM uint32_t BR1;
        struct
        {
            __IOM uint32_t DIV11_4          : 8;
            __IM  uint32_t RESERVED         : 24;
        }BR1_B;
    };

    /** Baud rate register 0  */
    union
    {
        __IOM uint32_t BR0;
        struct
        {
            __IOM uint32_t DIV3_0           : 4;
            __IOM uint32_t DIV15_12         : 4;
            __IM  uint32_t RESERVED         : 24;
        }BR0_B;
    };

    /** Control register 1  */
    union
    {
        __IOM uint32_t CTRL1;
        struct
        {
            __IOM uint32_t PIE              : 1;
            __IOM uint32_t PSEL             : 1;
            __IOM uint32_t PEN              : 1;
            __IOM uint32_t WMS              : 1;
            __IOM uint32_t DBL              : 1;
            __IOM uint32_t USARTDIS         : 1;
            __IOM uint32_t TDB8             : 1;
            __IOM uint32_t RDB8             : 1;
            __IM  uint32_t RESERVED         : 24;
        }CTRL1_B;
    };

    /** Control register 2  */
    union
    {
        __IOM uint32_t CTRL2;
        struct
        {
            __IOM uint32_t TXBRK            : 1;
            __IOM uint32_t RMM              : 1;
            __IOM uint32_t RXEN             : 1;
            __IOM uint32_t TXEN             : 1;
            __IOM uint32_t IDLEIE           : 1;
            __IOM uint32_t RXIE             : 1;
            __IOM uint32_t TXCIE            : 1;
            __IOM uint32_t TXIE             : 1;
            __IM  uint32_t RESERVED         : 24;
        }CTRL2_B;
    };

    /** Control register 3 */
    union
    {
        __IOM uint32_t CTRL3;
        struct
        {
            __IOM uint32_t LBCP             : 1;
            __IOM uint32_t CLKPHA           : 1;
            __IOM uint32_t CLKPOL           : 1;
            __IOM uint32_t CLKEN            : 1;
            __IOM uint32_t SBS              : 2;
            __IOM uint32_t LINEN            : 1;
            __IM  uint32_t RESERVED         : 25;
        }CTRL3_B;
    };

    /** Control register 4 */
    union
    {
        __IOM uint32_t CTRL4;
        struct
        {
            __IOM uint32_t ADDR             : 4;
            __IOM uint32_t LMBDF            : 1;
            __IOM uint32_t LMBDL            : 1;
            __IOM uint32_t LMBDIE           : 1;
            __IM  uint32_t RESERVED         : 25;
        }CTRL4_B;
    };

    /** Control register 5 */
    union
    {
        __IOM uint32_t CTRL5;
        struct
        {
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t IRDAEN           : 1;
            __IOM uint32_t ILPM             : 1;
            __IOM uint32_t HDMEN            : 1;
            __IOM uint32_t NACKEN           : 1;
            __IOM uint32_t SMEN             : 1;
            __IM  uint32_t RESERVED2        : 26;
        }CTRL5_B;
    };

    /** Guard time register */
    union
    {
        __IOM uint32_t GTS;
        struct
        {
            __IOM uint32_t GTS              : 8;
            __IM  uint32_t RESERVED         : 24;
        }GTS_B;
    };

    /** Divder number register */
    union
    {
        __IOM uint32_t PSC;
        struct
        {
            __IOM uint32_t PSC                : 8;
            __IM  uint32_t RESERVED         : 24;
        }DIV_B;
    };

    /** USART2/USART3 switch register */
    union
    {
        __IOM uint32_t SW;
        struct
        {
            __IOM uint32_t SW                : 1;
            __IM  uint32_t RESERVED         : 31;
        }SW_B;
    };


    /** USART3 IO switch register */
    union
    {
        __IOM uint32_t IOSW;
        struct
        {
            __IOM uint32_t SW                : 1;
            __IM  uint32_t RESERVED         : 31;
        }IOSW_B;
    };

}USART_T;


/**
 * @brief    Inter-integrated circuit interface (I2C)
 */
typedef struct
{
    /** Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;
        struct
        {
            __IOM uint32_t I2CEN            : 1;
            __IM  uint32_t RESERVED1        : 5;
            __IOM uint32_t BCEN             : 1;
            __IOM uint32_t STRDIS           : 1;
            __IM  uint32_t RESERVED2        : 24;
        }CTRL1_B;
    };

    /** Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;
        struct
        {
            __IOM uint32_t START            : 1;
            __IOM uint32_t STOP             : 1;
            __IOM uint32_t ACKEN            : 1;
            __IOM uint32_t ACKPOS           : 1;
            __IM  uint32_t RESERVED1        : 3;
            __IOM uint32_t SWRST            : 1;
            __IM  uint32_t RESERVED2        : 24;
        }CTRL2_B;
    };

    /** Frequency Control register */
    union
    {
        __IOM uint32_t CLKFREQ;
        struct
        {
            __IOM uint32_t FREQ                : 6;
            __IM  uint32_t RESERVED            : 26;
        }CLKFREQ_B;
    };

    /** Slave address register 0 */
    union
    {
        __IOM uint32_t ADDR0;
        struct
        {
            __IOM uint32_t ADDR                : 8;
            __IM  uint32_t RESERVED            : 24;
        }ADDR0_B;
    };

    /** Slave address register 1 */
    union
    {
        __IOM uint32_t ADDR1;
        struct
        {
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t ADDR             : 2;
            __IM  uint32_t RESERVED2        : 3;
            __IOM uint32_t ADDRCFG          : 1;
            __IOM uint32_t ADDRMODE         : 1;
            __IM  uint32_t RESERVED3        : 24;
        }ADDR1_B;
    };

    __IOM uint32_t RESERVED;

    /** Data register */
    union
    {
        __IOM uint32_t DATA;
        struct
        {
            __IOM uint32_t DATA             : 8;
            __IM  uint32_t RESERVED         : 24;
        }DATA_B;
    };

    /** Status register 1 */
    union
    {
        __IOM uint32_t STS1;
        struct
        {
            __IOM uint32_t SBTCF            : 1;
            __IOM uint32_t ADDRF            : 1;
            __IOM uint32_t BTCF             : 1;
            __IOM uint32_t ADDR10F          : 1;
            __IOM uint32_t SBDF             : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t RXBNEF           : 1;
            __IOM uint32_t TXBEF            : 1;
            __IM  uint32_t RESERVED2        : 24;
        }STS1_B;
    };

    /** Status register 2 */
    union
    {
        __IOM uint32_t STS2;
        struct
        {
            __IOM uint32_t BEF              : 1;
            __IOM uint32_t ALF              : 1;
            __IOM uint32_t AEF              : 1;
            __IOM uint32_t OUF              : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t WFHF             : 1;
            __IM  uint32_t RESERVED2        : 26;
        }STS2_B;
    };

    /** Status register 3 */
    union
    {
        __IOM uint32_t STS3;
        struct
        {
            __IOM uint32_t MMF              : 1;
            __IOM uint32_t BUSYF            : 1;
            __IOM uint32_t RWMF             : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t RBF              : 1;
            __IM  uint32_t RESERVED2        : 27;
        }STS3_B;
    };

    /** Interrupt control register */
    union
    {
        __IOM uint32_t INTCTRL;
        struct
        {
            __IOM uint32_t ERRIE            : 1;
            __IOM uint32_t EVTIE            : 1;
            __IOM uint32_t BUFIE            : 1;
            __IM  uint32_t RESERVED         : 29;
        }INTCTRL_B;
    };

    /** Clock control register 1 */
    union
    {
        __IOM uint32_t CLKCTRL1;
        struct
        {
            __IOM uint32_t CLKCTRL          : 8;
            __IM  uint32_t RESERVED         : 24;
        }CLKCTRL1_B;
    };

    /** Clock control register 2 */
    union
    {
        __IOM uint32_t CLKCTRL2;
        struct
        {
            __IOM uint32_t CLKCTRL          : 4;
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t FMDC             : 1;
            __IOM uint32_t FASTMODE         : 1;
            __IM  uint32_t RESERVED2        : 24;
        }CLKCTRL2_B;
    };

    /** Max Rise time register */
    union
    {
        __IOM uint32_t MRT;
        struct
        {
            __IOM uint32_t MRT              : 6;
            __IM  uint32_t RESERVED         : 26;
        }TRIM_B;
    };
}I2C_T;

/**
 * @brief   Timer1/Timer1A
 */
typedef struct
{
    /** Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;
        struct
        {
            __IOM uint32_t CNTEN            : 1;
            __IOM uint32_t NGUE             : 1;
            __IOM uint32_t UES              : 1;
            __IOM uint32_t SPMEN            : 1;
            __IOM uint32_t CNTDIR           : 1;
            __IOM uint32_t CNTMODE          : 2;
            __IOM uint32_t ARBEN            : 1;
            __IM  uint32_t RESERVED         : 24;
        }CTRL1_B;
    };

    /** Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;
        struct
        {
            __IOM uint32_t CCBEN            : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t CCUS             : 1;
            __IOM uint32_t RESERVED2        : 1;
            __IOM uint32_t MMFC             : 3;
            __IM  uint32_t RESERVED3        : 25;
        }CTRL2_B;
    };

    /** Slave mode congrol register */
    union
    {
        __IOM uint32_t SMC;
        struct
        {
            __IOM uint32_t SMFC             : 3;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t ITC              : 3;
            __IOM uint32_t MSMEN            : 1;
            __IM  uint32_t RESERVED2        : 24;
        }SMC_B;
    };

    /** External trigger control register */
    union
    {
        __IOM uint32_t ETC;
        struct
        {
            __IOM uint32_t ETFC             : 4;
            __IOM uint32_t ETRC             : 2;
            __IOM uint32_t ECM2EN           : 1;
            __IOM uint32_t ETPC             : 1;
            __IM  uint32_t RESERVED         : 24;
        }ETC_B;
    };

    /** interrupt control register */
    union
    {
        __IOM uint32_t INTCTRL;
        struct
        {
            __IOM uint32_t UDIE             : 1;
            __IOM uint32_t CH1CCIE          : 1;
            __IOM uint32_t CH2CCIE          : 1;
            __IOM uint32_t CH3CCIE          : 1;
            __IOM uint32_t CH4CCIE          : 1;
            __IOM uint32_t CCUIE            : 1;
            __IOM uint32_t TRGIE            : 1;
            __IOM uint32_t BRKIE            : 1;
            __IM  uint32_t RESERVED         : 24;
        }INTCTRL_B;
    };

    /** status register 1 */
    union
    {
        __IOM uint32_t STS1;
        struct
        {
            __IOM uint32_t UDIF             : 1;
            __IOM uint32_t CH1CCIF          : 1;
            __IOM uint32_t CH2CCIF          : 1;
            __IOM uint32_t CH3CCIF          : 1;
            __IOM uint32_t CH4CCIF          : 1;
            __IOM uint32_t CCUIF            : 1;
            __IOM uint32_t TRGIF            : 1;
            __IOM uint32_t BRKIF            : 1;
            __IM  uint32_t RESERVED         : 24;
        }STS1_B;
    };

    /** status register 2 */
    union
    {
        __IOM uint32_t STS2;
        struct
        {
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t CH1RCF           : 1;
            __IOM uint32_t CH2RCF           : 1;
            __IOM uint32_t CH3RCF           : 1;
            __IOM uint32_t CH4RCF           : 1;
            __IM  uint32_t RESERVED2        : 27;
        }STS2_B;
    };

    /** Software control event generate register */
    union
    {
        __IOM uint32_t SCEG;
        struct
        {
            __IOM uint32_t UEG              : 1;
            __IOM uint32_t CH1CCG           : 1;
            __IOM uint32_t CH2CCG           : 1;
            __IOM uint32_t CH3CCG           : 1;
            __IOM uint32_t CH4CCG           : 1;
            __IOM uint32_t CCUEG            : 1;
            __IOM uint32_t TEG              : 1;
            __IOM uint32_t BEG              : 1;
            __IM  uint32_t RESERVED2        : 24;
        }SCEG_B;
    };

    /** Channel 1 compare/capture mode register */
    union
    {
        __IOM uint32_t CH1CCM;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t OCFEN            : 1;
            __IOM uint32_t OCBEN            : 1;
            __IOM uint32_t OCMS             : 3;
            __IOM uint32_t OCCEN            : 1;
            __IM  uint32_t RESERVED         : 24;
        }CH1OC_B;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t IC1PSC           : 2;
            __IOM uint32_t ICFC             : 4;
            __IM  uint32_t RESERVED         : 24;
        }CH1IC_B;
    };

    /** Channel 2 compare/capture mode register */
    union
    {
        __IOM uint32_t CH2CCM;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t OCFEN            : 1;
            __IOM uint32_t OCBEN            : 1;
            __IOM uint32_t OCMS             : 3;
            __IOM uint32_t OCCEN            : 1;
            __IM  uint32_t RESERVED         : 24;
        }CH2OC_B;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t IC2PSC           : 2;
            __IOM uint32_t ICFC             : 4;
            __IM  uint32_t RESERVED         : 24;
        }CH2IC_B;
    };

    /** Channel 3 compare/capture mode register */
    union
    {
        __IOM uint32_t CH3CCM;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t OCFEN            : 1;
            __IOM uint32_t OCBEN            : 1;
            __IOM uint32_t OCMS             : 3;
            __IOM uint32_t OCCEN            : 1;
            __IM  uint32_t RESERVED         : 24;
        }CH3OC_B;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t IC3PSC           : 2;
            __IOM uint32_t ICFC             : 4;
            __IM  uint32_t RESERVED         : 24;
        }CH3IC_B;
    };

    /** Channel 4 compare/capture mode register */
    union
    {
        __IOM uint32_t CH4CCM;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t OCFEN            : 1;
            __IOM uint32_t OCBEN            : 1;
            __IOM uint32_t OCMS             : 3;
            __IOM uint32_t OCCEN            : 1;
            __IM  uint32_t RESERVED         : 24;
        }CH4OC_B;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t IC4PSC           : 2;
            __IOM uint32_t ICFC             : 4;
            __IM  uint32_t RESERVED         : 24;
        }CH4IC_B;
    };

    /** Channel control register 1 */
    union
    {
        __IOM uint32_t CHCTRL1;

        struct
        {
            __IOM uint32_t CH1CCEN          : 1;
            __IOM uint32_t CH1CCP           : 1;
            __IOM uint32_t CH1OCNEN         : 1;
            __IOM uint32_t CH1OCNP          : 1;
            __IOM uint32_t CH2CCEN          : 1;
            __IOM uint32_t CH2CCP           : 1;
            __IOM uint32_t CH2OCNEN         : 1;
            __IOM uint32_t CH2OCNP          : 1;
            __IM  uint32_t RESERVED         : 24;
        }CHCTRL1_B;
    };

    /** Channel control register 2 */
    union
    {
        __IOM uint32_t CHCTRL2;

        struct
        {
            __IOM uint32_t CH3CCEN          : 1;
            __IOM uint32_t CH3CCP           : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IM  uint32_t RESERVED2        : 1;
            __IOM uint32_t CH4CCEN          : 1;
            __IOM uint32_t CH4CCP           : 1;
            __IM  uint32_t RESERVED3        : 1;
            __IM  uint32_t RESERVED4        : 1;
            __IM  uint32_t RESERVED5        : 24;
        }CHCTRL2_B;
    };

    /** Count register 1 */
    union
    {
        __IOM uint32_t CNT1;

        struct
        {
            __IOM uint32_t CNT              : 8;
            __IM  uint32_t RESERVED         : 24;
        }CNT1_B;
    };

    /** Count register 0 */
    union
    {
        __IOM uint32_t CNT0;

        struct
        {
            __IOM uint32_t CNT              : 8;
            __IM  uint32_t RESERVED         : 24;
        }CNT0_B;
    };

    /** divider register 1 */
    union
    {
        __IOM uint32_t PSC1;

        struct
        {
            __IOM uint32_t PSC              : 8;
            __IM  uint32_t RESERVED         : 24;
        }DIV1_B;
    };

    /** divider register 0 */
    union
    {
        __IOM uint32_t PSC0;

        struct
        {
            __IOM uint32_t PSC              : 8;
            __IM  uint32_t RESERVED         : 24;
        }DIV0_B;
    };

    /** Auto reload register 1 */
    union
    {
        __IOM uint32_t AUTORLD1;

        struct
        {
            __IOM uint32_t AUTORLD          : 8;
            __IM  uint32_t RESERVED         : 24;
        }AUTORLD1_B;
    };

    /** Auto reload register 0 */
    union
    {
        __IOM uint32_t AUTORLD0;

        struct
        {
            __IOM uint32_t AUTORLD          : 8;
            __IM  uint32_t RESERVED         : 24;
        }AUTORLD0_B;
    };

    /** repetition count register 0 */
    union
    {
        __IOM uint32_t REPCNT;

        struct
        {
            __IOM uint32_t REPCNT           : 8;
            __IM  uint32_t RESERVED         : 24;
        }REPCNT_B;
    };

    /** channel 1 compare/capture register 1 */
    union
    {
        __IOM uint32_t CH1CC1;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH1CC1_B;
    };

    /** channel 1 compare/capture register 0 */
    union
    {
        __IOM uint32_t CH1CC0;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH1CC0_B;
    };

    /** channel 2 compare/capture register 1 */
    union
    {
        __IOM uint32_t CH2CC1;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH2CC1_B;
    };

    /** channel 2 compare/capture register 0 */
    union
    {
        __IOM uint32_t CH2CC0;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH2CC0_B;
    };

    /** channel 3 compare/capture register 1 */
    union
    {
        __IOM uint32_t CH3CC1;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH3CC1_B;
    };

    /** channel 3 compare/capture register 0 */
    union
    {
        __IOM uint32_t CH3CC0;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH3CC0_B;
    };

    /** channel 4 compare/capture register 1 */
    union
    {
        __IOM uint32_t CH4CC1;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH4CC1_B;
    };

    /** channel 4 compare/capture register 0 */
    union
    {
        __IOM uint32_t CH4CC0;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH4CC0_B;
    };

    /** Break control register */
    union
    {
        __IOM uint32_t BRKCTRL;

        struct
        {
            __IOM uint32_t PROTCFG          : 2;
            __IOM uint32_t IMOS             : 1;
            __IOM uint32_t RMOS             : 1;
            __IOM uint32_t BRKEN            : 1;
            __IOM uint32_t BRKPOL           : 1;
            __IOM uint32_t AOEN             : 1;
            __IOM uint32_t WOEN             : 1;
            __IM  uint32_t RESERVED         : 24;
        }BRKCTRL_B;
    };

    /** dead time setup register */
    union
    {
        __IOM uint32_t DTS;

        struct
        {
            __IOM uint32_t DTS              : 8;
            __IM  uint32_t RESERVED         : 24;
        }DTS_B;
    };

    /** idele status output register */
    union
    {
        __IOM uint32_t ISO;

        struct
        {
            __IOM uint32_t CH1ISO           : 1;
            __IOM uint32_t CH1NISO          : 1;
            __IOM uint32_t CH2ISO           : 1;
            __IOM uint32_t CH2NISO          : 1;
            __IOM uint32_t CH3ISO           : 1;
            __IOM uint32_t RESERVED1        : 1;
            __IOM uint32_t CH4ISO           : 1;
            __IM  uint32_t RESERVED         : 25;
        }ISO_B;
    };

    __IOM uint32_t RESERVED;

    /** Timer1A Channel enable register */
    union
    {
        __IOM uint32_t CHEN;

        struct
        {
            __IOM uint32_t CH1              : 1;
            __IOM uint32_t CH2              : 1;
            __IOM uint32_t CH3              : 1;
            __IOM uint32_t CH4              : 1;
            __IM  uint32_t RESERVED         : 28;
        }CHEN_B;
    };
}TMR1_T;

/**
 * @brief   Timer2
 */
typedef struct
{
    /** Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;
        struct
        {
            __IOM uint32_t CNTEN            : 1;
            __IOM uint32_t NGUE             : 1;
            __IOM uint32_t UES              : 1;
            __IOM uint32_t SPMEN            : 1;
            __IM  uint32_t RESERVED1        : 3;
            __IOM uint32_t ARBEN            : 1;
            __IM  uint32_t RESERVED2        : 24;
        }CTRL1_B;
    };

    /** Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;
        struct
        {
            __IM  uint32_t RESERVED1        : 4;
            __IOM uint32_t MMFC             : 3;
            __IM  uint32_t RESERVED2        : 25;
        }CTRL2_B;
    };

    /** Slave mode congrol register */
    union
    {
        __IOM uint32_t SMC;
        struct
        {
            __IOM uint32_t SMFC             : 3;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t ITC              : 3;
            __IOM uint32_t MSMEN            : 1;
            __IM  uint32_t RESERVED2        : 24;
        }SMC_B;
    };

    /** interrupt control register */
    union
    {
        __IOM uint32_t INTCTRL;
        struct
        {
            __IOM uint32_t UDIE             : 1;
            __IOM uint32_t CH1CCIE          : 1;
            __IOM uint32_t CH2CCIE          : 1;
            __IOM uint32_t CH3CCIE          : 1;
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t TRGIE            : 1;
            __IM  uint32_t RESERVED2        : 25;
        }INTCTRL_B;
    };

    /** status register 1 */
    union
    {
        __IOM uint32_t STS1;
        struct
        {
            __IOM uint32_t UDIF             : 1;
            __IOM uint32_t CH1CCIF          : 1;
            __IOM uint32_t CH2CCIF          : 1;
            __IOM uint32_t CH3CCIF          : 1;
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t TRGIF            : 1;
            __IM  uint32_t RESERVED2        : 25;
        }STS1_B;
    };

    /** status register 2 */
    union
    {
        __IOM uint32_t STS2;
        struct
        {
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t CH1RCF           : 1;
            __IOM uint32_t CH2RCF           : 1;
            __IOM uint32_t CH3RCF           : 1;
            __IM  uint32_t RESERVED2        : 28;
        }STS2_B;
    };

    /** Software control event generate register */
    union
    {
        __IOM uint32_t SCEG;
        struct
        {
            __IOM uint32_t UEG              : 1;
            __IOM uint32_t CH1CCG           : 1;
            __IOM uint32_t CH2CCG           : 1;
            __IOM uint32_t CH3CCG           : 1;
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t TEG              : 1;
            __IM  uint32_t RESERVED2        : 25;
        }SCEG_B;
    };

    /** Channel 1 compare/capture mode register */
    union
    {
        __IOM uint32_t CH1CCM;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t OCBEN            : 1;
            __IOM uint32_t OCMS             : 3;
            __IM  uint32_t RESERVED2        : 25;
        }CH1OC_B;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t IC1PSC           : 2;
            __IOM uint32_t ICFC             : 4;
            __IM  uint32_t RESERVED         : 24;
        }CH1IC_B;
    };

    /** Channel 2 compare/capture mode register */
    union
    {
        __IOM uint32_t CH2CCM;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t OCBEN            : 1;
            __IOM uint32_t OCMS             : 3;
            __IM  uint32_t RESERVED2        : 25;
        }CH2OC_B;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t IC2PSC           : 2;
            __IOM uint32_t ICFC             : 4;
            __IM  uint32_t RESERVED         : 24;
        }CH2IC_B;
    };

    /** Channel 3 compare/capture mode register */
    union
    {
        __IOM uint32_t CH3CCM;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t OCBEN            : 1;
            __IOM uint32_t OCMS             : 3;
            __IM  uint32_t RESERVED2        : 25;
        }CH3OC_B;

        struct
        {
            __IOM uint32_t MODESEL          : 2;
            __IOM uint32_t IC3PSC           : 2;
            __IOM uint32_t ICFC             : 4;
            __IM  uint32_t RESERVED         : 24;
        }CH3IC_B;
    };

    /** Channel control register 1 */
    union
    {
        __IOM uint32_t CHCTRL1;

        struct
        {
            __IOM uint32_t CH1CCEN          : 1;
            __IOM uint32_t CH1CCP           : 1;
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t CH2CCEN          : 1;
            __IOM uint32_t CH2CCP           : 1;
            __IM  uint32_t RESERVED2        : 2;
            __IM  uint32_t RESERVED3        : 24;
        }CHCTRL1_B;
    };

    /** Channel control register 2 */
    union
    {
        __IOM uint32_t CHCTRL2;

        struct
        {
            __IOM uint32_t CH3CCEN          : 1;
            __IOM uint32_t CH3CCP           : 1;
            __IM  uint32_t RESERVED         : 30;

        }CHCTRL2_B;
    };

    /** Count register 1 */
    union
    {
        __IOM uint32_t CNT1;

        struct
        {
            __IOM uint32_t CNT              : 8;
            __IM  uint32_t RESERVED         : 24;
        }CNT1_B;
    };

    /** Count register 0 */
    union
    {
        __IOM uint32_t CNT0;

        struct
        {
            __IOM uint32_t CNT              : 8;
            __IM  uint32_t RESERVED         : 24;
        }CNT0_B;
    };

    /** divider register */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint32_t PSC              : 8;
            __IM  uint32_t RESERVED         : 24;
        }DIV_B;
    };


    /** Auto reload register 1 */
    union
    {
        __IOM uint32_t AUTORLD1;

        struct
        {
            __IOM uint32_t AUTORLD          : 8;
            __IM  uint32_t RESERVED         : 24;
        }AUTORLD1_B;
    };

    /** Auto reload register 0 */
    union
    {
        __IOM uint32_t AUTORLD0;

        struct
        {
            __IOM uint32_t AUTORLD          : 8;
            __IM  uint32_t RESERVED         : 24;
        }AUTORLD0_B;
    };

    /** channel 1 compare/capture register 1 */
    union
    {
        __IOM uint32_t CH1CC1;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH1CC1_B;
    };

    /** channel 1 compare/capture register 0 */
    union
    {
        __IOM uint32_t CH1CC0;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH1CC0_B;
    };

    /** channel 2 compare/capture register 1 */
    union
    {
        __IOM uint32_t CH2CC1;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH2CC1_B;
    };

    /** channel 2 compare/capture register 0 */
    union
    {
        __IOM uint32_t CH2CC0;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH2CC0_B;
    };

    /** channel 3 compare/capture register 1 */
    union
    {
        __IOM uint32_t CH3CC1;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH3CC1_B;
    };

    /** channel 3 compare/capture register 0 */
    union
    {
        __IOM uint32_t CH3CC0;

        struct
        {
            __IOM uint32_t CC               : 8;
            __IM  uint32_t RESERVED         : 24;
        }CH3CC0_B;
    };
}TMR2_T;

/**
 * @brief   Timer4
 */
typedef struct
{
    /** Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;
        struct
        {
            __IOM uint32_t CNTEN            : 1;
            __IOM uint32_t NGUE             : 1;
            __IOM uint32_t UES              : 1;
            __IOM uint32_t SPMEN            : 1;
            __IM  uint32_t RESERVED1        : 3;
            __IOM uint32_t ARBEN            : 1;
            __IM  uint32_t RESERVED2        : 24;
        }CTRL1_B;
    };

    /** Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;
        struct
        {
            __IM  uint32_t RESERVED1        : 4;
            __IOM uint32_t MMFC             : 3;
            __IM  uint32_t RESERVED2        : 25;
        }CTRL2_B;
    };

    /** Slave mode congrol register */
    union
    {
        __IOM uint32_t SMC;
        struct
        {
            __IOM uint32_t SMFC             : 3;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t ITC              : 3;
            __IOM uint32_t MSMEN            : 1;
            __IM  uint32_t RESERVED2        : 24;
        }SMC_B;
    };

    /** interrupt control register */
    union
    {
        __IOM uint32_t INTCTRL;
        struct
        {
            __IOM uint32_t UDIE             : 1;
            __IM  uint32_t RESERVED1        : 5;
            __IOM uint32_t TRGIE            : 1;
            __IM  uint32_t RESERVED2        : 25;
        }INTCTRL_B;
    };

    /** status register */
    union
    {
        __IOM uint32_t STS;
        struct
        {
            __IOM uint32_t UDIF             : 1;
            __IM  uint32_t RESERVED1        : 5;
            __IOM uint32_t TRGIF            : 1;
            __IM  uint32_t RESERVED2        : 25;
        }STS1_B;
    };

    /** Software control event generate register */
    union
    {
        __IOM uint32_t SCEG;
        struct
        {
            __IOM uint32_t UEG              : 1;
            __IM  uint32_t RESERVED1        : 5;
            __IOM uint32_t TEG              : 1;
            __IM  uint32_t RESERVED2        : 25;
        }SCEG_B;
    };

    /** Count register */
    union
    {
        __IOM uint32_t CNT;

        struct
        {
            __IOM uint32_t CNT              : 8;
            __IM  uint32_t RESERVED         : 24;
        }CNT_B;
    };

    /** divider register */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint32_t PSC              : 3;
            __IM  uint32_t RESERVED         : 29;
        }DIV_B;
    };


    /** Auto reload register */
    union
    {
        __IOM uint32_t AUTORLD;

        struct
        {
            __IOM uint32_t AUTORLD          : 8;
            __IM  uint32_t RESERVED         : 24;
        }AUTORLD_B;
    };
}TMR4_T;

/**
 * @brief   SPI
 */
typedef struct
{
    /** Control  register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t CLKPHA           : 1;
            __IOM uint32_t CLKPOL           : 1;
            __IOM uint32_t MSTMODE          : 1;
            __IOM uint32_t BRC              : 3;
            __IOM uint32_t SPIEN            : 1;
            __IOM uint32_t LSBF             : 1;
            __IM  uint32_t RESERVED         : 24;
        }CTRL1_B;
    };

    /** Control  register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t ISS              : 1;
            __IOM uint32_t SSC              : 1;
            __IOM uint32_t UMRXO            : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t CRCNXT           : 1;
            __IOM uint32_t CRCEN            : 1;
            __IOM uint32_t BMTX             : 1;
            __IOM uint32_t BMEN             : 1;
            __IM  uint32_t RESERVED2        : 24;
        }CTRL2_B;
    };

    /** Interrupt control  register */
    union
    {
        __IOM uint32_t INTCTRL;

        struct
        {
            __IM  uint32_t RESERVED1        : 4;
            __IOM uint32_t WUPIE            : 1;
            __IOM uint32_t ERRIE            : 1;
            __IOM uint32_t RXBNEIE          : 1;
            __IOM uint32_t TXBEIE           : 1;
            __IM  uint32_t RESERVED2        : 24;
        }INTCTRL_B;
    };

    /** Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t RXBNEF           : 1;
            __IOM uint32_t TXBEF            : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t WUPF             : 1;
            __IOM uint32_t CRCEF            : 1;
            __IOM uint32_t MMEF             : 1;
            __IOM uint32_t RXOF             : 1;
            __IOM uint32_t BUSYF            : 1;
            __IM  uint32_t RESERVED2        : 24;
        }STS_B;
    };

    /** Data register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA             : 8;
            __IM  uint32_t RESERVED2        : 24;
        }DATA_B;
    };

    /** CRC polynomial register */
    union
    {
        __IOM uint32_t CRCPOLY;

        struct
        {
            __IOM uint32_t CRCPOLY          : 8;
            __IM  uint32_t RESERVED2        : 24;
        }CRCPOLY_B;
    };

    /** Rx CRC register */
    union
    {
        __IOM uint32_t RXCRC;

        struct
        {
            __IOM uint32_t RXCRC            : 8;
            __IM  uint32_t RESERVED2        : 24;
        }RXCRC_B;
    };

    /** Tx CRC register */
    union
    {
        __IOM uint32_t TXCRC;

        struct
        {
            __IOM uint32_t TXCRC            : 8;
            __IM  uint32_t RESERVED2        : 24;
        }TXCRC_B;
    };
}SPI_T;

/**
 * @brief   ADC
 */
typedef struct
{
    /** Data buffer */
    __IOM uint32_t DATABUF[20];

    __IM uint32_t RESERVED[12];

    /** Control  status register 1 */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IOM uint32_t CHSEL            : 4;
            __IOM uint32_t AWDIE            : 1;
            __IOM uint32_t CCIE             : 1;
            __IOM uint32_t AWDF             : 1;
            __IOM uint32_t CCF              : 1;
            __IM  uint32_t RESERVED2        : 24;
        }CSTS_B;
    };

    /** Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t ADCON            : 1;
            __IOM uint32_t CCM              : 1;
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t DIVSEL           : 3;
            __IM  uint32_t RESERVED2        : 25;
        }CTRL1_B;
    };

    /** Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t SMEN             : 1;
            __IM  uint32_t RESERVED2        : 1;
            __IOM uint32_t DAM              : 1;
            __IOM uint32_t ETS              : 2;
            __IOM uint32_t ETEN             : 1;
            __IM  uint32_t RESERVED3        : 25;
        }CTRL2_B;
    };

    /** Control register 3 */
    union
    {
        __IOM uint32_t CTRL3;

        struct
        {
            __IM  uint32_t RESERVED1        : 6;
            __IOM uint32_t OVRF             : 1;
            __IOM uint32_t DBEN             : 1;
            __IM  uint32_t RESERVED2        : 24;
        }CTRL3_B;
    };

    /** DATA register 1 */
    union
    {
        __IOM uint32_t DATA1;

        struct
        {
            __IOM uint32_t DATA             : 8;
            __IM  uint32_t RESERVED         : 24;
        }DATA1_B;
    };

    /** DATA register 0 */
    union
    {
        __IOM uint32_t DATA0;

        struct
        {
            __IOM uint32_t DATA             : 8;
            __IM  uint32_t RESERVED         : 24;
        }DATA0_B;
    };

    /** Schmitt trigger disable register 1 */
    union
    {
        __IOM uint32_t STD1;

        struct
        {
            __IOM uint32_t STD              : 8;
            __IM  uint32_t RESERVED         : 24;
        }STD1_B;
    };

    /** Schmitt trigger disable register 0 */
    union
    {
        __IOM uint32_t STD0;

        struct
        {
            __IOM uint32_t STD              : 8;
            __IM  uint32_t RESERVED         : 24;
        }STD0_B;
    };

    /** Analog Watch Dog high threshold register 1 */
    union
    {
        __IOM uint32_t AWDHT1;

        struct
        {
            __IOM uint32_t THRESHOLD        : 8;
            __IM  uint32_t RESERVED         : 24;
        }AWDHT1_B;
    };

    /** Analog Watch Dog high threshold register 0 */
    union
    {
        __IOM uint32_t AWDHT0;

        struct
        {
            __IOM uint32_t THRESHOLD        : 4;
            __IM  uint32_t RESERVED         : 28;
        }AWDHT0_B;
    };

    /** Analog Watch Dog low threshold register 1 */
    union
    {
        __IOM uint32_t AWDLT1;

        struct
        {
            __IOM uint32_t THRESHOLD        : 8;
            __IM  uint32_t RESERVED         : 24;
        }AWDLT1_B;
    };

    /** Analog Watch Dog low threshold register 0 */
    union
    {
        __IOM uint32_t AWDLT0;

        struct
        {
            __IOM uint32_t THRESHOLD        : 4;
            __IM  uint32_t RESERVED         : 28;
        }AWDLT0_B;
    };

    /** Analog Watch Dog status register 1 */
    union
    {
        __IOM uint32_t AWDS1;

        struct
        {
            __IOM uint32_t AWDS             : 8;
            __IM  uint32_t RESERVED         : 24;
        }AWDS1_B;
    };

    /** Analog Watch Dog status register 0 */
    union
    {
        __IOM uint32_t AWDS0;

        struct
        {
            __IOM uint32_t AWDS             : 8;
            __IM  uint32_t RESERVED         : 24;
        }AWDS0_B;
    };

    /** Analog Watch Dog enable register 1 */
    union
    {
        __IOM uint32_t AWDEN1;

        struct
        {
            __IOM uint32_t AWDEN             : 8;
            __IM  uint32_t RESERVED         : 24;
        }AWDEN1_B;
    };

    /** Analog Watch Dog enable register 0 */
    union
    {
        __IOM uint32_t AWDEN0;

        struct
        {
            __IOM uint32_t AWDEN             : 8;
            __IM  uint32_t RESERVED         : 24;
        }AWDEN0_B;
    };

    /** Control register 4 */
    union
    {
        __IOM uint32_t CTRL4;

        struct
        {
            __IOM  uint32_t DISH            : 1;
            __IOM  uint32_t GCMP            : 1;
            __IOM  uint32_t DFS             : 1;
            __IM  uint32_t RESERVED         : 29;
        }CTRL4_B;
    };

    /** Offset register */
    union
    {
        __IOM uint32_t OFFSET;

        struct
        {
            __IOM uint32_t OFFSET           : 8;
            __IM  uint32_t RESERVED         : 24;
        }OFFSET_B;
    };
}ADC_T;

/**
 * @brief   External interrupt
 */
typedef struct
{
    /** Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t PAIT             : 2;
            __IOM uint32_t PBIT             : 2;
            __IOM uint32_t PCIT             : 2;
            __IOM uint32_t PDIT             : 2;
            __IM  uint32_t RESERVED         : 24;
        }CTRL1_B;
    };

    /** Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t NMIT             : 1;
            __IM  uint32_t RESERVED2        : 29;
        }CTRL2_B;
    };

    /** Clear register */
    union
    {
        __IOM uint32_t CLR;

        struct
        {
            __IOM uint32_t PAIC             : 1;
            __IOM uint32_t PBIC             : 1;
            __IOM uint32_t PCIC             : 1;
            __IOM uint32_t PDIC             : 1;
            __IM  uint32_t RESERVED1        : 2;
            __IOM uint32_t NMIC             : 1;
            __IM  uint32_t RESERVED2        : 25;
        }CLR_B;
    };
}EINT_T;

/**
 * @brief   Independent watch dog
 */
typedef struct
{
    /** Keyword register */
    union
    {
        __IOM uint32_t KEYWORD;

        struct
        {
            __IOM uint8_t KEY               : 8;
            __IM  uint32_t RESERVED         : 24;
        }KEYWORD_B;
    };

    /** divider register */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint8_t  PSC              : 3;
            __IM  uint32_t RESERVED         : 29;
        }DIV_B;
    };

    /** Counter reload register */
    union
    {
        __IOM uint32_t CNTRLD;

        struct
        {
            __IOM uint8_t CNTRLD            : 8;
            __IM  uint32_t RESERVED         : 24;
        }CNTRLD_B;
    };
}IWDT_T;

/**
 * @brief   Windows watch dog
 */
typedef struct
{

    /** Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t CNT              : 7;
            __IOM uint32_t WWDTEN           : 1;
            __IM  uint32_t RESERVED         : 24;
        }CTRL_B;
    };

    /** Control data register */
    union
    {
        __IOM uint32_t WDDATA;

        struct
        {
            __IOM uint32_t WINCNT           : 7;
            __IOM uint32_t WWDTEN           : 1;
            __IM  uint32_t RESERVED         : 24;
        }WDDATA_B;
    };
}WWDT_T;

/**
 * @brief   BUZZER
 */
typedef struct
{
    /** Control status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IOM uint32_t DIV              : 5;
            __IOM uint32_t BUZEN            : 1;
            __IOM uint32_t BOFS             : 2;
            __IM  uint32_t RESERVED         : 24;
        }CSTS_B;
    };
}BUZZER_T;

/**
 * @brief   Wakeup timer
 */
typedef struct
{
    /** Control status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IOM uint32_t CFMEN            : 1;
            __IM  uint32_t RESERVED1        : 3;
            __IOM uint32_t WUPTEN           : 1;
            __IOM uint32_t WUPIF            : 1;
            __IM  uint32_t RESERVED2        : 26;
        }CSTS_B;
    };

    /** Divider register */
    union
    {
        __IOM uint32_t DIV;

        struct
        {
            __IOM uint32_t DIV              : 6;
            __IM  uint32_t RESERVED         : 26;
        }DIV_B;
    };

    /** Control status register */
    union
    {
        __IOM uint32_t TBC;

        struct
        {
            __IOM uint32_t TBC              : 4;
            __IM  uint32_t RESERVED         : 28;
        }TBC_B;
    };
}WUPT_T;

/**
  * @brief Flash memory controller (FMC)
  */
typedef struct
{
    /** Flash memory control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t LATENCY          : 3;
            __IOM uint32_t HCAEN            : 1;
            __IOM uint32_t PBEN             : 1;
            __IM  uint32_t PBSF             : 1;
            __IM  uint32_t RESERVED         : 26;
        } CTRL1_B;
    };

    /** key register */
    union
    {
        __OM  uint32_t KEY;

        struct
        {
            __OM  uint32_t KEY              : 32;
        } KEY_B;
    } ;

    /** option byte key register */
    union
    {
        __OM  uint32_t OBKEY;

        struct
        {
            __OM  uint32_t KEY              : 32;
        } OBKEY_B;
    } ;

    /** status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t BUSYF            : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t PEF              : 1;
            __IM  uint32_t RESERVED2        : 1;
            __IOM uint32_t WPEF             : 1;
            __IOM uint32_t OCF              : 1;
            __IM  uint32_t RESERVED3        : 26;
        } STS_B;
    } ;

    /** control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t PG               : 1;
            __IOM uint32_t PAGEERA          : 1;
            __IOM uint32_t MASSERA          : 1;
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t OBP              : 1;
            __IOM uint32_t OBE              : 1;
            __IOM uint32_t STA              : 1;
            __IOM uint32_t LOCK             : 1;
            __IM  uint32_t RESERVED2        : 1;
            __IOM uint32_t OBWEN            : 1;
            __IOM uint32_t ERRIE            : 1;
            __IM  uint32_t RESERVED3        : 1;
            __IOM uint32_t OCIE             : 1;
            __IM  uint32_t RESERVED4        : 19;
        } CTRL2_B;
    } ;

    /** address register */
    union
    {
        __IOM uint32_t ADDR;

        struct
        {
            __IOM uint32_t ADDR             : 32;
        } ADDR_B;
    } ;

    __IM  uint32_t  RESERVED;

    /** Option byte control/status register */
    union
    {
        __IOM uint32_t OBCS;

        struct
        {
            __IM  uint32_t OBE              : 1;
            __IOM uint32_t READPROT         : 1;
            __IM  uint32_t WWDTSW           : 1;
            __IM  uint32_t WWDTRST          : 1;
            __IM  uint32_t IWDTSW           : 1;
            __IM  uint32_t LIRCEN           : 1;
            __IM  uint32_t HIRCTRIM         : 1;
            __IM  uint32_t RESERVED1        : 3;
            __IM  uint32_t DATA0            : 8;
            __IM  uint32_t DATA1            : 8;
            __IM  uint32_t RESERVED2        : 6;
        } OBCS_B;
    } ;

    /** Write protection register */
    union
    {
        __IM uint32_t WRTPROT;

        struct
        {
            __IM uint32_t WRTPROT           : 32;
        } WRTPROT_B;
    } ;

    /** Low power mode register */
    union
    {
        __IOM uint32_t LPM;

        struct
        {
            __IOM uint32_t HALT             : 1;
            __IOM uint32_t AHALT            : 1;
            __IM  uint32_t RESERVED         : 30;
        } LPM_B;
    } ;

    /** tpower on register */
    union
    {
        __IOM uint32_t TPO;

        struct
        {
            __IOM uint32_t TPO             : 8;
            __IM  uint32_t RESERVED         : 24;
        } TPO_B;
    } ;
} FMC_T;

/**
  * @brief Option Bytes Registers
  */
typedef struct
{
    __IOM uint16_t READPROT;

    union
    {
        __IOM uint16_t USER;

        struct
        {
            __IOM uint16_t WWDTSW           : 1;
            __IOM uint16_t WWDTRST          : 1;
            __IOM uint16_t IWDTSW           : 1;
            __IOM uint16_t LIRCEN           : 1;
            __IOM uint16_t HIRCTRIM         : 1;
            __IOM uint16_t RESERVED         : 3;
            __IOM uint16_t nUSER            : 8;
        } USER_B;
    } ;

    __IOM uint16_t DATA0;
    __IOM uint16_t DATA1;
    __IOM uint16_t WRTPROT0;
    __IOM uint16_t WRTPROT1;
    __IOM uint16_t WRTPROT2;
    __IOM uint16_t WRTPROT3;
    __IOM uint16_t AFR;
    uint16_t RESERVED;
    __IOM uint16_t HXTCNT;

    union
    {
         __IOM uint16_t CLKOPT;

        struct
        {
            __IOM uint16_t WUPTDIV              : 2;
            __IOM uint16_t WUPTCS               : 1;
            __IOM uint16_t EXTCLK               : 1;
            __IOM uint16_t RESERVED             : 4;
            __IOM uint16_t nCLKOPT              : 8;
        } CLKOPT_B;
    } ;
} OB_T;

/**@} end of group Device_Register*/

/** FMC base address in the alias region */
#define FMC_BASE            ((uint32_t)0x00000000)
/** SRAM base address in the alias region */
#define SRAM_BASE           ((uint32_t)0x20000000)
/** Peripheral base address in the alias region */
#define PERIPH_BASE         ((uint32_t)0x40000000)

/*!< Peripheral memory map */
#define APBPERIPH_BASE      PERIPH_BASE
#define AHBPERIPH_BASE      (PERIPH_BASE + 0x00010000)

#define GPIOA_BASE          (APBPERIPH_BASE + 0x00000000)
#define GPIOB_BASE          (APBPERIPH_BASE + 0x00000400)
#define GPIOC_BASE          (APBPERIPH_BASE + 0x00000800)
#define GPIOD_BASE          (APBPERIPH_BASE + 0x00000C00)
#define TMR1A_BASE          (APBPERIPH_BASE + 0x00001000)
#define USART2_BASE         (APBPERIPH_BASE + 0x00001400)
#define EINT_BASE           (APBPERIPH_BASE + 0x00001800)
#define WWDT_BASE           (APBPERIPH_BASE + 0x00001C00)
#define IWDT_BASE           (APBPERIPH_BASE + 0x00002000)
#define WAKEUP_BASE         (APBPERIPH_BASE + 0x00002400)
#define BUZZER_BASE         (APBPERIPH_BASE + 0x00002800)
#define SPI_BASE            (APBPERIPH_BASE + 0x00002C00)
#define I2C_BASE            (APBPERIPH_BASE + 0x00003000)
#define USART1_BASE         (APBPERIPH_BASE + 0x00003400)
#define TMR1_BASE           (APBPERIPH_BASE + 0x00003800)
#define TMR2_BASE           (APBPERIPH_BASE + 0x00003C00)
#define TMR4_BASE           (APBPERIPH_BASE + 0x00004000)
#define ADC_BASE            (APBPERIPH_BASE + 0x00004400)
#define USART3_BASE         (APBPERIPH_BASE + 0x00004800)

#define RCM_BASE            (AHBPERIPH_BASE + 0x00000000)
#define FMC_R_BASE          (AHBPERIPH_BASE + 0x00001000)
#define OB_BASE             (0x00020400)


#define GPIOA               ((GPIO_T *) GPIOA_BASE)
#define GPIOB               ((GPIO_T *) GPIOB_BASE)
#define GPIOC               ((GPIO_T *) GPIOC_BASE)
#define GPIOD               ((GPIO_T *) GPIOD_BASE)

#define EINT                ((EINT_T *) EINT_BASE)
#define WWDT                ((WWDT_T *) WWDT_BASE)
#define IWDT                ((IWDT_T *) IWDT_BASE)
#define WUPT                ((WUPT_T *) WAKEUP_BASE)
#define BUZZER              ((BUZZER_T *) BUZZER_BASE)
#define SPI                 ((SPI_T *) SPI_BASE)
#define I2C                 ((I2C_T *) I2C_BASE)
#define USART1              ((USART_T *) USART1_BASE)
#define USART2              ((USART_T *) USART2_BASE)
#define USART3              ((USART_T *) USART3_BASE)
#define TMR1                ((TMR1_T *) TMR1_BASE)
#define TMR1A               ((TMR1_T *) TMR1A_BASE)
#define TMR2                ((TMR2_T *) TMR2_BASE)
#define TMR4                ((TMR4_T *) TMR4_BASE)
#define ADC                 ((ADC_T *) ADC_BASE)
#define RCM                 ((RCM_T *) RCM_BASE)

#define FMC                 ((FMC_T *) FMC_R_BASE)
#define OB                  ((OB_T *) OB_BASE)


/* Define one bit mask */
#define BIT0                0x00000001
#define BIT1                0x00000002
#define BIT2                0x00000004
#define BIT3                0x00000008
#define BIT4                0x00000010
#define BIT5                0x00000020
#define BIT6                0x00000040
#define BIT7                0x00000080
#define BIT8                0x00000100
#define BIT9                0x00000200
#define BIT10               0x00000400
#define BIT11               0x00000800
#define BIT12               0x00001000
#define BIT13               0x00002000
#define BIT14               0x00004000
#define BIT15               0x00008000
#define BIT16               0x00010000
#define BIT17               0x00020000
#define BIT18               0x00040000
#define BIT19               0x00080000
#define BIT20               0x00100000
#define BIT21               0x00200000
#define BIT22               0x00400000
#define BIT23               0x00800000
#define BIT24               0x01000000
#define BIT25               0x02000000
#define BIT26               0x04000000
#define BIT27               0x08000000
#define BIT28               0x10000000
#define BIT29               0x20000000
#define BIT30               0x40000000
#define BIT31               0x80000000

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**@} end of group CMSIS_Device*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_H */

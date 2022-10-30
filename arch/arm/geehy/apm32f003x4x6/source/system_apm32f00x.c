/*!
 * @file        system_apm32f00x.c
 *
 * @brief       CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File
 *
 * @version     V1.0.1
 *
 * @date        2021-04-11
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

#include "apm32f00x.h"

//#define MASTER_CLOCK_HXT    HXT_VALUE
//#define MASTER_CLOCK_LIRC   (128000)
//#define MASTER_CLOCK_6MHz   (6000000)
//#define MASTER_CLOCK_12MHz  (12000000)
//#define MASTER_CLOCK_24MHz  (24000000)
#define MASTER_CLOCK_48MHz  (48000000)

static void ConfigMasterClock(void);
#ifdef MASTER_CLOCK_HXT
static void MasterClockHXT(void);
#elif defined MASTER_CLOCK_6MHz
static void MasterClock6M(void);
#elif defined MASTER_CLOCK_12MHz
static void MasterClock12M(void);
#elif defined MASTER_CLOCK_24MHz
static void MasterClock24M(void);
#elif defined MASTER_CLOCK_48MHz
static void MasterClock48M(void);
#elif defined MASTER_CLOCK_LIRC
static void MasterClockLIRC(void);
#endif

/** #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET     0x00

/*!
 * @brief       Setup the microcontroller system.Initialize the Embedded Flash Interface and system clock
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function should be used only after reset
 */
void SystemInit (void)
{
    RCM->ICC = 0X01;
    RCM->ECC = 0X00;
    RCM->MCC = 0xE1;
    RCM->CSC = 0x00;
    RCM->CLKDIV = 0x18;
    RCM->APBEN1 = 0XFF;
    RCM->APBEN2 = 0XFF;
    RCM->APBEN3 = 0XFF;
    RCM->CSS = 0x00;
    RCM->COC = 0x00;
    while(RCM->COC_B.COEN == SET)
    {}
    RCM->COC = 0x00;
    RCM->HIRCTRIM = 0x00;

    ConfigMasterClock();

#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET;
#else
    SCB->VTOR = FMC_BASE | VECT_TAB_OFFSET;
#endif
}

/*!
 * @brief       Configures the master clock and cpu clock
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void ConfigMasterClock(void)
{
#ifdef MASTER_CLOCK_HXT
     MasterClockHXT();
#elif defined MASTER_CLOCK_6MHz
    MasterClock6M();
#elif defined MASTER_CLOCK_12MHz
    MasterClock12M();
#elif defined MASTER_CLOCK_24MHz
    MasterClock24M();
#elif defined MASTER_CLOCK_48MHz
    MasterClock48M();
#elif defined MASTER_CLOCK_LIRC
    MasterClockLIRC();
#endif
}

#ifdef MASTER_CLOCK_HXT

/*!
 * @brief       Selects HXT as Master clock source and configure CPU clock frequency
 *
 * @param        None
 *
 * @retval      None
 *
 * @note
 */
static void MasterClockHXT(void)
{
    uint16_t counter = 0xFFFF;

    /** Enable Prefetch Buffer */
    FMC->CTRL1_B.PBEN = BIT_SET;
    /** Flash 0 wait state */
    FMC->CTRL1_B.LATENCY = 0;

    RCM->CLKDIV_B.CPUDIV = 0;
    RCM->CSC_B.CSIE = 0;
    RCM->MCC = 0xB4;

    while((RCM->CSC_B.CSIF == BIT_RESET) && (counter))
    {
        counter--;
    }

    if(RCM->CSC_B.CSIF == BIT_SET)
    {
        RCM->CSC_B.CSEN = BIT_SET;
        RCM->ICC_B.HIRCEN = BIT_RESET;
        RCM->CSS_B.CSSEN = BIT_SET;
    }
    else
    {
        RCM->CSC_B.CSBF = BIT_RESET;
    }
}


#elif defined MASTER_CLOCK_6MHz

/*!
 * @brief       Selects HIRC/8 as Master clock source and configure CPU clock
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void MasterClock6M(void)
{
    /** Enable Prefetch Buffer */
    FMC->CTRL1_B.PBEN = BIT_SET;
    /** Flash 0 wait state */
    FMC->CTRL1_B.LATENCY = 0;

    RCM->CLKDIV_B.CPUDIV = 0;
    RCM->CLKDIV_B.HDS = 1;
    RCM->CLKDIV_B.HIRCDIV = 3;
}

#elif defined MASTER_CLOCK_12MHz

/*!
 * @brief       Selects HIRC/4 as Master clock source and configure CPU clock
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void MasterClock12M(void)
{
    /** Enable Prefetch Buffer */
    FMC->CTRL1_B.PBEN = BIT_SET;
    /** Flash 0 wait state */
    FMC->CTRL1_B.LATENCY = 0;

    RCM->CLKDIV_B.CPUDIV = 0;
    RCM->CLKDIV_B.HDS = 1;
    RCM->CLKDIV_B.HIRCDIV = 2;
}

#elif defined MASTER_CLOCK_24MHz

/*!
 * @brief       Selects HIRC/2 as Master clock source and configure CPU clock
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void MasterClock24M(void)
{
    /** Enable Prefetch Buffer */
    FMC->CTRL1_B.PBEN = BIT_SET;
    /** Flash 0 wait state */
    FMC->CTRL1_B.LATENCY = 0;
    RCM->CLKDIV_B.HDS = 1;
    RCM->CLKDIV_B.CPUDIV = 0;
    RCM->CLKDIV_B.HIRCDIV = 1;
}

#elif defined MASTER_CLOCK_48MHz

/*!
 * @brief       Selects HIRC as Master clock source and configure CPU clock
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void MasterClock48M(void)
{
    /** Enable Prefetch Buffer */
    FMC->CTRL1_B.PBEN = BIT_SET;
    /** Flash 1 wait state */
    FMC->CTRL1_B.LATENCY = 1;

    RCM->CLKDIV_B.CPUDIV = 0;
    RCM->CLKDIV_B.HDS = 1;
    RCM->CLKDIV_B.HIRCDIV = 0;
}

#elif defined MASTER_CLOCK_LIRC

/*!
 * @brief       Selects LIRC as Master clock source and configure CPU clock
 *
 * @param        None
 *
 * @retval      None
 *
 * @note
 */
static void MasterClockLIRC(void)
{
    uint16_t counter = 0xFFFF;

    /** Enable Prefetch Buffer */
    FMC->CTRL1_B.PBEN = BIT_SET;
    /** Flash 0 wait state */
    FMC->CTRL1_B.LATENCY = 0;

    RCM->CLKDIV_B.CPUDIV = 0;
    RCM->CSC_B.CSIE = 0;
    RCM->MCS = 0xD2;

    while((RCM->CSC_B.CSIF == BIT_RESET) && (counter))
    {
        counter--;
    }

    if(RCM->CSC_B.CSIF == BIT_SET)
    {
        RCM->CSC_B.CSEN = BIT_SET;
        RCM->ICC_B.HIRCEN = BIT_RESET;
    }
    else
    {
        RCM->CSC_B.CSBF = BIT_RESET;
    }

}
#endif

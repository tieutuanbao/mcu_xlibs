/// @file     SYSTEM_MM32.C
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _SYSTEM_MM32_C_

// Files includes

/// @addtogroup CMSIS
/// @{

#include "mm32_device.h"


/// @}



/// @}


/// Uncomment the line corresponding to the desired System clock (SYSCLK)
/// frequency (after reset the HSI is used as SYSCLK source)
///
/// IMPORTANT NOTE:
/// ==============
/// 1. After each device reset the HSI is used as System clock source.
///
/// 2. Please make sure that the selected System clock doesn't exceed your device's
/// maximum frequency.
///
/// 3. If none of the define below is enabled, the HSI is used as System clock
/// source.
///
/// 4. The System clock configuration functions provided within this file assume that:
/// - For Low, Medium and High density Value line devices an external 8MHz
/// crystal is used to drive the System clock.
/// - For Low, Medium and High density devices an external 8MHz crystal is
/// used to drive the System clock.
/// - For Connectivity line devices an external 25MHz crystal is used to drive
/// the System clock.
/// If you are using different crystal you have to adapt those functions accordingly.


//#define SYSCLK_FREQ_HSE    HSE_VALUE

#define SYSCLK_HSI_48MHz  48000000


/// @}


///////////////////////////////////////////////////////////////
///Clock Definitions
///////////////////////////////////////////////////////////////
// System Clock Frequency Select
#ifdef SYSCLK_FREQ_HSE
u32 SystemCoreClock         = SYSCLK_FREQ_HSE;                                  // HSE Selected as System Clock source
#elif defined SYSCLK_HSI_48MHz
u32 SystemCoreClock         = SYSCLK_HSI_48MHz;                                 // HSI Selected as System Clock source
#else
u32 SystemCoreClock         = HSI_VALUE;                                        // HSI Div 6 Selected as System Clock source
#endif

__I u8 AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
/// @}

static void SetSysClock(void);

#ifdef SYSCLK_FREQ_HSE
static void SetSysClockToHSE(void);

#elif defined SYSCLK_HSI_48MHz
static void SetSysClockTo48_HSI(void);
#endif




/// @}

///////////////////////////////////////////////////////////////
/// @brief  Setup the microcontroller system
///         Initialize the Embedded Flash Interface, the PLL and update the
///         SystemCoreClock variable.
/// @note   This function should be used only after reset.
/// @param  None
/// @retval None
///////////////////////////////////////////////////////////////
void SystemInit (void)
{

    // Reset the RCC clock configuration to the default reset state(for debug purpose)
    // Set HSION bit
    RCC->CR |= (u32)0x00000001;

    // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
    RCC->CFGR &= (u32)0xF0FF0000;

    // Reset HSEON, CSSON and PLLON bits
    RCC->CR &= (u32)0xFEF6FFFF;

    // Reset HSEBYP bit
    RCC->CR &= (u32)0xFFFBFFFF;

    // Disable all interrupts and clear pending bits
    RCC->CIR = 0x009F0000;

    // Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers
    // Configure the Flash Latency cycles and enable prefetch buffer
    SetSysClock();

}

///////////////////////////////////////////////////////////////
/// @brief  Configures the System clock frequency, HCLK,
///         PCLK2 and PCLK1 prescalers.
/// @param  None
/// @retval None
///////////////////////////////////////////////////////////////
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
    SetSysClockToHSE();

#elif defined SYSCLK_HSI_48MHz
    SetSysClockTo48_HSI();
#endif

    // If none of the define above is enabled, the HSI is used as System clock
    //source (default after reset)
}

#ifdef SYSCLK_FREQ_HSE
///////////////////////////////////////////////////////////////
/// @brief  Selects HSE as System clock source and configure HCLK, PCLK2
///          and PCLK1 prescalers.
/// @note   This function should be used only after reset.
/// @param  None
/// @retval None
///////////////////////////////////////////////////////////////
static void SetSysClockToHSE(void)
{
    __IO u32 StartUpCounter = 0, HSEStatus = 0;

    // SYSCLK, HCLK, PCLK2 and PCLK1 configuration
    // Enable HSE
    RCC->CR |= ((u32)RCC_CR_HSEON);

    // Wait till HSE is ready and if Time out is reached exit
    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
        HSEStatus = (u32)0x01;
    }
    else {
        HSEStatus = (u32)0x00;
    }

    if (HSEStatus == (u32)0x01) {
        // Enable Prefetch Buffer
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        // Flash 0 wait state ,bit0~2
        FLASH->ACR &= ~0x07;
        // HCLK = SYSCLK
        RCC->CFGR |= (u32)RCC_CFGR_HPRE_DIV1;


        // PCLK1 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV1;

        // Select HSE as system clock source
        RCC->CFGR &= (u32)((u32)~(RCC_CFGR_SW));
        RCC->CFGR |= (u32)RCC_CFGR_SW_HSE;

        // Wait till HSE is used as system clock source
        while ((RCC->CFGR & (u32)RCC_CFGR_SWS) != (u32)0x04) {
        }
    }
    else {
        // If HSE fails to start-up, the application will have wrong clock
        //  configuration. User can add here some code to deal with this error
    }
}


#elif defined SYSCLK_HSI_48MHz
void SetSysClockTo48_HSI()
{
    u8 temp = 0;

    RCC->CR |= RCC_CR_HSION;
    while(!(RCC->CR & RCC_CR_HSIRDY));

    RCC->CR &= ~(1 << 20);

    RCC->CR &= ~(1 << 2);

//    RCC->CFGR = RCC_CFGR_PPRE1_2;

    FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_PRFTBE;

    RCC->CFGR &= ~RCC_CFGR_SW;
    if (((SCB->CPUID & (0x00000070U)) == 0) && \
            (((u32) * ((u32*)(0x40013400))  == (0xCC4350D1U)) || ((u32) * ((u32*)(0x40013400))  == (0x8C4350D1U)))) {
        RCC->CFGR |= 0x02;

        while( temp != 0x02 ) {
            temp = RCC->CFGR >> 2;
            temp &= 0x03;
        }
    }
    else {
        SystemCoreClock         = HSI_VALUE;                                    //< System Clock Frequency (Core Clock)
    }
}

#endif

/// @}

/// @}

/// @}



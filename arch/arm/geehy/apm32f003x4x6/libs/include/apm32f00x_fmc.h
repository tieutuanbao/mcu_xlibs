/*!
 * @file        apm32f00x_fmc.h
 *
 * @brief       This file contains all the functions prototypes,enumeration and macro for the FMC firmware library
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

#ifndef __APM32F00X_FMC_H
#define __APM32F00X_FMC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f00x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup FMC_Driver FMC Driver
  @{
*/

/** @addtogroup FMC_Enumerations Enumerations
  @{
*/

/**
 * @brief   Flash Status
 */
typedef enum
{
    FMC_STATE_COMPLETE    = ((uint8_t)0), //!< Operation complete
    FMC_STATE_BUSY        = ((uint8_t)1), //!< Busy
    FMC_STATE_PG_ERR      = ((uint8_t)2), //!< Program error
    FMC_STATE_WRP_ERR     = ((uint8_t)3), //!< Write Protection error
    FMC_STATE_TIMEOUT     = ((uint8_t)4), //!< Time out
} FMC_STATE_T;

/**
 * @brief   Flash latency
 */
typedef enum
{
    FMC_LATENCY_0         = ((uint8_t)0),
    FMC_LATENCY_1         = ((uint8_t)1),
    FMC_LATENCY_2         = ((uint8_t)2),
} FMC_LATENCY_T;

/**
 * @brief   Option byte Window watch dog activation
 */
typedef enum
{
    FMC_OB_WWDT_HW        = ((uint16_t)0X00),     //!< activated by hardware
    FMC_OB_WWDT_SW        = ((uint16_t)0X01),     //!< activated by software
} FMC_OB_WWDT_T;

/**
 * @brief   Window watch dog halt reset
 */
typedef enum
{
    FMC_OB_WWDT_HALT_RST      = ((uint16_t)0x00), //!< Reset generate on halt if WWDT active
    FMC_OB_WWDT_HALT_NORST    = ((uint16_t)0x02), //!< No reset generate on halt if WWDT active
} FMC_OB_WWDT_HALT_T;

/**
 * @brief Option byte Independent watch dog activation
 */
typedef enum
{
    FMC_OB_IWDT_HW        = ((uint16_t)0X00),     //!< activated by hardware
    FMC_OB_IWDT_SW        = ((uint16_t)0X04),     //!< activated by software
} FMC_OB_IWDT_T;

/**
 * @brief   LIRC clock Enable or Disable
 */
typedef enum
{
    FMC_OB_LIRCEN_ENABLE  = ((uint16_t)0X00),     //!< LIRC clock is available as cpu clock source
    FMC_OB_LIRCEN_DISABLE = ((uint16_t)0X08),     //!< LIRC clock is not available as cpu clock source
} FMC_OB_LIRCEN_T;

/**
 * @brief   HIRC trimming
 */
typedef enum
{
    FMC_OB_HIRC_TRIM_4    = ((uint16_t)0x00),      //!< 4-bit trimming supported
    FMC_OB_HIRC_TRIM_3    = ((uint16_t)0x10),      //!< 3-bit trimming supported
} FMC_OB_HIRC_TRIM_T;

/**
 * @brief   Alternate function remap state
 */
typedef enum
{
    FMC_OB_AFR_DISABLE    = ((uint16_t)0X00),     //!< Disable Alternate function remap
    FMC_OB_AFR_ENABLE     = ((uint16_t)0X01),     //!< Enable Alternate function remap
} FMC_OB_AFR_T;

/**
 * @brief   Wakup timer divider
 */
typedef enum
{
    FMC_OB_WUPT_DIV_4M_128K   = ((uint16_t)0x00), //!< 4 MHz to 128 kHz prescaler
    FMC_OB_WUPT_DIV_8M_128K   = ((uint16_t)0x01), //!< 8 MHz to 128 kHz prescaler
    FMC_OB_WUPT_DIV_16M_128K  = ((uint16_t)0x02), //!< 8 MHz to 128 kHz prescaler
} FMC_OB_WUPT_DIV_T;

/**
 * @brief   Wakup timer clock source
 */
typedef enum
{
    FMC_OB_WUPT_CLKSRC_HXT_DIV    = ((uint16_t)0x00),     //!< HXT divider as Wakeup timer clock source
    FMC_OB_WUPT_CLKSRC_LIRC       = ((uint16_t)0x04),     //!< LIRC divider as Wakeup timer clock source
} FMC_OB_WUPT_CLKSRC_T;

/**
 * @brief   External clock selection
 */
typedef enum
{
    FMC_OB_EXTCLK_OSCIN       = ((uint16_t)0X00),     //!< External clock signal on OSCIN
    FMC_OB_EXTCLK_OSCIN_OUT   = ((uint16_t)0X08),     //!< External crystal connected to OSCIN/OSCOUT
} FMC_OB_EXTCLK_T;

/**
 * @brief   HXT stabilization time
 */
typedef enum
{
    FMC_OB_HXTCNT_HALF_CYCLE  = ((uint16_t)0x1E),     //!< HXT stabilization time is 0.5 HXT CYCLE
    FMC_OB_HXTCNT_8_CYCLE     = ((uint16_t)0x2D),     //!< HXT stabilization time is 8 HXT CYCLE
    FMC_OB_HXTCNT_128_CYCLE   = ((uint16_t)0x4B),     //!< HXT stabilization time is 128 HXT CYCLE
    FMC_OB_HXTCNT_2048_CYCLE  = ((uint16_t)0xFF),     //!< HXT stabilization time is 2048 HXT CYCLE
} FMC_OB_HXTCNT_T;

/**
 * @brief   Interrupt source
 */
typedef enum
{
    FMC_INT_ERROR             = ((uint32_t)0x400),    //!< Error interrupt
    FMC_INT_COMPLETE          = ((uint32_t)0x1000),   //!< Operation complete interrupt
} FMC_INT_T;

/**
 * @brief   Flags definition
 */
typedef enum
{
    FMC_FLAG_BUSY             = ((uint32_t)0x01),     //!< Busy flag
    FMC_FLAG_PE               = ((uint32_t)0x04),     //!< Program error flag
    FMC_FLAG_WPE              = ((uint32_t)0x10),     //!< Write protection flag
    FMC_FLAG_OC               = ((uint32_t)0x20),     //!< Operation complete flag
    FMC_FLAG_OBERR            = ((uint32_t)0x0100),   //!< Option byte error flag
} FMC_FLAG_T;

/**
 * @brief   Read protection state.Enable or Disable
 */
typedef enum
{
    FMC_RDP_ENABLE        = 0,
    FMC_RDP_DISABLE       = 0xA5,
} FMC_RDP_T;

/**@} end of group FMC_Enumerations*/

/** @addtogroup FMC_Macros Macros
  @{
*/

/** Flash write protect page definition */
#define FMC_WRP_PAGE_0        ((uint32_t)0x00000001)
#define FMC_WRP_PAGE_1        ((uint32_t)0x00000002)
#define FMC_WRP_PAGE_2        ((uint32_t)0x00000004)
#define FMC_WRP_PAGE_3        ((uint32_t)0x00000008)
#define FMC_WRP_PAGE_4        ((uint32_t)0x00000010)
#define FMC_WRP_PAGE_5        ((uint32_t)0x00000020)
#define FMC_WRP_PAGE_6        ((uint32_t)0x00000040)
#define FMC_WRP_PAGE_7        ((uint32_t)0x00000080)
#define FMC_WRP_PAGE_8        ((uint32_t)0x00000100)
#define FMC_WRP_PAGE_9        ((uint32_t)0x00000200)
#define FMC_WRP_PAGE_10       ((uint32_t)0x00000400)
#define FMC_WRP_PAGE_11       ((uint32_t)0x00000800)
#define FMC_WRP_PAGE_12       ((uint32_t)0x00001000)
#define FMC_WRP_PAGE_13       ((uint32_t)0x00002000)
#define FMC_WRP_PAGE_14       ((uint32_t)0x00004000)
#define FMC_WRP_PAGE_15       ((uint32_t)0x00008000)
#define FMC_WRP_PAGE_16       ((uint32_t)0x00010000)
#define FMC_WRP_PAGE_17       ((uint32_t)0x00020000)
#define FMC_WRP_PAGE_18       ((uint32_t)0x00040000)
#define FMC_WRP_PAGE_19       ((uint32_t)0x00080000)
#define FMC_WRP_PAGE_20       ((uint32_t)0x00100000)
#define FMC_WRP_PAGE_21       ((uint32_t)0x00200000)
#define FMC_WRP_PAGE_22       ((uint32_t)0x00400000)
#define FMC_WRP_PAGE_23       ((uint32_t)0x00800000)
#define FMC_WRP_PAGE_24       ((uint32_t)0x01000000)
#define FMC_WRP_PAGE_25       ((uint32_t)0x02000000)
#define FMC_WRP_PAGE_26       ((uint32_t)0x04000000)
#define FMC_WRP_PAGE_27       ((uint32_t)0x08000000)
#define FMC_WRP_PAGE_28       ((uint32_t)0x10000000)
#define FMC_WRP_PAGE_29       ((uint32_t)0x20000000)
#define FMC_WRP_PAGE_30       ((uint32_t)0x40000000)
#define FMC_WRP_PAGE_31       ((uint32_t)0x80000000)
#define FMC_WRP_PAGE_ALL      ((uint32_t)0xFFFFFFFF)

/**@} end of group FMC_Macros*/

/** @addtogroup FMC_Structure Data Structure
  @{
*/

/**
 * @brief   User Option byte config struct definition
 */
typedef struct
{
    FMC_OB_WWDT_T wwdtSw;             //!< Window watch dog activation
    FMC_OB_IWDT_T iwdtSw;             //!< Independent watch dog activation
    FMC_OB_WWDT_HALT_T wwdtHalt;      //!< Window watch dog halt reset
    FMC_OB_LIRCEN_T LIRCen;           //!< Enable or Disable LIRC as CPU clock source
    FMC_OB_HIRC_TRIM_T trimHIRC;      //!< HIRC timming value
} FMC_UserConfig_T;

/**
 * @brief   Option byte Alternate function remap config struct definition
 */
typedef struct
{
    uint8_t AFR0:      1;                //!< AF0.Can be one of value @ref FMC_OB_AFR_T
    uint8_t AFR1:      1;                //!< AF1.Can be one of value @ref FMC_OB_AFR_T
    uint8_t RESERVED1: 1;
    uint8_t AFR3:      1;                //!< AF3.Can be one of value @ref FMC_OB_AFR_T
    uint8_t AFR4:      1;                //!< AF4.Can be one of value @ref FMC_OB_AFR_T
    uint8_t AFR5:      1;                //!< AF5.Can be one of value @ref FMC_OB_AFR_T
    uint8_t RESERVED2: 1;
    uint8_t AFR7:      1;                //!< AF7.Can be one of value @ref FMC_OB_AFR_T
} FMC_AFRConfig_T;


/**@} end of group FMC_Structure*/

/** @addtogroup FMC_Fuctions Fuctions
  @{
*/

/** Latency */
void FMC_SetLatency(FMC_LATENCY_T latency);

/** Hlaf Cycle Access */
void FMC_EnableHlafCycleAccess(void);
void FMC_DisableHlafCycleAccess(void);

/** Prefetch Buffer */
void FMC_EnablePrefetchBuffer(void);
void FMC_DisablePrefetchBuffer(void);
uint8_t FMC_ReadPrefetchBufferStatus(void);

/** Lock */
void FMC_Unlock(void);
void FMC_Lock(void);

/** State management */
FMC_STATE_T FMC_ReadState(void);
FMC_STATE_T FMC_WaitForReady(uint32_t timeOut);

/** Erase and Program */
FMC_STATE_T FMC_ErasePage(uint32_t pageAddr);
FMC_STATE_T FMC_EraseAllPages(void);
FMC_STATE_T FMC_EraseOptionByte(void);
FMC_STATE_T FMC_ProgramWord(uint32_t addr, uint32_t data);
FMC_STATE_T FMC_ProgramHalfWord(uint32_t addr, uint16_t data);
FMC_STATE_T FMC_ProgramOptionByte(uint32_t addr, uint16_t data);

/** Write and Read Protection */
FMC_STATE_T FMC_EnableWriteProtection(uint32_t page);
FMC_STATE_T FMC_ConfigReadOutProtection(FMC_RDP_T rdp);
uint32_t FMC_ReadOptionByteWriteProtection(void);
uint8_t FMC_ReadProtectionStatus(void);

/** Option Byte Configruration and Read */
FMC_STATE_T FMC_ConfigOptionByteUser(FMC_UserConfig_T *userConfig);
FMC_STATE_T FMC_ConfigOptionByteAFR(FMC_AFRConfig_T *AFRConfig);
FMC_STATE_T FMC_ConfigOptionByteClk(FMC_OB_EXTCLK_T extClk, FMC_OB_WUPT_CLKSRC_T wuptClk,
                                                    FMC_OB_WUPT_DIV_T wuptDiv);
FMC_STATE_T FMC_ConfigOptionByteHXTCNT(FMC_OB_HXTCNT_T counter);
uint32_t FMC_ReadOptionByteUser(void);

/** Interrupt and Flag */
void FMC_EnableInterrupt(uint32_t interrupt);
void FMC_DisableInterrupt(uint32_t interrupt);
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag);
void FMC_ClearStatusFlag(uint32_t flag);

/** Low power mode */
void FMC_EnablePowerDownHaltMode(void);
void FMC_DisablePowerDownHaltMode(void);
void FMC_EnablePowerDownActHaltMode(void);
void FMC_DisablePowerDownActHaltMode(void);
void FMC_SetPowerOnTime(uint8_t time);

/**@} end of group FMC_Fuctions*/
/**@} end of group FMC_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F00X_FMC_H */

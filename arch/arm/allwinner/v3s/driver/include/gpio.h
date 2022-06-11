/**
	******************************************************************************
	* @file display.c
	*
	* @brief GPIO header for V3s
	*
	*
	* @author Tieu Tuan Bao
	* Contact: tieutuanbao@gmail.com
	* P-Number: +84979755670
	******************************************************************************
	*/

#ifndef __BITS_V3S_GPIO_H__
#define __BITS_V3S_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

	
#include <stdint.h>
#include "memmap.h"
#include "io.h"


#define GPIOB ((GPIO_REGISTER_TypeDef *)(PIO_BASE+1*0x24))
#define GPIOC ((GPIO_REGISTER_TypeDef *)(PIO_BASE+2*0x24))
#define GPIOD ((GPIO_REGISTER_TypeDef *)(PIO_BASE+3*0x24))
#define GPIOE ((GPIO_REGISTER_TypeDef *)(PIO_BASE+4*0x24))
#define GPIOF ((GPIO_REGISTER_TypeDef *)(PIO_BASE+5*0x24))
#define GPIOG ((GPIO_REGISTER_TypeDef *)(PIO_BASE+6*0x24))
	
#define GPIOB_INTERRUPT	((GPIO_INTERRUPT_REGISTER_TypeDef *)(PIO_BASE + 1*0x20 + 0x200))
#define GPIOG_INTERRUPT	((GPIO_INTERRUPT_REGISTER_TypeDef *)(PIO_BASE + 2*0x20 + 0x200))

#define GPIO_PIN_0                 ((uint32_t)0x00000001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint32_t)0x00000002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint32_t)0x00000004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint32_t)0x00000008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint32_t)0x00000010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint32_t)0x00000020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint32_t)0x00000040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint32_t)0x00000080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint32_t)0x00000100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint32_t)0x00000200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint32_t)0x00000400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint32_t)0x00000800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint32_t)0x00001000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint32_t)0x00002000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint32_t)0x00004000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint32_t)0x00008000)  /* Pin 15 selected   */
#define GPIO_PIN_16                ((uint32_t)0x00010000)  /* Pin 16 selected   */
#define GPIO_PIN_17                ((uint32_t)0x00020000)  /* Pin 17 selected   */
#define GPIO_PIN_18                ((uint32_t)0x00040000)  /* Pin 18 selected   */
#define GPIO_PIN_19                ((uint32_t)0x00080000)  /* Pin 19 selected   */
#define GPIO_PIN_20                ((uint32_t)0x00100000)  /* Pin 20 selected   */
#define GPIO_PIN_21                ((uint32_t)0x00200000)  /* Pin 21 selected   */
#define GPIO_PIN_22                ((uint32_t)0x00400000)  /* Pin 22 selected   */
#define GPIO_PIN_23                ((uint32_t)0x00800000)  /* Pin 23 selected   */
#define GPIO_PIN_24                ((uint32_t)0x01000000)  /* Pin 24 selected   */
#define GPIO_PIN_25                ((uint32_t)0x02000000)  /* Pin 25 selected   */
#define GPIO_PIN_26                ((uint32_t)0x04000000)  /* Pin 26 selected   */
#define GPIO_PIN_27                ((uint32_t)0x08000000)  /* Pin 27 selected   */
#define GPIO_PIN_28                ((uint32_t)0x10000000)  /* Pin 28 selected   */
#define GPIO_PIN_29                ((uint32_t)0x20000000)  /* Pin 29 selected   */
#define GPIO_PIN_30                ((uint32_t)0x40000000)  /* Pin 30 selected   */
#define GPIO_PIN_31                ((uint32_t)0x80000000)  /* Pin 31 selected   */
#define GPIO_PIN_All               ((uint32_t)0xFFFFFFFF)  /* All pins selected */

#define GPIO_NUMBER           32U
	
typedef struct{
	volatile uint32_t CFG0;			// Configure 0
	volatile uint32_t CFG1;			// Configure 1
	volatile uint32_t CFG2;			// Configure 2
	volatile uint32_t CFG3;			// Configure 3
	volatile uint32_t DATA;			// DATA
	volatile uint32_t DRV0;			// Multi-Driving 0
	volatile uint32_t DRV1;			// Multi-Driving 1
	volatile uint32_t PUL0;			// Pull 0
	volatile uint32_t PUL1;			// Pull 1
} GPIO_REGISTER_TypeDef;

typedef struct{
	volatile uint32_t CFG0;			// Interrupt Configure 0
	volatile uint32_t CFG1;			// Interrupt Configure 1
	volatile uint32_t CFG2;			// Interrupt Configure 2
	volatile uint32_t CFG3;			// Interrupt Configure 3
	volatile uint32_t CTL;			// Interrupt Control
	volatile uint32_t STA;			// Interrupt Status
	volatile uint32_t DEB;			// Interrupt Debounce
} GPIO_INTERRUPT_REGISTER_TypeDef;

typedef enum
{
	GPIO_MODE_INPUT     = 0,
	GPIO_MODE_OUTPUT    = 1,
	GPIO_MODE_AF2       = 2,
	GPIO_MODE_AF3       = 3,
	GPIO_MODE_AF4       = 4,
	GPIO_MODE_AF5       = 5,
	GPIO_MODE_AF6       = 6,
	GPIO_MODE_DISABLED  = 7,
} GPIO_Pinmode;

typedef enum
{
	GPIO_PULL_UP_DisDOWN	= 0,
	GPIO_PULL_UP					= 1,
	GPIO_PULL_DOWN				= 2,
	GPIO_PULL_NONE				= 3,
} GPIO_Pullmode;

typedef enum
{
	GPIO_DRV_0          = 0,
	GPIO_DRV_1          = 1,
	GPIO_DRV_2          = 2,
	GPIO_DRV_3          = 3
} GPIO_Driving;

typedef struct{
	uint32_t Pin;
	GPIO_Pinmode Mode;
	GPIO_Pullmode Pull;
	GPIO_Driving MultiDriving;	
} GPIO_InitTypeDef;

typedef enum
{
	EINT_TRG_RISING     = 0,
	EINT_TRG_FALLING    = 1,
	EINT_TRG_HIGH       = 2,
	EINT_TRG_LOW        = 3,
	EINT_TRG_DOUBLE     = 4
} GPIO_InterruptTrigger;

typedef enum
{
	EINT_DEB_SRC_LOSC   = 0,
	EINT_DEB_SRC_HOSC   = 1
} GPIO_DebounceClockSource;

typedef enum
{
	EINT_DEB_DIV_1      = 0,
	EINT_DEB_DIV_2      = 1,
	EINT_DEB_DIV_4      = 2,
	EINT_DEB_DIV_8      = 3,
	EINT_DEB_DIV_16     = 4,
	EINT_DEB_DIV_32     = 5,
	EINT_DEB_DIV_64     = 6,
	EINT_DEB_DIV_128    = 7
} GPIO_DebounceClockScale;

typedef struct{
	uint32_t Pin;
	GPIO_InterruptTrigger Trigger;
	GPIO_DebounceClockScale ClkScale;
	GPIO_DebounceClockSource ClkSource;
} GPIO_Interrupt_InitTypeDef;


void GPIO_Init(GPIO_REGISTER_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void GPIO_Interrupt_Init(GPIO_INTERRUPT_REGISTER_TypeDef *GPIOx_INTERRUPT, GPIO_Interrupt_InitTypeDef *GPIO_Interrupt_Init);

#ifdef __cplusplus
}
#endif

#endif /* __V3S_GPIO_H__ */

#ifndef __F1C100S_TIMER_H__
#define __F1C100S_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "memmap.h"

#define TIM_IRQ_EN		*(volatile uint32_t *)(TIMER_BASE)
#define TIM_IRQ_STA		*(volatile uint32_t *)(TIMER_BASE + 0x04)
	
#define TIM_0_CTRL		*(volatile uint32_t *)(TIMER_BASE + 0x10)
#define TIM_0_INTV		*(volatile uint32_t *)(TIMER_BASE + 0x14)
#define TIM_0_CUR			*(volatile uint32_t *)(TIMER_BASE + 0x18)
#define TIM_1_CTRL		*(volatile uint32_t *)(TIMER_BASE + 0x20)
#define TIM_1_INTV		*(volatile uint32_t *)(TIMER_BASE + 0x24)
#define TIM_1_CUR			*(volatile uint32_t *)(TIMER_BASE + 0x28)
#define TIM_2_CTRL		*(volatile uint32_t *)(TIMER_BASE + 0x30)
#define TIM_2_INTV		*(volatile uint32_t *)(TIMER_BASE + 0x34)
#define TIM_2_CUR			*(volatile uint32_t *)(TIMER_BASE + 0x38)

#define AVS_CTRL			*(volatile uint32_t *)(TIMER_BASE + 0x80)
#define AVS_CNT0			*(volatile uint32_t *)(TIMER_BASE + 0x84)
#define AVS_CNT1			*(volatile uint32_t *)(TIMER_BASE + 0x88)
#define AVS_DIV				*(volatile uint32_t *)(TIMER_BASE + 0x8C)

#define WDG_IRQ_EN		*(volatile uint32_t *)(TIMER_BASE + 0xA0)
#define WDG_IRQ_STA		*(volatile uint32_t *)(TIMER_BASE + 0xA4)
#define WDG_CTRL			*(volatile uint32_t *)(TIMER_BASE + 0xB0)
#define WDG_CFG				*(volatile uint32_t *)(TIMER_BASE + 0xB4)
#define WDG_MODE			*(volatile uint32_t *)(TIMER_BASE + 0xB8)

#define CNT64_CTRL		*(volatile uint32_t *)(TIMER_BASE + 0xD0)
#define CNT64_LOW			*(volatile uint32_t *)(TIMER_BASE + 0xD4)
#define CNT64_HIGH		*(volatile uint32_t *)(TIMER_BASE + 0xD8)

#define __TIM_START(__CHANNEL__)					*(volatile uint32_t *)(TIMER_BASE + 0x10 + ((__CHANNEL__) * 0x10)) |= 3
#define __TIM_STOP(__CHANNEL__)						*(volatile uint32_t *)(TIMER_BASE + 0x10 + ((__CHANNEL__) * 0x10)) &= 0xFFFFFFFE
#define __TIM_SET_PERIOD(__CHANNEL__)			*(volatile uint32_t *)(TIMER_BASE + 0x14 + ((__CHANNEL__) * 0x10)) = (__CHANNEL__)
#define __TIM_RELOAD(__CHANNEL__)					*(volatile uint32_t *)(TIMER_BASE + 0x10 + ((__CHANNEL__) * 0x10)) &= 0xFFFFFFFD
#define __TIM_INTERRUPT_EN(__CHANNEL__)		TIM_IRQ_EN |= (1U << (__CHANNEL__))
#define __TIM_INTERRUPT_DIS(__CHANNEL__)	TIM_IRQ_EN &= ~(1U << (__CHANNEL__))
#define __TIM_GET_STATUS(__CHANNEL__)			TIM_IRQ_STA & (1U << (__CHANNEL__))
#define __TIM_CLEAR_STATUS(__CHANNEL__)		TIM_IRQ_STA &= ~(1U << (__CHANNEL__))
	
/**
	*	@brief	Config Watchdog timer.
	*	@param	__CONFIG__	Watchdog generates a reset signal
  *          This parameter can be one of the following values:
  *            @arg 1: To whole system
  *            @arg 2: Only interrupt
	*/
#define __WDF_CONFIG(__CONFIG__)			WDG_CFG = (__CONFIG__);

/**
	*	@brief	Config Watchdog interval value.
	*	@param	__VALUE__	Watchdog interval value
  *          This parameter can be one of the following values:
  *            @arg 0: 16000 cycles  (0.5s)
  *            @arg 1: 32000 cycles  (1s)
  *            @arg 2: 64000 cycles  (2s)
  *            @arg 3: 96000 cycles  (3s)
  *            @arg 4: 128000 cycles  (4s)
  *            @arg 5: 160000 cycles  (5s)
  *            @arg 6: 192000 cycles  (6s)
  *            @arg 7: 256000 cycles  (8s)
  *            @arg 8: 320000 cycles  (10s)
  *            @arg 9: 384000 cycles  (12s)
  *            @arg 10: 448000 cycles  (14s)
  *            @arg 11: 512000 cycles  (16s)
	*/
#define __WDG_SET_INTV(__VALUE__)			WDG_MODE &= 0xFFFFFF0F;	\
																			WDG_MODE |= (__VALUE__)<<4;

/**
	*	@brief	Enable Watchdog timer.
	*/
#define __WDG_ENABLE									WDG_MODE |= 1;
/**
	*	@brief	Disable Watchdog timer.
	*/
#define __WDG_DISABLE									WDG_MODE &= 0xFFFFFFFE;

/**
	*	@brief	Config 64bit counter.
	*	@param	__MODE__	64bit Counter test mode enable
  *          This parameter can be one of the following values:
  *            @arg 0: Normal mode
  *            @arg 1: Test mode
	*	@param	__SOURCE__	64bit Counter clock source select
  *          This parameter can be one of the following values:
  *            @arg 0: OSC24M
  *            @arg 1: /
	*	@param	__RL_EN__	64bit Counter Read latch select
  *          This parameter can be one of the following values:
  *            @arg 0: No effect
  *            @arg 1: To latch the 64bit Coutner to the Low/Hi register and it will change to zero after the register are latched.
	*	@param	__RL_EN__	64bit Counter clear select
  *          This parameter can be one of the following values:
  *            @arg 0: No effect
  *            @arg 1: To clear the 64bit Coutner Low/Hi register and it will change to zero after the register are cleared.
	*/
#define __COUNTER_64bit_ENABLE(__MODE__, __SOURCE__, __RL_EN__, __CLR_EN__)			CNT64_CTRL = ((__MODE__)<<31)|((__SOURCE__)<<2)|((__RL_EN__)<<1)|(__CLR_EN__);
																			
typedef enum{
	CONTINUOUS,
	SIGNLE
} TIM_MODE_Enum;

typedef enum{
	CLK_DIV_1,
	CLK_DIV_2,
	CLK_DIV_4,
	CLK_DIV_8,
	CLK_DIV_16,
	CLK_DIV_32,
	CLK_DIV_64,
	CLK_DIV_128
} TIME_CLK_PRESCALE_Enum;

typedef enum{
	INTERNAL_DIV_512,
	OSC_24M
} TIM_CLK_SRC_Enum;

#ifdef __cplusplus
}
#endif

#endif /* __F1C100S_TIMER_H__ */

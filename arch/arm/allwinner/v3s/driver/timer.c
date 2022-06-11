/**
	******************************************************************************
	* @file timer.c
	*
	* @brief Timer Config for V3s
	*
	*
	* @author Tieu Tuan Bao
	* Contact: tieutuanbao@gmail.com
	* P-Number: +84979755670
	******************************************************************************
	*/

#include "timer.h"

void TIM_Init(uint8_t channel, TIM_MODE_Enum mode, TIME_CLK_PRESCALE_Enum psc, TIM_CLK_SRC_Enum src) {
	uint32_t temp = (mode << 7) | (psc << 4) | (src << 2);
	*(volatile uint32_t *)((uint32_t)&TIM_0_CTRL + (channel * 0x10)) = temp;
}

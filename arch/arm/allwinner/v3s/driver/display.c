/**
	******************************************************************************
	* @file display.c
	*
	* @brief Display Config for V3s
	*
	*
	* @author Tieu Tuan Bao
	* Contact: tieutuanbao@gmail.com
	* P-Number: +84979755670
	******************************************************************************
	*/

#include "display.h"
#include "gpio.h"
#include "clock.h"
#include "de.h"
#include "tcon.h"


void display_Init(){
	/* ------------------ GPIO Init ------------------ */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode = GPIO_MODE_AF3;
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|
												GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_16|GPIO_PIN_17|GPIO_PIN_18|GPIO_PIN_19|GPIO_PIN_23|GPIO_PIN_24;
	
	GPIO_InitStruct.Pull = GPIO_PULL_NONE;
	GPIO_InitStruct.MultiDriving = GPIO_DRV_3;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
		
	/* ------------------ CLOCK Init ------------------ */
	PLL_Init(PLL_VIDEO, (PLL_PARAM_TypeDef){.P = 1, .N = 100, .K = 1, .M = 4});		//PLL_Video = (24 * N) / M        N=[1,128] M=[1,16]
	PLL_Init(PLL_VE, (PLL_PARAM_TypeDef){.P = 1, .N = 100, .K = 1, .M = 4});		//PLL_VE = (24 * N) / M        N=[1,128] M=[1,16]
	
	write32(CCU_DE_CLK, read32(CCU_DE_CLK)|(1U<<31));					// Enable Gating Clock
	write32(CCU_TCON_CLK, read32(CCU_TCON_CLK)|(1U<<31));			// Enable Gating Clock
	
	TCON_Timing_TypeDef timing;
	timing.pixel_clock_hz = 33000000;
	timing.h_front_porch = 40;
	timing.h_back_porch = 87;
	timing.h_sync_len = 1;
	timing.v_front_porch = 13;
	timing.v_back_porch = 31;
	timing.v_sync_len = 1;
	timing.h_sync_active = 0;
	timing.v_sync_active = 0;
	timing.den_active = 0;
	timing.clk_active = 0;

	TCON_Disable();
	DE_set_mode(800, 480);
	DE_Enable();
	TCON_set_mode(800, 480, 24, timing);
	TCON_Enable();
	DE_Set_Address();
	DE_Enable();
}
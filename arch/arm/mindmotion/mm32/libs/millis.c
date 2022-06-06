#include "millis.h"
#include "hal_conf.h"

static volatile uint32_t _millis_counter = 0;
static uint32_t _factor_ms = 0;
void millis_init(uint8_t systick_clock){    
    _factor_ms = systick_clock * 1000;
    /* Chọn AHB clock và cho phép ngắt */
    SysTick->CTRL = 0xfffffffE;
    /* Kích hoạt NVIC */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
    SysTick->LOAD = _factor_ms;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= 0x01 ;
}

uint32_t millis(void){
    return _millis_counter;
}
/**
 * @brief Hàm phục vụ ngắt Systick
 **/
void SysTick_Handler(void){
    _millis_counter++;
}
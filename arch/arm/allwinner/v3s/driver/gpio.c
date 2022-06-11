/**
	******************************************************************************
	* @file gpio.c
	*
	* @brief PIO Config for V3s
	*
	*
	* @author Tieu Tuan Bao
	* Contact: tieutuanbao@gmail.com
	* P-Number: +84979755670
	******************************************************************************
	*/

#include "gpio.h"

void GPIO_Init(GPIO_REGISTER_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init){
	uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;
	uint32_t temp = 0;
  /* Configure the port pins */	
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
    /* Get the IO position */
    ioposition = 0x01U << position;
    /* Get the current IO position */
    iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;
    if(iocurrent == ioposition)
    {
			/* Set GPIO Mode */
			if(position < 8){							// Px0 -> Px7
				temp = GPIOx->CFG0;										// Get Old Data
				temp &= ~(0x0F << (position * 4));		// Set zero 4bit
				temp |= (GPIO_Init->Mode << (position * 4));
				GPIOx->CFG0 = temp;
			}else if(position < 16){			// Px8 -> Px15
				temp = GPIOx->CFG1;										// Get Old Data
				temp &= ~(0x0F << (position * 4));		// Set zero 4bit
				temp |= (GPIO_Init->Mode << (position * 4));
				GPIOx->CFG1 = temp;				
			}else if(position < 24){			// Px16 -> Px23
				temp = GPIOx->CFG2;										// Get Old Data
				temp &= ~(0x0F << (position * 4));		// Set zero 4bit
				temp |= (GPIO_Init->Mode << (position * 4));
				GPIOx->CFG2 = temp;				
			}else{												// Px24 -> Px31
				temp = GPIOx->CFG3;										// Get Old Data
				temp &= ~(0x0F << (position * 4));		// Set zero 4bit
				temp |= (GPIO_Init->Mode << (position * 4));
				GPIOx->CFG3 = temp;				
			}
			/* Set Multi-Driving */
			if(position < 16){
				temp = GPIOx->DRV0;										// Get Old Data
				temp &= ~(0x03 << (position * 2));		// Set zero 4bit
				temp |= (GPIO_Init->MultiDriving << (position * 2));
				GPIOx->DRV0 = temp;
			}else {
				temp = GPIOx->DRV1;										// Get Old Data
				temp &= ~(0x03 << (position * 2));		// Set zero 4bit
				temp |= (GPIO_Init->MultiDriving << (position * 2));
				GPIOx->DRV1 = temp;				
			}
			/* Set Pull Mode */
			if(position < 16){
				temp = GPIOx->PUL0;										// Get Old Data
				temp &= ~(0x03 << (position * 2));		// Set zero 4bit
				temp |= (GPIO_Init->Pull << (position * 2));
				GPIOx->PUL0 = temp;
			}else {
				temp = GPIOx->PUL1;										// Get Old Data
				temp &= ~(0x03 << (position * 2));		// Set zero 4bit
				temp |= (GPIO_Init->Pull << (position * 2));
				GPIOx->PUL1 = temp;				
			}
		}
	}
}

void GPIO_Interrupt_Init(GPIO_INTERRUPT_REGISTER_TypeDef *GPIOx_INTERRUPT, GPIO_Interrupt_InitTypeDef *GPIO_Interrupt_Init){
	uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;
	uint32_t temp = 0;
  /* Configure the port pins */	
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
    /* Get the IO position */
    ioposition = 0x01U << position;
    /* Get the current IO position */
    iocurrent = (uint32_t)(GPIO_Interrupt_Init->Pin) & ioposition;
    if(iocurrent == ioposition)
    {
			/* Set GPIO Interrupt Controller Register */
			GPIOx_INTERRUPT->CTL |= GPIO_Interrupt_Init->Pin;
			
			/* Set GPIO Interrupt Trigger Register */
			if(position < 8){							// Px0 -> Px7
				temp = GPIOx_INTERRUPT->CFG0;										// Get Old Data
				temp &= ~(0x0F << (position * 4));		// Set zero 4bit
				temp |= (GPIO_Interrupt_Init->Trigger << (position * 4));
				GPIOx_INTERRUPT->CFG0 = temp;
			}else if(position < 16){			// Px8 -> Px15
				temp = GPIOx_INTERRUPT->CFG1;										// Get Old Data
				temp &= ~(0x0F << (position * 4));		// Set zero 4bit
				temp |= (GPIO_Interrupt_Init->Trigger << (position * 4));
				GPIOx_INTERRUPT->CFG1 = temp;				
			}else if(position < 24){			// Px16 -> Px23
				temp = GPIOx_INTERRUPT->CFG2;										// Get Old Data
				temp &= ~(0x0F << (position * 4));		// Set zero 4bit
				temp |= (GPIO_Interrupt_Init->Trigger << (position * 4));
				GPIOx_INTERRUPT->CFG2 = temp;				
			}else{												// Px24 -> Px31
				temp = GPIOx_INTERRUPT->CFG3;										// Get Old Data
				temp &= ~(0x0F << (position * 4));		// Set zero 4bit
				temp |= (GPIO_Interrupt_Init->Trigger << (position * 4));
				GPIOx_INTERRUPT->CFG3 = temp;				
			}
			
			/* Set GPIO Interrupt Debounce Register */
			GPIOx_INTERRUPT->DEB = (GPIO_Interrupt_Init->ClkScale << 4) | (GPIO_Interrupt_Init->ClkSource);
		}
	}
}

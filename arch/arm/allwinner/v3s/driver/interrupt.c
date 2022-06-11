/**
	******************************************************************************
	* @file interrupt.c
	*
	* @brief Config interrupt V3s
	*
	*
	* @author Tieu Tuan Bao
	* Contact: tieutuanbao@gmail.com
	* P-Number: +84979755670
	******************************************************************************
	*/

#include "interrupt.h"

/* enable IRQ interrupts */
void enable_interrupts (void)
{
	asm("CPSIE i");
	return;
}


/*
 * disable IRQ/FIQ interrupts
 * returns true if interrupts had been enabled before we disabled them
 */
void disable_interrupts (void)
{	
	asm("CPSID i");
	return;
}
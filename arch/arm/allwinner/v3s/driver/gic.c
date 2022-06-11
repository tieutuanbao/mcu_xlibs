/**
 * @file GIC_400.c
 *
 * @brief 
 *
 * @ingroup PackageName
 * (Note: this needs exactly one @defgroup somewhere)
 *
 * @author Tieu Tuan Bao
 * Contact: tieutuanbao@gmail.com
 * P-Number: +84979755670
 */


#include "gic.h"
#include "string.h"
#include "stdio.h"
#include "stdint.h"


_irq_handler sunxi_int_handlers[GIC_IRQ_NUM];

static void default_isr(void *data)
{
//	printf("default_isr():  called from IRQ %d\n", (uint32_t)data);
	while(1);
}

int irq_enable(uint32_t irq_no)
{
	uint32_t reg_val;
	uint32_t offset;

	if(irq_no >= GIC_IRQ_NUM){
//		printf("irq NO.(%d) > GIC_IRQ_NUM(%d) !!\n", irq_no, GIC_IRQ_NUM);
		return -1;
	}
	if(irq_no == IRQ_NMI){
		*(volatile uint32_t *)(0x01f00c00 + 0x10) |= 1;
		*(volatile uint32_t *)(0x01f00c00 + 0x40) |= 1;
	}

	offset   = irq_no >> 5;
	reg_val  = GICD_ISENABLER(offset);
	reg_val |= 1 << (irq_no & 0x1f);
	GICD_ISENABLER(offset) = reg_val;
	return 0;
}

int irq_disable(uint32_t irq_no)
{
	uint32_t reg_val;
	uint32_t offset;

	if (irq_no >= GIC_IRQ_NUM)
	{
//		printf("irq NO.(%d) > GIC_IRQ_NUM(%d) !!\n", irq_no, GIC_IRQ_NUM);
		return -1;
	}
	if(irq_no == IRQ_NMI)
	{
		*(volatile uint32_t *)(0x01f00c00 + 0x10) |= 1;
		*(volatile uint32_t *)(0x01f00c00 + 0x40) &= ~1;
	}

	offset   = irq_no >> 5;
	reg_val  = (1 << (irq_no & 0x1f));
	GICD_ICENABLER(offset) = reg_val;

	return 0;
}

static void gic_sgi_handler(uint32_t irq_no)
{
//	printf("SGI irq %d coming... \n", irq_no);
}

static void gic_ppi_handler(uint32_t irq_no)
{
//	printf("PPI irq %d coming... \n", irq_no);
}

static void gic_spi_handler(uint32_t irq_no)
{
	if (sunxi_int_handlers[irq_no].m_func != default_isr)
	{
		sunxi_int_handlers[irq_no].m_func(sunxi_int_handlers[irq_no].m_data);
	}
}

static void gic_clear_pending(uint32_t irq_no)
{
	uint32_t reg_val;
	uint32_t offset;

	offset = irq_no >> 5;
	reg_val = GICD_ICPENDR(offset);
	reg_val |= (1 << (irq_no & 0x1f));
	GICD_ICPENDR(offset) = reg_val;
	return ;
}

void irq_install_handler (uint32_t irq, interrupt_handler_t handle_irq, void *data){
	disable_interrupts();
	if (irq >= GIC_IRQ_NUM || !handle_irq)
	{
		enable_interrupts();
		return;
	}

	sunxi_int_handlers[irq].m_data = data;
	sunxi_int_handlers[irq].m_func = handle_irq;

	enable_interrupts();
}

void irq_free_handler(uint32_t irq)
{
	disable_interrupts();
	if (irq >= GIC_IRQ_NUM)
	{
		enable_interrupts();
		return;
	}

	sunxi_int_handlers[irq].m_data = NULL;
	sunxi_int_handlers[irq].m_func = default_isr;

	enable_interrupts();
}

void SystemIrqHandler()
{
	uint32_t idnum;

	idnum = GICC_IAR;
	if (idnum == 1023)
	{
//		printf("spurious irq !!\n");
		return;
	}
	if (idnum >= GIC_IRQ_NUM) {
//		printf("irq NO.(%d) > GIC_IRQ_NUM(%d) !!\n", idnum, GIC_IRQ_NUM-32);
		return;
	}
	if (idnum < 16)
		gic_sgi_handler(idnum);
	else if (idnum < 32)
		gic_ppi_handler(idnum);
	else
		gic_spi_handler(idnum);

	if(idnum == IRQ_NMI)
	{
		*(volatile uint32_t *)(0x01f00c00 + 0x10) |= 1;
	}

	GICC_EOIR = idnum;
	GICC_DIR = idnum;
	gic_clear_pending(idnum);
	return;
}

static void gic_distributor_init(void)
{
	uint32_t cpumask = 0x01010101;
	uint32_t gic_irqs;
	uint32_t i;

	GICD_CTRL = 0;

	/* check GIC hardware configutation */
	gic_irqs = ((GICD_TYPER & 0x1f) + 1) * 32;
	if (gic_irqs > 1020)
	{
		gic_irqs = 1020;
	}
	if (gic_irqs < GIC_IRQ_NUM)
	{
//		printf("GIC parameter config error, only support %d irqs < %d(spec define)!!\n", gic_irqs, GIC_IRQ_NUM);
		return ;
	}
	/* set trigger type to be level-triggered, active low */
	for (i=0; i<GIC_IRQ_NUM; i+=16)
	{
		GICD_ICFGR_SGI(i>>4) = 0;
	}
	/* set priority SPI */
	for (i = 32; i < GIC_IRQ_NUM; i += 4)
	{
		GICD_IPRIORITYR(((i - 32) >> 2) + 8) = 0xa0a0a0a0;
	}
	/* set processor target */
	for (i = 32; i < GIC_IRQ_NUM; i += 4)
	{
		GICD_ITARGETSR(((i - 32)>>2) + 8) = cpumask;
	}
	/* disable all interrupts */
	for (i=32; i<GIC_IRQ_NUM; i+=32)
	{
		GICD_ICENABLER(i>>5) = 0xffffffff;
	}
	/* clear all interrupt active state */
	for (i=32; i<GIC_IRQ_NUM; i+=32)
	{
		GICD_ICACTIVER(i>>5) = 0xffffffff;
	}
	GICD_CTRL = 1;
	return ;
}

static void gic_cpuif_init(void)
{
	uint32_t i;

	GICC_CTRL = 0;
	/*
	 * Deal with the banked PPI and SGI interrupts - disable all
	 * PPI interrupts, ensure all SGI interrupts are enabled.
	*/
	GICD_ICENABLER(0) = 0xffff0000;
	GICD_ISENABLER(0) = 0x0000ffff;
	/* Set priority on PPI and SGI interrupts */
	for (i=0; i<16; i+=4)
	{
		GICD_IPRIORITYR(i >> 2) = 0xa0a0a0a0;
	}
	for (i=16; i<32; i+=4)
	{
		GICD_IPRIORITYR(((i - 16) >> 2) + 4) = 0xa0a0a0a0;
	}

	GICC_PMR = 0xf0;
	GICC_CTRL = 1;
	return ;
}

int arch_interrupt_init (void)
{
	int i;
	for (i=0; i<GIC_IRQ_NUM; i++)
	{
		sunxi_int_handlers[i].m_func = default_isr;
	}
	//if((gd->securemode == SUNXI_SECURE_MODE_NO_SECUREOS) ||
	//	(gd->securemode == SUNXI_NORMAL_MODE) || (gd->securemode == SUNXI_SECURE_MODE))
	{
		//printf("gic: normal or no secure os mode\n");
		gic_distributor_init();
		gic_cpuif_init();
	}
	return 0;
}

int arch_interrupt_exit(void)
{
	gic_distributor_init();
	gic_cpuif_init();
	return 0;
}


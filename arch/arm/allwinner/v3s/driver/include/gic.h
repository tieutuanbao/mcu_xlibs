/**
 * @file GIC_400.h
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

#ifndef __GIC400_H
#define __GIC400_H

#include "memmap.h"
#include "interrupt.h"

/* +++++++++++++++++++++++++++ GIC registers +++++++++++++++++++++++++++ */
/* Distributor register summary */
#define GICD_CTRL						*(volatile uint32_t *)(GIC_BASE + 0x0000)
#define GICD_TYPER					*(volatile uint32_t *)(GIC_BASE + 0x0004)
#define GICD_IIDR						*(volatile uint32_t *)(GIC_BASE + 0x0008)

#define GICD_IGROUPR(n)			*(volatile uint32_t *)(GIC_BASE + 0x0080 + (n) * 4)

#define GICD_ISENABLER(_n)			*(volatile uint32_t *)(GIC_BASE + 0x100 + 4 * (_n))
#define GICD_ISENABLER_SPI(_n)	*(volatile uint32_t *)(GIC_BASE + 0x104 + 4 * (_n))

#define GICD_ICENABLER(_n)	*(volatile uint32_t *)(GIC_BASE + 0x180 + 4 * (_n))

#define GICD_ISPENDR(_n)		*(volatile uint32_t *)(GIC_BASE + 0x200 + 4 * (_n))
#define GICD_ICPENDR(_n)		*(volatile uint32_t *)(GIC_BASE + 0x280 + 4 * (_n))
#define GICD_ISACTIVER(_n)	*(volatile uint32_t *)(GIC_BASE + 0x300 + 4 * (_n))
#define GICD_ICACTIVER(_n)	*(volatile uint32_t *)(GIC_BASE + 0x380 + 4 * (_n))
#define GICD_IPRIORITYR(_n)	*(volatile uint32_t *)(GIC_BASE + 0x400 + 4 * (_n))
#define GICD_ITARGETSR(_n)	*(volatile uint32_t *)(GIC_BASE + 0x800 + 4 * (_n))

#define GICD_ICFGR_SGI(_n)	*(volatile uint32_t *)(GIC_BASE + 0xC00 + 4 * (_n))
#define GICD_ICFGR_PPI			*(volatile uint32_t *)(GIC_BASE + 0xC04)
#define GICD_ICFGR_SPI(_n)	*(volatile uint32_t *)(GIC_BASE + 0xC08 + 4 * (_n))

#define GICD_PPISR					*(volatile uint32_t *)(GIC_BASE + 0xD00)
#define GICD_SPISR(_n)			*(volatile uint32_t *)(GIC_BASE + 0xD04 + 4 * (_n))
#define GICD_SGIR						*(volatile uint32_t *)(GIC_BASE + 0xF00)

#define GICD_CPENDSGIR(_n)	*(volatile uint32_t *)(GIC_BASE + 0xF10 + 4 * (_n))
#define GICD_SPENDSGIR(_n)	*(volatile uint32_t *)(GIC_BASE + 0xF20 + 4 * (_n))

#define GICD_PIDR4					*(volatile uint32_t *)(GIC_BASE + 0xFD0)
#define GICD_PIDR5					*(volatile uint32_t *)(GIC_BASE + 0xFD4)
#define GICD_PIDR6					*(volatile uint32_t *)(GIC_BASE + 0xFD8)
#define GICD_PIDR7					*(volatile uint32_t *)(GIC_BASE + 0xFDC)
#define GICD_PIDR0					*(volatile uint32_t *)(GIC_BASE + 0xFE0)
#define GICD_PIDR1					*(volatile uint32_t *)(GIC_BASE + 0xFE4)
#define GICD_PIDR2					*(volatile uint32_t *)(GIC_BASE + 0xFE8)
#define GICD_PIDR3					*(volatile uint32_t *)(GIC_BASE + 0xFEC)

#define GICD_CIDR0					*(volatile uint32_t *)(GIC_BASE + 0xFF0)
#define GICD_CIDR1					*(volatile uint32_t *)(GIC_BASE + 0xFF4)
#define GICD_CIDR2					*(volatile uint32_t *)(GIC_BASE + 0xFF8)
#define GICD_CIDR3					*(volatile uint32_t *)(GIC_BASE + 0xFFC)

/* CPU interface register summary */
#define GICC_CTRL						*(volatile uint32_t *)(CPUIF_BASE + 0x000)	//	0x8000
#define GICC_PMR						*(volatile uint32_t *)(CPUIF_BASE + 0x004) 	//	0x8004
#define GICC_BPR						*(volatile uint32_t *)(CPUIF_BASE + 0x008)	//	0x8008
#define GICC_IAR						*(volatile uint32_t *)(CPUIF_BASE + 0x00C)	//	0x800c
#define GICC_EOIR						*(volatile uint32_t *)(CPUIF_BASE + 0x010)	//	0x8010
#define GICC_RPR						*(volatile uint32_t *)(CPUIF_BASE + 0x014)	//	0x8014
#define GICC_HPPIR					*(volatile uint32_t *)(CPUIF_BASE + 0x018)	//	0x8018
#define GICC_ABPR						*(volatile uint32_t *)(CPUIF_BASE + 0x01C)	//	0x801C
#define GICC_AIAR						*(volatile uint32_t *)(CPUIF_BASE + 0x020)	//	0x8020
#define GICC_AEOIR					*(volatile uint32_t *)(CPUIF_BASE + 0x024)	//	0x8024
#define GICC_AHPPIR					*(volatile uint32_t *)(CPUIF_BASE + 0x028)	//	0x8028

#define GICC_APR(n)					*(volatile uint32_t *)(CPUIF_BASE + 0x0D0 + (n) * 4)	//	Active Priorities Register
#define GICC_NSAPR(n)				*(volatile uint32_t *)(CPUIF_BASE + 0x0E0 + (n) * 4)	//	Non-secure Active Priorities Registers

#define GICC_IIDR						*(volatile uint32_t *)(CPUIF_BASE + 0x0FC)	//	0x80FC
#define GICC_DIR						*(volatile uint32_t *)(CPUIF_BASE + 0x1000)	//	0x1000

typedef struct
{
	void *m_data;
	void (*m_func)( void * data);
} _irq_handler;

extern int gic_init(void);
extern int gic_exit(void);

#endif

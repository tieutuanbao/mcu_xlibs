#ifndef __MEMMAP_H
#define __MEMMAP_H

#define SRAM_A1								(0x0)
#define SRAM_C								(0x4000)

#define DE_BASE								(0x01000000)
#define SYS_CTRL_BASE					(0x01C00000)
#define DMA_BASE							(0x01C02000)
#define TCON_BASE							(0x01C0C000)
#define VE_BASE								(0x01C0E000)

#define MMC0_BASE							(0x01C0F000)
#define MMC1_BASE							(0x01C10000)
#define MMC2_BASE							(0x01C11000)

#define CRPT_ENGINE_BASE			(0x01C15000)
#define OTG_DEVICE_BASE				(0x01C19000)
#define OTG_OHCI0_EHCI0_BASE	(0x01C1A000)

#define CCU_BASE							(0x01C20000)

#define PIO_BASE							(0x01C20800)
#define TIMER_BASE						(0x01C20C00)
#define PWM_BASE							(0x01C21400)

#define LRADC_BASE						(0x01C22800)
#define AC_BASE								(0x01C22C00)

#define UART0_BASE						(0x01C28000)
#define UART1_BASE						(0x01C28400)
#define UART2_BASE						(0x01C28800)

#define TWI0_BASE							(0x01C2AC00)
#define TWI1_BASE							(0x01C2B000)

#define EMAC_BASE							(0x01C30000)

#define HSTMR_BASE						(0x01C60000)

#define DRAMCOM_BASE					(0x01C62000)
#define DRAMCTL0_BASE					(0x01C63000)
#define DRAMPHY0_BASE					(0x01C65000)

#define SPI0_BASE							(0x01C68000)

#define SCU_BASE							(0x01C80000)
#define GIC_BASE							(0x01C81000)
#define CPUIF_BASE						(0x01C82000)

#define CSI_BASE							(0x01CB0000)

#define RTC_BASE							(0x01C20400)

#define CORESIGHT_DBG_BASE		(0x3F500000)

#define TSGEN_RO_BASE					(0x3F506000)
#define TSGEN_CTRL_BASE				(0x3F507000)

#define DDR2_BASE							(0x40000000)
#define BROM_BASE							(0xFFFF0000)

#endif

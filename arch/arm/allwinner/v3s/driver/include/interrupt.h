#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include <stdint.h>

#define IRQ_GIC_START    (32)

#ifndef CONFIG_FPGA	

#define IRQ_UART0					(IRQ_GIC_START + 0)		/*	UART0		*/
#define IRQ_UART1					(IRQ_GIC_START + 1)		/*	UART1		*/
#define IRQ_UART2					(IRQ_GIC_START + 2)		/*	UART2		*/
#define IRQ_UART3					(IRQ_GIC_START + 3)		/*	UART3		*/
#define IRQ_UART4					(IRQ_GIC_START + 4)		/*	UART4		*/
#define IRQ_UART5					(IRQ_GIC_START + 5)		/*	UART5		*/
#define IRQ_TWI0					(IRQ_GIC_START + 6)		/*	TWI0		*/
#define IRQ_TWI1					(IRQ_GIC_START + 7)		/*	TWI1		*/
#define IRQ_TWI2					(IRQ_GIC_START + 8)		/*	TWI0		*/
#define IRQ_TWI3					(IRQ_GIC_START + 9)		/*	TWI1		*/

#define IRQ_EINTA					(IRQ_GIC_START + 11)		/*	EINTA		*/
#define IRQ_SPDIF					(IRQ_GIC_START + 12)		/*	SPDIF		*/
#define IRQ_DAUDIO0				(IRQ_GIC_START + 13)		/*	DAUDIO0		*/
#define IRQ_DAUDIO1  		 	(IRQ_GIC_START + 14)    /*  DAUDIO1     */
#define IRQ_EINTB    		 	(IRQ_GIC_START + 15)    /*  EINTB       */
#define IRQ_EINTE    		 	(IRQ_GIC_START + 16)    /*  EINTE       */
#define IRQ_EINTG     		(IRQ_GIC_START + 17)    /*  EINTG       */
#define IRQ_TIMER0				(IRQ_GIC_START + 18)		/*	Timer0		*/
#define IRQ_TIMER1				(IRQ_GIC_START + 19)		/*	Timer1		*/
#define IRQ_TIMER2				(IRQ_GIC_START + 20)		/*	Timer2		*/
#define IRQ_TIMER3       	(IRQ_GIC_START + 21)    /*  Timer3      */
#define IRQ_TIMER4       	(IRQ_GIC_START + 22)    /*  Timer4      */
#define IRQ_TIMER5       	(IRQ_GIC_START + 23)    /*  Timer5      */
#define	IRQ_WATCHDOG4			(IRQ_GIC_START + 24)		/*	WATCHDOG4	*/
#define	IRQ_WATCHDOG1			(IRQ_GIC_START + 25)		/*	WATCHDOG1	*/
#define	IRQ_WATCHDOG2			(IRQ_GIC_START + 26)		/*	WATCHDOG2	*/
#define	IRQ_WATCHDOG3			(IRQ_GIC_START + 27)		/*	WATCHDOG3	*/
#define	IRQ_TOUCHPANEL		(IRQ_GIC_START + 28)		/*	TOUCH PANEL	*/
#define IRQ_CODEC					(IRQ_GIC_START +	29)		/*	AUDIO CEDEC	*/
#define IRQ_LRADC					(IRQ_GIC_START + 30)		/*	LRADC		*/
#define IRQ_MTCACC				(IRQ_GIC_START + 31)		/*	MTCACC		*/
#define IRQ_NMI						(IRQ_GIC_START + 32)		/*	NMI			*/
#define IRQ_RTIMER0				(IRQ_GIC_START + 33)		/*	R_TIMER 0	*/
#define IRQ_RTIMER1				(IRQ_GIC_START + 34)		/*	R_TIMER 1	*/

#define IRQ_RWATCHDOG			(IRQ_GIC_START + 36)    /*	R_WATCHDO	*/
#define IRQ_RCIR					(IRQ_GIC_START + 37)    /*  R_CIR		*/
#define	IRQ_RUART					(IRQ_GIC_START + 38)		/*	R_UART		*/
#define IRQ_RP2TWI				(IRQ_GIC_START + 39)		/*	R_P2TWI		*/
#define	IRQ_RALARM0				(IRQ_GIC_START + 40)		/*	R_RLARM 0	*/
#define	IRQ_RALARM1				(IRQ_GIC_START + 41)		/*	R_RLARM 1	*/

#define IRQ_R_1WIRE				(IRQ_GIC_START + 43)		/*	R_ONE_WIRE	*/
#define	IRQ_RTWI					(IRQ_GIC_START + 44)		/*	R_TWI		*/
#define IRQ_EINTL					(IRQ_GIC_START + 45)		/*	R_EINTL		*/
#define IRQ_EINTM					(IRQ_GIC_START + 46)		/*	R_EINTM		*/

#define	IRQ_SPINLOCK			(IRQ_GIC_START + 48)		/*	SPINLOCK	*/
#define	IRQ_MBOX					(IRQ_GIC_START + 49)		/*	M-BOX		*/
#define	IRQ_DMA						(IRQ_GIC_START + 50)		/*	DMA			*/
#define IRQ_HSTIMER0			(IRQ_GIC_START + 51)		/*	HSTIMER0	*/
#define IRQ_HSTIMER1			(IRQ_GIC_START + 52)		/*	HSTIMER1	*/
#define IRQ_HSTIMER2			(IRQ_GIC_START + 53)		/*	HSTIMER2	*/
#define IRQ_HSTIMER3			(IRQ_GIC_START + 54)		/*	HSTIMER3	*/

#define	IRQ_TZASC					(IRQ_GIC_START + 56)		/*	TZASC		*/

#define	IRQ_VE						(IRQ_GIC_START + 58)		/*	VE			*/
#define	IRQ_DIGMIC				(IRQ_GIC_START + 59)		/*	DIG_MIC		*/
#define IRQ_MMC0					(IRQ_GIC_START + 60)		/*	MMC0		*/
#define IRQ_MMC1					(IRQ_GIC_START + 61)		/*	MMC1		*/
#define IRQ_MMC2					(IRQ_GIC_START + 62)		/*	MMC2		*/
#define IRQ_MMC3					(IRQ_GIC_START + 63)		/*	MMC3		*/

#define IRQ_SPI0					(IRQ_GIC_START + 65)		/*	SPI0		*/
#define IRQ_SPI1					(IRQ_GIC_START + 66)		/*	SPI1		*/
#define IRQ_SPI2					(IRQ_GIC_START + 67)		/*	SPI2		*/
#define IRQ_SPI3					(IRQ_GIC_START + 68)		/*	SPI3		*/
#define IRQ_NAND1					(IRQ_GIC_START + 69)		/*	NAND1		*/
#define IRQ_NAND0					(IRQ_GIC_START + 70)		/*	NAND0		*/

#define IRQ_USB_OTG				(IRQ_GIC_START + 71)		/*	USB_OTG		*/
#define IRQ_USB_EHCI0			(IRQ_GIC_START + 72)		/*	USB_EHCI0	*/
#define IRQ_USB_OHCI0			(IRQ_GIC_START + 73)		/*	USB_OHCI0	*/
#define IRQ_USB_EHCI1			(IRQ_GIC_START + 74)		/*	USB_EHCI1	*/
#define IRQ_USB_OHCI1			(IRQ_GIC_START + 75)		/*	USB_OHCI1	*/

#define IRQ_USB_OHCI2			(IRQ_GIC_START + 77)		/*	USB_OHCI2	*/


#define IRQ_SS						(IRQ_GIC_START + 80)		/*	SS			*/
#define IRQ_TS						(IRQ_GIC_START + 81)		/*	TS			*/
#define IRQ_GMAC					(IRQ_GIC_START + 82)		/*	GMAC		*/
#define IRQ_MP						(IRQ_GIC_START + 83)		/*	MP			*/
#define IRQ_CSI0					(IRQ_GIC_START + 84)		/*	CSI0		*/
#define IRQ_CSI1					(IRQ_GIC_START + 85)		/*	CSI1		*/
#define IRQ_LCD0					(IRQ_GIC_START + 86)		/*	LCD0		*/
#define IRQ_LCD1					(IRQ_GIC_START + 87)		/*	LCD1		*/
#define IRQ_HDMI					(IRQ_GIC_START + 88)		/*	HDMI		*/
#define IRQ_MIPIDSI				(IRQ_GIC_START + 89)		/*	MIPI DSI	*/
#define IRQ_MIPICSI				(IRQ_GIC_START + 90)		/*	MIPI CSI	*/
#define IRQ_DEIRQ0				(IRQ_GIC_START + 91)		/*	DE_IRQ0		*/
#define IRQ_DEIRQ1				(IRQ_GIC_START + 92)		/*	DE IRQ1		*/
#define	IRQ_GPU						(IRQ_GIC_START + 97)		/*	GPU			*/

#define	IRQ_CTI0					(IRQ_GIC_START + 108)	/*	CTI0		*/
#define	IRQ_CTI1					(IRQ_GIC_START + 109)	/*	CTI1		*/
#define	IRQ_CTI2					(IRQ_GIC_START + 110)	/*	CTI2		*/
#define	IRQ_CTI3					(IRQ_GIC_START + 111)	/*	CTI3		*/
#define IRQ_COMMTX0				(IRQ_GIC_START + 112)	/*	COMMTX0		*/
#define IRQ_COMMTX1				(IRQ_GIC_START + 113)	/*	COMMTX1		*/
#define IRQ_COMMTX2				(IRQ_GIC_START + 114)	/*	COMMTX2		*/
#define IRQ_COMMTX3				(IRQ_GIC_START + 115)	/*	COMMTX3		*/
#define IRQ_COMMRX0				(IRQ_GIC_START + 116)	/*	COMMRX0		*/
#define IRQ_COMMRX1				(IRQ_GIC_START + 117)	/*	COMMRX1		*/
#define IRQ_COMMRX2				(IRQ_GIC_START + 118)	/*	COMMRX2		*/
#define IRQ_COMMRX3				(IRQ_GIC_START + 119)	/*	COMMRX3		*/
#define	IRQ_PMU0					(IRQ_GIC_START + 120)	/*	PMU0		*/
#define	IRQ_PMU1					(IRQ_GIC_START + 121)	/*	PMU1		*/
#define	IRQ_PMU2					(IRQ_GIC_START + 122)	/*	PMU2		*/
#define	IRQ_PMU3					(IRQ_GIC_START + 123)	/*	PMU3		*/
#define	IRQ_AXI_ERROR			(IRQ_GIC_START + 124)	/*	AXI_ERROR	*/

#define GIC_IRQ_NUM				(IRQ_AXI_ERROR + 1)

#else
#define GIC_SRC_SPI(_n)		(32 + (_n))
#define IRQ_NMI                     GIC_SRC_SPI(0)  /* 32 */
#define IRQ_UART0                   GIC_SRC_SPI(1)  /* 33 */
#define IRQ_TWI0                    GIC_SRC_SPI(2)  /* 34 */
#define IRQ_TWI1                    GIC_SRC_SPI(2)  /* 34 */
#define IRQ_TWI2                    GIC_SRC_SPI(2)  /* 34 */
#define IRQ_PAEINT                  GIC_SRC_SPI(3)  /* 35 */
#define IRQ_PBEINT                  GIC_SRC_SPI(3)  /* 35 */
#define IRQ_PGEINT                  GIC_SRC_SPI(3)  /* 35 */
#define IRQ_IIS0                    GIC_SRC_SPI(4)  /* 36 */
#define IRQ_IIS1                    GIC_SRC_SPI(4)  /* 36 */
#define IRQ_CSI                     GIC_SRC_SPI(5)  /* 37 */
#define IRQ_TIMER0                  GIC_SRC_SPI(6)  /* 38 */
#define IRQ_TIMER1                  GIC_SRC_SPI(6)  /* 38 */
#define IRQ_WATCHDOG                GIC_SRC_SPI(6)  /* 38 */
#define IRQ_DMA                     GIC_SRC_SPI(7)  /* 39 */
#define IRQ_LCD0                    GIC_SRC_SPI(8)  /* 40 */
#define IRQ_RTIMER0                 GIC_SRC_SPI(9)  /* 41 */
#define IRQ_RTIMER1                 GIC_SRC_SPI(9)  /* 41 */
#define IRQ_RWATCHDOG               GIC_SRC_SPI(9)  /* 41 */
#define IRQ_MBOX                    GIC_SRC_SPI(9)  /* 41 */
#define IRQ_HSTMR                   GIC_SRC_SPI(10) /* 42 */
#define IRQ_MMC0                    GIC_SRC_SPI(11) /* 43 */
#define IRQ_MMC1                    GIC_SRC_SPI(11) /* 43 */
#define IRQ_MMC2                    GIC_SRC_SPI(11) /* 43 */
#define IRQ_SPI0                    GIC_SRC_SPI(12) /* 44 */
#define IRQ_SPI1                    GIC_SRC_SPI(12) /* 44 */
#define IRQ_NAND                    GIC_SRC_SPI(13) /* 45 */
#define IRQ_RUART                   GIC_SRC_SPI(14) /* 46 */
#define IRQ_RSB                     GIC_SRC_SPI(14) /* 46 */
#define IRQ_RTWI                    GIC_SRC_SPI(14) /* 46 */
#define IRQ_RALARM0                 GIC_SRC_SPI(15) /* 47 */
#define IRQ_RALARM1                 GIC_SRC_SPI(15) /* 47 */
#define IRQ_VE                      GIC_SRC_SPI(16) /* 48 */
#define IRQ_USB_OTG                 GIC_SRC_SPI(17) /* 49 */
#define IRQ_USB_EHCI0               GIC_SRC_SPI(18) /* 50 */
#define IRQ_USB_OHCI0               GIC_SRC_SPI(19) /* 51 */
#define IRQ_GPUGP                   GIC_SRC_SPI(20) /* 52 */
#define IRQ_GPUGPMMU                GIC_SRC_SPI(21) /* 53 */
#define IRQ_GPUPP0                  GIC_SRC_SPI(22) /* 54 */
#define IRQ_GPUPPMMU0               GIC_SRC_SPI(23) /* 55 */
#define IRQ_GPUPMU                  GIC_SRC_SPI(24) /* 56 */
#define IRQ_GPUPP1                  GIC_SRC_SPI(25) /* 57 */
#define IRQ_GPUPPMMU1               GIC_SRC_SPI(26) /* 58 */


#define IRQ_SS			GIC_SRC_SPI(80)		/*	SS			*/
#define IRQ_TS			GIC_SRC_SPI(81)		/*	TS			*/
#define IRQ_GMAC			GIC_SRC_SPI(82)		/*	GMAC		*/
#define IRQ_MP			GIC_SRC_SPI(83)		/*	MP			*/
#define IRQ_CSI0			GIC_SRC_SPI(84)		/*	CSI0		*/
#define IRQ_CSI1			GIC_SRC_SPI(85)		/*	CSI1		*/
#define IRQ_LCD1			GIC_SRC_SPI(87)		/*	LCD1		*/
#define IRQ_HDMI			GIC_SRC_SPI(88)		/*	HDMI		*/
#define IRQ_MIPIDSI		GIC_SRC_SPI(89)		/*	MIPI DSI	*/
#define IRQ_MIPICSI		GIC_SRC_SPI(90)		/*	MIPI CSI	*/
#define IRQ_DRC01		GIC_SRC_SPI(91)		/*	DRC 0/1		*/
#define IRQ_DEU01		GIC_SRC_SPI(92)		/*	DEU	0/1		*/
#define IRQ_DEFE0		GIC_SRC_SPI(93)		/*	DE_FE0		*/
#define IRQ_DEFE1		GIC_SRC_SPI(94)		/*	DE_FE1		*/
#define IRQ_DEBE0		GIC_SRC_SPI(95)		/*	DE_BE0		*/
#define IRQ_DEBE1		GIC_SRC_SPI(96)		/*	DE_BE1		*/
#define	IRQ_GPU			GIC_SRC_SPI (97)		/*	GPU			*/

#define GIC_IRQ_NUM			(IRQ_GPUPPMMU1 + 1)

#endif	//fpga irq mapping

/* processer target */
#define GIC_CPU_TARGET(_n)	(1 << (_n))
#define GIC_CPU_TARGET0		GIC_CPU_TARGET(0)
#define GIC_CPU_TARGET1		GIC_CPU_TARGET(1)
#define GIC_CPU_TARGET2		GIC_CPU_TARGET(2)
#define GIC_CPU_TARGET3		GIC_CPU_TARGET(3)
#define GIC_CPU_TARGET4		GIC_CPU_TARGET(4)
#define GIC_CPU_TARGET5		GIC_CPU_TARGET(5)
#define GIC_CPU_TARGET6		GIC_CPU_TARGET(6)
#define GIC_CPU_TARGET7		GIC_CPU_TARGET(7)
/* trigger mode */
#define GIC_SPI_LEVEL_TRIGGER	(0)	//2b'00
#define GIC_SPI_EDGE_TRIGGER	(2)	//2b'10

typedef void (interrupt_handler_t)(void *);

extern void irq_install_handler (uint32_t irq, interrupt_handler_t handle_irq, void *data);
extern void irq_free_handler(uint32_t irq);
extern int irq_enable(uint32_t irq_no);
extern int irq_disable(uint32_t irq_no);

int arch_interrupt_init (void);

int arch_interrupt_exit (void);

extern void disable_interrupts(void);
extern void enable_interrupts(void);

#endif
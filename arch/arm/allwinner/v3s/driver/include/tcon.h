#ifndef __TCON_H
#define __TCON_H

#include <stdint.h>
#include "memmap.h"


typedef struct {
	uint32_t ctrl;									/* 0x000 */
	uint32_t int0;									/* 0x004 */
	uint32_t int1;									/* 0x008 */
	uint8_t __dummy0[4];							/* 4 byte dummy */
	uint32_t tcon0_frm_ctrl;				/* 0x010 */
	uint32_t tcon0_frm_seed[6];			/* 0x014 */
	uint32_t tcon0_frm_table[4];		/* 0x02c */
	uint8_t __dummy1[4];							/* 4 byte dummy */
	uint32_t tcon0_ctrl;						/* 0x040 */
	uint32_t tcon0_dclk;						/* 0x044 */
	uint32_t tcon0_timing_active;		/* 0x048 */
	uint32_t tcon0_timing_h;				/* 0x04c */
	uint32_t tcon0_timing_v;				/* 0x050 */
	uint32_t tcon0_timing_sync;			/* 0x054 */
	uint32_t tcon0_hv_intf;					/* 0x058 */
	uint8_t __dummy2[4];							/* 4 byte dummy */
	uint32_t tcon0_cpu_intf;				/* 0x060 */
	uint32_t tcon0_cpu_wr_dat;			/* 0x064 */
	uint32_t tcon0_cpu_rd_dat0;			/* 0x068 */
	uint32_t tcon0_cpu_rd_dat1;			/* 0x06c */
	uint8_t __dummy3[24];						/* 24 byte dummy */
	uint32_t tcon0_io_polarity;			/* 0x88 */
	uint32_t tcon0_io_tristate;			/* 0x8c */
	uint8_t __dummy4[104];						/* 107 byte dummy */
	uint32_t tcon_ecc_fifo;					/* 0x0f8 */
	uint32_t tcon_debug;						/* 0x0fc */
	uint32_t tcon_ceu_ctl;					/* 0x100 */
	uint8_t __dummy5[12];						/* 12 byte dummy */
	uint32_t tcon_ceu_coef_mul[11];	/* 0x110 + N * 0x04 */
	uint32_t tcon_ceu_coef_add0;		/* 0x11C + 0 * 0x10 */
	uint8_t __dummy6[15];						/* 15 byte dummy */
	uint32_t tcon_ceu_coef_add1;		/* 0x11C + 0 * 0x10 */
	uint8_t __dummy7[15];						/* 15 byte dummy */
	uint32_t tcon_ceu_coef_add2;		/* 0x11C + 0 * 0x10 */
	uint8_t __dummy8[27];						/* 27 byte dummy */
	uint32_t tcon_ceu_coef_rang[3];	/* 0x140 + N * 0x04 */
	uint8_t __dummy9[23];						/* 23 byte dummy */
	uint32_t tcon0_cpu_tri[4];			/* 0x160 + N * 0x04 */
	uint8_t __dummy10[19];						/* 19 byte dummy */
	uint32_t tcon_cmap_ctl;					/* 0x180 */
	uint8_t __dummy11[15];						/* 15 byte dummy */
	uint32_t tcon_cmap_odd[2];			/* 0x190 + N * 0x04 */
	uint32_t tcon_cmap_even[2];			/* 0x198 + N * 0x04 */
	uint8_t __dummy12[83];						/* 83 byte dummy */
	uint32_t tcon_safe_period;			/* 0x1F0 */
	uint8_t __dummy13[527];						/* 527 byte dummy */
	uint32_t tcon0_gamma_table[256];/* 0x400 - 0x7FF */
	uint8_t __dummy14[2038];					/* 2038 byte dummy */
	uint32_t tcon_tri_fifo_bist;		/* 0xFF8 */
	uint32_t tcon_ecc_fifo_bist;		/* 0xFFC */
} TCON_TypeDef;

typedef struct {
	int pixel_clock_hz;
	int h_front_porch;
	int h_back_porch;
	int h_sync_len;
	int v_front_porch;
	int v_back_porch;
	int v_sync_len;
	int h_sync_active;
	int v_sync_active;
	int den_active;
	int clk_active;
} TCON_Timing_TypeDef;


void TCON_Enable();
void TCON_Disable();
void TCON_set_mode(uint16_t width, uint16_t height, uint8_t bits_per_pixel, TCON_Timing_TypeDef timing);


#endif
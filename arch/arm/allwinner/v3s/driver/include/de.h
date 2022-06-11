/**
	******************************************************************************
	* @file de.h
	*
	* @brief DE header for V3s
	*
	*
	* @author Tieu Tuan Bao
	* Contact: tieutuanbao@gmail.com
	* P-Number: +84979755670
	******************************************************************************
	*/

#ifndef __DE_H
#define __DE_H

#include "memmap.h"
#include <stdint.h>

#define DE_DISP_SYS									DE_BASE
#define DE_RTW											(DE_BASE + 0x00010000)
#define DE_RTM0											(DE_BASE + 0x00100000)

#define DE_DISP_SYS_SCLK_GATE				(DE_DISP_SYS)
#define DE_DISP_SYS_HCLK_GATE				(DE_DISP_SYS + 0x004)
#define DE_DISP_SYS_AHB_RESET				(DE_DISP_SYS + 0x008)
#define DE_DISP_SYS_SCLK_DIV				(DE_DISP_SYS + 0x00C)
#define DE_DISP_SYS_D2TCON_MUX			(DE_DISP_SYS + 0x010)

#define DE_RTM0_GLB									(DE_RTM0 + 0x00000)
#define DE_RTM0_BLD									(DE_RTM0 + 0x01000)
#define DE_RTM0_CHAN								(DE_RTM0 + 0x02000)
#define DE_RTM0_VSU									(DE_RTM0 + 0x20000)
#define DE_RTM0_GSU1								(DE_RTM0 + 0x30000)
#define DE_RTM0_GSU2								(DE_RTM0 + 0x40000)
#define DE_RTM0_GSU3								(DE_RTM0 + 0x50000)
#define DE_RTM0_FCE									(DE_RTM0 + 0xa0000)
#define DE_RTM0_BWS									(DE_RTM0 + 0xa2000)
#define DE_RTM0_LTI									(DE_RTM0 + 0xa4000)
#define DE_RTM0_PEAK								(DE_RTM0 + 0xa6000)
#define DE_RTM0_ASE									(DE_RTM0 + 0xa8000)
#define DE_RTM0_FCC									(DE_RTM0 + 0xaa000)
#define DE_RTM0_DCSC								(DE_RTM0 + 0xb0000)

typedef struct{
	uint32_t ctl;
	uint32_t status;
	uint32_t dbuff;
	uint32_t size;
} DE_GLB_TypeDef;

typedef struct{
	uint32_t fcolor_ctl;
	struct{
		uint32_t fcolor;
		uint32_t insize;
		uint32_t offset;
		uint32_t dum;
	} attr[4];
	uint32_t dum0[15];
	uint32_t route;
	uint32_t premultiply;
	uint32_t bkcolor;
	uint32_t output_size;
	uint32_t bld_mode[4];
	uint32_t dum1[4];
	uint32_t ck_ctl;
	uint32_t ck_cfg;
	uint32_t dum2[2];
	uint32_t ck_max[4];
	uint32_t dum3[4];
	uint32_t ck_min[4];
	uint32_t dum4[3];
	uint32_t out_ctl;
} DE_BLD_TypeDef;

typedef struct{
	struct {
		uint32_t attr;
		uint32_t size;
		uint32_t coord;
		uint32_t pitch[3];
		uint32_t top_laddr[3];
		uint32_t bot_laddr[3];
	} cfg[4];
	uint32_t fcolor[4];
	uint32_t top_haddr[3];
	uint32_t bot_haddr[3];
	uint32_t ovl_size[2];
	uint32_t hori[2];
	uint32_t vert[2];
} DE_V_TypeDef;

typedef struct {
	struct {
		uint32_t attr;
		uint32_t size;
		uint32_t coord;
		uint32_t pitch;
		uint32_t top_laddr;
		uint32_t bot_laddr;
		uint32_t fcolor;
		uint32_t dum;
	} cfg[4];
	uint32_t top_haddr;
	uint32_t bot_haddr;
	uint32_t ovl_size;
} DE_UI_TypeDef;



void DE_Enable();
void DE_Set_Address();
void DE_set_mode(uint32_t width, uint32_t height);

#endif
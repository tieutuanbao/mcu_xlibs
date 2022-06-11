/**
	******************************************************************************
	* @file de.c
	*
	* @brief DE Config for V3s
	*
	*
	* @author Tieu Tuan Bao
	* Contact: tieutuanbao@gmail.com
	* P-Number: +84979755670
	******************************************************************************
	*/

#include "de.h"
#include "io.h"
#include <stdlib.h>
#include <string.h>

/* Place following data in section MY_DATA */
//#pragma default_variable_attributes = @ "MY_DATA"
uint8_t vrambuf[800*480*4];
/* Stop placing data in section MY_DATA */
//#pragma default_variable_attributes =

uint8_t *vram = vrambuf;

void DE_set_mode(uint32_t width, uint32_t height){
	uint32_t temp = 0;
	uint32_t size = (((height - 1) << 16) | (width - 1));
	uint32_t pixlen = (width * height * 4);
	DE_GLB_TypeDef * glb = (DE_GLB_TypeDef *)(DE_RTM0_GLB);
	DE_BLD_TypeDef * bld = (DE_BLD_TypeDef *)(DE_RTM0_BLD);
	
	if(vram == 0){
		vram = (uint8_t *)malloc(pixlen);
	}
//else if(sizeof(vram) < pixlen){
//		vram = (uint8_t *)realloc(vram, pixlen);
//	}

	/* set Reset off */
	temp = read32(DE_DISP_SYS_AHB_RESET);
	temp |= 1 << 0;
	write32(DE_DISP_SYS_AHB_RESET, temp);

	/* set Clock pass */
	temp = read32(DE_DISP_SYS_SCLK_GATE);
	temp |= 1 << 0;
	write32(DE_DISP_SYS_SCLK_GATE, temp);

	/* set Clock pass */
	temp = read32(DE_DISP_SYS_HCLK_GATE);
	temp |= 1 << 0;
	write32(DE_DISP_SYS_HCLK_GATE, temp);
	
	/* Mixer0 => TCON0 */
	temp = read32(DE_DISP_SYS_D2TCON_MUX);
	temp &= ~(1 << 0);
	write32(DE_DISP_SYS_D2TCON_MUX, temp);

	write32(&glb->ctl, (1 << 0));
	write32(&glb->status, 0);
	write32(&glb->dbuff, 1);
	write32(&glb->size, size);

	for(uint8_t i = 0; i < 4; i++)
	{
		void * chan = (void *)(DE_RTM0_CHAN + 0x1000 * i);
		memset(chan, 0, i == 0 ? sizeof(DE_V_TypeDef) : sizeof(DE_UI_TypeDef));
	}

	write32(&bld->fcolor_ctl, 0x00000101);
	write32(&bld->route, 2);
	write32(&bld->premultiply, 0);
	write32(&bld->bkcolor, 0xff000000);
	write32(&bld->bld_mode[0], 0x03010301);
	write32(&bld->bld_mode[1], 0x03010301);
	write32(&bld->output_size, size);
	write32(&bld->out_ctl, 0);
	write32(&bld->ck_ctl, 0);
	for(uint8_t i = 0; i < 4; i++)
	{
		write32(&bld->attr[i].fcolor, 0xff000000);
		write32(&bld->attr[i].insize, size);
	}

	write32(DE_RTM0_VSU, 0);
	write32(DE_RTM0_GSU1, 0);
	write32(DE_RTM0_GSU2, 0);
	write32(DE_RTM0_GSU3, 0);
	write32(DE_RTM0_FCE, 0);
	write32(DE_RTM0_BWS, 0);
	write32(DE_RTM0_LTI, 0);
	write32(DE_RTM0_PEAK, 0);
	write32(DE_RTM0_ASE, 0);
	write32(DE_RTM0_FCC, 0);
	write32(DE_RTM0_DCSC, 0);

	write32((uint32_t)&(((DE_UI_TypeDef *)(DE_RTM0_CHAN + 0x1000 * 2))->cfg[0].attr), (1 << 0) | (4 << 8) | (1 << 1) | (0xff << 24));
	write32((uint32_t)&(((DE_UI_TypeDef *)(DE_RTM0_CHAN + 0x1000 * 2))->cfg[0].size), size);
	write32((uint32_t)&(((DE_UI_TypeDef *)(DE_RTM0_CHAN + 0x1000 * 2))->cfg[0].coord), 0);
	write32((uint32_t)&(((DE_UI_TypeDef *)(DE_RTM0_CHAN + 0x1000 * 2))->cfg[0].pitch), 4 * width);
	write32((uint32_t)&(((DE_UI_TypeDef *)(DE_RTM0_CHAN + 0x1000 * 2))->cfg[0].top_laddr), (uint32_t)vram);
	write32((uint32_t)&(((DE_UI_TypeDef *)(DE_RTM0_CHAN + 0x1000 * 2))->ovl_size), size);
}

void DE_Enable(){	
	DE_GLB_TypeDef * glb = (DE_GLB_TypeDef *)(DE_RTM0_GLB);
	write32((uint32_t)&glb->dbuff, 1);
}

void DE_Set_Address()
{
	DE_UI_TypeDef * ui = (DE_UI_TypeDef *)(DE_RTM0_CHAN + 0x1000 * 2);
	write32((uint32_t)&ui->cfg[0].top_laddr, (uint32_t)vram);
}
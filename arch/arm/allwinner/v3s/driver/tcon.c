#include "tcon.h"
#include "clock.h"
#include "io.h"

void TCON_Disable(){
	TCON_TypeDef * tcon = (TCON_TypeDef *)TCON_BASE;
	uint32_t temp;

	write32((uint32_t)&tcon->ctrl, 0);
	write32((uint32_t)&tcon->int0, 0);

	temp = read32((uint32_t)&tcon->tcon0_dclk);
	temp &= ~(0xf << 28);
	write32((uint32_t)&tcon->tcon0_dclk, temp);

	write32((uint32_t)&tcon->tcon0_io_tristate, 0xffffffff);
}

void TCON_set_mode(uint16_t width, uint16_t height, uint8_t bits_per_pixel, TCON_Timing_TypeDef timing)
{
	TCON_TypeDef * tcon = (TCON_TypeDef *)TCON_BASE;
	int bp, total;
	uint32_t val;

	val = read32((uint32_t)&tcon->ctrl);
	val &= ~(0x1 << 0);
	write32((uint32_t)&tcon->ctrl, val);

	val = (timing.v_front_porch + timing.v_back_porch + timing.v_sync_len) / 2;
	write32((uint32_t)&tcon->tcon0_ctrl, (1U << 31) | ((val & 0x1f) << 4));
	val = PLL_Get_Clock(PLL_VIDEO) / timing.pixel_clock_hz;
	write32((uint32_t)&tcon->tcon0_dclk, (0xfU << 28) | ((val / 2) << 0));
	write32((uint32_t)&tcon->tcon0_timing_active, ((width - 1) << 16) | ((height - 1) << 0));

	bp = timing.h_sync_len + timing.h_back_porch;
	total = width + timing.h_front_porch + bp;
	write32((uint32_t)&tcon->tcon0_timing_h, ((total - 1) << 16) | ((bp - 1) << 0));
	bp = timing.v_sync_len + timing.v_back_porch;
	total = height + timing.v_front_porch + bp;
	write32((uint32_t)&tcon->tcon0_timing_v, ((total * 2) << 16) | ((bp - 1) << 0));
	write32((uint32_t)&tcon->tcon0_timing_sync, ((timing.h_sync_len - 1) << 16) | ((timing.v_sync_len - 1) << 0));

	write32((uint32_t)&tcon->tcon0_hv_intf, 0);
	write32((uint32_t)&tcon->tcon0_cpu_intf, 0);

	if(bits_per_pixel == 18 || bits_per_pixel == 16)
	{
		write32((uint32_t)&tcon->tcon0_frm_seed[0], 0x11111111);
		write32((uint32_t)&tcon->tcon0_frm_seed[1], 0x11111111);
		write32((uint32_t)&tcon->tcon0_frm_seed[2], 0x11111111);
		write32((uint32_t)&tcon->tcon0_frm_seed[3], 0x11111111);
		write32((uint32_t)&tcon->tcon0_frm_seed[4], 0x11111111);
		write32((uint32_t)&tcon->tcon0_frm_seed[5], 0x11111111);
		write32((uint32_t)&tcon->tcon0_frm_table[0], 0x01010000);
		write32((uint32_t)&tcon->tcon0_frm_table[1], 0x15151111);
		write32((uint32_t)&tcon->tcon0_frm_table[2], 0x57575555);
		write32((uint32_t)&tcon->tcon0_frm_table[3], 0x7f7f7777);
		write32((uint32_t)&tcon->tcon0_frm_ctrl, (bits_per_pixel == 18) ? ((1 << 31) | (0 << 4)) : ((1 << 31) | (5 << 4)));
	}

	val = (1 << 28);
	if(!timing.h_sync_active){
		val |= (1 << 25);
	}
	if(!timing.v_sync_active){
		val |= (1 << 24);
	}
	if(!timing.den_active){
		val |= (1 << 27);
	}
	if(!timing.clk_active){
		val |= (1 << 26);
	}
	write32((uint32_t)&tcon->tcon0_io_polarity, val);
	write32((uint32_t)&tcon->tcon0_io_tristate, 0);
}

void TCON_Enable()
{
	TCON_TypeDef * tcon = (TCON_TypeDef *)TCON_BASE;
	uint32_t val;

	val = read32((uint32_t)&tcon->ctrl);
	val |= (1U << 31);
	write32((uint32_t)&tcon->ctrl, val);
}

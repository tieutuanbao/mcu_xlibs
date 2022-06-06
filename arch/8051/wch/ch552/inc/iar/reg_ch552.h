#ifndef __REG_CH552_H
#define __REG_CH552_H

__sfr __no_init volatile union{
	unsigned char P1;
	struct{
		unsigned char BIT0 : 1;
		unsigned char BIT1 : 1;
		unsigned char BIT2 : 1;
		unsigned char BIT3 : 1;
		unsigned char BIT4 : 1;
		unsigned char BIT5 : 1;
		unsigned char BIT6 : 1;
		unsigned char BIT7 : 1;
	} P1_bit;
} @ 0x90;

__sfr __no_init volatile union{
	unsigned char P1_MOD_OC;
	struct{
		unsigned char BIT0 : 1;
		unsigned char BIT1 : 1;
		unsigned char BIT2 : 1;
		unsigned char BIT3 : 1;
		unsigned char BIT4 : 1;
		unsigned char BIT5 : 1;
		unsigned char BIT6 : 1;
		unsigned char BIT7 : 1;
	} P1_MOD_OC_bit;
} @ 0x92;

__sfr __no_init volatile union{
	unsigned char P1_DIR_PU;
	struct{
		unsigned char BIT0 : 1;
		unsigned char BIT1 : 1;
		unsigned char BIT2 : 1;
		unsigned char BIT3 : 1;
		unsigned char BIT4 : 1;
		unsigned char BIT5 : 1;
		unsigned char BIT6 : 1;
		unsigned char BIT7 : 1;
	} P1_DIR_PU_bit;
} @ 0x93;

#endif
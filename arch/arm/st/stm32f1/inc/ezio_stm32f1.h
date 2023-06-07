#ifndef __BITBANDING_STM32_H
#define __BITBANDING_STM32_H

/************************************* BIT BANDING Calculation ****************************************/
#define BITBANDING(addr, bitnum) ((addr & 0xF0000000)+0x2000000+(addr*32)+(bitnum*4))

/************************************* IO Ofset Address ****************************************/
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08

/************************************* IO Macro ****************************************/
#define PORT_A(n)          *((volatile unsigned long  *)(BITBANDING(GPIOA_ODR_Addr,n)))  //
#define PIN_A(n)           *((volatile unsigned long  *)(BITBANDING(GPIOA_IDR_Addr,n)))  //

#define PORT_B(n)          *((volatile unsigned long  *)(BITBANDING(GPIOB_ODR_Addr,n)))  //
#define PIN_B(n)           *((volatile unsigned long  *)(BITBANDING(GPIOB_IDR_Addr,n)))  //

#define PORT_C(n)          *((volatile unsigned long  *)(BITBANDING(GPIOC_ODR_Addr,n)))  //
#define PIN_C(n)           *((volatile unsigned long  *)(BITBANDING(GPIOC_IDR_Addr,n)))  //

#define PORT_D(n)          *((volatile unsigned long  *)(BITBANDING(GPIOD_ODR_Addr,n)))  //
#define PIN_D(n)           *((volatile unsigned long  *)(BITBANDING(GPIOD_IDR_Addr,n)))  //

#define PORT_E(n)          *((volatile unsigned long  *)(BITBANDING(GPIOE_ODR_Addr,n)))  //
#define PIN_E(n)           *((volatile unsigned long  *)(BITBANDING(GPIOE_IDR_Addr,n)))  //

#define PORT_F(n)          *((volatile unsigned long  *)(BITBANDING(GPIOF_ODR_Addr,n)))  //
#define PIN_F(n)           *((volatile unsigned long  *)(BITBANDING(GPIOF_IDR_Addr,n)))  //

#define PORT_G(n)          *((volatile unsigned long  *)(BITBANDING(GPIOG_ODR_Addr,n)))  //
#define PIN_G(n)           *((volatile unsigned long  *)(BITBANDING(GPIOG_IDR_Addr,n)))  //
/***************************************************************/
/***************** I/O A *************************/
#define PORTA       GPIOA->ODR
#define PORTA_0     PORT_A(0)
#define PORTA_1     PORT_A(1)
#define PORTA_2     PORT_A(2)
#define PORTA_3     PORT_A(3)
#define PORTA_4     PORT_A(4)
#define PORTA_5     PORT_A(5)
#define PORTA_6     PORT_A(6)
#define PORTA_7     PORT_A(7)
#define PORTA_8     PORT_A(8)
#define PORTA_9     PORT_A(9)
#define PORTA_10    PORT_A(10)
#define PORTA_11    PORT_A(11)
#define PORTA_12    PORT_A(12)
#define PORTA_13    PORT_A(13)
#define PORTA_14    PORT_A(14)
#define PORTA_15    PORT_A(15)
#define PINA        GPIOA->IDR
#define PINA_0      PIN_A(0)
#define PINA_1      PIN_A(1)
#define PINA_2      PIN_A(2)
#define PINA_3      PIN_A(3)
#define PINA_4      PIN_A(4)
#define PINA_5      PIN_A(5)
#define PINA_6      PIN_A(6)
#define PINA_7      PIN_A(7)
#define PINA_8      PIN_A(8)
#define PINA_9      PIN_A(9)
#define PINA_10     PIN_A(10)
#define PINA_11     PIN_A(11)
#define PINA_12     PIN_A(12)
#define PINA_13     PIN_A(13)
#define PINA_14     PIN_A(14)
#define PINA_15     PIN_A(15)
/***************** I/O B *************************/
#define PORTB       GPIOB->ODR
#define PORTB_0     PORT_B(0)
#define PORTB_1     PORT_B(1)
#define PORTB_2     PORT_B(2)
#define PORTB_3     PORT_B(3)
#define PORTB_4     PORT_B(4)
#define PORTB_5     PORT_B(5)
#define PORTB_6     PORT_B(6)
#define PORTB_7     PORT_B(7)
#define PORTB_8     PORT_B(8)
#define PORTB_9     PORT_B(9)
#define PORTB_10    PORT_B(10)
#define PORTB_11    PORT_B(11)
#define PORTB_12    PORT_B(12)
#define PORTB_13    PORT_B(13)
#define PORTB_14    PORT_B(14)
#define PORTB_15    PORT_B(15)
#define PINB        GPIOB->IDR
#define PINB_0      PIN_B(0)
#define PINB_1      PIN_B(1)
#define PINB_2      PIN_B(2)
#define PINB_3      PIN_B(3)
#define PINB_4      PIN_B(4)
#define PINB_5      PIN_B(5)
#define PINB_6      PIN_B(6)
#define PINB_7      PIN_B(7)
#define PINB_8      PIN_B(8)
#define PINB_9      PIN_B(9)
#define PINB_10     PIN_B(10)
#define PINB_11     PIN_B(11)
#define PINB_12     PIN_B(12)
#define PINB_13     PIN_B(13)
#define PINB_14     PIN_B(14)
#define PINB_15     PIN_B(15)
/***************** I/O C *************************/
#define PORTC       GPIOC->ODR
#define PORTC_0     PORT_C(0)
#define PORTC_1     PORT_C(1)
#define PORTC_2     PORT_C(2)
#define PORTC_3     PORT_C(3)
#define PORTC_4     PORT_C(4)
#define PORTC_5     PORT_C(5)
#define PORTC_6     PORT_C(6)
#define PORTC_7     PORT_C(7)
#define PORTC_8     PORT_C(8)
#define PORTC_9     PORT_C(9)
#define PORTC_10    PORT_C(10)
#define PORTC_11    PORT_C(11)
#define PORTC_12    PORT_C(12)
#define PORTC_13    PORT_C(13)
#define PORTC_14    PORT_C(14)
#define PORTC_15    PORT_C(15)
#define PINC        GPIOC->IDR
#define PINC_0      PIN_C(0)
#define PINC_1      PIN_C(1)
#define PINC_2      PIN_C(2)
#define PINC_3      PIN_C(3)
#define PINC_4      PIN_C(4)
#define PINC_5      PIN_C(5)
#define PINC_6      PIN_C(6)
#define PINC_7      PIN_C(7)
#define PINC_8      PIN_C(8)
#define PINC_9      PIN_C(9)
#define PINC_10     PIN_C(10)
#define PINC_11     PIN_C(11)
#define PINC_12     PIN_C(12)
#define PINC_13     PIN_C(13)
#define PINC_14     PIN_C(14)
#define PINC_15     PIN_C(15)
/***************** I/O D *************************/
#define PORTD       GPIOC->ODR
#define PORTD_0     PORT_D(0)
#define PORTD_1     PORT_D(1)
#define PORTD_2     PORT_D(2)
#define PORTD_3     PORT_D(3)
#define PORTD_4     PORT_D(4)
#define PORTD_5     PORT_D(5)
#define PORTD_6     PORT_D(6)
#define PORTD_7     PORT_D(7)
#define PORTD_8     PORT_D(8)
#define PORTD_9     PORT_D(9)
#define PORTD_10    PORT_D(10)
#define PORTD_11    PORT_D(11)
#define PORTD_12    PORT_D(12)
#define PORTD_13    PORT_D(13)
#define PORTD_14    PORT_D(14)
#define PORTD_15    PORT_D(15)
#define PIND        GPIOD->IDR
#define PIND_0      PIN_D(0)
#define PIND_1      PIN_D(1)
#define PIND_2      PIN_D(2)
#define PIND_3      PIN_D(3)
#define PIND_4      PIN_D(4)
#define PIND_5      PIN_D(5)
#define PIND_6      PIN_D(6)
#define PIND_7      PIN_D(7)
#define PIND_8      PIN_D(8)
#define PIND_9      PIN_D(9)
#define PIND_10     PIN_D(10)
#define PIND_11     PIN_D(11)
#define PIND_12     PIN_D(12)
#define PIND_13     PIN_D(13)
#define PIND_14     PIN_D(14)
#define PIND_15     PIN_D(15)
/***************** I/O E *************************/
#define PORTE       GPIOE->ODR
#define PORTE_0     PORT_E(0)
#define PORTE_1     PORT_E(1)
#define PORTE_2     PORT_E(2)
#define PORTE_3     PORT_E(3)
#define PORTE_4     PORT_E(4)
#define PORTE_5     PORT_E(5)
#define PORTE_6     PORT_E(6)
#define PORTE_7     PORT_E(7)
#define PORTE_8     PORT_E(8)
#define PORTE_9     PORT_E(9)
#define PORTE_10    PORT_E(10)
#define PORTE_11    PORT_E(11)
#define PORTE_12    PORT_E(12)
#define PORTE_13    PORT_E(13)
#define PORTE_14    PORT_E(14)
#define PORTE_15    PORT_E(15)
#define PINE        GPIOE->IDR
#define PINE_0      PIN_E(0)
#define PINE_1      PIN_E(1)
#define PINE_2      PIN_E(2)
#define PINE_3      PIN_E(3)
#define PINE_4      PIN_E(4)
#define PINE_5      PIN_E(5)
#define PINE_6      PIN_E(6)
#define PINE_7      PIN_E(7)
#define PINE_8      PIN_E(8)
#define PINE_9      PIN_E(9)
#define PINE_10     PIN_E(10)
#define PINE_11     PIN_E(11)
#define PINE_12     PIN_E(12)
#define PINE_13     PIN_E(13)
#define PINE_14     PIN_E(14)
#define PINE_15     PIN_E(15)
/***************** I/O F *************************/
#define PORTF       GPIOF->ODR
#define PORTF_0     PORT_F(0)
#define PORTF_1     PORT_F(1)
#define PORTF_2     PORT_F(2)
#define PORTF_3     PORT_F(3)
#define PORTF_4     PORT_F(4)
#define PORTF_5     PORT_F(5)
#define PORTF_6     PORT_F(6)
#define PORTF_7     PORT_F(7)
#define PORTF_8     PORT_F(8)
#define PORTF_9     PORT_F(9)
#define PORTF_10    PORT_F(10)
#define PORTF_11    PORT_F(11)
#define PORTF_12    PORT_F(12)
#define PORTF_13    PORT_F(13)
#define PORTF_14    PORT_F(14)
#define PORTF_15    PORT_F(15)
#define PINF        GPIOF->IDR
#define PINF_0      PIN_F(0)
#define PINF_1      PIN_F(1)
#define PINF_2      PIN_F(2)
#define PINF_3      PIN_F(3)
#define PINF_4      PIN_F(4)
#define PINF_5      PIN_F(5)
#define PINF_6      PIN_F(6)
#define PINF_7      PIN_F(7)
#define PINF_8      PIN_F(8)
#define PINF_9      PIN_F(9)
#define PINF_10     PIN_F(10)
#define PINF_11     PIN_F(11)
#define PINF_12     PIN_F(12)
#define PINF_13     PIN_F(13)
#define PINF_14     PIN_F(14)
#define PINF_15     PIN_F(15)
/***************** I/O G *************************/
#define PORTG       GPIOG->ODR
#define PORTG_0     PORT_G(0)
#define PORTG_1     PORT_G(1)
#define PORTG_2     PORT_G(2)
#define PORTG_3     PORT_G(3)
#define PORTG_4     PORT_G(4)
#define PORTG_5     PORT_G(5)
#define PORTG_6     PORT_G(6)
#define PORTG_7     PORT_G(7)
#define PORTG_8     PORT_G(8)
#define PORTG_9     PORT_G(9)
#define PORTG_10    PORT_G(10)
#define PORTG_11    PORT_G(11)
#define PORTG_12    PORT_G(12)
#define PORTG_13    PORT_G(13)
#define PORTG_14    PORT_G(14)
#define PORTG_15    PORT_G(15)
#define PING        GPIOG->IDR
#define PING_0      PIN_G(0)
#define PING_1      PIN_G(1)
#define PING_2      PIN_G(2)
#define PING_3      PIN_G(3)
#define PING_4      PIN_G(4)
#define PING_5      PIN_G(5)
#define PING_6      PIN_G(6)
#define PING_7      PIN_G(7)
#define PING_8      PIN_G(8)
#define PING_9      PIN_G(9)
#define PING_10     PIN_G(10)
#define PING_11     PIN_G(11)
#define PING_12     PIN_G(12)
#define PING_13     PIN_G(13)
#define PING_14     PIN_G(14)
#define PING_15     PIN_G(15)
#endif

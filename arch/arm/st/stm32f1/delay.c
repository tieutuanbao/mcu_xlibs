#include "delay.h"

static unsigned char  fac_us=0;
static unsigned int fac_ms=0;

void delay_init(uint8_t SYSCLK)
{
    SysTick->CTRL&=0xFFFFFFFC;
    fac_us=SYSCLK;
    fac_ms=(unsigned int)fac_us*1000;
}
void __delay_ms(uint32_t _ms)
{
    unsigned long temp;
    SysTick->LOAD=(unsigned long)_ms*fac_ms;
    SysTick->VAL =0x00;
    SysTick->CTRL=0x05 ;
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));
    SysTick->CTRL=0x00;
    SysTick->VAL =0X00;
}
void delay_ms(uint32_t _ms)
{
    unsigned int i;
    for(i=_ms;i>0;i--)
    {
        __delay_ms(1);
    }
}
void delay_us(uint32_t _nus)
{
    unsigned long temp;
    SysTick->LOAD=_nus*fac_us;
    SysTick->VAL=0x00;
    SysTick->CTRL=0x05 ;
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));
    SysTick->CTRL=0x00;
    SysTick->VAL =0X00;
}

void delay_250ns(uint32_t _ns) {
    unsigned long temp;
    unsigned int i;
    for(i=0;i<_ns;i++) {
        SysTick->LOAD=1;
        SysTick->VAL=0x00;
        SysTick->CTRL=0x05;
        do
        {
            temp=SysTick->CTRL;
        }
        while(temp&0x01&&!(temp&(1<<16)));
        SysTick->CTRL=0x00;
        SysTick->VAL =0X00;
    }
}

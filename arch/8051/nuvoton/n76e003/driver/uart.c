#include "User_UART.h"
#include "Function_Define.h"
#include "SFR_Macro.h"
#include "string.h"

UART_Structure UART0;
UART_Structure UART1;

//----------------------------------------------------------------------------------
// UART0 baud rate initial setting
//----------------------------------------------------------------------------------
void InitialUART0_Timer1(unsigned long u32Baudrate)    //T1M = 1, SMOD = 1
{
    SCON = 0x50;         //UART0 Mode1,REN=1,TI=1
    TMOD |= 0x20;        //Timer1 Mode1

    set_SMOD;            //UART0 Double Rate Enable
    set_T1M;
    clr_BRCK;            //Serial port 0 baud rate clock source = Timer1

    TH1 = 256 - (1000000/u32Baudrate+1);               /*16 MHz */

    set_TR1;
    set_TI;                        //For printf function must setting TI = 1

    set_ES;                //Enable Serial Port 0 Interrupt

    memset(UART0.Data_Buffer,0,UART_BUFFER_SIZE);
    UART0.Char_Counter=0;
}
//---------------------------------------------------------------
void InitialUART0_Timer3(unsigned long u32Baudrate) //use timer3 as Baudrate generator
{
    SCON = 0x50;        //UART0 Mode1,REN=1,TI=1
    set_SMOD;            //UART0 Double Rate Enable
    T3CON &= 0xF8;       //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
    set_BRCK;            //UART0 baud rate clock source = Timer3

    RH3    = HIBYTE(65536 - (1000000/u32Baudrate)-1);          /*16 MHz */
    RL3    = LOBYTE(65536 - (1000000/u32Baudrate)-1);            /*16 MHz */

    set_TR3;            //Trigger Timer3
    set_TI;            //For printf function must setting TI = 1

    set_ES;                //Enable Serial Port 0 Interrupt

    memset(UART0.Data_Buffer,0,UART_BUFFER_SIZE);
    UART0.Char_Counter=0;
}

void UART0_Send_Char(uint8_t c)
{
    UART0.Tx_Cmplt=0;
    SBUF = c;
    while(UART0.Tx_Cmplt==0);
}

void UART0_Send_String(uint8_t *str, uint16_t length) {
    while(length--) {
        TI = 0;
        UART0.Tx_Cmplt=0;
        SBUF = *str;
        str++;
        while(UART0.Tx_Cmplt==0);
    }
}

//----------------------------------------------------------------------------------
// UART1 baud rate initial setting
//----------------------------------------------------------------------------------
void InitialUART1_Timer3(unsigned long u32Baudrate) //use timer3 as Baudrate generator
{
    SCON_1 = 0x50;       //UART1 Mode1,REN_1=1,TI_1=1
    T3CON = 0x08;       //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1
    clr_BRCK;

    RH3    = HIBYTE(65536 - (1000000/u32Baudrate)-1);          /*16 MHz */
    RL3    = LOBYTE(65536 - (1000000/u32Baudrate)-1);            /*16 MHz */

    set_TR3;            //Trigger Timer3
    set_TI;                //For printf function must setting TI = 1

    set_ES_1;            //Enable Serial Port 1 Interrupt

    memset(UART1.Data_Buffer,0,UART_BUFFER_SIZE);
    UART1.Char_Counter=0;
}

void UART1_Send_Char(uint8_t c)
{
    UART1.Tx_Cmplt=0;
    SBUF_1 = c;
    while(UART1.Tx_Cmplt==0);
}

void UART1_Send_String(unsigned char *str) {
    while(*str) {
        TI_1 = 0;
        UART1.Tx_Cmplt=0;
        SBUF_1 = *str;
        str++;
        while(UART1.Tx_Cmplt==0);
    }
}

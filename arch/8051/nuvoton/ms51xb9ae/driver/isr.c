//***********************************************************************************************************
//  File Function: MS51 interrupt vector
//***********************************************************************************************************
#include "MS51_16K_IAR.h"


/*all interrupt subroutine list */
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x03
__interrupt void INT0_ISR(void) {
    _push_(SFRS);

    clr_TCON_IE0;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x0B
__interrupt void Timer0_ISR(void) {
    _push_(SFRS);

    clr_TCON_TF0;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x13
__interrupt void INT1_ISR(void) {
    _push_(SFRS);

    clr_TCON_IE1;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x1B
__interrupt void Timer1_ISR(void) {
    _push_(SFRS);

    clr_TCON_TF1;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x23
__interrupt void UART0_ISR(void) {
    _push_(SFRS);

    clr_SCON_RI;
    clr_SCON_TI;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x2B
__interrupt void Timer2_ISR(void) {
    _push_(SFRS);

    clr_T2CON_TF2;

    _pop_(SFRS);
}

//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x3B
__interrupt void Pin_INT_ISR(void) {
    _push_(SFRS);

    PIF = 0;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x43
__interrupt void BOD_ISR(void) {
    _push_(SFRS);

    clr_BODCON0_BOF;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x4B
__interrupt void SPI_ISR(void) {
    _push_(SFRS);

    clr_BODCON0_BOF;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x53
__interrupt void WDT_ISR (void) {
    _push_(SFRS);

    clr_WDCON_WDTF;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x5B
__interrupt void ADC_ISR (void) {
    _push_(SFRS);

    clr_ADCCON0_ADCF;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x63
__interrupt void Capture_ISR (void) {
    _push_(SFRS);

    clr_CAPCON0_CAPF0;
    clr_CAPCON0_CAPF1;
    clr_CAPCON0_CAPF2;
}
#pragma vector=0x6B
__interrupt void PWM_ISR (void) {
    _push_(SFRS);



    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x73
__interrupt void PWM_Brake_ISR(void) {
    _push_(SFRS);

    clr_FBD_FBF;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------

#pragma vector=0x83
__interrupt void Timer3_ISR(void) {
    _push_(SFRS);

    clr_T3CON_TF3;

    _pop_(SFRS);
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x8B
__interrupt void WKT_ISR(void) {
    _push_(SFRS);

    clr_WKCON_WKTF;

    _pop_(SFRS);
}

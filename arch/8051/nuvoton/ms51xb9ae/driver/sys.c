#include "sys.h"
#include "reg_ms51.h"
unsigned char BIT_TMP;

void clock_hirc_16_config(void) {
    unsigned char hircmap0, hircmap1;
    set_CHPCON_IAPEN;
    IAPAL = 0x30;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    set_IAPTRG_IAPGO;
    hircmap0 = IAPFD;
    IAPAL = 0x31;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    hircmap1 = IAPFD;
    clr_CHPCON_IAPEN;
    TA = 0XAA;
    TA = 0X55;
    RCTRIM0 = hircmap0;
    TA = 0XAA;
    TA = 0X55;
    RCTRIM1 = hircmap1;
}

void clock_hirc_24_config(void) {
    unsigned char hircmap0, hircmap1;
    /* Check if power on reset, modify HIRC */
    if (PCON & SET_BIT4)
    {
        set_CHPCON_IAPEN;
        IAPAL = 0x38;
        IAPAH = 0x00;
        IAPCN = READ_UID;
        set_IAPTRG_IAPGO;
        hircmap0 = IAPFD;
        IAPAL = 0x39;
        IAPAH = 0x00;
        set_IAPTRG_IAPGO;
        hircmap1 = IAPFD;
        clr_CHPCON_IAPEN;
        TA = 0XAA;
        TA = 0X55;
        RCTRIM0 = hircmap0;
        TA = 0XAA;
        TA = 0X55;
        RCTRIM1 = hircmap1;
        clr_CHPCON_IAPEN;
    }
}

/****************************************************************************/
/* If call this macro, Please Modify option -> Preproceessing Symbols*********/
/* -> Define "FOSC_160000" to "FOSC_166000"**********************************/
/****************************************************************************/
/*==========================================================================*/
void clock_hirc_166_config(void) {
    unsigned char hircmap0, hircmap1;
    unsigned int trimvalue16bit;
    /* Check if power on reset, modify HIRC */
    if (PCON & SET_BIT4)
    {
        hircmap0 = RCTRIM0;
        hircmap1 = RCTRIM1;
        trimvalue16bit = ((hircmap0 << 1) + (hircmap1 & 0x01));
        trimvalue16bit = trimvalue16bit - 15;
        hircmap1 = trimvalue16bit & 0x01;
        hircmap0 = trimvalue16bit >> 1;
        TA = 0XAA;
        TA = 0X55;
        RCTRIM0 = hircmap0;
        TA = 0XAA;
        TA = 0X55;
        RCTRIM1 = 0X03;
        /* Clear power on flag */
        PCON &= CLR_BIT4;
    }
}

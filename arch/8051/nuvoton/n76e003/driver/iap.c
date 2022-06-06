/**
  ******************************************************************************
  * File Name          : User_IAP.c
  * Description        : File In Application Programming
    * Author                         : Tieu Tuan Bao
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "User_IAP.h"

//***********************************************************************************************************
#define     CID_READ            0x0B
#define     DID_READ            0x0C

/*
    Since the DATAFLASH is in the APROM. Program command is same as program APROM
*/
#define     PAGE_ERASE_AP       0x22
#define     BYTE_READ_AP        0x00
#define     BYTE_PROGRAM_AP     0x21
#define     PAGE_SIZE           128


#define     ERASE_FAIL          0x70
#define     PROGRAM_FAIL        0x71
#define     IAPFF_FAIL          0x72
#define     IAP_PASS            0x00

//-----------------------------------------------------------------------------------------------------------/
void IAP_ERROR_LED(void)
{
//    while (1)
// {
//
//    }
}
//-----------------------------------------------------------------------------------------------------------/
void Trigger_IAP(void)
{
    uint8_t _bitTemp = EA;
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    IAPTRG |= SET_BIT0;
    EA = _bitTemp;

    if((CHPCON & SET_BIT6) == SET_BIT6)             // if fail flag is set, toggle error LED and IAP stop
    {
        _bitTemp = EA;
        EA = 0;
        TA = 0xAA;
        TA = 0x55;
        CHPCON &= ~SET_BIT6;
        EA = _bitTemp;

        IAP_ERROR_LED();
    }
}
/*
        WARNING:
    No matter read or writer, when IAPFF is set 1,
    this step process is fail. DATA should be ignore.
*/
//-----------------------------------------------------------------------------------------------------------/

/*****************************************************************************************************************
Erase APROM subroutine:


******************************************************************************************************************/
void Erase_APROM(uint16_t u16_addr, uint16_t size_data)
{
    uint16_t u16Count;

    // set_IAPEN
    uint8_t _bitTemp = EA;
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON |= SET_BIT0;
    EA = _bitTemp;                                            // Enable IAP function

    IAPFD = 0xFF;                                                // IMPORTANT !! To erase function must setting IAPFD = 0xFF
    IAPCN = PAGE_ERASE_AP;

    // set_APUEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    IAPUEN |= SET_BIT0;
    EA = _bitTemp;                                                    //  APROM modify Enable

    for(u16Count=0x0000;u16Count<size_data/PAGE_SIZE;u16Count++) {
            IAPAL = LOBYTE(u16Count*PAGE_SIZE + u16_addr);
            IAPAH = HIBYTE(u16Count*PAGE_SIZE + u16_addr);
            Trigger_IAP();
    }

    // clr_APUEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    IAPUEN &= ~SET_BIT0;
    EA = _bitTemp;

    // clr_IAPEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON &= ~SET_BIT0;
    EA = _bitTemp;
}

//-----------------------------------------------------------------------------------------------------------
void Erase_APROM_Verify(void)
{
    uint16_t u16Count;

    // set_IAPEN
    uint8_t _bitTemp = EA;
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON |= SET_BIT0;
    EA = _bitTemp;                                            // Enable IAP function

    IAPAL = LOBYTE(DATA_START_ADDR);
    IAPAH = HIBYTE(DATA_START_ADDR);
    IAPCN = BYTE_READ_AP;

    for(u16Count=0;u16Count<DATA_SIZE;u16Count++)
    {
            IAPFD = 0x00;
            Trigger_IAP();
            if(IAPFD != 0xFF)
                IAP_ERROR_LED();
            IAPAL++;
            if(IAPAL == 0x00)
                IAPAH++;
    }

    // clr_IAPEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON &= ~SET_BIT0;
    EA = _bitTemp;
}
//-----------------------------------------------------------------------------------------------------------
void Program_APROM(uint8_t __data *data_poiter, uint16_t u16_addr, uint16_t size_data)
{
    uint16_t u16Count;

    // set_IAPEN
    uint8_t _bitTemp = EA;
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON |= SET_BIT0;
    EA = _bitTemp;                                            // Enable IAP function

    // set_APUEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    IAPUEN |= SET_BIT0;
    EA = _bitTemp;                                                    //  APROM modify Enable

    IAPAL = LOBYTE(u16_addr);
    IAPAH = HIBYTE(u16_addr);
    IAPCN = BYTE_PROGRAM_AP;

    for(u16Count=0;u16Count<size_data;u16Count++)
    {
        IAPFD = *(data_poiter++);
        Trigger_IAP();
        IAPAL++;
        if(IAPAL == 0)
        {
                IAPAH++;
        }
    }

    // clr_APUEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    IAPUEN &= ~SET_BIT0;
    EA = _bitTemp;

    // clr_IAPEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON &= ~SET_BIT0;
    EA = _bitTemp;
}
//
//-----------------------------------------------------------------------------------------------------------
void Read_APROM(uint8_t __data  *data_poiter, uint16_t u16_addr, uint16_t size_data)
{
    uint16_t u16Count;

    // set_IAPEN
    uint8_t _bitTemp = EA;
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON |= SET_BIT0;
    EA = _bitTemp;                                            // Enable IAP function

    IAPAL = LOBYTE(u16_addr);
    IAPAH = HIBYTE(u16_addr);
    IAPCN = BYTE_READ_AP;

    for(u16Count = 0; u16Count < size_data; u16Count++) {
        Trigger_IAP();
        *data_poiter = IAPFD;
        IAPAL++;
        if(IAPAL == 0) {
            IAPAH++;
        }
        data_poiter++;
    }

    // clr_IAPEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON &= ~SET_BIT0;
    EA = _bitTemp;
}
//-----------------------------------------------------------------------------------------------------------
void Program_APROM_Verify(void)
{
    uint16_t u16Count;
    uint8_t  u8Read_Data;

    // set_IAPEN
    uint8_t _bitTemp = EA;
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON |= SET_BIT0;
    EA = _bitTemp;                                            // Enable IAP function

    IAPAL = LOBYTE(DATA_START_ADDR);
    IAPAH = HIBYTE(DATA_START_ADDR);
    IAPCN = BYTE_READ_AP;
    u8Read_Data = 0x00;

    for(u16Count=0;u16Count<DATA_SIZE;u16Count++)
    {
            Trigger_IAP();
            if(IAPFD != u8Read_Data)
                IAP_ERROR_LED();
            IAPAL++;
            if(IAPAL == 0)
            {
                    IAPAH++;
            }
            u8Read_Data ++;
    }

    // clr_IAPEN
    EA = 0;
    TA = 0xAA;
    TA = 0x55;
    CHPCON &= ~SET_BIT0;
    EA = _bitTemp;
}

#include "User_I2C.h"
#include "N76E003.h"
#include "Function_Define.h"
#include "SFR_Macro.h"
#include "User_delay.h"
#include "User_GPIO.h"

unsigned int Timeout_counter=0;

void I2C_Init() {
    DS1307_I2C_GPIO_Init();

     /* Set I2C clock rate */
    I2CLK = 13;
    /* Enable I2C */
    set_I2CEN;
}

unsigned char I2C_Send(unsigned char DevAddress,unsigned char MemAddress,unsigned char *pData, unsigned char Lenght) {
    /* Step1 */
    set_STA;                                    /* Send Start bit to I2C EEPROM */
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x08)                         //Check status value after every step
        return 0;

    /* Step2 */
    clr_STA;                                    //STA=0
    I2DAT = DevAddress;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x18)
        return 0;

    /* Step3 */
    I2DAT = MemAddress;                         //address high for I2C EEPROM
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x28)
        return 0;

    /* Step4 */
    while(Lenght) {
        I2DAT = *pData;                               //address high for I2C EEPROM
        clr_SI;
        while (!SI);                                //Check SI set or not
        if (I2STAT != 0x28)
            return 0;
        pData++;
        Lenght--;
    }

    /* Step5 */
    do {
        set_STO;
        clr_SI;

        set_STA;                                //Check if no ACK is returned by EEPROM, it is under timed-write cycle
        clr_SI;
        while (!SI);                            //Check SI set or not
        if (I2STAT != 0x08)                     //Check status value after every step
            return 0;

        clr_STA;
        I2DAT = DevAddress;
        clr_SI;
        while (!SI);                            //Check SI set or not
    }while (I2STAT != 0x18);

    /* Step6 */
    set_STO;
    clr_SI;
    while (STO);                                /* Check STOP signal */
    return 1;
}

unsigned char I2C_Receive(unsigned char DevAddress,unsigned char MemAddress,unsigned char *pData, unsigned char Lenght) {
    /* Step8 */
    set_STA;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x08)                         //Check status value after every step
        return 0;

    /* Step9 */
    I2DAT = DevAddress;
    clr_STA;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x18)
        return 0;

    /* Step10 */
    I2DAT = MemAddress;                               //address high for I2C EEPROM
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x28)
        return 0;

    /* Step12 */
    /* Repeated START */
    set_STA;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x10)                         //Check status value after every step
        return 0;

    /* Step13 */
    clr_STA;                                    //STA needs to be cleared after START codition is generated
    I2DAT = DevAddress;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x40)
        return 0;

    /* Step14 */
    while(Lenght)
    {
        set_AA;
        clr_SI;
        while (!SI);                            //Check SI set or not
        if (I2STAT != 0x50)
            return 0;
        *pData=I2DAT;
        pData++;
        Lenght--;
    }

    /* Step15 */
    clr_AA;
    clr_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x58)
        return 0;

    /* Step16 */
    set_STO;
    clr_SI;
    while (STO);                                /* Check STOP signal */
    return 1;
}

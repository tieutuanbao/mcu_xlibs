/**
  ******************************************************************************
  * @file           : gpio.c
  * @brief          : Thư viện lập trình chip N76E003.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

#include "User_gpio.h"

const struct {
  TypeGPIOMode Normal;
  TypeGPIOMode PushPull;
  TypeGPIOMode Input;
  TypeGPIOMode OpenDrain;
  TypeGPIOMode LowLevelInterrupt;
  TypeGPIOMode HighLevelInterrupt;
  TypeGPIOMode FallingInterrupt;
  TypeGPIOMode RasingInterrupt;
} GPIOMode = {
  0, 1, 2, 3, 4, 5, 6, 7
};

void P0Mode(uint8_t _PIN, TypeGPIOMode Mode) {
    if(Mode.Value & 0x01)
        P0M2 |= _PIN;
    else
        P0M2 &= ~_PIN;

    if(Mode.Value & 0x02)
        P0M1 |= _PIN;
    else
        P0M1 &= ~_PIN;
}

void P1Mode(uint8_t _PIN, TypeGPIOMode Mode) {
    if(Mode.Value & 0x01)
        P1M2 |= _PIN;
    else
        P1M2 &= ~_PIN;

    if(Mode.Value & 0x02)
        P1M1 |= _PIN;
    else
        P1M1 &= ~_PIN;
}

void P3Mode(uint8_t _PIN, TypeGPIOMode Mode) {
    if(Mode.Value & 0x01)
        P3M2 |= _PIN;
    else
        P3M2 &= ~_PIN;

    if(Mode.Value & 0x02)
        P3M1 |= _PIN;
    else
        P3M1 &= ~_PIN;
}

static void PinInterruptConfig(uint8_t _PIN, TypeGPIOMode Mode) {
    if(_PIN == PIN4 || _PIN == PIN5) {
        PICON = Mode.Value==6 || Mode.Value==7? PICON|0x40:PICON&0xBF;
    }
    else if(_PIN == PIN6 || _PIN == PIN7) {
        PICON = Mode.Value==6 || Mode.Value==7? PICON|0x80:PICON&0x7F;
    }else {
        PICON = Mode.Value==6 || Mode.Value==7? PICON|(_PIN<<2):PICON&(_PIN<<2);
    }
    PINEN = Mode.Value==4 || Mode.Value==6? PINEN|_PIN : PINEN&(~_PIN);
    PIPEN = Mode.Value==5 || Mode.Value==7? PIPEN|_PIN : PIPEN&(~_PIN);
}

void GPIO_Init(void) {
    /*
        ----- OUTPUT ------
    */
    P0Mode(PIN0|PIN6, GPIOMode.PushPull);
    P1Mode(PIN1|PIN3|PIN5|PIN7, GPIOMode.PushPull);
    P3Mode(PIN0, GPIOMode.PushPull);
    /*
        ----- INPUT ------
    */
    P0Mode(PIN1|PIN3|PIN4|PIN5|PIN7, GPIOMode.Input);
    P1Mode(PIN0|PIN2|PIN4, GPIOMode.Input);

    /*
        ----- _PIN Interrupt ------
    */
//    PinInterruptConfig(PIN5, GPIOMode.FallingInterrupt);
//    set_EPI;
    /*
        ----- Preset ------
    */
    P30 = P17 = 0;
    P00 = P11 = P13 = P15 = 0;
}

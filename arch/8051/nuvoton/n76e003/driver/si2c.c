#include "User_Soft_I2C.h"
#include "N76E003.h"
#include "Function_Define.h"
#include "SFR_Macro.h"
#include "User_delay.h"
#include "User_GPIO.h"

unsigned int Timeout_counter=0;

void Bit_0() {
    I2C_SDA_W=0;
    delay_us(1);
    I2C_SCL_W=1;
    delay_us(1);
    I2C_SCL_W=0;
    delay_us(1);
    I2C_SDA_W=0;
    delay_us(1);
}
void Bit_1() {
    I2C_SDA_W=1;
    delay_us(1);
    I2C_SCL_W=1;
    delay_us(1);
    I2C_SCL_W=0;
    delay_us(1);
    I2C_SDA_W=0;
    delay_us(1);
}

void Soft_I2C_Init() {
    DS1307_I2C_GPIO_Init();
    I2C_SDA_W = 1;
    I2C_SCL_W = 1;
}

void I2C_Start() {
    I2C_SDA_W = 0;
    delay_us(1);
    I2C_SCL_W = 0;
    delay_us(1);
}
void I2C_Stop() {
    I2C_SCL_W = 1;
    delay_us(1);
    I2C_SDA_W = 1;
    delay_us(1);
}
unsigned char Receive_ACK() {
    I2C_SDA_W = 1;
    I2C_SCL_W = 1;
    delay_us(1);
    if(I2C_SDA_R) {
        delay_us(1);
        I2C_SCL_W = 0;
        return NACK;
    }
    else {
        delay_us(1);
        I2C_SCL_W = 0;
        return ACK;
    }
}
void Send_ACK(unsigned char ACK_bit) {
    I2C_SDA_W = ACK_bit;
    delay_us(1);
    I2C_SCL_W = 1;
    delay_us(1);
    I2C_SCL_W = 0;
    delay_us(1);
    I2C_SDA_W = 0;
    delay_us(1);
}
unsigned char I2C_Send(unsigned char Data) {
    /* Send 8-bit Data */
    if(Data&0x80) Bit_1();    else Bit_0();
    if(Data&0x40) Bit_1();    else Bit_0();
    if(Data&0x20) Bit_1();    else Bit_0();
    if(Data&0x10) Bit_1();    else Bit_0();
    if(Data&0x08) Bit_1();    else Bit_0();
    if(Data&0x04) Bit_1();    else Bit_0();
    if(Data&0x02) Bit_1();    else Bit_0();
    if(Data&0x01) Bit_1();    else Bit_0();
    /* Check ACK */
    return Receive_ACK();
}

unsigned char I2C_Receive() {
    unsigned char Data,temp;
    I2C_SDA_W = 1;
    /* Receive 8-bit Data */
    for(temp=0;temp<8;temp++) {
        I2C_SCL_W = 1;
        Data <<= temp;
        Data |= I2C_SDA_R;
        delay_us(1);
        I2C_SCL_W = 0;
        delay_us(1);
    }
    /* Return Data */
    return Data;
}

unsigned char I2C_Receive_Last_Byte() {
    unsigned char Data=0,temp=0;
    I2C_SDA_W = 1;
    /* Receive 8-bit Data */
    for(temp=0;temp<8;temp++) {
        I2C_SCL_W = 1;
        Data <<= 1;
        Data |= I2C_SDA_R&0x01;
        delay_us(1);
        I2C_SCL_W = 0;
        delay_us(1);
    }
    /* Return Data */
    Send_ACK(NACK);
    return Data;
}

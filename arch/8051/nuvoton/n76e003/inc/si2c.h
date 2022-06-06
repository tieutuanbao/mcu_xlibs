#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H


#define I2C_SDA_R        P14
#define I2C_SDA_W        P14
#define I2C_SCL_W        P13
#define I2C_SCL_R        P13

#define ACK        0
#define NACK    1

void Soft_I2C_Init();
void I2C_Start();
void I2C_Stop();
unsigned char Receive_ACK();
void Send_ACK(unsigned char ACK_bit);
unsigned char I2C_Send(unsigned char Data);
unsigned char I2C_Receive();
unsigned char I2C_Receive_Last_Byte();

#endif

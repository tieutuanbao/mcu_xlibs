#ifndef __I2C_H
#define __I2C_H


#define I2C_SDA        P14
#define I2C_SCL        P13

#define ACK        0
#define NACK    1

void I2C_Init();
unsigned char I2C_Send(unsigned char DevAddress,unsigned char MemAddress,unsigned char *pData, unsigned char Lenght);
unsigned char I2C_Receive(unsigned char DevAddress,unsigned char MemAddress,unsigned char *pData, unsigned char Lenght);

#endif

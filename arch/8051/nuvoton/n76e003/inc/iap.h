/**
  ******************************************************************************
  * File Name          : User_IAP.c
  * Description        : File header In Application Programming
    * Author                         : Tieu Tuan Bao
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#ifndef __IAP_H
#define __IAP_H


#include "main.h"


//---------------------------------------------------------------
// Following define by customer
// Please confirm the start addresss not over your code size
//---------------------------------------------------------------
#define        DATA_SIZE                        1024                // Byte
#define        APROM_SIZE                    16                    // KByte
#define        DATA_START_ADDR            0x3800            // Page


void Erase_APROM(unsigned int u16_addr, unsigned int size_data);
void Program_APROM( uint8_t __data *data_poiter, unsigned int u16_addr, unsigned int size_data);
void Read_APROM( uint8_t __data *data_poiter, unsigned int u16_addr, unsigned int size_data);
#endif

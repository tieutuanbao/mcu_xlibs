/**
  ******************************************************************************
  * @file           : i2c.c
  * @brief          : Thư viện driver i2c lập trình nuvoton ms51.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

#include "i2c.h"

void i2c_init(void) {
    /* Set clock to 100Khz at 16Mhz Fclk
            I2C_clk = Fsys / (4* (I2CLK + 1))
    */
    I2CLK = 79;
    /* Enable I2C */
    I2CEN = 1;
    /* I2c pins select */
    I2CPX = 0;
}

uint8_t i2c_mem_read(uint16_t dev_addr, uint8_t mem_addr, uint8_t* data, uint16_t size, uint32_t timeout) {
    uint32_t temp_timeout = 0;
    uint8_t ret = 0;
    /* Send start bit */
    STA = 1;
    SI = 0;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if (I2STAT != 0x08) {
        ret = 1;
        goto END_READ_I2C;
    }
    /* Send slave address */
    STA = 0;
    I2DAT = dev_addr;
    SI = 0;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if (I2STAT != 0x18) {
        ret = 1;
        goto END_READ_I2C;
    }
    /* Send mem address */
    I2DAT = mem_addr;
    SI = 0;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if (I2STAT != 0x28) {
        ret = 1;
        goto END_READ_I2C;
    }
    /* Repeat start */
    set_STA;
    clr_SI;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if(I2STAT != 0x10) {
        ret = 1;
        goto END_READ_I2C;
    }
    /* Send slave address */
    STA = 0;
    I2DAT = dev_addr|0x01;
    SI = 0;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if(I2STAT != 0x40) {
        ret = 1;
        goto END_READ_I2C;
    }
    /* Read data */
    for(uint16_t index_mem = 0; index_mem < size; index_mem++) {
        /* Set ACK */
        set_AA;
        clr_SI;
        for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
        if(I2STAT != 0x50) {
            ret = 1;
            goto END_READ_I2C;
        }
        *(data + index_mem) = I2DAT;
    }
    /* Send NACK */
    clr_AA;
    clr_SI;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if(I2STAT != 0x58) {
        ret = 1;
    }
END_READ_I2C:
    clr_SI;
    set_STO;
    /* Wait stop signal */
    for(temp_timeout = 0; (STO) && (temp_timeout < timeout); temp_timeout++);
    return ret;
}

uint8_t i2c_mem_write(uint16_t dev_addr, uint8_t mem_addr, uint8_t* data, uint16_t size, uint32_t timeout) {
    uint32_t temp_timeout = 0;
    uint32_t temp_timeout_2 = 0;
    uint8_t ret = 0;
    /* Send start bit */
    STA = 1;
    SI = 0;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if (I2STAT != 0x08) {
        ret = 1;
        goto END_WRITE_I2C;
    }
    /* Send slave address */
    STA = 0;
    I2DAT = dev_addr;
    SI = 0;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if (I2STAT != 0x18) {
        ret = 1;
        goto END_WRITE_I2C;
    }
    /* Send mem address */
    I2DAT = mem_addr;
    SI = 0;
    for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    if (I2STAT != 0x28) {
        ret = 1;
        goto END_WRITE_I2C;
    }
    /* Write data */
    for(uint16_t index_data = 0; index_data < size; index_data++) {
        I2DAT = *(data + index_data);
        clr_SI;
        for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
        if(I2STAT != 0x28) {
            ret = 1;
            goto END_WRITE_I2C;
        }
    }
    /* Send Stop */
    do {
        set_STO;
        clr_SI;
        for(temp_timeout = 0; (STO) && (temp_timeout < timeout); temp_timeout++);

        set_STA;
        clr_SI;
        for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
        if(I2STAT != 0x08) {
            ret = 1;
            goto END_WRITE_I2C;
        }

        clr_STA;                            /* Clear STA and Keep SI value in I2CON */
        I2DAT = dev_addr;   /* Send (SLA+W) to EEPROM */
        clr_SI;
        for(temp_timeout = 0; (!SI) && (temp_timeout < timeout); temp_timeout++);
    }while((I2STAT != 0x18) && (temp_timeout_2++ < timeout));

END_WRITE_I2C:
    set_STO;
    clr_SI;
    /* Wait stop signal */
    for(temp_timeout = 0; (STO) && (temp_timeout < timeout); temp_timeout++);
    return ret;
}

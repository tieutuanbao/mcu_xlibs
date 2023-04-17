#ifndef __E32_SX1278_H
#define __E32_SX1278_H

#include <stdint.h>
#include <stdbool.h>

#define E32_TTL_M0          P17
#define E32_TTL_M1          P30
#define E32_TTL_AUX         P05

typedef enum{
    E32_Save_No             = 0xC0,
    E32_Save_Yes            = 0xC2
} E32_Param_Save_t;

typedef enum{    
    E32_UARTParityBit_8N1   = 0,
    E32_UARTParityBit_8O1   = 1,
    E32_UARTParityBit_8E1   = 2
} E32_Param_UARTParityBit_t;

typedef enum{
    E32_Baudrate_1200       = 0,
    E32_Baudrate_2400       = 1,
    E32_Baudrate_4800       = 2,
    E32_Baudrate_9600       = 3,
    E32_Baudrate_19200      = 4,
    E32_Baudrate_38400      = 5,
    E32_Baudrate_57600      = 6,
    E32_Baudrate_115200     = 7
} E32_Param_Baudrate_t;

typedef enum{
    E32_Airrate_0_3k        = 0,
    E32_Airrate_1_2k        = 1,
    E32_Airrate_2_4k        = 2,
    E32_Airrate_4_8k        = 3,
    E32_Airrate_9_6k        = 4,
    E32_Airrate_19_2k       = 5
} E32_Param_Airrate_t;

typedef enum{
    E32_Transparentmode     = 0,
    E32_Fixedmode           = 1
} E32_FixedTransEn_Mode_t;

typedef enum{
    E32_IO_OD_Mode          = 0,
    E32_IO_PP_Mode          = 1
} E32_Param_IO_Mode_t;

typedef enum{
    E32_Wakeup_250ms        = 0,
    E32_Wakeup_500ms        = 1,
    E32_Wakeup_750ms        = 2,
    E32_Wakeup_1000ms       = 3,
    E32_Wakeup_1250ms       = 4,
    E32_Wakeup_1500ms       = 5,
    E32_Wakeup_1750ms       = 6,
    E32_Wakeup_2000ms       = 7
} E32_Param_Wakeup_Time_t;

typedef enum{
    E32_FEC_TurnOFF         = 0,
    E32_FEC_TurnON          = 1
} E32_Param_FEC_t;

typedef enum{
    E32_Tx_Power_30dBm      = 0,
    E32_Tx_Power_27dBm      = 1,
    E32_Tx_Power_24dBm      = 2,
    E32_Tx_Power_21dBm      = 3
} E32_Param_Tx_Power_t;

typedef enum{
    E32_Normal_Mode         = 0x00,
    E32_Wakeup_Mode         = 0x01,
    E32_PowerSave_Mode      = 0x02,
    E32_Sleep_Mode          = 0x03
} E32_Operating_Mode_t;

typedef struct {
    E32_Param_Save_t save                           : 8;
    uint8_t ADDH                                    : 8; /* 00H~FFH */
    uint8_t ADDL                                    : 8; /* 00H~FFH */
    E32_Param_UARTParityBit_t UARTParityBit         : 2;
    E32_Param_Baudrate_t UARTBaudrate               : 3;
    E32_Param_Airrate_t AirDataRate                 : 3;
    uint8_t Channel                                 : 8; /* 00H~1FH correspond to 410-441Mhz */
    E32_FixedTransEn_Mode_t FixedTransmissionEn     : 1;
    E32_Param_IO_Mode_t IODriverMode                : 1;
    E32_Param_Wakeup_Time_t WakeupTime              : 3;
    E32_Param_FEC_t FECSwitch                       : 1;
    E32_Param_Tx_Power_t TransmissionPower          : 2;
} E32_SX1278_Param_t;

typedef struct {
    void (*transmit_driver)(uint8_t *, uint32_t);
    void (*setM0_driver)(bool level);
    void (*setM1_driver)(bool level);
    E32_SX1278_Param_t param;
} E32_SX1278_t;

void E32_SX1276_init(E32_SX1278_t *dev,
                    void (*transmitDriver)(uint8_t *,uint32_t ),
                    void (*setM0_driver)(bool level),
                    void (*setM1_driver)(bool level)
                    );
void E32_SX1276_enterMode(E32_SX1278_t *dev, E32_Operating_Mode_t opMode);
void E32_SX1276_transmit(E32_SX1278_t *dev, uint8_t *data, uint32_t dataLength);
void E32_SX1276_paramConfig(E32_SX1278_t *dev);

#endif

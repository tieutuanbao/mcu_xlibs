#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#include "nrf24.h"

/* Memory Map */
#define NRF24L01_REG_CONFIG      0x00
#define NRF24L01_REG_EN_AA       0x01
#define NRF24L01_REG_EN_RXADDR   0x02
#define NRF24L01_REG_SETUP_AW    0x03
#define NRF24L01_REG_SETUP_RETR  0x04
#define NRF24L01_REG_RF_CH       0x05
#define NRF24L01_REG_RF_SETUP    0x06
#define NRF24L01_REG_STATUS      0x07
#define NRF24L01_REG_OBSERVE_TX  0x08
#define NRF24L01_REG_CD          0x09
#define NRF24L01_REG_RX_ADDR_P0  0x0A
#define NRF24L01_REG_RX_ADDR_P1  0x0B
#define NRF24L01_REG_RX_ADDR_P2  0x0C
#define NRF24L01_REG_RX_ADDR_P3  0x0D
#define NRF24L01_REG_RX_ADDR_P4  0x0E
#define NRF24L01_REG_RX_ADDR_P5  0x0F
#define NRF24L01_REG_TX_ADDR     0x10
#define NRF24L01_REG_RX_PW_P0    0x11
#define NRF24L01_REG_RX_PW_P1    0x12
#define NRF24L01_REG_RX_PW_P2    0x13
#define NRF24L01_REG_RX_PW_P3    0x14
#define NRF24L01_REG_RX_PW_P4    0x15
#define NRF24L01_REG_RX_PW_P5    0x16
#define NRF24L01_REG_FIFO_STATUS    0x17
#define NRF24L01_REG_DYNPD	        0x1C
#define NRF24L01_REG_FEATURE	    0x1D

/* Bit Mnemonics */
#define NRF24L01_BIT_MASK_RX_DR  6
#define NRF24L01_BIT_MASK_TX_DS  5
#define NRF24L01_BIT_MASK_MAX_RT 4
#define NRF24L01_BIT_EN_CRC      3
#define NRF24L01_BIT_CRCO        2
#define NRF24L01_BIT_PWR_UP      1
#define NRF24L01_BIT_PRIM_RX     0
#define NRF24L01_BIT_ENAA_P5     5
#define NRF24L01_BIT_ENAA_P4     4
#define NRF24L01_BIT_ENAA_P3     3
#define NRF24L01_BIT_ENAA_P2     2
#define NRF24L01_BIT_ENAA_P1     1
#define NRF24L01_BIT_ENAA_P0     0
#define NRF24L01_BIT_ERX_P5      5
#define NRF24L01_BIT_ERX_P4      4
#define NRF24L01_BIT_ERX_P3      3
#define NRF24L01_BIT_ERX_P2      2
#define NRF24L01_BIT_ERX_P1      1
#define NRF24L01_BIT_ERX_P0      0
#define NRF24L01_BIT_AW          0
#define NRF24L01_BIT_ARD         4
#define NRF24L01_BIT_ARC         0
#define NRF24L01_BIT_PLL_LOCK    4
#define NRF24L01_BIT_RF_DR       3
#define NRF24L01_BIT_RF_PWR      6
#define NRF24L01_BIT_RX_DR       6
#define NRF24L01_BIT_TX_DS       5
#define NRF24L01_BIT_MAX_RT      4
#define NRF24L01_BIT_RX_P_NO     1
#define NRF24L01_BIT_TX_FULL     0
#define NRF24L01_BIT_PLOS_CNT    4
#define NRF24L01_BIT_ARC_CNT     0
#define NRF24L01_BIT_TX_REUSE    6
#define NRF24L01_BIT_FIFO_FULL   5
#define NRF24L01_BIT_TX_EMPTY    4
#define NRF24L01_BIT_RX_FULL     1
#define NRF24L01_BIT_RX_EMPTY    0
#define NRF24L01_BIT_DPL_P5	    5
#define NRF24L01_BIT_DPL_P4	    4
#define NRF24L01_BIT_DPL_P3	    3
#define NRF24L01_BIT_DPL_P2	    2
#define NRF24L01_BIT_DPL_P1	    1
#define NRF24L01_BIT_DPL_P0	    0
#define NRF24L01_BIT_EN_DPL	    2
#define NRF24L01_BIT_EN_ACK_PAY  1
#define NRF24L01_BIT_EN_DYN_ACK  0

/* Instruction Mnemonics */
#define NRF24L01_REG_R_REGISTER         0x00
#define NRF24L01_REG_W_REGISTER         0x20
#define NRF24L01_REG_REGISTER_MASK      0x1F
#define NRF24L01_REG_ACTIVATE           0x50
#define NRF24L01_REG_R_RX_PL_WID        0x60
#define NRF24L01_REG_R_RX_PAYLOAD       0x61
#define NRF24L01_REG_W_TX_PAYLOAD       0xA0
#define NRF24L01_REG_W_ACK_PAYLOAD      0xA8
#define NRF24L01_REG_FLUSH_TX           0xE1
#define NRF24L01_REG_FLUSH_RX           0xE2
#define NRF24L01_REG_REUSE_TX_PL        0xE3
#define NRF24L01_REG_W_TX_PAYLOAD_NACK  0xB0
#define NRF24L01_REG_NOP                0xFF

/* Non-P omissions */
#define NRF24L01_REG_LNA_HCURR   0

/* P model memory Map */
#define NRF24L01_REG_RPD         0x09

/* P model bit Mnemonics */
#define NRF24L01_REG_RF_DR_LOW   5
#define NRF24L01_REG_RF_DR_HIGH  3
#define NRF24L01_REG_RF_PWR_LOW  1
#define NRF24L01_REG_RF_PWR_HIGH 2

void nRF24L01_setChannel(nRF24_t *nRF24, uint8_t channel) ;
nRF24_PA_dbm_t nRF24L01_getPALevel(nRF24_t *nRF24);
void nRF24L01_setPALevel(nRF24_t *nRF24, nRF24_PA_dbm_t level);
nRF24_dataRate_t nRF24L01_getDataRate(nRF24_t *nRF24);
bool nRF24L01_setDataRate(nRF24_t *nRF24, nRF24_dataRate_t dataRate);
void nRF24L01_setAddressWidth(nRF24_t *nRF24, nRF24_addressWidth_t addressWidth);
nRF24_addressWidth_t nRF24L01_getAddressWidth(nRF24_t *nRF24);
nRF24_CRCLength_t nRF24L01_getCRCLength(nRF24_t *nRF24);
void nRF24L01_setCRCLength(nRF24_t *nRF24, nRF24_CRCLength_t length);
void nRF24L01_disableCRC(nRF24_t *nRF24);
void nRF24L01_setRetries(nRF24_t *nRF24, uint8_t delay, uint8_t count);
void nRF24L01_disableDynamicPayloads(nRF24_t *nRF24);
void nRF24L01_setPayloadSize(nRF24_t *nRF24, uint8_t pipe, uint8_t payloadSize);
void nRF24L01_resetStatus(nRF24_t *nRF24);
void nRF24L01_flushRx(nRF24_t *nRF24);
void nRF24L01_flushTx(nRF24_t *nRF24);
void nRF24L01_powerUp(nRF24_t *nRF24);
void nRF24L01_powerDown(nRF24_t *nRF24);
void nRF24L01_printDetails(nRF24_t *nRF24);

bool nRF24L01_isPTXorPRX(nRF24_t *nRF24);
void nRF24L01_startListening(nRF24_t *nRF24);
void nRF24L01_stopListening(nRF24_t *nRF24);
void nRF24L01_openWritingPipe(nRF24_t *nRF24, uint64_t address);
void nRF24L01_openReadingPipe(nRF24_t *nRF24, uint8_t child, uint64_t address);
int8_t nRF24L01_available(nRF24_t *nRF24);
nRF24_txResult_t nRF24L01_write(nRF24_t *nRF24, uint8_t *dataBuf, uint8_t dataLength, bool multicast);
uint8_t nRF24L01_readPayload(nRF24_t *nRF24, uint8_t pipe, uint8_t *pBuf, bool dpl);

void nRF24L01_config(nRF24_t *nRF24);

#endif

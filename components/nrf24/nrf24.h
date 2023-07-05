#ifndef __NRF24_H__
#define __NRF24_H__

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    nRF24_PA_dbm_MIN = 0,
    nRF24_PA_dbm_LOW,
    nRF24_PA_dbm_HIGH,
    nRF24_PA_dbm_MAX,
    nRF24_PA_dbm_ERROR
} nRF24_PA_dbm_t;

typedef enum {
    nRF24_dataRate_1MBPS = 0,
    nRF24_dataRate_2MBPS,
    nRF24_dataRate_250KBPS
} nRF24_dataRate_t;

typedef enum {
    nRF24_CRCLength_DISABLED = 0,
    nRF24_CRCLength_8,
    nRF24_CRCLength_16
} nRF24_CRCLength_t;

typedef enum {
    nRF24_addressWidth_ILLEGAL = 0,
    nRF24_addressWidth_3BYTE,
    nRF24_addressWidth_4BYTE,
    nRF24_addressWidth_5BYTE
} nRF24_addressWidth_t;

typedef enum {
	nRF24_txResult_ERROR  = (uint8_t)0x00, // Unknown error
	nRF24_txResult_SUCCESS,                // Packet has been transmitted successfully
	nRF24_txResult_TIMEOUT,                // It was timeout during packet transmit
	nRF24_txResult_MAXRT                   // Transmit failed with maximum auto retransmit count
} nRF24_txResult_t;

typedef struct {
    void (*setCE_drv)(bool level);
    void (*setCS_drv)(bool level);
    uint8_t (*transferSPI_drv)(uint8_t val);
    uint8_t payloadSize;
    uint64_t pipe0RxAddr;
    bool isPipe0Rx;
    bool dynamicPayloads;
} nRF24_t;

void NRF24_init(
    nRF24_t *nRF24,
    void (*setCE_drv)(bool level),
    void (*setCS_drv)(bool level),
    uint8_t (*transferSPI_drv)(uint8_t val),
    uint8_t payloadSize
    );

uint8_t nRF24_writeReg(nRF24_t *nRF24, uint8_t reg, uint8_t *buf, uint8_t len);
uint8_t nRF24_readReg(nRF24_t *nRF24, uint8_t reg, uint8_t *buf, uint8_t len);
void nRF24_writePayload(nRF24_t *nRF24, uint8_t *pBuf, uint8_t len, uint8_t writeType);

#endif

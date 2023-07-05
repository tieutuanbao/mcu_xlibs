#include "nrf24.h"
#include "bits_delay.h"
#include "bits_env.h"

/**
 * @brief Khởi tạo nRF24 
 * 
 * @param nRF24 
 * @param setCE_drv 
 * @param setCS_drv 
 * @param writeSPI_drv 
 * @param readSPI_drv 
 */
void NRF24_init(
    nRF24_t *nRF24,
    void (*setCE_drv)(bool level),
    void (*setCS_drv)(bool level),
    uint8_t (*transferSPI_drv)(uint8_t val),
    uint8_t payloadSize
    ) {
    nRF24->setCE_drv = setCE_drv;
    nRF24->setCS_drv = setCS_drv;
    nRF24->transferSPI_drv = transferSPI_drv;
    nRF24->payloadSize = payloadSize;

    nRF24->setCE_drv(0);
    nRF24->setCS_drv(1);
    delay(10); // 5ms
}

uint8_t nRF24_writeReg(nRF24_t *nRF24, uint8_t reg, uint8_t *buf, uint8_t len) {
    uint8_t status = 0;
    nRF24->setCS_drv(false);
    delayMicroseconds(5);
    status = nRF24->transferSPI_drv(0x20 | reg);
    while(len--) {
        nRF24->transferSPI_drv(*buf);
        buf++;
        delayMicroseconds(5);
    }
    nRF24->setCS_drv(true);
    return status;
}

uint8_t nRF24_readReg(nRF24_t *nRF24, uint8_t reg, uint8_t *buf, uint8_t len) {
    uint8_t status = 0;
    nRF24->setCS_drv(false);
    delayMicroseconds(5);
    status = nRF24->transferSPI_drv(reg);
    while(len--) {
        *buf = nRF24->transferSPI_drv(0xFF);
        buf++;
        delayMicroseconds(5);
    }
    nRF24->setCS_drv(true);
    return status;
}

void nRF24_writePayload(nRF24_t *nRF24, uint8_t *pBuf, uint8_t len, uint8_t writeType) {
    uint8_t blankLength = 0;
    if(nRF24->dynamicPayloads == false) {
        blankLength = nRF24->payloadSize - len;
    }
    /* begin transfer */
    nRF24->setCS_drv(false);
    delayMicroseconds(5);
    nRF24->transferSPI_drv(writeType);
    while(len--) {
        nRF24->transferSPI_drv(*pBuf);
        pBuf++;
        delayMicroseconds(5);
    }
    while(blankLength--) {
        nRF24->transferSPI_drv(0);
        delayMicroseconds(5);
    }
    nRF24->setCS_drv(true);
}
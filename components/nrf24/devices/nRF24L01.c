#include "nRF24L01.h"
#include "bits_delay.h"
#include "bits_env.h"

#define TAG     "nrf24L01"

void nRF24L01_config(nRF24_t *nRF24) {
    nRF24L01_powerDown(nRF24);
    delayMicroseconds(200);
    nRF24L01_setRetries(nRF24, 5, 15);
    nRF24L01_setDataRate(nRF24, nRF24_dataRate_1MBPS);
    nRF24L01_setPALevel(nRF24, nRF24_PA_dbm_LOW);
    nRF24L01_disableDynamicPayloads(nRF24);
    nRF24->dynamicPayloads = false;
    nRF24_writeReg(nRF24, NRF24L01_REG_EN_AA, (uint8_t *)"\x3F", 1);
    nRF24_writeReg(nRF24, NRF24L01_REG_EN_RXADDR, (uint8_t *)"\x03", 1);
    for(uint8_t indexPipe = 0; indexPipe < 6; indexPipe++) {
        nRF24L01_setPayloadSize(nRF24, indexPipe, 32);
    }
    nRF24L01_setAddressWidth(nRF24, nRF24_addressWidth_5BYTE);

    nRF24L01_setChannel(nRF24, 5);
    nRF24L01_resetStatus(nRF24);

    nRF24L01_flushRx(nRF24);
    nRF24L01_flushTx(nRF24);

    nRF24_writeReg(nRF24, NRF24L01_REG_CONFIG, (uint8_t *)"\x0C", 1) ;
    
    nRF24L01_powerUp(nRF24);
}
void nRF24L01_flushRx(nRF24_t *nRF24) {
    nRF24_writeReg(nRF24, NRF24L01_REG_FLUSH_RX, (void *)0, 0);
}
void nRF24L01_flushTx(nRF24_t *nRF24) {
    nRF24_writeReg(nRF24, NRF24L01_REG_FLUSH_TX, (void *)0, 0);
}
void nRF24L01_setChannel(nRF24_t *nRF24, uint8_t channel) {
    if(channel > 127) {
        channel = 127;
    }
    nRF24_writeReg(nRF24, NRF24L01_REG_RF_CH, &channel, 1);
}
uint8_t nRF24L01_getChannel(nRF24_t *nRF24) {
    uint8_t retVal = 0;
    nRF24_readReg(nRF24, NRF24L01_REG_RF_CH, &retVal, 1);
    return retVal;
}
nRF24_PA_dbm_t nRF24L01_getPALevel(nRF24_t *nRF24) {
    nRF24_PA_dbm_t result = nRF24_PA_dbm_ERROR;
    uint8_t power = 0;

    nRF24_readReg(nRF24, NRF24L01_REG_RF_SETUP, &power, 1);
    power = power & ((1 << NRF24L01_REG_RF_PWR_LOW) | (1 << NRF24L01_REG_RF_PWR_HIGH));

    if(power == ((1 << NRF24L01_REG_RF_PWR_LOW) | (1 << NRF24L01_REG_RF_PWR_HIGH))) {
        result = nRF24_PA_dbm_MAX ;
    }
    else if(power == (1 << NRF24L01_REG_RF_PWR_HIGH)) {
        result = nRF24_PA_dbm_HIGH ;
    }
    else if(power == (1 << NRF24L01_REG_RF_PWR_LOW)) {
        result = nRF24_PA_dbm_LOW ;
    }
    else {
        result = nRF24_PA_dbm_MIN;
    }
    return result;
}
void nRF24L01_setPALevel(nRF24_t *nRF24, nRF24_PA_dbm_t level) {
    uint8_t setupVal = 0;
    nRF24_readReg(nRF24, NRF24L01_REG_RF_SETUP, &setupVal, 1);
    setupVal &= ~((1 << NRF24L01_REG_RF_PWR_LOW) | (1 << NRF24L01_REG_RF_PWR_HIGH));
    
    if(level == nRF24_PA_dbm_MAX) {
        setupVal |= ((1 << NRF24L01_REG_RF_PWR_LOW) | (1 << NRF24L01_REG_RF_PWR_HIGH)) ;
    }
    else if(level == nRF24_PA_dbm_HIGH) {
        setupVal |= (1 << NRF24L01_REG_RF_PWR_HIGH) ;
    }
    else if(level == nRF24_PA_dbm_LOW) {
        setupVal |= (1 << NRF24L01_REG_RF_PWR_LOW);
    }
    else if(level == nRF24_PA_dbm_MIN) {
    }
    else if (level == nRF24_PA_dbm_ERROR ) {
        setupVal |= ((1 << NRF24L01_REG_RF_PWR_LOW) | (1 << NRF24L01_REG_RF_PWR_HIGH)) ;
    }
    nRF24_writeReg(nRF24, NRF24L01_REG_RF_SETUP, &setupVal, 1) ;
}
nRF24_dataRate_t nRF24L01_getDataRate(nRF24_t *nRF24) {
    nRF24_dataRate_t result = nRF24_dataRate_1MBPS;
    uint8_t dataRate = 0;

    nRF24_readReg(nRF24, NRF24L01_REG_RF_SETUP, &dataRate, 1);
    dataRate = dataRate & ((1 << NRF24L01_REG_RF_DR_LOW) | (1 << NRF24L01_REG_RF_DR_HIGH));    
        if(dataRate == (1 << NRF24L01_REG_RF_DR_LOW)) {
            result = nRF24_dataRate_250KBPS ;
        }
        else if(dataRate == (1 << NRF24L01_REG_RF_DR_HIGH)) {
            result = nRF24_dataRate_2MBPS ;
        }
        else {
            result = nRF24_dataRate_1MBPS ;
        }
    return result ;
}
bool nRF24L01_setDataRate(nRF24_t *nRF24, nRF24_dataRate_t dataRate) {
    uint8_t setup = 0, tempSetup = 0;

    nRF24_readReg(nRF24, NRF24L01_REG_RF_SETUP, &setup, 1);
    setup &= ~((1 << NRF24L01_REG_RF_DR_LOW) | (1 << NRF24L01_REG_RF_DR_HIGH)) ;
    if(dataRate == nRF24_dataRate_250KBPS ) {
        setup |= (1 << NRF24L01_REG_RF_DR_LOW) ;
    }
    else {
        if (dataRate == nRF24_dataRate_2MBPS ) {
            setup |= (1 << NRF24L01_REG_RF_DR_HIGH);
        }
        else {
            // 1Mbs
        }
    }
    nRF24_writeReg(nRF24, NRF24L01_REG_RF_SETUP,&setup, 1);

    nRF24_readReg(nRF24, NRF24L01_REG_RF_SETUP, &tempSetup, 1);
    if (tempSetup == setup) {
        return true;
    }
    return false;
}
void nRF24L01_setAddressWidth(nRF24_t *nRF24, nRF24_addressWidth_t addressWidth) {
    nRF24_writeReg(nRF24, NRF24L01_REG_SETUP_AW, (uint8_t *)(&addressWidth), 1);
}
nRF24_addressWidth_t nRF24L01_getAddressWidth(nRF24_t *nRF24) {
    uint8_t retVal;
    nRF24_readReg(nRF24, NRF24L01_REG_SETUP_AW, &retVal, 1);
    return (nRF24_addressWidth_t)(retVal & 0x03);
}
nRF24_CRCLength_t nRF24L01_getCRCLength(nRF24_t *nRF24) {
    uint8_t config = 0;
    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, &config, 1);
    config = config & ((1 << NRF24L01_BIT_CRCO) | (1 << NRF24L01_BIT_EN_CRC));

    if (config & (1 << NRF24L01_BIT_EN_CRC)) {
        if(config & (1 << NRF24L01_BIT_CRCO)) {
            return nRF24_CRCLength_16;
        }
        else {
            return nRF24_CRCLength_8;
        }
    }
    return nRF24_CRCLength_DISABLED;
}
void nRF24L01_setCRCLength(nRF24_t *nRF24, nRF24_CRCLength_t length) {
    uint8_t config = 0;

    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, &config, 1);
    config = config & ~((1 << NRF24L01_BIT_CRCO) | (1 << NRF24L01_BIT_EN_CRC));
    if (length == nRF24_CRCLength_DISABLED) {
    }
    else if (length == nRF24_CRCLength_8) {
        config |= (1 << NRF24L01_BIT_EN_CRC);
    }
    else {
        config |= (1 << NRF24L01_BIT_EN_CRC);
        config |= (1 << NRF24L01_BIT_CRCO );
    }
    nRF24_writeReg(nRF24, NRF24L01_REG_CONFIG, &config, 1) ;
}
void nRF24L01_disableCRC(nRF24_t *nRF24) {
    uint8_t disable = 0;
    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, &disable, 1);
    disable = disable & ~(NRF24L01_BIT_EN_CRC) ;
    nRF24_writeReg(nRF24, NRF24L01_REG_CONFIG, &disable, 1) ;
}
void nRF24L01_setRetries(nRF24_t *nRF24, uint8_t delay, uint8_t count) {
    uint8_t val = ((delay & 0x0F) << NRF24L01_BIT_ARD) | ((count & 0x0F) << NRF24L01_BIT_ARC);
    nRF24_writeReg(nRF24, NRF24L01_REG_SETUP_RETR, &val, 1);
}
void nRF24L01_disableDynamicPayloads(nRF24_t *nRF24) {
    uint8_t val = 0;
    nRF24_writeReg(nRF24, NRF24L01_REG_DYNPD, &val, 1);
}
void nRF24L01_setPayloadSize(nRF24_t *nRF24, uint8_t pipe, uint8_t payloadSize) {
    if(payloadSize > 32) {
        nRF24->payloadSize = 32;
    }
    nRF24_writeReg(nRF24, NRF24L01_REG_RX_PW_P0 + pipe, &(nRF24->payloadSize), 1);
}
uint8_t nRF24L01_getStatus(nRF24_t *nRF24) {
    return nRF24_readReg(nRF24, NRF24L01_REG_NOP, (void *)0, 0);
}
void nRF24L01_setStatus(nRF24_t *nRF24, uint8_t status) {
    nRF24_writeReg(nRF24, NRF24L01_REG_STATUS, &status, 1);
}
void nRF24L01_resetStatus(nRF24_t *nRF24) {
    uint8_t val = (1 << NRF24L01_BIT_RX_DR) | (1 << NRF24L01_BIT_TX_DS) | (1 << NRF24L01_BIT_MAX_RT);
    nRF24_writeReg(nRF24, NRF24L01_REG_STATUS, &val, 1);
}
void nRF24L01_powerUp(nRF24_t *nRF24) {
    uint8_t tempVal = 0;
    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
    if((tempVal & (1 << NRF24L01_BIT_PWR_UP)) == 0) {
        tempVal |= (1 << NRF24L01_BIT_PWR_UP) ;
        nRF24_writeReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
        delay(5);
    }
}
void nRF24L01_powerDown(nRF24_t *nRF24) {
    uint8_t tempVal = 0;
    nRF24->setCE_drv(0);
    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
    tempVal &= ~(1 << NRF24L01_BIT_PWR_UP) ;
    nRF24_writeReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
}
void nRF24L01_printDetails(nRF24_t *nRF24) {
    uint8_t tempBuf[12];
    BITS_LOG(TAG, "*************** nRF24L01 detail ***************");
    nRF24_readReg(nRF24, NRF24L01_REG_STATUS, tempBuf, 1);
    BITS_LOG(TAG, "STATUS: 0x%02x RX_DR=%d TX_DS=%d MAX_RT=%d RX_P_NO=%x TX_FULL=%d\r\n", tempBuf[0],
            (tempBuf[0] >> NRF24L01_BIT_RX_DR) & 0x01, (tempBuf[0] >> NRF24L01_BIT_TX_DS) & 0x01, (tempBuf[0] >> NRF24L01_BIT_MAX_RT) & 0x01,
            (tempBuf[0] >> NRF24L01_BIT_RX_P_NO) & 0x07, tempBuf[0] & 0x01);
    nRF24_writeReg(nRF24, NRF24L01_REG_NOP, (void *)0, 0);

    nRF24_readReg(nRF24, NRF24L01_REG_RX_ADDR_P0, tempBuf, 5);
    nRF24_readReg(nRF24, NRF24L01_REG_RX_ADDR_P1, tempBuf + 5, 5);
    BITS_LOG(TAG, "RX_ADDR_P0-P1: 0x%02X%02X%02X%02X%02X - 0x%02X%02X%02X%02X%02X", tempBuf[4], tempBuf[3], tempBuf[2], tempBuf[1], tempBuf[0], tempBuf[9], tempBuf[8], tempBuf[7], tempBuf[6], tempBuf[5]);
    nRF24_readReg(nRF24, NRF24L01_REG_RX_ADDR_P2, tempBuf, 1);
    nRF24_readReg(nRF24, NRF24L01_REG_RX_ADDR_P3, tempBuf + 1, 1);
    nRF24_readReg(nRF24, NRF24L01_REG_RX_ADDR_P4, tempBuf + 2, 1);
    nRF24_readReg(nRF24, NRF24L01_REG_RX_ADDR_P5, tempBuf + 3, 1);
    BITS_LOG(TAG, "RX_ADDR_P2-P5: 0x%02X 0x%02X 0x%02X 0x%02X", tempBuf[0], tempBuf[1], tempBuf[2], tempBuf[3]);

    nRF24_readReg(nRF24, NRF24L01_REG_TX_ADDR, tempBuf, 5);
    BITS_LOG(TAG, "TX_ADDR: 0x%02X%02X%02X%02X%02X", tempBuf[4], tempBuf[3], tempBuf[2], tempBuf[1], tempBuf[0]);

    nRF24_readReg(nRF24, NRF24L01_REG_RX_PW_P0, tempBuf, 6);
    BITS_LOG(TAG, "RX_PW_P0-6: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", tempBuf[0], tempBuf[1], tempBuf[2], tempBuf[3], tempBuf[4], tempBuf[5]);

    nRF24_readReg(nRF24, NRF24L01_REG_EN_AA, tempBuf, 1);
    BITS_LOG(TAG, "EN_AA: 0x%02X", tempBuf[0]);
    nRF24_readReg(nRF24, NRF24L01_REG_EN_RXADDR, tempBuf, 1);
    BITS_LOG(TAG, "EN_RXADDR: 0x%02X", tempBuf[0]);
    nRF24_readReg(nRF24, NRF24L01_REG_RF_CH, tempBuf, 1);
    BITS_LOG(TAG, "RF_CH: 0x%02X", tempBuf[0]);
    nRF24_readReg(nRF24, NRF24L01_REG_RF_SETUP, tempBuf, 1);
    BITS_LOG(TAG, "RF_SETUP: 0x%02X", tempBuf[0]);
    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, tempBuf, 1);
    BITS_LOG(TAG, "CONFIG: 0x%02X", tempBuf[0]);
    nRF24_readReg(nRF24, NRF24L01_REG_DYNPD, tempBuf, 1);
    BITS_LOG(TAG, "DYNPD: 0x%02X", tempBuf[0]);
}

/**
 * @brief Kiểm tra chế độ hoạt động
 * 
 * @param nRF24 Thiết bị giao tiếp
 * @return true PTX
 * @return false PRX
 */
bool nRF24L01_isPTXorPRX(nRF24_t *nRF24) {
    uint8_t tempVal = 0;
    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
    if(tempVal & (1 << NRF24L01_BIT_PRIM_RX)) {
        return false;
    }
    return true;
}
/**
 * @brief Cấu hình địa chỉ gửi
 * 
 * @param nRF24 
 * @param address 
 */
void nRF24L01_openWritingPipe(nRF24_t *nRF24, uint64_t address) {
    // Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
    // expects it LSB first too, so we're good.
    nRF24_writeReg(nRF24, NRF24L01_REG_RX_ADDR_P0, (uint8_t *)(&address), 5);
    nRF24_writeReg(nRF24, NRF24L01_REG_TX_ADDR, (uint8_t *)(&address), 5);
    if(nRF24->payloadSize > 32) {
        nRF24->payloadSize = 32;
    }
    nRF24_writeReg(nRF24, NRF24L01_REG_RX_PW_P0, &nRF24->payloadSize, 1);
}
/**
 * @brief Cấu hình địa chỉ nhận dữ liệu cho mỗi ống
 * 
 * @param nRF24 
 * @param value 
 */
static const uint8_t child_pipe[] = {NRF24L01_REG_RX_ADDR_P0, NRF24L01_REG_RX_ADDR_P1, NRF24L01_REG_RX_ADDR_P2, NRF24L01_REG_RX_ADDR_P3, NRF24L01_REG_RX_ADDR_P4, NRF24L01_REG_RX_ADDR_P5};
static const uint8_t child_payload_size[] = {NRF24L01_REG_RX_PW_P0, NRF24L01_REG_RX_PW_P1, NRF24L01_REG_RX_PW_P2, NRF24L01_REG_RX_PW_P3, NRF24L01_REG_RX_PW_P4, NRF24L01_REG_RX_PW_P5};
static const uint8_t child_pipe_enable[] = {NRF24L01_BIT_ERX_P0, NRF24L01_BIT_ERX_P1, NRF24L01_BIT_ERX_P2, NRF24L01_BIT_ERX_P3, NRF24L01_BIT_ERX_P4, NRF24L01_BIT_ERX_P5};
void nRF24L01_openReadingPipe(nRF24_t *nRF24, uint8_t child, uint64_t address) {
    uint8_t tempVal = 0;
    if(child == 0) {
        nRF24->pipe0RxAddr = address;
        nRF24->isPipe0Rx = true;
    }
    if (child < 6) {
        if ( child < 2 ) {
            nRF24_writeReg(nRF24, child_pipe[child], (uint8_t *)(&address), 5);
        }
        else {
            nRF24_writeReg(nRF24, child_pipe[child], (uint8_t *)(&address), 1);
        }
        nRF24_writeReg(nRF24, child_payload_size[child], &(nRF24->payloadSize), 1);
        nRF24_readReg(nRF24, NRF24L01_REG_EN_RXADDR, &tempVal, 1);
        tempVal |= (1 << child_pipe_enable[child]);
        nRF24_writeReg(nRF24, NRF24L01_REG_EN_RXADDR, &tempVal, 1);
    }
}
/**
 * @brief Bắt đầu nhận dữ liệu
 * 
 * @param nRF24 thiết bị giao tiếp
 */
void nRF24L01_startListening(nRF24_t *nRF24) {
    uint8_t tempVal = 0;
    nRF24L01_powerUp(nRF24);
    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
    tempVal |= (1 << NRF24L01_BIT_PRIM_RX);
    nRF24_writeReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
    nRF24L01_resetStatus(nRF24);
    nRF24->setCE_drv(true);
    
    if(nRF24->isPipe0Rx) {
        nRF24_writeReg(nRF24, NRF24L01_REG_RX_ADDR_P0, (uint8_t *)(&(nRF24->pipe0RxAddr)), 5);
    }
    else {
        nRF24_readReg(nRF24, NRF24L01_REG_EN_RXADDR, &tempVal, 1);
        tempVal &= ~(1 << child_pipe_enable[0]);
        nRF24_writeReg(nRF24, NRF24L01_REG_EN_RXADDR, &tempVal, 1);
        nRF24->isPipe0Rx = 0;
    }
}
/**
 * @brief Dừng nhận dữ liệu
 * 
 * @param nRF24 thiết bị giao tiếp
 */
void nRF24L01_stopListening(nRF24_t *nRF24) {
    uint8_t tempVal = 0;
    nRF24->setCE_drv(false);
    delayMicroseconds(130);
    // nRF24L01_flushTx(nRF24);
    nRF24_readReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
    tempVal &= ~(1 << NRF24L01_BIT_PRIM_RX);
    nRF24_writeReg(nRF24, NRF24L01_REG_CONFIG, &tempVal, 1);
    // nRF24L01_flushRx(nRF24);
    /* Enable Rx pipe 0 */
    nRF24_readReg(nRF24, NRF24L01_REG_EN_RXADDR, &tempVal, 1);
    tempVal |= (1 << child_pipe_enable[0]);
    nRF24_writeReg(nRF24, NRF24L01_REG_EN_RXADDR, &tempVal, 1);
}
/**
 * @brief Kiểm tra có dữ liệu nhận không
 * 
 * @param nRF24 
 * @return int8_t trả về ống đang nhận dữ liệu
 * (< 0) : không có dữ liệu nhận | (>= 0) : có dữ liệu ở ống
 */
int8_t nRF24L01_available(nRF24_t *nRF24) {
    uint8_t status = nRF24L01_getStatus(nRF24);
    int8_t pipe = 0;
    if (status & (1 << NRF24L01_BIT_MASK_RX_DR)) {
        pipe = (status >> NRF24L01_BIT_RX_P_NO) & 0x07;
        if(pipe > 5) {
            return 0;
        }
        // nRF24L01_setStatus(nRF24, (1 << NRF24L01_BIT_RX_P_NO));
        // if (status & (1 << NRF24L01_BIT_MASK_TX_DS)) {
        //     nRF24L01_setStatus(nRF24, (1 << NRF24L01_BIT_MASK_TX_DS));
        // }
        return pipe;
    }
    return -1;
}
uint8_t nRF24L01_getDynamicPayloadWidth(nRF24_t *nRF24) {
    uint8_t ret = 0;
    nRF24_readReg(nRF24, NRF24L01_REG_R_RX_PL_WID, &ret, 1);
    return ret;
}
/**
 * @brief Hàm truyền giữ liệu nRF24L01
 * 
 * @param nRF24 
 * @param dataBuf 
 * @param dataLength 
 * @param multicast 
 * @return nRF24_txResult_t 
 */
nRF24_txResult_t nRF24L01_write(nRF24_t *nRF24, uint8_t *dataBuf, uint8_t dataLength, bool multicast) {
    nRF24_txResult_t ret = nRF24_txResult_ERROR;
    uint8_t tempVal = 0;
    uint32_t tickNow = 0;

    /* Write payload */
    nRF24_writePayload(nRF24, dataBuf, dataLength, multicast?NRF24L01_REG_W_TX_PAYLOAD_NACK:NRF24L01_REG_W_TX_PAYLOAD);
    delayMicroseconds(1);
    /* CE HIGH */
    nRF24->setCE_drv(1);
    delayMicroseconds(1);
    /* Wait until complete or failed */
    tickNow = millis();
    while(1) {
        tempVal = nRF24L01_getStatus(nRF24);
        if (tempVal & ((1 << NRF24L01_BIT_MASK_TX_DS) | (1 << NRF24L01_BIT_MASK_MAX_RT))) {
            break;
        }
        if((millis() - tickNow) > 100) {
            return nRF24_txResult_TIMEOUT; 
        }
    }
    tickNow = millis();
    /* CE LOW */
    nRF24->setCE_drv(0);
    /* Clear IRQ */
    nRF24L01_resetStatus(nRF24);
    /* return result */
    if(tempVal & (1 << NRF24L01_BIT_MASK_MAX_RT)) {
        nRF24L01_flushTx(nRF24);
        return nRF24_txResult_MAXRT;
    }
    if(tempVal & (1 << NRF24L01_BIT_MASK_TX_DS)) {
        return nRF24_txResult_SUCCESS;
    }
    return ret;
}
/**
 * @brief Hàm đọc giữ liệu nRF24L01
 * 
 * @param nRF24 Đối tượng đang giao tiếp
 * @param pipe Ống cần đọc
 * @param pBuf Con trỏ buffer đọc
 * @param dpl Dynamic Payload - true: có sử dụng | false: không sử dụng
 * @return uint8_t Độ dài đã đọc được
 */
uint8_t nRF24L01_readPayload(nRF24_t *nRF24, uint8_t pipe, uint8_t *pBuf, bool dpl) {
    uint8_t length = 0;
	if (pipe < 6) {
		if(dpl) {
			length = nRF24L01_getDynamicPayloadWidth(nRF24);
			if(length > 32) {
				length = 0;
				nRF24L01_flushRx(nRF24);
			}
		}
        else {
			nRF24_readReg(nRF24, child_payload_size[pipe], &length, 1);
		}
		if (length) {
			nRF24_readReg(nRF24, NRF24L01_REG_R_RX_PAYLOAD, pBuf, length);
            nRF24_writeReg(nRF24, NRF24L01_REG_STATUS, (uint8_t *)"\x40", 1); // clear interrupt flag
		}
	}
	return length;
}

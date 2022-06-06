/**
    *    @brief: Thư viện lập trình sim800 non-blocking
    *    Thuật toán non-blocking:
    *        Layer 1: Bao gồm function (AT command) và các lệnh truy vấn.
    *        Layer 2: Function handle và parsing dữ liệu.
    */

#include "sim800.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

/**
    *    @brief: Hàm tìm chuỗi trong buffer
    *
    */
int16_t SIM800_strstr(uint8_t *strSource, uint16_t strSourceSize, uint8_t *strSearch, uint8_t strSearchLen) {
    int16_t indexSource = 0;
    for(indexSource = 0; indexSource < strSourceSize; indexSource++) {
        uint16_t indexSearch = 0;
        for(indexSearch = 0; indexSearch < strSearchLen; indexSearch++) {
            if(strSource[(indexSource + indexSearch)%strSourceSize] != strSearch[indexSearch]) {
                break;
            }
        }
        /* Nếu tất cả ký tự đều giống nhau thì trả về vị trí trong source */
        if(indexSearch == strSearchLen) return indexSource;
        else if((indexSource + 1) == strSourceSize) return -1;
    }
    return -1;
}

/**
    *    @brief: Hàm khởi tạo module sim800
    *
    */
void SIM800_Init(SIM800Module_TypeStruct *module) {
    /* Thoát nếu thiếu 1 trong các Driver */
    if((module->delay == 0)||(module->setPWRKEY == 0)||(module->RxBuffer.pData == 0)||(module->getRI == 0)) {
        return;
    }
    /* Reset module */
    module->setPWRKEY(1);
    module->delay(500);
    module->setPWRKEY(0);
    module->delay(5000);
    module->command.state = IDLE;
}

/**
    *    @brief: Hàm xử lý phản hồi đột ngột từ module
    *
    */
void SIM800_suddenlyHandler(SIM800Module_TypeStruct *module) {
    if(strstr((char const *)module->RxBuffer.pData, "+CMTI:")) {        // Must be config AT+CNMI=2,1
        if((module->RxBuffer.pData[8] == 'S') && (module->RxBuffer.pData[9] == 'M')) {
            module->sms.available = atoi((char const *)&module->RxBuffer.pData[12]);
        }
    }else if(strstr((char const *)module->RxBuffer.pData, "RING")) {
        return;
    }
}

/**
    *    @brief: Hàm xử lý trả về OK hoặ FAIL
    *
    */
void SIM800_AT_STATUS_Handler(SIM800Module_TypeStruct *module) {
    /* Tìm lệnh AT\r\n trong buffer nhận dữ liệu */
    if(strstr(module->RxBuffer.pData, "OK\r\n")) {
        module->command.state = IDLE;
        module->command.lastResponse = AT_OK;
        module->command.responseHandler = 0;
        return;
    }else if(strstr(module->RxBuffer.pData, "FAIL\r\n")) {
        module->command.state = IDLE;
        module->command.lastResponse = AT_FAIL;
        module->command.responseHandler = 0;
        return;
    }else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.lastResponse = AT_NOTRESP;
            module->command.responseHandler = 0;
            return;
        }
    }
}

/**
    *    @brief: Hàm giao tiếp dữ liệu ATCommand
    *
    *    @param: module - Module đang sử dụng
    *                    commandMode -    BLOCKING
    *                                            -    NONBLOCKING
    *                    ATCommand    -    Lệnh AT kèm theo \r\n
    *                    timeout - Thời gian hết hạn thực thi lệnh
    *                    ... - Các con trỏ tham chiếu return của lệnh AT
    */
uint8_t SIM800_ATCommand(SIM800Module_TypeStruct *module, SIM800CommandMode_TypeEnum commandMode, uint8_t *ATCommand, void (*callbackHandler)(SIM800Module_TypeStruct *), uint16_t timeout) {
    /* Module bận thì trả về BUSY */
    if((module->command.state == BUSY) && (module->command.timeout != 0)) {
        return 1;
    }
    module->command.state = BUSY;
    /* Cấu hình callback */
    module->command.responseHandler = callbackHandler;
    /* Gửi dữ liệu */
    module->sendData(ATCommand, strlen((char const *)ATCommand));
    /* Đặt timeout */
    module->command.timeout = timeout/10;
    if(commandMode == BLOCKING) {
        while(module->command.timeout) {
            module->delay(1);
        }
    }
    return 0;
}


/**
    *    @brief: Hàm xử lý trả về lệnh AT\r\n
    *
    */
void SIM800_AT_Handler(SIM800Module_TypeStruct *module) {
    /* Tìm lệnh AT\r\n trong buffer nhận dữ liệu */
    if(strstr((char const *)module->RxBuffer.pData, "AT\r\r\n")) {
        module->command.responseHandler = SIM800_AT_STATUS_Handler;
        return;
    }
}

void SIM800_ATCMGR_Content1_Handler(SIM800Module_TypeStruct *module);
void SIM800_ATCMGR_Content2_Handler(SIM800Module_TypeStruct *module);
/**
    *    @brief: Hàm xử lý trả về lệnh ATCMGR\r\n
    *
    */
void SIM800_ATCMGR_Handler(SIM800Module_TypeStruct *module) {
    if(strstr((char const *)module->RxBuffer.pData, "AT+CMGR")) {
        module->command.responseHandler = SIM800_ATCMGR_Content1_Handler;
        return;
    }else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.lastResponse = AT_NOTRESP;
            module->command.responseHandler = 0;
        }
    }
}

/**
    *    @brief: Hàm lấy nội dung ATCMGR\r\n
    *
    */
void SIM800_ATCMGR_Content1_Handler(SIM800Module_TypeStruct *module) {
    char *pData = (int8_t *)strstr((char const *)module->RxBuffer.pData, "+CMGR:");
    char *pDataStop = 0;
    if(pData) {
        /* URC */
        pData = strchr((char const *)pData, '"');
        if(pData) pData++;
        else return;
        pData = strchr((char const *)pData, '"');
        if(pData) pData++;
        else return;
        /* Phone number */
        pData = strchr((char const *)pData, '"');
        if(pData) pData++;
        else return;
        pDataStop = strchr((char const *)pData, '"');
        if(pDataStop == 0) return;
        if((pDataStop - pData) <= 15) {
            memcpy(module->sms.phone, pData, (pDataStop - pData));
        }else {
            return;
        }
        pData = pDataStop+1;
        /* null */
        pData = strchr((char const *)pData, '"');
        if(pData) pData++;
        else return;
        pData = strchr((char const *)pData, '"');
        if(pData) pData++;
        else return;
        /* Date and Time */
        pData = strchr((char const *)pData, '"');
        if(pData) pData++;
        else return;
        pDataStop = strchr((char const *)pData, '"');
        if(pDataStop == 0) return;
        if((pDataStop - pData) <= 20) {
            memcpy(module->sms.time, pData, (pDataStop - pData));
        }else {
            return;
        }
        /* Next handler -> Get content */
        module->command.responseHandler = SIM800_ATCMGR_Content2_Handler;
        return;
    }else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.lastResponse = AT_NOTRESP;
            module->command.responseHandler = 0;
        }
    }
}

/**
    *    @brief: Hàm lấy nội dung 2 ATCMGR\r\n
    *
    */
void SIM800_ATCMGR_Content2_Handler(SIM800Module_TypeStruct *module) {
    char *pDataStop = (int8_t *)strstr((char const *)module->RxBuffer.pData, "\r\n");
    if(pDataStop) {
        if((pDataStop - module->RxBuffer.pData) <= SIM800_SMS_SIZE) {
            memcpy(module->sms.content, module->RxBuffer.pData, (pDataStop - module->RxBuffer.pData));
        }
        module->command.responseHandler = SIM800_AT_STATUS_Handler;
        module->sms.available = 0;
        return;
    }else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.lastResponse = AT_NOTRESP;
            module->command.responseHandler = 0;
        }
    }
}

/**
    *    @brief: Hàm handler Calling
    *
    */
void SIM800_ATD_Handler(SIM800Module_TypeStruct *module) {
    if(strstr((char const *)module->RxBuffer.pData,(char const *)"NO ANSWER")!=0) {
        module->call.lastCalling = 1;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->RxBuffer.pData,(char const *)"BUSY")!=0) {
        module->call.lastCalling = 2;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->RxBuffer.pData,(char const *)"NO DIALTONE")!=0) {
        module->call.lastCalling = 3;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->RxBuffer.pData,(char const *)"NO CARRIER")!=0) {
        module->call.lastCalling = 4;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->RxBuffer.pData,(char const *)"ERROR")!=0) {
        module->call.lastCalling = 5;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->RxBuffer.pData,(char const *)"RING")!=0) {
        module->call.lastCalling = 6;
        module->command.timeout = 0;
    }
    else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.lastResponse = AT_NOTRESP;
            module->command.responseHandler = 0;
        }
    }
}

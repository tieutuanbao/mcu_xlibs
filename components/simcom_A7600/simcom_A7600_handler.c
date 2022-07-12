/**
  ******************************************************************************
  * @file           : simcom_a7600_handler.c
  * @brief          : Thư viện handler simcom 7600.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    * Thư viện lập trình sim A7600 hỗ trợ non-blocking
    *
  ******************************************************************************
  */

#include "simcom_A7600_handler.h"
#include <string.h>
#include <stdlib.h>

/**
    *    @brief: Hàm xử lý phản hồi đột ngột từ module
    *
    */
void sim7600_suddenly_handler(sim7600_t *module) {
    if(strstr((char const *)module->serial.pData, "+CMTI:")) {        // Must be config AT+CNMI=2,1
        if((module->serial.pData[8] == 'S') && (module->serial.pData[9] == 'M')) {
            module->sms.available = atoi((char const *)&module->serial.pData[12]);
        }
    }else if(strstr((char const *)module->serial.pData, "RING")) {
        return;
    }
}

/**
    *    @brief: Hàm xử lý trả về OK hoặ FAIL
    *
    */
void sim7600_ATCMD_resp_handler(sim7600_t *module) {
    /* Tìm lệnh AT\r\n trong buffer nhận dữ liệu */
    if(strstr((char const *)module->serial.pData, "OK\r\n")) {
        module->command.state = IDLE;
        module->command.last_resp = AT_OK;
        module->command.resp_handler = 0;
        return;
    }else if(strstr((char const *)module->serial.pData, "FAIL\r\n")) {
        module->command.state = IDLE;
        module->command.last_resp = AT_FAIL;
        module->command.resp_handler = 0;
        return;
    }else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.last_resp = AT_NOTRESP;
            module->command.resp_handler = 0;
            return;
        }
    }
}
/**
    *    @brief: Hàm xử lý trả về lệnh AT\r\n
    *
    */
void sim7600_AT_handler(sim7600_t *module) {
    /* Tìm lệnh AT\r\n trong buffer nhận dữ liệu */
    if(strstr((char const *)module->serial.pData, "AT\r\r\n")) {
        module->command.resp_handler = sim7600_ATCMD_resp_handler;
        return;
    }
}

/* ------------------------------------------------- AT+CMGR ------------------------------------------------- */
/**
    *    @brief: Hàm xử lý trả về lệnh ATCMGR\r\n
    *
    */
void sim7600_ATCMGR_Handler(sim7600_t *module) {
    if(strstr((char const *)module->serial.pData, "AT+CMGR")) {
        module->command.resp_handler = sim7600_ATCMGR_param_Handler;
        return;
    }else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.last_resp = AT_NOTRESP;
            module->command.resp_handler = 0;
        }
    }
}

/**
    *    @brief: Hàm lấy nội dung ATCMGR\r\n
    *
    */
void sim7600_ATCMGR_param_Handler(sim7600_t *module) {
    char *pData = (char *)strstr((char const *)module->serial.pData, "+CMGR:");
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
        module->command.resp_handler = sim7600_ATCMGR_data_Handler;
        return;
    }else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.last_resp = AT_NOTRESP;
            module->command.resp_handler = 0;
        }
    }
}

/**
    *    @brief: Hàm lấy <data> ATCMGR\r\n
    *
    */
void sim7600_ATCMGR_data_Handler(sim7600_t *module) {
    char *pDataStop = (char *)strstr((char const *)module->serial.pData, "\r\n");
    if(pDataStop) {
        if((pDataStop - (char *)module->serial.pData) <= SIM7600_SMS_SIZE) {
            memcpy(module->sms.content, module->serial.pData, (pDataStop - (char *)module->serial.pData));
        }
        module->command.resp_handler = sim7600_ATCMD_resp_handler;
        module->sms.available = 0;
        return;
    }else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.last_resp = AT_NOTRESP;
            module->command.resp_handler = 0;
        }
    }
}

/* ------------------------------------------------- ATD ------------------------------------------------- */
/**
    *    @brief: Hàm handler Calling lệnh ATD
    *
    */
void sim7600_ATD_handler(sim7600_t *module) {
    if(strstr((char const *)module->serial.pData,(char const *)"NO ANSWER")!=0) {
        module->call.last_resp = CALL_NO_ANSWER;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->serial.pData,(char const *)"BUSY")!=0) {
        module->call.last_resp = CALL_BUSY;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->serial.pData,(char const *)"NO DIALTONE")!=0) {
        module->call.last_resp = CALL_NO_DIALTONE;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->serial.pData,(char const *)"NO CARRIER")!=0) {
        module->call.last_resp = CALL_NO_CARRIER;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->serial.pData,(char const *)"ERROR")!=0) {
        module->call.last_resp = CALL_ERROR;
        module->command.timeout = 0;
    }
    else if(strstr((char const *)module->serial.pData,(char const *)"RING")!=0) {
        module->call.last_resp = CALL_RING;
        module->command.timeout = 0;
    }
    else {
        if(module->command.timeout == 0) {
            module->command.state = IDLE;
            module->command.last_resp = AT_NOTRESP;
            module->command.resp_handler = 0;
        }
    }
}

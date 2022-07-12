#ifndef __SIM800_DELAY_H
#define __SIM800_DELAY_H

#include "SFR_Macro.h"

#define SIM800_BUFFER_SIZE    140
#define SIM800_SMS_SIZE            50

#define SIM800_END_CMD                        "\r\n\0"
#define SIM800_END_SMS                        "\X1a\0"

typedef enum {
    BLOCKING,
    NONBLOCKING
} SIM800CommandMode_TypeEnum;

typedef enum {
    IDLE,                // Đang rảnh
    BUSY,                // Chờ response
    TIMEOUT
} SIM800ModuleStatus_TypeEnum;

typedef enum {
    AT_OK,
    AT_FAIL,
    AT_NOTRESP
} SIM800Resp_TypeEnum;

typedef enum {
    CALL_NO_ANSWER,
    CALL_BUSY,
    CALL_NO_DIALTONE,
    CALL_NO_CARRIER,
    CALL_ERROR,
    CALL_RING
} SIM800CallingResp_TypeEnum;

typedef struct {
    /* Các hàm Driver */
    void (*sendData)(uint8_t *pData, uint16_t dataLen);            // Hàm gửi dữ liệu giao tiếp UART
    void (*delay)(uint16_t ms);                                                            // Hàm delay chương trình đang sử dụng
    void (*setPWRKEY)(uint8_t level);                                                // Hàm điều khiển chân PWRKey
    uint8_t (*getRI)();                                                                            // Hàm lấy tín hiệu chân RI
    /* Cấu trúc Buffer nhận dữ liệu */
    struct {
        uint8_t pData[SIM800_BUFFER_SIZE];
        uint16_t count;
    } RxBuffer;
    /* Cấu trúc xử lý SMS */
    struct {
        uint8_t available;
        uint8_t phone[15];
        uint8_t time[20];
        uint8_t content[SIM800_SMS_SIZE];
    } sms;
    /* Cấu trúc xử lý cuộc gọi */
    struct {
        SIM800CallingResp_TypeEnum lastCalling;
    } call;
    /* Cấu trúc xử lý non-blocking */
    struct {
        SIM800ModuleStatus_TypeEnum state;
        volatile uint16_t timeout;
        SIM800Resp_TypeEnum lastResponse;
        void (*responseHandler)();
    } command;
} SIM800Module_TypeStruct;

#define SIM800_GetData(module, data)            if(module.RxBuffer.count < (SIM800_BUFFER_SIZE - 1)) {        \
                                                                                        module.RxBuffer.pData[module.RxBuffer.count++] = data;        \
                                                                                        module.RxBuffer.pData[module.RxBuffer.count] = 0;        \
                                                                                        if((data == '\n') ) {        \
                                                                                            if(module.RxBuffer.count >= 3) {        \
                                                                                                if(module.command.responseHandler != 0) {        \
                                                                                                    module.command.responseHandler(&module);        \
                                                                                                }        \
                                                                                                SIM800_suddenlyHandler(&module);        \
                                                                                            }        \
                                                                                            module.RxBuffer.count = 0;    \
                                                                                        }        \
                                                                                    }

extern void SIM800_Init(SIM800Module_TypeStruct *module);
extern uint8_t SIM800_ATCommand(SIM800Module_TypeStruct *module, SIM800CommandMode_TypeEnum commandMode, uint8_t *ATCommand, void (*callbackHandler)(SIM800Module_TypeStruct *), uint16_t timeout);

extern void SIM800_suddenlyHandler(SIM800Module_TypeStruct *module);
extern void SIM800_AT_STATUS_Handler(SIM800Module_TypeStruct *module);

extern void SIM800_AT_Handler(SIM800Module_TypeStruct *module);
extern void SIM800_ATCMGR_Content1_Handler(SIM800Module_TypeStruct *module);
extern void SIM800_ATCMGR_Content2_Handler(SIM800Module_TypeStruct *module);

extern void SIM800_ATCMGR_Handler(SIM800Module_TypeStruct *module);
extern void SIM800_ATCMGR_Content1_Handler(SIM800Module_TypeStruct *module);
extern void SIM800_ATCMGR_Content2_Handler(SIM800Module_TypeStruct *module);


void SIM800_ATD_Handler(SIM800Module_TypeStruct *module);

#endif

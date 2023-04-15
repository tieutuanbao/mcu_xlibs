/**
  ******************************************************************************
  * @file           : simcom_a7600.h
  * @brief          : Thư viện driver simcom 7600.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    * Thư viện lập trình sim A7600 hỗ trợ non-blocking
    *
  ******************************************************************************
  */

#ifndef __SIMCOM_7600_H
#define __SIMCOM_7600_H

#include <stdint.h>
#include <stdbool.h>

#define SIM7600_BUFFER_SIZE     500
#define SIM7600_SMS_SIZE        256

#define SIM7600_END_CMD         "\r\n\0"
#define SIM7600_END_SMS         "\X1a\0"

#if defined(STM32)
    #define SIM7600_TickType_t  uint32_t
#elif defined(ESP32)
    #define SIM7600_TickType_t  int64_t
#else
    #pragma message "Please define SIM7600_TickType_t type"
#endif
/**
 *  Trạng thái hoạt động
 */
typedef enum {
    SIM7600_State_WAIT_PWR_ON,    // Chờ khởi động, mặc định 14 giây
    SIM7600_State_IDLE,           // Đang rảnh
    SIM7600_State_BUSY,           // Chờ response
    SIM7600_State_WAIT_RESET,     // Chờ reset
    SIM7600_State_TIMEOUT
} SIM7600_State_t;

/**
 *  Trả về AT command
 */
typedef enum {
    SIM7600_Response_OK,
    SIM7600_Response_FAIL,
    SIM7600_Response_NOTRESP
} SIM7600_Response_t;

/**
 *  @brief Trả về sau cuộc gọi
 */
typedef enum {
    SIM7600_CallStatus_NO_ANSWER,
    SIM7600_CallStatus_BUSY,
    SIM7600_CallStatus_NO_DIALTONE,
    SIM7600_CallStatus_NO_CARRIER,
    SIM7600_CallStatus_ERROR,
    SIM7600_CallStatus_RING
} SIM7600_CallStatus_t;

typedef enum {
    SIM7600_COMMAND_AT,
    SIM7600_COMMAND_CMGR,
    SIM7600_COMMAND_CMGS,
    SIM7600_COMMAND_ATD,
    SIM7600_COMMAND_ATH
} SIM7600_CommandName_t;

typedef struct {
    /* public */
    void (*send)(uint8_t *pData, uint16_t dataLen); // Hàm gửi dữ liệu giao tiếp UART
    void (*PWRKEY_set)(bool level);  // Hàm điều khiển chân PWRKey
    void (*RESET_set)(bool level);  // Hàm điều khiển chân RESET
    bool (*RI_get)();   // Hàm lấy tín hiệu chân RI

    SIM7600_TickType_t lastTick;
    /* Cấu trúc Buffer nhận dữ liệu raw */
    struct {
        uint8_t pData[SIM7600_BUFFER_SIZE];
        uint16_t count;
    } serial;
    /* Cấu trúc tạm lưu SMS */
    struct {
        struct {
            uint8_t available;
            uint8_t phone[15];
            uint8_t time[20];
            uint8_t content[SIM7600_SMS_SIZE];
        } recv;
        struct {
            char *content;
            uint16_t len;
        } send;
    } sms;
    /* Cấu trúc tạm lưu cuộc gọi */
    struct {
        uint8_t phone[15];
        SIM7600_CallStatus_t last_resp;
    } call;
    /* Cấu trúc xử lý non-blocking */
    struct {
        uint32_t timeout;
        SIM7600_Response_t last_resp;
        void (*resp_handler)();
    } command;
    SIM7600_State_t state;
} SIM7600_t;

/**
 * @brief Hàm xử lý Byte dữ liệu UART cho SIM7600
 * 
 */
#define SIM7600_uartHandler(module, data)   if(module.serial.count < (sim7600_BUFFER_SIZE - 1)) { \
                                                module.serial.pData[module.serial.count++] = data; \
                                                module.serial.pData[module.serial.count] = 0; \
                                                if((data == '\n') ) { \
                                                    if(module.serial.count >= 3) { \
                                                        if(module.command.resp_handler != 0) { \
                                                            module.command.resp_handler(&module); \
                                                        } \
                                                        sim7600_suddenly_handler(&module); \
                                                    } \
                                                    module.serial.count = 0; \
                                                } \
                                            }

void SIM7600_init(SIM7600_t *module, void (*PWRKEY_set)(bool level), void (*RESET_set)(bool level), bool (*RI_get)(), SIM7600_TickType_t currentTick);
void SIM7600_commandRaw(SIM7600_t *module, uint8_t *ATCommand, void (*callbackHandler)(SIM7600_t *), uint16_t timeout);

#endif

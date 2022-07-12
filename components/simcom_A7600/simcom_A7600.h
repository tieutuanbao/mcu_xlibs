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

#define SIM7600_BUFFER_SIZE        500
#define SIM7600_SMS_SIZE            256

#define SIM7600_END_CMD                        "\r\n\0"
#define SIM7600_END_SMS                        "\X1a\0"

/**
    *    Chế độ hoạt động
    */
typedef enum {
    BLOCKING,
    NONBLOCKING
} sim7600_cmd_mode_t;

/**
    *    Trạng thái hoạt động
    */
typedef enum {
    IDLE,                // Đang rảnh
    BUSY,                // Chờ response
    TIMEOUT
} sim7600_state_t;


/**
    *    Trả về AT command
    */
typedef enum {
    AT_OK,
    AT_FAIL,
    AT_NOTRESP
} sim7600_resp_t;

/**
    *    Trả về sau cuộc gọi
    */
typedef enum {
    CALL_NO_ANSWER,
    CALL_BUSY,
    CALL_NO_DIALTONE,
    CALL_NO_CARRIER,
    CALL_ERROR,
    CALL_RING
} sim7600_call_return_t;

typedef struct {
    /* Các hàm Driver */
    void (*sendData)(uint8_t *pData, uint16_t dataLen);            // Hàm gửi dữ liệu giao tiếp UART
    void (*delay)(uint16_t ms);                                                            // Hàm delay chương trình đang sử dụng
    void (*setPWRKEY)(uint8_t level);                                                // Hàm điều khiển chân PWRKey
    uint8_t (*getRI)();                                                                            // Hàm lấy tín hiệu chân RI
    /* Cấu trúc Buffer nhận dữ liệu raw */
    struct {
        uint8_t pData[SIM7600_BUFFER_SIZE];
        uint16_t count;
    } serial;
    /* Cấu trúc tạm lưu SMS */
    struct {
        uint8_t available;
        uint8_t phone[15];
        uint8_t time[20];
        uint8_t content[SIM7600_SMS_SIZE];
    } sms;
    /* Cấu trúc tạm lưu cuộc gọi */
    struct {
        uint8_t phone[15];
        sim7600_call_return_t last_resp;
    } call;
    /* Cấu trúc xử lý non-blocking */
    struct {
        sim7600_state_t state;
        volatile uint16_t timeout;
        sim7600_resp_t last_resp;
        void (*resp_handler)();
    } command;
} sim7600_t;

#define sim7600_get_data(module, data)            if(module.serial.count < (sim7600_BUFFER_SIZE - 1)) {        \
                                                                                            module.serial.pData[module.serial.count++] = data;        \
                                                                                            module.serial.pData[module.serial.count] = 0;        \
                                                                                            if((data == '\n') ) {        \
                                                                                                if(module.serial.count >= 3) {        \
                                                                                                    if(module.command.resp_handler != 0) {        \
                                                                                                        module.command.resp_handler(&module);        \
                                                                                                    }        \
                                                                                                    sim7600_suddenly_handler(&module);        \
                                                                                                }        \
                                                                                                module.serial.count = 0;    \
                                                                                            }        \
                                                                                        }

extern void sim7600_init(sim7600_t *module);
extern uint8_t sim7600_AT_command(sim7600_t *module, uint8_t *ATCommand, void (*callbackHandler)(sim7600_t *), sim7600_cmd_mode_t cmd_mode, uint16_t timeout);

#endif

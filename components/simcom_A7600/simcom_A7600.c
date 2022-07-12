/**
  ******************************************************************************
  * @file           : simcom_a7600.c
  * @brief          : Thư viện driver simcom 7600.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    * Thư viện lập trình sim A7600 hỗ trợ non-blocking
    *
  ******************************************************************************
  */

#include "simcom_A7600.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

/**
    *    @brief: Hàm tìm chuỗi trong buffer
    *
    */
int16_t sim7600_strstr(uint8_t *strSource, uint16_t strSourceSize, uint8_t *strSearch, uint16_t strSearchLen) {
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
void sim7600_Init(sim7600_t *module) {
    /* Thoát nếu thiếu 1 trong các Driver */
    if((module->delay == 0)||(module->setPWRKEY == 0)||(module->serial.pData == 0)||(module->getRI == 0)) {
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
    *    @brief: Hàm giao tiếp dữ liệu ATCommand
    *
    *    @param: module        - Module đang sử dụng
    *                    cmd_mode    -    BLOCKING
    *                                        -    NONBLOCKING
    *                    ATCommand    -    Lệnh AT kèm theo \r\n
    *                    timeout        - Thời gian hết hạn chờ phản hồi trong chế độ BLOCKING (milisecond*10)
    */
uint8_t sim7600_at_command(sim7600_t *module, uint8_t *ATCommand, void (*callbackHandler)(sim7600_t *), sim7600_cmd_mode_t cmd_mode, uint16_t timeout) {
    /* Module bận thì trả về BUSY */
    if((module->command.state == BUSY) && (module->command.timeout != 0)) {
        return 1;
    }
    module->command.state = BUSY;
    /* Cấu hình callback */
    module->command.resp_handler = callbackHandler;
    /* Gửi dữ liệu */
    module->sendData(ATCommand, strlen((char const *)ATCommand));
    /* Đặt timeout */
    module->command.timeout = timeout;
    if(cmd_mode == BLOCKING) {
        while(module->command.timeout) {
            module->delay(1);
        }
    }
    return 0;
}

void sim7600_timeout_counter(sim7600_t *module) {
    if(module->command.timeout > 0) {
        module->command.timeout--;
    }
}

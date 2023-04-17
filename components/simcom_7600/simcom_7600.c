/**
  ******************************************************************************
  * @file           : simcom_7600.c
  * @brief          : Thư viện driver simcom 7600.
  * @author         : Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
  * Thư viện lập trình sim 7600 non-blocking
  *
  ******************************************************************************
  */

#include "simcom_7600.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "simcom_7600_handler.h"

/**
 *  @brief Hàm khởi tạo module sim800
 *  @param module: module SIM7600 đang dùng
 */
void SIM7600_init(SIM7600_t *module, void (*PWRKEY_set)(bool level), void (*RESET_set)(bool level), bool (*RI_get)(), SIM7600_TickType_t currentTick) {
    /* Thoát nếu thiếu 1 trong các Drivers cần thiết */
    if((PWRKEY_set == 0) || (RESET_set == 0) || (RI_get == 0)) {
        return;
    }
    /* Cài đặt driver */
    module->PWRKEY_set = PWRKEY_set;
    module->RESET_set = RESET_set;
    module->RI_get = RI_get;
    /* Power on module */
    SIM7600_powerHardControl(module, true, currentTick);
}

/**
 * @brief Hàm điều khiển nguồn SIM7600 qua chân PWRKEY
 * @param state true:On false:Off
 */
void SIM7600_powerHardControl(SIM7600_t *module, bool state, SIM7600_TickType_t currentTick) {
    if(state == true) {
        module->state = SIM7600_State_WAIT_PWR_ON;
        module->PWRKEY_set(false);
        module->lastTick = currentTick;
    }
}
/**
 * @brief Kiểm tra module SIM7600 đang Busy
 * 
 * @param module 
 * @return true 
 * @return false 
 */
bool SIM7600_isBusy(SIM7600_t *module) {
    if(module->state != SIM7600_State_IDLE) {
        return true;
    }
    return false;
}
/**
 *  @brief: Hàm giao tiếp dữ liệu ATCommand
 *  @param module Module đang sử dụng
 *  @param ATCommand Lệnh AT kèm theo \r\n
 *  @param timeout Thời gian hết hạn chờ phản hồi trong chế độ BLOCKING (milisecond*10)
 */
void SIM7600_commandRaw(SIM7600_t *module, uint8_t *ATCommand, void (*callbackHandler)(SIM7600_t *), uint16_t timeout) {
    if(module->state != SIM7600_State_IDLE) {
        return SIM7600_State_BUSY;
    }
    module->state = SIM7600_State_BUSY;
    /* Cấu hình callback */
    module->command.resp_handler = callbackHandler;
    /* Gửi dữ liệu */
    module->send(ATCommand, strlen((char const *)ATCommand));
    module->send(ATCommand, strlen((char const *)ATCommand));
    /* Đặt timeout */
    module->command.timeout = timeout;
    return 0;
}

void SIM7600_dial(SIM7600_t *module, char *phoneNumber, uint32_t timeout) {
    module->send("ATD", 3);
    module->send(phoneNumber, strlen((char const *)phoneNumber));
    module->send(";", 1);
    module->send(SIM7600_END_CMD, 2);
    module->command.timeout = timeout;
}

void SIM7600_exec(SIM7600_t *module, SIM7600_TickType_t currentTick) {
    switch(module->state) {
        case SIM7600_State_WAIT_PWR_ON: {
            if((currentTick - module->lastTick) >= 125000) { // Power on trong 12.5s
                module->state = SIM7600_State_IDLE;
            }
            break;
        }
        case SIM7600_State_BUSY: {
            if((currentTick - module->lastTick) >= module->command.timeout) {
                module->state = SIM7600_State_IDLE;
            }
            break;
        }
        default: {
            break;
        }
    }
}

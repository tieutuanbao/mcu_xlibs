#include "../E32_SX1278.h"

E32_SX1278_t LoraE32;

void UART_transmit(uint8_t *data, uint32_t dataLength) {
    /* send UART */
}

void LoraE32_M0_set(bool level) {
    /* set level M0 pin */
}

void LoraE32_M1_set(bool level) {
    /* set level M1 pin */
}

void main() {
    /* Khởi tạo cấu trúc giao tiếp Lora E32 */
    E32_SX1276_init(&LoraE32, UART_transmit, LoraE32_M0_set, LoraE32_M1_set);
    /* Vào chế độ Sleep */
    E32_SX1276_enterMode(&LoraE32, E32_Sleep_Mode);
    /* Chờ chút ... */
    delay_ms(1000);
    /* Tùy chọn thông số hoạt động */
    LoraE32.param.save = E32_Save_Yes;
    LoraE32.param.ADDH = 0x00;
    LoraE32.param.ADDL = 0x00;
    LoraE32.param.UARTParityBit = E32_UARTParityBit_8N1;
    LoraE32.param.UARTBaudrate = E32_Baudrate_9600;
    LoraE32.param.AirDataRate = E32_Airrate_2_4k;
    LoraE32.param.Channel = 0x1E;
    LoraE32.param.FixedTransmissionEn = E32_Transparentmode;
    LoraE32.param.IODriverMode = E32_IO_PP_Mode;
    LoraE32.param.WakeupTime = E32_Wakeup_250ms;
    LoraE32.param.FECSwitch = E32_FEC_TurnON;
    LoraE32.param.TransmissionPower = E32_Tx_Power_30dBm;
    /* Cấu hình các tham số */
    E32_SX1276_paramConfig(&LoraE32);
    /* Chờ chút ... */
    delay_ms(1000);
    /* Vào chế độ hoạt động bình thường */
    E32_SX1276_enterMode(&LoraE32, E32_Normal_Mode);
    /* Chờ chút ... */
    delay_ms(100);
    /* Bắt đầu gửi nhận dữ liệu bình thường ... */
}
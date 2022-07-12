/**
 * @brief File example lập trình w25qxx
 * Yêu cầu:
 *
 */
#include "w25qxxx.h"

w25qxxx_stt_t ret;
w25qxxx_t w25q_flash;
uint8_t ex_flash_buf[500] = "Cong hoa xa hoi chu nghia Viet Nam, Doc lap, Tu do, Hanh phuc!";
/**
 * @brief Hàm đọc cho w25qxx
 *
 * @param addr địa chỉ đọc
 * @param buff_to_read buffer dữ liệu đọc
 * @param size kích thước dữ liệu đọc
 * @return w25qxxx_stt_t
 */
w25qxxx_stt_t flash_w25qxx_drv_read(uint8_t *buff_to_read, uint32_t size) {

}
/**
 * @brief Hàm ghi cho w25qxx
 *
 * @param addr địa chỉ ghi
 * @param buff_to_read buffer dữ liệu ghi
 * @param size kích thước dữ liệu ghi
 * @return w25qxxx_stt_t
 */
w25qxxx_stt_t flash_w25qxx_drv_write(uint8_t *buff_to_write, uint32_t size) {

}
/**
 * @brief Hàm điều khiển chân cs
 *
 * @param level
 */
void flash_w25qxx_cs_control(uint8_t level) {

}
/**
 * @brief Hàm delay miliseconds
 *
 * @param ms_val thời gian delay tính bằng miliseconds
 */
void delay_ms(uint32_t ms_val) {

}

void main() {
    w25qxxx_init(&w25q_flash, flash_w25qxx_drv_read, flash_w25qxx_drv_write, flash_w25qxx_cs_control, delay_ms);

    /* -------- Test Flash -------- */
    printf("Du lieu ban dau: %s\n", ex_flash_buf);
    /* 1 - Xóa sector vị trí 0 */
    ret = w25q_erase_sector(&w25q_flash, 0);
    printf("Buoc 1: Xoa sector - %d\n", ret);
    /* 2 - Ghi dữ liệu từ ex_flash_buf từ địa chỉ 250 */
    ret = w25qxx_write_mem(&w25q_flash, 250, ex_flash_buf, strlen((const char *)ex_flash_buf));
    printf("Buoc 2: Ghi du lieu - %d\n", ret);
    /* 3 - Đọc dữ liệu từ flash ở địa chỉ 250 ra ex_flash_buf */
    ret = w25qxx_fast_read_mem(&w25q_flash, 250, ex_flash_buf, strlen((const char *)ex_flash_buf));
    printf("Buoc 3: Doc du lieu - %d\n", ret);
    /* 4 - In dữ liệu vừa đọc */
    printf("Du lieu vua doc: %s\n", ex_flash_buf);
    while(1) {

    }
}

/**
 * @brief File example lập trình ucs1903 hỗ trợ điều khiển song song
 * Yêu cầu:
 *         - Tất cả các line chạy song song phải đặt chung một port.
 *         - list ucs1903[] không yêu cầu các line phải chung một port.
 *         - Nếu người dùng đặt 2 port khác nhau trên cùng một list thì khi update song song có thể chạy:
 *                 ucs1903_multi_update(&ucs1903[5], 3) : trong đó port này có line bắt đầu từ 5 và tổng là 3 line
 *                 lưu ý: 2 port khác nhau trên cùng một list cũng không thể chạy được song song.
 *         - Ví dụ 2 port khác nhau trên list ở vị trí 0 và 6, port ở vị trí 0 có 6 line và vị trí 6 có 4 line:
 *                 ucs1903_multi_update(&ucs1903[0], 6);
 *                 ucs1903_multi_update(&ucs1903[6], 4);
 */
#include "ucs1903.h"

/* 1 - Cấu hình kiểu IO trong file ucs1903.h : UCS1903_IO_SUPPORT_CLR_SET */
/* 2 - Define Port giao tiếp */
#if UCS1903_IO_SUPPORT_CLR_SET
    #define GPIO_1903_PORT_SET    0x08000004
    #define GPIO_1903_PORT_CLR    0x80000008
#else
    #define GPIO_1903_PORT            0x80000008
#endif

/* Define IO cho 1903 */
#define GPIO_1903_DI_CH0        12
#define GPIO_1903_DI_CH1        13
#define GPIO_1903_DI_CH2        14

#define GPIO1903_DI_CH0_BIT_MASK        (1ULL << GPIO_1903_DI_CH0)
#define GPIO1903_DI_CH1_BIT_MASK        (1ULL << GPIO_1903_DI_CH1)
#define GPIO1903_DI_CH2_BIT_MASK        (1ULL << GPIO_1903_DI_CH2)

/* Define số cổng - chạy song song */
#define MAX_CHIP_PARA        3
/* Define số lượng chip nối tiếp mỗi cổng */
#define MAX_CHIP_SERI        200

ucs1903_color_t color_buf[8][MAX_CHIP_SERI];
ucs1903_t ucs1903[8];

void main() {
    #if UCS1903_IO_SUPPORT_CLR_SET
    ucs1903_init(&ucs1903[0], (uint32_t *)GPIO_1903_PORT_SET, (uint32_t *)GPIO_1903_PORT_CLR, GPIO1903_DI_CH0_BIT_MASK, MAX_CHIP_SERI, &color_buf[0][0], 100, 100, 100, 100, 1, 8, 2);
    ucs1903_init(&ucs1903[1], (uint32_t *)GPIO_1903_PORT_SET, (uint32_t *)GPIO_1903_PORT_CLR, GPIO1903_DI_CH1_BIT_MASK, MAX_CHIP_SERI, &color_buf[1][0], 100, 100, 100, 100, 1, 8, 2);
    ucs1903_init(&ucs1903[2], (uint32_t *)GPIO_1903_PORT_SET, (uint32_t *)GPIO_1903_PORT_CLR, GPIO1903_DI_CH2_BIT_MASK, MAX_CHIP_SERI, &color_buf[2][0], 100, 100, 100, 100, 1, 8, 2);
    #else
    ucs1903_init(&ucs1903[0], (uint32_t *)GPIO_1903_PORT, 1ULL << GPIO_1903_DI_CH2, MAX_CHIP_SERI, &color_buf[2][0], 100, 100, 100, 100, 1, 8, 2);

    #endif
    while(1) {
        /* ------------------- Update song song ------------------- */
        for(uint8_t index_chip_parall = 0; index_chip_parall < MAX_CHIP_PARA; index_chip_parall++) {
            for(uint8_t index_chip_seri = 0; index_chip_seri < MAX_CHIP_SERI; index_chip_seri++) {
                color_buf[index_chip_parall][index_chip_seri].r = 255;
                color_buf[index_chip_parall][index_chip_seri].g = 0;
                color_buf[index_chip_parall][index_chip_seri].b = 0;
            }
        }
        ucs1903_multi_update(ucs1903, MAX_CHIP_PARA);
        delay_ms(500);
        for(uint8_t index_chip_parall = 0; index_chip_parall < MAX_CHIP_PARA; index_chip_parall++) {
            for(uint8_t index_chip_seri = 0; index_chip_seri < MAX_CHIP_SERI; index_chip_seri++) {
                color_buf[index_chip_parall][index_chip_seri].r = 0;
                color_buf[index_chip_parall][index_chip_seri].g = 255;
                color_buf[index_chip_parall][index_chip_seri].b = 0;
            }
        }
        ucs1903_multi_update(ucs1903, MAX_CHIP_PARA);
        delay_ms(500);
        for(uint8_t index_chip_parall = 0; index_chip_parall < MAX_CHIP_PARA; index_chip_parall++) {
            for(uint8_t index_chip_seri = 0; index_chip_seri < MAX_CHIP_SERI; index_chip_seri++) {
                color_buf[index_chip_parall][index_chip_seri].r = 0;
                color_buf[index_chip_parall][index_chip_seri].g = 0;
                color_buf[index_chip_parall][index_chip_seri].b = 255;
            }
        }
        ucs1903_multi_update(ucs1903, MAX_CHIP_PARA);
        delay_ms(500);
        /* ------------------- Update từng line độc lập ------------------- */
        ucs1903_single_update(ucs1903);
        delay_ms(500);
        ucs1903_single_update(ucs1903 + 1);
        delay_ms(500);
        ucs1903_single_update(ucs1903 + 2);
        delay_ms(500);
    }
}

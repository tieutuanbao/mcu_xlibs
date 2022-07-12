#ifndef __MATRIX_RGB
#define __MATRIX_RGB


/* Public includes ----------------------------------------------------------*/
#include "main.h"

/* Public defines -----------------------------------------------------------*/
//    Định nghĩa độ phân giải của ma trận
#define MATRIX_WIDTH        64
#define MATRIX_HEIGHT        32

//    Định nghĩa độ phân giải của màu
#define MATRIX_BIT_PER_PIXCEL        5

//    Định nghĩa PORT data
#define MATRIX_GPIO_DATA                GPIOA->ODR

//    Đưa chân CLK xuống mức thấp
#define MATRIX_GPIO_CLK_LOW            GPIOA->BSRR = 0x00400000;

//    Đưa chân CLK lên mức cao
#define MATRIX_GPIO_CLK_HIGH        GPIOA->BSRR = 0x00000040;

//    Định nghĩa GPIO chuyển Row
#define MATRIX_GPIO_ROW                    GPIOB->ODR

//    Đưa chân LATCH xuống mức thấp
#define MATRIX_GPIO_LAT_LOW            GPIOA->ODR = 0;

//    Đưa chân LATCH lên mức cao
#define MATRIX_GPIO_LAT_HIGH        GPIOA->ODR = 0x80;

//     Reset bộ đếm timer
#define MATRIX_RESET_TIMER(_indexBit)        TIM4->PSC = timerPSC[_indexBit];\
                                                                                TIM4->CNT = 0;

//    Tắt OE
#define MATRIX_OE_DISABLE                TIM1->BDTR = 0x00000000;

//    Cấu hình độ sáng
#define MATRIX_BRIGHTNESS_CONFIG(_brightness)    TIM1->CCR2 = (_brightness);

//    Bật OE
#define MATRIX_OE_ENABLE                TIM1->BDTR = 0x00008000;

/* Public typedef -----------------------------------------------------------*/
typedef struct {
    uint8_t indexBit;
    uint8_t indexLine;
    uint8_t indexCol;
} _MATRIX_matrixDriverParam;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} argb_color_t;
/* Export variable -----------------------------------------------------------*/
extern _MATRIX_matrixDriverParam MATRIX_matrixDriverParam;
extern uint8_t _Matrix_BufferGPIO[MATRIX_BIT_PER_PIXCEL][MATRIX_HEIGHT/2][MATRIX_WIDTH];
extern const uint16_t timerPSC[];

/* Export macro --------------------------------------------------------------*/
#define MATRIX_Driver()    /* Disable OE - Force Disable output */\
                                                MATRIX_OE_DISABLE\
                                                /* Dịch dữ liệu ra MATRIX_WIDTH lần */\
                                                for(MATRIX_matrixDriverParam.indexCol = 0; MATRIX_matrixDriverParam.indexCol < MATRIX_WIDTH; MATRIX_matrixDriverParam.indexCol++) {\
                                                    MATRIX_GPIO_DATA = _Matrix_BufferGPIO[MATRIX_matrixDriverParam.indexBit][MATRIX_matrixDriverParam.indexLine][MATRIX_matrixDriverParam.indexCol];\
                                                    MATRIX_GPIO_CLK_HIGH\
                                                }\
                                                /* Chốt dữ liệu ra IC ghi dịch */\
                                                MATRIX_GPIO_LAT_HIGH\
                                                MATRIX_GPIO_LAT_LOW\
                                                /* Switch row */\
                                                GPIOB->ODR = (MATRIX_matrixDriverParam.indexLine<<13)|(MATRIX_matrixDriverParam.indexLine>>2);\
                                                /* Counter BitPerPixcel and Scan Row*/\
                                                if(++MATRIX_matrixDriverParam.indexLine >= (MATRIX_HEIGHT/2)) {\
                                                    MATRIX_matrixDriverParam.indexLine = 0;\
                                                    ++MATRIX_matrixDriverParam.indexBit;\
                                                    MATRIX_matrixDriverParam.indexBit %= MATRIX_BIT_PER_PIXCEL; \
                                                    /* Reset Counter timer, clear flag and reconfig Prescaler */\
                                                    MATRIX_RESET_TIMER(MATRIX_matrixDriverParam.indexBit);\
                                                }\
                                                /* Bật OE */    \
                                                MATRIX_OE_ENABLE

/* Exported functions prototypes ---------------------------------------------*/
void MATRIX_Update(uint8_t _MATRIX_BufferRGB[3][MATRIX_HEIGHT][MATRIX_WIDTH]);
void MATRIX_draw_point(uint16_t x_pos, uint16_t y_pos, argb_color_t color);

#endif

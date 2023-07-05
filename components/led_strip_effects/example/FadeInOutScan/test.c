#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "port.h"
#include "LedStripEffect_FadeWipe.h"
#include "LEDStrip_effect.h"

#define LED_LENGTH  20
#define TAG     "test.c"

uint32_t tick = 0;
Color_RGB_t led_buf[LED_LENGTH];

void ColorSet_drv(uint16_t index, Color_RGB_t color) {
    led_buf[index] = color;
}

void main(){
    LEDStripEffect_Drv_t listEff = (LEDStripEffect_Drv_t){0, ColorSet_drv};
    LEDStripEffect_fadeWipe_t fadeCW[2];
    LEDStripEffect_fadeWipe_t fadeCCW[2];
    /* arg0 = con trỏ hiệu ứng, arg1 = tick bắt đầu hiệu ứng, arg3 = thời gian chạy hiệu ứng(ms), arg4 = Buffer dải led, arg5 = độ dài LED, arg5 = dải màu gradient áp dụng cho hiệu ứng, arg6 = số lượng màu trong dải */
    LEDStripEffect_fadeWipe_init(&fadeCW[0], tick, 10000, led_buf, LED_LENGTH, (Color_RGB_t []){COLOR_BLACK, COLOR_BLACK}, 2, (Color_RGB_t []){COLOR_RED, COLOR_GREEN}, 2, true);
    LEDStripEffect_fadeWipe_init(&fadeCCW[0], tick + 10000, 10000, led_buf, LED_LENGTH, (Color_RGB_t []){COLOR_RED, COLOR_GREEN}, 2, (Color_RGB_t []){COLOR_VIOLET, COLOR_ROSE}, 2, false);
    LEDStripEffect_fadeWipe_init(&fadeCW[1], tick + 20000, 10000, led_buf, LED_LENGTH, (Color_RGB_t []){COLOR_VIOLET, COLOR_ROSE}, 2, (Color_RGB_t []){COLOR_CYAN, COLOR_YELLOW}, 2, true);
    LEDStripEffect_fadeWipe_init(&fadeCCW[1], tick + 30000, 10000, led_buf, LED_LENGTH, (Color_RGB_t []){COLOR_CYAN, COLOR_YELLOW}, 2, (Color_RGB_t []){COLOR_BLACK, COLOR_BLACK}, 2, false);
    LEDStripEffect_addEffect((LEDStripEffect_t *)&listEff, (LEDStripEffect_t *)&fadeCW[0]);
    LEDStripEffect_addEffect((LEDStripEffect_t *)&fadeCW[0], (LEDStripEffect_t *)&fadeCCW[0]);
    LEDStripEffect_addEffect((LEDStripEffect_t *)&fadeCCW[0], (LEDStripEffect_t *)&fadeCW[1]);
    LEDStripEffect_addEffect((LEDStripEffect_t *)&fadeCW[1], (LEDStripEffect_t *)&fadeCCW[1]);
    {
        for(;; tick++) {
            LEDStripEffect_State_t ret = LEDStripEffect_run(&listEff, tick);
            /* Test in màu */
            for(uint16_t idx_led = 0; idx_led < LED_LENGTH; idx_led++){
                printf("\x1b[38;2;%d;%d;%dm#", led_buf[idx_led].R, led_buf[idx_led].G, led_buf[idx_led].B);
            }
            if(ret == LEDStrip_effectState_stop) {
                break;
            }
            usleep(300);
            printf("\r");
        }
        printf("\n");
        printf("\033[0m");
        printf("Tick stop at: %d\n", tick);
    }
}

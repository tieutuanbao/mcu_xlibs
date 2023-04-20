#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "port.h"
#include "LedStripEffect_Fade.h"
#include "LEDStrip_effect.h"

#define LED_LENGTH  20
#define TAG     "test.c"

uint32_t tick = 0;
Color_RGB_t led_buf[LED_LENGTH];

void main(){
    LEDStripEffect_t effectPar;
    LEDStripEffect_fade_t fadeInEff;
    LEDStripEffect_fade_t fadeOutEff;
    Color_RGB_t fadeInColorStrip[] = {COLOR_BLACK, COLOR_GREEN};
    Color_RGB_t fadeOutColorStrip[] = {COLOR_GREEN, COLOR_BLACK};
    /* init effect */
    LEDStripEffect_init(&effectPar);
    /* arg0 = con trỏ hiệu ứng, arg1 = tick bắt đầu hiệu ứng, arg3 = thời gian chạy hiệu ứng(ms), arg4 = Buffer dải led, arg5 = độ dài LED, arg5 = dải màu gradient áp dụng cho hiệu ứng, arg6 = số lượng màu trong dải */
    LEDStripEffect_fade_init(&fadeInEff, tick, 1000, led_buf, LED_LENGTH, fadeInColorStrip, 2);
    LEDStripEffect_fade_init(&fadeOutEff, tick + 1000, 1000, led_buf, LED_LENGTH, fadeOutColorStrip, 2);
    LEDStripEffect_addEffect(&effectPar, (LEDStripEffect_t *)&fadeInEff);
    LEDStripEffect_addEffect((LEDStripEffect_t *)(&fadeInEff), (LEDStripEffect_t *)&fadeOutEff);
    {
        for(;; tick++){
            LEDStripEffect_State_t ret = effectPar.exec(&effectPar, tick);
            printf("Color: %d;%d;%d", led_buf[0].R, led_buf[0].G, led_buf[0].B);
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
        printf("0x%X\n", effectPar.effects);
    }
}


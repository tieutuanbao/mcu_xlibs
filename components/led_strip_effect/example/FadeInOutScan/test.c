#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "port.h"
#include "LedStripEffect_FadeInWipe.h"
#include "LedStripEffect_FadeOutWipe.h"
#include "LEDStrip_effect.h"

#define LED_LENGTH  20
#define TAG     "test.c"

uint32_t tick = 0;
Color_RGB_t led_buf[LED_LENGTH];


void main(){
    LEDStripEffect_t effectPar;
    LEDStripEffect_fadeInWipe_t fadeInCW;
    LEDStripEffect_fadeOutWipe_t fadeOutCW;
    LEDStripEffect_fadeInWipe_t fadeInCCW;
    LEDStripEffect_fadeOutWipe_t fadeOutCCW;
    Color_RGB_t fadeInColorStripCW[] = {COLOR_GREEN, COLOR_GREEN};
    Color_RGB_t fadeOutColorStripCW[] = {COLOR_GREEN, COLOR_GREEN};
    Color_RGB_t fadeInColorStripCCW[] = {COLOR_RED, COLOR_RED};
    Color_RGB_t fadeOutColorStripCCW[] = {COLOR_RED, COLOR_RED};
    /* init effect */
    LEDStripEffect_init(&effectPar);
    /* arg0 = con trỏ hiệu ứng, arg1 = tick bắt đầu hiệu ứng, arg3 = thời gian chạy hiệu ứng(ms), arg4 = Buffer dải led, arg5 = độ dài LED, arg5 = dải màu gradient áp dụng cho hiệu ứng, arg6 = số lượng màu trong dải */
    LEDStripEffect_fadeInWipe_init(&fadeInCW, tick, 2000, led_buf, LED_LENGTH, fadeInColorStripCW, 2, true);
    LEDStripEffect_fadeOutWipe_init(&fadeOutCW, tick + 2000, 2000, led_buf, LED_LENGTH, fadeOutColorStripCW, 2, false);
    LEDStripEffect_fadeInWipe_init(&fadeInCCW, tick + 2000 + 2000, 2000, led_buf, LED_LENGTH, fadeInColorStripCCW, 2, false);
    LEDStripEffect_fadeOutWipe_init(&fadeOutCCW,  tick + 2000 + 2000 + 2000, 2000, led_buf, LED_LENGTH, fadeOutColorStripCCW, 2, true);
    LEDStripEffect_addEffect(&effectPar, (LEDStripEffect_t *)&fadeInCW);
    LEDStripEffect_addEffect((LEDStripEffect_t *)&fadeInCW, (LEDStripEffect_t *)&fadeOutCW);
    LEDStripEffect_addEffect((LEDStripEffect_t *)&fadeOutCW, (LEDStripEffect_t *)&fadeInCCW);
    LEDStripEffect_addEffect((LEDStripEffect_t *)&fadeInCCW, (LEDStripEffect_t *)&fadeOutCCW);
    {
        for(;; tick++){
            LEDStripEffect_State_t ret = effectPar.exec(&effectPar, tick);
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
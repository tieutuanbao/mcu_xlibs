#include <string.h>
#include <stdio.h>
#include "port.h"
#include "meteor.h"

#define LED_LENGTH  100
#define TAG     "test.c"

rgb_color_t led_buf[LED_LENGTH];
strip_color_t meteor_color[3];

void main(){
    meteor_color[3].value = (rgb_color_t){255, 0, 0};
    meteor_color[3].len = 1;
    meteor_color[2].value = (rgb_color_t){100, 0, 0};
    meteor_color[2].len = 30;
    meteor_color[1].value = (rgb_color_t){255, 255, 255};
    meteor_color[1].len = 2;
    meteor_color[0].value = (rgb_color_t){255, 255, 255};
    meteor_color[0].len = 10;
    /* Preview */
    {
        for(int32_t update_interval = -10; update_interval < 50; update_interval++){
            memset(led_buf, 0, sizeof(led_buf));
            meteor_draw(led_buf, LED_LENGTH, update_interval, meteor_color, 4);
            for(uint16_t idx_led = 0; idx_led < LED_LENGTH; idx_led++){
                printf("\x1b[38;2;%d;%d;%dm#", led_buf[idx_led].r, led_buf[idx_led].g, led_buf[idx_led].b,' '*21);
            }
            usleep(20000);
            printf("\r");
            // printf("\n");
        }
        printf("\033[0m");
    }
}
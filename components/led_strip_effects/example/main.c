#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "port.h"
#include "LedStripEffects_fade.h"
#include "LedStripEffects_fadeWipe.h"
#include "LEDStripEffects.h"

#define LED_LENGTH  20

typedef enum {
    FadeIn,
    FadeOut,
    FadeCW,
    FadeCCW,
    MeteorCW,
    MeteorCCW,
    MeteorToMid,
    MeteorToSide,
    EFFECT_MAX
} effectsList_t;

uint32_t virtualTick = 0;
Color_RGB_t ledStrip_buf[LED_LENGTH];
void *effect = 0;

void setColorAt(uint16_t indexLed, Color_RGB_t color) {
    ledStrip_buf[indexLed] = color;
}
Color_RGB_t getColorAt(uint16_t indexLed) {
    return ledStrip_buf[indexLed];
}

void main(){
    Color_RGB_t fadeColorStrip[] = {COLOR_BLACK, COLOR_GREEN, COLOR_ORANGE, COLOR_AZURE, COLOR_ROSE, COLOR_VIOLET, COLOR_BLACK};
    effectsList_t effectIndex = FadeIn;
    while(1) {
        if(effect == 0) {
            switch(effectIndex++) {
                case FadeIn: {
                    effect = malloc(sizeof(LEDStripEffects_fade_t));
                    LEDStripEffects_fade_init(effect, 3000, 0, LED_LENGTH, fadeColorStrip, 2);
                    break;
                }
                case FadeOut: {
                    effect = malloc(sizeof(LEDStripEffects_fade_t));
                    LEDStripEffects_fade_init(effect, 3000, 0, LED_LENGTH, fadeColorStrip + 5, 2);
                    break;
                }
                case FadeCW: {
                    effect = malloc(sizeof(LEDStripEffects_fadeWipe_t));
                    LEDStripEffects_fadeWipe_init(effect, 50, 0, LED_LENGTH - 1, fadeColorStrip + 5, 2, fadeColorStrip + 1, 2, 1);
                    break;
                }
                case FadeCCW: {
                    effect = malloc(sizeof(LEDStripEffects_fadeWipe_t));
                    LEDStripEffects_fadeWipe_init(effect, 50, 0, LED_LENGTH - 1, fadeColorStrip + 1, 2, fadeColorStrip + 3, 2, 0);
                    break;
                }
                default: {
                    return;
                }
            }
        }
        else {
            if(LEDStripEffects_run(effect, setColorAt, getColorAt) == LEDStripEffects_state_STOP) {
                free(effect);
                effect = 0;
            }
        }

        /* Test in màu */
        printf("\e[?25l"); // hide cursor
        for(uint16_t idx_led = 0; idx_led < LED_LENGTH; idx_led++){
            printf("\x1b[38;2;%d;%d;%dm#", ledStrip_buf[idx_led].R, ledStrip_buf[idx_led].G, ledStrip_buf[idx_led].B);
        }
        printf("\e[?25h"); // enable cursor
        printf("\r");
        virtualTick++;
        usleep(1000);
    }
}

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "LEDSingleEffects_fade.h"
#include "LEDSingleEffects_fadeWipe.h"

#define MAX_LED_BUFFER  50

/* Danh sách hiệu ứng */
typedef enum {
    FadeCW,
    FadeCCW,
    FadeIn,
    FadeOut,
    FadeOutToIn,
    FadeInToOut,
} effectsList_t;

/* Buffer LED */
uint8_t ledBuffer[MAX_LED_BUFFER];

/* Tick counter */
uint32_t virtualTick = 0;

effectsList_t effectIndex = FadeCW;

void ledBuffer_setBrightness(uint32_t indexLED, uint8_t brightness) {
    ledBuffer[indexLED] = brightness;
}

void *effect = 0;

void main() {
    while(true) {
        if(effect == 0) {
            switch(effectIndex) {
                case FadeCW: {
                    effect = malloc(sizeof(LedSingleEffects_fadeWipe_t));
                    LEDSingleEffects_fadeWipe_init((LedSingleEffects_fadeWipe_t *)effect, MAX_LED_BUFFER, 0, 255, true, 2000, virtualTick);
                    break;
                }
                case FadeCCW: {
                    effect = malloc(sizeof(LedSingleEffects_fadeWipe_t));
                    LEDSingleEffects_fadeWipe_init((LedSingleEffects_fadeWipe_t *)effect, MAX_LED_BUFFER, 255, 0, false, 2000, virtualTick);
                    break;
                }
                case FadeIn: {
                    effect = malloc(sizeof(LedSingleEffects_fade_t));
                    LEDSingleEffects_fade_init((LedSingleEffects_fade_t *)effect, MAX_LED_BUFFER, 0, 255, 2000, virtualTick);
                    break;
                }
                case FadeOut: {
                    effect = malloc(sizeof(LedSingleEffects_fade_t));
                    LEDSingleEffects_fade_init((LedSingleEffects_fade_t *)effect, MAX_LED_BUFFER, 255, 0, 2000, virtualTick);
                    break;
                }
                default: {
                    return;
                }
            }
        }
        if(LEDSingleEffects_run(effect, ledBuffer_setBrightness, virtualTick) == LEDSingle_effectState_STOP) {
            effectIndex++;
            free(effect);
            effect = 0;
        }
        /* Mô phỏng LED */
        for(uint16_t indexLED = 0; indexLED < MAX_LED_BUFFER; indexLED++){
            printf("\x1b[38;2;%dm#", ledBuffer[indexLED]);
        }
        printf("\r");
        virtualTick++;
        usleep(1000);
    }
}
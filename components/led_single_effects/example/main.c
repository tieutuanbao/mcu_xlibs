#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "LEDSingleEffects_fade.h"
#include "LEDSingleEffects_fadeWipe.h"
#include "LEDSingleEffects_meteor.h"
#include "LEDSingleEffects_meteorToMid.h"
#include "LEDSingleEffects_meteorToSide.h"

#define MAX_LED_BUFFER  20

/* Danh sách hiệu ứng */
typedef enum {
    FadeCW,
    FadeCCW,
    FadeIn,
    FadeOut,
    MeteorCW,
    MeteorCCW,
    MeteorToMid,
    MeteorToSide,
    EFFECT_MAX
} effectsList_t;

/* Buffer LED */
uint8_t ledBuffer[MAX_LED_BUFFER];

/* Tick counter */
uint32_t virtualTick = 0;

effectsList_t effectIndex = FadeCCW;

void ledBuffer_setBrightness(uint32_t indexLED, uint8_t brightness) {
    ledBuffer[indexLED] = brightness;
}

void *effect = 0;

void main() {
    effect = 0;
    int32_t offsetMeteor = -9;
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
                    LEDSingleEffects_fadeWipe_init((LedSingleEffects_fadeWipe_t *)effect, MAX_LED_BUFFER, 0, 255, false, 2000, virtualTick);
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
                case MeteorCW: {
                    effect = malloc(sizeof(LedSingleEffects_meteor_t));
                    LEDSingleEffects_meteor_init((LedSingleEffects_meteor_t *)effect, MAX_LED_BUFFER, 10, 30, 255, true, 2000, virtualTick);
                    break;
                }
                case MeteorCCW: {
                    effect = malloc(sizeof(LedSingleEffects_meteor_t));
                    LEDSingleEffects_meteor_init((LedSingleEffects_meteor_t *)effect, MAX_LED_BUFFER, 10, 30, 255, false, 2000, virtualTick);
                    break;
                }
                case MeteorToMid: {
                    effect = malloc(sizeof(LedSingleEffects_meteorToMid_t));
                    LEDSingleEffects_meteorToMid_init((LedSingleEffects_meteorToMid_t *)effect, MAX_LED_BUFFER, 10, 30, 255, 2000, virtualTick);
                    break;
                }
                case MeteorToSide: {
                    effect = malloc(sizeof(LedSingleEffects_meteorToSide_t));
                    LEDSingleEffects_meteorToSide_init((LedSingleEffects_meteorToSide_t *)effect, MAX_LED_BUFFER, 10, 30, 255, 2000, virtualTick);
                    break;
                }
                case EFFECT_MAX: {
                    return;
                }
            }
        }
        for(uint32_t indexLED = 0; indexLED < MAX_LED_BUFFER; indexLED++) {
            ledBuffer_setBrightness(indexLED, 0);
        }
        if(LEDSingleEffects_run(effect, ledBuffer_setBrightness, virtualTick) == LEDSingle_effectState_STOP) {
            effectIndex++;
            free(effect);
            effect = 0;
        }
        /* Mô phỏng LED */
        printf("\e[?25l"); // hide cursor
        for(uint16_t indexLED = 0; indexLED < MAX_LED_BUFFER; indexLED++) {
            printf("\x1b[38;2;%dm#", ledBuffer[indexLED]);
        }
        printf("\e[?25h"); // enable cursor
        printf("\n");
        virtualTick++;
        usleep(1000);
    }
}
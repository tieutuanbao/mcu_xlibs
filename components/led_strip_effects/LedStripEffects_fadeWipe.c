#include "LedStripEffects_fadeWipe.h"
#include <stdlib.h>

static LEDStripEffects_state_t LEDStripEffects_fadeWipe_exec(
        LEDStripEffects_fadeWipe_t *eff,
        void (*setPixelAt)(uint16_t index, Color_RGB_t color)
    ) {
    Color_RGB_t startColor = {0, 0, 0};
    Color_RGB_t currentColor = {0, 0, 0};
    int16_t indexLed = 0;

    if(eff->dir) {
        indexLed = eff->base.limit.bot;
        if(eff->base.indexStep >= eff->stepPerLed) {
            eff->base.indexStep = 0;
            if(eff->indexLed < eff->base.limit.top) {
                eff->indexLed++;
            }
            else {
                return LEDStripEffects_state_STOP;
            }
        }
    }
    else {
        indexLed = eff->base.limit.top;
        if(eff->base.indexStep >= eff->stepPerLed) {
            eff->base.indexStep = 0;
            if(eff->indexLed > eff->base.limit.bot) {
                eff->indexLed--;
            }
            else {
                return LEDStripEffects_state_STOP;
            }
        }
    }
    while(1) {
        if(eff->dir) {
            if(indexLed > eff->indexLed) {
                break;
            }
        }
        else {
            if(indexLed < eff->indexLed) {
                break;
            }
        }
        startColor = LEDStripEffect_getColorGradient(indexLed, eff->base.limit.top - eff->base.limit.bot, eff->stripColor.start.color, eff->stripColor.start.length); // Màu hiện tại của LED
        currentColor = LEDStripEffect_getColorGradient(indexLed, eff->base.limit.top - eff->base.limit.bot, eff->stripColor.stop.color, eff->stripColor.stop.length); // Màu cuối cùng sau thay đổi
        if(indexLed == eff->indexLed) {
            currentColor = LEDStripEffect_getColorGradient(eff->base.indexStep, eff->stepPerLed, (Color_RGB_t []){startColor, currentColor}, 2);
        }
        setPixelAt(indexLed, currentColor);
        
        if(eff->dir) {
            indexLed++;
        }
        else {
            indexLed--;
        }
    }

    eff->base.indexStep++;
    return LEDStripEffects_state_RUNNING;
}

/**
 * @brief 
 * 
 * @param eff Hàm khởi tạo một hiệu ứng Fade
 * @param nowTick Tick hiện tại millisecond
 * @param runInterval Thời gian chạy millisecond, không nhỏ hơn số lượng LED
 * @param colorStrip Buffer dải màu Gradient
 * @param colorCount Số lượng màu trong dải
 * @return LEDStripEffects_fadeWipe_t* 
 */
LEDStripEffects_fadeWipe_t *LEDStripEffects_fadeWipe_init(
        LEDStripEffects_fadeWipe_t *eff,
        uint32_t stepPerLed,
        uint32_t limitBot, uint32_t limitTop,
        Color_RGB_t *startColor, uint8_t startColorLength,
        Color_RGB_t *stopColor, uint8_t stopColorLength,
        bool dir) {
    eff->base.exec = (LEDStripEffects_exec_t)LEDStripEffects_fadeWipe_exec;
    eff->base.state = LEDStripEffects_state_RUNNING;
    eff->base.limit.bot = limitBot;
    eff->base.limit.top = limitTop;

    eff->stepPerLed = stepPerLed;
    eff->stripColor.start.color = startColor;
    eff->stripColor.start.length = startColorLength;
    eff->stripColor.stop.color = stopColor;
    eff->stripColor.stop.length = stopColorLength;
    eff->dir = dir;
    if(eff->dir) {
        eff->indexLed = eff->base.limit.bot;
    }
    else {
        eff->indexLed = eff->base.limit.top;
    }
    return eff;
}

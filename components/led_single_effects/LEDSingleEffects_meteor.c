#include "LEDSingleEffects_meteor.h"
#include <stdio.h>

static LEDSingleEffects_state_t LEDSingleEffects_meteor_run(LedSingleEffects_meteor_t *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick) {
    int32_t indexLED = 0;
    int32_t offset = 0;
    uint32_t nextLEDInterval = 0;

    nowTick = nowTick - effect->startTick;
    if(nowTick >= effect->runInterval) {
        return LEDSingle_effectState_STOP;
    }
    nextLEDInterval = effect->runInterval / (effect->led.count + effect->meteorLength * 2 - 2);
    /* Điểm sáng nhất của sao băng */
    effect->led.now = nowTick / nextLEDInterval;
    if(effect->dir == false) {
        effect->led.now = effect->led.count - effect->led.now;
        offset = effect->led.now - 1;
    }
    else {
        offset = (effect->led.now - effect->meteorLength) + 1;
    }
    if(effect->dir == false) {
        LEDSingleEffects_meteorDraw(offset, effect->meteorLength, effect->endBrightness, effect->beginBrightness, 0, effect->led.count, drv);
        if(offset == -effect->meteorLength) {
            return LEDSingle_effectState_STOP;
        }
    }
    else {
        LEDSingleEffects_meteorDraw(offset, effect->meteorLength, effect->beginBrightness, effect->endBrightness, 0, effect->led.count, drv);
        if(offset == effect->led.count) {
            return LEDSingle_effectState_STOP;
        }
    }
    return LEDSingle_effectState_RUNNING;
}

/**
 * @brief Hàm khởi tạo hiệu ứng meteor cho LED
 * 
 * @param effect Con trỏ đến hiệu ứng
 * @param LEDCount Số lượng LED, luôn phải lớn hơn 0
 * @param runInterval Thời gian chạy
 * @param nowTick Tick hiện tại
 */
void LEDSingleEffects_meteor_init(
        LedSingleEffects_meteor_t *effect,
        uint32_t LEDCount, uint32_t meteorLength, uint8_t beginBrightness, uint8_t endBrightness, bool dir,
        LEDSingleEffect_tick_t runInterval,
        LEDSingleEffect_tick_t nowTick
    )
{
    effect->startTick = nowTick;
    effect->led.count = LEDCount;
    effect->meteorLength = meteorLength;
    effect->beginBrightness = beginBrightness;
    effect->endBrightness = endBrightness;
    effect->dir = dir;
    if(dir) {
        effect->led.now = 0;
    }
    else {
        effect->led.now = LEDCount - 1;
    }
    effect->runInterval = runInterval;
    effect->exec = (LEDSingleEffects_exec_t)LEDSingleEffects_meteor_run;
}
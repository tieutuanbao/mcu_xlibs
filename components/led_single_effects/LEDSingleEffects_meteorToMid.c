#include "LEDSingleEffects_meteorToMid.h"
#include <stdio.h>

static LEDSingleEffects_state_t LEDSingleEffects_meteorToMid_run(LedSingleEffects_meteorToMid_t *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick) {
    int32_t indexLED = 0;
    int32_t offsetBot = 0;
    int32_t offsetTop = 0;
    uint32_t lenBot = effect->led.count / 2;
    uint32_t lenTop = effect->led.count - lenBot;
    uint32_t nextLEDInterval = 0;

    nowTick = nowTick - effect->startTick;
    if(nowTick >= effect->runInterval) {
        return LEDSingle_effectState_STOP;
    }
    nextLEDInterval = effect->runInterval / ((effect->led.count / 2) + effect->meteorLength * 2 - 1);
    /* Điểm sáng nhất của sao băng */
    effect->led.now = nowTick / nextLEDInterval;
    offsetBot = (effect->led.now - effect->meteorLength) + 1;
    offsetTop = (effect->led.count - effect->led.now) - 1;
    LEDSingleEffects_meteorDraw(offsetBot, effect->meteorLength, effect->beginBrightness, effect->endBrightness, 0, lenBot, drv);
    LEDSingleEffects_meteorDraw(offsetTop, effect->meteorLength, effect->endBrightness, effect->beginBrightness, effect->led.count - effect->meteorLength, effect->led.count - 1, drv);
    if(offsetTop <= (offsetBot - (int32_t)effect->meteorLength)) {
        return LEDSingle_effectState_STOP;
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
void LEDSingleEffects_meteorToMid_init(
        LedSingleEffects_meteorToMid_t *effect,
        uint32_t LEDCount, uint32_t meteorLength, uint8_t beginBrightness, uint8_t endBrightness,
        LEDSingleEffect_tick_t runInterval,
        LEDSingleEffect_tick_t nowTick
    )
{
    effect->startTick = nowTick;
    effect->led.count = LEDCount;
    effect->meteorLength = meteorLength;
    effect->beginBrightness = beginBrightness;
    effect->endBrightness = endBrightness;
    effect->led.now = 0;
    effect->runInterval = runInterval;
    effect->exec = (LEDSingleEffects_exec_t)LEDSingleEffects_meteorToMid_run;
}
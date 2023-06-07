#include "LEDSingleEffects_meteorToSide.h"
#include <stdio.h>

static LEDSingleEffects_state_t LEDSingleEffects_meteorToSide_run(LedSingleEffects_meteorToSide_t *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick) {
    int32_t indexLED = 0;
    int32_t offsetBot = 0;
    int32_t offsetTop = 0;
    uint32_t nextLEDInterval = 0;

    nowTick = nowTick - effect->startTick;
    if(nowTick >= effect->runInterval) {
        return LEDSingle_effectState_STOP;
    }
    nextLEDInterval = effect->runInterval / ((effect->led.count / 2) + effect->meteorLength * 2 - 1);
    effect->led.now = nowTick / nextLEDInterval;
    offsetBot = (effect->led.count / 2) - effect->led.now;
    offsetTop = ((effect->led.count / 2) + effect->led.now) - effect->meteorLength;
    LEDSingleEffects_meteorDraw(offsetBot, effect->meteorLength, effect->endBrightness, effect->beginBrightness, 0, effect->led.count / 2, drv);
    LEDSingleEffects_meteorDraw(offsetTop, effect->meteorLength, effect->beginBrightness, effect->endBrightness, effect->led.count / 2, effect->led.count, drv);
    if(offsetTop >= effect->led.count) {
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
void LEDSingleEffects_meteorToSide_init(
        LedSingleEffects_meteorToSide_t *effect,
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
    effect->exec = (LEDSingleEffects_exec_t)LEDSingleEffects_meteorToSide_run;
}
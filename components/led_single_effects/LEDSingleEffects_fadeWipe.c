#include "LEDSingleEffects_fadeWipe.h"

LEDSingleEffects_state_t LEDSingleEffects_fadeWipe_run(LedSingleEffects_fadeWipe_t *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick) {
    nowTick = nowTick - effect->startTick;
    if(nowTick >= effect->runInterval) {
        return LEDSingle_effectState_STOP;
    }
    uint32_t nextLEDInterval = effect->runInterval / effect->led.count;
    if(effect->dirWipe == true) {
        drv(nowTick / nextLEDInterval, effect->beginBrightness + (int16_t)(nowTick % nextLEDInterval) * (int16_t)(effect->endBrightness - effect->beginBrightness) / (int16_t)nextLEDInterval);
    }
    else {
        drv(effect->led.count - (nowTick / nextLEDInterval), effect->beginBrightness + (int16_t)(nowTick % nextLEDInterval) * (int16_t)(effect->endBrightness - effect->beginBrightness) / (int16_t)nextLEDInterval);
    }
    return LEDSingle_effectState_RUNNING;
}

/**
 * @brief Hàm khởi tạo hiệu ứng Fade cho LED
 * 
 * @param effect Con trỏ đến hiệu ứng
 * @param LEDCount Số lượng LED, luôn phải lớn hơn 0
 * @param runInterval Thời gian chạy
 * @param nowTick Tick hiện tại
 */
void LEDSingleEffects_fadeWipe_init(
        LedSingleEffects_fadeWipe_t *effect,
        uint32_t LEDCount, uint8_t beginBrightness, uint8_t endBrightness, bool dirWipe,
        LEDSingleEffect_tick_t runInterval,
        LEDSingleEffect_tick_t nowTick
    )
{
    effect->startTick = nowTick;
    effect->led.count = LEDCount;
    effect->led.now = 0;
    effect->beginBrightness = beginBrightness;
    effect->endBrightness = endBrightness;
    effect->dirWipe = dirWipe;
    effect->runInterval = runInterval;
    effect->exec = (LEDSingleEffects_exec_t)LEDSingleEffects_fadeWipe_run;
}
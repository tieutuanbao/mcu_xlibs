#include "LEDSingleEffects_fade.h"

static LEDSingleEffects_state_t LEDSingleEffects_fade_run(LedSingleEffects_fade_t *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick) {
    nowTick = nowTick - effect->startTick;
    if(nowTick >= effect->runInterval) {
        return LEDSingle_effectState_STOP;
    }
    uint32_t nextLEDInterval = effect->runInterval / effect->led.count;
    for(uint32_t indexLED = 0; indexLED < effect->led.count; indexLED++) {
        drv(indexLED, effect->beginBrightness + (int32_t)(nowTick) * (int32_t)(effect->endBrightness - effect->beginBrightness) / (int32_t)effect->runInterval);
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
void LEDSingleEffects_fade_init(
        LedSingleEffects_fade_t *effect,        
        uint32_t LEDCount, uint8_t beginBrightness, uint8_t endBrightness,
        LEDSingleEffect_tick_t runInterval,
        LEDSingleEffect_tick_t nowTick
    )
{
    effect->startTick = nowTick;
    effect->led.count = LEDCount;
    effect->beginBrightness = beginBrightness;
    effect->endBrightness = endBrightness;
    effect->runInterval = runInterval;
    effect->exec = (LEDSingleEffects_exec_t)LEDSingleEffects_fade_run;
}
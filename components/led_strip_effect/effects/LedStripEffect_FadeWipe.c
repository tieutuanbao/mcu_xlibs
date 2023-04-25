#include "LedStripEffect_FadeWipe.h"
#include <stdlib.h>

static LEDStripEffect_State_t LEDStripEffect_fadeWipe_exec(LEDStripEffect_fadeWipe_t *eff, void (*pixelAt_set)(uint16_t index, Color_RGB_t color), LedStripEffect_tick_t currentTick) {
    LEDStripEffect_State_t ret = LEDStrip_effectState_running;
    currentTick = currentTick - eff->base.lastTick;
    if(currentTick < 0) {
        currentTick = 1;
    }
    if((currentTick >= eff->base.runInterval) || (eff->base.runInterval == 0) || (eff->led.at == 0) || (eff->led.count == 0)) {
        eff->base.runInterval = currentTick;
        return LEDStrip_effectState_stop;
    }

    LedStripEffect_tick_t tickPerLed = eff->base.runInterval / eff->led.count;
    LedStripEffect_tick_t currentTickLed = currentTick % tickPerLed;
    if(tickPerLed <= 0) {
        tickPerLed = 1;
    }
    if(currentTickLed > tickPerLed) {
        currentTickLed = tickPerLed;
    }
    Color_RGB_t startColor = LEDStripEffect_getColorGradient(eff->indexLed, eff->led.count, eff->startColor.at, eff->startColor.count);
    Color_RGB_t stopColor = LEDStripEffect_getColorGradient(eff->indexLed, eff->led.count, eff->stopColor.at, eff->stopColor.count);
    Color_RGB_t currentColor = LEDStripEffect_getColorGradient(currentTickLed, tickPerLed, (Color_RGB_t []){startColor, stopColor}, 2);
    pixelAt_set(eff->indexLed, currentColor);
    if(currentTickLed >= (tickPerLed - 1)) {
        if(eff->dir) {
            eff->indexLed++;
            if(eff->indexLed == eff->led.count) {
                return LEDStrip_effectState_stop;
            }
        }
        else {
            eff->indexLed--;
            if(eff->indexLed < 0) {
                return LEDStrip_effectState_stop;
            }
        }
    }
    return ret;
}

/**
 * @brief 
 * 
 * @param eff Hàm khởi tạo một hiệu ứng Fade
 * @param currentTick Tick hiện tại millisecond
 * @param runInterval Thời gian chạy millisecond, không nhỏ hơn số lượng LED
 * @param ledBuffer Buffer LED
 * @param ledCount Số mắt LED
 * @param colorStrip Buffer dải màu Gradient
 * @param colorCount Số lượng màu trong dải
 * @return LEDStripEffect_fadeWipe_t* 
 */
LEDStripEffect_fadeWipe_t *LEDStripEffect_fadeWipe_init(LEDStripEffect_fadeWipe_t *eff, LedStripEffect_tick_t currentTick, uint32_t runInterval, Color_RGB_t *ledBuffer, uint16_t ledCount, 
                                                            Color_RGB_t *startColor, uint8_t startColorCount, Color_RGB_t *stopColor, uint8_t stopColorCount, bool dir) {
    if(ledCount == 0) {
        return (LEDStripEffect_fadeWipe_t *)0;
    }
    eff->base.effects = 0;
    eff->base.exec = (LEDStripEffect_exec_t)LEDStripEffect_fadeWipe_exec;
    eff->base.lastTick = currentTick;
    eff->base.runInterval = runInterval;

    eff->led.at = ledBuffer;
    eff->led.count = ledCount;
    eff->startColor.at = startColor;
    eff->startColor.count = startColorCount;
    eff->stopColor.at = stopColor;
    eff->stopColor.count = stopColorCount;
    eff->dir = dir;
    if(eff->dir) {
        eff->indexLed = 0;
    }
    else {
        eff->indexLed = eff->led.count - 1;
    }
    return eff;
}

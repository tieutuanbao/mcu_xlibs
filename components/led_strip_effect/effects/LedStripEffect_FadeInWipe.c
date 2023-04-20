#include "LedStripEffect_FadeInWipe.h"
#include <stdlib.h>

static LEDStripEffect_State_t LEDStripEffect_fadeInWipe_exec(LEDStripEffect_fadeInWipe_t *eff, LedStripEffect_tick_t currentTick) {
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
    Color_RGB_t currentColor = LEDStripEffect_getColorGradient(eff->indexLed, eff->led.count, eff->stripColor.at, eff->stripColor.count);
    eff->led.at[eff->indexLed].R = currentTickLed * (uint32_t)currentColor.R / (tickPerLed - 1);
    eff->led.at[eff->indexLed].G = currentTickLed * (uint32_t)currentColor.G / (tickPerLed - 1);
    eff->led.at[eff->indexLed].B = currentTickLed * (uint32_t)currentColor.B / (tickPerLed - 1);
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
 * @param colorBuffer Buffer dải màu Gradient
 * @param colorCount Số lượng màu trong dải
 * @return LEDStripEffect_fadeInWipe_t* 
 */
LEDStripEffect_fadeInWipe_t *LEDStripEffect_fadeInWipe_init(LEDStripEffect_fadeInWipe_t *eff, LedStripEffect_tick_t currentTick, uint32_t runInterval, Color_RGB_t *ledBuffer, uint16_t ledCount, Color_RGB_t *colorBuffer, uint8_t colorCount, bool dir) {
    if(ledCount == 0) {
        return (LEDStripEffect_fadeInWipe_t *)0;
    }
    eff->base.effects = 0;
    eff->base.exec = (LEDStripEffect_exec_t)LEDStripEffect_fadeInWipe_exec;
    eff->base.lastTick = currentTick;
    eff->base.runInterval = runInterval;

    eff->led.at = ledBuffer;
    eff->led.count = ledCount;
    eff->stripColor.at = colorBuffer;
    eff->stripColor.count = colorCount;
    eff->dir = dir;
    if(eff->dir) {
        eff->indexLed = 0;
    }
    else {
        eff->indexLed = eff->led.count - 1;
    }
    return eff;
}

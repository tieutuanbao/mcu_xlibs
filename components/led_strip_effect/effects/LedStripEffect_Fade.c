#include "LedStripEffect_Fade.h"

static LEDStripEffect_State_t LEDStripEffect_fade_exec(LEDStripEffect_fade_t *eff, LedStripEffect_tick_t currentTick) {
    LEDStripEffect_State_t ret = LEDStrip_effectState_running;
    currentTick = currentTick - eff->base.lastTick;
    if((currentTick < 0) || (currentTick >= eff->base.runInterval) || (eff->base.runInterval == 0) || (eff->led.at == 0) || (eff->led.count == 0)) {
        currentTick = 1;
        eff->base.runInterval = 1;
        ret = LEDStrip_effectState_stop;
    }
    eff->led.at[0] = LEDStripEffect_getColorGradient(currentTick, eff->base.runInterval, eff->stripColor.at, eff->stripColor.count);
    for(uint16_t indexLED = 1; indexLED < eff->led.count; indexLED++) {
        eff->led.at[indexLED] = eff->led.at[0];
    }
    return ret;
}

/**
 * @brief 
 * 
 * @param eff Hàm khởi tạo một hiệu ứng Fade
 * @param currentTick Tick hiện tại millisecond
 * @param runInterval Thời gian chạy millisecond
 * @param ledBuffer Buffer LED
 * @param ledCount Số mắt LED
 * @param colorBuffer Buffer dải màu Gradient
 * @param colorCount Số lượng màu trong dải
 * @return LEDStripEffect_fade_t* 
 */
LEDStripEffect_fade_t *LEDStripEffect_fade_init(LEDStripEffect_fade_t *eff, LedStripEffect_tick_t currentTick, uint32_t runInterval, Color_RGB_t *ledBuffer, uint16_t ledCount, Color_RGB_t *colorBuffer, uint8_t colorCount) {
    eff->base.effects = 0;
    eff->base.exec = (LEDStripEffect_exec_t)LEDStripEffect_fade_exec;
    eff->base.lastTick = currentTick;
    eff->base.runInterval = runInterval;
    eff->stripColor.at = colorBuffer;
    eff->stripColor.count = colorCount;
    eff->led.at = ledBuffer;
    eff->led.count = ledCount;
    return eff;
}
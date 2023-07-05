#include "LedStripEffects_Fade.h"

static LEDStripEffects_state_t LEDStripEffects_fade_exec(
        LEDStripEffects_fade_t *eff,
        void (*setColorAt)(uint16_t index, Color_RGB_t color)
    ) {
    LEDStripEffects_state_t ret = LEDStripEffects_state_RUNNING;
    Color_RGB_t startColor;
    Color_RGB_t stopColor;
    Color_RGB_t nowColor;
    uint16_t ledLength = (eff->base.limit.top + 1) - eff->base.limit.bot;
    for(uint16_t indexLED = eff->base.limit.bot; indexLED <= eff->base.limit.top; indexLED++) {
        startColor = LEDStripEffect_getColorGradient(indexLED, ledLength, eff->stripColor.start.color, eff->stripColor.start.length);
        stopColor = LEDStripEffect_getColorGradient(indexLED, ledLength, eff->stripColor.stop.color, eff->stripColor.stop.length);
        nowColor = LEDStripEffect_getColorGradient(eff->base.indexStep, eff->limitStep, (Color_RGB_t []){startColor, stopColor}, 2);
        setColorAt(indexLED, nowColor);
    }
    eff->base.indexStep++;
    if(eff->base.indexStep >= eff->limitStep) {
        return LEDStripEffects_state_STOP;
    }
    return ret;
}

/**
 * @brief 
 * 
 * @param eff Hàm khởi tạo một hiệu ứng Fade
 * @param nowTick Tick hiện tại millisecond
 * @param runInterval Thời gian chạy millisecond
 * @param ledBuffer Buffer LED
 * @param ledCount Số mắt LED
 * @param colorBuffer Buffer dải màu Gradient
 * @param colorCount Số lượng màu trong dải
 * @return LEDStripEffect_fade_t* 
 */
LEDStripEffects_fade_t *LEDStripEffects_fade_init(
        LEDStripEffects_fade_t *eff,
        uint32_t limitStep,
        uint32_t limitBot, uint32_t limitTop,
        Color_RGB_t *startColor, uint8_t startColorLen,
        Color_RGB_t *stopColor, uint8_t stopColorLen
    ) {
    eff->base.exec = (LEDStripEffects_exec_t)LEDStripEffects_fade_exec;
    eff->base.indexStep = 0;
    eff->base.limit.bot = limitBot;
    eff->base.limit.top = limitTop;
    eff->base.state = LEDStripEffects_state_RUNNING;

    eff->limitStep = limitStep;
    eff->stripColor.start.color = startColor;
    eff->stripColor.start.length = startColorLen;
    eff->stripColor.stop.color = stopColor;
    eff->stripColor.stop.length = stopColorLen;
    return eff;
}
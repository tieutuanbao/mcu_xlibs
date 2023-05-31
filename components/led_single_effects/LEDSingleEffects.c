#include "LEDSingleEffects.h"

typedef struct {
    LEDSingleEffects_exec_t exec;
} LEDSingleEffects_t;

LEDSingleEffects_state_t LEDSingleEffects_run(void *effect, LEDSingleEffects_setBrightnessLED_t drv, LEDSingleEffect_tick_t nowTick) {
    return ((LEDSingleEffects_t *)effect)->exec(effect, drv, nowTick);
}

uint8_t LEDSingleEffects_getFade(int32_t step, int32_t minStep, int32_t maxStep, int16_t startBrightness, int16_t stopBrightness) {
    if(step < minStep) {
        return startBrightness;
    }
    if(step > maxStep) {
        return stopBrightness;
    }
    return startBrightness + ((step - minStep) * (stopBrightness - startBrightness)) / (maxStep - minStep);
}

void LEDSingleEffects_meteorDraw(int32_t offset, uint16_t length, uint8_t startBrn, uint8_t stopBrn, uint32_t drawFrom, uint32_t drawTo, LEDSingleEffects_setBrightnessLED_t drv) {
    uint32_t startDraw = 0;
    uint32_t stopDraw = 0;
    if(offset < (int32_t)drawFrom) {
        startDraw = drawFrom;
    }
    else {
        startDraw = offset;
    }
    stopDraw = offset + length;
    if(stopDraw > drawTo) {
        stopDraw = drawTo;
    }
    length -= 1;
    for(uint8_t indexLED = startDraw; indexLED < stopDraw; indexLED++) {
        drv(indexLED, LEDSingleEffects_getFade(indexLED, offset, offset + length, startBrn, stopBrn));
    }
}

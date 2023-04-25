#include "LedStrip_effect.h"
#include <stdlib.h>

void LEDStripEffect_removeAllEffect(LEDStripEffect_t *eff) {
    /* duyệt tất cả hiệu ứng trong hiệu ứng này */
    if(eff->effects != 0) {
        for(uint8_t indexEffect = 0; indexEffect < 255; indexEffect++) {
            if(eff->effects[indexEffect] == 0) {
                break;
            }
            else if(((LEDStripEffect_t *)(eff->effects[indexEffect]))->effects != 0) { // Hiệu ứng này có list hiệu ứng con
                LEDStripEffect_removeAllEffect(eff->effects[indexEffect]);
            }
        }
        /* giải phóng bộ nhớ */
        free(eff->effects);
        eff->effects = 0;
    }
}

/**
 * @brief Hàm xóa hiệu ứng, nó sẽ xóa hiệu ứng được tham chiếu và tất cả những hiệu ứng tiếp theo trong hiệu ứng đó
 * 
 * @param eff 
 * @param effect 
 * @return true 
 * @return false 
 */
bool LEDStripEffect_removeEffect(LEDStripEffect_t *eff, void *effect) {
    LEDStripEffect_t *parrent = 0;
    if(effect == 0) { // Effect is not existed
        return false;
    }
    else {
        /* Tìm effect */
        if(eff->effects != 0) {
            for(uint8_t indexEffect = 0; indexEffect < 255; indexEffect++) {
                if(eff->effects[indexEffect] != 0) {
                    if(eff->effects[indexEffect] != effect) { // Không phải hiệu ứng cần xóa
                        /* tiếp tục tìm trong hiệu ứng này */
                        bool ret = LEDStripEffect_removeEffect((LEDStripEffect_t *)(eff->effects[indexEffect]), effect);
                        if(ret == true) {
                            return true;
                        }
                    }
                    else { // Đúng hiệu ứng cần xóa
                        LEDStripEffect_removeAllEffect(eff->effects[indexEffect]);
                        /* Children Count */
                        uint8_t effCount = 0;
                        for(; effCount < 255; effCount++) {
                            if(eff->effects[effCount] == 0) {
                                break;
                            }
                        }
                        /* realloc | free */
                        if(effCount == 1) {
                            free(eff->effects);
                            eff->effects = 0;
                        }
                        else {
                            for(uint8_t indexEffect1 = indexEffect; indexEffect1 < (effCount - 1); indexEffect1++) {
                                eff->effects[indexEffect] = eff->effects[indexEffect + 1];
                            }
                            LEDStripEffect_t **newEffAdd = (LEDStripEffect_t **)realloc(parrent->effects, effCount * sizeof(void (*)));
                            if(newEffAdd != 0) {
                                parrent->effects = (void **)newEffAdd;
                                eff->effects[effCount - 1] = 0;
                            }
                        }
                        break;
                    }
                }
                else {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

LEDStripEffect_State_t LEDStripEffect_run(LEDStripEffect_Drv_t *eff, LedStripEffect_tick_t currentTick) {
    if(eff->effects != 0) {
        if(((LEDStripEffect_t *)(eff->effects[0]))->exec(eff->effects[0], eff->pixelAt_set, currentTick) == LEDStrip_effectState_stop) {
            if(((LEDStripEffect_t *)(eff->effects[0]))->effects != 0) {
                if(((LEDStripEffect_t *)(eff->effects[0]))->effects[0] != 0)
                eff->effects[0] = ((LEDStripEffect_t *)(eff->effects[0]))->effects[0];
                return LEDStrip_effectState_running;
            }
            else {
                LEDStripEffect_removeEffect((LEDStripEffect_t *)eff, eff->effects[0]);
                return LEDStrip_effectState_stop;
            }
        }
        else {
            return LEDStrip_effectState_running;
        }
    }
    return LEDStrip_effectState_stop;
}

void LEDStripEffect_addEffect(LEDStripEffect_t *parrent, LEDStripEffect_t *children) {
    if(parrent->effects == 0) {
        parrent->effects = malloc(2 * sizeof(void (*)));
        if(parrent->effects != 0) {
            parrent->effects[0] = children;
            parrent->effects[1] = 0;
        }
    }
    else {
        uint8_t indexEff = 0;
        /* Children Count */
        for(; indexEff < 255; indexEff++) {
            if(parrent->effects[indexEff] == 0) {
                break;
            }
        }
        LEDStripEffect_t **newEffAdd = (LEDStripEffect_t **)realloc(parrent->effects, (indexEff + 2) * sizeof(void (*)));
        if(newEffAdd != 0) {
            parrent->effects = (void **)newEffAdd;
            parrent->effects[indexEff] = children;
            indexEff++;
            parrent->effects[indexEff] = 0;
        }
    }
}

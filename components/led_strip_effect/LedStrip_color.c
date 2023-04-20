#include "LedStrip_color.h"

/**
 * @brief Hàm lấy màu Gradien theo frame
 * 
 * @param startColor 
 * @param endColor 
 * @param currentFrame 
 * @param maxFrame 
 * @return Color_RGB_t 
 */
Color_RGB_t LEDStripEffect_getColorGradient(uint32_t colorAt, uint32_t resolution, Color_RGB_t *colorStrip, uint8_t colorCount) {
    if((colorCount == 0) || (colorStrip == 0) || (resolution == 0) || (colorAt >= resolution)) {
        return (Color_RGB_t){0, 0, 0};
    }
    if(colorCount == 1) {
        return colorStrip[0];
    }
    uint32_t resolutionPerSeg = resolution / (colorCount - 1); // số lượng frame mỗi khoảng màu
    uint32_t currentFrame = colorAt % (resolutionPerSeg); // chỉ mục của frame ở mỗi khoảng màu
    uint16_t startColorIndex = colorAt / (resolutionPerSeg);
    uint16_t endColorIndex = startColorIndex + 1;
    if(endColorIndex >= colorCount) {
        return (Color_RGB_t){0, 0, 0};
    }
    Color_RGB_t startColor = colorStrip[startColorIndex];
    Color_RGB_t endColor = colorStrip[endColorIndex];
    Color_RGB_Signed_t diff = (Color_RGB_Signed_t){(int16_t)(endColor.R) - (int16_t)(startColor.R),
                                                    (int16_t)(endColor.G )- (int16_t)(startColor.G),
                                                    (int16_t)(endColor.B) - (int16_t)(startColor.B)};
    Color_RGB_t ret;
    int16_t rateBrightness = currentFrame * 100 / resolutionPerSeg;
    ret.R = startColor.R  + (rateBrightness * diff.R) / 100;
    ret.G = startColor.G  + (rateBrightness * diff.G) / 100;
    ret.B = startColor.B  + (rateBrightness * diff.B) / 100;
    return ret;
}

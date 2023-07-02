#include "dfplayer.h"
#include "bits_delay.h"
#include <string.h>

typedef struct {
    uint8_t start;
    uint8_t vers;
    uint8_t len;
    uint8_t cmd;
    uint8_t ack;
    uint8_t paramMSB;
    uint8_t paramLSB;
    uint8_t checkMSB;
    uint8_t checkLSB;
    uint8_t end;
} DFPlayer_commandFrame_t;

void DFPlayer_sendCommand(DFPlayer_t *dev, uint8_t command, uint16_t param);

/**
 * @brief Khởi tạo DFPlayer
 * 
 * @param dev 
 * @param write 
 * @param read 
 */
void DFPlayer_init(DFPlayer_t *dev,
    void (*send)(uint8_t *pBuf, uint8_t len),
    bool ack, bool resetModule
    )
{
	dev->send = send;
    memcpy(dev->frameTx, (uint8_t []){0x7E, 0xFF, 06, 00, ack, 00, 00, 00, 00, 0xEF}, 10);
    DFPlayer_sendCommand(dev, 0x0C, 0);
    delay(1000);
}

void DFPlayer_sendCommand(DFPlayer_t *dev, uint8_t command, uint16_t param) {
	DFPlayer_commandFrame_t *frame = (DFPlayer_commandFrame_t *)dev->frameTx;
    uint16_t checksum = 0;
    frame->cmd = command;
    frame->paramMSB = (param >> 8) & 0xff;
    frame->paramLSB = param & 0xff;

    checksum = 0xFF;
    checksum += 0x06;
    checksum += command;
    checksum += frame->ack;
    checksum += frame->paramMSB;
    checksum += frame->paramLSB;
    checksum = 0xFFFF - checksum;
    checksum += 1;

    frame->checkMSB = (checksum >> 8) & 0xff;
    frame->checkLSB = checksum & 0xff;
	dev->send(dev->frameTx, sizeof(dev->frameTx));
    dev->lastTick = millis();
}

DFPlayer_handle_t DFPlayer_parseReturn(DFPlayer_t *dev, uint8_t *pBuf) {
    DFPlayer_handle_t ret;
    DFPlayer_commandFrame_t *cmdFrame = (DFPlayer_commandFrame_t *)pBuf;
    uint8_t param = ((uint16_t)(cmdFrame->paramMSB) << 8) | cmdFrame->paramLSB;
    if (cmdFrame->cmd == 0x41) {
        dev->busy = false;
        ret.type = DFPlayer_returnType_READY_RECV;
        ret.param = param;
        return ret;
    }
    
    switch (cmdFrame->cmd) {
        case 0x3C:
        case 0x3D:
            ret.type = DFPlayer_returnType_PLAY_FINISHED;
            ret.param = param;
            break;
        case 0x3F:
            if (param & 0x01) {
                ret.type = DFPlayer_returnType_USB_ONLINE;
                ret.param = param;
            }
            else if (param & 0x02) {
                ret.type = DFPlayer_returnType_CARD_ONLINE;
                ret.param = param;
            }
            else if (param & 0x03) {
                ret.type = DFPlayer_returnType_CARDUSB_ONLINE;
                ret.param = param;
            }
            break;
        case 0x3A:
            if (param & 0x01) {
                ret.type = DFPlayer_returnType_USB_INSERTED;
                ret.param = param;
            }
            else if (param & 0x02) {
                ret.type = DFPlayer_returnType_CARD_INSERTED;
                ret.param = param;
            }
            break;
        case 0x3B:
            if (param & 0x01) {
                ret.type = DFPlayer_returnType_USB_REMOVED;
                ret.param = param;
            }
            else if (param & 0x02) {
                ret.type = DFPlayer_returnType_CARD_REMOVED;
                ret.param = param;
            }
            break;
        case 0x40:
            ret.type = DFPlayer_returnType_ERROR;
            ret.param = param;
            break;
        case 0x3E:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
            ret.type = DFPlayer_returnType_FEEDBACK;
            ret.param = param;
            break;
        default:
            ret.type = DFPlayer_returnType_WRONG_RETURN;
            ret.param = param;
            break;
    }
    return ret;
}

void DFPlayer_play(DFPlayer_t *dev, uint16_t fileNum) {
    DFPlayer_sendCommand(dev, 0x03, fileNum);
}
void DFPlayer_stop(DFPlayer_t *dev) {
    DFPlayer_sendCommand(dev, 0x16, 0);
}
void DFPlayer_volume(DFPlayer_t *dev, uint8_t volume) {
    DFPlayer_sendCommand(dev, 0x06, volume);
}
void DFPlayer_enableLoop(DFPlayer_t *dev) {
    DFPlayer_sendCommand(dev, 0x19, 0x00);
}
void DFPlayer_disableLoop(DFPlayer_t *dev) {
    DFPlayer_sendCommand(dev, 0x19, 0x01);
}
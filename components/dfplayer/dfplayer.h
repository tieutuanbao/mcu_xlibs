#ifndef __DFPLAYER_H__
#define __DFPLAYER_H__

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    DFPlayer_controlCommand_PLAY_NEXT = 0x01,
    DFPlayer_controlCommand_PLAY_PREV,
    DFPlayer_controlCommand_SPEC_PLAYBACK_TRACK,
    DFPlayer_controlCommand_INCREASE_VOL,
    DFPlayer_controlCommand_DECREASE_VOL,
    DFPlayer_controlCommand_SPEC_VOL,
    DFPlayer_controlCommand_SPEC_EQ,
    DFPlayer_controlCommand_SPEC_SINGLE_REPEAT_PLAYBACK,
    DFPlayer_controlCommand_SPEC_PLAYBACK_DEV,
    DFPlayer_controlCommand_SET_SLEEP,
    DFPlayer_controlCommand_RESERVED_0,
    DFPlayer_controlCommand_RESET,
    DFPlayer_controlCommand_PLAY,
    DFPlayer_controlCommand_PAUSE,
    DFPlayer_controlCommand_SPEC_PLAYBACK_TRACK_IN_FOLDER,
    DFPlayer_controlCommand_AUDIO_AMP_SET,
    DFPlayer_controlCommand_SET_ALL_REPEAT_PLAYBACK,
    DFPlayer_controlCommand_SPEC_PLAYBACK_OF_MP3_FOLDER,
    DFPlayer_controlCommand_INSERT_ADV,
    DFPlayer_controlCommand_SPEC_PLAYBACK_TRACK_3000,
    DFPlayer_controlCommand_SPEC_PLAY_ADV_AND_GOBACK,
    DFPlayer_controlCommand_STOP,
    DFPlayer_controlCommand_SPEC_REPEAT_PLAYBACK,
    DFPlayer_controlCommand_SET_RANDOM_PLAYBACK,
    DFPlayer_controlCommand_SET_REPEAT_PLAYBACK_CURRENT_TRACK,
    DFPlayer_controlCommand_SET_DAC
} DFPlayer_controlCommand_t;

typedef enum {
    DFPlayer_queryCommand_RESERVED_0 = 0x3C,
    DFPlayer_queryCommand_RESERVED_1,
    DFPlayer_queryCommand_RESERVED_2,
    DFPlayer_queryCommand_QUERY_CURR_STORAGE,
    DFPlayer_queryCommand_RET_AN_ERROR,
    DFPlayer_queryCommand_REPORT_A_FEEDBACK,
    DFPlayer_queryCommand_QUERY_CURR_STT,
    DFPlayer_queryCommand_QUERY_CURR_VOL,
    DFPlayer_queryCommand_QUERY_CURR_EQ,
    DFPlayer_queryCommand_RESERVED_3,
    DFPlayer_queryCommand_RESERVED_4,
    DFPlayer_queryCommand_QUERY_NUM_TRACK_IN_USB,
    DFPlayer_queryCommand_QUERY_NUM_TRACK_IN_SD_CARD,
    DFPlayer_queryCommand_RESERVED_5,
    DFPlayer_queryCommand_RESERVED_6,
    DFPlayer_queryCommand_QUERY_CURR_TRACK_IN_USB,
    DFPlayer_queryCommand_QUERY_CURR_TRACK_IN_SD_CARD,
    DFPlayer_queryCommand_RESERVED_7,
    DFPlayer_queryCommand_QUERY_NUM_TRACK_IN_FOLDER,
    DFPlayer_queryCommand_QUERY_NUM_FOLDER_IN_CURR_STORAGE,
} DFPlayer_queryCommand_t;

typedef enum {
    DFPlayer_returnType_READY_RECV,
    DFPlayer_returnType_TIMEOUT,
    DFPlayer_returnType_WRONG_RETURN,
    DFPlayer_returnType_CARD_INSERTED,
    DFPlayer_returnType_CARD_REMOVED,
    DFPlayer_returnType_CARD_ONLINE,
    DFPlayer_returnType_PLAY_FINISHED,
    DFPlayer_returnType_ERROR,
    DFPlayer_returnType_USB_INSERTED,
    DFPlayer_returnType_USB_REMOVED,
    DFPlayer_returnType_USB_ONLINE,
    DFPlayer_returnType_CARDUSB_ONLINE,
    DFPlayer_returnType_FEEDBACK
} DFPlayer_returnType_t;

typedef struct {
    DFPlayer_returnType_t type;
    uint16_t param;
} DFPlayer_handle_t;

typedef struct {
    void (*send)(uint8_t *pBuf, uint8_t len);
    uint8_t frameTx[10];
    uint32_t lastTick;
    bool busy;
} DFPlayer_t;

void DFPlayer_init(DFPlayer_t *dev,
    void (*send)(uint8_t *pBuf, uint8_t len),
    bool ack, bool resetModule);
DFPlayer_handle_t DFPlayer_parseReturn(DFPlayer_t *dev, uint8_t *pBuf);
void DFPlayer_play(DFPlayer_t *dev, uint16_t fileNum);
void DFPlayer_stop(DFPlayer_t *dev);
void DFPlayer_volume(DFPlayer_t *dev, uint8_t volume);
void DFPlayer_enableLoop();
void DFPlayer_disableLoop();

#endif
#ifndef __ESP8266_WIFI_SCAN_H
#define __ESP8266_WIFI_SCAN_H

#include "port_macros.h"
#include "user_interface.h"

#define WIFI_SCAN_RUNNING   (-1)
#define WIFI_SCAN_FAILED    (-2)

typedef struct {
    bool scan_started;
    bool scan_async;
    bool scan_complete;
    struct bss_info *scan_result;
    size_t scan_count;
    void (*scan_complete_callback)(size_t scan_result_count);
} esp8266_wifi_scan_t;

extern esp8266_wifi_scan_t esp8266_scanner;

int8_t esp8266_wifi_scan(bool async, char *ssid, uint8_t channel, bool show_hidden);
uint8_t esp8266_wifi_result_count(void);
struct bss_info *esp8266_wifi_get_result(uint8_t idx_result);
int8_t esp8266_wifi_complete();
void esp8266_wifi_scan_delete();


#endif
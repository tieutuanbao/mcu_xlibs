#include "esp8266_wifi_scan.h"
#include "mem.h"

esp8266_wifi_scan_t esp8266_scanner;

/**
 * @brief Prototype
 * 
 */
void esp8266_wifi_scan_done(void* result, STATUS status);

/**
 * @brief Code
 * 
 */
void esp8266_wifi_scan_delete() {
    if(esp8266_scanner.scan_result) {
        free(esp8266_scanner.scan_result);
        esp8266_scanner.scan_result = 0;
        esp8266_scanner.scan_count = 0;
    }
    esp8266_scanner.scan_complete = false;
}

int8_t esp8266_wifi_scan(bool async, char *ssid, uint8_t channel, bool show_hidden) {
    /* Kiểm tra có đang scan không */
    if(esp8266_scanner.scan_started == true) {
        return WIFI_SCAN_RUNNING;
    }

    esp8266_scanner.scan_async = async;
    /* Kiểm tra wifi đang trong chế độ station không */
    if((wifi_get_opmode() & STATION_MODE) == 0){
        wifi_set_opmode(STATION_MODE);
    }
    /* Nếu đang kết nối wifi thì ngắt kết nối */
    int status = wifi_station_get_connect_status();
    if(status != STATION_GOT_IP && status != STATION_IDLE) {
        wifi_station_disconnect();
    }
    /* Xóa dữ liệu scan cũ */
    esp8266_wifi_scan_delete();
    /* Cấu hình dữ liệu scan mới */
    struct scan_config config;
    memset(&config, 0, sizeof(config));
    config.ssid = ssid;
    config.channel = channel;
    config.show_hidden = show_hidden;
    if(wifi_station_scan(&config, esp8266_wifi_scan_done)) {
        esp8266_scanner.scan_complete = false;
        esp8266_scanner.scan_started = true;

        if(esp8266_scanner.scan_async == true) {
            return WIFI_SCAN_RUNNING;
        }
        return esp8266_scanner.scan_count;
    } else {
        return WIFI_SCAN_FAILED;
    }
}
/**
 * @brief Hàm kiểm tra complete
 * 
 * @return int8_t WIFI_SCAN_RUNNING
 * @return int8_t WIFI_SCAN_FAILED
 * @return int8_t Số lượng kết quả scan được
 */
int8_t esp8266_wifi_complete() {
    if(esp8266_scanner.scan_started) {
        return WIFI_SCAN_RUNNING;
    }
    if(esp8266_scanner.scan_complete) {
        return esp8266_scanner.scan_count;
    }
    return WIFI_SCAN_FAILED;
}
/**
 * @brief Lấy số lượng kết quả sau khi scan
 * 
 * @return uint8_t Số lượng kết quả sau scan
 */
uint8_t esp8266_wifi_result_count(void) {
    return esp8266_scanner.scan_count;
}

/**
 * @brief Lấy kết quả scan ở vị trí xác định
 * 
 * @param idx_result vị trí lấy kết quả
 * @return struct bss_info* con trỏ đến kết quả
 */
struct bss_info *esp8266_wifi_get_result(uint8_t idx_result) {
    return esp8266_scanner.scan_result + idx_result;
}

void esp8266_print_result() {
    for(uint8_t idx_result = 0; idx_result < esp8266_scanner.scan_count;idx_result++){
        BITS_LOGD("%s: esp8266_print_result(): - result[%d].ssid = %s\r\n", __FILE__, idx_result, esp8266_scanner.scan_result[idx_result].ssid);
        BITS_LOGD("%s: esp8266_print_result():     + channel = %d\r\n", __FILE__, esp8266_scanner.scan_result[idx_result].channel);
        BITS_LOGD("%s: esp8266_print_result():     + authmode = %d\r\n", __FILE__, esp8266_scanner.scan_result[idx_result].authmode);
        BITS_LOGD("%s: esp8266_print_result():     + rssi = %d\r\n", __FILE__, esp8266_scanner.scan_result[idx_result].rssi);
    }
}
/**
 * @brief Hàm callback sau khi scan
 * 
 * @param result Kết quả scan
 * @param status Trạng thái scan
 */
void esp8266_wifi_scan_done(void *result, STATUS status) {
    if(status != OK) {
        BITS_LOGE("%s: esp8266_wifi_scan_done(): status FAIL!\r\n", __FILE__);
        esp8266_scanner.scan_count = 0;
        esp8266_scanner.scan_result = 0;
    } else {
        /* Đếm số lượng kết quả */
        struct bss_info* head = ((struct bss_info *)result);
        for(struct bss_info* idx_result = head; idx_result; idx_result = STAILQ_NEXT(idx_result, next), ++esp8266_scanner.scan_count);
        if(esp8266_scanner.scan_count == 0) {
            esp8266_scanner.scan_result = 0;
        } else {
            if(esp8266_scanner.scan_result == 0) {
                /* Cấp phát bộ nhớ để lưu dữ liệu scan */
                esp8266_scanner.scan_result = malloc(esp8266_scanner.scan_count * sizeof(struct bss_info));
                if(esp8266_scanner.scan_result == 0) {
                    BITS_LOGE("%s: esp8266_wifi_scan_done(): Error malloc for scan result = %d!\r\n", __FILE__, esp8266_scanner.scan_count * sizeof(struct bss_info));
                }
            } else {
                /* Cấp phát bộ nhớ để lưu dữ liệu scan */
                esp8266_scanner.scan_result = realloc(esp8266_scanner.scan_result, esp8266_scanner.scan_count * sizeof(struct bss_info));
                if(esp8266_scanner.scan_result == 0) {
                    BITS_LOGE("%s: esp8266_wifi_scan_done(): Error realloc for scan result!\r\n", __FILE__);
                }
            }
            /* Lưu lại dữ liệu scan */
            struct bss_info* next_result = ((struct bss_info *)result);
            for(uint8_t idx_result = 0; idx_result < esp8266_scanner.scan_count; idx_result++) {
                *(esp8266_scanner.scan_result + idx_result) = *next_result;
                next_result = STAILQ_NEXT(next_result, next);
            }
        }
    }

    esp8266_scanner.scan_started = false;
    esp8266_scanner.scan_complete = true;
    
    if (esp8266_scanner.scan_complete_callback) {
        esp8266_scanner.scan_complete_callback(esp8266_scanner.scan_count);
        esp8266_scanner.scan_complete_callback = 0;
    }
}
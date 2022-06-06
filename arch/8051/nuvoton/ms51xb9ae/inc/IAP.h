/**
  ******************************************************************************
  * @file           : iap.h
  * @brief          : Thư viện driver iap lập trình nuvoton ms51.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

#ifndef __IAP_H
#define __IAP_H

#include <stdint.h>

#define IAP_PAGE_SIZE                    128
#define IAP_APROM_MAX_SIZE        16*1024

typedef enum {
    iap_ok,
    iap_error,
    iap_ldrom_not_blank,
    iap_ldrom_verify_failed,
    iap_aprom_not_blank,
    iap_aprom_verify_failed
} iap_error_t;

iap_error_t iap_ldrom_erase(uint16_t address, uint16_t size);
iap_error_t iap_ldrom_is_blank(uint16_t address, uint16_t size);
iap_error_t iap_ldrom_program(uint16_t address, uint8_t *buffer, uint16_t size);
iap_error_t iap_ldrom_read(uint16_t address, uint8_t *buffer, uint16_t size);
iap_error_t iap_ldrom_verify(uint16_t address, uint8_t *buffer, uint16_t size);

iap_error_t iap_aprom_erase(uint16_t address, uint16_t size);
iap_error_t iap_aprom_is_blank(uint16_t address, uint16_t size);
iap_error_t iap_aprom_program(uint16_t address, uint8_t __generic *buffer, uint16_t size);
iap_error_t iap_aprom_read(uint16_t address, uint8_t __generic *buffer, uint16_t size);
iap_error_t iap_aprom_verify(uint16_t address, uint8_t __generic *buffer, uint16_t size);

iap_error_t iap_cid_read(uint8_t *buffer);
iap_error_t iap_did_read(uint8_t *buffer);

#endif

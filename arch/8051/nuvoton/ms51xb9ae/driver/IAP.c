/**
  ******************************************************************************
  * @file           : iap.c
  * @brief          : Thư viện driver iap lập trình nuvoton ms51.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

#include "iap.h"
#include "reg_ms51.h"

extern unsigned char  BIT_TMP;

/**
 * @brief       Trig IAP and check status flag
 * @param       None
 * @return      iap_error_t
 * @details     Trig IAPGO, check IAP Status flag if error set IAP disable all.
 */
iap_error_t iap_trigger(void) {
    /* Trigger IAP */
    set_IAPTRG_IAPGO;
    /* if fail flag is set, IAP stop */
    if(CHPCON & SET_BIT6) {
        clr_CHPCON_IAPFF;
        return iap_error;
    }
    return iap_ok;
}

/**
 * @brief                Erase LDROM
 * @param                address define LDROM area start address
 * @param                size define LDROM need be erase bytes size
 * @return            iap_error_t
 * @details            Page erase LDROM area base on data start address
 * @example            iap_ldrom_erase(0x0000, 2048);
 */
iap_error_t iap_ldrom_erase(uint16_t address, uint16_t size) {
    uint16_t index_page = 0;
    /* Enable IAP function */
    set_CHPCON_IAPEN;
    /* LDROM modify Enable */
    set_IAPUEN_LDUEN;
    /* IMPORTANT !! To erase function must setting IAPFD = 0xFF */
    IAPFD = 0xFF;
    IAPCN = PAGE_ERASE_LDROM;
    /* Loop page*/
    for(index_page = 0; index_page < (size/IAP_PAGE_SIZE); index_page++) {
        IAPAL = LOBYTE(index_page * IAP_PAGE_SIZE + address);
        IAPAH = HIBYTE(index_page * IAP_PAGE_SIZE + address);
        if(iap_trigger() != iap_ok) return iap_error;
    }
    /* Disable LDROM modify */
    clr_IAPUEN_LDUEN;
    /* Disable IAP */
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                LDROM blank check
 * @param                address define LDROM area start address
 * @param                size define LDROM need be erase bytes size
 * @return            iap_error_t
 * @details            Check each byte of LDROM is FFH or not.
 * @example            iap_ldrom_is_blank(0x0000, 2048);
 */
iap_error_t iap_ldrom_is_blank(uint16_t address, uint16_t size)
{
    uint16_t index_address = 0;
    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(address);
    IAPAH = HIBYTE(address);
    IAPCN = BYTE_READ_LDROM;
    for(index_address = 0; index_address < size; index_address++) {
        IAPFD = 0x00;
        if(iap_trigger() != iap_ok) return iap_error;
        if(IAPFD != 0xFF) {
            return iap_ldrom_not_blank;
        }
        IAPAL++;
        if(IAPAL == 0x00) {
            IAPAH++;
        }
    }
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                LDROM program
 * @param                address define LDROM area start address
 * @param                buffer define pointer to buffer data
 * @param                size define LDROM need be program bytes size
 * @return            iap_error_t
 * @details            Copy buffer to LDROM
 * @example            iap_ldrom_program(0x0000, pointer_buffer, 1024);
 */
iap_error_t iap_ldrom_program(uint16_t address, uint8_t *buffer, uint16_t size) {
    uint16_t index_data = 0;
    set_CHPCON_IAPEN;
    set_IAPUEN_LDUEN;
    IAPAL = LOBYTE(address);
    IAPAH = HIBYTE(address);
    IAPCN = BYTE_PROGRAM_LDROM;

    for(index_data = 0; index_data < size; index_data++) {
        IAPFD = buffer[index_data];
        if(iap_trigger() != iap_ok) return iap_error;
        IAPAL++;
        if(IAPAL == 0) {
            IAPAH++;
        }
    }
    clr_IAPUEN_LDUEN;
    clr_CHPCON_IAPEN;
    return iap_ok;
}
/**
 * @brief                LDROM read
 * @param                address define LDROM area start address
 * @param                buffer define pointer to buffer data
 * @param                size define LDROM need be read bytes size
 * @return            iap_error_t
 * @details            get data from LDROM
 * @example            iap_ldrom_verify(0x0000, pointer_buffer, 1024);
 */
iap_error_t iap_ldrom_read(uint16_t address, uint8_t *buffer, uint16_t size) {
    uint16_t index_data = 0;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(address);
    IAPAH = HIBYTE(address);
    IAPCN = BYTE_READ_LDROM;
    for(index_data = 0; index_data < size; index_data++) {
        IAPFD = 0x00;
        if(iap_trigger() != iap_ok) return iap_error;
        buffer[index_data] = IAPFD;
        IAPAL++;
        if(IAPAL == 0) {
            IAPAH++;
        }
    }
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                LDROM verify
 * @param                address define LDROM area start address
 * @param                buffer define pointer to buffer data
 * @param                size define LDROM need be verify bytes size
 * @return            iap_error_t
 * @details            Check buffer with LDROM
 * @example            iap_ldrom_verify(0x0000, pointer_buffer, 1024);
 */
iap_error_t iap_ldrom_verify(uint16_t address, uint8_t *buffer, uint16_t size) {
    uint16_t index_data = 0;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(address);
    IAPAH = HIBYTE(address);
    IAPCN = BYTE_READ_LDROM;
    for(index_data = 0; index_data < size; index_data++) {
        IAPFD = 0x00;
        if(iap_trigger() != iap_ok) return iap_error;
        if (IAPFD != buffer[index_data]) return iap_ldrom_verify_failed;
        IAPAL++;
        if(IAPAL == 0) {
            IAPAH++;
        }
    }
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                Erase APROM
 * @param                address define APROM area start address
 * @param                size define APROM need be erase bytes size
 * @return            iap_error_t
 * @details            Page erase APROM area base on data start address
 * @example            iap_aprom_erase(0x0000, 2048);
 */
iap_error_t iap_aprom_erase(uint16_t address, uint16_t size) {
    uint16_t index_page = 0;
    if(size < IAP_PAGE_SIZE) size = IAP_PAGE_SIZE;
    /* Enable IAP function */
    set_CHPCON_IAPEN;
    /* APROM modify Enable */
    set_IAPUEN_APUEN;
    /* IMPORTANT !! To erase function must setting IAPFD = 0xFF */
    IAPFD = 0xFF;
    IAPCN = PAGE_ERASE_APROM;
    /* Loop page*/
    for(index_page = 0; index_page < (size/IAP_PAGE_SIZE); index_page++) {
        IAPAL = LOBYTE(index_page * IAP_PAGE_SIZE + address);
        IAPAH = HIBYTE(index_page * IAP_PAGE_SIZE + address);
        if(iap_trigger() != iap_ok) return iap_error;
    }
    /* Disable APROM modify */
    clr_IAPUEN_LDUEN;
    /* Disable IAP */
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                APROM blank check
 * @param                address define APROM area start address
 * @param                size define APROM need be erase bytes size
 * @return            iap_error_t
 * @details            Check each byte of APROM is FFH or not.
 * @example            iap_aprom_is_blank(0x0000, 2048);
 */
iap_error_t iap_aprom_is_blank(uint16_t address, uint16_t size) {
    uint16_t index_address = 0;
    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(address);
    IAPAH = HIBYTE(address);
    IAPCN = BYTE_READ_APROM;
    for(index_address = 0; index_address < size; index_address++) {
        IAPFD = 0x00;
        if(iap_trigger() != iap_ok) return iap_error;
        if(IAPFD != 0xFF) {
            return iap_aprom_not_blank;
        }
        IAPAL++;
        if(IAPAL == 0x00) {
            IAPAH++;
        }
    }
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                APROM program
 * @param                address define APROM area start address
 * @param                buffer define pointer to buffer data
 * @param                size define APROM need be program bytes size
 * @return            iap_error_t
 * @details            Copy buffer to APROM
 * @example            iap_aprom_program(0x0000, pointer_buffer, 1024);
 */
iap_error_t iap_aprom_program(uint16_t address, uint8_t __generic *buffer, uint16_t size) {
    uint16_t index_data = 0;
    set_CHPCON_IAPEN;
    set_IAPUEN_APUEN;
    IAPAL = LOBYTE(address);
    IAPAH = HIBYTE(address);
    IAPCN = BYTE_PROGRAM_APROM;

    for(index_data = 0; index_data < size; index_data++) {
        IAPFD = buffer[index_data];
        if(iap_trigger() != iap_ok) {
            return iap_error;
        }
        IAPAL++;
        if(IAPAL == 0) {
            IAPAH++;
        }
    }
    clr_IAPUEN_LDUEN;
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                APROM read
 * @param                address define APROM area start address
 * @param                buffer define pointer to buffer data
 * @param                size define APROM need be read bytes size
 * @return            iap_error_t
 * @details            Check with XRAM IAPDataBuf with APROM
 * @example            iap_aprom_read(0x0000, pointer_buffer, 1024);
 */
iap_error_t iap_aprom_read(uint16_t address, uint8_t __generic *buffer, uint16_t size) {
    uint16_t index_data = 0;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(address);
    IAPAH = HIBYTE(address);
    IAPCN = BYTE_READ_APROM;
    for(index_data = 0; index_data < size; index_data++) {
        IAPFD = 0x00;
        if(iap_trigger() != iap_ok) return iap_error;
        buffer[index_data] = IAPFD;
        IAPAL++;
        if(IAPAL == 0) {
            IAPAH++;
        }
    }
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                APROM verify
 * @param                address define APROM area start address
 * @param                buffer define pointer to buffer data
 * @param                size define APROM need be erase bytes size
 * @return            iap_error_t
 * @details            Check with XRAM IAPDataBuf with APROM
 * @example            iap_aprom_verify(0x0000,1024);
 */
iap_error_t iap_aprom_verify(uint16_t address, uint8_t __generic *buffer, uint16_t size) {
    uint16_t index_data = 0;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(address);
    IAPAH = HIBYTE(address);
    IAPCN = BYTE_READ_APROM;
    for(index_data = 0; index_data < size; index_data++) {
        IAPFD = 0x00;
        if(iap_trigger() != iap_ok) return iap_error;
        if (IAPFD != buffer[index_data]) return iap_aprom_verify_failed;
        IAPAL++;
        if(IAPAL == 0) {
            IAPAH++;
        }
    }
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                Read CID
 * @param                buffer define buffer to read ucid - sizeof buffer 12Byte
 * @return            iap_error_t
 * @details            IAP command read CID area storage data in XRAM buffer[0:8]
 * @example            iap_cid_read(pounter_buffer);
 */
iap_error_t iap_cid_read(uint8_t *buffer) {
    uint8_t index_data;

    set_CHPCON_IAPEN;
    IAPAL = 0x20;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    for (index_data = 0; index_data < 12; index_data++) {
        IAPFD = 0x00;
        if(iap_trigger() != iap_ok) return iap_error;
        buffer[index_data] = IAPFD;
        IAPAL++;
    }
    clr_CHPCON_IAPEN;
    return iap_ok;
}

/**
 * @brief                Read DID
 * @param                buffer define buffer to read ucid - sizeof buffer 12Byte
 * @return            iap_error_t
 * @details            IAP command read DID area storage data in XRAM buffer[0:8]
 * @example            iap_did_read(pounter_buffer);
 */
iap_error_t iap_did_read(uint8_t *buffer) {
    uint8_t index_data;

    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = 0x00;
    IAPCN = READ_DID;
    for (index_data = 0; index_data < 4; index_data++) {
        IAPFD = 0x00;
        if(iap_trigger() != iap_ok) return iap_error;
        buffer[index_data] = IAPFD;
        IAPAL++;
    }
    clr_CHPCON_IAPEN;
    return iap_ok;
}

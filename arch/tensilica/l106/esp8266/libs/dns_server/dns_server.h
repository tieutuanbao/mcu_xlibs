/**
 * @file dns_server.h
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief Thư viện tạo dns_server cho esp8266
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DNS_SERVER_H
#define __DNS_SERVER_H

#include "c_types.h"
#include "port_macros.h"
#include "lwip/ip_addr.h"
#include "lwipopts.h"
#include "lwip/def.h"
#include "udp.h"

typedef struct __attribute__((packed)) __dns_header_t{
	uint16_t id;
    union {
        struct{
            uint16_t RD : 1;         // recursion desired
            uint16_t TC : 2;         // truncated message
            uint16_t OPCode : 4;     // message_type
            uint16_t QR : 1;         // query/response flag
            uint16_t reserved : 4;   // reserved
            uint16_t NA : 1;         // non-authenticated data
            uint16_t Z : 3;          // its z! reserved
        } query_bit;
        struct{
            uint16_t RD : 1;        // recursion desired
            uint16_t TC : 1;        // truncated message
            uint16_t AU : 1;        // authoritative
            uint16_t OPCode : 4;    // message_type
            uint16_t QR : 1;        // query/response flag
            uint16_t RCode : 4;     // response code
            uint16_t NA : 1;        // non-authenticated data
            uint16_t AA : 1;        // answer authoritative
            uint16_t Z : 1;         // its z! reserved
            uint16_t RA : 1;        // recursion available
        } resp_bit;
	    uint16_t value;
    } flags;
	uint16_t QDCount;
	uint16_t ANCount;
	uint16_t NSCount;
	uint16_t ARCount;
} dns_header_t;

typedef enum {
    DNS_REPLY_NO_ERROR              = 0,
    DNS_REPLY_FORM_ERROR            = 1,
    DNS_REPLY_SERVER_FAILURE        = 2,
    DNS_REPLY_NON_EXISTENT_DOMAIN   = 3,
    DNS_REPLY_NOT_IMPLEMENTED       = 4,
    DNS_REPLY_REFUSED               = 5,
    DNS_REPLY_YXDOMAIN              = 6,
    DNS_REPLY_YXRRSET               = 7,
    DNS_REPLY_NXRRSET               = 8
} dns_reply_code_t;

typedef struct {
    struct udp_pcb espudp; 
    ip_addr_t resolve_ip;
    char *domain_name;
} dns_server_param_t;

typedef struct espconn dns_server_t;

dns_server_t *dns_server_init(uint16_t port, char *domain_name, ip_addr_t resolve_ip);
void dns_server_reply_error(  dns_server_t *dev,
                                            dns_header_t *dns_header,
                                            dns_reply_code_t rep_code,
                                            uint8_t *query,
                                            size_t query_length);
void dns_server_reply_ip( dns_server_t *dev,
                                        dns_header_t *dns_header,
			                            uint8_t * query,
			                            size_t query_length);

#endif
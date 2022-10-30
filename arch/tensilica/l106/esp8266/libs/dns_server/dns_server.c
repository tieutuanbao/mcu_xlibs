/**
 * @file dns_server.c
 * @author Tieu Tuan Bao (tieutuanbao@gmail.com)
 * @brief Thư viện tạo dns_server cho esp8266
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "dns_server.h"
#include "user_interface.h"

#define DNS_QR_QUERY 0
#define DNS_QR_RESPONSE 1
#define DNS_OPCODE_QUERY 0

#define DNS_QCLASS_IN 1
#define DNS_QCLASS_ANY 255

#define DNS_QTYPE_A 1
#define DNS_QTYPE_ANY 255

#define MAX_DNSNAME_LENGTH 253
#define MAX_DNS_PACKETSIZE 512


static void dns_server_udp_recv(void *arg, char *pusrdata, unsigned short length);

dns_server_t *dns_server_init(uint16_t port, char *domain_name, ip_addr_t resolve_ip) {
    dns_server_t *ret;
    dns_server_param_t *dns_sv_param;
    struct ip_info ipconfig;

    /* Tạo object server */
    ret = malloc(sizeof(dns_server_t));
    ret->type = ESPCONN_UDP;
    ret->state = ESPCONN_NONE;

    /* Tạo object connection */
    ret->reverse = malloc(sizeof(dns_server_param_t));

    /* Cấu hình server */
    dns_sv_param = ret->reverse;
    dns_sv_param->domain_name = domain_name;
    dns_sv_param->resolve_ip.addr = resolve_ip.addr;
    dns_sv_param->espudp.local_ip[0] = 0;
    dns_sv_param->espudp.local_ip[1] = 0;
    dns_sv_param->espudp.local_ip[2] = 0;
    dns_sv_param->espudp.local_ip[3] = 0;
    dns_sv_param->espudp.local_port = port;

    ret->proto.udp = &(dns_sv_param->espudp);
    espconn_regist_recvcb(ret, dns_server_udp_recv);

    BITS_LOGD(__FILE__": UDP DNS server init error = %d !!! \r\n", espconn_create(ret));
    return ret;
}

static void dns_server_udp_recv(void *arg, char *pusrdata, unsigned short length) {
    dns_server_param_t *dns_sv_param = ((dns_server_t *)arg)->reverse;
    dns_header_t *dns_header = (dns_header_t *) pusrdata;
    uint8_t *query, *start;
    const char *match_string;
    size_t remaining, labelLength, queryLength;
    uint16_t qtype, qclass;
    
    /* ---- Giải mã dữ liệu ---- */
    // Bắt buộc phải là cờ QUERY
    if(dns_header->flags.query_bit.QR != DNS_QR_QUERY) {
        return;
    }
    // Không thực hiện nếu thao tác này không phải QUERY
    if (dns_header->flags.query_bit.OPCode != DNS_OPCODE_QUERY){
        return dns_server_reply_error(arg, dns_header, DNS_REPLY_NOT_IMPLEMENTED, 0, 0);
    }
    // Chỉ hỗ trợ yêu cầu truy vấn đơn lẻ
    if (dns_header->QDCount != lwip_htons(1)){
        return dns_server_reply_error(arg, dns_header, DNS_REPLY_FORM_ERROR, 0, 0);
    }
    // Phải trả về FormError trong trường hợp ARCount khác 0 để tương thích tối thiểu với các trình phân giải EDNS
    if ((dns_header->ANCount != 0) || (dns_header->NSCount != 0) || (dns_header->ARCount != 0)){
        return dns_server_reply_error(arg, dns_header, DNS_REPLY_FORM_ERROR, 0, 0);
    }
    // Kiểm tra lại địa chỉ đang được truy vấn
    query = start = pusrdata + sizeof(dns_header_t);
    remaining = length - sizeof(dns_header_t);
    while ((remaining != 0) && (*start != 0)) {
        labelLength = *start;
        if ((labelLength + 1) > remaining){
            return dns_server_reply_error(arg, dns_header, DNS_REPLY_FORM_ERROR, 0, 0);
        }
        remaining -= (labelLength + 1);
        start += (labelLength + 1);
    }
    // 1 octet labelLength, 2 octet qtype, 2 octet qclass
    if (remaining < 5) {
        return dns_server_reply_error(arg, dns_header, DNS_REPLY_FORM_ERROR, 0, 0);
    }

    start += 1; // Skip the 0 length label that we found above

    memcpy(&qtype, start, sizeof(qtype));
    start += 2;
    memcpy(&qclass, start, sizeof(qclass));
    start += 2;

    queryLength = start - query;

    if ((qclass != lwip_htons(DNS_QCLASS_ANY)) && (qclass != lwip_htons(DNS_QCLASS_IN))){
        return dns_server_reply_error(arg, dns_header, DNS_REPLY_NON_EXISTENT_DOMAIN, query, queryLength);
    }

    if ((qtype != lwip_htons(DNS_QTYPE_A)) && (qtype != lwip_htons(DNS_QTYPE_ANY))){
        return dns_server_reply_error(arg, dns_header, DNS_REPLY_NON_EXISTENT_DOMAIN, query, queryLength);
    }
    // Nếu không có demain nào được cấu hình thì trả về lỗi
    if (dns_sv_param->domain_name == 0){
        return dns_server_reply_error(arg, dns_header, DNS_REPLY_NON_EXISTENT_DOMAIN, query, queryLength);
    }
    // Nếu dùng domain name là ký tự đại diện cho bất kỳ domain nào thì trả về với IP   
    if (strcmp(dns_sv_param->domain_name, "*") == 0){
        return dns_server_reply_ip(arg, dns_header, query, queryLength);
    }

    match_string = dns_sv_param->domain_name;

    start = query;

    // Bỏ qua mở đầu với www
    if ((*start == 3) && (strncasecmp("www", (char *)start + 1, 3) == 0)){
        start += 4;
    }
    while (*start != 0) {
        labelLength = *start;
        start += 1;
        while (labelLength > 0) {
            if (tolower(*start) != *match_string){
                return dns_server_reply_error(arg, dns_header, DNS_REPLY_NON_EXISTENT_DOMAIN, query, queryLength);
            }
            ++start;
            ++queryLength;
            --labelLength;
        }
        if (*start == 0 && *match_string == '\0')
        return dns_server_reply_ip(arg, dns_header, query, queryLength);

        if (*match_string != '.'){
            return dns_server_reply_error(arg, dns_header, DNS_REPLY_NON_EXISTENT_DOMAIN, query, queryLength);
        }
        ++match_string;
    }
    return dns_server_reply_error(arg, dns_header, DNS_REPLY_NON_EXISTENT_DOMAIN, query, queryLength);
}

void dns_server_reply_error(  dns_server_t *dev,
                                            dns_header_t *dns_header,
                                            dns_reply_code_t rep_code,
                                            unsigned char *query,
                                            size_t query_length)
{
    dns_server_param_t *dns_sv_param = dev->reverse;
    remot_info *premot = NULL;

    dns_header->flags.resp_bit.QR = DNS_QR_RESPONSE;
    dns_header->flags.resp_bit.RCode = (unsigned char) rep_code;
    if (query){
        dns_header->QDCount = lwip_htons(1);
    }
    else{
        dns_header->QDCount = 0;
    }
    dns_header->ANCount = 0;
    dns_header->NSCount = 0;
    dns_header->ARCount = 0;

    size_t response_len = sizeof(dns_header_t) + query_length;
    char * response_buf = malloc(response_len);
    /* Lấy dữ liệu header */
    memcpy(response_buf, (char *)dns_header, sizeof(dns_header_t));
    /* Lấy dữ liệu query */
    memcpy(response_buf + sizeof(dns_header_t), (char *)query, query_length);

    /* Gửi dữ liệu udp */
    // Cấu hình lại report port mỗi lần gửi dữ liệu UDP
    // chi tiết trong esp8266_non_os_sdk_api_reference 4.1.10 trang 109/164
    if (espconn_get_connection_info(dev, &premot, 0) != ESPCONN_OK) return;
    dns_sv_param->espudp.remote_port = premot->remote_port;
    memcpy(dns_sv_param->espudp.remote_ip, premot->remote_ip, 4);
    espconn_sendto(dev, response_buf, response_len);

    free(response_buf);
}

void dns_server_reply_ip( dns_server_t *dev,
                                        dns_header_t *dns_header,
			                            uint8_t * query,
			                            size_t query_length)
{
    uint16_t value;
    uint32_t value_32;
    dns_server_param_t *dns_sv_param = dev->reverse;
    remot_info *premot = NULL;

    dns_header->flags.resp_bit.QR = DNS_QR_RESPONSE;
    dns_header->QDCount = lwip_htons(1);
    dns_header->ANCount = lwip_htons(1);
    dns_header->NSCount = 0;
    dns_header->ARCount = 0;

    size_t response_len = sizeof(dns_header_t) + query_length + 16;
    char * response_buf = malloc(response_len);

    /* Lấy dữ liệu header */
    memcpy(response_buf, (char *)dns_header, sizeof(dns_header_t));
    /* Lấy dữ liệu query */
    memcpy(response_buf + sizeof(dns_header_t), (char *)query, query_length);

    // Thay vì ghi lại domain thì sử dụng con trỏ với Byte đầu tiên là 192 và byte tiếp theo là vị trí của domain ở phần header trên
    value = lwip_htons(0xC000 | sizeof(dns_header_t));
    response_buf[sizeof(dns_header_t) + query_length] = ((uint8_t *)&value)[0];
    response_buf[sizeof(dns_header_t) + query_length + 1] = ((uint8_t *)&value)[1];

    // Answer is type A (an IPv4 address)
    value = lwip_htons(DNS_QTYPE_A);
    response_buf[sizeof(dns_header_t) + query_length + 2] = ((uint8_t *)&value)[0];
    response_buf[sizeof(dns_header_t) + query_length + 3] = ((uint8_t *)&value)[1];

    // Answer is in the Internet Class
    value = lwip_htons(DNS_QCLASS_IN);
    response_buf[sizeof(dns_header_t) + query_length + 4] = ((uint8_t *)&value)[0];
    response_buf[sizeof(dns_header_t) + query_length + 5] = ((uint8_t *)&value)[1];

    // Output TTL (already NBO)
    value_32 = lwip_htonl(60);
    response_buf[sizeof(dns_header_t) + query_length + 6] = ((uint8_t *)&value_32)[0];
    response_buf[sizeof(dns_header_t) + query_length + 7] = ((uint8_t *)&value_32)[1];
    response_buf[sizeof(dns_header_t) + query_length + 8] = ((uint8_t *)&value_32)[2];
    response_buf[sizeof(dns_header_t) + query_length + 9] = ((uint8_t *)&value_32)[3];

    // Độ dài của RData là 4Byte vì nó là IPv4
    value = lwip_htons(4);
    response_buf[sizeof(dns_header_t) + query_length + 10] = ((uint8_t *)&value)[0];
    response_buf[sizeof(dns_header_t) + query_length + 11] = ((uint8_t *)&value)[1];
    // RData
    response_buf[sizeof(dns_header_t) + query_length + 12] = ip4_addr1(&dns_sv_param->resolve_ip.addr);
    response_buf[sizeof(dns_header_t) + query_length + 13] = ip4_addr2(&dns_sv_param->resolve_ip.addr);
    response_buf[sizeof(dns_header_t) + query_length + 14] = ip4_addr3(&dns_sv_param->resolve_ip.addr);
    response_buf[sizeof(dns_header_t) + query_length + 15] = ip4_addr4(&dns_sv_param->resolve_ip.addr);

    /* --- Gửi dữ liệu udp --- */
    // Cấu hình lại report port mỗi lần gửi dữ liệu UDP
    // chi tiết trong esp8266_non_os_sdk_api_reference 4.1.10 trang 109/164
    if (espconn_get_connection_info(dev, &premot, 0) != ESPCONN_OK) return;
    dns_sv_param->espudp.remote_port = premot->remote_port;
    memcpy(dns_sv_param->espudp.remote_ip, premot->remote_ip, 4);
    espconn_sendto(dev, response_buf, response_len);

    free(response_buf);
}
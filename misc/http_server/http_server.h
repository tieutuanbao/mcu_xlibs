#ifndef __HTTP_SERVER_H
#define __HTTP_SERVER_H

#include "env.h"

#include "lwip/err.h"

#include <stdint.h>
#include <stdbool.h>

/* Max supported HTTP request header length */
#define HTTP_MAX_REQ_HDR_LEN    CONFIG_HTTP_MAX_REQ_HDR_LEN

/* Max supported HTTP request URI length */
#define HTTP_MAX_URI_LEN        CONFIG_HTTP_MAX_URI_LEN

/**
 * @brief   HTTP Server Instance Handle
 *
 * Every instance of the server will have a unique handle.
 */
typedef void* http_handle_t;
/**
 * @brief   HTTP Method Type wrapper over "enum http_method"
 *          available in "http_parser" library
 */
typedef enum http_method httpd_method_t;

/* Request Methods */
typedef enum {
    HTTP_METHOD_DELETE  =   0,
    HTTP_METHOD_GET,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    /* pathological */
    HTTP_METHOD_CONNECT,
    HTTP_METHOD_OPTION,
    HTTP_METHOD_TRACE,
    /* WebDAV */ 
    HTTP_METHOD_COPY
} http_method_t;

typedef struct httpd_req {
    http_handle_t   handle;                     /*!< Handle to server instance */
    int             method;                     /*!< The type of HTTP request, -1 if unsupported method */
    const char      uri[HTTP_MAX_URI_LEN + 1];  /*!< The URI of this request (1 byte extra for null termination) */
    size_t          content_len;                /*!< Length of the request body */
} http_req_t;

typedef struct {
    const char *uri;
    http_method_t method;
    err_t (*handler)(http_req_t *r);
} http_uri_t;

typedef struct {
    int *socket_list;
    uint16_t max_connection;
    http_uri_t *uri_list;
} http_server_t;


http_server_t *http_server(uint16_t local_port);

#endif
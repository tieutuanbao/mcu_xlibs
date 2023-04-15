#ifndef __SIM7600_HANDLER_H
#define __SIM7600_HANDLER_H

#include "simcom_7600.h"

extern void sim7600_suddenly_handler(SIM7600_t *module);

extern void sim7600_ATCMD_resp_handler(SIM7600_t *module);

extern void sim7600_AT_handler(SIM7600_t *module);

extern void sim7600_ATCMGR_Handler(SIM7600_t *module);
extern void sim7600_ATCMGR_param_Handler(SIM7600_t *module);
extern void sim7600_ATCMGR_data_Handler(SIM7600_t *module);

extern void sim7600_ATD_Handler(SIM7600_t *module);

#endif
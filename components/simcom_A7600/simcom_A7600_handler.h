#ifndef __SIM7600_HANDLER_H
#define __SIM7600_HANDLER_H

#include "simcom_A7600.h"

extern void sim7600_suddenly_handler(sim7600_t *module);

extern void sim7600_ATCMD_resp_handler(sim7600_t *module);

extern void sim7600_AT_handler(sim7600_t *module);

extern void sim7600_ATCMGR_Handler(sim7600_t *module);
extern void sim7600_ATCMGR_param_Handler(sim7600_t *module);
extern void sim7600_ATCMGR_data_Handler(sim7600_t *module);

extern void sim7600_ATD_Handler(sim7600_t *module);

#endif
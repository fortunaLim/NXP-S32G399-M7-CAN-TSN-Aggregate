/*
 * TSN_SKKU.h
 *
 *  Created on: 2024. 8. 5.
 *      Author: sh970
 */

#ifndef ETH_SKKU_H_
#define ETH_SKKU_H_

#include "device.h"
#include "math.h"
#include "stdlib.h"
#include "Gmac_Ip.h"
#include "string.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "lwip/etharp.h"
#include "lwip/tcpip.h"
#include "lwipcfg.h"
#include "lwip/sys.h"
#include "gmacif.h"
#include "Gmac_Ip.h"
#include "Gmac_Ip_Hw_Access.h"
#include "netifcfg.h"
#include "FreeRTOS.h"
#include "Siul2_Dio_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Eth_GeneralTypes.h" /* Mandatory include - see the SWS */
#include "MCAL_lib_SKKU.h"
#include "Eth.h"


void TSN_init();
void Eth_RxIrqCallback_SKKU(const uint8 CtrlIdx, const uint8 DMAChannel);
void read_status( void *pvParameters );
void tas_trans_test( void *pvParameters );
void PDU_Decoder( void *pvParameters );
void Eth2CAN_send( void *pvParameters );
void start_TSN();
void Eth_Receive_SKKU(uint8 CtrlIdx,
                 uint8 FifoIdx,
                 Eth_RxStatusType *RxStatusPtr,
				 uint8 **R_FrameData
                );

#endif /* ETH_SKKU_H_ */

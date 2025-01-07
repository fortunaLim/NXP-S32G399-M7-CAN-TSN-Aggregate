/*
 * FlexCAN_SKKU.h
 *
 *  Created on: 2024. 7. 15.
 *      Author: sh970
 */

#ifndef FLEXCAN_SKKU_H_
#define FLEXCAN_SKKU_H_

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
#include "Gmac_Ip.h"
#include "Gmac_Ip_Hw_Access.h"
#include "netifcfg.h"
#include "FreeRTOS.h"
#include "Siul2_Dio_Ip.h"
#include "Siul2_Port_Ip.h"
#include "FlexCAN_Ip_Sa_PBcfg.h"
#include "FlexCAN_Ip_Types.h"




uint32 Gmac_Ip_ReadGateControlList(uint8 Instance, uint16 AddrGateList);
uint8 get_current_slot();
void FlexCAN_init_SKKU();
void CAN_SendTask( void *pvParameters );
void CAN_SendTask1( void *pvParameters );
void CAN_SendTask2( void *pvParameters );
void CAN_SendTask3( void *pvParameters );
void ETH_Traffic_Send( void *pvParameters );
void CAN_ReceiveTask( void *pvParameters );
void ETH_PDU_Send( void *pvParameters );

void start_CAN();
void CAN0_Callback_SKKU(uint8 instance, Flexcan_Ip_EventType eventType,
                  uint32 buffIdx, const Flexcan_Ip_StateType * flexcanState);


#endif /* FLEXCAN_SKKU_H_ */

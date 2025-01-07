/*
 * MCAL_lib_SKKU.h
 *
 *  Created on: 2024. 8. 6.
 *      Author: sh970
 */

#ifndef MCAL_LIB_SKKU_H_
#define MCAL_LIB_SKKU_H_


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
#include "GMAC_PTP_SKKU.h"


/**************************************************************************/
// Vlan
/**************************************************************************/
//Eth_Vlan_setting();
/*Gmac_Ip_VlanConfigType gmac_0_vlanConfig =
{
	 .enDoubleVlan =  TRUE,
	 .enSvlan =  FALSE,
	 .outerVlanIns =  GMAC_VLAN_TAG_INSERTION,
	 .innerVlanIns =  GMAC_VLAN_TAG_INSERTION,
	 .outerVlanStrip =  GMAC_VLAN_TAG_DO_NOT_STRIP,
	 .innerVlanStrip =  GMAC_VLAN_TAG_DO_NOT_STRIP,
};

Gmac_Ip_VlanRxFilterType gmac_0_vlanRxFilterConfig = {
 .enInnerVlanMatch =  FALSE,
 .enSvlanMatch =  FALSE,
 .disVlanTypeMatch =  FALSE,
 .enInverseMatch =  FALSE,
 .en12bitMatch =  TRUE,
};*/



void Eth_Trans_SKKU(uint8 Des_MAC[6], uint8 Src_MAC[6], uint8 Type[4], uint8 *Payload, uint8 Payload_Size);


#endif /* MCAL_LIB_SKKU_H_ */

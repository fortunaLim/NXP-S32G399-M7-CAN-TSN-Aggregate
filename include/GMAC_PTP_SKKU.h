#ifndef GMAC_PTP_SKKU_H
#define GMAC_PTP_SKKU_H

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
#include "ComStackTypes.h" /* Mandatory include - see the SWS */
#include "Eth_Ipw.h"
#include "Eth.h"
#include "FlexCAN_SKKU.h"
#include "FlexCAN_Ip_Sa_PBcfg.h"
#include "FlexCAN_Ip_Types.h"
#include "FlexCAN_Ip.h"
#include "ETH_SKKU.h"

#define PTP_UPDT_MODE 3 //1: software / 2: hardware
#define PTP_Master 1
#define PTP_Slave 0


/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
#define ETH_FRAME_MACDST_OFFSET     (0U)
#define ETH_FRAME_MACSRC_OFFSET     (6U)
#define ETH_FRAME_ETHTYPE_OFFSET    (12U)
#define ETH_FRAME_PAYLOAD_OFFSET    (14U)

#define ETH_FRAME_MACDST_LENGTH     (6U)
#define ETH_FRAME_MACSRC_LENGTH     (6U)
#define ETH_FRAME_ETHTYPE_LENGTH    (2U)
#define ETH_FRAME_HEADER_LENGTH     (ETH_FRAME_MACDST_LENGTH + ETH_FRAME_MACSRC_LENGTH + ETH_FRAME_ETHTYPE_LENGTH)

#define ETH_BUFFER_INDEX_UNUSED     (0U)


/* PTP */
#define Typ_PTP                             0x88F7
#define IEEE1588v2                          0x02
#define Sync                                0x0
#define Delay_Req                           0x1
#define Pdelay_Req                          0x2
#define Pdelay_Resp                         0x3
#define Follow_Up                           0x8
#define Delay_Res                           0x9
#define Pdelay_Resp_Follow_Up               0xa
#define Announce                            0xb
#define Signaling                           0xc

/* PIT instance used - 0 */
#define PIT_INST_0 0U
/* PIT Channel used - 0 */
#define CH_0 0U
/* PIT time-out period - equivalent to 1s */
#define PIT_PERIOD 40000


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/



/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

void sendSynchronization();
void sendFollowUp();
void sendDealyReq();
void sendDelayResp();

inline void Total_time(sint64 * total_time ,uint32 sec, uint32 nano_sec);
void PTP_init();
inline void PTP_Update_func();
void Print_IO();
void start_PTP();
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void Eth_TxIrqCallback_SKKU(uint8 instance, uint8 channel);

//static inline void Eth_Local_Memcpy(uint8 *Dst, const uint8 *Src, uint8 BytesNum);
void Eth_Local_Memcpy(uint8 *Dst, const uint8 *Src, uint32 BytesNum);
/*==================================================================================================
*
==================================================================================================*/
typedef struct {

    /////////////////////////////////////////
    /** IEEE 1588v2 Layer (PTP version 2) **/
    /////////////////////////////////////////

    uint8                 MsgType         : 4;
    uint8                 trans_Spec      : 4;
    uint8                 versionPTP      : 4;
    uint8                 Reserved_a      : 4;
    uint8                 MsgLength[2];
    uint8                 DomainNumber;
    uint8                 Reserved_b;
    uint8                 flags[2];
    uint8                 correctField[8];
    uint8                 Reserved_c[4];
    uint8                 SrcClockID[8]; //???
    uint8                 SrcPortNum[2];
    uint8                 SequenceID[2];
    uint8                 ControlField;
    uint8                 LogMsgInterval;

    uint8                 orgTimeStamp_sec[6];
    uint8                 orgTimeStamp_nano[4];
    uint8                 Padding[8];

    /////////////////////////////////////////
    /** Delay_Response (Extra Frame) **/
    /////////////////////////////////////////

    //uint8_t             req_Src_PortIdentity[ETH_HEAD_SIZE_6B];
    uint8                 req_Src_PortId[2];

} Ptp_PayloadTpye;


/**
* @brief        Transmit & receive in internal loopback mode
* @details
*/

#endif


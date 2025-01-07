/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : GMAC
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 4.0.2
*   Build Version        : S32_RTD_4_0_2_D2306_ASR_REL_4_4_REV_0000_20230630
*
*   Copyright 2020-2023 NXP Semiconductors
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/*   @implements Gmac_Ip_PBcfg.c_Artifact */
/**
*   @file
*
*   @addtogroup GMAC_DRIVER_CONFIGURATION GMAC Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Gmac_Ip_Types.h"
#include "Gmac_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define GMAC_IP_PBCFG_VENDOR_ID_C                     43
#define GMAC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define GMAC_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C      4
#define GMAC_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define GMAC_IP_PBCFG_SW_MAJOR_VERSION_C              4
#define GMAC_IP_PBCFG_SW_MINOR_VERSION_C              0
#define GMAC_IP_PBCFG_SW_PATCH_VERSION_C              2

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Gmac_Ip_Types.h */
#if (GMAC_IP_PBCFG_VENDOR_ID_C != GMAC_IP_TYPES_VENDOR_ID)
    #error "Gmac_Ip_PBcfg.c and Gmac_Ip_Types.h have different vendor ids"
#endif
#if ((GMAC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != GMAC_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (GMAC_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C    != GMAC_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (GMAC_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != GMAC_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Gmac_Ip_PBcfg.c and Gmac_Ip_Types.h are different"
#endif
#if ((GMAC_IP_PBCFG_SW_MAJOR_VERSION_C != GMAC_IP_TYPES_SW_MAJOR_VERSION) || \
     (GMAC_IP_PBCFG_SW_MINOR_VERSION_C != GMAC_IP_TYPES_SW_MINOR_VERSION) || \
     (GMAC_IP_PBCFG_SW_PATCH_VERSION_C != GMAC_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Gmac_Ip_PBcfg.c and Gmac_Ip_Types.h are different"
#endif

/* Checks against Gmac_Ip_Cfg.h */
#if (GMAC_IP_PBCFG_VENDOR_ID_C != GMAC_IP_CFG_VENDOR_ID)
    #error "Gmac_Ip_PBcfg.c and Gmac_Ip_Cfg.h have different vendor ids"
#endif
#if ((GMAC_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != GMAC_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (GMAC_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C    != GMAC_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (GMAC_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != GMAC_IP_CFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Gmac_Ip_PBcfg.c and Gmac_Ip_Cfg.h are different"
#endif
#if ((GMAC_IP_PBCFG_SW_MAJOR_VERSION_C != GMAC_IP_CFG_SW_MAJOR_VERSION) || \
     (GMAC_IP_PBCFG_SW_MINOR_VERSION_C != GMAC_IP_CFG_SW_MINOR_VERSION) || \
     (GMAC_IP_PBCFG_SW_PATCH_VERSION_C != GMAC_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Gmac_Ip_PBcfg.c and Gmac_Ip_Cfg.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define GMAC_MAC_ADDR_LENGTH        (6U)

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define ETH_START_SEC_CODE
#include "Eth_MemMap.h"

/*! @brief Channel callbacks external declarations */
extern void Eth_RxIrqCallback_SKKU(uint8 instance, uint8 channel);
extern void Eth_TxIrqCallback(uint8 instance, uint8 channel);

#define ETH_STOP_SEC_CODE
#include "Eth_MemMap.h"

/*==================================================================================================
*                                      BUFFER DECLARATIONS
==================================================================================================*/
#define ETH_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"

extern Gmac_Ip_BufferDescriptorType GMAC_0_RxRing_0_DescBuffer[];
extern uint8 GMAC_0_RxRing_0_DataBuffer[];
extern Gmac_Ip_BufferDescriptorType GMAC_0_TxRing_0_DescBuffer[];
extern uint8 GMAC_0_TxRing_0_DataBuffer[];
extern Gmac_Ip_BufferDescriptorType GMAC_0_TxRing_1_DescBuffer[];
extern uint8 GMAC_0_TxRing_1_DataBuffer[];
extern Gmac_Ip_BufferDescriptorType GMAC_0_TxRing_2_DescBuffer[];
extern uint8 GMAC_0_TxRing_2_DataBuffer[];

#define ETH_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"

/*==================================================================================================
*                                   STATE STRUCTURE DECLARATIONS
==================================================================================================*/
#define ETH_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_MemMap.h"

extern Gmac_Ip_StateType GMAC_0_StateStructure;

#define ETH_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_MemMap.h"

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"


/*! @brief The MAC address(es) of the configured controller(s) */
static const uint8 GMAC_0_au8MacAddrPB[GMAC_MAC_ADDR_LENGTH] = { 0x00U, 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

/*! @brief Reception ring configuration structures */
static const Gmac_Ip_RxRingConfigType GMAC_0_aRxRingConfigPB[1U] =
{
    /* The configuration structure for Rx Ring 0 */
    {
        /*.ringDesc = */GMAC_0_RxRing_0_DescBuffer,
        /*.callback = */Eth_RxIrqCallback_SKKU,
        /*.buffer = */GMAC_0_RxRing_0_DataBuffer,
        /*.interrupts = */(uint32)GMAC_CH_INTERRUPT_RI,
        /*.bufferLen = */512U,
        /*.ringSize = */256U,
        /*.priorityMask = */(uint8)GMAC_VLAN_PRIORITY_0,
        /*.dmaBurstLength = */64U
    }
};

/*! @brief Transmission ring configuration structures */
static const Gmac_Ip_TxRingConfigType GMAC_0_aTxRingConfigPB[3U] =
{
    /* The configuration structure for Tx Ring 0 */
    {
        /*.weight = */0U,
        /*.idleSlopeCredit = */0U,
        /*.sendSlopeCredit = */0U,
        /*.hiCredit = */0U,
        /*.loCredit = */0,
        /*.ringDesc = */GMAC_0_TxRing_0_DescBuffer,
        /*.callback = */Eth_TxIrqCallback,
        /*.buffer = */GMAC_0_TxRing_0_DataBuffer,
        /*.interrupts = */(uint32)GMAC_CH_INTERRUPT_TI,
        /*.bufferLen = */1456U,
        /*.ringSize = */128U,
        /*.priorityMask = */(uint8)GMAC_VLAN_PRIORITY_0,
        /*.dmaBurstLength = */64U,
        /*.queueOpMode = */GMAC_OP_MODE_DCB_GEN
    },
    /* The configuration structure for Tx Ring 1 */
    {
        /*.weight = */0U,
        /*.idleSlopeCredit = */0U,
        /*.sendSlopeCredit = */0U,
        /*.hiCredit = */0U,
        /*.loCredit = */0,
        /*.ringDesc = */GMAC_0_TxRing_1_DescBuffer,
        /*.callback = */Eth_TxIrqCallback,
        /*.buffer = */GMAC_0_TxRing_1_DataBuffer,
        /*.interrupts = */(uint32)GMAC_CH_INTERRUPT_TI,
        /*.bufferLen = */1456U,
        /*.ringSize = */128U,
        /*.priorityMask = */(uint8)GMAC_VLAN_PRIORITY_1,
        /*.dmaBurstLength = */64U,
        /*.queueOpMode = */GMAC_OP_MODE_DCB_GEN
    },
    /* The configuration structure for Tx Ring 2 */
    {
        /*.weight = */0U,
        /*.idleSlopeCredit = */0U,
        /*.sendSlopeCredit = */0U,
        /*.hiCredit = */0U,
        /*.loCredit = */0,
        /*.ringDesc = */GMAC_0_TxRing_2_DescBuffer,
        /*.callback = */Eth_TxIrqCallback,
        /*.buffer = */GMAC_0_TxRing_2_DataBuffer,
        /*.interrupts = */(uint32)GMAC_CH_INTERRUPT_TI,
        /*.bufferLen = */1456U,
        /*.ringSize = */128U,
        /*.priorityMask = */(uint8)GMAC_VLAN_PRIORITY_2,
        /*.dmaBurstLength = */64U,
        /*.queueOpMode = */GMAC_OP_MODE_DCB_GEN
    }
};

/*! @brief Module configuration structures */
static const Gmac_Ip_ConfigType GMAC_0_InitConfigPB =
{
    /*.rxRingCount = */1U,
    /*.txRingCount = */3U,
#if (FEATURE_GMAC_ASP_ALL || FEATURE_GMAC_ASP_ECC)
    /*.safetyInterrupts = */0U,
    /*.safetyCallback = */NULL_PTR,
#endif
    /*.interrupts = */0U,
    /*.callback = */NULL_PTR,
    /*.miiMode = */GMAC_RGMII_MODE,
    /*.txSchedAlgo = */GMAC_SCHED_ALGO_SP,
    /*.speed = */GMAC_SPEED_1G,
    /*.duplex = */GMAC_FULL_DUPLEX,
    /*.macConfig = */0U | (uint32)GMAC_MAC_CONFIG_CRC_STRIPPING | (uint32)GMAC_MAC_CONFIG_AUTO_PAD,
    /*.macPktFilterConfig = */0U | (uint32)GMAC_PKT_FILTER_RECV_ALL | (uint32)GMAC_PKT_FILTER_HASH_OR_PERFECT_FILTER,
    /*.enableCtrl = */FALSE
};

static const Gmac_Ip_TxGateControl GMAC_0_GateControlListPB[4U]  =
{
    {
        /*.timeInterval = */1000000U,
        /*.gateControlFifo = */1U
    },
    {
        /*.timeInterval = */5000000U,
        /*.gateControlFifo = */2U
    },
    {
        /*.timeInterval = */3984000U,
        /*.gateControlFifo = */4U
    },
    {
        /*.timeInterval = */16000U,
        /*.gateControlFifo = */0U
    }
};
static const Gmac_Ip_TxTimeAwareShaper GMAC_0_pTxTimeShaperPB =
{
    /*.baseTimeSecond = */0U,
    /*.baseTimenanoSecond = */0U,
    /*.cycleTimeSecond = */0U,
    /*.cycleTimeNanoSecond = */10000000U,
    /*.extendedTime = */0U,
    /*.gateControlListDepth = */4U,
    /*.releaseAdvanceTime = */0U,
    /*.holdAdvanceTime = */0U,
    /*.preemptionClassification = */0U,
    /*.GateControlList = */GMAC_0_GateControlListPB
};

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"
/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

const Gmac_CtrlConfigType Gmac_aCtrlConfigPB[1U] =
{
    /* The configuration structure for Gmac_aCtrlConfig[0U] */
    {
        &GMAC_0_StateStructure,
        &GMAC_0_InitConfigPB,
        &GMAC_0_aRxRingConfigPB[0U],
        &GMAC_0_aTxRingConfigPB[0U],
        &GMAC_0_au8MacAddrPB[0U],
        &GMAC_0_pTxTimeShaperPB
    }
};

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */


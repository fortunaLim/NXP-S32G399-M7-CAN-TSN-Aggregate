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

#ifndef ETH_PBCFG_H
#define ETH_PBCFG_H

/**
*   @file
*
*   @addtogroup ETH_DRIVER_CONFIGURATION Ethernet Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_PBCFG_VENDOR_ID                     43
#define ETH_PBCFG_AR_RELEASE_MAJOR_VERSION      4
#define ETH_PBCFG_AR_RELEASE_MINOR_VERSION      4
#define ETH_PBCFG_AR_RELEASE_REVISION_VERSION   0
#define ETH_PBCFG_SW_MAJOR_VERSION              4
#define ETH_PBCFG_SW_MINOR_VERSION              0
#define ETH_PBCFG_SW_PATCH_VERSION              2

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/


#ifndef ETH_MDIO_CLAUSE22_API
    #define ETH_MDIO_CLAUSE22_API    (STD_ON)
#endif

#ifndef ETH_MDIO_CLAUSE45_API
    #define ETH_MDIO_CLAUSE45_API    (STD_ON)
#endif

#ifndef ETH_RX_IRQ_ENABLED
    #define ETH_RX_IRQ_ENABLED      (STD_ON)
#endif

#ifndef ETH_TX_IRQ_ENABLED
    #define ETH_TX_IRQ_ENABLED        (STD_ON)
#endif

#ifndef EthConf_EthCtrlConfig_EthCtrlConfig_0
    #define EthConf_EthCtrlConfig_EthCtrlConfig_0    (0U)
#elif (EthConf_EthCtrlConfig_EthCtrlConfig_0 != 0)
    #error "[TPS_ECUC_06074] Invalid configuration due to symbolic name values"
#endif

#ifndef EthConf_EthCtrlConfigIngressFifo_EthCtrlConfigIngressFifo_0
    #define EthConf_EthCtrlConfigIngressFifo_EthCtrlConfigIngressFifo_0        (0U)
#elif (EthConf_EthCtrlConfigIngressFifo_EthCtrlConfigIngressFifo_0 != 0)
    #error "[TPS_ECUC_06074] Invalid configuration due to symbolic name values"
#endif

/* Maximum number of configured Tx FIFOs */
#ifndef ETH_MAX_TXFIFO_SUPPORTED
    #define ETH_MAX_TXFIFO_SUPPORTED        (3U)
#elif (ETH_MAX_TXFIFO_SUPPORTED < 3)
    #undef ETH_MAX_TXFIFO_SUPPORTED
    #define ETH_MAX_TXFIFO_SUPPORTED        (3U)
#endif

/* Maximum number of configured Rx FIFOs */
#ifndef ETH_MAX_RXFIFO_SUPPORTED
    #define ETH_MAX_RXFIFO_SUPPORTED        (1U)
#elif (ETH_MAX_RXFIFO_SUPPORTED < 1)
    #undef ETH_MAX_RXFIFO_SUPPORTED
    #define ETH_MAX_RXFIFO_SUPPORTED        (1U)
#endif

/* Maximum number of configured buffers per Tx FIFO */
#ifndef ETH_MAX_TXBUFF_SUPPORTED
    #define ETH_MAX_TXBUFF_SUPPORTED        (32U)
#elif (ETH_MAX_TXBUFF_SUPPORTED < 32)
    #undef ETH_MAX_TXBUFF_SUPPORTED
    #define ETH_MAX_TXBUFF_SUPPORTED        (32U)
#endif

/* Maximum number of configured buffers per Rx FIFO */
#ifndef ETH_MAX_RXBUFF_SUPPORTED
    #define ETH_MAX_RXBUFF_SUPPORTED        (256U)
#elif (ETH_MAX_RXBUFF_SUPPORTED < 256)
    #undef ETH_MAX_RXBUFF_SUPPORTED
    #define ETH_MAX_RXBUFF_SUPPORTED        (256U)
#endif

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ETH_PBCFG_H */


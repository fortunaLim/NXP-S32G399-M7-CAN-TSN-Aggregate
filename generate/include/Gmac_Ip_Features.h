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

#ifndef GMAC_IP_FEATURES_H
#define GMAC_IP_FEATURES_H

/**
*   @file
*
*   @addtogroup GMAC_DRIVER_CONFIGURATION GMAC Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*
* @page misra_violations MISRA-C:2012 violations
*
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define GMAC_IP_FEATURES_VENDOR_ID                    43
#define GMAC_IP_FEATURES_AR_RELEASE_MAJOR_VERSION     4
#define GMAC_IP_FEATURES_AR_RELEASE_MINOR_VERSION     4
#define GMAC_IP_FEATURES_AR_RELEASE_REVISION_VERSION  0
#define GMAC_IP_FEATURES_SW_MAJOR_VERSION             4
#define GMAC_IP_FEATURES_SW_MINOR_VERSION             0
#define GMAC_IP_FEATURES_SW_PATCH_VERSION             2

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

    /*! @brief Number of instances */
    #define FEATURE_GMAC_NUM_INSTANCES              (1U)
    /*! @brief Number of DMA channels (Assumption: DmaChannels = TxQueues = Rx Queues) */
    #define FEATURE_GMAC_NUM_CHANNELS               (5U)
    /*! @brief Number of MTL queues (Assumption: TxQueues = Rx Queues) */
    #define FEATURE_GMAC_NUM_QUEUES                 (5U)

    /*! @brief The common interrupts */
    #define FEATURE_GMAC_COMMON_IRQS                { GMAC0_Common_IRQn }
    /*! @brief The transmission interrupts */
    #define FEATURE_GMAC_TX_IRQS                    { {GMAC0_CH0_TX_IRQn, GMAC0_CH1_TX_IRQn, GMAC0_CH2_TX_IRQn, GMAC0_CH3_TX_IRQn, GMAC0_CH4_TX_IRQn} }
    /*! @brief The reception interrupts */
    #define FEATURE_GMAC_RX_IRQS                    { {GMAC0_CH0_RX_IRQn, GMAC0_CH1_RX_IRQn, GMAC0_CH2_RX_IRQn, GMAC0_CH3_RX_IRQn, GMAC0_CH4_RX_IRQn} }

    /*! @brief The common interrupt handlers */
    #define FEATURE_GMAC_COMMON_IRQ_HDLRS           { GMAC0_Common_IRQHandler }
    /*! @brief The transmission interrupt handlers */
    #define FEATURE_GMAC_TX_IRQ_HDLRS               { {GMAC0_CH0_TX_IRQHandler, GMAC0_CH1_TX_IRQHandler, GMAC0_CH2_TX_IRQHandler, GMAC0_CH3_TX_IRQHandler, GMAC0_CH4_TX_IRQHandler} }
    /*! @brief The reception interrupts handlers */
    #define FEATURE_GMAC_RX_IRQ_HDLRS               { {GMAC0_CH0_RX_IRQHandler, GMAC0_CH1_RX_IRQHandler, GMAC0_CH2_RX_IRQHandler, GMAC0_CH3_RX_IRQHandler, GMAC0_CH4_RX_IRQHandler} }

    /*! @brief Definitions used for the different IRQ configurations */
    #define FEATURE_GMAC_UNIFIED_CH_IRQS            (0U)
    #define FEATURE_GMAC_INDIVIDUAL_CH_IRQS         (1U)

    /*! @brief Definition used for aligning the buffer pools and buffer descriptors */
    #define FEATURE_GMAC_DATA_BUS_WIDTH_BITS        (64UL)
    #define FEATURE_GMAC_DATA_BUS_WIDTH_BYTES       (FEATURE_GMAC_DATA_BUS_WIDTH_BITS / 8UL)
    #define FEATURE_GMAC_LOG2_DATA_BUS_WIDTH_BYTES  (3UL)
    /*! @brief Maximum number of beats in a a data-bus (AXI/AHB) burst */
    #define FEATURE_GMAC_MAX_DATA_BUS_BURST_LENGTH  (32UL)
    /*! @brief Definition used for aligning the buffer descriptors */
    #define FEATURE_GMAC_BUFFDESCR_ALIGNMENT_BITS   (FEATURE_GMAC_DATA_BUS_WIDTH_BITS)
    #define FEATURE_GMAC_BUFFDESCR_ALIGNMENT_BYTES  (FEATURE_GMAC_DATA_BUS_WIDTH_BYTES)
    /*! @brief Definition used for aligning the buffer pools */
    #define FEATURE_GMAC_BUFF_ALIGNMENT_BITS        (FEATURE_GMAC_MAX_DATA_BUS_BURST_LENGTH * FEATURE_GMAC_DATA_BUS_WIDTH_BITS)
    #define FEATURE_GMAC_BUFF_ALIGNMENT_BYTES       (FEATURE_GMAC_MAX_DATA_BUS_BURST_LENGTH * FEATURE_GMAC_DATA_BUS_WIDTH_BYTES)
    /*! @brief Definition used for aligning the buffer length */
    #define FEATURE_GMAC_BUFFLEN_ALIGNMENT_BYTES    (FEATURE_GMAC_DATA_BUS_WIDTH_BYTES)

    /*! @brief Minimum allocatable unit in a Tx FIFO */
    #define FEATURE_GMAC_MTL_TX_FIFO_BLOCK_SIZE     (256U)
    /*! @brief Minimum allocatable unit in an Rx FIFO */
    #define FEATURE_GMAC_MTL_RX_FIFO_BLOCK_SIZE     (256U)

    /*! @brief MTL Transmit FIFO Pool Size */
    #define FEATURE_GMAC_MTL_RX_POOL_SIZE           (16384U)
    /*! @brief MTL Receive FIFO Pool Size */
    #define FEATURE_GMAC_MTL_TX_POOL_SIZE           (16384U)

    /*! @brief Definition used for aligning the total ring length (ringSize * buffLen) */
    #define FEATURE_GMAC_TXRINGLEN_ALIGNMENT_BYTES  (FEATURE_GMAC_MTL_TX_FIFO_BLOCK_SIZE)
    /*! @brief Definition used for aligning the total ring length (ringSize * buffLen) */
    #define FEATURE_GMAC_RXRINGLEN_ALIGNMENT_BYTES  (FEATURE_GMAC_MTL_RX_FIFO_BLOCK_SIZE)

    /*! @brief Definitions used for the Application Interface Parameters */
    #define FEATURE_GMAC_DATA_BUS_AXI               (1U)
    #define FEATURE_GMAC_DATA_BUS_AHB               (0U)

    /*! @brief Definitions used for the PHY Interface Parameters */
    #define FEATURE_GMAC_RGMII_EN                   (1U)
    #define FEATURE_GMAC_SGMII_EN                   (1U)
    #define FEATURE_GMAC_SMII_EN                    (0U)

    /*! @brief Definitions used for the Low Power Management Parameters */
    #define FEATURE_GMAC_PMT_EN                     (1U)

    /*! @brief Definitions used for the TCPIP Offloading Parameters */
    #define FEATURE_GMAC_ARP_EN                     (1U)

    /*! @brief Definitions used for the Automotive Safety Parameters */
    #define FEATURE_GMAC_ASP_ALL                    (0U)
    #define FEATURE_GMAC_ASP_ECC                    (0U)

    /*! @brief Definitions used for the Filtering Parameters */
    #define FEATURE_GMAC_HASH_EN                    (1U)
    #define FEATURE_GMAC_HASH_TABLE_SZ              (256U)
    #define FEATURE_GMAC_HASH_TABLE_MSB_SHIFT       (24U)

    /*! @brief Number of VLAN Rx filters */
    #define FEATURE_GMAC_VLAN_RX_FILTERS_NUM        (32U)
    
/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* GMAC_IP_FEATURES_H */


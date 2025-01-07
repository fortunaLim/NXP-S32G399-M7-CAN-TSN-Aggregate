/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 4.0.2
*   Build Version        : S32_RTD_4_0_2_D2306_ASR_REL_4_4_REV_0000_20230630
*
*   Copyright 2020-2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef SIUL2_DIO_IP_CFG_H
#define SIUL2_DIO_IP_CFG_H

/**
*   @file Siul2_Dio_Ip_Cfg.h
*   @implements     Siul2_Dio_Ip_Cfg.h_Artifact
*
*   @addtogroup DIO_CFG
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
#include "S32G399A_SIUL2.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SIUL2_DIO_IP_VENDOR_ID_CFG_H                       43
#define SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_CFG_H        4
#define SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_CFG_H        4
#define SIUL2_DIO_IP_AR_RELEASE_REVISION_VERSION_CFG_H     0
#define SIUL2_DIO_IP_SW_MAJOR_VERSION_CFG_H                4
#define SIUL2_DIO_IP_SW_MINOR_VERSION_CFG_H                0
#define SIUL2_DIO_IP_SW_PATCH_VERSION_CFG_H                2

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define DIO_VIRTWRAPPER_SUPPORT        (STD_OFF)

/**
* @brief          Pre-processor switch to enable/disable development error detection for Dio Ip API
*
* @implements     Siul2_Dio_Ip_ErrorDetect_define
*/
#define SIUL2_DIO_IP_DEV_ERROR_DETECT                         (STD_OFF)

/* SIUL2 - GPIO Peripheral instance base addresses */
/* SIUL2_0 */
#define PTA ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_0->PGPDO0)))
#define PTB ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_0->PGPDO1)))
#define PTC ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_0->PGPDO2)))
#define PTD ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_0->PGPDO3)))
#define PTE ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_0->PGPDO4)))
#define PTF ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_0->PGPDO5)))
#define PTG ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_0->PGPDO6)))

/* SIUL2_1 */
#define PTH ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_1->PGPDO7)))
#define PTJ ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_1->PGPDO9)))
#define PTK ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_1->PGPDO10)))
#define PTL ((Siul2_Dio_Ip_GpioType *)(&(IP_SIUL2_1->PGPDO11)))

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SIUL2_DIO_IP_CFG_H */


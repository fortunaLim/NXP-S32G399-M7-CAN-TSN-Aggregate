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
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file      Siul2_Port_Ip_Cfg.c
*
*   @addtogroup Port_CFG
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
#include "Siul2_Port_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SIUL2_PORT_IP_VENDOR_ID_CFG_C                       43
#define SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_C        4
#define SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_C        4
#define SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_C     0
#define SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_C                4
#define SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_C                0
#define SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_C                2

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are of the same vendor */
#if (SIUL2_PORT_IP_VENDOR_ID_CFG_C != SIUL2_PORT_IP_VENDOR_ID_CFG_H)
    #error "Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are of the same Autosar version */
#if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_C    != SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
    (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_C    != SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
    (SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_C != SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are different"
#endif
/* Check if Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are of the same Software version */
#if ((SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_C != SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
    (SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_C != SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
    (SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_C != SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are different"
#endif

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
                                           GLOBAL VARIABLES
==================================================================================================*/

/* clang-format off */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: M7_0}
- pin_list:
  - {pin_num: V23, peripheral: GMAC_0, signal: gmac_mdc, pin_signal: PD_12}
  - {pin_num: R19, peripheral: GMAC_0, signal: gmac_md, pin_signal: PD_13, direction: INPUT/OUTPUT}
  - {pin_num: R21, peripheral: GMAC_0, signal: gmac_rx_clk, pin_signal: PE_08, direction: INPUT}
  - {pin_num: R23, peripheral: GMAC_0, signal: gmac_rx_dv, pin_signal: PE_09}
  - {pin_num: P19, peripheral: GMAC_0, signal: 'gmac_rx, 0', pin_signal: PE_10}
  - {pin_num: P18, peripheral: GMAC_0, signal: 'gmac_rx, 1', pin_signal: PE_11}
  - {pin_num: N18, peripheral: GMAC_0, signal: 'gmac_rx, 2', pin_signal: PE_12}
  - {pin_num: U21, peripheral: GMAC_0, signal: 'gmac_rx, 3', pin_signal: PE_13}
  - {pin_num: P20, peripheral: GMAC_0, signal: gmac_tx_clk, pin_signal: PE_02, direction: OUTPUT}
  - {pin_num: U23, peripheral: GMAC_0, signal: gmac_tx_en, pin_signal: PE_03, direction: OUTPUT}
  - {pin_num: T23, peripheral: GMAC_0, signal: 'gmac_tx, 0', pin_signal: PE_04, direction: OUTPUT}
  - {pin_num: T22, peripheral: GMAC_0, signal: 'gmac_tx, 1', pin_signal: PE_05, direction: OUTPUT}
  - {pin_num: U22, peripheral: GMAC_0, signal: 'gmac_tx, 2', pin_signal: PE_06, direction: OUTPUT}
  - {pin_num: T21, peripheral: GMAC_0, signal: 'gmac_tx, 3', pin_signal: PE_07, direction: OUTPUT}
  - {pin_num: L22, peripheral: GMAC_0, signal: gmac_ts_clk, pin_signal: PF_01, direction: OUTPUT}
  - {pin_num: Y11, peripheral: SIUL2_0, signal: 'gpio, 7', pin_signal: PA_07, direction: OUTPUT}
  - {pin_num: E7, peripheral: CAN_0, signal: txd, pin_signal: PB_01}
  - {pin_num: D7, peripheral: CAN_0, signal: rxd, pin_signal: PB_02, outputBuffer: disabled}
  - {pin_num: C6, peripheral: CAN_1, signal: txd, pin_signal: PB_03}
  - {pin_num: E8, peripheral: CAN_1, signal: rxd, pin_signal: PB_04}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*! @brief Array of pin configuration structures */
const Siul2_Port_Ip_PinSettingsConfig g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0] =
{
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 60u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 61u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMuxReg                 = {
                                         15u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 72u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMuxReg                 = {
                                         17u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 73u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMuxReg                 = {
                                         18u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 74u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMuxReg                 = {
                                         19u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 75u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMuxReg                 = {
                                         20u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 76u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMuxReg                 = {
                                         21u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 77u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMuxReg                 = {
                                         22u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 66u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 67u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 68u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 69u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 70u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 71u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 81u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 7u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 0u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 17u,
        .mux                         = PORT_MUX_ALT2,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 18u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMuxReg                 = {
                                         1u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT3,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 19u,
        .mux                         = PORT_MUX_ALT2,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .initValue                   = 2u
    },
    {
        .base                        = IP_SIUL2_0,
        .pinPortIdx                  = 20u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMuxReg                 = {
                                         631u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
        .initValue                   = 2u
    },
};

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

#ifdef SIUL2_PORT_IP_INIT_UNUSED_PIN
#if (STD_ON == SIUL2_PORT_IP_INIT_UNUSED_PIN)

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*! @brief Array of unused pin */
const Siul2_Port_Ip_UnUsedPinType g_unused_Pin[NUM_OF_UNUSED_PINS] =
{
    { (uint16)2, SIUL2_0_U8 },
    { (uint16)3, SIUL2_0_U8 },
    { (uint16)6, SIUL2_0_U8 },
    { (uint16)8, SIUL2_0_U8 },
    { (uint16)9, SIUL2_0_U8 },
    { (uint16)10, SIUL2_0_U8 },
    { (uint16)11, SIUL2_0_U8 },
    { (uint16)12, SIUL2_0_U8 },
    { (uint16)13, SIUL2_0_U8 },
    { (uint16)14, SIUL2_0_U8 },
    { (uint16)15, SIUL2_0_U8 },
    { (uint16)16, SIUL2_0_U8 },
    { (uint16)21, SIUL2_0_U8 },
    { (uint16)22, SIUL2_0_U8 },
    { (uint16)23, SIUL2_0_U8 },
    { (uint16)24, SIUL2_0_U8 },
    { (uint16)25, SIUL2_0_U8 },
    { (uint16)26, SIUL2_0_U8 },
    { (uint16)27, SIUL2_0_U8 },
    { (uint16)28, SIUL2_0_U8 },
    { (uint16)29, SIUL2_0_U8 },
    { (uint16)30, SIUL2_0_U8 },
    { (uint16)31, SIUL2_0_U8 },
    { (uint16)32, SIUL2_0_U8 },
    { (uint16)33, SIUL2_0_U8 },
    { (uint16)34, SIUL2_0_U8 },
    { (uint16)35, SIUL2_0_U8 },
    { (uint16)36, SIUL2_0_U8 },
    { (uint16)37, SIUL2_0_U8 },
    { (uint16)38, SIUL2_0_U8 },
    { (uint16)39, SIUL2_0_U8 },
    { (uint16)40, SIUL2_0_U8 },
    { (uint16)41, SIUL2_0_U8 },
    { (uint16)42, SIUL2_0_U8 },
    { (uint16)43, SIUL2_0_U8 },
    { (uint16)44, SIUL2_0_U8 },
    { (uint16)45, SIUL2_0_U8 },
    { (uint16)46, SIUL2_0_U8 },
    { (uint16)47, SIUL2_0_U8 },
    { (uint16)48, SIUL2_0_U8 },
    { (uint16)49, SIUL2_0_U8 },
    { (uint16)50, SIUL2_0_U8 },
    { (uint16)51, SIUL2_0_U8 },
    { (uint16)52, SIUL2_0_U8 },
    { (uint16)53, SIUL2_0_U8 },
    { (uint16)54, SIUL2_0_U8 },
    { (uint16)55, SIUL2_0_U8 },
    { (uint16)56, SIUL2_0_U8 },
    { (uint16)57, SIUL2_0_U8 },
    { (uint16)58, SIUL2_0_U8 },
    { (uint16)59, SIUL2_0_U8 },
    { (uint16)62, SIUL2_0_U8 },
    { (uint16)63, SIUL2_0_U8 },
    { (uint16)64, SIUL2_0_U8 },
    { (uint16)65, SIUL2_0_U8 },
    { (uint16)78, SIUL2_0_U8 },
    { (uint16)79, SIUL2_0_U8 },
    { (uint16)80, SIUL2_0_U8 },
    { (uint16)82, SIUL2_0_U8 },
    { (uint16)83, SIUL2_0_U8 },
    { (uint16)84, SIUL2_0_U8 },
    { (uint16)85, SIUL2_0_U8 },
    { (uint16)86, SIUL2_0_U8 },
    { (uint16)87, SIUL2_0_U8 },
    { (uint16)88, SIUL2_0_U8 },
    { (uint16)89, SIUL2_0_U8 },
    { (uint16)90, SIUL2_0_U8 },
    { (uint16)91, SIUL2_0_U8 },
    { (uint16)92, SIUL2_0_U8 },
    { (uint16)93, SIUL2_0_U8 },
    { (uint16)94, SIUL2_0_U8 },
    { (uint16)95, SIUL2_0_U8 },
    { (uint16)96, SIUL2_0_U8 },
    { (uint16)97, SIUL2_0_U8 },
    { (uint16)98, SIUL2_0_U8 },
    { (uint16)99, SIUL2_0_U8 },
    { (uint16)100, SIUL2_0_U8 },
    { (uint16)101, SIUL2_0_U8 },
    { (uint16)112, SIUL2_1_U8 },
    { (uint16)113, SIUL2_1_U8 },
    { (uint16)114, SIUL2_1_U8 },
    { (uint16)115, SIUL2_1_U8 },
    { (uint16)116, SIUL2_1_U8 },
    { (uint16)117, SIUL2_1_U8 },
    { (uint16)118, SIUL2_1_U8 },
    { (uint16)119, SIUL2_1_U8 },
    { (uint16)120, SIUL2_1_U8 },
    { (uint16)121, SIUL2_1_U8 },
    { (uint16)122, SIUL2_1_U8 },
    { (uint16)144, SIUL2_1_U8 },
    { (uint16)145, SIUL2_1_U8 },
    { (uint16)146, SIUL2_1_U8 },
    { (uint16)147, SIUL2_1_U8 },
    { (uint16)148, SIUL2_1_U8 },
    { (uint16)149, SIUL2_1_U8 },
    { (uint16)150, SIUL2_1_U8 },
    { (uint16)151, SIUL2_1_U8 },
    { (uint16)152, SIUL2_1_U8 },
    { (uint16)153, SIUL2_1_U8 },
    { (uint16)154, SIUL2_1_U8 },
    { (uint16)155, SIUL2_1_U8 },
    { (uint16)156, SIUL2_1_U8 },
    { (uint16)157, SIUL2_1_U8 },
    { (uint16)158, SIUL2_1_U8 },
    { (uint16)159, SIUL2_1_U8 },
    { (uint16)160, SIUL2_1_U8 },
    { (uint16)161, SIUL2_1_U8 },
    { (uint16)162, SIUL2_1_U8 },
    { (uint16)163, SIUL2_1_U8 },
    { (uint16)164, SIUL2_1_U8 },
    { (uint16)165, SIUL2_1_U8 },
    { (uint16)166, SIUL2_1_U8 },
    { (uint16)167, SIUL2_1_U8 },
    { (uint16)168, SIUL2_1_U8 },
    { (uint16)169, SIUL2_1_U8 },
    { (uint16)170, SIUL2_1_U8 },
    { (uint16)171, SIUL2_1_U8 },
    { (uint16)172, SIUL2_1_U8 },
    { (uint16)173, SIUL2_1_U8 },
    { (uint16)174, SIUL2_1_U8 },
    { (uint16)175, SIUL2_1_U8 },
    { (uint16)176, SIUL2_1_U8 },
    { (uint16)177, SIUL2_1_U8 },
    { (uint16)178, SIUL2_1_U8 },
    { (uint16)179, SIUL2_1_U8 },
    { (uint16)180, SIUL2_1_U8 },
    { (uint16)181, SIUL2_1_U8 },
    { (uint16)182, SIUL2_1_U8 },
    { (uint16)183, SIUL2_1_U8 },
    { (uint16)184, SIUL2_1_U8 },
    { (uint16)185, SIUL2_1_U8 },
    { (uint16)186, SIUL2_1_U8 },
    { (uint16)187, SIUL2_1_U8 },
    { (uint16)188, SIUL2_1_U8 },
    { (uint16)189, SIUL2_1_U8 },
    { (uint16)190, SIUL2_1_U8 }
};

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

#endif /* (STD_ON == SIUL2_PORT_IP_INIT_UNUSED_PIN) */
#endif /* (SIUL2_PORT_IP_INIT_UNUSED_PIN) */

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


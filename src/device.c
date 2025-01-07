/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 2.2, Highest operation, function 'Eth_T_EnableIRQs', lacks side-effects
 * It is required because the function body is made and visible based on the definition of several macros.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.3, Expression assigned to a narrower or different essential type.
 * The cast is required to perform a conversion between an unsigned integer and an enum type.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 11.4, Conversion between a pointer and
 * integer type.
 * The cast is required to initialize a pointer with an unsigned long define,
 * representing an address.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.6, Cast from pointer to unsigned long,
 * cast from unsigned long to pointer and cast from unsigned int to pointer.
 * The cast is required to perform a conversion between a pointer
 * and an unsigned long define, representing an address or vice versa.
 */

#include <ETH_SKKU.h>
#include "S32G399A.h"
#include "IntCtrl_Ip.h"
#include "device.h"
#include "Mcal.h"
#include "Clock_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Gmac_Ip.h"
#include "Gmac_Ip_Irq.h"
#include "OsIf.h"
#include "HAL_init_SKKU.h"
#include "GMAC_PTP_SKKU.h"
#include "FlexCAN_SKKU.h"
#include "Eth_Ipw.h"
#include "Eth.h"

#define CFG_PHY_CTRL_IDX        (0U)
#define ENABLE_PHY_LOOPBACK     (0U)   /* Set to 1 to enable PHY loop-back */
#define ENABLE_PHY_FULL_DUPLEX  (1U)   /* Set to 0 to enable PHY Half-duplex mode */

#define PHY_ID1                 (0x0022U)
#define PHY_ID2                 (0x1622U)

#define PHY_LED_ON              (1U)

#if 0
/* This feature is not used. Uncomment it if needed. */

static void Eth_T_InitPhys(void)
{
    uint16 phy_reg_val0 = 0U;
    uint16 phy_reg_val1 = 0U;
    uint16 phy_addr = 0U;
    Gmac_Ip_StatusType err;

    Gmac_Ip_EnableMDIO(CFG_PHY_CTRL_IDX, FALSE, 400000000U);

    /* Search for the PHY address */
    for (phy_addr = 0U; phy_addr < 32U; ++phy_addr)
    {
        err = Gmac_Ip_MDIORead(CFG_PHY_CTRL_IDX, phy_addr, 2U, &phy_reg_val0, 1U);
        DevAssert(GMAC_STATUS_SUCCESS == err);
        err = Gmac_Ip_MDIORead(CFG_PHY_CTRL_IDX, phy_addr, 3U, &phy_reg_val1, 1U);
        DevAssert(GMAC_STATUS_SUCCESS == err);

        /* Check for PHY ID */
        if ((phy_reg_val0 == PHY_ID1) && (phy_reg_val1 == PHY_ID2))
        {
            break; /* found the PHY ID*/
        }
    }

    /* Reset the PHY */
    err = Gmac_Ip_MDIOWrite(CFG_PHY_CTRL_IDX, phy_addr, 0U, 0x8000U, 1U);
    DevAssert(GMAC_STATUS_SUCCESS == err);

    /* Wait until the PHY is out of reset */
    do
    {
        err = Gmac_Ip_MDIORead(CFG_PHY_CTRL_IDX, phy_addr, 0U, &phy_reg_val0, 1U);
    } while (0U != ((uint16)err & 0x8000U));


    /* Configure the PHY */
    phy_reg_val0 &= ~((uint16)1U << 14U);    /* Disable Loop-back */
    phy_reg_val0 |= ((uint16)ENABLE_PHY_LOOPBACK << 14U);  /* Configure Loop back */
    phy_reg_val0 &= ~((uint16)1U << 12U); /* Disable AN */

    /* Configure speed 1G */
    phy_reg_val0 &= ~((uint16)1U << 13U);
    phy_reg_val0 |= ((uint16)1U << 6U);

    phy_reg_val0 &= ~((uint16)1U << 8U);
    phy_reg_val0 |= ((uint16)ENABLE_PHY_FULL_DUPLEX << 8U); /* FULL_DUPLEX or HALF_DUPLEX */

    err = Gmac_Ip_MDIOWrite(CFG_PHY_CTRL_IDX, phy_addr, 0U, phy_reg_val0, 1U);
    DevAssert(GMAC_STATUS_SUCCESS == err);

    /* Wait to establish link */
    do
    {
        (void)Gmac_Ip_MDIORead(CFG_PHY_CTRL_IDX, phy_addr, 1U, &phy_reg_val0, 1U);
    } while (0U == (phy_reg_val0 & ((uint16)1U << 2U)));
}
#endif

static void Eth_T_EnableIRQs(void)
{
    uint32 instance;

#ifdef FEATURE_ETH_COMMON_IRQS
    /*! @brief ETH common IRQ number for each instance. */
    const IRQn_Type ethCommonIrqId[FEATURE_ETH_NUM_INSTANCES] = FEATURE_ETH_COMMON_IRQS;
    /*! @brief ETH common IRQ handler for each instance. */
    void (*ethCommonIrqHandler[FEATURE_ETH_NUM_INSTANCES])(void) = FEATURE_GMAC_COMMON_IRQ_HDLRS;
#endif /* FEATURE_ETH_COMMON_IRQS */

#ifdef FEATURE_ETH_SAFETY_IRQS
    /*! @brief ETH safety IRQ number for each instance. */
    const IRQn_Type ethSafetyIrqId[FEATURE_ETH_NUM_INSTANCES] = FEATURE_ETH_SAFETY_IRQS;
    /*! @brief ETH safety IRQ handler for each instance. */
    void (*ethSafetyIrqHandler[FEATURE_ETH_NUM_INSTANCES])(void) = FEATURE_GMAC_SAFETY_IRQ_HDLRS;
#endif /* FEATURE_ETH_SAFETY_IRQS */

#ifdef FEATURE_ETH_TX_IRQS
    /*! @brief ETH transmit IRQ number for each channel and each instance. */
    const IRQn_Type ethTxIrqId[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS] = FEATURE_ETH_TX_IRQS;
    /*! @brief ETH transmit IRQ handler for each channel and each instance. */
    void (*ethTxIrqHandler[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS])(void) = FEATURE_ETH_TX_IRQ_HDLRS;
#endif /* FEATURE_ETH_TX_IRQS */

#ifdef FEATURE_ETH_RX_IRQS
    /*! @brief ETH receive IRQ number for each channel and each instance. */
    const IRQn_Type ethRxIrqId[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS] = FEATURE_ETH_RX_IRQS;
    /*! @brief ETH receive IRQ handler for each channel and each instance. */
    void (*ethRxIrqHandler[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS])(void) = FEATURE_ETH_RX_IRQ_HLDRS;
#endif /* FEATURE_ETH_RX_IRQS */

    /* Enable IRQs in a platform-specific way */
    for (instance = 0U; instance < FEATURE_GMAC_NUM_INSTANCES; ++instance)
    {
    #ifdef FEATURE_ETH_COMMON_IRQS
        ((volatile uint32*)S32_SCB->VTOR)[ethCommonIrqId[instance] + 16] = (uint32)ethCommonIrqHandler[instance];
        S32_NVIC->ISER[(uint32)(ethCommonIrqId[instance]) >> 5U] = (uint32)(1UL << ((uint32)(ethCommonIrqId[instance]) & (uint32)0x1FU));
    #endif /* FEATURE_ETH_COMMON_IRQS */

    #ifdef FEATURE_ETH_SAFETY_IRQS
        ((volatile uint32*)S32_SCB->VTOR)[ethSafetyIrqId[instance] + 16] = (uint32)ethSafetyIrqHandler[instance];
        S32_NVIC->ISER[(uint32)(ethSafetyIrqId[instance]) >> 5U] = (uint32)(1UL << ((uint32)(ethSafetyIrqId[instance]) & (uint32)0x1FU));
    #endif /* FEATURE_ETH_SAFETY_IRQS */

    #ifdef FEATURE_ETH_RX_IRQS
        for (uint32 channel = 0U; channel < FEATURE_ETH_NUM_CHANNELS; ++channel)
        {
            ((volatile uint32*)S32_SCB->VTOR)[ethRxIrqId[instance][channel] + 16] = (uint32)ethRxIrqHandler[instance][channel];
            S32_NVIC->ISER[(uint32)(ethRxIrqId[instance][channel]) >> 5U] = (uint32)(1UL << ((uint32)(ethRxIrqId[instance][channel]) & (uint32)0x1FU));
        }
    #endif /* FEATURE_ETH_RX_IRQS */

    #ifdef FEATURE_ETH_TX_IRQS
        for (uint32 channel = 0U; channel < FEATURE_ETH_NUM_CHANNELS; ++channel)
        {
            ((volatile uint32*)S32_SCB->VTOR)[ethTxIrqId[instance][channel] + 16] = (uint32)ethTxIrqHandler[instance][channel];
            S32_NVIC->ISER[(uint32)(ethTxIrqId[instance][channel]) >> 5U] = (uint32)(1UL << ((uint32)(ethTxIrqId[instance][channel]) & (uint32)0x1FU));
        }
    #endif /* FEATURE_ETH_TX_IRQS */
    }
}

Gmac_Ip_VlanConfigType gmac_0_vlanConfig =
{
	/* .enDoubleVlan = */ TRUE,
	/* .enSvlan = */ FALSE,
	/* .outerVlanIns = */ GMAC_VLAN_TAG_INSERTION,
	/* .innerVlanIns = */ GMAC_VLAN_TAG_NO_CONTROL,
	/* .outerVlanStrip = */ GMAC_VLAN_TAG_DO_NOT_STRIP,
	/* .innerVlanStrip = */ GMAC_VLAN_TAG_DO_NOT_STRIP,
};

Gmac_Ip_VlanRxFilterType gmac_0_vlanRxFilterConfig = {
/* .enInnerVlanMatch = */ FALSE,
/* .enSvlanMatch = */ FALSE,
/* .disVlanTypeMatch = */ FALSE,
/* .enInverseMatch = */ FALSE,
/* .en12bitMatch = */ TRUE,
};

extern void CAN0_ORED_0_7_MB_IRQHandler(void);

volatile StatusType err;

void device_init(void)
{

    /* Init mode for PHY node and PHY interface with RGMII mode, speed 1G */
    IP_SRC->GMAC_0_CTRL_STS |= (SRC_GMAC_0_CTRL_STS_PHY_MODE(0U) | SRC_GMAC_0_CTRL_STS_PHY_INTF_SEL(1U));

    /* Initialize all pins using the Port driver */
    err = Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    DevAssert((StatusType)E_OK == err);

    /* Initialize Clocks */
    err = Clock_Ip_Init(&Mcu_aClockConfigPB[0U]);
    DevAssert((StatusType)E_OK == err);

    OsIf_Init(NULL_PTR);
    /* Install interrupt handlers for EMAC */

    IntCtrl_Ip_InstallHandler(GMAC0_CH0_TX_IRQn, GMAC0_CH0_TX_IRQHandler, NULL_PTR);
    IntCtrl_Ip_SetPriority(GMAC0_CH0_TX_IRQn, 2);
    IntCtrl_Ip_EnableIrq(GMAC0_CH0_TX_IRQn);

    IntCtrl_Ip_InstallHandler(GMAC0_CH0_RX_IRQn, GMAC0_CH0_RX_IRQHandler, NULL_PTR);
    IntCtrl_Ip_SetPriority(GMAC0_CH0_RX_IRQn, 2);
    IntCtrl_Ip_EnableIrq(GMAC0_CH0_RX_IRQn);

    IntCtrl_Ip_InstallHandler(CAN0_ORED_0_7_MB_IRQn, CAN0_ORED_0_7_MB_IRQHandler, NULL_PTR);
    IntCtrl_Ip_SetPriority(CAN0_ORED_0_7_MB_IRQn, 2);
    IntCtrl_Ip_EnableIrq(CAN0_ORED_0_7_MB_IRQn);

    /* Initialize and enable the GMAC module */
    Eth_Init(EthConf_EthCtrlConfig_EthCtrlConfig_0);

    //Eth_TxTimeAwareShaperInit(EthConf_EthCtrlConfig_EthCtrlConfig_0);
    FlexCAN_init_SKKU();

    /* Initialize Os Interface */

#ifndef USING_OS_FREERTOS
    OsIf_SetTimerFrequency(400000000U,  OSIF_USE_SYSTEM_TIMER);
#endif /* USING_OS_FREERTOS */

    Gmac_Ip_InitSysTime_skku(INST_GMAC_0, NULL);

    Eth_T_EnableIRQs();

    PTP_init();

    TSN_init();

    Eth_SetControllerMode(EthConf_EthCtrlConfig_EthCtrlConfig_0, ETH_MODE_ACTIVE);

    Gmac_Ip_EnableVlan(EthConf_EthCtrlConfig_EthCtrlConfig_0, &gmac_0_vlanConfig);
    //Gmac_Ip_SetVlanTagRxFilter(EthConf_EthCtrlConfig_EthCtrlConfig_0, TRUE, &gmac_0_vlanRxFilterConfig);
    Gmac_Ip_SetTxOuterVlanTagForInsertion(EthConf_EthCtrlConfig_EthCtrlConfig_0,
    		    															0U,
    																		 GMAC_VLAN_TYPE_C_VLAN,
    																		 0x1801U );
    Gmac_Ip_SetTxOuterVlanTagForInsertion(EthConf_EthCtrlConfig_EthCtrlConfig_0,
    		    															1U,
    																		 GMAC_VLAN_TYPE_C_VLAN,
    																		 0x3801U );
    /* Initialize Ethernet Phy */
    /* Eth_T_InitPhys(); */
}

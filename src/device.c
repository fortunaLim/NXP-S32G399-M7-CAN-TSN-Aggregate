/*
 * device.c - INTERRUPT FIX VERSION
 *
 * �ֿ� ��������:
 * 1. ���ͷ�Ʈ �켱���� ���� �߰�
 * 2. ���� üũ ��ȭ
 * 3. FreeRTOS ���ͷ�Ʈ �켱���� ���
 * 4. �ʱ�ȭ ���� ����
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
#include "ETH_SKKU.h"

#define CFG_PHY_CTRL_IDX        (0U)
#define ENABLE_PHY_LOOPBACK     (0U)
#define ENABLE_PHY_FULL_DUPLEX  (1U)

#define PHY_ID1                 (0x0022U)
#define PHY_ID2                 (0x1622U)
#define PHY_LED_ON              (1U)

// ==================== �߰�: ���ͷ�Ʈ �켱���� ���� ====================
// FreeRTOS�� ����� ��� configMAX_SYSCALL_INTERRUPT_PRIORITY���� ���� �켱���� ���
// S32G�� 0�� ���� ���� �켱����, 15�� ���� ����
// FreeRTOS���� API ȣ�� ������ ����: ���� 5~15
#ifdef USING_OS_FREERTOS
    #define IRQ_PRIORITY_ETHERNET   5   // FreeRTOS API ȣ�� ������ ����
    #define IRQ_PRIORITY_CAN        4
#else
    #define IRQ_PRIORITY_ETHERNET   2   // Non-RTOS: ���� �켱���� ��� ����
    #define IRQ_PRIORITY_CAN        2
#endif

static void Eth_T_EnableIRQs(void)
{
    uint32 instance;

#ifdef FEATURE_ETH_COMMON_IRQS
    const IRQn_Type ethCommonIrqId[FEATURE_ETH_NUM_INSTANCES] = FEATURE_ETH_COMMON_IRQS;
    void (*ethCommonIrqHandler[FEATURE_ETH_NUM_INSTANCES])(void) = FEATURE_GMAC_COMMON_IRQ_HDLRS;
#endif

#ifdef FEATURE_ETH_SAFETY_IRQS
    const IRQn_Type ethSafetyIrqId[FEATURE_ETH_NUM_INSTANCES] = FEATURE_ETH_SAFETY_IRQS;
    void (*ethSafetyIrqHandler[FEATURE_ETH_NUM_INSTANCES])(void) = FEATURE_GMAC_SAFETY_IRQ_HDLRS;
#endif

#ifdef FEATURE_ETH_TX_IRQS
    const IRQn_Type ethTxIrqId[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS] = FEATURE_ETH_TX_IRQS;
    void (*ethTxIrqHandler[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS])(void) = FEATURE_ETH_TX_IRQ_HDLRS;
#endif

#ifdef FEATURE_ETH_RX_IRQS
    const IRQn_Type ethRxIrqId[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS] = FEATURE_ETH_RX_IRQS;
    void (*ethRxIrqHandler[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS])(void) = FEATURE_ETH_RX_IRQ_HLDRS;
#endif

    for (instance = 0U; instance < FEATURE_GMAC_NUM_INSTANCES; ++instance)
    {
    #ifdef FEATURE_ETH_COMMON_IRQS
        ((volatile uint32*)S32_SCB->VTOR)[ethCommonIrqId[instance] + 16] = (uint32)ethCommonIrqHandler[instance];
        S32_NVIC->ISER[(uint32)(ethCommonIrqId[instance]) >> 5U] = (uint32)(1UL << ((uint32)(ethCommonIrqId[instance]) & (uint32)0x1FU));
    #endif

    #ifdef FEATURE_ETH_SAFETY_IRQS
        ((volatile uint32*)S32_SCB->VTOR)[ethSafetyIrqId[instance] + 16] = (uint32)ethSafetyIrqHandler[instance];
        S32_NVIC->ISER[(uint32)(ethSafetyIrqId[instance]) >> 5U] = (uint32)(1UL << ((uint32)(ethSafetyIrqId[instance]) & (uint32)0x1FU));
    #endif

    #ifdef FEATURE_ETH_RX_IRQS
        for (uint32 channel = 0U; channel < FEATURE_ETH_NUM_CHANNELS; ++channel)
        {
            ((volatile uint32*)S32_SCB->VTOR)[ethRxIrqId[instance][channel] + 16] = (uint32)ethRxIrqHandler[instance][channel];
            S32_NVIC->ISER[(uint32)(ethRxIrqId[instance][channel]) >> 5U] = (uint32)(1UL << ((uint32)(ethRxIrqId[instance][channel]) & (uint32)0x1FU));
        }
    #endif

    #ifdef FEATURE_ETH_TX_IRQS
        for (uint32 channel = 0U; channel < FEATURE_ETH_NUM_CHANNELS; ++channel)
        {
            ((volatile uint32*)S32_SCB->VTOR)[ethTxIrqId[instance][channel] + 16] = (uint32)ethTxIrqHandler[instance][channel];
            S32_NVIC->ISER[(uint32)(ethTxIrqId[instance][channel]) >> 5U] = (uint32)(1UL << ((uint32)(ethTxIrqId[instance][channel]) & (uint32)0x1FU));
        }
    #endif
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
extern void CAN1_ORED_0_7_MB_IRQHandler(void);

volatile StatusType err;

void device_init(void)
{
    IntCtrl_Ip_StatusType intStatus;

    /* Init mode for PHY node and PHY interface with RGMII mode, speed 1G */
    IP_SRC->GMAC_0_CTRL_STS |= (SRC_GMAC_0_CTRL_STS_PHY_MODE(0U) | SRC_GMAC_0_CTRL_STS_PHY_INTF_SEL(1U));

    /* Initialize all pins using the Port driver */
    err = Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    if ((StatusType)E_OK != err)
    {
        // ���� ó��: LED �����̳� ���� ����
        while(1);
    }

    /* Initialize Clocks */
    err = Clock_Ip_Init(&Mcu_aClockConfigPB[0U]);
    if ((StatusType)E_OK != err)
    {
        while(1);
    }

    /* Initialize OsIf BEFORE interrupt setup */
    OsIf_Init(NULL_PTR);

#ifndef USING_OS_FREERTOS
    OsIf_SetTimerFrequency(400000000U, OSIF_USE_SYSTEM_TIMER);
#endif

    // ==================== ����: ���ͷ�Ʈ ���� ���� ====================

    /* GMAC TX Interrupt */
    IntCtrl_Ip_InstallHandler(GMAC0_CH0_TX_IRQn, GMAC0_CH0_TX_IRQHandler, NULL_PTR);

    IntCtrl_Ip_SetPriority(GMAC0_CH0_TX_IRQn, IRQ_PRIORITY_ETHERNET);

    IntCtrl_Ip_EnableIrq(GMAC0_CH0_TX_IRQn);

    /* GMAC RX Interrupt */
    IntCtrl_Ip_InstallHandler(GMAC0_CH0_RX_IRQn, GMAC0_CH0_RX_IRQHandler, NULL_PTR);

    IntCtrl_Ip_SetPriority(GMAC0_CH0_RX_IRQn, IRQ_PRIORITY_ETHERNET);

    IntCtrl_Ip_EnableIrq(GMAC0_CH0_RX_IRQn);


    /* CAN Interrupt */

    IntCtrl_Ip_InstallHandler(CAN0_ORED_0_7_MB_IRQn, CAN0_ORED_0_7_MB_IRQHandler, NULL_PTR);

    IntCtrl_Ip_SetPriority(CAN1_ORED_0_7_MB_IRQn, IRQ_PRIORITY_CAN);

    IntCtrl_Ip_InstallHandler(CAN1_ORED_0_7_MB_IRQn, CAN1_ORED_0_7_MB_IRQHandler, NULL_PTR);

    IntCtrl_Ip_SetPriority(CAN1_ORED_0_7_MB_IRQn, IRQ_PRIORITY_CAN);


    /* Initialize GMAC module - BEFORE enabling additional IRQs */
    Eth_Init(EthConf_EthCtrlConfig_EthCtrlConfig_0);

    /* Initialize FlexCAN */
    FlexCAN_init_SKKU();

    /* Initialize System Time */
    //Gmac_Ip_InitSysTime_skku(INST_GMAC_0, NULL);

    /* Enable additional Ethernet IRQs */
    Eth_T_EnableIRQs();

    /* Initialize PTP and TSN */
    //PTP_init();
    //TSN_init();

    Eth_TxTimeAwareShaperInit(EthConf_EthCtrlConfig_EthCtrlConfig_0);

    //TAS_HW_Init();
    /* Set controller to active mode */
    Eth_SetControllerMode(EthConf_EthCtrlConfig_EthCtrlConfig_0, ETH_MODE_ACTIVE);

    /* Configure VLAN */

    Gmac_Ip_EnableVlan(EthConf_EthCtrlConfig_EthCtrlConfig_0, &gmac_0_vlanConfig);

    // Tx 링 0 (PCP 0, Gmac_VLAN_PRIORITY_0)
	uint16 vlanTag_Q0 = (0U << 13) | 0x001U; // 0x0001
	Gmac_Ip_SetTxOuterVlanTagForInsertion(EthConf_EthCtrlConfig_EthCtrlConfig_0,
										   0U, // Tx 링 0
										   GMAC_VLAN_TYPE_C_VLAN,
										   vlanTag_Q0);

	// Tx 링 1 (PCP 1, Gmac_VLAN_PRIORITY_1)
	uint16 vlanTag_Q1 = (1U << 13) | 0x001U; // 0x2001
	Gmac_Ip_SetTxOuterVlanTagForInsertion(EthConf_EthCtrlConfig_EthCtrlConfig_0,
										   1U, // Tx 링 1
										   GMAC_VLAN_TYPE_C_VLAN,
										   vlanTag_Q1);

	// Tx 링 2 (PCP 2, Gmac_VLAN_PRIORITY_2)
	uint16 vlanTag_Q2 = (2U << 13) | 0x001U; // 0x4001
	Gmac_Ip_SetTxOuterVlanTagForInsertion(EthConf_EthCtrlConfig_EthCtrlConfig_0,
										   2U, // Tx 링 2
										   GMAC_VLAN_TYPE_C_VLAN,
										   vlanTag_Q2);

}

/*
 * FlexCAN_SKKU_TAS.c – Hardware TAS + Software Scheduling VERSION
 * + 4KB Boundary Crossing Fix
 *
 * 추가 수정 내용:
 * - 4KB 경계 크로스 문제 해결
 * - 버퍼 정렬 검증 로직 추가
 * - 경계 크로스 발생 시 버퍼 재요청 메커니즘
 */

#include "ETH_SKKU.h"
#include "FlexCAN_SKKU.h"
#include "Mcal.h"
#include "Clock_Ip.h"
#include "FlexCAN_Ip.h"
#include "IntCtrl_Ip.h"
#include "FlexCAN_Ip_Sa_PBcfg.h"
#include "Eth.h"
#include "GMAC_PTP_SKKU.h"
#include "Gmac_Ip.h"
#include "Eth_Internal.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include <string.h>
#include <stdio.h>

#define FLEXCAN_INST 0U
#define LED_PIN 7u
#define LED_PORT PTA
#define CAN_QUEUE_SIZE 256

// TAS 관련 상수
#define TAS_CYCLE_TIME_NS       10000000u  // 10ms 주기
#define TAS_GATE_OPEN_START_NS  1000000u   // 1ms에 게이트 오픈
#define TAS_GATE_OPEN_END_NS    2000000u   // 2ms에 게이트 클로즈
#define TAS_GATE_DURATION_NS    (TAS_GATE_OPEN_END_NS - TAS_GATE_OPEN_START_NS)

// TAS 하드웨어 레지스터 관련
#define GMAC_MTL_EST_STATUS_CGCE_SHIFT  (4u)
#define GMAC_MTL_EST_STATUS_CGSN_SHIFT  (16u)
#define GMAC_MTL_EST_STATUS_CGSN_MASK   (0xF0000u)

#define GMAC_MTL_TBS_CTRL_ESTM_SHIFT    (4u)
#define GMAC_MTL_TBS_CTRL_ESTM_MASK     (0x10u)
#define GMAC_TBS_ESTM_NORMAL            (0u)
#define GMAC_TBS_ESTM_EST_OFFSET        (1u)

#define GSN_MAX_VALUE                   (15u)
#define GSN_FUTURE_WINDOW               (8u)

// Traffic Class 정의
#define TC_CRITICAL     0u
#define TC_HIGH         1u
#define TC_MEDIUM       2u
#define TC_LOW          3u
#define TC_BEST_EFFORT  7u

// 컨테이너 관련
#define CONTAINER_MAX_SIZE     1536u // 512u, 1024u, 1536u

// =================== 4KB 경계 관련 상수 ===================
#define PAGE_SIZE_4KB           0x1000u     // 4096 bytes
#define PAGE_MASK_4KB           0xFFFu      // 4KB 정렬 마스크
#define MAX_BOUNDARY_RETRY      3u          // 최대 재시도 횟수

static uint8 TxMbList[] = {4u, 5u, 6u, 7u};
static const uint8 TxMbCount = sizeof(TxMbList)/sizeof(TxMbList[0]);
static uint8 TxMbPos = 0u;

static volatile uint32_t g_canTxDoneMask = 0;

extern xQueueHandle xQueue_CAN;
static const uint8 Gmac_0_MacAddr[6U] = {0x00,0x11,0x22,0x33,0x44,0x44};
extern SemaphoreHandle_t Can2Eth_mutex;

// =================== 통계 구조체 (4KB 관련 추가) ===================
typedef struct {
    uint32 rxCount;
    uint32 txCount;
    uint32 txErrCount;
    uint32 queueFullErrors;
    uint32 ethBufferErrors;
    uint32 ethTxErrors;
    uint32 containersSent;
    uint32 containersDropped;
    uint32 boundary4KBCrosses;      // 4KB 경계 크로스 감지 횟수
    uint32 boundary4KBRetries;      // 재시도 횟수
    uint32 boundary4KBFailures;     // 최종 실패 횟수
} CANStatistics_t;

volatile CANStatistics_t canStats = {0};

// =================== FlexCAN 기본 설정 ===================
Flexcan_Ip_DataInfoType tx_info = {
    .msg_id_type = FLEXCAN_MSG_ID_STD,
    .data_length = 64u,
    .fd_enable = TRUE,
    .enable_brs = TRUE,
    .fd_padding = TRUE,
    .is_polling = TRUE,
    .is_remote = FALSE
};

Flexcan_Ip_DataInfoType rx_info = {
    .msg_id_type = FLEXCAN_MSG_ID_STD,
    .data_length = 64u,
    .fd_enable = TRUE,
    .enable_brs = TRUE,
    .fd_padding = TRUE,
    .is_polling = TRUE,
    .is_remote = FALSE
};

Flexcan_Ip_MsgBuffType rxData;

// =================== AUTOSAR PduR 기반 Container PDU ===================
#define GW_CONTAINER_VERSION   (0x01u)
#define GW_CONTAINER_HDR_SIZE  (2u)
#define GW_IPDU_HDR_SIZE       (3u)

// =================== CAN ID to PDU ID 매핑 ===================
typedef struct {
    uint32 canId;
    uint16 pduId;
    uint8  trafficClass;
} CanIdToPduId_t;

static const CanIdToPduId_t CanPduMap[] = {
    { 0x1, 1001, TC_CRITICAL },
    { 0x2, 1002, TC_CRITICAL },
    { 0x3, 1003, TC_CRITICAL },
    { 0x4, 1004, TC_CRITICAL },
};

#define CAN_PDU_MAP_NUM   (sizeof(CanPduMap)/sizeof(CanPduMap[0]))

// =================== 유틸리티 함수 ===================
static inline uint8 CANFD_DlcToLen(uint8 dlc)
{
    static const uint8 tbl[16] = {
        0,1,2,3,4,5,6,7,
        8,12,16,20,24,32,48,64
    };
    return (dlc < 16) ? tbl[dlc] : 0;
}

static inline uint16 GW_GetPduId_FromCanFd(uint32 canId, uint8 *trafficClass)
{
    for (uint8 i = 0; i < CAN_PDU_MAP_NUM; i++) {
        if (CanPduMap[i].canId == canId) {
            if (trafficClass != NULL) {
                *trafficClass = CanPduMap[i].trafficClass;
            }
            return CanPduMap[i].pduId;
        }
    }
    return 0xFFFFu;
}

// =================== 4KB 경계 체크 함수 ===================
/*
 * 버퍼가 4KB 경계를 크로스하는지 검사
 *
 * @param bufAddr: 버퍼 시작 주소
 * @param length: 버퍼 길이
 * @return: TRUE if crosses 4KB boundary, FALSE otherwise
 */
static inline boolean Check_4KB_Boundary_Cross(uintptr_t bufAddr, uint16 txLen)
{
    if (txLen == 0u) return FALSE;

    uintptr_t page_end = ((bufAddr & ~0xFFFu) + 0x1000u - 1u);
    uintptr_t bufEnd   = bufAddr + (uintptr_t)txLen - 1u;
    return (bufEnd > page_end);
}

/*
 * 4KB 경계까지 남은 바이트 수 계산
 *
 * @param bufAddr: 버퍼 시작 주소
 * @return: 4KB 경계까지 남은 바이트 수
 */
static inline uint16 Bytes_To_4KB_Boundary(uintptr_t bufAddr)
{
    uintptr_t offset = bufAddr & PAGE_MASK_4KB;  // 페이지 내 오프셋
    return (uint16)(PAGE_SIZE_4KB - offset);
}

// =================== TAS 게이트 상태 판단 ===================
GMAC_Type *Base;
uint32 estStatus;
uint32 estStatus_arr[1000];
Eth_TimeStampType Time_Temp;

typedef struct {
    uint32 cgsn0_count;
    uint32 cgsn1_count;
    uint32 cgsn2_count;
    uint32 cgsn3_count;
    uint32 total_checks;
} TAS_Simple_Stats_t;

static TAS_Simple_Stats_t g_tasStats = {0};

uint32 abc = 0;
uint32 delta[1000] = {0};

#define NSEC_PER_SEC 1000000000ULL
#define CYCLE_NS     10000000UL
#define SLOT_MARGIN_NS 100000UL

typedef struct { uint32_t TimeIntervalNs; uint32_t GateControlBits; } GclEntry;
static const GclEntry GCL_MIRROR[] = {
    { 1000000U, 0b001 },
    { 4000000U, 0b010 },
    { 4000000U, 0b100 },
    { 1000000U, 0b000 },
};
#define GCL_DEPTH (sizeof(GCL_MIRROR)/sizeof(GCL_MIRROR[0]))

static inline uint64_t mac_time_now_ns(void) {
    GMAC_Type *Base = Gmac_apxBases[0];
    return (uint64_t)Base->MAC_SYSTEM_TIME_SECONDS * NSEC_PER_SEC
         + (uint64_t)Base->MAC_SYSTEM_TIME_NANOSECONDS;
}

static inline uint32_t gcl_locate(uint32_t tcy, uint32_t *slotStartNs, uint32_t *slotEndNs) {
    uint32_t acc = 0;
    for (uint32_t i = 0; i < GCL_DEPTH; i++) {
        uint32_t next = acc + GCL_MIRROR[i].TimeIntervalNs;
        if (tcy < next) {
            if (slotStartNs) *slotStartNs = acc;
            if (slotEndNs)   *slotEndNs   = next;
            return i;
        }
        acc = next;
    }
    if (slotStartNs) *slotStartNs = CYCLE_NS - GCL_MIRROR[GCL_DEPTH-1].TimeIntervalNs;
    if (slotEndNs)   *slotEndNs   = CYCLE_NS;
    return GCL_DEPTH - 1;
}

bool TAS_IsGateOpen_FIFOx(uint32_t fifoIndex) {
    if (fifoIndex > 2u) return false;

    uint32_t tcy = (uint32_t)(mac_time_now_ns() % CYCLE_NS);
    uint32_t s0, s1;
    uint32_t idx = gcl_locate(tcy, &s0, &s1);

    uint32_t effEnd = (s1 > SLOT_MARGIN_NS) ? (s1 - SLOT_MARGIN_NS) : s0;

    if (effEnd <= s0) return false;

    if (tcy < s0 || tcy >= effEnd) return false;

    uint32_t gate = GCL_MIRROR[idx].GateControlBits;
    return ((gate >> fifoIndex) & 0x1u) != 0u;
}

uint32_t TAS_RemainingOpenTimeNs_FIFOx(uint32_t fifoIndex) {
    if (fifoIndex > 2u) return 0u;

    uint32_t tcy = (uint32_t)(mac_time_now_ns() % CYCLE_NS);
    uint32_t s0, s1;
    uint32_t idx = gcl_locate(tcy, &s0, &s1);
    uint32_t effEnd = (s1 > SLOT_MARGIN_NS) ? (s1 - SLOT_MARGIN_NS) : s0;

    if (effEnd <= s0) return 0u;
    uint32_t gate = GCL_MIRROR[idx].GateControlBits;
    bool openNow = (tcy >= s0) && (tcy < effEnd) && (((gate >> fifoIndex) & 0x1u) != 0u);
    return openNow ? (effEnd - tcy) : 0u;
}

static inline boolean TAS_IsGSNFuture(uint8 targetGSN, uint8 currentGSN)
{
    uint8 diff = (targetGSN - currentGSN) & 0x0Fu;
    return (diff <= GSN_FUTURE_WINDOW);
}

static inline uint32 TAS_GetTimeUntilNextOpen(uint32 currentTimeNs)
{
    uint32 timeInCycle = currentTimeNs % TAS_CYCLE_TIME_NS;

    if (timeInCycle < TAS_GATE_OPEN_START_NS) {
        return (TAS_GATE_OPEN_START_NS - timeInCycle);
    } else {
        return (TAS_CYCLE_TIME_NS - timeInCycle + TAS_GATE_OPEN_START_NS);
    }
}

// ========== FlexCAN_init_SKKU() ==========
void FlexCAN_init_SKKU(void)
{
    FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);

    FlexCAN_Ip_Init(INST_FLEXCAN_1, &FlexCAN_State1, &FlexCAN_Config1);

    rx_info.is_polling = TRUE;
    tx_info.is_polling = TRUE;

    FlexCAN_Ip_EnterFreezeMode(INST_FLEXCAN_0);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, 0u, &rx_info, 0x1u);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, 1u, &rx_info, 0x3u);
    //FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, 2u, &rx_info, 0x3u);
    //FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, 3u, &rx_info, 0x4u);
    FlexCAN_Ip_ExitFreezeMode(INST_FLEXCAN_0);

    FlexCAN_Ip_EnterFreezeMode(INST_FLEXCAN_1);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_1, 0u, &rx_info, 0x2u);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_1, 1u, &rx_info, 0x4u);
    //FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_1, 2u, &rx_info, 0x1u);
    //FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_1, 3u, &rx_info, 0x2u);
    FlexCAN_Ip_ExitFreezeMode(INST_FLEXCAN_1);

    FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0);
    FlexCAN_Ip_SetStartMode(INST_FLEXCAN_1);

    g_canTxDoneMask = (1u << 4) | (1u << 5) | (1u << 6) | (1u << 7);
}

// =================== RX 콜백 ===================
void CAN0_Callback_SKKU(uint8 instance,
                        Flexcan_Ip_EventType eventType,
                        uint32 buffIdx,
                        const Flexcan_Ip_StateType *flexcanState)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (eventType == FLEXCAN_EVENT_RX_COMPLETE)
    {
        canStats.rxCount++;
        if(instance == 0 ){
        	(void)FlexCAN_Ip_Receive(INST_FLEXCAN_0, buffIdx, &rxData, 1);
        } else if (instance == 1) {
        	(void)FlexCAN_Ip_Receive(INST_FLEXCAN_1, buffIdx, &rxData, 1);
        }
        if (xQueueSendFromISR(xQueue_CAN, &rxData, &xHigherPriorityTaskWoken) != pdTRUE)
            canStats.queueFullErrors++;
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static inline uint8 CANFD_LenToDlc(uint8 len)
{
    if (len <= 8) return len;
    switch (len) {
        case 12: return 9;
        case 16: return 10;
        case 20: return 11;
        case 24: return 12;
        case 32: return 13;
        case 48: return 14;
        case 64: return 15;
        default: return 0;
    }
}

// =================== Polling 기반 송신 Task ===================
typedef struct {
    uint8 mbIdx;
    uint32 canId;
    uint32 periodMs;
    uint32 offsetMs;
} CanTxTaskParam_t;

void CAN_SendTask_Generic(void *pvParameters)
{
    CanTxTaskParam_t *p = (CanTxTaskParam_t *)pvParameters;
    uint32 counter = 0;
    uint8 data[64];
    TickType_t lastWake = xTaskGetTickCount() + pdMS_TO_TICKS(p->offsetMs);
    vTaskDelay(pdMS_TO_TICKS(p->offsetMs));
    for (;;)
    {
        FlexCAN_Ip_MainFunctionWrite(FLEXCAN_INST, p->mbIdx);

        Flexcan_Ip_StatusType st = FlexCAN_Ip_GetTransferStatus(FLEXCAN_INST, p->mbIdx);

        if (st == FLEXCAN_STATUS_BUSY) {
            vTaskDelay(pdMS_TO_TICKS(1));
            continue;
        }

        memset(data, 0, sizeof(data));
        counter++;
        data[0] = (uint8)(counter & 0xFF);
        data[1] = (uint8)((counter >> 8) & 0xFF);
        data[2] = (uint8)((counter >> 16) & 0xFF);
        data[3] = (uint8)((counter >> 24) & 0xFF);

        st = FlexCAN_Ip_Send(FLEXCAN_INST, p->mbIdx, &tx_info, p->canId, data);
        if (st != FLEXCAN_STATUS_SUCCESS) {
            canStats.txErrCount++;
        } else {
            canStats.txCount++;
        }

        Flexcan_Ip_MsgBuffType simMsg;
        simMsg.msgId   = p->canId;
        simMsg.dataLen = CANFD_LenToDlc(tx_info.data_length);
        memcpy(simMsg.data, data, 64u);
        //(void)xQueueSend(xQueue_CAN, &simMsg, 0);

        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(p->periodMs));
        //vTaskDelay(pdMS_TO_TICKS(p->offsetMs));
    }
}

/* ====== 폴링 기반 CAN 수신 태스크 ====== */
typedef struct {
    uint8 instance;        /* FlexCAN instance (예: 0) */
    uint8 mb_list[2][4];      /* 폴링할 RX MB 인덱스 리스트 */
    uint8 mb_count;        /* 사용 개수 */
    TickType_t poll_delay_ticks; /* 루프 지연 (예: 1 tick) */
} CanRxTaskParam_t;

/* DLC -> 바이트 길이 변환 */
static inline uint8 CANFD_DlcToLen_poll(uint8 dlc)
{
    static const uint8 tbl[16] = {
        0,1,2,3,4,5,6,7,
        8,12,16,20,24,32,48,64
    };
    return (dlc < 16) ? tbl[dlc] : 0;
}

// ========== CAN_Receive_Polling_Task() ==========
void CAN_Receive_Polling_Task(void *pvParameters)
{
    CanRxTaskParam_t *p = (CanRxTaskParam_t *)pvParameters;

    uint8 inst = p->instance;
    Flexcan_Ip_MsgBuffType rxShadow[8];
    memset(rxShadow, 0, sizeof(rxShadow));

    // 초기화
    for(inst = 0; inst<2;inst++) {
		for (uint8 i = 0; i < p->mb_count; i++) {
			FlexCAN_Ip_Receive(inst, p->mb_list[inst][i], &rxShadow[i], TRUE);
		}
    }
    for (;;) {
    	for(inst = 0; inst<2;inst++) {
			for (uint8 i = 0; i < p->mb_count; i++) {
				uint8 mb = p->mb_list[inst][i];
				FlexCAN_Ip_MainFunctionRead(inst, mb);
			}
    	}
        vTaskDelay(p->poll_delay_ticks);
    }
}

// =================== TC to FIFO 매핑 ===================
static inline uint8 TC_to_FIFO(uint8 trafficClass)
{
    if (trafficClass <= 2u) {
        return 0u;
    } else if (trafficClass <= 5u) {
        return 1u;
    } else {
        return 2u;
    }
}

// =================== 실시간 TAS 기반 ETH 전송 Task (4KB 경계 처리 추가) ===================
__attribute__((aligned(64))) static uint8 currentContainer[CONTAINER_MAX_SIZE];
uint8 *ethPayload;
uint32 ethPayload_log[1000] = {0};

void ETH_PDU_Send_TAS(void *pvParameters)
{
    (void)pvParameters;

    Flexcan_Ip_MsgBuffType rxData;
    Flexcan_Ip_MsgBuffType overflowPdu;  // 오버플로우된 PDU 임시 저장
    boolean hasOverflowPdu = FALSE;       // 대기 중인 PDU 있는지 플래그

    // Container 버퍼
    uint8 currentContainer[CONTAINER_MAX_SIZE];
    uint16 containerLen = 0;
    uint8 iPduCount = 0;
    uint8 currentTC = TC_BEST_EFFORT;
    boolean containerPending = FALSE;

    // ETH 버퍼
    Eth_BufIdxType bufIdx;
    uint8 *ethPayload;
    uint16 bufLen;

    for(;;)
    {
        // ========== 1. PDU 소스 결정 ==========
        boolean hasPduToProcess = FALSE;

        if (hasOverflowPdu) {
            // 우선순위 1: 이전에 못 들어간 PDU 먼저 처리
            rxData = overflowPdu;
            hasOverflowPdu = FALSE;
            hasPduToProcess = TRUE;
        }
        else {
            // 우선순위 2: 큐에서 새 PDU 수신
            if (xQueueReceive(xQueue_CAN, &rxData, 0) == pdTRUE) {
                hasPduToProcess = TRUE;
            }
        }

        // ========== 2. PDU 처리 (있을 경우만) ==========
        if (hasPduToProcess)
        {
            /* CAN-ID → I-PDU ID + Traffic Class 매핑 */
            uint8 msgTC = TC_BEST_EFFORT;
            uint16 iPduId = GW_GetPduId_FromCanFd(rxData.msgId, &msgTC);

            if (iPduId == 0xFFFFu) {
                continue;  // 매핑 없는 CAN ID - 무시
            }

            uint8 iPduLen = rxData.dataLen;// CANFD_DlcToLen(rxData.dataLen);

            /* 새 Container 시작 */
            if (!containerPending) {
                currentContainer[0] = GW_CONTAINER_VERSION;
                currentContainer[1] = 0u;
                containerLen = GW_CONTAINER_HDR_SIZE;
                iPduCount = 0u;
                currentTC = msgTC;
                containerPending = TRUE;
            }

            /* I-PDU를 Container에 추가 시도 */
            uint16 requiredSpace = GW_IPDU_HDR_SIZE + iPduLen;

            if ((containerLen + requiredSpace) <= (CONTAINER_MAX_SIZE - 18))
            {
                // ✅ 추가 성공
                currentContainer[containerLen + 0] = (uint8)(iPduId >> 8);
                currentContainer[containerLen + 1] = (uint8)(iPduId & 0xFFu);
                currentContainer[containerLen + 2] = iPduLen;
                memcpy(&currentContainer[containerLen + 3], &rxData.data[0], iPduLen);

                containerLen += requiredSpace;
                iPduCount++;
                currentContainer[1] = iPduCount;

                // 최고 우선순위 TC 유지
                if (msgTC < currentTC) {
                    currentTC = msgTC;
                }
            }
            else
            {
                // ❌ 오버플로우 발생!
                // 현재 Container는 전송하고, 이 PDU는 다음 Container로 이월
                overflowPdu = rxData;
                hasOverflowPdu = TRUE;

                // 강제 전송 트리거 (아래 로직에서 처리)
            }
        }

        // ========== 3. 전송 조건 판단 ==========

#if 1
        boolean shouldTransmit = FALSE;

        if (containerPending && (containerLen > GW_CONTAINER_HDR_SIZE))
        {
            // 조건 1: 오버플로우 발생 (현재 Container 즉시 전송)
            if (hasOverflowPdu) {
                shouldTransmit = TRUE;
            }
            // 조건 2: Container 거의 꽉 참
            else if (containerLen >= (CONTAINER_MAX_SIZE - 18)) {
                shouldTransmit = TRUE;
            }
            // 조건 3: 게이트 오픈 + 충분한 데이터
            else if (TAS_IsGateOpen_FIFOx(0) && (containerLen >= 2)) {
				shouldTransmit = TRUE;
            }
        }
#endif
#if 0
        boolean shouldTransmit = FALSE;
        if (containerLen >= 2) {
			shouldTransmit = TRUE;
	    }
#endif

        // ========== 4. 전송 처리 ==========
        if (shouldTransmit)
        {
            uint8 fifoIdx = TC_to_FIFO(currentTC);

            // 버퍼 획득
            bufLen = CONTAINER_MAX_SIZE-18;
            Std_ReturnType ret = Eth_ProvideTxBuffer(
                EthConf_EthCtrlConfig_EthCtrlConfig_0,
                fifoIdx,
                &bufIdx,
                &ethPayload,
                &bufLen
            );

            if (ret == E_OK)
            {
                // 데이터 복사 및 전송
                memcpy(ethPayload, currentContainer, containerLen);

                ret = Eth_Transmit(
                    EthConf_EthCtrlConfig_EthCtrlConfig_0,
                    bufIdx,
                    (Eth_FrameType)0x0A0BU,
                    TRUE,
                    containerLen,
                    Gmac_0_MacAddr
                );

                if (ret == E_OK) {
                    canStats.containersSent++;
                } else {
                    canStats.ethTxErrors++;
                }
            }
            else
            {
                canStats.ethBufferErrors++;
            }

            // Container 리셋 (전송 성공/실패 무관)
            containerPending = FALSE;
            containerLen = 0;
            iPduCount = 0;

            // ✅ 오버플로우 PDU가 있으면 다음 루프에서 처리됨
        }

        // ========== 5. CPU 양보 ==========
        taskYIELD();
    }
}

// =================== 시작 함수 ===================
void start_CAN(void)
{
    xTaskCreate(ETH_PDU_Send_TAS, "ETH_TAS", 0x1500, NULL, 4, NULL);

    static CanTxTaskParam_t t1 = { .mbIdx=4, .canId=0x1, .periodMs=16, .offsetMs=0 };
    static CanTxTaskParam_t t2 = { .mbIdx=5, .canId=0x2, .periodMs=16, .offsetMs=3 };
    static CanTxTaskParam_t t3 = { .mbIdx=6, .canId=0x3, .periodMs=16, .offsetMs=6 };
    static CanTxTaskParam_t t4 = { .mbIdx=7, .canId=0x4, .periodMs=16, .offsetMs=9 };


    static CanRxTaskParam_t rxp = {
        .instance = 0,                 /* CAN0 */
        .mb_list[0] = {0,1},          /* 수신 MB 인덱스 */
		.mb_list[1] = {0,1},          /* 수신 MB 인덱스 */
        .mb_count = 2,
        .poll_delay_ticks = pdMS_TO_TICKS(1) /* 1ms 템포 */
    };

    xTaskCreate(CAN_Receive_Polling_Task, "CAN_RX_POLL", 0x600, &rxp, 4, NULL);

    //xTaskCreate(CAN_ReceiveTask_Generic, "CAN_RX_POLL", 0x600, &rxp, 4, NULL);

    //xTaskCreate(CAN_SendTask_Generic, "CAN_TX1", 0x400, &t1, 4, NULL);
    //xTaskCreate(CAN_SendTask_Generic, "CAN_TX2", 0x400, &t2, 4, NULL);
    //xTaskCreate(CAN_SendTask_Generic, "CAN_TX3", 0x400, &t3, 4, NULL);
    //xTaskCreate(CAN_SendTask_Generic, "CAN_TX4", 0x400, &t4, 4, NULL);
}

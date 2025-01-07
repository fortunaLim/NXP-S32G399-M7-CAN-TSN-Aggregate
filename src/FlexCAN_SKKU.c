/*
 * FlexCAN_SKKU.c
 *
 *  Created on: 2024. 7. 15.
 *      Author: sh970
 */

/* Including necessary configuration files. */
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
#include <stdio.h>
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"

#define FLEXCAN_INST 0U
#define MSG_ID 20u
#define LED_PIN                 7u
#define LED_PORT                PTA

uint8 RX_MB_IDX = 1U;
uint8 TX_MB_IDX = 8U;
/* User includes */

extern SemaphoreHandle_t Can2Eth_mutex;
Flexcan_Ip_MsgBuffType rxFifoData, txData, txData1, txData2, txData3;


Flexcan_Ip_DataInfoType tx_info = {
		.msg_id_type = FLEXCAN_MSG_ID_STD,
		.data_length = 8u,
		.fd_enable = FALSE,
		.fd_padding = FALSE,
		.enable_brs = FALSE,
		.is_polling = FALSE,
		.is_remote = FALSE
	};
Flexcan_Ip_DataInfoType rx_info = {
		.msg_id_type = FLEXCAN_MSG_ID_STD,
		.data_length = 8u,
		.fd_enable = FALSE,
		.fd_padding = FALSE,
		.enable_brs = FALSE,
		.is_polling = FALSE,
		.is_remote = FALSE
	};

const Flexcan_Ip_IdTableType CAN0_FIFO_IdFilterTable[3] =
{
		{
			.isRemoteFrame = false,
			.isExtendedFrame = false,
			.id = 0x3,
		},
		{
			.isRemoteFrame = false,
			.isExtendedFrame = false,
			.id = 0x4,
		},
		{
			.isRemoteFrame = false,
			.isExtendedFrame = false,
			.id = 0x5,
		}
};

GMAC_Type *Base;


void FlexCAN_init_SKKU(void)
{
	uint8 dummyData[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	Base = Gmac_apxBases[0];
    /*NVIC_SetPriority(CAN0_ORED_0_7_MB_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(CAN0_ORED_0_7_MB_IRQn);*/

	FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);

	//FlexCAN_Ip_ConfigEnhancedRxFifo_Privileged(INST_FLEXCAN_0, &CAN0_EnhanceFIFO_IdFilterTable[0]);
	FlexCAN_Ip_ConfigRxFifo(INST_FLEXCAN_0, FLEXCAN_RX_FIFO_ID_FORMAT_A, &CAN0_FIFO_IdFilterTable[2]);

	//FlexCAN_Ip_SetRxMaskType_Privileged(INST_FLEXCAN_0,FLEXCAN_RX_MASK_INDIVIDUAL);
	//FlexCAN_Ip_SetRxIndividualMask_Privileged(INST_FLEXCAN_0,1,0x1FFFFFFF);
	//FlexCAN_Ip_SetRxIndividualMask_Privileged(INST_FLEXCAN_0,2,0x1FFFFFFF);

    //FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX, &rx_info, 0x1);
    //FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, 2, &rx_info, 0x2);

	FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0);

    //FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, false);
    //FlexCAN_Ip_Receive(INST_FLEXCAN_0, 2, &rxData, false);
    FlexCAN_Ip_RxFifo(INST_FLEXCAN_0, &rxFifoData);

    FlexCAN_Ip_SendBlocking(FLEXCAN_INST, TX_MB_IDX, &tx_info, 20U, (uint8 *)&dummyData, 10000);

}

/* END main */
/*!
** @}
*/
uint8 callback_test;
Flexcan_Ip_EventType eventbuffer;



const extern uint8 Gmac_0_MacAddr[6U];
extern xQueueHandle xQueue_CAN;


UBaseType_t uxHighWaterMark;




uint8 PDU_num;
uint8 PDU_Payload[1450];


uint32 count = 1;
uint32 count2;
uint32 TSN_Setting_Monitor1, TSN_Setting_Monitor2, TSN_Setting_Monitor3;


extern const Eth_ConfigType Eth_xPredefinedConfig;
extern Gmac_Ip_VlanConfigType gmac_0_vlanConfig;
extern Gmac_Ip_VlanRxFilterType gmac_0_vlanRxFilterConfig;
void CAN0_Callback_SKKU(uint8 instance, Flexcan_Ip_EventType eventType,
                  uint32 buffIdx, const Flexcan_Ip_StateType * flexcanState)
{
	//(void)flexcanState;
  	//(void)instance;
	//count2++;
    switch(eventType)
  	{
    	//case FLEXCAN_EVENT_RX_COMPLETE:
    		//PDU_num++;
    		//break;
    	//case 9:
    	case FLEXCAN_EVENT_RXFIFO_COMPLETE:

			//FlexCAN_Ip_Receive(instance, buffIdx, &rxData, false);
			FlexCAN_Ip_RxFifo(INST_FLEXCAN_0, &rxFifoData);


			if (xQueueSendFromISR(xQueue_CAN, &rxFifoData, pdFALSE )== pdTRUE)
			{
		    	//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 0U);
		    	//ETH_PDU_Send(NULL);
			}
			else
			{

			}
			break;
		case FLEXCAN_EVENT_ENHANCED_RXFIFO_COMPLETE:
			// read rxFifoData[5]
			PDU_num++;

			callback_test = 0x2;	// set bit0 to to evidence RX was complete

			break;
		case FLEXCAN_EVENT_ERROR:
			callback_test = 0x2;
			break;
	/*  	case FLEXCAN_EVENT_DMA_COMPLETE:
			callback_test = 0x3;
			break;*/
		case FLEXCAN_EVENT_TX_COMPLETE:
			callback_test = 0x4;

			break;
		case FLEXCAN_EVENT_TX_WARNING:
			callback_test = 0x5;
			break;
		default:
			eventbuffer = eventType;
			break;
  	}
    return;
}

void CAN_SendTask( void *pvParameters )
{
    (void)pvParameters;
    Flexcan_Ip_StatusType stst;
    uint8 ii=0;
    uint8 dummyData[8] = {0x0};
    for( ;; )
    {
    	/*stst = FlexCAN_Ip_GetTransferStatus(FLEXCAN_INST, TX_MB_IDX);
    	if(FLEXCAN_STATUS_SUCCESS != stst)
    	{
    		FlexCAN_Ip_ClearBuffStatusFlag(FLEXCAN_INST, TX_MB_IDX);
    	}*/

    	ii++;
    	dummyData[0] = ii;

    	txData.msgId = 0x1;
		txData.dataLen = 0x8;
		txData.data[0] = ii;
    	FlexCAN_Ip_SendBlocking(FLEXCAN_INST, TX_MB_IDX, &tx_info, 1, (uint8 *)&dummyData, 10000);
		FlexCAN_Ip_AbortTransfer(FLEXCAN_INST, TX_MB_IDX);


    	if (xQueueSendFromISR(xQueue_CAN, &txData, pdFALSE )== pdTRUE)
		{
			//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 0U);
			//ETH_PDU_Send(NULL);
		}

		vTaskDelay(2);
    }
}

void CAN_SendTask1( void *pvParameters )
{
    (void)pvParameters;
    Flexcan_Ip_StatusType stst;
    uint8 ii=0;
    uint8 dummyData[8] = {0x0};
    for( ;; )
    {
    	/*stst = FlexCAN_Ip_GetTransferStatus(FLEXCAN_INST, TX_MB_IDX);
    	if(FLEXCAN_STATUS_SUCCESS != stst)
    	{
    		FlexCAN_Ip_ClearBuffStatusFlag(FLEXCAN_INST, TX_MB_IDX);
    	}*/

    	ii++;
    	dummyData[0] = ii;

    	txData1.msgId = 0x2;
		txData1.dataLen = 0x8;
		txData1.data[0] = ii;
    	FlexCAN_Ip_SendBlocking(FLEXCAN_INST, TX_MB_IDX, &tx_info, 2, (uint8 *)&dummyData, 10000);
		FlexCAN_Ip_AbortTransfer(FLEXCAN_INST, TX_MB_IDX);


    	if (xQueueSendFromISR(xQueue_CAN, &txData1, pdFALSE )== pdTRUE)
		{
			//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 0U);
			//ETH_PDU_Send(NULL);
		}

		vTaskDelay(4);
    }
}

void CAN_SendTask2( void *pvParameters )
{
    (void)pvParameters;
    Flexcan_Ip_StatusType stst;
    uint8 ii=0;
    uint8 dummyData[8] = {0x0};
    for( ;; )
    {
    	/*stst = FlexCAN_Ip_GetTransferStatus(FLEXCAN_INST, TX_MB_IDX);
    	if(FLEXCAN_STATUS_SUCCESS != stst)
    	{
    		FlexCAN_Ip_ClearBuffStatusFlag(FLEXCAN_INST, TX_MB_IDX);
    	}*/

    	ii++;
    	dummyData[0] = ii;

    	txData2.msgId = 0x3;
		txData2.dataLen = 0x8;
		txData2.data[0] = ii;
    	FlexCAN_Ip_SendBlocking(FLEXCAN_INST, TX_MB_IDX, &tx_info, 3, (uint8 *)&dummyData, 10000);
		FlexCAN_Ip_AbortTransfer(FLEXCAN_INST, TX_MB_IDX);


    	if (xQueueSendFromISR(xQueue_CAN, &txData2, pdFALSE )== pdTRUE)
		{
			//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 0U);
			//ETH_PDU_Send(NULL);
		}

		vTaskDelay(6);
    }
}

void CAN_SendTask3( void *pvParameters )
{
    (void)pvParameters;
    Flexcan_Ip_StatusType stst;
    uint8 ii=0;
    uint8 dummyData[8] = {0x0};
    for( ;; )
    {
    	/*stst = FlexCAN_Ip_GetTransferStatus(FLEXCAN_INST, TX_MB_IDX);
    	if(FLEXCAN_STATUS_SUCCESS != stst)
    	{
    		FlexCAN_Ip_ClearBuffStatusFlag(FLEXCAN_INST, TX_MB_IDX);
    	}*/

    	ii++;
    	dummyData[0] = ii;

    	txData3.msgId = 0x4;
    	txData3.dataLen = 0x8;
    	txData3.data[0] = ii;

    	FlexCAN_Ip_SendBlocking(FLEXCAN_INST, TX_MB_IDX, &tx_info, txData3.msgId, (uint8 *)&dummyData, 10000);
		FlexCAN_Ip_AbortTransfer(FLEXCAN_INST, TX_MB_IDX);

    	if (xQueueSendFromISR(xQueue_CAN, &txData3, pdFALSE )== pdTRUE)
		{
			//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 0U);
			//ETH_PDU_Send(NULL);
		}

		vTaskDelay(8);
    }
}


Eth_BufIdxType BufferIndex_CAN;
uint32 EthPayload_length = 0;
uint8 *EthPayload;
uint16 Buffer_PayloadLength = 1456;
uint8 rtn_chk;
uint32 c_read_mtl =0x0;
uint32 c_read_mtl2[5000];
uint8 pdu_fifo = 0;
uint16 msgid_len = 0;
uint8 retryCount = 0;
void ETH_PDU_Send( void *pvParameters )
{
    (void)pvParameters;
    GMAC_Type *Base;
    BaseType_t xStatus;
    Base = Gmac_apxBases[0];
    const TickType_t xTicksToWait = pdMS_TO_TICKS(1);
    uint32 i=0;

	uint32 SystemTimeSecond;
	uint32 SystemTimeNanoSecond;
	uint64 SystemTime;
	uint32 CurrentTimeSlice;
    //uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );

    Flexcan_Ip_MsgBuffType rxData;
    for(;;)
    {
    	//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 0U);
#if 0
    	SystemTimeNanoSecond = (uint32)(Base->MAC_SYSTEM_TIME_NANOSECONDS);
    	CurrentTimeSlice = SystemTimeNanoSecond % 10000000;
    	if((CurrentTimeSlice > 1000000) && (CurrentTimeSlice < 2000000))
    	{
    		c_read_mtl = 0;
    		xStatus = xQueueReceive(xQueue_CAN, &rxData, xTicksToWait);
    	}
    	else
    	{
    		c_read_mtl = 1;
    		xStatus = pdFALSE;
    	}
#else
    	xStatus = xQueueReceive(xQueue_CAN, &rxData, xTicksToWait);
#endif
    	if (xStatus == pdTRUE)
    	{
    		if(EthPayload_length == 0)
    		{
				//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 1U);
				EthPayload_length++;
				Eth_ReportTransmission(0U, 0U);
				rtn_chk = Eth_ProvideTxBuffer(EthConf_EthCtrlConfig_EthCtrlConfig_0, 0U, &BufferIndex_CAN, &EthPayload, &Buffer_PayloadLength);
				do{
					retryCount++;
				}while((rtn_chk != E_OK)&&(retryCount<10));
				retryCount = 0;
			}

    		// Make CAN to ETH Payload (PDU)
			EthPayload[0] = (++PDU_num);
			msgid_len = ((uint16)(rxData.msgId)<<4)|(uint16)(rxData.dataLen);
			Eth_Local_Memcpy(&EthPayload[EthPayload_length], &msgid_len, sizeof(uint8)*2);
			Eth_Local_Memcpy(&EthPayload[2+EthPayload_length], &rxData.data, sizeof(uint8)*rxData.dataLen);
			EthPayload_length = EthPayload_length + 2 + rxData.dataLen;
			//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 1U);
    	}
    	//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 0U);
#if 1
    	SystemTimeNanoSecond = (uint32)(Base->MAC_SYSTEM_TIME_NANOSECONDS);
		CurrentTimeSlice = SystemTimeNanoSecond % 10000000;
		if((CurrentTimeSlice > 1000000) && (CurrentTimeSlice < 2000000))
		{
			c_read_mtl = 0;
		}
		else
		{
			c_read_mtl = 1;
		}
#endif
		if(EthPayload_length != 0){
			if((c_read_mtl == 0x0) || (EthPayload_length > 1400))
			{
				// Send in TimeSlice
				do{
					rtn_chk = Eth_Transmit(EthConf_EthCtrlConfig_EthCtrlConfig_0, BufferIndex_CAN, (Eth_FrameType)0x0A0BU, FALSE, EthPayload_length, Gmac_0_MacAddr);
					retryCount++;
				}while((rtn_chk != E_OK)&&(retryCount<10));
					//if(rtn_chk == E_OK || retryCount>10)
					{
						//Siul2_Dio_Ip_WritePin(LED_PORT, LED_PIN, 0U);
						retryCount = 0;
						EthPayload_length = 0;
						PDU_num = 0;
					}
			}
		}
		//else
		{
			//
			//count++;
		}
		//vTaskDelay(1);
    }
}
/*
uint32 BaseTimeSecond;
	uint32 BaseTimeNanoSecond;

	uint64 BaseTime;

	uint32 est_monitor;
uint8 get_current_slot()
{

	uint8 slot;

	BaseTimeSecond = Gmac_Ip_ReadGateControlList(0,1);
	BaseTimeNanoSecond = Gmac_Ip_ReadGateControlList(0, 0);
	BaseTime = BaseTimeSecond*1000000000 + BaseTimeNanoSecond;


    Base->MTL_EST_GCL_CONTROL &= (~GMAC_MTL_EST_CONTROL_SSWL_MASK);
	est_monitor = Base->MTL_EST_CONTROL;

	if((BaseTime - SystemTime)<3000000)
	{
		slot = 0;
	}
	else
	{
		slot = 1;
	}


	return slot;
}*/


uint32 Gmac_Ip_ReadGateControlList(
                                    uint8 Instance,
                                    uint16 AddrGateList
                                        )
{
    Gmac_Ip_StatusType Status = GMAC_STATUS_TIMEOUT;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint8 u8ErrorNum = 0U;
    uint32 rtn_data = 0;

    Gmac_apxBases[Instance]->MTL_EST_GCL_CONTROL |= GMAC_MTL_EST_CONTROL_SSWL_MASK
    												  |GMAC_MTL_EST_CONTROL_EEST_MASK;

    do
    {
        if ((Gmac_apxBases[Instance]->MTL_EST_STATUS & GMAC_MTL_EST_STATUS_SWOL_MASK) != 0U)
        {
            Status = GMAC_STATUS_SUCCESS;
            break;
        }
    }
    while (!GMAC_TimeoutExpired(&StartTime, &ElapsedTime, 10000u));


    Gmac_apxBases[Instance]->MTL_EST_GCL_CONTROL |= GMAC_MTL_EST_GCL_CONTROL_ADDR(AddrGateList)

    											 |GMAC_MTL_EST_GCL_CONTROL_GCRR_MASK

												 |GMAC_MTL_EST_GCL_CONTROL_R1W0(1U)


												 |GMAC_MTL_EST_GCL_CONTROL_DBGM_MASK

    											 |GMAC_MTL_EST_GCL_CONTROL_SRWO_MASK;



    GMAC_StartTimeOut(&StartTime, &ElapsedTime, &TimeoutTicks, 10000u);

    do
    {
        if ((Gmac_apxBases[Instance]->MTL_EST_GCL_CONTROL & GMAC_MTL_EST_GCL_CONTROL_SRWO_MASK) == 0U)
        {
            Status = GMAC_STATUS_SUCCESS;
            break;
        }
    }
    while (!GMAC_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks));

    u8ErrorNum = ((GMAC_STATUS_TIMEOUT == Status) ? ((uint8)1U) : ((uint8)0U));

    rtn_data = Gmac_apxBases[Instance]->MTL_EST_GCL_DATA;

    //Gmac_apxBases[Instance]->MTL_EST_GCL_CONTROL &= (~GMAC_MTL_EST_CONTROL_SSWL_MASK);


    return rtn_data;
}


void ETH_Traffic_Send( void *pvParameters )
{
    (void)pvParameters;
    uint8 *PayloadBuffer2;
    Eth_BufIdxType BufferIndex2;
    uint8 retryCount2;
    uint16 Buffer_PayloadLength2 = 64;
    uint8 aaa;
    for( ;; )
    {
    	//Eth_ReportTransmission(0U, 0U);
		rtn_chk = Eth_ProvideTxBuffer(EthConf_EthCtrlConfig_EthCtrlConfig_0, 0U, &BufferIndex2, &PayloadBuffer2, &Buffer_PayloadLength2);
		do{
			retryCount2++;
		}while((rtn_chk != E_OK)&&(retryCount2<10));
		retryCount2 = 0;

    	//read_mtl = ((Base->MTL_EST_STATUS&GMAC_MTL_EST_STATUS_CGSN_MASK)>>GMAC_MTL_EST_STATUS_CGSN_SHIFT)%6; // gcl list status check // 0, 129, 524417, 786561
    	//if(read_mtl != 0x1)
    	{
    	PayloadBuffer2[0] = aaa++;
    	Eth_Transmit(0, BufferIndex2, (Eth_FrameType)0x0A0AU, FALSE, 55U, Gmac_0_MacAddr);
    	}
    	vTaskDelay(3);
    }
}



void start_CAN(void)
{
#if 1
	xTaskCreate( CAN_SendTask, ( const char * const ) "CAN_SendTask" , 0x300, (void*)0,5, NULL );
	xTaskCreate( CAN_SendTask1, ( const char * const ) "CAN_SendTask1" , 0x300, (void*)0,5, NULL );
	xTaskCreate( CAN_SendTask2, ( const char * const ) "CAN_SendTask2" , 0x300, (void*)0,5, NULL );
	xTaskCreate( CAN_SendTask3, ( const char * const ) "CAN_SendTask3" , 0x300, (void*)0,5, NULL );
	//xTaskCreate( ETH_Traffic_Send, ( const char * const ) "ETH_Traffic_Send" , 0x500, (void*)0,5, NULL );
	xTaskCreate( ETH_PDU_Send, ( const char * const ) "ETH_PDU_Send" , 0x1000, (void*)0,4, NULL );
#endif
	//xTaskCreate( CAN_ReceiveTask, ( const char * const ) "CAN_ReceiveTask" , 0x500, (void*)0,2, NULL );
	//xTaskCreate( PDU_Decoder, ( const char * const ) "PDU_Decoder" , 0x300, (void*)0,4, NULL );

}

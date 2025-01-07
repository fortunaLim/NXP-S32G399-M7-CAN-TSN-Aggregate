/*
 * TSN_SKKU.c
 *
 *  Created on: 2024. 8. 5.
 *      Author: sh970
 */
#include "ETH_SKKU.h"
#include "GMAC_PTP_SKKU.h"
#include "FlexCAN_SKKU.h"
#include <stdio.h>
#include "Gmac_Ip_Types.h"

extern Ptp_PayloadTpye PTP_SYNC_Frame, PTP_REQ_Frame, PTP_RESP_Frame, PTP_Fallow_Frame;
extern Flexcan_Ip_DataInfoType tx_info;
extern uint8 TX_MB_IDX;
uint8	Eth_Des_MAC[6] = {0x01, 0x1b, 0x19, 0x00, 0x00, 0x00};
uint8	Eth_Src_MAC[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x99};
uint8	Eth_Type[4] = {0x00,0x0A,0X00,0X0B};
Gmac_Ip_StatusType Gmac_status_eth;

uint32 TSN_Setting_Monitor;

Flexcan_Ip_DataInfoType tx_info2 = {
		.msg_id_type = FLEXCAN_MSG_ID_STD,
		.data_length = 8u,
		.fd_enable = FALSE,
		.fd_padding = FALSE,
		.enable_brs = FALSE,
		.is_polling = FALSE,
		.is_remote = FALSE
	};

void TSN_init()
{
    GMAC_Type *Base;
    Base = Gmac_apxBases[0];


#if 1
    /*Base->MTL_EST_GCL_CONTROL |= GMAC_MTL_EST_GCL_CONTROL_DBGB(0x0)
    					  |  GMAC_MTL_EST_GCL_CONTROL_DBGM(0x1);*/

    //TSN_Setting_Monitor = Base->MTL_EST_CONTROL;// |= GMAC_MTL_EST_CONTROL_SSWL_MASK;

    //Base->MTL_EST_GCL_CONTROL =  Base->MTL_EST_GCL_CONTROL & (~GMAC_MTL_EST_GCL_CONTROL_GCRR_MASK);
#endif
}


/*volatile uint32 read_mtl =0x0;
volatile uint32 read_txq0 =0x0;
volatile uint32 read_txq1 =0x0;
volatile uint32 read_txq2 =0x0;
volatile uint32 readread  =0x0;
void read_status( void *pvParameters )
{
	(void)pvParameters;
    GMAC_Type *Base;
    Base = Gmac_apxBases[0];
    for(;;){

    	//read_txq0 = Base->MTL_EST_GCL_CONTROL; // 1284
    	//read_txq0 = Base->MTL_TXQ0_DEBUG; // 6, 131088, 65552
    	//read_txq1 = Base->MTL_TXQ1_DEBUG; // 6, 131088, 65552
    	//read_txq2 = Base->MTL_TXQ2_DEBUG; // 6, 131088, 65552
    	//read_txq0 = Base->MTL_TXQ0_OPERATION_MODE; // 589834
    	//read_txq0 = Base->MTL_TXQ1_ETS_CONTROL; //
    	//read_txq1 = Base->MTL_EST_CONTROL; // 3, 1
    	//read_mtl = ((Base->MTL_EST_STATUS&GMAC_MTL_EST_STATUS_CGSN_MASK)>>GMAC_MTL_EST_STATUS_CGSN_SHIFT)%6; // gcl list status check // 0, 129, 524417, 786561
    	//read_txq0 = Base->MTL_EST_GCL_DATA; // 2
    	if(read_mtl != readread)
    	{
    		readread = read_mtl;
    	}
    	else
    	{

    	}
    	//vTaskDelay(1000);
    }
}*/

extern xQueueHandle xQueue;
uint32 ETH_err;
uint8 ETH_time_out = 0;
Gmac_Ip_BufferType bd;
void Eth_RxIrqCallback_SKKU(uint8 instance, uint8 channel)
{

	/*
    Gmac_Ip_RxInfoType info;
    uint32 ret;

    Gmac_Ip_ChannelType *ChBase;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(3);
	Gmac_Ip_BufferDescriptorType *ListBd;
	uint16 aa,bb;
	Gmac_Ip_StatusType gmac_status;

    do
    {
    	//Gmac_Ip_ProvideRxBuff(instance, channel, &bd);
        gmac_status = Gmac_Ip_ReadFrame(instance, channel, &bd, &info);
        if (GMAC_STATUS_SUCCESS == gmac_status)
        {
            if (0 != info.ErrMask)
            {
                ret = ERR_IF;
                if (GMAC_RX_ERR_OVERFLOW_ERROR != (GMAC_RX_ERR_OVERFLOW_ERROR | info.ErrMask))
                {
                    //
                }
            }
            else
            {
            	if (Gmac_Ip_IsFrameAvailable(0, channel))
				{
            		gmac_status = 2;
				}
        		if(bd.Data[12+4] == 0x88) // non-vlan ver
        		{
        		//if(bd.Data[10] == 0x88) { // vlan ver

        #if PTP_Slave == 1
        			if(bd.Data[14] == 0x00) // sync
        			{
        				if(PTP_Update == 0)
        				{
        					rx_lock = 0;
        					PTP_Update = 0;

        					Time_T2.seconds = info.Timestamp.seconds;
        					Time_T2.nanoseconds = info.Timestamp.nanoseconds;

        					Eth_Local_Memcpy(utemp_sec_T1, &bd.Data[0x30],6);
        					Eth_Local_Memcpy(utemp_nsec_T1, &bd.Data[0x36],4);

        #if PTP_UPDT_MODE == 1
        					sendDealyReq();
        #endif

        				}
        			}
        			else if(bd.Data[14] == 0x09) // update
        			{
        				if(PTP_Update == 0) // OFFLOAD
        				{

        #if PTP_UPDT_MODE == 2
        					Time_T3.seconds = Base->MAC_TX_TIMESTAMP_STATUS_SECONDS;
        					Time_T3.nanoseconds = Base->MAC_TX_TIMESTAMP_STATUS_NANOSECONDS;
        #endif
        					Eth_Local_Memcpy(utemp_sec_T4, &bd.Data[0x30],6);
        					Eth_Local_Memcpy(utemp_nsec_T4, &bd.Data[0x36],4);

        					PTP_Update = 1;
        					PTP_Update_func();

        				}
        			}
        #endif
        #if PTP_UPDT_MODE == 1
        #if PTP_Master == 1
        			if(bd.Data[14] == 0x01) // delay_resp
        			{
        				PTP_RESP_Frame.req_Src_PortId[1] = bd.Data[0x2b];
        				PTP_RESP_Frame.req_Src_PortId[0] = bd.Data[0x2a];
        				sendDelayResp();
        			}
        #endif
        #endif
        		}
        		else if(bd.Data[12+4] == 0x0A) // CAN PDU receive
        		{

        			//Gmac_Ip_ProvideRxBuff(instance, channel, &bd);
        			//if (xQueueSendFromISR( xQueue, &bd, pdFALSE )== pdTRUE)
        			{
        				//ETH_err++;
        			}
        			//else
        			{

        			}

        		}

            }
            if (ERR_OK != ret)
            {
                //Gmac_Ip_ProvideRxBuff(instance, channel, &bd);

            }
        }
        ETH_time_out++;
    }while((GMAC_STATUS_SUCCESS != gmac_status) &&
    	      (2 != gmac_status) &&
    	      (ETH_time_out > 10));
    ETH_time_out = 0;
    */
}

	uint16 CAN_i,CAN_j ;
   uint16 CAN_MSG_ID = 0;
   uint8 CAM_MSG_LEN = 0;
   uint8 PDU_num_Tx = 0;

   Gmac_Ip_BufferType bd2;

volatile uint32 CAN_msg_index = 18;
void Eth2CAN_send( void *pvParameters )
{
    (void)pvParameters;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(3);
    BaseType_t xStatus;

    uint32 index_temp=0;
    uint8 dummyData_E2C[8] = {0};
    for(;;)
    {

    	if (xQueueReceive(xQueue, &bd2, xTicksToWait) == pdTRUE)
    	{
    	CAN_msg_index = 18;
		PDU_num_Tx = bd2.Data[CAN_msg_index];
		CAN_msg_index++;

		for(CAN_i=0;CAN_i<PDU_num_Tx;CAN_i++)
		{
			vTaskDelay(1);
			CAN_MSG_ID = (bd2.Data[CAN_msg_index]>>4) | bd2.Data[CAN_msg_index+1]<<4;
			CAM_MSG_LEN =bd2.Data[CAN_msg_index] & 0xf;
			CAN_msg_index = CAN_msg_index + 2;

			index_temp = CAN_msg_index;

			for(CAN_msg_index; CAN_msg_index<index_temp+CAM_MSG_LEN; CAN_msg_index++)
			{
				dummyData_E2C[CAN_msg_index-index_temp] = bd2.Data[CAN_msg_index];
			}

			//memcpy(&dummyData_E2C[CAN_msg_index], &bd.Data[CAN_msg_index], CAM_MSG_LEN);
			//CAN_msg_index = CAN_msg_index+CAM_MSG_LEN;
			tx_info.data_length = CAM_MSG_LEN;

			TSN_Setting_Monitor = FlexCAN_Ip_SendBlocking(0U, TX_MB_IDX, &tx_info, CAN_MSG_ID, (uint8 *)&dummyData_E2C, 10000);
			FlexCAN_Ip_AbortTransfer(0U, TX_MB_IDX);

			TX_MB_IDX = 8+(TX_MB_IDX+1)%8;

		}
    	}
		vTaskDelay(1);
    }
}

void tas_trans_test( void *pvParameters )
{
    (void)pvParameters;
    uint8 Gmac_0_MacAddr[6U] = {0x01,0x1b,0x19,0x00,0x00,0x00};
    Eth_BufIdxType BufferIndex2, BufferIndex_RX;
    uint8 *PayloadBuffer2;
    uint8 aaa = 0;
    GMAC_Type *Base;
    Base = Gmac_apxBases[0];
    for( ;; )
    {
    	//read_mtl = ((Base->MTL_EST_STATUS&GMAC_MTL_EST_STATUS_CGSN_MASK)>>GMAC_MTL_EST_STATUS_CGSN_SHIFT)%6; // gcl list status check // 0, 129, 524417, 786561
    	//if(read_mtl != 0x1)
    	{
    	Eth_ProvideTxBuffer(EthConf_EthCtrlConfig_EthCtrlConfig_0, 1U, &BufferIndex2, &PayloadBuffer2, 64U);
    	PayloadBuffer2[0] = aaa++;
    	Eth_Local_Memcpy(PayloadBuffer2, (uint8*) &Gmac_0_MacAddr, 64U);
    	Eth_Transmit(EthConf_EthCtrlConfig_EthCtrlConfig_0, BufferIndex2, (Eth_FrameType)0x0A0AU, TRUE, 64U, Gmac_0_MacAddr);
        Eth_TxConfirmation(EthConf_EthCtrlConfig_EthCtrlConfig_0);
    	}
    	vTaskDelay(3);
    }
}

void start_TSN()
{
	//xTaskCreate( Eth2CAN_send, ( const char * const ) "Eth2CAN_send" , 0x800, (void*)0,5, NULL );

	//xTaskCreate( read_status, ( const char * const ) "read_status" , 0x300, (void*)0,2, NULL );
	// trans test
	//xTaskCreate( tas_trans_test, ( const char * const ) "tas_trans_test" , 0x500, (void*)0,5, NULL );
}

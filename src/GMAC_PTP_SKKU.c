
/* Including necessary configuration files. */

#include "GMAC_PTP_SKKU.h"

/////////////////////////////////

Ptp_PayloadTpye PTP_SYNC_Frame, PTP_REQ_Frame, PTP_RESP_Frame, PTP_Fallow_Frame;


/**************************************************************************/
// PTP
/**************************************************************************/
uint8	PTP_Des_MAC[6] = {0x01, 0x1b, 0x19, 0x00, 0x00, 0x00};
uint8	PTP_Src_MAC[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x99};

const uint8	Master_ClockID[8] = {0x01, 0x1b, 0x19, 0xFF, 0xFE, 0x01, 0x02, 0x03}; // PTP Local Clock ID
const uint8	Slave_ClockID[8]  = {0x01, 0x1b, 0x19, 0xFF, 0xFE, 0x04, 0x05, 0x06}; // PTP Local Clock ID

const uint8	Master_PortNum[2] = {0x00, 0x01}; // PTP Local PortNum
const uint8	Slave_PortNum[2]  = {0x00, 0x02}; // PTP Local PortNum

uint8	PTP_VLAN_TYPE[2] = {0x81, 0x00};

uint8 temp_uint8[2];

Eth_TimeStampType Time_Temp1;
Eth_TimeStampType Time_T1;
Eth_TimeStampType TimeStampRESP, TimeStampSYNC;
Eth_TimeStampType Time_T1_old;
Eth_TimeStampType Time_T2;
Eth_TimeStampType Time_T2_old;
Eth_TimeStampType Time_T3;
Eth_TimeStampType Time_T4;
Eth_TimeStampType Time_Current;

volatile uint8 utemp_sec_T1[6], utemp_nsec_T1[4];
volatile uint8 utemp_sec_T4[6], utemp_nsec_T4[4];

volatile uint8 PTP_Update = 0;

sint32 PTP_sec_Offset, PTP_nsec_Offset, PTP_Offset_initial;

sint64 PTP_Offset;
sint64 PTP_Offset2;

uint64 PTP_Offset_abs;
uint32 PTP_new_nsec, PTP_new_sec;
uint32 PTP_avg_nsec, PTP_avg_sec;
uint8 PTP_sign;
uint64 PTP_T1, PTP_T2, PTP_T3, PTP_T4, PTP_Current,PTP_T1_old,PTP_T2_old, PTP_Temp3;
uint32 manual_offset;
uint8 PTP_Lock;
uint8 rx_lock=0;
uint8 Gmac_0_MacAddr[6U] = {0x01,0x1b,0x19,0x00,0x00,0x00};
Eth_BufIdxType BufferIndex, BufferIndex_RX;
uint8 *PayloadBuffer;

extern Flexcan_Ip_DataInfoType tx_info;
/**************************************************************************/
// Vlan
/**************************************************************************/
/*
Gmac_Ip_VlanConfigType gmac_0_vlanConfig =
{
	 .enDoubleVlan =  TRUE,
	 .enSvlan =  FALSE,
	 .outerVlanIns =  GMAC_VLAN_TAG_INSERTION,
	 .innerVlanIns =  GMAC_VLAN_TAG_INSERTION,
	 .outerVlanStrip =  GMAC_VLAN_TAG_DO_NOT_STRIP,
	 .innerVlanStrip =  GMAC_VLAN_TAG_DO_NOT_STRIP,
};

Gmac_Ip_VlanRxFilterType gmac_0_vlanRxFilterConfig = {
 .enInnerVlanMatch =  FALSE,
 .enSvlanMatch =  FALSE,
 .disVlanTypeMatch =  FALSE,
 .enInverseMatch =  FALSE,
 .en12bitMatch =  TRUE,
};
*/

/**************************************************************************/
// Ethernet
/**************************************************************************/
Gmac_Ip_BufferType TxBuffer = {0};
Gmac_Ip_BufferType RxBuffer = {0};
Gmac_Ip_TxInfoType TxInfo;
Gmac_Ip_RxInfoType RxInfo;
Gmac_Ip_StatusType Status;
Gmac_Ip_TxOptionsType TxOptions = {TRUE, FALSE, FALSE};
uint16 ChFrameType;

extern GMAC_Type * const Gmac_apxBases[FEATURE_GMAC_NUM_INSTANCES];
extern Gmac_Ip_StateType *Gmac_apxState[FEATURE_GMAC_NUM_INSTANCES];
extern Gmac_Ip_BufferDescriptorType *TxCurrentDesc[FEATURE_GMAC_NUM_CHANNELS]; /*!< The current available transmit buffer descriptor pointer array. */
extern Gmac_Ip_ChannelType * const Gmac_apxChBases[FEATURE_GMAC_NUM_INSTANCES][FEATURE_GMAC_NUM_CHANNELS];

Gmac_Ip_StatusType Gmac_status;
/**************************************************************************/
// ETC..
/**************************************************************************/
uint32 i, a;
uint8 sig_toggle = 0x01;
uint32 Flags;
uint32 Sec_Old = 0;
int ii, jj;
uint8 no_update_zone;
uint32 kkk;
boolean Result = TRUE;

uint64 Offset_array1[1000] = {0};
uint64 Offset_array2[1000] = {0};
uint64 Offset_array3[1000] = {0};
uint64 Offset_array4[1000] = {0};
sint64 Offset_array5[1000] = {0};

////////////////////////////


/**
* @brief        SendTask is used to give the semaphore
* @details      SendTask give the semaphore every 1 second
*/
void GetTimeTask( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;

    for( ;; )
    {
    }
}

/**
* @brief        SendTask is used to give the semaphore
* @details      SendTask give the semaphore every 1 second
*/

uint32 aaaa;
void PrintIOTask( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;
    GMAC_Type *Base;
    Base = Gmac_apxBases[0];
    uint32 bt, bt2;

    for( ;; )
    {
    	bt = (uint32)(Base->MAC_SYSTEM_TIME_NANOSECONDS);
    	bt2 = bt;
    	bt = bt % 100000000;
    	if((bt > 1125 )&&(bt < 1225 ))
    	//if((bt < 1000 ))
    	{
    		sig_toggle = ((bt2 / 100000000))%2;
    		/*Offset_array1[aaaa] = bt;

    		if(aaaa<500)
    		{
    			aaaa++;
    		}*/
    		//sig_toggle ^= 0xff;
    		Siul2_Dio_Ip_WritePin(PTA, 07U, sig_toggle);
    	}
    	//vTaskDelay(1);
    	//vTaskDelay(500);
    }
}

/**
* @brief        ReceiveTask get the semaphore and toggle pins
* @details      ReceiveTask try to get the semaphore with portMAX_DELAY timeout,
*               After receiving the semaphore successfully, the led will be toggle
*               LED_PIN <-> PTB8
*/
void UpdateTask( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;
    BaseType_t count = 0;

    GMAC_Type *Base;
    Base = Gmac_apxBases[0];

    for( ;; )
    {

    	vTaskDelay(500);
    }
}

void PTP_SyncTask( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;
    BaseType_t count = 0;

    GMAC_Type *Base;
    Base = Gmac_apxBases[0];
    uint32 aa=0;
    uint32_t dma_ck;
    for( ;; )
    {
    	if(PTP_Lock == 0)
    	{
#if PTP_UPDT_MODE == 1
#if PTP_Master == 1
    		sendSynchronization();
#endif
#endif
    	}
    	vTaskDelay(10);
    }
}

void PTP_init()
{
	uint8 temp_uint8[2];
	uint8 i;


	/*=====================================================================*/
	// Set PTP SYNC Header
	/*=====================================================================*/
	/*=====================================================================*/
	// Set PTP SYNC Header
	/*=====================================================================*/
	/*=====================================================================*/
	// Set PTP SYNC Header
	/*=====================================================================*/

	PTP_SYNC_Frame.MsgType = Sync;
	PTP_SYNC_Frame.trans_Spec = 0x0;
	PTP_SYNC_Frame.versionPTP = IEEE1588v2;
	PTP_SYNC_Frame.Reserved_a = 0x0;

	//memcpy(PTP_REQ_Frame.MsgLength, 0x002c, 2U);
	for(i=0U;i<2U;i++) PTP_SYNC_Frame.MsgLength[i] = (0x002c >> 8U*(2U-(i+1U))) &0xff;

	PTP_SYNC_Frame.DomainNumber = 0x0;
	PTP_SYNC_Frame.Reserved_b = 0x0;

	//memcpy(PTP_REQ_Frame.correctField, 0x00, 8U);
	for(i=0U;i<8U;i++) PTP_SYNC_Frame.correctField[i] = (0x00 >> 8U*(8U-(i+1U))) &0xff;
	//memcpy(PTP_REQ_Frame.Reserved_c, 0x00, 4U);
	for(i=0U;i<4U;i++) PTP_SYNC_Frame.Reserved_c[i] = (0x00 >> 8U*(4U-(i+1U))) &0xff;

	memcpy(PTP_SYNC_Frame.SrcClockID, Master_ClockID, 8U);
	memcpy(PTP_SYNC_Frame.SrcPortNum, Master_PortNum, 2U);
	PTP_SYNC_Frame.ControlField = 0x0;
	PTP_SYNC_Frame.LogMsgInterval = 0xF9;

	/*=====================================================================*/
	// Set PTP REQ Header
	/*=====================================================================*/
	/*=====================================================================*/
	// Set PTP REQ Header
	/*=====================================================================*/
	/*=====================================================================*/
	// Set PTP REQ Header
	/*=====================================================================*/

	PTP_REQ_Frame.MsgType = Delay_Req;
	PTP_REQ_Frame.trans_Spec = 0x0;
	PTP_REQ_Frame.versionPTP = IEEE1588v2;
	PTP_REQ_Frame.Reserved_a = 0x0;
	temp_uint8[0] = PTP_REQ_Frame.MsgType | (PTP_REQ_Frame.trans_Spec<<4U);
	temp_uint8[1] = PTP_REQ_Frame.versionPTP | (PTP_REQ_Frame.Reserved_a<<4U);

	//memcpy(PTP_REQ_Frame.MsgLength, 0x002c, 2U);
	for(i=0U;i<2U;i++) PTP_REQ_Frame.MsgLength[i] = (0x002c >> 8U*(2U-(i+1U))) &0xff;

	PTP_REQ_Frame.DomainNumber = 0x0;
	PTP_REQ_Frame.Reserved_b = 0x0;

	//memcpy(PTP_REQ_Frame.flags, 0x0000, 2U);
	for(i=0U;i<2U;i++) PTP_REQ_Frame.MsgLength[i] = (0x002c >> 8U*(2U-(i+1U))) &0xff;

	//memcpy(PTP_REQ_Frame.correctField, 0x00, 8U);
	for(i=0U;i<8U;i++) PTP_REQ_Frame.correctField[i] = (0x00 >> 8U*(8U-(i+1U))) &0xff;
	//memcpy(PTP_REQ_Frame.Reserved_c, 0x00, 4U);
	for(i=0U;i<4U;i++) PTP_REQ_Frame.Reserved_c[i] = (0x00 >> 8U*(4U-(i+1U))) &0xff;

	memcpy(PTP_REQ_Frame.SrcClockID, Master_ClockID, 8U);
	memcpy(PTP_REQ_Frame.SrcPortNum, Master_PortNum, 2U);

	PTP_REQ_Frame.ControlField = 0x0;
	PTP_REQ_Frame.LogMsgInterval = 0xF9;

	temp_uint8[0] = PTP_REQ_Frame.MsgType | (PTP_REQ_Frame.trans_Spec<<4U);
	temp_uint8[1] = PTP_REQ_Frame.versionPTP | (PTP_REQ_Frame.Reserved_a<<4U);


	/*=====================================================================*/
	// Set PTP RESP Header
	/*=====================================================================*/
	/*=====================================================================*/
	// Set PTP RESP Header
	/*=====================================================================*/
	/*=====================================================================*/
	// Set PTP RESP Header
	/*=====================================================================*/

	PTP_RESP_Frame.MsgType = 0x09;
	PTP_RESP_Frame.trans_Spec = 0x0;
	PTP_RESP_Frame.versionPTP = IEEE1588v2;
	PTP_RESP_Frame.Reserved_a = 0x0;

	for(i=0U;i<2U;i++) PTP_RESP_Frame.MsgLength[i] = (0x0036 >> 8U*(2U-(i+1U))) &0xff;

	PTP_RESP_Frame.DomainNumber = 0x0;
	PTP_RESP_Frame.Reserved_b = 0x0;

	for(i=0U;i<8U;i++) PTP_RESP_Frame.correctField[i] = (0x00 >> 8U*(8U-(i+1U))) &0xff;

	for(i=0U;i<4U;i++) PTP_RESP_Frame.Reserved_c[i] = (0x00 >> 8U*(4U-(i+1U))) &0xff;

	memcpy(PTP_RESP_Frame.SrcClockID, Master_ClockID, 8U);
	memcpy(PTP_RESP_Frame.SrcPortNum, Master_PortNum, 2U);
	PTP_RESP_Frame.ControlField = 0x03;
	PTP_RESP_Frame.LogMsgInterval = 0xF9;


	/*=====================================================================*/
	// Set PTP Fallow Header
	/*=====================================================================*/
	/*=====================================================================*/
	// Set PTP Fallow Header
	/*=====================================================================*/
	/*=====================================================================*/
	// Set PTP Fallow Header
	/*=====================================================================*/

	PTP_Fallow_Frame.MsgType = 0x08;
	PTP_Fallow_Frame.trans_Spec = 0x0;
	PTP_Fallow_Frame.versionPTP = IEEE1588v2;
	PTP_Fallow_Frame.Reserved_a = 0x0;

	for(i=0U;i<2U;i++) PTP_Fallow_Frame.MsgLength[i] = (0x002c >> 8U*(2U-(i+1U))) &0xff;

	PTP_Fallow_Frame.DomainNumber = 0x0;
	PTP_Fallow_Frame.Reserved_b = 0x0;

	for(i=0U;i<8U;i++) PTP_Fallow_Frame.correctField[i] = (0x00 >> 8U*(8U-(i+1U))) &0xff;
	for(i=0U;i<4U;i++) PTP_Fallow_Frame.Reserved_c[i] = (0x00 >> 8U*(4U-(i+1U))) &0xff;

	memcpy(PTP_Fallow_Frame.SrcClockID, Master_ClockID, 8U);
	memcpy(PTP_Fallow_Frame.SrcPortNum, Master_PortNum, 2U);
	PTP_Fallow_Frame.ControlField = 0x0;
	PTP_Fallow_Frame.LogMsgInterval = 0xF9;

}

void sendSynchronization() {
    //printf("Sending synchronization message...\n");
    // Code to send sync message
    GMAC_Type *Base;
	Base = Gmac_apxBases[0];
	uint8 temp_uint8;
	uint8 i;


	/*=====================================================================*/
	// Set PayloadBuffer
	/*=====================================================================*/
	Eth_ProvideTxBuffer(EthConf_EthCtrlConfig_EthCtrlConfig_0, 0U, &BufferIndex, &PayloadBuffer, 64U);

	/*=====================================================================*/
	// Set PTP Header
	/*=====================================================================*/
	TimeStampSYNC.seconds = Base->MAC_SYSTEM_TIME_SECONDS;
	TimeStampSYNC.nanoseconds = Base->MAC_SYSTEM_TIME_NANOSECONDS;
	for(i=0U;i<6U;i++) PTP_SYNC_Frame.orgTimeStamp_sec[i] = (TimeStampSYNC.seconds >> 8U*(6U-(i+1U))) &0xff;
	for(i=0U;i<4U;i++) PTP_SYNC_Frame.orgTimeStamp_nano[i] = (TimeStampSYNC.nanoseconds >> 8U*(4U-(i+1U))) &0xff;

	Eth_Local_Memcpy(PayloadBuffer, (uint8*) &PTP_SYNC_Frame, 44U);

	/*=====================================================================*/
	// PTP Header
	/*=====================================================================*/
	//Gmac_Ip_SetTxOuterVlanTagForInsertion(EthConf_EthCtrlConfig_EthCtrlConfig_0, BufferIndex_SYNC, GMAC_VLAN_TYPE_C_VLAN, 0x6802U);
	//Gmac_Ip_SetTxOuterVlanTagForInsertion(EthConf_EthCtrlConfig_EthCtrlConfig_0, BufferIndex_SYNC, GMAC_VLAN_TYPE_C_VLAN, 0x5006U);
	//Gmac_Ip_SetTxInnerVlanTag(EthConf_EthCtrlConfig_EthCtrlConfig_0, GMAC_VLAN_TYPE_C_VLAN, 0x6802U);
	PTP_Lock = 1;


	Gmac_Ip_SetTxOuterVlanTagForInsertion(EthConf_EthCtrlConfig_EthCtrlConfig_0,
	                                                         0U,
															 GMAC_VLAN_TYPE_C_VLAN,
															 0x5800U);


	Eth_Transmit(EthConf_EthCtrlConfig_EthCtrlConfig_0, BufferIndex, (Eth_FrameType)0x88f7U, TRUE, 64U, Gmac_0_MacAddr);

    Eth_TxConfirmation(EthConf_EthCtrlConfig_EthCtrlConfig_0);

    PTP_Lock = 0;
}

void sendFollowUp() {
    //printf("Sending follow up message...\n");
    // Code to send follow up message

}

void sendDealyReq() {
    //printf("Sending announcement message...\n");
    // Code to announce presence

	/*=====================================================================*/
	// Set PayloadBuffer
	/*=====================================================================*/
    TxBuffer.Length = 60U;
    if ((GMAC_STATUS_SUCCESS != Gmac_Ip_GetTxBuff(INST_GMAC_0, 0U, &TxBuffer, NULL_PTR)) )
    {
        Result = FALSE;
    }
    TxBuffer.Length = 60U;
	/*=====================================================================*/
	// Set PTP Header
	/*=====================================================================*/

	/*=====================================================================*/
	// PTP Header
	/*=====================================================================*/

	/*=====================================================================*/
	// PTP Body
	/*=====================================================================*/

    /* Insert ethernet header (DST + SRC + TYPE) into the buffer */
    Eth_Local_Memcpy(&TxBuffer.Data[ETH_FRAME_MACDST_OFFSET], PTP_Des_MAC, ETH_FRAME_MACDST_LENGTH);

    //Gmac_Ip_GetMacAddr(0, PhysSrcAddr);
    Eth_Local_Memcpy(&TxBuffer.Data[ETH_FRAME_MACSRC_OFFSET], PTP_Src_MAC, ETH_FRAME_MACSRC_LENGTH);

    ChFrameType = 0xf788;
    Eth_Local_Memcpy(&TxBuffer.Data[ETH_FRAME_ETHTYPE_OFFSET], (uint8*) &ChFrameType, ETH_FRAME_ETHTYPE_LENGTH);

    Eth_Local_Memcpy(&TxBuffer.Data[ETH_FRAME_PAYLOAD_OFFSET], (uint8*) &PTP_REQ_Frame, 44U);


	/*=====================================================================*/
	// PTP Send
	/*=====================================================================*/
    if (GMAC_STATUS_SUCCESS != Gmac_Ip_SendFrame(INST_GMAC_0, 0U, &TxBuffer, &TxOptions))
    {
        Result = FALSE;
    }

    /* Wait for the frame to be transmitted */
    do {
        Status = Gmac_Ip_GetTransmitStatus(INST_GMAC_0, 0U, &TxBuffer, &TxInfo);
    } while (Status == GMAC_STATUS_BUSY);

    /* Check the frame status */
    if ((GMAC_STATUS_SUCCESS != Status) || (0U != TxInfo.ErrMask))
    {
        Result = FALSE;
    }

	//if(no_update_zone == 0)
	{
		Time_T3.seconds = TxInfo.Timestamp.seconds;
		Time_T3.nanoseconds = TxInfo.Timestamp.nanoseconds;
	}
}

void sendDelayResp() {
    //printf("Handling delay requests...\n");
    // Code to handle and respond to delay requests
    GMAC_Type *Base;
	Base = Gmac_apxBases[0];
	uint8 temp_uint8[2];
	uint8 i;
	uint64 PTP_Total_time;


	/*=====================================================================*/
	// Set PayloadBuffer
	/*=====================================================================*/
    TxBuffer.Length = 68U;
    if ((GMAC_STATUS_SUCCESS != Gmac_Ip_GetTxBuff(INST_GMAC_0, 0U, &TxBuffer, NULL_PTR)))
    {
        Result = FALSE;
    }
    TxBuffer.Length = 68U;
	/*=====================================================================*/
	// Set PTP Header
	/*=====================================================================*/
	//for(i=0U;i<2U;i++) PTP_RESP_Frame.SequenceID[i] = ((Master_Resp_Sequence++) >> 8U*(2U-(i+1U))) &0xff;

/*	Total_time(&PTP_Total_time,Base->MAC_SYSTEM_TIME_SECONDS,Base->MAC_SYSTEM_TIME_NANOSECONDS);
	TimeStampRESP.seconds = (uint32)((PTP_Total_time)/((uint64)1000000000));
	TimeStampRESP.nanoseconds = (uint32)((PTP_Total_time)%((uint64)1000000000));*/

	/*=====================================================================*/
	// PTP Header
	/*=====================================================================*/

    Eth_Local_Memcpy(&TxBuffer.Data[ETH_FRAME_MACDST_OFFSET], PTP_Des_MAC, ETH_FRAME_MACDST_LENGTH);

    Eth_Local_Memcpy(&TxBuffer.Data[ETH_FRAME_MACSRC_OFFSET], PTP_Src_MAC, ETH_FRAME_MACSRC_LENGTH);

    ChFrameType = 0xf788;
    Eth_Local_Memcpy(&TxBuffer.Data[ETH_FRAME_ETHTYPE_OFFSET], (uint8*) &ChFrameType, ETH_FRAME_ETHTYPE_LENGTH);

	TimeStampRESP.seconds = Base->MAC_SYSTEM_TIME_SECONDS;
	TimeStampRESP.nanoseconds = Base->MAC_SYSTEM_TIME_NANOSECONDS;

	for(i=0U;i<6U;i++) PTP_RESP_Frame.orgTimeStamp_sec[i] = (TimeStampRESP.seconds >> 8U*(6U-(i+1U))) &0xff;
	for(i=0U;i<4U;i++) PTP_RESP_Frame.orgTimeStamp_nano[i] = (TimeStampRESP.nanoseconds >> 8U*(4U-(i+1U))) &0xff;

    Eth_Local_Memcpy(&TxBuffer.Data[ETH_FRAME_PAYLOAD_OFFSET], (uint8*) &PTP_RESP_Frame, 56U);

	/*=====================================================================*/
	// PTP Header
	/*=====================================================================*/

	//Eth_TimeStampType TimeTx1, TimeTx2;
	PTP_Lock = 1;
    if (GMAC_STATUS_SUCCESS != Gmac_Ip_SendFrame(INST_GMAC_0, 0U, &TxBuffer, &TxOptions))
    {
        Result = FALSE;
    }

    /* Wait for the frame to be transmitted */
    do {
        Status = Gmac_Ip_GetTransmitStatus(INST_GMAC_0, 0U, &TxBuffer, &TxInfo);
    } while (Status == GMAC_STATUS_BUSY);

    /* Check the frame status */
    if ((GMAC_STATUS_SUCCESS != Status) || (0U != TxInfo.ErrMask))
    {
        Result = FALSE;
    }

    PTP_Lock = 0;
}


void Total_time(sint64 * total_time ,uint32 sec, uint32 nano_sec)
{
	*total_time = (((sint64)(sec) * 1000000000) + (sint64)nano_sec);
}


/***********************************
   PPS Versioin
 ***********************************/
void Print_IO()
{
    GMAC_Type *Base;
	Base = Gmac_apxBases[0];
	uint32 bt,bt2;
	bt = (uint32)(Base->MAC_SYSTEM_TIME_NANOSECONDS);
	bt2 = bt;
	bt = bt % 100000000;
	if((bt > 750+500 -250 +125)&&(bt < 850+500 -250 +125))
	//if((bt > 750 )&&(bt < 850 ))
	//if((bt < 1000 ))
	{
		//sig_toggle ^= 0xff;
		sig_toggle = ((bt2 / 100000000))%2;
		Siul2_Dio_Ip_WritePin(PTA, 07U, sig_toggle);
	}
}

void PTP_Update_func()
{
	GMAC_Type *Base;
	Base = Gmac_apxBases[0];

	Print_IO();
	/***********************************
	   Time Update
	 ***********************************/
	if((PTP_Update == 1))
	{
		// locking mechanism
		no_update_zone = 1;

		// Get T1
		Time_T1.seconds = 0;
		Time_T1.nanoseconds = 0;
		for(i=0U;i<6U;i++){
			Time_T1.seconds += ((utemp_sec_T1[5U-i]))<<(4*2*i);
		}
		for(i=0U;i<4U;i++){
			Time_T1.nanoseconds += ((utemp_nsec_T1[3U-i]))<<(4*2*i);
		}
		Print_IO();
		// Get T4
		Time_T4.seconds = 0;
		Time_T4.nanoseconds = 0;
		for(i=0U;i<6U;i++){
			Time_T4.seconds += ((utemp_sec_T4[5U-i]))<<(4*2*i);
		}
		for(i=0U;i<4U;i++){
			Time_T4.nanoseconds += ((utemp_nsec_T4[3U-i]))<<(4*2*i);
		}
		Print_IO();
		// Integrate Time


		Total_time(&PTP_T1, Time_T1.seconds, Time_T1.nanoseconds);
		Total_time(&PTP_T2, Time_T2.seconds, Time_T2.nanoseconds);
		Total_time(&PTP_T3, Time_T3.seconds, Time_T3.nanoseconds);
		Total_time(&PTP_T4, Time_T4.seconds, Time_T4.nanoseconds);



		// manual_offset
		manual_offset = 0;// -260000;//; + 140000;//-245000;
		Print_IO();

		// Calculate PTP Offset
		PTP_Offset = (sint64)((sint64)(PTP_T2-PTP_T1)/2) - ((sint64)(PTP_T4-PTP_T3)/2) + manual_offset;

/*
		PTP_sec_Offset = ((sint32)(Time_T2.seconds-Time_T1.seconds)/2)
						- ((sint32)(Time_T4.seconds-Time_T3.seconds)/2);

		PTP_nsec_Offset = ((sint32)(Time_T2.nanoseconds-Time_T1.nanoseconds)/2)
						- ((sint32)(Time_T4.nanoseconds-Time_T3.nanoseconds)/2);
*/


		// Absolute value of PTP Offset

		PTP_Offset_abs = (PTP_Offset > 0) ? PTP_Offset : (PTP_Offset * (sint64)(-1));


		no_update_zone = 0;

		PTP_Offset2 = PTP_Offset;
		PTP_sign = (PTP_Offset > 0) ? 1U:0U; // 0:add 1:sub
		PTP_new_sec = (uint32)((PTP_Offset_abs)/((uint64)1000000000));
		PTP_new_nsec = (uint32)((PTP_Offset_abs)%((uint64)1000000000));
		Print_IO();
		Gmac_status = Gmac_Ip_SetSysTimeCorr(0, PTP_sign, PTP_new_sec, PTP_new_nsec);

		if( (ii < 1000) )
		{
/*			Offset_array1[ii] = PTP_T1;
			Offset_array2[ii] = PTP_T2;
			Offset_array3[ii] = PTP_T3;
			Offset_array4[ii] = PTP_T4;*/
			Offset_array5[ii] = PTP_Offset;
		}

/***********************************
Set PPS base Time
***********************************/
		if((ii % 500 == 0) || (ii == 10)){
			Gmac_Ip_GetSysTime(0, &Time_Temp1);
			Base->MAC_PPS0_TARGET_TIME_SECONDS = Time_Temp1.seconds + 1;
			Base->MAC_PPS0_TARGET_TIME_NANOSECONDS = 0;
		}

		PTP_T1_old = PTP_T1;
		PTP_T2_old = PTP_T2;

		PTP_Offset = 0;
		PTP_Update = 0;

		ii++;

	}


}

void Eth_Local_Memcpy(uint8 *Dst, const uint8 *Src, uint32 BytesNum)
{
    uint32 TempVar = BytesNum;

    /* Start copy data*/
    while (TempVar > 0U)
    {
        TempVar--;
        Dst[TempVar] = Src[TempVar];
    }
}

void start_PTP()
{
    GMAC_Type *Base;
    Base = Gmac_apxBases[0];
#if PTP_UPDT_MODE == 2
#if PTP_Master == 1
    Base->MAC_PTO_CONTROL |= (GMAC_MAC_PTO_CONTROL_ASYNCTRIG_MASK | GMAC_MAC_PTO_CONTROL_ASYNCEN_MASK);
#endif
#endif

	//xTaskCreate( GetTimeTask   , ( const char * const ) "GetTimeTask", 0x200, (void*)0, 3, NULL );
	//xTaskCreate( PrintIOTask , ( const char * const ) "PrintIOTask", 0x300, (void*)0, 3, NULL );
	//xTaskCreate( UpdateTask, ( const char * const ) "UpdateTask" , 0x300, (void*)0, 3, NULL );
	xTaskCreate( PTP_SyncTask, ( const char * const ) "PTP_SyncTask" , 0x300, (void*)0,4, NULL );
}

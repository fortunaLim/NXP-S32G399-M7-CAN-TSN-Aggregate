/*
 * MCAL_lib_SKKU.c
 *
 *  Created on: 2024. 8. 6.
 *      Author: sh970
 */

#include "MCAL_lib_SKKU.h"

/**************************************************************************/
// Ethernet
/**************************************************************************/
Gmac_Ip_BufferType TxBuffer_MCAL = {0};
Gmac_Ip_BufferType RxBuffer_MCAL = {0};
Gmac_Ip_TxInfoType TxInfo_MCAL;
Gmac_Ip_RxInfoType RxInfo_MCAL;
Gmac_Ip_StatusType Status_MCAL;
Gmac_Ip_TxOptionsType TxOptions_MCAL = {TRUE, FALSE, FALSE};
uint8 Result_MCAL;

extern GMAC_Type * const Gmac_apxBases[FEATURE_GMAC_NUM_INSTANCES];
extern Gmac_Ip_StateType *Gmac_apxState[FEATURE_GMAC_NUM_INSTANCES];
extern Gmac_Ip_BufferDescriptorType *TxCurrentDesc[FEATURE_GMAC_NUM_CHANNELS]; /*!< The current available transmit buffer descriptor pointer array. */
extern Gmac_Ip_ChannelType * const Gmac_apxChBases[FEATURE_GMAC_NUM_INSTANCES][FEATURE_GMAC_NUM_CHANNELS];

void Eth_Trans_SKKU(uint8 Des_MAC[6], uint8 Src_MAC[6], uint8 Type[4], uint8 *Payload, uint8 Payload_Size)
{

    GMAC_Type *Base;
	Base = Gmac_apxBases[0];
	uint8 temp_uint8[2];
	uint8 i;


	/*=====================================================================*/
	// Set PayloadBuffer
	/*=====================================================================*/
    TxBuffer_MCAL.Length = 60U;
    if ((GMAC_STATUS_SUCCESS != Gmac_Ip_GetTxBuff(INST_GMAC_0, 0U, &TxBuffer_MCAL, NULL_PTR)))
    {
        Result_MCAL = FALSE;
    }
    TxBuffer_MCAL.Length = 60U;

	/*=====================================================================*/
	// PTP Header
	/*=====================================================================*/

    /* Insert ethernet header (DST + SRC + TYPE) into the buffer */
    Eth_Local_Memcpy(&TxBuffer_MCAL.Data[ETH_FRAME_MACDST_OFFSET], Des_MAC, ETH_FRAME_MACDST_LENGTH);

    Eth_Local_Memcpy(&TxBuffer_MCAL.Data[ETH_FRAME_MACSRC_OFFSET], Src_MAC, ETH_FRAME_MACSRC_LENGTH);

    Eth_Local_Memcpy(&TxBuffer_MCAL.Data[ETH_FRAME_ETHTYPE_OFFSET], Type, ETH_FRAME_ETHTYPE_LENGTH);

    Eth_Local_Memcpy(&TxBuffer_MCAL.Data[ETH_FRAME_PAYLOAD_OFFSET], (uint8*) &Payload, Payload_Size);

    if (GMAC_STATUS_SUCCESS != Gmac_Ip_SendFrame(INST_GMAC_0, 0U, &TxBuffer_MCAL, &TxOptions_MCAL))
    {
        Result_MCAL = FALSE;
    }

    /* Wait for the frame to be transmitted */
    do {
        Status_MCAL = Gmac_Ip_GetTransmitStatus(INST_GMAC_0, 0U, &TxBuffer_MCAL, &TxInfo_MCAL);
    } while (Status_MCAL == GMAC_STATUS_BUSY);

    /* Check the frame status */
    if ((GMAC_STATUS_SUCCESS != Status_MCAL) || (0U != TxInfo_MCAL.ErrMask))
    {
        Result_MCAL = FALSE;
    }

}

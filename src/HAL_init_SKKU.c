#include "HAL_init_SKKU.h"
#include "GMAC_PTP_SKKU.h"

void Gmac_Ip_InitSysTime_skku(uint8 Instance,
                         const Gmac_Ip_SysTimeConfigType * SysTimeConfig)
{
    GMAC_Type *Base;

    //volatile uint8 inter;
    //GMAC_DEV_ASSERT(Instance <  FEATURE_GMAC_NUM_INSTANCES);
    //GMAC_DEV_ASSERT(SysTimeConfig != NULL_PTR);
    //GMAC_DEV_ASSERT(SysTimeConfig->InitialTimestamp != NULL_PTR);

    Base = Gmac_apxBases[Instance];

    // timestamp interrupt enable
    //Base->MAC_INTERRUPT_ENABLE |= GMAC_MAC_INTERRUPT_ENABLE_TSIE_MASK;

    /* Set sub-second and sub-nanosecond increments. */
    Base->MAC_SUB_SECOND_INCREMENT = GMAC_MAC_SUB_SECOND_INCREMENT_SSINC(20) |
                                     GMAC_MAC_SUB_SECOND_INCREMENT_SNSINC(0);


    //Page 50
    Base->MAC_PACKET_FILTER |= GMAC_MAC_PACKET_FILTER_RA_MASK;

    /* Enable digital rollover, enable Timestamping for all packets, enable Timestamp. */
    //Page 400
    Base->MAC_TIMESTAMP_CONTROL = (
    							  GMAC_MAC_TIMESTAMP_CONTROL_TSENA_MASK |
    							  GMAC_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK |
								  GMAC_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK |
								  GMAC_MAC_TIMESTAMP_CONTROL_TSVER2ENA_MASK |

#if PTP_UPDT_MODE == 2
#if PTP_Master == 1
								  GMAC_MAC_TIMESTAMP_CONTROL_TSMSTRENA_MASK | // use if master
#endif
								  GMAC_MAC_TIMESTAMP_CONTROL_TSEVNTENA_MASK |
								  GMAC_MAC_TIMESTAMP_CONTROL_TSENALL_MASK |
#endif

								  GMAC_MAC_TIMESTAMP_CONTROL_TSENA_MASK
								  );

    //Page 810, 815
#if PTP_UPDT_MODE == 2
    Base->MAC_TIMESTAMP_CONTROL &= (~GMAC_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_MASK);
    Base->MAC_PTO_CONTROL =
    			 GMAC_MAC_PTO_CONTROL_PTOEN_MASK;
    Base->MAC_LOG_MESSAGE_INTERVAL = 0xfa;// fd=8 / fc=16 / fb=32 / fa=64 / f9=128
#endif


//asdf
    Base->MAC_PPS0_TARGET_TIME_SECONDS = 5;
    Base->MAC_PPS0_TARGET_TIME_NANOSECONDS = 0;

    /* Set initial value for system time. */
    Base->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS = SysTimeConfig->InitialTimestamp->secondsHi;
    Base->MAC_SYSTEM_TIME_SECONDS_UPDATE = SysTimeConfig->InitialTimestamp->seconds;
    Base->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = (SysTimeConfig->InitialTimestamp->nanoseconds) &
                                               GMAC_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK;
    /* Initialize the Timestamp. */
    Base->MAC_TIMESTAMP_CONTROL |= GMAC_MAC_TIMESTAMP_CONTROL_TSINIT_MASK;
}

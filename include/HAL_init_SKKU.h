
#ifndef HAL_init_SKKU_H
#define HAL_init_SKKU_H

#include "Gmac_Ip_Types.h"
#include "Gmac_Ip_Hw_Access.h"
#include "Gmac_Ip.h"
#include "GMAC_PTP_SKKU.h"
#include "OsIf.h"
#include "GMAC_PTP_SKKU.h"

void Gmac_Ip_InitSysTime_skku(uint8 Instance,
                         const Gmac_Ip_SysTimeConfigType * SysTimeConfig);

#endif

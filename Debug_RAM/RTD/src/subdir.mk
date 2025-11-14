################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTD/src/Clock_Ip.c \
../RTD/src/Clock_Ip_Data.c \
../RTD/src/Clock_Ip_Data1.c \
../RTD/src/Clock_Ip_Data2.c \
../RTD/src/Clock_Ip_Divider.c \
../RTD/src/Clock_Ip_DividerTrigger.c \
../RTD/src/Clock_Ip_ExtOsc.c \
../RTD/src/Clock_Ip_FracDiv.c \
../RTD/src/Clock_Ip_Frequency.c \
../RTD/src/Clock_Ip_Frequency1.c \
../RTD/src/Clock_Ip_Frequency2.c \
../RTD/src/Clock_Ip_Gate.c \
../RTD/src/Clock_Ip_IntOsc.c \
../RTD/src/Clock_Ip_Irq.c \
../RTD/src/Clock_Ip_Monitor.c \
../RTD/src/Clock_Ip_Pll.c \
../RTD/src/Clock_Ip_ProgFreqSwitch.c \
../RTD/src/Clock_Ip_Selector.c \
../RTD/src/Clock_Ip_Specific.c \
../RTD/src/Clock_Ip_Specific1.c \
../RTD/src/Clock_Ip_Specific2.c \
../RTD/src/Det.c \
../RTD/src/Det_stub.c \
../RTD/src/Eth.c \
../RTD/src/EthIf_Cbk.c \
../RTD/src/EthSwt.c \
../RTD/src/EthTrcv.c \
../RTD/src/Eth_Ipw.c \
../RTD/src/Eth_Irq.c \
../RTD/src/FlexCAN_Ip.c \
../RTD/src/FlexCAN_Ip_HwAccess.c \
../RTD/src/FlexCAN_Ip_Irq.c \
../RTD/src/Gmac_Ip.c \
../RTD/src/Gmac_Ip_Hw_Access.c \
../RTD/src/Gmac_Ip_Irq.c \
../RTD/src/IntCtrl_Ip.c \
../RTD/src/Mcu.c \
../RTD/src/Mcu_Dem_Wrapper.c \
../RTD/src/Mcu_Ipw.c \
../RTD/src/OsIf_Interrupts.c \
../RTD/src/OsIf_Timer.c \
../RTD/src/OsIf_Timer_System.c \
../RTD/src/OsIf_Timer_System_Internal_GenericTimer.c \
../RTD/src/OsIf_Timer_System_Internal_Systick.c \
../RTD/src/Power_Ip.c \
../RTD/src/Power_Ip_CortexA.c \
../RTD/src/Power_Ip_CortexM7.c \
../RTD/src/Power_Ip_MC_ME.c \
../RTD/src/Power_Ip_MC_RGM.c \
../RTD/src/Power_Ip_MC_RGM_Irq.c \
../RTD/src/Power_Ip_MSCM.c \
../RTD/src/Power_Ip_PMC.c \
../RTD/src/Power_Ip_Private.c \
../RTD/src/Ram_Ip.c \
../RTD/src/SchM_Can.c \
../RTD/src/SchM_Dio.c \
../RTD/src/SchM_Eth.c \
../RTD/src/SchM_Mcu.c \
../RTD/src/SchM_Port.c \
../RTD/src/Siul2_Dio_Ip.c \
../RTD/src/Siul2_Port_Ip.c 

OBJS += \
./RTD/src/Clock_Ip.o \
./RTD/src/Clock_Ip_Data.o \
./RTD/src/Clock_Ip_Data1.o \
./RTD/src/Clock_Ip_Data2.o \
./RTD/src/Clock_Ip_Divider.o \
./RTD/src/Clock_Ip_DividerTrigger.o \
./RTD/src/Clock_Ip_ExtOsc.o \
./RTD/src/Clock_Ip_FracDiv.o \
./RTD/src/Clock_Ip_Frequency.o \
./RTD/src/Clock_Ip_Frequency1.o \
./RTD/src/Clock_Ip_Frequency2.o \
./RTD/src/Clock_Ip_Gate.o \
./RTD/src/Clock_Ip_IntOsc.o \
./RTD/src/Clock_Ip_Irq.o \
./RTD/src/Clock_Ip_Monitor.o \
./RTD/src/Clock_Ip_Pll.o \
./RTD/src/Clock_Ip_ProgFreqSwitch.o \
./RTD/src/Clock_Ip_Selector.o \
./RTD/src/Clock_Ip_Specific.o \
./RTD/src/Clock_Ip_Specific1.o \
./RTD/src/Clock_Ip_Specific2.o \
./RTD/src/Det.o \
./RTD/src/Det_stub.o \
./RTD/src/Eth.o \
./RTD/src/EthIf_Cbk.o \
./RTD/src/EthSwt.o \
./RTD/src/EthTrcv.o \
./RTD/src/Eth_Ipw.o \
./RTD/src/Eth_Irq.o \
./RTD/src/FlexCAN_Ip.o \
./RTD/src/FlexCAN_Ip_HwAccess.o \
./RTD/src/FlexCAN_Ip_Irq.o \
./RTD/src/Gmac_Ip.o \
./RTD/src/Gmac_Ip_Hw_Access.o \
./RTD/src/Gmac_Ip_Irq.o \
./RTD/src/IntCtrl_Ip.o \
./RTD/src/Mcu.o \
./RTD/src/Mcu_Dem_Wrapper.o \
./RTD/src/Mcu_Ipw.o \
./RTD/src/OsIf_Interrupts.o \
./RTD/src/OsIf_Timer.o \
./RTD/src/OsIf_Timer_System.o \
./RTD/src/OsIf_Timer_System_Internal_GenericTimer.o \
./RTD/src/OsIf_Timer_System_Internal_Systick.o \
./RTD/src/Power_Ip.o \
./RTD/src/Power_Ip_CortexA.o \
./RTD/src/Power_Ip_CortexM7.o \
./RTD/src/Power_Ip_MC_ME.o \
./RTD/src/Power_Ip_MC_RGM.o \
./RTD/src/Power_Ip_MC_RGM_Irq.o \
./RTD/src/Power_Ip_MSCM.o \
./RTD/src/Power_Ip_PMC.o \
./RTD/src/Power_Ip_Private.o \
./RTD/src/Ram_Ip.o \
./RTD/src/SchM_Can.o \
./RTD/src/SchM_Dio.o \
./RTD/src/SchM_Eth.o \
./RTD/src/SchM_Mcu.o \
./RTD/src/SchM_Port.o \
./RTD/src/Siul2_Dio_Ip.o \
./RTD/src/Siul2_Port_Ip.o 

C_DEPS += \
./RTD/src/Clock_Ip.d \
./RTD/src/Clock_Ip_Data.d \
./RTD/src/Clock_Ip_Data1.d \
./RTD/src/Clock_Ip_Data2.d \
./RTD/src/Clock_Ip_Divider.d \
./RTD/src/Clock_Ip_DividerTrigger.d \
./RTD/src/Clock_Ip_ExtOsc.d \
./RTD/src/Clock_Ip_FracDiv.d \
./RTD/src/Clock_Ip_Frequency.d \
./RTD/src/Clock_Ip_Frequency1.d \
./RTD/src/Clock_Ip_Frequency2.d \
./RTD/src/Clock_Ip_Gate.d \
./RTD/src/Clock_Ip_IntOsc.d \
./RTD/src/Clock_Ip_Irq.d \
./RTD/src/Clock_Ip_Monitor.d \
./RTD/src/Clock_Ip_Pll.d \
./RTD/src/Clock_Ip_ProgFreqSwitch.d \
./RTD/src/Clock_Ip_Selector.d \
./RTD/src/Clock_Ip_Specific.d \
./RTD/src/Clock_Ip_Specific1.d \
./RTD/src/Clock_Ip_Specific2.d \
./RTD/src/Det.d \
./RTD/src/Det_stub.d \
./RTD/src/Eth.d \
./RTD/src/EthIf_Cbk.d \
./RTD/src/EthSwt.d \
./RTD/src/EthTrcv.d \
./RTD/src/Eth_Ipw.d \
./RTD/src/Eth_Irq.d \
./RTD/src/FlexCAN_Ip.d \
./RTD/src/FlexCAN_Ip_HwAccess.d \
./RTD/src/FlexCAN_Ip_Irq.d \
./RTD/src/Gmac_Ip.d \
./RTD/src/Gmac_Ip_Hw_Access.d \
./RTD/src/Gmac_Ip_Irq.d \
./RTD/src/IntCtrl_Ip.d \
./RTD/src/Mcu.d \
./RTD/src/Mcu_Dem_Wrapper.d \
./RTD/src/Mcu_Ipw.d \
./RTD/src/OsIf_Interrupts.d \
./RTD/src/OsIf_Timer.d \
./RTD/src/OsIf_Timer_System.d \
./RTD/src/OsIf_Timer_System_Internal_GenericTimer.d \
./RTD/src/OsIf_Timer_System_Internal_Systick.d \
./RTD/src/Power_Ip.d \
./RTD/src/Power_Ip_CortexA.d \
./RTD/src/Power_Ip_CortexM7.d \
./RTD/src/Power_Ip_MC_ME.d \
./RTD/src/Power_Ip_MC_RGM.d \
./RTD/src/Power_Ip_MC_RGM_Irq.d \
./RTD/src/Power_Ip_MSCM.d \
./RTD/src/Power_Ip_PMC.d \
./RTD/src/Power_Ip_Private.d \
./RTD/src/Ram_Ip.d \
./RTD/src/SchM_Can.d \
./RTD/src/SchM_Dio.d \
./RTD/src/SchM_Eth.d \
./RTD/src/SchM_Mcu.d \
./RTD/src/SchM_Port.d \
./RTD/src/Siul2_Dio_Ip.d \
./RTD/src/Siul2_Port_Ip.d 


# Each subdirectory must supply rules for building sources it contributes
RTD/src/%.o: ../RTD/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@RTD/src/Clock_Ip.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



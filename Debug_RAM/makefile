################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include stacks/tcpip/lwip/src/netif/ppp/polarssl/subdir.mk
-include stacks/tcpip/lwip/src/netif/ppp/subdir.mk
-include stacks/tcpip/lwip/src/netif/subdir.mk
-include stacks/tcpip/lwip/src/core/ipv6/subdir.mk
-include stacks/tcpip/lwip/src/core/ipv4/subdir.mk
-include stacks/tcpip/lwip/src/core/subdir.mk
-include stacks/tcpip/lwip/src/apps/tftp/subdir.mk
-include stacks/tcpip/lwip/src/apps/sntp/subdir.mk
-include stacks/tcpip/lwip/src/apps/snmp/subdir.mk
-include stacks/tcpip/lwip/src/apps/netbiosns/subdir.mk
-include stacks/tcpip/lwip/src/apps/mqtt/subdir.mk
-include stacks/tcpip/lwip/src/apps/mdns/subdir.mk
-include stacks/tcpip/lwip/src/apps/lwiperf/subdir.mk
-include stacks/tcpip/lwip/src/apps/http/subdir.mk
-include stacks/tcpip/lwip/src/api/subdir.mk
-include stacks/tcpip/code/ports/osif/rtd/subdir.mk
-include stacks/tcpip/code/ports/netif/gmacif/rtd/subdir.mk
-include stacks/tcpip/code/ports/OS/FreeRTOS/subdir.mk
-include stacks/tcpip/code/apps/udpecho_raw/subdir.mk
-include stacks/tcpip/code/apps/udpecho/subdir.mk
-include stacks/tcpip/code/apps/tcpecho_raw/subdir.mk
-include stacks/tcpip/code/apps/tcpecho/subdir.mk
-include stacks/tcpip/code/apps/socket_examples/subdir.mk
-include stacks/tcpip/code/apps/snmp_private_mib/subdir.mk
-include stacks/tcpip/code/apps/shell/subdir.mk
-include stacks/tcpip/code/apps/rtp/subdir.mk
-include stacks/tcpip/code/apps/netio/subdir.mk
-include stacks/tcpip/code/apps/netif_shutdown/subdir.mk
-include stacks/tcpip/code/apps/httpserver/subdir.mk
-include stacks/tcpip/code/apps/chargen/subdir.mk
-include stacks/tcpip/code/apps/ccov/subdir.mk
-include src/subdir.mk
-include generate/src/subdir.mk
-include board/subdir.mk
-include RTD/src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include FreeRTOS/Source/portable/MemMang/subdir.mk
-include FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include FreeRTOS/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
lwip_FreeRTOS_S32G399A_M7_hw_ver.siz \


# All Target
all: lwip_FreeRTOS_S32G399A_M7_hw_ver.elf secondary-outputs

# Tool invocations
lwip_FreeRTOS_S32G399A_M7_hw_ver.elf: $(OBJS) C:/Users/sh970/workspace_paper/lwip_FreeRTOS_S32G399A_M7_hw_ver/Project_Settings/Linker_Files/linker_ram_s32g3xx.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "lwip_FreeRTOS_S32G399A_M7_hw_ver.elf" "@lwip_FreeRTOS_S32G399A_M7_hw_ver.args"  $(USER_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

lwip_FreeRTOS_S32G399A_M7_hw_ver.siz: lwip_FreeRTOS_S32G399A_M7_hw_ver.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley lwip_FreeRTOS_S32G399A_M7_hw_ver.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets

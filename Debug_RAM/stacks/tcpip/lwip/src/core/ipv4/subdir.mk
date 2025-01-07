################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/core/ipv4/autoip.c \
../stacks/tcpip/lwip/src/core/ipv4/dhcp.c \
../stacks/tcpip/lwip/src/core/ipv4/etharp.c \
../stacks/tcpip/lwip/src/core/ipv4/icmp.c \
../stacks/tcpip/lwip/src/core/ipv4/igmp.c \
../stacks/tcpip/lwip/src/core/ipv4/ip4.c \
../stacks/tcpip/lwip/src/core/ipv4/ip4_addr.c \
../stacks/tcpip/lwip/src/core/ipv4/ip4_frag.c 

OBJS += \
./stacks/tcpip/lwip/src/core/ipv4/autoip.o \
./stacks/tcpip/lwip/src/core/ipv4/dhcp.o \
./stacks/tcpip/lwip/src/core/ipv4/etharp.o \
./stacks/tcpip/lwip/src/core/ipv4/icmp.o \
./stacks/tcpip/lwip/src/core/ipv4/igmp.o \
./stacks/tcpip/lwip/src/core/ipv4/ip4.o \
./stacks/tcpip/lwip/src/core/ipv4/ip4_addr.o \
./stacks/tcpip/lwip/src/core/ipv4/ip4_frag.o 

C_DEPS += \
./stacks/tcpip/lwip/src/core/ipv4/autoip.d \
./stacks/tcpip/lwip/src/core/ipv4/dhcp.d \
./stacks/tcpip/lwip/src/core/ipv4/etharp.d \
./stacks/tcpip/lwip/src/core/ipv4/icmp.d \
./stacks/tcpip/lwip/src/core/ipv4/igmp.d \
./stacks/tcpip/lwip/src/core/ipv4/ip4.d \
./stacks/tcpip/lwip/src/core/ipv4/ip4_addr.d \
./stacks/tcpip/lwip/src/core/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/core/ipv4/%.o: ../stacks/tcpip/lwip/src/core/ipv4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/core/ipv4/autoip.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



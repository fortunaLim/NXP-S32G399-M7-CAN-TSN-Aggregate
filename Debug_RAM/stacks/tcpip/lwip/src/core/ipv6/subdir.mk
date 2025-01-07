################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/core/ipv6/dhcp6.c \
../stacks/tcpip/lwip/src/core/ipv6/ethip6.c \
../stacks/tcpip/lwip/src/core/ipv6/icmp6.c \
../stacks/tcpip/lwip/src/core/ipv6/inet6.c \
../stacks/tcpip/lwip/src/core/ipv6/ip6.c \
../stacks/tcpip/lwip/src/core/ipv6/ip6_addr.c \
../stacks/tcpip/lwip/src/core/ipv6/ip6_frag.c \
../stacks/tcpip/lwip/src/core/ipv6/mld6.c \
../stacks/tcpip/lwip/src/core/ipv6/nd6.c 

OBJS += \
./stacks/tcpip/lwip/src/core/ipv6/dhcp6.o \
./stacks/tcpip/lwip/src/core/ipv6/ethip6.o \
./stacks/tcpip/lwip/src/core/ipv6/icmp6.o \
./stacks/tcpip/lwip/src/core/ipv6/inet6.o \
./stacks/tcpip/lwip/src/core/ipv6/ip6.o \
./stacks/tcpip/lwip/src/core/ipv6/ip6_addr.o \
./stacks/tcpip/lwip/src/core/ipv6/ip6_frag.o \
./stacks/tcpip/lwip/src/core/ipv6/mld6.o \
./stacks/tcpip/lwip/src/core/ipv6/nd6.o 

C_DEPS += \
./stacks/tcpip/lwip/src/core/ipv6/dhcp6.d \
./stacks/tcpip/lwip/src/core/ipv6/ethip6.d \
./stacks/tcpip/lwip/src/core/ipv6/icmp6.d \
./stacks/tcpip/lwip/src/core/ipv6/inet6.d \
./stacks/tcpip/lwip/src/core/ipv6/ip6.d \
./stacks/tcpip/lwip/src/core/ipv6/ip6_addr.d \
./stacks/tcpip/lwip/src/core/ipv6/ip6_frag.d \
./stacks/tcpip/lwip/src/core/ipv6/mld6.d \
./stacks/tcpip/lwip/src/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/core/ipv6/%.o: ../stacks/tcpip/lwip/src/core/ipv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/core/ipv6/dhcp6.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



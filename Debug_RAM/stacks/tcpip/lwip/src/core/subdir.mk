################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/core/altcp.c \
../stacks/tcpip/lwip/src/core/altcp_alloc.c \
../stacks/tcpip/lwip/src/core/altcp_tcp.c \
../stacks/tcpip/lwip/src/core/def.c \
../stacks/tcpip/lwip/src/core/dns.c \
../stacks/tcpip/lwip/src/core/inet_chksum.c \
../stacks/tcpip/lwip/src/core/init.c \
../stacks/tcpip/lwip/src/core/ip.c \
../stacks/tcpip/lwip/src/core/mem.c \
../stacks/tcpip/lwip/src/core/memp.c \
../stacks/tcpip/lwip/src/core/netif.c \
../stacks/tcpip/lwip/src/core/pbuf.c \
../stacks/tcpip/lwip/src/core/raw.c \
../stacks/tcpip/lwip/src/core/stats.c \
../stacks/tcpip/lwip/src/core/sys.c \
../stacks/tcpip/lwip/src/core/tcp.c \
../stacks/tcpip/lwip/src/core/tcp_in.c \
../stacks/tcpip/lwip/src/core/tcp_out.c \
../stacks/tcpip/lwip/src/core/timeouts.c \
../stacks/tcpip/lwip/src/core/udp.c 

OBJS += \
./stacks/tcpip/lwip/src/core/altcp.o \
./stacks/tcpip/lwip/src/core/altcp_alloc.o \
./stacks/tcpip/lwip/src/core/altcp_tcp.o \
./stacks/tcpip/lwip/src/core/def.o \
./stacks/tcpip/lwip/src/core/dns.o \
./stacks/tcpip/lwip/src/core/inet_chksum.o \
./stacks/tcpip/lwip/src/core/init.o \
./stacks/tcpip/lwip/src/core/ip.o \
./stacks/tcpip/lwip/src/core/mem.o \
./stacks/tcpip/lwip/src/core/memp.o \
./stacks/tcpip/lwip/src/core/netif.o \
./stacks/tcpip/lwip/src/core/pbuf.o \
./stacks/tcpip/lwip/src/core/raw.o \
./stacks/tcpip/lwip/src/core/stats.o \
./stacks/tcpip/lwip/src/core/sys.o \
./stacks/tcpip/lwip/src/core/tcp.o \
./stacks/tcpip/lwip/src/core/tcp_in.o \
./stacks/tcpip/lwip/src/core/tcp_out.o \
./stacks/tcpip/lwip/src/core/timeouts.o \
./stacks/tcpip/lwip/src/core/udp.o 

C_DEPS += \
./stacks/tcpip/lwip/src/core/altcp.d \
./stacks/tcpip/lwip/src/core/altcp_alloc.d \
./stacks/tcpip/lwip/src/core/altcp_tcp.d \
./stacks/tcpip/lwip/src/core/def.d \
./stacks/tcpip/lwip/src/core/dns.d \
./stacks/tcpip/lwip/src/core/inet_chksum.d \
./stacks/tcpip/lwip/src/core/init.d \
./stacks/tcpip/lwip/src/core/ip.d \
./stacks/tcpip/lwip/src/core/mem.d \
./stacks/tcpip/lwip/src/core/memp.d \
./stacks/tcpip/lwip/src/core/netif.d \
./stacks/tcpip/lwip/src/core/pbuf.d \
./stacks/tcpip/lwip/src/core/raw.d \
./stacks/tcpip/lwip/src/core/stats.d \
./stacks/tcpip/lwip/src/core/sys.d \
./stacks/tcpip/lwip/src/core/tcp.d \
./stacks/tcpip/lwip/src/core/tcp_in.d \
./stacks/tcpip/lwip/src/core/tcp_out.d \
./stacks/tcpip/lwip/src/core/timeouts.d \
./stacks/tcpip/lwip/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/core/%.o: ../stacks/tcpip/lwip/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/core/altcp.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



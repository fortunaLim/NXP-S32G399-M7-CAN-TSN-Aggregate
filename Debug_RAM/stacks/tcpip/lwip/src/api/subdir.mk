################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/api/api_lib.c \
../stacks/tcpip/lwip/src/api/api_msg.c \
../stacks/tcpip/lwip/src/api/err.c \
../stacks/tcpip/lwip/src/api/if_api.c \
../stacks/tcpip/lwip/src/api/netbuf.c \
../stacks/tcpip/lwip/src/api/netdb.c \
../stacks/tcpip/lwip/src/api/netifapi.c \
../stacks/tcpip/lwip/src/api/sockets.c \
../stacks/tcpip/lwip/src/api/tcpip.c 

OBJS += \
./stacks/tcpip/lwip/src/api/api_lib.o \
./stacks/tcpip/lwip/src/api/api_msg.o \
./stacks/tcpip/lwip/src/api/err.o \
./stacks/tcpip/lwip/src/api/if_api.o \
./stacks/tcpip/lwip/src/api/netbuf.o \
./stacks/tcpip/lwip/src/api/netdb.o \
./stacks/tcpip/lwip/src/api/netifapi.o \
./stacks/tcpip/lwip/src/api/sockets.o \
./stacks/tcpip/lwip/src/api/tcpip.o 

C_DEPS += \
./stacks/tcpip/lwip/src/api/api_lib.d \
./stacks/tcpip/lwip/src/api/api_msg.d \
./stacks/tcpip/lwip/src/api/err.d \
./stacks/tcpip/lwip/src/api/if_api.d \
./stacks/tcpip/lwip/src/api/netbuf.d \
./stacks/tcpip/lwip/src/api/netdb.d \
./stacks/tcpip/lwip/src/api/netifapi.d \
./stacks/tcpip/lwip/src/api/sockets.d \
./stacks/tcpip/lwip/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/api/%.o: ../stacks/tcpip/lwip/src/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/api/api_lib.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/netif/ppp/polarssl/arc4.c \
../stacks/tcpip/lwip/src/netif/ppp/polarssl/des.c \
../stacks/tcpip/lwip/src/netif/ppp/polarssl/md4.c \
../stacks/tcpip/lwip/src/netif/ppp/polarssl/md5.c \
../stacks/tcpip/lwip/src/netif/ppp/polarssl/sha1.c 

OBJS += \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/arc4.o \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/des.o \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/md4.o \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/md5.o \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/sha1.o 

C_DEPS += \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/arc4.d \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/des.d \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/md4.d \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/md5.d \
./stacks/tcpip/lwip/src/netif/ppp/polarssl/sha1.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/netif/ppp/polarssl/%.o: ../stacks/tcpip/lwip/src/netif/ppp/polarssl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/netif/ppp/polarssl/arc4.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



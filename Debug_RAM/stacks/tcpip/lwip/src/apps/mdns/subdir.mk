################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/apps/mdns/mdns.c 

OBJS += \
./stacks/tcpip/lwip/src/apps/mdns/mdns.o 

C_DEPS += \
./stacks/tcpip/lwip/src/apps/mdns/mdns.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/apps/mdns/%.o: ../stacks/tcpip/lwip/src/apps/mdns/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/apps/mdns/mdns.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



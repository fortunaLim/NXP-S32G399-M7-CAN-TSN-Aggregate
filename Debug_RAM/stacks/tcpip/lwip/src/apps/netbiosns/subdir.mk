################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/apps/netbiosns/netbiosns.c 

OBJS += \
./stacks/tcpip/lwip/src/apps/netbiosns/netbiosns.o 

C_DEPS += \
./stacks/tcpip/lwip/src/apps/netbiosns/netbiosns.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/apps/netbiosns/%.o: ../stacks/tcpip/lwip/src/apps/netbiosns/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/apps/netbiosns/netbiosns.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



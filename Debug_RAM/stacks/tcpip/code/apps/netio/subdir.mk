################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/code/apps/netio/netio.c 

OBJS += \
./stacks/tcpip/code/apps/netio/netio.o 

C_DEPS += \
./stacks/tcpip/code/apps/netio/netio.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/code/apps/netio/%.o: ../stacks/tcpip/code/apps/netio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/code/apps/netio/netio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



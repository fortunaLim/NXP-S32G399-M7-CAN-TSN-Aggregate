################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/code/apps/tcpecho/tcpecho.c 

OBJS += \
./stacks/tcpip/code/apps/tcpecho/tcpecho.o 

C_DEPS += \
./stacks/tcpip/code/apps/tcpecho/tcpecho.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/code/apps/tcpecho/%.o: ../stacks/tcpip/code/apps/tcpecho/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/code/apps/tcpecho/tcpecho.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



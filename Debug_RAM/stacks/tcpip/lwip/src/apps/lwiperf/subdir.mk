################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/apps/lwiperf/lwiperf.c 

OBJS += \
./stacks/tcpip/lwip/src/apps/lwiperf/lwiperf.o 

C_DEPS += \
./stacks/tcpip/lwip/src/apps/lwiperf/lwiperf.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/apps/lwiperf/%.o: ../stacks/tcpip/lwip/src/apps/lwiperf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/apps/lwiperf/lwiperf.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/code/ports/osif/rtd/OsIf_rtd_port.c 

OBJS += \
./stacks/tcpip/code/ports/osif/rtd/OsIf_rtd_port.o 

C_DEPS += \
./stacks/tcpip/code/ports/osif/rtd/OsIf_rtd_port.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/code/ports/osif/rtd/%.o: ../stacks/tcpip/code/ports/osif/rtd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/code/ports/osif/rtd/OsIf_rtd_port.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



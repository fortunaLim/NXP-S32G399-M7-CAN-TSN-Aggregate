################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stacks/tcpip/lwip/src/apps/http/fs.c \
../stacks/tcpip/lwip/src/apps/http/httpd.c 

OBJS += \
./stacks/tcpip/lwip/src/apps/http/fs.o \
./stacks/tcpip/lwip/src/apps/http/httpd.o 

C_DEPS += \
./stacks/tcpip/lwip/src/apps/http/fs.d \
./stacks/tcpip/lwip/src/apps/http/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
stacks/tcpip/lwip/src/apps/http/%.o: ../stacks/tcpip/lwip/src/apps/http/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@stacks/tcpip/lwip/src/apps/http/fs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



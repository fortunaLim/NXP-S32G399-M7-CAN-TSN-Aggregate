################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ETH_SKKU.c \
../src/FlexCAN_SKKU.c \
../src/device.c \
../src/main.c 

OBJS += \
./src/ETH_SKKU.o \
./src/FlexCAN_SKKU.o \
./src/device.o \
./src/main.o 

C_DEPS += \
./src/ETH_SKKU.d \
./src/FlexCAN_SKKU.d \
./src/device.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/ETH_SKKU.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



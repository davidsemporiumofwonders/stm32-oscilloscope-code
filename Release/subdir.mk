################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../startup.c 

OBJS += \
./main.o \
./startup.o 

C_DEPS += \
./main.d \
./startup.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -march=armv7-m -mthumb -mlittle-endian -O0 -ffunction-sections -fdata-sections -fno-common -fno-inline-functions -ffreestanding -fno-builtin -flto -Wall -Wfloat-equal -DSTM32F10X_MD -I"C:\Users\david\toolchainsandlibraries\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\CoreSupport" -I"C:\Users\david\toolchainsandlibraries\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x" -I"C:\Users\david\toolchainsandlibraries\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\STM32F10x_StdPeriph_Driver\inc" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



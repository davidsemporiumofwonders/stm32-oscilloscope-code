################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
oscilloscope.hex \

SECONDARY_LIST += \
oscilloscope.lst \

SECONDARY_SIZE += \
oscilloscope.siz \


# All Target
all: oscilloscope.elf secondary-outputs

# Tool invocations
oscilloscope.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -march=armv7-m -mthumb -mlittle-endian -O0 -ffunction-sections -fdata-sections -fno-common -fno-inline-functions -ffreestanding -fno-builtin -flto -Wall -Wfloat-equal -T "C:\Users\david\workspacestm\oscilloscope\linkerscript.ld" -nostdlib -Xlinker --gc-sections -Xlinker --print-gc-sections -Wl,-Map,"oscilloscope.map" --specs=nano.specs -o "oscilloscope.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

oscilloscope.hex: oscilloscope.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "oscilloscope.elf"  "oscilloscope.hex"
	@echo 'Finished building: $@'
	@echo ' '

oscilloscope.lst: oscilloscope.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "oscilloscope.elf" > "oscilloscope.lst"
	@echo 'Finished building: $@'
	@echo ' '

oscilloscope.siz: oscilloscope.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "oscilloscope.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) oscilloscope.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets

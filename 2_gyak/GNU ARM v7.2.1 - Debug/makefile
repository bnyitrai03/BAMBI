################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: 2_gyak.axf

# Tool invocations
2_gyak.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "2_gyak.ld" -Xlinker --gc-sections -Xlinker -Map="2_gyak.map" --specs=nano.specs -o 2_gyak.axf "./CMSIS/EFM32GG/startup_gcc_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./emlib/em_system.o" "./src/gyak_2.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: 2_gyak.hex'
	arm-none-eabi-objcopy -O ihex "2_gyak.axf" "2_gyak.hex"
	@echo ' '

	@echo 'Building bin file: 2_gyak.bin'
	arm-none-eabi-objcopy -O binary "2_gyak.axf" "2_gyak.bin"
	@echo ' '

	@echo 'Building s37 file: 2_gyak.s37'
	arm-none-eabi-objcopy -O srec "2_gyak.axf" "2_gyak.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "2_gyak.axf" -A
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) 2_gyak.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

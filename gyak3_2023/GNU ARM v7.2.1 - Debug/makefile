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
all: gyak3_2023.axf

# Tool invocations
gyak3_2023.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "gyak3_2023.ld" -Xlinker --gc-sections -Xlinker -Map="gyak3_2023.map" --specs=nano.specs -o gyak3_2023.axf "./CMSIS/EFM32GG/startup_gcc_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./emlib/em_cmu.o" "./emlib/em_gpio.o" "./emlib/em_system.o" "./emlib/em_usart.o" "./src/UART_initGy.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: gyak3_2023.hex'
	arm-none-eabi-objcopy -O ihex "gyak3_2023.axf" "gyak3_2023.hex"
	@echo ' '

	@echo 'Building bin file: gyak3_2023.bin'
	arm-none-eabi-objcopy -O binary "gyak3_2023.axf" "gyak3_2023.bin"
	@echo ' '

	@echo 'Building s37 file: gyak3_2023.s37'
	arm-none-eabi-objcopy -O srec "gyak3_2023.axf" "gyak3_2023.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "gyak3_2023.axf" -A
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) gyak3_2023.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

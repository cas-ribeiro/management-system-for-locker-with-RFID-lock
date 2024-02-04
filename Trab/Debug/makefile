################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Trab
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Trab.axf

# Tool invocations
Trab.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\SE\CMSIS_CORE_LPC17XX\Debug" -L"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\MFRC522\Release" -L"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\DRIVERS\Debug" -L"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\HAL\Debug" -Xlinker -Map="Trab.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T Trab_Debug.ld -o "Trab.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lMFRC522 -lDRIVERS -lHAL -lCMSIS_CORE_LPC17xx
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Trab.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Trab.axf"; # arm-none-eabi-objcopy -v -O binary "Trab.axf" "Trab.bin" ; # checksum -p LPC1769 -d "Trab.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets

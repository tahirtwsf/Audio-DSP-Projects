################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/lcd/subdir.mk
-include Utilities/Fonts/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32H735G-DK/subdir.mk
-include Drivers/BSP/Components/wm8994/subdir.mk
-include Drivers/BSP/Components/s70kl1281/subdir.mk
-include Drivers/BSP/Components/mx25lm51245g/subdir.mk
-include Drivers/BSP/Components/ft5336/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := lab_spectrum_analyzer
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
lab_spectrum_analyzer.elf \

MAP_FILES += \
lab_spectrum_analyzer.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
lab_spectrum_analyzer.list \

OBJCOPY_HEX += \
lab_spectrum_analyzer.hex \


# All Target
all: main-build

# Main-build Target
main-build: lab_spectrum_analyzer.elf secondary-outputs

# Tool invocations
lab_spectrum_analyzer.elf lab_spectrum_analyzer.map: $(OBJS) $(USER_OBJS) /Users/richarddansereau/STM32CubeIDE/workspace_1.10.1/lab_spectrum_analyzer/STM32H735IGKX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "lab_spectrum_analyzer.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/Users/richarddansereau/STM32CubeIDE/workspace_1.10.1/lab_spectrum_analyzer/STM32H735IGKX_FLASH.ld" --specs=nosys.specs -Wl,-Map="lab_spectrum_analyzer.map" -Wl,--gc-sections -static -L"../Middlewares/ST/STM32_Audio/Addons/PDM/Lib" -L../Drivers/CMSIS/DSP/Lib/GCC --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

lab_spectrum_analyzer.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "lab_spectrum_analyzer.list"
	@echo 'Finished building: $@'
	@echo ' '

lab_spectrum_analyzer.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "lab_spectrum_analyzer.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout lab_spectrum_analyzer.elf lab_spectrum_analyzer.hex lab_spectrum_analyzer.list lab_spectrum_analyzer.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

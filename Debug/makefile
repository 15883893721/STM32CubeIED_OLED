################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32L1xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
OLED_STM32L151CCU6_SPI_IIC.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
OLED_STM32L151CCU6_SPI_IIC.list \


# All Target
all: OLED_STM32L151CCU6_SPI_IIC.elf secondary-outputs

# Tool invocations
OLED_STM32L151CCU6_SPI_IIC.elf: $(OBJS) $(USER_OBJS) D:\workdone\STM32CubeIDE_1.0.2\space3\OLED_STM32L151CCU6_SPI_IIC\STM32L151CCUX_FLASH.ld
	arm-none-eabi-gcc -o "OLED_STM32L151CCU6_SPI_IIC.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\workdone\STM32CubeIDE_1.0.2\space3\OLED_STM32L151CCU6_SPI_IIC\STM32L151CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="OLED_STM32L151CCU6_SPI_IIC.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

OLED_STM32L151CCU6_SPI_IIC.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "OLED_STM32L151CCU6_SPI_IIC.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DELAY.c \
../src/LCD.c \
../src/LED.c \
../src/RTC.c 

C_DEPS += \
./src/DELAY.d \
./src/LCD.d \
./src/LED.d \
./src/RTC.d 

OBJS += \
./src/DELAY.o \
./src/LCD.o \
./src/LED.o \
./src/RTC.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -D__REDLIB__ -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -I"C:\Users\carlo\Documents\MCUXpressoIDE_11.8.0_1165\workspace\DRIVERS\inc" -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\SE\CMSIS_CORE_LPC17XX\inc" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/DELAY.d ./src/DELAY.o ./src/LCD.d ./src/LCD.o ./src/LED.d ./src/LED.o ./src/RTC.d ./src/RTC.o

.PHONY: clean-src


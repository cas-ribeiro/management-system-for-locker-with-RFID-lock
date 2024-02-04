################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DELAY.c \
../src/DRIVERS_FLASH.c \
../src/DRIVERS_MFRC522.c \
../src/ENCODER.c \
../src/LCD.c \
../src/LED.c \
../src/RTC.c 

C_DEPS += \
./src/DELAY.d \
./src/DRIVERS_FLASH.d \
./src/DRIVERS_MFRC522.d \
./src/ENCODER.d \
./src/LCD.d \
./src/LED.d \
./src/RTC.d 

OBJS += \
./src/DELAY.o \
./src/DRIVERS_FLASH.o \
./src/DRIVERS_MFRC522.o \
./src/ENCODER.o \
./src/LCD.o \
./src/LED.o \
./src/RTC.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\HAL\inc" -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\MFRC522\inc" -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\DRIVERS\inc" -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\SE\CMSIS_CORE_LPC17XX\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/DELAY.d ./src/DELAY.o ./src/DRIVERS_FLASH.d ./src/DRIVERS_FLASH.o ./src/DRIVERS_MFRC522.d ./src/DRIVERS_MFRC522.o ./src/ENCODER.d ./src/ENCODER.o ./src/LCD.d ./src/LCD.o ./src/LED.d ./src/LED.o ./src/RTC.d ./src/RTC.o

.PHONY: clean-src


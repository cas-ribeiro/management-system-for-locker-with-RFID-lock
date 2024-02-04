################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Trab.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/modes.c \
../src/utils.c 

C_DEPS += \
./src/Trab.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/modes.d \
./src/utils.d 

OBJS += \
./src/Trab.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/modes.o \
./src/utils.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\Trab\inc" -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\DRIVERS\inc" -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\HAL\inc" -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\workspace\MFRC522\inc" -I"C:\Users\carlo\Documents\ISEL\Semestre 5\SE\SE\CMSIS_CORE_LPC17XX\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Trab.d ./src/Trab.o ./src/cr_startup_lpc175x_6x.d ./src/cr_startup_lpc175x_6x.o ./src/crp.d ./src/crp.o ./src/modes.d ./src/modes.o ./src/utils.d ./src/utils.o

.PHONY: clean-src


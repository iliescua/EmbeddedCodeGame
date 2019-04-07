################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/delay.c \
../src/keypad.c \
../src/lcd.c \
../src/led.c \
../src/main.c \
../src/rotary.c \
../src/speaker.c 

OBJS += \
./src/delay.o \
./src/keypad.o \
./src/lcd.o \
./src/led.o \
./src/main.o \
./src/rotary.o \
./src/speaker.o 

C_DEPS += \
./src/delay.d \
./src/keypad.d \
./src/lcd.d \
./src/led.d \
./src/main.d \
./src/rotary.d \
./src/speaker.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -I"C:/Users/iliescua/EM SYS 2/Lab8/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



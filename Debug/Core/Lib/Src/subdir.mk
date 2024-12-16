################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/Src/Potentiometer.c \
../Core/Lib/Src/RTC_Functions.c \
../Core/Lib/Src/button_control.c \
../Core/Lib/Src/dht11.c \
../Core/Lib/Src/esp32_dht11.c \
../Core/Lib/Src/fonts.c \
../Core/Lib/Src/lcd_menu.c \
../Core/Lib/Src/ssd1306.c \
../Core/Lib/Src/subContorl.c \
../Core/Lib/Src/timer_funs.c \
../Core/Lib/Src/timer_mode.c 

OBJS += \
./Core/Lib/Src/Potentiometer.o \
./Core/Lib/Src/RTC_Functions.o \
./Core/Lib/Src/button_control.o \
./Core/Lib/Src/dht11.o \
./Core/Lib/Src/esp32_dht11.o \
./Core/Lib/Src/fonts.o \
./Core/Lib/Src/lcd_menu.o \
./Core/Lib/Src/ssd1306.o \
./Core/Lib/Src/subContorl.o \
./Core/Lib/Src/timer_funs.o \
./Core/Lib/Src/timer_mode.o 

C_DEPS += \
./Core/Lib/Src/Potentiometer.d \
./Core/Lib/Src/RTC_Functions.d \
./Core/Lib/Src/button_control.d \
./Core/Lib/Src/dht11.d \
./Core/Lib/Src/esp32_dht11.d \
./Core/Lib/Src/fonts.d \
./Core/Lib/Src/lcd_menu.d \
./Core/Lib/Src/ssd1306.d \
./Core/Lib/Src/subContorl.d \
./Core/Lib/Src/timer_funs.d \
./Core/Lib/Src/timer_mode.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/Src/%.o Core/Lib/Src/%.su: ../Core/Lib/Src/%.c Core/Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32CubeIDE_1.9.0/Stm32_WorkSpace/OJ_CODING_EMBEDED/Part4/Timer_Clock_Stm/Core/Lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-Src

clean-Core-2f-Lib-2f-Src:
	-$(RM) ./Core/Lib/Src/Potentiometer.d ./Core/Lib/Src/Potentiometer.o ./Core/Lib/Src/Potentiometer.su ./Core/Lib/Src/RTC_Functions.d ./Core/Lib/Src/RTC_Functions.o ./Core/Lib/Src/RTC_Functions.su ./Core/Lib/Src/button_control.d ./Core/Lib/Src/button_control.o ./Core/Lib/Src/button_control.su ./Core/Lib/Src/dht11.d ./Core/Lib/Src/dht11.o ./Core/Lib/Src/dht11.su ./Core/Lib/Src/esp32_dht11.d ./Core/Lib/Src/esp32_dht11.o ./Core/Lib/Src/esp32_dht11.su ./Core/Lib/Src/fonts.d ./Core/Lib/Src/fonts.o ./Core/Lib/Src/fonts.su ./Core/Lib/Src/lcd_menu.d ./Core/Lib/Src/lcd_menu.o ./Core/Lib/Src/lcd_menu.su ./Core/Lib/Src/ssd1306.d ./Core/Lib/Src/ssd1306.o ./Core/Lib/Src/ssd1306.su ./Core/Lib/Src/subContorl.d ./Core/Lib/Src/subContorl.o ./Core/Lib/Src/subContorl.su ./Core/Lib/Src/timer_funs.d ./Core/Lib/Src/timer_funs.o ./Core/Lib/Src/timer_funs.su ./Core/Lib/Src/timer_mode.d ./Core/Lib/Src/timer_mode.o ./Core/Lib/Src/timer_mode.su

.PHONY: clean-Core-2f-Lib-2f-Src


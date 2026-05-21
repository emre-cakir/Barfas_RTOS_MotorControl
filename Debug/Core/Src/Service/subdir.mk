################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Service/emergency.c \
../Core/Src/Service/motor_driver.c \
../Core/Src/Service/network_interface.c \
../Core/Src/Service/rgb_led.c 

OBJS += \
./Core/Src/Service/emergency.o \
./Core/Src/Service/motor_driver.o \
./Core/Src/Service/network_interface.o \
./Core/Src/Service/rgb_led.o 

C_DEPS += \
./Core/Src/Service/emergency.d \
./Core/Src/Service/motor_driver.d \
./Core/Src/Service/network_interface.d \
./Core/Src/Service/rgb_led.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Service/%.o Core/Src/Service/%.su Core/Src/Service/%.cyclo: ../Core/Src/Service/%.c Core/Src/Service/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/App" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/Service" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/Wiznet" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/App" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/Service" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/Wiznet" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Service

clean-Core-2f-Src-2f-Service:
	-$(RM) ./Core/Src/Service/emergency.cyclo ./Core/Src/Service/emergency.d ./Core/Src/Service/emergency.o ./Core/Src/Service/emergency.su ./Core/Src/Service/motor_driver.cyclo ./Core/Src/Service/motor_driver.d ./Core/Src/Service/motor_driver.o ./Core/Src/Service/motor_driver.su ./Core/Src/Service/network_interface.cyclo ./Core/Src/Service/network_interface.d ./Core/Src/Service/network_interface.o ./Core/Src/Service/network_interface.su ./Core/Src/Service/rgb_led.cyclo ./Core/Src/Service/rgb_led.d ./Core/Src/Service/rgb_led.o ./Core/Src/Service/rgb_led.su

.PHONY: clean-Core-2f-Src-2f-Service


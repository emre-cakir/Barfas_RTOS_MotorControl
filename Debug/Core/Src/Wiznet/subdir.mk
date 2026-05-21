################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Wiznet/socket.c \
../Core/Src/Wiznet/user_spi_w5500.c \
../Core/Src/Wiznet/w5500.c \
../Core/Src/Wiznet/wizchip_conf.c 

OBJS += \
./Core/Src/Wiznet/socket.o \
./Core/Src/Wiznet/user_spi_w5500.o \
./Core/Src/Wiznet/w5500.o \
./Core/Src/Wiznet/wizchip_conf.o 

C_DEPS += \
./Core/Src/Wiznet/socket.d \
./Core/Src/Wiznet/user_spi_w5500.d \
./Core/Src/Wiznet/w5500.d \
./Core/Src/Wiznet/wizchip_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Wiznet/%.o Core/Src/Wiznet/%.su Core/Src/Wiznet/%.cyclo: ../Core/Src/Wiznet/%.c Core/Src/Wiznet/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/App" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/Service" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/Wiznet" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/App" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/Service" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/Wiznet" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Wiznet

clean-Core-2f-Src-2f-Wiznet:
	-$(RM) ./Core/Src/Wiznet/socket.cyclo ./Core/Src/Wiznet/socket.d ./Core/Src/Wiznet/socket.o ./Core/Src/Wiznet/socket.su ./Core/Src/Wiznet/user_spi_w5500.cyclo ./Core/Src/Wiznet/user_spi_w5500.d ./Core/Src/Wiznet/user_spi_w5500.o ./Core/Src/Wiznet/user_spi_w5500.su ./Core/Src/Wiznet/w5500.cyclo ./Core/Src/Wiznet/w5500.d ./Core/Src/Wiznet/w5500.o ./Core/Src/Wiznet/w5500.su ./Core/Src/Wiznet/wizchip_conf.cyclo ./Core/Src/Wiznet/wizchip_conf.d ./Core/Src/Wiznet/wizchip_conf.o ./Core/Src/Wiznet/wizchip_conf.su

.PHONY: clean-Core-2f-Src-2f-Wiznet


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/App/command_parser.c \
../Core/Src/App/state_machine.c \
../Core/Src/App/task_manager.c 

OBJS += \
./Core/Src/App/command_parser.o \
./Core/Src/App/state_machine.o \
./Core/Src/App/task_manager.o 

C_DEPS += \
./Core/Src/App/command_parser.d \
./Core/Src/App/state_machine.d \
./Core/Src/App/task_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/App/%.o Core/Src/App/%.su Core/Src/App/%.cyclo: ../Core/Src/App/%.c Core/Src/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/App" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/Service" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Inc/Wiznet" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/App" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/Service" -I"C:/Users/Eray/STM32CubeIDE/workspace_2.1.1/Barfas_RTOS_MotorControl/Core/Src/Wiznet" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-App

clean-Core-2f-Src-2f-App:
	-$(RM) ./Core/Src/App/command_parser.cyclo ./Core/Src/App/command_parser.d ./Core/Src/App/command_parser.o ./Core/Src/App/command_parser.su ./Core/Src/App/state_machine.cyclo ./Core/Src/App/state_machine.d ./Core/Src/App/state_machine.o ./Core/Src/App/state_machine.su ./Core/Src/App/task_manager.cyclo ./Core/Src/App/task_manager.d ./Core/Src/App/task_manager.o ./Core/Src/App/task_manager.su

.PHONY: clean-Core-2f-Src-2f-App


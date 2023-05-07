################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.c 

C_DEPS += \
./Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.d 

OBJS += \
./Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.o 


# Each subdirectory must supply rules for building sources it contributes
Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/%.o Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/%.su: ../Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/%.c Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/FTPClient_module/Middleware/FreeRTOS/Source/include" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/FTPClient_module/Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f" -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/FTPClient_module/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-gcc-2f-arm_cm4f

clean-Middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-gcc-2f-arm_cm4f:
	-$(RM) ./Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.d ./Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.o ./Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.su

.PHONY: clean-Middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-gcc-2f-arm_cm4f


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.c 

C_DEPS += \
./middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.d 

OBJS += \
./middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.o 


# Each subdirectory must supply rules for building sources it contributes
middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/%.o middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/%.su: ../middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/%.c middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/littleFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/portable/gcc/arm_cm4f" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/include" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-gcc-2f-arm_cm4f

clean-middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-gcc-2f-arm_cm4f:
	-$(RM) ./middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.d ./middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.o ./middleware/FreeRTOS/Source/portable/gcc/arm_cm4f/port.su

.PHONY: clean-middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-gcc-2f-arm_cm4f


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/FreeRTOS/Source/portable/memmang/heap_4.c 

C_DEPS += \
./middleware/FreeRTOS/Source/portable/memmang/heap_4.d 

OBJS += \
./middleware/FreeRTOS/Source/portable/memmang/heap_4.o 


# Each subdirectory must supply rules for building sources it contributes
middleware/FreeRTOS/Source/portable/memmang/%.o middleware/FreeRTOS/Source/portable/memmang/%.su: ../middleware/FreeRTOS/Source/portable/memmang/%.c middleware/FreeRTOS/Source/portable/memmang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/littleFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/portable/gcc/arm_cm4f" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/include" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-memmang

clean-middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-memmang:
	-$(RM) ./middleware/FreeRTOS/Source/portable/memmang/heap_4.d ./middleware/FreeRTOS/Source/portable/memmang/heap_4.o ./middleware/FreeRTOS/Source/portable/memmang/heap_4.su

.PHONY: clean-middleware-2f-FreeRTOS-2f-Source-2f-portable-2f-memmang


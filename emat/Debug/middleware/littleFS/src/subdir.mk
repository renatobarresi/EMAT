################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/littleFS/src/lfs.c \
../middleware/littleFS/src/lfs_util.c 

C_DEPS += \
./middleware/littleFS/src/lfs.d \
./middleware/littleFS/src/lfs_util.d 

OBJS += \
./middleware/littleFS/src/lfs.o \
./middleware/littleFS/src/lfs_util.o 


# Each subdirectory must supply rules for building sources it contributes
middleware/littleFS/src/%.o middleware/littleFS/src/%.su: ../middleware/littleFS/src/%.c middleware/littleFS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/littleFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/portable/gcc/arm_cm4f" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/include" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-middleware-2f-littleFS-2f-src

clean-middleware-2f-littleFS-2f-src:
	-$(RM) ./middleware/littleFS/src/lfs.d ./middleware/littleFS/src/lfs.o ./middleware/littleFS/src/lfs.su ./middleware/littleFS/src/lfs_util.d ./middleware/littleFS/src/lfs_util.o ./middleware/littleFS/src/lfs_util.su

.PHONY: clean-middleware-2f-littleFS-2f-src


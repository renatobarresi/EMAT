################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../modules/src/rtos_module.cpp 

OBJS += \
./modules/src/rtos_module.o 

CPP_DEPS += \
./modules/src/rtos_module.d 


# Each subdirectory must supply rules for building sources it contributes
modules/src/%.o modules/src/%.su: ../modules/src/%.cpp modules/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/FTPClient_module/Middleware/FreeRTOS/Source/include" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/FTPClient_module/Middleware/FreeRTOS/Source/portable/gcc/arm_cm4f" -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/FTPClient_module/modules/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/FTPClient_module/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-src

clean-modules-2f-src:
	-$(RM) ./modules/src/rtos_module.d ./modules/src/rtos_module.o ./modules/src/rtos_module.su

.PHONY: clean-modules-2f-src


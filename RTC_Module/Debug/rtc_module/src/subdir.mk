################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../rtc_module/src/rtc_module.cpp 

OBJS += \
./rtc_module/src/rtc_module.o 

CPP_DEPS += \
./rtc_module/src/rtc_module.d 


# Each subdirectory must supply rules for building sources it contributes
rtc_module/src/%.o rtc_module/src/%.su: ../rtc_module/src/%.cpp rtc_module/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/RTC_Module/project_cpp/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/RTC_Module/rtc_module/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-rtc_module-2f-src

clean-rtc_module-2f-src:
	-$(RM) ./rtc_module/src/rtc_module.d ./rtc_module/src/rtc_module.o ./rtc_module/src/rtc_module.su

.PHONY: clean-rtc_module-2f-src


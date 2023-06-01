################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../modules/src/SD_module.cpp \
../modules/src/W25Qx_module.cpp \
../modules/src/filesystem.cpp \
../modules/src/gpio_module.cpp \
../modules/src/hmi_module.cpp \
../modules/src/littleFSInterface.cpp \
../modules/src/rtc_module.cpp \
../modules/src/rtos_module.cpp \
../modules/src/serialPort_module.cpp \
../modules/src/spi_module.cpp 

OBJS += \
./modules/src/SD_module.o \
./modules/src/W25Qx_module.o \
./modules/src/filesystem.o \
./modules/src/gpio_module.o \
./modules/src/hmi_module.o \
./modules/src/littleFSInterface.o \
./modules/src/rtc_module.o \
./modules/src/rtos_module.o \
./modules/src/serialPort_module.o \
./modules/src/spi_module.o 

CPP_DEPS += \
./modules/src/SD_module.d \
./modules/src/W25Qx_module.d \
./modules/src/filesystem.d \
./modules/src/gpio_module.d \
./modules/src/hmi_module.d \
./modules/src/littleFSInterface.d \
./modules/src/rtc_module.d \
./modules/src/rtos_module.d \
./modules/src/serialPort_module.d \
./modules/src/spi_module.d 


# Each subdirectory must supply rules for building sources it contributes
modules/src/%.o modules/src/%.su: ../modules/src/%.cpp modules/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/littleFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/include" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/portable/gcc/arm_cm4f" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/project_cpp/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/modules/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-src

clean-modules-2f-src:
	-$(RM) ./modules/src/SD_module.d ./modules/src/SD_module.o ./modules/src/SD_module.su ./modules/src/W25Qx_module.d ./modules/src/W25Qx_module.o ./modules/src/W25Qx_module.su ./modules/src/filesystem.d ./modules/src/filesystem.o ./modules/src/filesystem.su ./modules/src/gpio_module.d ./modules/src/gpio_module.o ./modules/src/gpio_module.su ./modules/src/hmi_module.d ./modules/src/hmi_module.o ./modules/src/hmi_module.su ./modules/src/littleFSInterface.d ./modules/src/littleFSInterface.o ./modules/src/littleFSInterface.su ./modules/src/rtc_module.d ./modules/src/rtc_module.o ./modules/src/rtc_module.su ./modules/src/rtos_module.d ./modules/src/rtos_module.o ./modules/src/rtos_module.su ./modules/src/serialPort_module.d ./modules/src/serialPort_module.o ./modules/src/serialPort_module.su ./modules/src/spi_module.d ./modules/src/spi_module.o ./modules/src/spi_module.su

.PHONY: clean-modules-2f-src


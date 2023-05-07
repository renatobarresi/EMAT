################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/FatFS/src/diskio.c \
../Middleware/FatFS/src/ff.c \
../Middleware/FatFS/src/ffsystem.c \
../Middleware/FatFS/src/ffunicode.c 

CPP_SRCS += \
../Middleware/FatFS/src/W25Q64_wrapper.cpp 

C_DEPS += \
./Middleware/FatFS/src/diskio.d \
./Middleware/FatFS/src/ff.d \
./Middleware/FatFS/src/ffsystem.d \
./Middleware/FatFS/src/ffunicode.d 

OBJS += \
./Middleware/FatFS/src/W25Q64_wrapper.o \
./Middleware/FatFS/src/diskio.o \
./Middleware/FatFS/src/ff.o \
./Middleware/FatFS/src/ffsystem.o \
./Middleware/FatFS/src/ffunicode.o 

CPP_DEPS += \
./Middleware/FatFS/src/W25Q64_wrapper.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/FatFS/src/%.o Middleware/FatFS/src/%.su: ../Middleware/FatFS/src/%.cpp Middleware/FatFS/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/fatFs_module/modules/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/fatFs_module/Middleware/FatFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/fatFs_module/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middleware/FatFS/src/%.o Middleware/FatFS/src/%.su: ../Middleware/FatFS/src/%.c Middleware/FatFS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/fatFs_module/Middleware/FatFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/fatFs_module/modules/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/fatFs_module/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-FatFS-2f-src

clean-Middleware-2f-FatFS-2f-src:
	-$(RM) ./Middleware/FatFS/src/W25Q64_wrapper.d ./Middleware/FatFS/src/W25Q64_wrapper.o ./Middleware/FatFS/src/W25Q64_wrapper.su ./Middleware/FatFS/src/diskio.d ./Middleware/FatFS/src/diskio.o ./Middleware/FatFS/src/diskio.su ./Middleware/FatFS/src/ff.d ./Middleware/FatFS/src/ff.o ./Middleware/FatFS/src/ff.su ./Middleware/FatFS/src/ffsystem.d ./Middleware/FatFS/src/ffsystem.o ./Middleware/FatFS/src/ffsystem.su ./Middleware/FatFS/src/ffunicode.d ./Middleware/FatFS/src/ffunicode.o ./Middleware/FatFS/src/ffunicode.su

.PHONY: clean-Middleware-2f-FatFS-2f-src


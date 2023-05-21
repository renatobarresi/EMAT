################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/FreeRTOS/Source/croutine.c \
../middleware/FreeRTOS/Source/event_groups.c \
../middleware/FreeRTOS/Source/list.c \
../middleware/FreeRTOS/Source/queue.c \
../middleware/FreeRTOS/Source/stream_buffer.c \
../middleware/FreeRTOS/Source/tasks.c \
../middleware/FreeRTOS/Source/timers.c 

C_DEPS += \
./middleware/FreeRTOS/Source/croutine.d \
./middleware/FreeRTOS/Source/event_groups.d \
./middleware/FreeRTOS/Source/list.d \
./middleware/FreeRTOS/Source/queue.d \
./middleware/FreeRTOS/Source/stream_buffer.d \
./middleware/FreeRTOS/Source/tasks.d \
./middleware/FreeRTOS/Source/timers.d 

OBJS += \
./middleware/FreeRTOS/Source/croutine.o \
./middleware/FreeRTOS/Source/event_groups.o \
./middleware/FreeRTOS/Source/list.o \
./middleware/FreeRTOS/Source/queue.o \
./middleware/FreeRTOS/Source/stream_buffer.o \
./middleware/FreeRTOS/Source/tasks.o \
./middleware/FreeRTOS/Source/timers.o 


# Each subdirectory must supply rules for building sources it contributes
middleware/FreeRTOS/Source/%.o middleware/FreeRTOS/Source/%.su: ../middleware/FreeRTOS/Source/%.c middleware/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/littleFS/inc" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/portable/gcc/arm_cm4f" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/middleware/FreeRTOS/Source/include" -I"/home/renatobarresi/Renato/CESE_fiuba/Tesis/Code/emat/project_cpp/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-middleware-2f-FreeRTOS-2f-Source

clean-middleware-2f-FreeRTOS-2f-Source:
	-$(RM) ./middleware/FreeRTOS/Source/croutine.d ./middleware/FreeRTOS/Source/croutine.o ./middleware/FreeRTOS/Source/croutine.su ./middleware/FreeRTOS/Source/event_groups.d ./middleware/FreeRTOS/Source/event_groups.o ./middleware/FreeRTOS/Source/event_groups.su ./middleware/FreeRTOS/Source/list.d ./middleware/FreeRTOS/Source/list.o ./middleware/FreeRTOS/Source/list.su ./middleware/FreeRTOS/Source/queue.d ./middleware/FreeRTOS/Source/queue.o ./middleware/FreeRTOS/Source/queue.su ./middleware/FreeRTOS/Source/stream_buffer.d ./middleware/FreeRTOS/Source/stream_buffer.o ./middleware/FreeRTOS/Source/stream_buffer.su ./middleware/FreeRTOS/Source/tasks.d ./middleware/FreeRTOS/Source/tasks.o ./middleware/FreeRTOS/Source/tasks.su ./middleware/FreeRTOS/Source/timers.d ./middleware/FreeRTOS/Source/timers.o ./middleware/FreeRTOS/Source/timers.su

.PHONY: clean-middleware-2f-FreeRTOS-2f-Source


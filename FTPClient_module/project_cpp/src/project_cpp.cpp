/*
 * project_cpp.cpp
 *
 *  Created on: Mar 19, 2023
 *      Author: renatobarresi
 */

#include "project_cpp.h"
#include "rtos_module.h"
#include "stm32f4xx_hal.h"
#include "main.h"

void MyTaskFunction1(void *parameters) {
    // Blink LED at a 500 ms interval
    while (1) {
        HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin); // Toggle the LED
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 ms
    }
}

void MyTaskFunction2(void *parameters) {
    // Blink LED at a 1000 ms interval
    while (1) {
        HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin); // Toggle the LED
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
    }
}


void main_cpp(void)
{
	rtosTask taskOne("task1", MyTaskFunction1, configMINIMAL_STACK_SIZE, tskIDLE_PRIORITY + 1, nullptr);
	rtosTask taskTwo("task2", MyTaskFunction2, configMINIMAL_STACK_SIZE, tskIDLE_PRIORITY + 1, nullptr);

	vTaskStartScheduler();

    while(1);
}
/*
 * taskCreator.cpp
 *
 *  Created on: May 21, 2023
 *      Author: renatobarresi
 */

 /* Includes */
#include "taskCreator.h"
#include "rtos_module.h"
#include "applicationManager.h"
#include "commandManager.h"
#include "stm32f4xx_hal.h"
#include "error.h"

/* Constant expressions  */

/* Private variables */

/* Private functions */
void visualTask(void *pvParam)
{
	while (1)
	{
        HAL_GPIO_TogglePin(INDICATOR_LED_PORT, INDICATOR_LED_PIN); // Toggle the LED
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 1000 ms
	}
}

/* Tasks */

// Application Task
const char appTaskName[] = "application task";
TaskStackDepth appTaskStackDepth = configMINIMAL_STACK_SIZE;
TaskPriority appTaskStackPriority = tskIDLE_PRIORITY + 2;
TaskHandle_t appTaskHandler;

//class RTOSTask appTask(appTaskName, applicationManager, appTaskStackDepth, appTaskStackPriority, NULL);

// Command Manager Task
const char CMDTaskName[] = "command task";
TaskStackDepth CMDTaskStackDepth = configMINIMAL_STACK_SIZE;
TaskPriority CMDTaskStackPriority = tskIDLE_PRIORITY + 2;
TaskHandle_t cmdTaskHandler;

//class RTOSTask cmdManagerTask(CMDTaskName, commandManager, CMDTaskStackDepth, CMDTaskStackPriority, NULL);

// Visual indicator Task
const char visualTaskName[] = "visual task";
TaskStackDepth visualTaskStackDepth = configMINIMAL_STACK_SIZE;
TaskPriority visualTaskStackPriority = tskIDLE_PRIORITY + 1;
TaskHandle_t visualTaskHandler;

/* Public functions */

void createTasks()
{
	BaseType_t xReturned;

	/* Create visual indicator task */
	xReturned = xTaskCreate(visualTask, visualTaskName, visualTaskStackDepth, nullptr, visualTaskStackPriority, &visualTaskHandler);

	if (xReturned != pdPASS)
	{
		errorHandler(__FILE__, __LINE__, ERROR_FATAL, "Unable to create visual Task\n");
	}

	/* Create application manager task */
	xReturned = xTaskCreate(applicationManager, appTaskName, appTaskStackDepth, nullptr, CMDTaskStackPriority, &appTaskHandler);

	if (xReturned != pdPASS)
	{
		errorHandler(__FILE__, __LINE__, ERROR_FATAL, "Unable to create application Task\n");
	}

	/* Create command manager task */
	xReturned = xTaskCreate(commandManager, CMDTaskName, CMDTaskStackDepth, nullptr, CMDTaskStackPriority, &cmdTaskHandler);

	if (xReturned != pdPASS)
	{
		errorHandler(__FILE__, __LINE__, ERROR_FATAL, "Unable to create command Task\n");
	}
}

void initOS()
{
	vTaskStartScheduler();
}

void initVisualLedIndicator()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
	GPIO_InitStruct.Pin = INDICATOR_LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(INDICATOR_LED_PORT, &GPIO_InitStruct);
}

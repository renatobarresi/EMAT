/*
 * commandManager.cpp
 *
 *  Created on: May 21, 2023
 *      Author: renatobarresi
 */

#include "commandManager.h"
#include "rtos_module.h"

void commandManager(void *pvParams)
{
	while (1)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


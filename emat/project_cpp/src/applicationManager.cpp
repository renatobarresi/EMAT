/*
 * applicationManager.cpp
 *
 *  Created on: May 21, 2023
 *      Author: renatobarresi
 */

#include "applicationManager.h"
#include "rtos_module.h"

void applicationManager(void *pvParams)
{
	while (1)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

/*
 * rtos_module.c
 *
 *  Created on: May 7, 2023
 *      Author: renatobarresi
 */

#include "rtos_module.h"

/* Constructor */
RTOSTask::RTOSTask(const char *taskName,
		void (*taskFunction)(void *),
		TaskStackDepth stackSize,
		TaskPriority priority,
		void *parameters)
{
	this->m_taskFunction = taskFunction;
	this->m_name = taskName;
	this->m_stackSize = stackSize;
	this->m_priority = priority;
	this->m_parameters = parameters;
}

void RTOSTask::create()
{
	BaseType_t xReturned;

	xReturned = xTaskCreate(this->m_taskFunction, this->m_name, this->m_stackSize, this->m_parameters, this->m_priority, &(this->m_handle));
	if (xReturned != pdPASS)
	{
		errorHandler(__FILE__, __LINE__, ERROR_FATAL, "Unable to create Task\n");
	}
}

void RTOSTask::suspend()
{
	vTaskSuspend(m_handle);
}

void RTOSTask::resume()
{
	vTaskResume(m_handle);
}

void RTOSTask::delay(const tickType xTicksToDelay)
{
	vTaskDelay(xTicksToDelay);
}

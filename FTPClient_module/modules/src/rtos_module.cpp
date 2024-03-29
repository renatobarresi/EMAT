/*
 * rtos_module.c
 *
 *  Created on: May 7, 2023
 *      Author: renatobarresi
 */

#include "rtos_module.h"

/* Constructor */
rtosTask::rtosTask(const char *taskName,
		void (*taskFunction)(void *),
		uint16_t stackSize,
		UBaseType_t priority,
		void *parameters)
{
	this->m_taskFunction = taskFunction;
	this->m_stackSize = stackSize;
	this->m_priority = priority;
	this->m_parameters = parameters;

	BaseType_t xReturned;

	xReturned = xTaskCreate(m_taskFunction, taskName, m_stackSize, m_parameters, m_priority, &m_handle);
	if (xReturned != pdPASS)
	{
		while(1);
	}
}

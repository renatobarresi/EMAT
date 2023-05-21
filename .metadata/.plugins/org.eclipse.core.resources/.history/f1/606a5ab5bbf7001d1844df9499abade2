#pragma once
#ifdef __cplusplus

#include <cstdint>
#include "FreeRTOS.h"
#include "task.h"

class rtosTask
{
public:
	/* Constructor */
	rtosTask(const char *taskName,
			void (*taskFunction)(void *),
			uint16_t stackSize,
			UBaseType_t priority,
			void *parameters);


private:
    TaskHandle_t m_handle;
    void (*m_taskFunction)(void *);
    void *m_parameters;
    uint16_t m_stackSize;
    UBaseType_t m_priority;
};

#endif




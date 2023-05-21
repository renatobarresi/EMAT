#pragma once
#ifdef __cplusplus

#include <cstdint>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "error.h"

// Define your own types
using TaskPriority = UBaseType_t;
using TaskStackDepth = uint16_t;
using QueueLength = UBaseType_t;
using QueueItemSize = UBaseType_t;
using tickType = TickType_t;

class RTOSTask
{
public:
	/**
	 * @brief Constructor for the rtosTask class.
	 *
	 * @param taskName The name of the task.
	 * @param taskFunction The function to be executed by the task.
	 * @param stackSize The stack size of the task.
	 * @param priority The priority of the task.
	 * @param parameters Additional parameters to pass to the task function.
	 */
	RTOSTask(const char *taskName,
			void (*taskFunction)(void *),
			TaskStackDepth stackSize,
			TaskPriority priority,
			void *parameters);
	/**
	* @brief Create and start the task.
	*/
	void create();

	/**
	* @brief Suspend the execution of the task.
	*/
	void suspend();

	/**
	* @brief Resume the execution of the task.
	*/
	void resume();

	/**
	* @brief Delay the execution of the task for a specified number of ticks.
	*
	* @param xTicksToDelay The number of ticks to delay.
	*/
	void delay(const tickType xTicksToDelay);

private:
	TaskHandle_t m_handle;
	const char *m_name;
	void (*m_taskFunction)(void *);
	void *m_parameters;
	TaskStackDepth m_stackSize;
	TaskPriority m_priority;
};

class RTOSMutex
{
public:
    /**
     * @brief Constructor for the RTOSMutex class.
     */
    RTOSMutex() : mutexHandle(xSemaphoreCreateMutex()) {}

    /**
     * @brief Take the mutex.
     */
    void take()
    {
        xSemaphoreTake(mutexHandle, portMAX_DELAY);
    }

    /**
     * @brief Give the mutex.
     */
    void give()
    {
        xSemaphoreGive(mutexHandle);
    }

private:
    SemaphoreHandle_t mutexHandle;
};

class RTOSQueue
{
public:
	/**
	 * @brief Constructor for the RTOSQueue class.
	 *
	 * @param length The maximum length of the queue.
	 * @param itemSize The size of each item in the queue.
	 */
	RTOSQueue(QueueLength length, QueueItemSize itemSize) : queueHandle(xQueueCreate(length, itemSize)) {}

	/**
	 * @brief Enqueue an item to the queue.
	 *
	 * @param item Pointer to the item to be enqueued.
	 */
	void enqueue(const void* item)
	{
		xQueueSend(queueHandle, item, portMAX_DELAY);
	}

	/**
	 * @brief Dequeue an item from the queue.
	 *
	 * @param item Pointer to the variable to store the dequeued item.
	 */
	void dequeue(void* item)
	{
		xQueueReceive(queueHandle, item, portMAX_DELAY);
	}

private:
	QueueHandle_t queueHandle;
};

#endif




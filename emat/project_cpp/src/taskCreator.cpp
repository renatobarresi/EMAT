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
#include "error.h"

/* Constant expressions  */

/* Private variables */

/* Private functions */

/* Tasks */

// Application Task
const char appTaskName[] = "application task";
TaskStackDepth appTaskStackDepth = 100;
TaskPriority appTaskStackPriority = 1;

class RTOSTask appTask(appTaskName, applicationManager, appTaskStackDepth, appTaskStackPriority, NULL);

// Command Manager Task
const char CMDTaskName[] = "command task";
TaskStackDepth CMDTaskStackDepth = 100;
TaskPriority CMDTaskStackPriority = 1;

class RTOSTask cmdManagerTask(CMDTaskName, commandManager, CMDTaskStackDepth, CMDTaskStackPriority, NULL);

/* Public functions */

void createTasks()
{

}



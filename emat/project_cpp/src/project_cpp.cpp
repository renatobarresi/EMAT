/*
 * project_cpp.cpp
 *
 *  Created on: May 14, 2023
 *      Author: renatobarresi
 */

#include "project_cpp.h"
#include "taskCreator.h"
#include "error.h"

/* Includes for testing purposes */
#include "filesystem.h"
#include "SD_module.h"

void main_cpp(void)
{

	fileSystem& fs = fileSystem::getInstance();

	char buff[1024];
	fs.read("errorLog.txt", buff, 50);

	/*
	initVisualLedIndicator();

	createTasks();

	initOS();
	*/
	while(1);
}


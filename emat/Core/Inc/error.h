/*
 * error.h
 *
 *  Created on: May 14, 2023
 *      Author: renatobarresi
 */

#pragma once

typedef enum
{
	ERROR_FATAL,
}errorSeverity;

#ifdef __cplusplus

#include <stdint.h>
#include <string.h>

#define ASSERT_STOP_PROGRAM 1

extern "C"
{
	void assert_failed(uint8_t *file, uint32_t line);
	void errorHandler(const char* fileName, int lineNum, errorSeverity errorType, const char* errorName);
}

#endif /* INC_ERROR_H_ */
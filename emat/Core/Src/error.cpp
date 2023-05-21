/*
 * error.c
 *
 *  Created on: May 14, 2023
 *      Author: renatobarresi
 */

#include <littleFSInterface.h>
#include "error.h"
#include "cmsis_gcc.h"
#include "filesystem.h"
#include "string"
#include <cstring>

static constexpr const char * errorLogFileName = "errorLog.txt";
static constexpr uint16_t BUFFER_SIZE = 256;

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
#if ASSERT_STOP_PROGRAM
	while(1);
#endif
}

void errorHandler(const char* fileName, int lineNum, errorSeverity errorType, const char* errorName)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    switch (errorType)
    {
        case ERROR_FATAL:
            __disable_irq();

            fileSystem& fs = fileSystem::getInstance();

            char buffer[BUFFER_SIZE];
            snprintf(buffer, BUFFER_SIZE, "File: %s\nLine: %d\nType: %d\nName: %s\n",
                     fileName, lineNum, errorType, errorName);

            fs.write(errorLogFileName, buffer);

            while (1);
    }
    /* USER CODE END Error_Handler_Debug */
}

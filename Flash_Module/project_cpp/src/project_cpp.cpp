/*
 * project_cpp.cpp
 *
 *  Created on: Mar 19, 2023
 *      Author: renatobarresi
 */

#include "project_cpp.h"
#include "W25Qx_module.h"
#include <cstring>

SPI_HandleTypeDef hspi1;

W25Q64 myFlash(&hspi1, GPIOF, GPIO_PIN_13);
SPI mySPI(&hspi1, GPIO_PIN_13, GPIOF);

void main_cpp(void)
{
	/*if (myFlash.init() == HAL_ERROR)
	{
		while(1);
	}
	while(1)
	{
		//myFlash.read_JDEC();
		uint8_t statusReg;
		myFlash.write_enable();
		HAL_Delay(250);
		statusReg = myFlash.read_status_register();
		HAL_Delay(250);
		myFlash.write_disable();
		HAL_Delay(250);
		statusReg = myFlash.read_status_register();
		HAL_Delay(250);
	}*/
	uint8_t buffer[] = "12345 flash";
	uint8_t rxBuf[11];
	uint32_t address = 0;
	if (myFlash.init() == HAL_ERROR)
	{
		while(1);
	}
	while(1)
	{
		myFlash.chip_erase();
		myFlash.page_program(address, buffer, 11);
		myFlash.read_data(address, rxBuf, 11);
	}
	/*if (mySPI.init() == HAL_ERROR)
	{
		while(1);
	}
	uint8_t cmd = 0x9F;
	uint8_t dummy = 0x00;
	while(1)
	{
		mySPI.csLow();
		mySPI.transmit(&cmd, 1);
		mySPI.transmit(&dummy, 1);
		mySPI.transmit(&dummy, 1);
		mySPI.transmit(&dummy, 1);
		mySPI.csHigh();
	}*/
}
/*
 * rtc_module.h
 *
 *  Created on: Apr 2, 2023
 *      Author: renatobarresi
 */

#pragma once
#ifdef __cplusplus

#include "stm32f4xx_hal.h"
#include <string>

class RTCModule
{
public:
	HAL_StatusTypeDef init();
	void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
	void setDate(uint8_t weekDay, uint8_t month, uint8_t date, uint8_t year);
	void getTime(uint8_t* hours, uint8_t* minutes, uint8_t* seconds);
	void getDate(uint8_t* weekDay, uint8_t* month, uint8_t* date, uint8_t* year);
	void setTimeAndDate(const std::string &pBuff);
	std::string getTimeAndDate();
};

#endif

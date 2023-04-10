/*
 * main_cpp.cpp
 *
 *  Created on: Apr 2, 2023
 *      Author: renatobarresi
 */

#include "main_cpp.h"
#include "rtc_module.h"

RTCModule myRTC;

void main_cpp()
{
	myRTC.init();
	myRTC.setTimeAndDate("21:15:00-21/08/2023");
	std::string currentTimeAndDate = myRTC.getTimeAndDate();
	while(1)
	{

	}
}


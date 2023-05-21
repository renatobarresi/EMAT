/*
 * hmi_module.h
 *
 *  Created on: Mar 19, 2023
 *      Author: renatobarresi
 */

#pragma once
#ifdef __cplusplus

#include <cstdint>
#include <string>
#include "stm32f4xx_hal.h"
#include "serialPort_module.h"

constexpr char const* CMD_SET_TIME = "SET_TIME:hh:mm:ss-dd.mm.yyyy";
constexpr char const* CMD_PRINT_TIME = "PRINT_TIME";

class humanMachineInterface
{
private:
	USART_TypeDef *instance;
	UART_HandleTypeDef *uartHandler;
	uint32_t baudrate;
	serialPort mySerialPort;
public:
	humanMachineInterface(USART_TypeDef *instance, UART_HandleTypeDef *uartHandler, uint32_t baudrate);
	bool print(const std::string &pBuff);
	bool init();
	void processCommand();
	void printWelcomeBanner();
	void clearScreen();
	void printDeviceInfo();
	void printCommands();
	uint8_t serialAvailable();
};

#endif
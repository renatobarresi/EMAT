/*
 * hmi_module.cpp
 *
 *  Created on: Mar 19, 2023
 *      Author: renatobarresi
 */

/* Includes */

#include <cstring>
#include "hmi_module.h"
#include "serialPort_module.h"

/* Private variables */

static const char *banner = "E.M.A.T\r\n";
static const char *clearScreenBuff = "\033[2J";
static const char *moveCursorOrigin = "\033[1;1H";
std::string EMATCommands = "Ingrese uno de los siguientes comandos:\r\n1)" + std::string(CMD_SET_TIME) + "\r\n2)" + std::string(CMD_PRINT_TIME) + "\r\n";

/* Private functions */

/* Private methods */

/* Constructor */

/**
 * @brief
 */
humanMachineInterface::humanMachineInterface(USART_TypeDef *instance, UART_HandleTypeDef *uartHandler, uint32_t baudrate)
	: mySerialPort(instance, uartHandler, baudrate)
{
	this->instance = instance;
	this->uartHandler = uartHandler;
	this->baudrate = baudrate;
}

/* Public methods */

/**
 * @brief
 */
bool humanMachineInterface::init()
{
	return mySerialPort.init();
}

/**
 * @brief
 */
bool humanMachineInterface::print(const std::string &pBuff)
{
	return mySerialPort.write(pBuff);
}

/**
 * @brief Process the received command via the serial port
 */
void humanMachineInterface::processCommand()
{
	std::string rxStr = mySerialPort.read();
	if (rxStr != "")
	{
		mySerialPort.write(rxStr);
	}
}

/**
 * @brief
 */
void humanMachineInterface::printWelcomeBanner()
{
	print(banner);
}

/**
 * @brief
 */
void humanMachineInterface::clearScreen()
{
	print(clearScreenBuff);
	print(moveCursorOrigin);
}

/**
 * @brief
 */
void humanMachineInterface::printDeviceInfo()
{

}

/**
 * @brief
 */
void humanMachineInterface::printCommands()
{
	mySerialPort.write(EMATCommands);
}

/**
 * @brief
 */
uint8_t serialAvailable()
{
	return 1;
}














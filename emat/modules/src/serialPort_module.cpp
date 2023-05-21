/*
 * serialPort_module.cpp
 *
 *  Created on: Mar 22, 2023
 *      Author: renatobarresi
 */

#include "serialPort_module.h"
#include <cstring>

/* DMA related objects TODO: Abstract it */
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;

#define RxBuf_SIZE 512
#define MainBuf_SIZE 2048

#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD

uint8_t RxBuf[RxBuf_SIZE];
uint8_t MainBuf[MainBuf_SIZE];

uint16_t oldPos = 0;
uint16_t newPos = 0;

uint8_t isOK = 0;

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(huart->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART3 DMA Init */
    /* USART3_RX Init */
    hdma_usart3_rx.Instance = DMA1_Stream1;
    hdma_usart3_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_rx.Init.Mode = DMA_NORMAL;
    hdma_usart3_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
    {
      //Error_Handler();
    }

    __HAL_LINKDMA(huart,hdmarx,hdma_usart3_rx);

    /* USART3_TX Init */
    hdma_usart3_tx.Instance = DMA1_Stream3;
    hdma_usart3_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_tx.Init.Mode = DMA_NORMAL;
    hdma_usart3_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart3_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_tx) != HAL_OK)
    {
      //Error_Handler();
    }

    __HAL_LINKDMA(huart,hdmatx,hdma_usart3_tx);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }

}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOD, STLK_RX_Pin|STLK_TX_Pin);

    /* USART3 DMA DeInit */
    HAL_DMA_DeInit(huart->hdmarx);
    HAL_DMA_DeInit(huart->hdmatx);

    /* USART3 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART3)
	{
		oldPos = newPos;  // Update the last position before copying new data

		/* If the data in large and it is about to exceed the buffer size, we have to route it to the start of the buffer
		 * This is to maintain the circular buffer
		 * The old data in the main buffer will be overlapped
		 */
		if (oldPos+Size > MainBuf_SIZE)  // If the current position + new data size is greater than the main buffer
		{
			uint16_t datatocopy = MainBuf_SIZE-oldPos;  // find out how much space is left in the main buffer
			memcpy ((uint8_t *)MainBuf+oldPos, RxBuf, datatocopy);  // copy data in that remaining space

			oldPos = 0;  // point to the start of the buffer
			memcpy ((uint8_t *)MainBuf, (uint8_t *)RxBuf+datatocopy, (Size-datatocopy));  // copy the remaining data
			newPos = (Size-datatocopy);  // update the position
		}

		/* if the current position + new data size is less than the main buffer
		 * we will simply copy the data into the buffer and update the position
		 */
		else
		{
			memcpy ((uint8_t *)MainBuf+oldPos, RxBuf, Size);
			newPos = Size+oldPos;
		}

		/* start the DMA again */
		HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *) RxBuf, RxBuf_SIZE);
		__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
	}
}

/* Private methods */
void serialPort::initDMAPeripheral()
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
}

bool serialPort::initUartPeripheral(UART_HandleTypeDef *uartHandler, USART_TypeDef *instance, uint32_t baudrate)
{
	// fill the UART_HandleTypeDef structure and Init the USART peripheral
	uartHandler->Instance = instance;
	uartHandler->Init.BaudRate = baudrate;
	uartHandler->Init.WordLength = UART_WORDLENGTH_8B;
	uartHandler->Init.StopBits = UART_STOPBITS_1;
	uartHandler->Init.Parity = UART_PARITY_NONE;
	uartHandler->Init.Mode = UART_MODE_TX_RX;
	uartHandler->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandler->Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(uartHandler) != HAL_OK)
	{
		return false;
	}

	// Start the DMA IDLE line
	if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(uartHandler, RxBuf, RxBuf_SIZE))
	{
		return false;
	}
	__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
	return true;
}

/* Constructor */
/**
 * @brief Constructor for the serialPort class
 * @param instance: Pointer to the USART_TypeDef structure
 * @param uartHandler: Pointer to the UART_HandleTypeDef structure
 * @param baudrate: Baud rate of the USART peripheral
 */
serialPort::serialPort(USART_TypeDef *instance, UART_HandleTypeDef *uartHandler, uint32_t baudrate)
{
	this->instance = instance;
	this->uartHandler = uartHandler;
	this->baudrate = baudrate;
}


/* Public Methods */
/**
 * @brief Initializes the serial port
 * @return true if successful, false otherwise
 */
bool serialPort::init()
{
	initDMAPeripheral();
	return initUartPeripheral(this->uartHandler, this->instance, this->baudrate);
}

/**
 * @brief Write a string to the serial port
 * @param pBuff: String to be sent
 * @return true if successful, false otherwise
 */
bool serialPort::write(const std::string &pBuff)
{
	// Calculate string width
	uint32_t buffLenght = pBuff.length();

	// Convert string to char TODO: check that new worked
	char *charArray = new char[buffLenght + 1];
	strcpy(charArray, pBuff.c_str());

	// Transmit buffer via UART port
	HAL_UART_Transmit_DMA(this->uartHandler, (const uint8_t *)charArray, buffLenght);
	HAL_Delay(10);

	// Free memory
	delete[] charArray;

	return true;
}

/**
 * @brief Read data from the serial buffer
 * @return A std::string containing the data from the buffer
 */
std::string serialPort::read()
{
    //std::lock_guard<std::mutex> lock(bufferMutex); // Optional: use a mutex for thread safety

    std::string receivedData;
    bool delimiterFound = false;
    uint16_t delimiterPosition = 0;

    // Search for the newline character as a delimiter
    for (uint16_t i = oldPos; i < newPos; ++i) {
        if (MainBuf[i] == '\r') {
            delimiterFound = true;
            delimiterPosition = i;
            break;
        }
    }

    if (delimiterFound) {
        // Copy data from MainBuf to a new string
        receivedData.assign(reinterpret_cast<char*>(MainBuf) + oldPos, delimiterPosition - oldPos);

        // Clear the part of MainBuf that was read
        std::memset(MainBuf + oldPos, 0, delimiterPosition - oldPos + 1);

        // Update oldPos
        oldPos = delimiterPosition + 1;
    }

    return receivedData;
}

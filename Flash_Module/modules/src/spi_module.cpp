/*
 * spi_module.cpp
 *
 *  Created on: Apr 5, 2023
 *      Author: renatobarresi
 */

#include "spi_module.h"

DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;


/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hspi->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* SPI1 DMA Init */
    /* SPI1_RX Init */
    /*hdma_spi1_rx.Instance = DMA2_Stream0;
    hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_rx.Init.Mode = DMA_NORMAL;
    hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
    {
      while(1);
    }

    __HAL_LINKDMA(hspi,hdmarx,hdma_spi1_rx);*/

    /* SPI1_TX Init */
    /*hdma_spi1_tx.Instance = DMA2_Stream3;
    hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      while(1);
    }

    __HAL_LINKDMA(hspi,hdmatx,hdma_spi1_tx);*/

    /* SPI1 interrupt Init */
    //HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(SPI1_IRQn);
  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }

}

SPI::SPI(SPI_HandleTypeDef *hspi, uint16_t pin, GPIO_TypeDef *port)
{
	this->hspi_ = hspi;
	this->CSPin = pin;
	this->CSPort = port;
}

HAL_StatusTypeDef SPI::init()
{

	// Configure CS GPIO
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOF_CLK_ENABLE(); //TODO add modularity

	GPIO_InitStruct.Pin = this->CSPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(this->CSPort, &GPIO_InitStruct);

	HAL_GPIO_WritePin(this->CSPort, this->CSPin, GPIO_PIN_SET);

	this->hspi_->Instance = SPI1; //TODO add modularity
	this->hspi_->Init.Mode = SPI_MODE_MASTER;
	this->hspi_->Init.Direction = SPI_DIRECTION_2LINES;
	this->hspi_->Init.DataSize = SPI_DATASIZE_8BIT;
	this->hspi_->Init.CLKPolarity = SPI_POLARITY_LOW;
	this->hspi_->Init.CLKPhase = SPI_PHASE_1EDGE;
	this->hspi_->Init.NSS = SPI_NSS_SOFT;
	this->hspi_->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	this->hspi_->Init.FirstBit = SPI_FIRSTBIT_MSB;
	this->hspi_->Init.TIMode = SPI_TIMODE_DISABLE;
	this->hspi_->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	this->hspi_->Init.CRCPolynomial = 10;

	// DMA init
	/* DMA controller clock enable */
	//__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream0_IRQn interrupt configuration */
	//HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	//HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	/* DMA2_Stream3_IRQn interrupt configuration */
	//HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
	//HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

	return HAL_SPI_Init(this->hspi_);
}

HAL_StatusTypeDef SPI::transmit(uint8_t *pData, uint16_t size)
{
	return HAL_SPI_Transmit(this->hspi_, pData, size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef SPI::receive(uint8_t *pData, uint16_t size)
{
	return HAL_SPI_Receive(this->hspi_, pData, size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef SPI::transmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t size)
{
	return HAL_SPI_TransmitReceive(this->hspi_, pTxData, pRxData, size, HAL_MAX_DELAY);
}

void SPI::csHigh()
{
	HAL_GPIO_WritePin(this->CSPort, this->CSPin, GPIO_PIN_SET);
}

void SPI::csLow()
{
	HAL_GPIO_WritePin(this->CSPort, this->CSPin, GPIO_PIN_RESET);
}

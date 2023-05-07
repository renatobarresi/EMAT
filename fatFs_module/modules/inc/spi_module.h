/*
 * spi_module.h
 *
 *  Created on: Apr 5, 2023
 *      Author: renatobarresi
 */

#pragma once
#ifdef __cplusplus

#include "stm32f4xx_hal.h"

class SPI {
private:
    SPI_HandleTypeDef *hspi_;
    uint16_t CSPin;
    GPIO_TypeDef *CSPort;
    //DMA_HandleTypeDef *hdma_tx_;
    //DMA_HandleTypeDef *hdma_rx_;
public:
    SPI(SPI_HandleTypeDef *hspi, uint16_t pin, GPIO_TypeDef *port);
    HAL_StatusTypeDef init();
    HAL_StatusTypeDef transmit(uint8_t *pData, uint16_t size);
    HAL_StatusTypeDef receive(uint8_t *pData, uint16_t size);
    HAL_StatusTypeDef transmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t size);
    void csHigh();
    void csLow();
};

#endif
/*
 * W25Qx_module.h
 *
 *  Created on: Apr 5, 2023
 *      Author: renatobarresi
 */
#pragma once
#ifdef __cplusplus

#include "stm32f4xx_hal.h"
#include "spi_module.h"

class W25Q64 {
public:
    W25Q64(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_gpio_port, uint16_t cs_pin);

    HAL_StatusTypeDef init();
    void write_enable();
    void write_disable();
    uint8_t read_status_register();
    void write_status_register(uint8_t status);
    void chip_erase();
    void sector_erase(uint32_t addr);
    void block_erase(uint32_t addr);
    void page_program(uint32_t addr, uint8_t *data, uint16_t size);
    void read_data(uint32_t addr, uint8_t *data, uint16_t size);
    void wait_until_ready();
    void read_JDEC();

private:
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *csGPIOPort;
    uint16_t csPin;

    SPI mySPIPort;

    void cs_select();
    void cs_deselect();
};
#endif

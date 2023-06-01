/*
 * SD_module.h
 *
 *  Created on: May 24, 2023
 *      Author: renatobarresi
 */

#pragma once
#ifdef __cplusplus

#include "stm32f4xx_hal.h"
#include "spi_module.h"

enum class TypeOfCard
{
    SDSC,
    SDHC,
    SDXC
};

/**
 * @class SDCard
 * @brief Singleton class for handling SD card operations.
 *
 * This class provides an interface for communicating with SD card via SPI.
 * It's a singleton design pattern to make sure only one instance exists for the SD card throughout the application.
 */
class SDCard
{
public:
	/**
	* @brief Constructs the SDCard class.
	*
	* @param hspi         SPI handler.
	* @param cs_gpio_port GPIO port for the CS (Chip Select) pin.
	* @param cs_pin       CS pin.
	*/
	SDCard(GPIO_TypeDef *cs_gpio_port, uint16_t cs_pin);

	/**
	* @brief Initializes the SD card and prepares it for use.
	*/
	HAL_StatusTypeDef init();
	/**
	* @brief Reads a block of data from the SD card.
	*
	* @param blockNumber The block number to read.
	* @param buffer      Pointer to the buffer where the data will be stored.
	*/
	HAL_StatusTypeDef readBlock(uint32_t blockNumber, uint8_t* buffer);

	/**
	* @brief Writes a block of data to the SD card.
	*
	* @param blockNumber The block number to write.
	* @param data        Pointer to the data to be written.
	*/
	HAL_StatusTypeDef writeBlock(uint32_t blockNumber, const uint8_t* data);

	/**
	* @brief Reads multiple blocks of data from the SD card.
	*
	* @param startBlock The starting block number.
	* @param numBlocks  Number of blocks to read.
	* @param buffer     Pointer to the buffer where the data will be stored.
	*/
	HAL_StatusTypeDef readMultipleBlocks(uint32_t startBlock, uint32_t numBlocks, uint8_t* buffer);

	/**
	* @brief Writes multiple blocks of data to the SD card.
	*
	* @param startBlock The starting block number.
	* @param numBlocks  Number of blocks to write.
	* @param data       Pointer to the data to be written.
	*/
	HAL_StatusTypeDef writeMultipleBlocks(uint32_t startBlock, uint32_t numBlocks, const uint8_t* data);

	/**
	* @brief Returns the total capacity of the SD card in bytes.
	*
	* @return Capacity of the SD card in bytes.
	*/
	uint64_t getSize();

	/**
	* @brief Returns the block size of the SD card in bytes.
	*
	* @return Block size of the SD card in bytes.
	*/
	uint16_t getBlockSize();

	/**
	* @brief Returns the type of the SD card (SDSC, SDHC, or SDXC).
	*
	* @return Type of the SD card.
	*/
	TypeOfCard getCardType();

	/**
	* @brief Checks if the SD card is ready and accessible.
	*
	* @return True if the SD card is ready, false otherwise.
	*/
	bool isReady();

	/**
	* @brief Checks if the SD card is writable.
	*
	* @return True if the SD card is writable, false otherwise.
	*/
	bool isWritable();



private:
    GPIO_TypeDef *csGPIOPort; ///< GPIO port for the chip select pin.
    uint16_t csPin; ///< Pin number for the chip select.

    SPI& mySPIPort; ///< SPI port for communication with the SD card.

    /**
     * @brief Selects the chip by pulling the chip select pin low.
     */
    void cs_select();

    /**
     * @brief Deselects the chip by pulling the chip select pin high.
     */
    void cs_deselect();

	/**
	* @brief Generate a command to be sent to the SD card.
	*
	* @param command The command index.
	* @param argument The argument for the command.
	* @param cmdBuffer The buffer to hold the generated command bytes. Must be at least 6 bytes.
	*/
    void commandGenerator(uint8_t command, uint32_t argument, uint8_t* cmdBuffer);
};

#endif

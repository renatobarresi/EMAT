/*
 * SD_module.cpp
 *
 *  Created on: May 24, 2023
 *      Author: renatobarresi
 */

#include "SD_module.h"
#include "spi_module.h"
#include "gpio_module.h"
#include "error.h"

/*
 * defines
 */

// Basic commands (class 0)
#define CMD0    0  // GO_IDLE_STATE
#define CMD1    1  // SEND_OP_COND (not used in SD)
#define CMD2    2  // ALL_SEND_CID
#define CMD3    3  // SEND_RELATIVE_ADDR
#define CMD4    4  // SET_DSR
#define CMD5    5  // Reserved for SDIO
#define CMD6    6  // SWITCH_FUNC
#define CMD7    7  // SELECT/DESELECT_CARD
#define CMD8    8  // SEND_IF_COND
#define CMD9    9  // SEND_CSD
#define CMD10   10 // SEND_CID
#define CMD11   11 // Voltage switch
#define CMD12   12 // STOP_TRANSMISSION
#define CMD13   13 // SEND_STATUS

// Block read commands (class 2)
#define CMD16   16 // SET_BLOCKLEN
#define CMD17   17 // READ_SINGLE_BLOCK
#define CMD18   18 // READ_MULTIPLE_BLOCK
#define CMD19   19 // Speed class control
#define CMD20   20 // Speed class control
#define CMD23   23 // SET_BLOCK_COUNT

// Block write commands (class 4)
#define CMD24   24 // WRITE_BLOCK
#define CMD25   25 // WRITE_MULTIPLE_BLOCK
#define CMD26   26 // PROGRAM_CID
#define CMD27   27 // PROGRAM_CSD

// Write protection (class 6)
#define CMD28   28 // SET_WRITE_PROT
#define CMD29   29 // CLR_WRITE_PROT
#define CMD30   30 // SEND_WRITE_PROT

// Erase commands (class 5)
#define CMD32   32 // ERASE_WR_BLK_START
#define CMD33   33 // ERASE_WR_BLK_END
#define CMD38   38 // ERASE

// I/O mode commands (class 9)
// Reserved for SDIO

// Lock card (class 7)
#define CMD42   42 // LOCK_UNLOCK

// Application specific commands (class 8)
#define CMD55   55 // APP_CMD
#define CMD56   56 // GEN_CMD
#define ACMD6   6  // SET_BUS_WIDTH (A is for 'Application')
#define ACMD13  13 // SD_STATUS
#define ACMD22  22 // SEND_NUM_WR_BLOCKS
#define ACMD23  23 // SET_WR_BLK_ERASE_COUNT
#define ACMD41  41 // SD_SEND_OP_COND
#define ACMD42  42 // SET_CLR_CARD_DETECT
#define ACMD51  51 // SEND_SCR

// Placeholder for SD card types.
enum SD_CardType {
    SDSC,
    SDHC,
    SDXC
};

/* Constructor */
SDCard::SDCard(GPIO_TypeDef *cs_gpio_port, uint16_t cs_pin)
: csGPIOPort(cs_gpio_port), csPin(cs_pin), mySPIPort(SPI::getInstance())
{
}

/**
 * @brief Generate a command to be sent to the SD card.
 *
 * @param command The command index.
 * @param argument The argument for the command.
 * @param cmdBuffer The buffer to hold the generated command bytes. Must be at least 6 bytes.
 */
void SDCard::commandGenerator(uint8_t command, uint32_t argument, uint8_t* cmdBuffer) {
    // Check that cmdBuffer is not null
    if (cmdBuffer == nullptr) {
    	errorHandler(__FILE__, __LINE__, ERROR_FATAL, "NULL POINTER");
    }

    // Start bit (0) + transmission bit (1) + command index
    cmdBuffer[0] = 0x40 | command;

    // Argument (4 bytes, MSB first)
    cmdBuffer[1] = (argument >> 24) & 0xFF;
    cmdBuffer[2] = (argument >> 16) & 0xFF;
    cmdBuffer[3] = (argument >> 8) & 0xFF;
    cmdBuffer[4] = argument & 0xFF;

    // CRC and end bit for CMD0 and CMD8, otherwise ignored for other commands
    cmdBuffer[5] = (command == CMD0 || command == CMD8) ? 0x87 : 0x01;
}

HAL_StatusTypeDef SDCard::init() {

	HAL_StatusTypeDef status;
    uint8_t cmdBuffer[6];  // Buffer to hold the command.

	// Init GPIO peripheral
	initGPIOOutput(this->csPin, this->csGPIOPort);

	// Check if the SPI peripheral has already been initialized
	if (SPIStates::NotInitialized == mySPIPort.state)
	{
		status = mySPIPort.init();
		if (HAL_OK != status)
		{
			return status;
		}
	}

	// Reset the card
	cs_select();
	commandGenerator(CMD0, 0, cmdBuffer);
	status = mySPIPort.transmit(cmdBuffer, sizeof(cmdBuffer));
	cs_deselect();
    if (status != HAL_OK)
    {
        return status;
    }

    HAL_Delay(1);

	// Check if the card is version 2.x
    cs_select();
    commandGenerator(CMD8, 0x1AA, cmdBuffer);
    status = mySPIPort.transmit(cmdBuffer, sizeof(cmdBuffer));
    if (status != HAL_OK)
    {
    	cs_deselect();
        return status;
    }

	// The response should be 0x01 if the card is version 2.x
    uint8_t response[5];
    status = mySPIPort.receive(response, sizeof(response));
    if (status != HAL_OK) {
        return status;
    }
    if ((response[3] & 0x0F) != 0x01 || response[4] != 0xAA) {
        // Card is not version 2.0 compliant or does not support the voltage level of 2.7-3.6V
        return HAL_ERROR;
    }


	// Use CMD55 and ACMD41 to initialize the card

	// The response should be 0x01 if CMD55 was accepted

	 // The response should be 0x00 if ACMD41 was accepted and the card is ready

	return HAL_OK;
}

HAL_StatusTypeDef SDCard::readBlock(uint32_t blockNumber, uint8_t* buffer) {
    SPI& spi = SPI::getInstance();

    spi.csLow(csPin, csGPIOPort);

    // Send command to read a block...

    spi.csHigh(csPin, csGPIOPort);
}

HAL_StatusTypeDef SDCard::writeBlock(uint32_t blockNumber, const uint8_t* data) {
    SPI& spi = SPI::getInstance();

    spi.csLow(csPin, csGPIOPort);

    // Send command to write a block...

    spi.csHigh(csPin, csGPIOPort);
}

HAL_StatusTypeDef SDCard::readMultipleBlocks(uint32_t startBlock, uint32_t numBlocks, uint8_t* buffer) {
    // Similar to readBlock, but with a loop and handling for multiple blocks.
}

HAL_StatusTypeDef SDCard::writeMultipleBlocks(uint32_t startBlock, uint32_t numBlocks, const uint8_t* data) {
    // Similar to writeBlock, but with a loop and handling for multiple blocks.
}

uint64_t SDCard::getSize() {
    // Implement code to return the total capacity of the SD card in bytes.
    // This will depend on specific SD card commands and how they're handled.
    return 0; // placeholder
}

uint16_t SDCard::getBlockSize() {
    // Implement code to return the block size of the SD card in bytes.
    // This will depend on specific SD card commands and how they're handled.
    return 0; // placeholder
}

TypeOfCard SDCard::getCardType() {
    // Implement code to identify the SD card type and return as a string.
    // This will depend on specific SD card commands and how they're handled.
    return TypeOfCard::SDHC; // placeholder
}

bool SDCard::isReady() {
    // Implement code to check if the SD card is ready.
    // This will depend on specific SD card commands and how they're handled.
    return false; // placeholder
}

bool SDCard::isWritable() {
    // Implement code to check if the SD card is writable.
    // This will depend on specific SD card commands and how they're handled.
    return false; // placeholder
}

void SDCard::cs_select()
{
	mySPIPort.csLow(this->csPin, this->csGPIOPort);
}

void SDCard::cs_deselect()
{
	mySPIPort.csHigh(this->csPin, this->csGPIOPort);
}

#include "W25Q64_wrapper.h"
#include "W25Qx_module.h"
#include "string.h"

#define FF_BUFFER_SIZE 4096
static BYTE write_buffer[FF_BUFFER_SIZE]; // define a write buffer of size FF_BUFFER_SIZE

SPI_HandleTypeDef hspi1;
W25Q64 myFlash(&hspi1, GPIOF, GPIO_PIN_13);

uint8_t is_initialized = 0;

extern "C"
{
	DSTATUS W25Q64Init()
	{
		if (myFlash.init() == HAL_OK)
		{
			is_initialized = 1;
		}
		return RES_OK; // assuming there is no error, otherwise return appropriate error code
	}

	DSTATUS W25Q64Read(BYTE *buff, LBA_t sector, UINT count)
	{
	    uint32_t addr = sector * FF_MAX_SS;
	    uint32_t size = count * FF_MAX_SS;
	    myFlash.read_data(addr, (uint8_t *)buff, size);
	    return RES_OK; // assuming there is no error, otherwise return appropriate error code
	}

	DSTATUS W25Q64Write(const BYTE *buff, LBA_t sector, UINT count)
	{
	    uint32_t sector_offset = 0;
	    uint32_t sector_bytes_left = 0;
	    uint32_t bytes_to_copy = 0;
	    uint32_t addr = sector * FF_MAX_SS;
	    uint32_t size = count * FF_MAX_SS;

	    while (size > 0)
	    {
	        // Calculate the number of bytes left in the current sector
	        sector_bytes_left = FF_MAX_SS - (addr % FF_MAX_SS);

	        // Calculate the offset within the current sector
	        sector_offset = addr % FF_MAX_SS;

	        // Determine the number of bytes to copy to the write buffer
	        bytes_to_copy = (size < sector_bytes_left) ? size : sector_bytes_left;

	        // Copy the data to the write buffer
	        memcpy(&write_buffer[sector_offset], &buff[addr - (sector * FF_MAX_SS)], bytes_to_copy);

	        // If the write buffer is full or we have reached the end of the data, program the page
	        if ((sector_offset + bytes_to_copy == FF_MAX_SS) || (size == bytes_to_copy))
	        {
	            myFlash.page_program(addr - sector_offset, write_buffer, FF_MAX_SS);
	        }

	        // Increment the address and decrement the number of bytes left to write
	        addr += bytes_to_copy;
	        size -= bytes_to_copy;
	    }

	    return RES_OK; // assuming there is no error, otherwise return appropriate error code
	}

	DSTATUS W25Q64EraseBlock(uint32_t addr)
	{
		myFlash.block_erase(addr);
		return RES_OK; // assuming there is no error, otherwise return appropriate error code
	}

	DSTATUS W25Q64EraseSector(uint32_t addr)
	{
		myFlash.sector_erase(addr);
		return RES_OK; // assuming there is no error, otherwise return appropriate error code
	}

	DRESULT W25Q64DiskIoctl(BYTE cmd, void *buff)
	{
	    switch (cmd)
	    {
	    case CTRL_SYNC:
	        myFlash.sync();
	        return RES_OK;

	    case GET_SECTOR_COUNT:
	        // Set the sector count in the buffer, for W25Q64, it would be (8 * 1024 * 1024) / FF_MAX_SS
	        *(DWORD *)buff = (8 * 1024 * 1024) / FF_MAX_SS;
	        return RES_OK;

	    case GET_SECTOR_SIZE:
	        // Set the sector size in the buffer, which is the value of FF_MAX_SS
	        *(WORD *)buff = FF_MAX_SS;
	        return RES_OK;

	    case GET_BLOCK_SIZE:
	        // Set the block size (erase block size) in the buffer, which can be 4 KB, 32 KB or 64 KB depending on your requirement
	        *(DWORD *)buff = 64 * 1024; // example for 64 KB erase block size
	        return RES_OK;

	    default:
	        return RES_PARERR;
	    }
	}

	DSTATUS W25Q64DiskStatus()
	{
	    // Assuming you have a variable to track the initialization status
	    if (is_initialized)
	    {
	        return RES_OK;
	    }
	    else
	    {
	        return STA_NOINIT;
	    }
	}
}

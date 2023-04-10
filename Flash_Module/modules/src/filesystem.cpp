/*
 * filesystem.cpp
 *
 *  Created on: Apr 10, 2023
 *      Author: renatobarresi
 */
#include "filesystem.h"
#include "W25Qx_module.h"

SPI_HandleTypeDef hspi1;
W25Q64 myFlash(&hspi1, GPIOF, GPIO_PIN_13);

int flash_init()
{
	myFlash.init();
}

int w25q64_read(const struct lfs_config *c, lfs_block_t block,
                lfs_off_t off, void *buffer, lfs_size_t size)
{
    uint32_t addr = block * c->block_size + off;
    myFlash.read_data(addr, static_cast<uint8_t *>(buffer), size);
    return 0;
}

int w25q64_prog(const struct lfs_config *c, lfs_block_t block,
                lfs_off_t off, const void *buffer, lfs_size_t size)
{
    uint32_t addr = block * c->block_size + off;
    myFlash.page_program(addr, const_cast<uint8_t *>(static_cast<const uint8_t *>(buffer)), size);
    return 0;
}

int w25q64_erase(const struct lfs_config *c, lfs_block_t block)
{
    uint32_t addr = block * c->block_size;
    myFlash.block_erase(addr);
    return 0;
}

int w25q64_sync(const struct lfs_config *c)
{
    // Nothing to do since we're not using any caching or buffering
    return 0;
}

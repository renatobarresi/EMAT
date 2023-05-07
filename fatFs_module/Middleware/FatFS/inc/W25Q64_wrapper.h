
#pragma once

#include <stdint.h>
#include "ff.h"
#include "diskio.h"

#ifdef __cplusplus
extern "C"
{

	DSTATUS W25Q64Init();
	DSTATUS W25Q64Read(BYTE *buff, LBA_t sector, UINT count);
	DSTATUS W25Q64Write(const BYTE *buff, LBA_t sector, UINT count);
	DSTATUS W25Q64EraseBlock(uint32_t addr);
	DSTATUS W25Q64EraseSector(uint32_t addr);
	DRESULT W25Q64DiskIoctl(BYTE cmd, void *buff);
	DSTATUS W25Q64DiskStatus();
}
#endif

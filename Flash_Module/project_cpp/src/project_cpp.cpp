/*
 * project_cpp.cpp
 *
 *  Created on: Mar 19, 2023
 *      Author: renatobarresi
 */

#include "project_cpp.h"
#include "W25Qx_module.h"
#include <cstring>
#include "filesystem.h"

//W25Q64 myFlash(&hspi1, GPIOF, GPIO_PIN_13);
//SPI mySPI(&hspi1, GPIO_PIN_13, GPIOF);

void main_cpp(void)
{
	/*if (myFlash.init() == HAL_ERROR)
	{
		while(1);
	}
	while(1)
	{
		//myFlash.read_JDEC();
		uint8_t statusReg;
		myFlash.write_enable();
		HAL_Delay(250);
		statusReg = myFlash.read_status_register();
		HAL_Delay(250);
		myFlash.write_disable();
		HAL_Delay(250);
		statusReg = myFlash.read_status_register();
		HAL_Delay(250);
	}*/
	/*uint8_t buffer[] = "12345 flash";
	uint8_t rxBuf[11];
	uint32_t address = 0;
	if (myFlash.init() == HAL_ERROR)
	{
		while(1);
	}
	while(1)
	{
		myFlash.chip_erase();
		myFlash.page_program(address, buffer, 11);
		myFlash.read_data(address, rxBuf, 11);
	}*/
	/*if (mySPI.init() == HAL_ERROR)
	{
		while(1);
	}
	uint8_t cmd = 0x9F;
	uint8_t dummy = 0x00;
	while(1)
	{
		mySPI.csLow();
		mySPI.transmit(&cmd, 1);
		mySPI.transmit(&dummy, 1);
		mySPI.transmit(&dummy, 1);
		mySPI.transmit(&dummy, 1);
		mySPI.csHigh();
	}*/

	flash_init();

    lfs_t lfs;
    int res = lfs_mount(&lfs, &cfg);
    if (res < 0) {
        // If the mount fails, try formatting the filesystem
        res = lfs_format(&lfs, &cfg);
        if (res < 0) {
        	while(1);
        }
        // Try mounting again
        res = lfs_mount(&lfs, &cfg);
        if (res < 0) {
        	while(1);
        }
    }

    // Open the file for writing
    lfs_file_t file;
    res = lfs_file_open(&lfs, &file, "example.txt", LFS_O_WRONLY | LFS_O_CREAT);
    if (res < 0) {
    	while(1);
    }

    // Write some data to the file
    const char *data = "Hello, LittleFS!";
    res = lfs_file_write(&lfs, &file, data, strlen(data));
    if (res < 0) {
    	while(1);
    }

    // Close the file after writing
    lfs_file_close(&lfs, &file);

    // Open the file for reading
    res = lfs_file_open(&lfs, &file, "example.txt", LFS_O_RDONLY);
    if (res < 0) {
    	while(1);
    }

    // Read the data from the file
    char buffer[32];
    res = lfs_file_read(&lfs, &file, buffer, sizeof(buffer));
    if (res < 0) {
        while(1);
    }

    // Null-terminate the read data
    buffer[res] = '\0';

    // Print the read data
    printf("Read data: %s\n", buffer);

    // Close the file after reading
    lfs_file_close(&lfs, &file);

    // Unmount the filesystem
    lfs_unmount(&lfs);

    while(1);
}

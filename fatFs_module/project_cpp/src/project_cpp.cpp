/*
 * project_cpp.cpp
 *
 *  Created on: Mar 19, 2023
 *      Author: renatobarresi
 */

#include <W25Q64_wrapper.h>
#include "project_cpp.h"
#include "ff.h"
#include "diskio.h"
#include <string.h>
#include <stdio.h>

// Implement this function to output data on your system
void print_data(const char *data)
{
    // Output the data using your preferred method, e.g., UART, display, etc.
}

void main_cpp(void)
{
    //FATFS fs;
    //FIL file;
    FRESULT fr;
    //UINT bw, br;
    BYTE work[FF_MAX_SS]; // Work area for the f_mkfs function
    /*const char *filename = "testfile.txt";
    const char *write_data = "Hello, W25Q64!";
    char read_data[32] = {0};*/

    // Format the W25Q64 SPI flash memory chip with FatFs
    fr = f_mkfs("", 0, work, sizeof(work));

    /*
    // Initialize the file system
    fr = f_mount(&fs, "", 1);
    if (fr != FR_OK) {
        print_data("Failed to mount the file system.");
        return;
    }

    // Create and open a new file
    fr = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (fr != FR_OK) {
        print_data("Failed to create the file.");
        return;
    }

    // Write data to the file
    fr = f_write(&file, write_data, strlen(write_data), &bw);
    if (fr != FR_OK || bw != strlen(write_data)) {
        print_data("Failed to write data to the file.");
        return;
    }

    // Close the file
    f_close(&file);

    // Open the file for reading
    fr = f_open(&file, filename, FA_READ);
    if (fr != FR_OK) {
        print_data("Failed to open the file for reading.");
        return;
    }

    // Read data from the file
    fr = f_read(&file, read_data, sizeof(read_data) - 1, &br);
    if (fr != FR_OK) {
        print_data("Failed to read data from the file.");
        return;
    }

    // Close the file
    f_close(&file);

    // Unmount the file system
    f_mount(NULL, "", 1);

    // Print the read data
    print_data("Data read from the file: ");
    print_data(read_data);
*/
    while(1);
}

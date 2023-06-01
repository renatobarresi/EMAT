/*
 * filesystem.cpp
 *
 *  Created on: May 19, 2023
 *      Author: renatobarresi
 */

#include "filesystem.h"
#include "error.h"
#include <string>

/**
 * @brief Constructor for the fileSystem class.
 *
 * Initializes the file system by mounting the filesystem.
 * If mounting fails, it tries to format the filesystem and mount again.
 * If both operations fail, it calls the errorHandler function.
 */
fileSystem::fileSystem()
{
    flash_init();
    int res = lfs_mount(&lfs, &w25q64_cfg);
    if (res < 0)
    {
        // If the mount fails, try formatting the filesystem
        res = lfs_format(&lfs, &w25q64_cfg);
        if (res < 0)
        {
            errorHandler(__FILE__, __LINE__, ERROR_FATAL, "unable to format filesystem");
        }

        // Try mounting again
        res = lfs_mount(&lfs, &w25q64_cfg);
        if (res < 0)
        {
            errorHandler(__FILE__, __LINE__, ERROR_FATAL, "unable to mount filesystem");
        }
    }
}

void fileSystem::switchConfig(FileSystemConfig config)
{
 if (FileSystemConfig::SD_CARD == config)
 {
	 current_config = &sd_cfg;
 }
 else if (FileSystemConfig::W25Q64 == config)
 {
	 current_config = &w25q64_cfg;
 }
}

/**
 * @brief Get the singleton instance of the fileSystem class.
 *
 * @return A reference to the fileSystem instance.
 */
fileSystem& fileSystem::getInstance()
{
    static fileSystem instance;
    return instance;
}

/**
 * @brief Write data to a file.
 *
 * @param fileName The name of the file.
 * @param data The data to write to the file.
 * @return The result of the write operation (fileSystemReturnType).
 */
fileSystemReturnType fileSystem::write(const char *fileName, const char *data)
{
    if (fileName == nullptr || data == nullptr)
    {
        errorHandler(__FILE__, __LINE__, ERROR_FATAL, "NULL POINTER");
    }

    int res;
    lfs_file_t file;

    res = lfs_file_open(&lfs, &file, fileName, LFS_O_WRONLY | LFS_O_CREAT);

    if (res < 0)
    {
        return fileSystemReturnType::errorOpeningFile;
    }

    res = lfs_file_write(&lfs, &file, data, strlen(data));

    res = lfs_file_close(&lfs, &file);

    return fileSystemReturnType::noError;
}

/**
 * @brief Read data from a file.
 *
 * @param fileName The name of the file to read from.
 * @param buffer The buffer to store the read data.
 * @param sizeToRead The size to read from the file.
 * @return The result of the read operation (fileSystemReturnType).
 */
fileSystemReturnType fileSystem::read(const char *fileName, char *buffer, size_t sizeToRead)
{
    if (fileName == nullptr || buffer == nullptr)
    {
        errorHandler(__FILE__, __LINE__, ERROR_FATAL, "NULL POINTER");
    }

    int res;
    lfs_file_t file;

    res = lfs_file_open(&lfs, &file, fileName, LFS_O_RDONLY);

    if (res < 0)
    {
        return fileSystemReturnType::errorOpeningFile;
    }

    res = lfs_file_read(&lfs, &file, buffer, sizeToRead);

    res = lfs_file_close(&lfs, &file);

    return fileSystemReturnType::noError;
}

/**
 * @brief Erase a file.
 *
 * @param fileName The name of the file to erase.
 * @return The result of the erase operation (fileSystemReturnType).
 */
fileSystemReturnType fileSystem::erase(const char* fileName)
{
    if (fileName == nullptr)
    {
        errorHandler(__FILE__, __LINE__, ERROR_FATAL, "NULL POINTER");
    }

    int res = lfs_remove(&lfs, fileName);

    if (res < 0)
    {
        return fileSystemReturnType::errorErasingFile;
    }

    return fileSystemReturnType::noError;
}

/**
 * @brief Calculate the used space in the file system.
 *
 * @return The used space in bytes.
 */
lfs_soff_t fileSystem::calculateUsedSpace()
{
    lfs_soff_t totalSize = 0;
    lfs_dir_t dir;
    lfs_dir_open(&lfs, &dir, "/");

    struct lfs_info info;
    while (lfs_dir_read(&lfs, &dir, &info) == 1) {
        if(info.type == LFS_TYPE_REG) { // Regular file
            totalSize += info.size;
        }
    }

    lfs_dir_close(&lfs, &dir);

    return totalSize;
}

/**
 * @brief Calculate the free space in the file system.
 *
 * @return The free space in bytes.
 */
lfs_soff_t fileSystem::calculateFreeSpace()
{
    lfs_soff_t totalSpace = w25q64_cfg.block_count * w25q64_cfg.block_size; // total space
    lfs_soff_t usedSpace = calculateUsedSpace();

    return totalSpace - usedSpace;
}

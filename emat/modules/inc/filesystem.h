/*
 * filesystem.h
 *
 *  Created on: May 19, 2023
 *      Author: renatobarresi
 */

#pragma once
#ifdef __cplusplus

#include "littleFSInterface.h"
#include <cstdint>

/**
 * @brief Enumeration representing the state of the file system.
 */
enum class fileSystemState
{
    Uninitialized, /**< File system is uninitialized. */
    Initialized /**< File system is initialized. */
};

/**
 * @brief Enumeration representing the return types of file system operations.
 */
enum class fileSystemReturnType
{
    errorOpeningFile, /**< Error occurred while opening a file. */
    errorWritingFile, /**< Error occurred while writing to a file. */
    errorReadingFile, /**< Error occurred while reading from a file. */
    errorClosingFile, /**< Error occurred while closing a file. */
    errorErasingFile, /**< Error occurred while erasing a file. */
    noError /**< No error occurred. */
};

/**
 * @brief Class representing the file system.
 */
class fileSystem
{
public:
    /**
     * @brief Get the singleton instance of the fileSystem class.
     *
     * @return A reference to the fileSystem instance.
     */
    static fileSystem& getInstance();

    /**
     * @brief Write data to a file.
     *
     * @param fileName The name of the file.
     * @param data The data to write to the file.
     * @return The result of the write operation (fileSystemReturnType).
     */
    fileSystemReturnType write(const char *fileName, const char *data);

    /**
     * @brief Read data from a file.
     *
     * @param fileName The name of the file to read from.
     * @param buffer The buffer to store the read data.
     * @param sizeToRead The size to read from the file.
     * @return The result of the read operation (fileSystemReturnType).
     */
    fileSystemReturnType read(const char *fileName, char *buffer, size_t sizeToRead);

    /**
     * @brief Erase a file.
     *
     * @param fileName The name of the file to erase.
     * @return The result of the erase operation (fileSystemReturnType).
     */
    fileSystemReturnType erase(const char* fileName);

    /**
     * @brief Calculate the used space in the file system.
     *
     * @return The used space in bytes.
     */
    lfs_soff_t calculateUsedSpace();

    /**
     * @brief Calculate the free space in the file system.
     *
     * @return The free space in bytes.
     */
    lfs_soff_t calculateFreeSpace();

private:
    lfs_t lfs; /**< LittleFS object. */
    fileSystemState state; /**< State of the file system. */

    /**
     * @brief Constructor for the fileSystem class.
     *
     * Initializes the file system by mounting the filesystem.
     * If mounting fails, it tries to format the filesystem and mount again.
     * If both operations fail, it calls the errorHandler function.
     */
    fileSystem();
};

#endif

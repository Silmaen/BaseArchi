/**
 * @file utils.h
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#ifdef ARDUINO_ARCH_AVR
#include <stdint.h>
#else
#include <cstdint>
#endif

/**
 * @brief Namespace for i2c devices
 */
namespace sbs::io::i2c {

/**
 * @brief Activate or deactivate the emulated i2c mode
 * @param emulated the mode
 */
void setEmulatedMode(bool emulated);

/**
 * @brief Define the content of the emulated read buffer
 * @param size Buffer size
 * @param buffer Buffer content
 */
void setEmulatedBuffer(uint8_t size, uint8_t* buffer);

/**
 * \brief \brief Write one byte at the given register
 * \param address Device's address
 * \param reg The register to read
 * \param value tThe value to write
 */
void writeCommand(uint8_t address,  uint8_t reg, uint8_t value);

/**
 * \brief Read one byte at the given register in the given device
 * \param address Device's address
 * \param reg The register to read
 * \return The content of the byte
 */
[[nodiscard]] uint8_t read8(uint8_t address, uint8_t reg) ;

/**
 * \brief Read one byte at the given register in the given device
 * \param address Device's address
 * \param reg The register to read
 * \return The value as signed integer
 */
[[nodiscard]] int8_t readS8(uint8_t address, uint8_t reg);

/**
 * @brief Read bytes at the given register in the given device
 * @param address  Device's address
 * @param reg The starting register to read
 * @param size The amount of byte to read
 * @param output The read bytes
 * @param lowFirst If true the lowest byte is get first
 */
void read(uint8_t address, uint8_t reg, uint8_t size, uint8_t* output, bool lowFirst = false);

/**
 * \brief Read the 2 bytes at the given register in the given device
 * \param address Device's address
 * \param reg The register to read
 * \param lowFirst If true the lowest byte is get first
 * \return The value as unsigned integer
 */
[[nodiscard]] uint16_t read16(uint8_t address, uint8_t reg, bool lowFirst = false) ;

/**
 * \brief Read the 2 bytes at the given register in the given device
 * \param address Device's address
 * \param reg The register to read
 * \param lowFirst If true the lowest byte is get first
 * \return The value as signed integer
 */
[[nodiscard]] int16_t readS16(uint8_t address, uint8_t reg, bool lowFirst = false) ;

/**
 * \brief Read the 3 bytes at the given register in the given device
 * \param address Device's address
 * \param reg The register to read
 * \param lowFirst If true the lowest byte is get first
 * \return The value as unsigned integer
 */
[[nodiscard]] uint32_t read24(uint8_t address, uint8_t reg, bool lowFirst = false) ;

/**
 * \brief Read the 3 bytes at the given register in the given device
 * \param address Device's address
 * \param reg The register to read
 * \param lowFirst If true the lowest byte is get first
 * \return The value as signed integer
 */
[[nodiscard]] int32_t readS24(uint8_t address, uint8_t reg, bool lowFirst = false) ;

/**
 * \brief Read the 4 bytes at the given register in the given device
 * \param address Device's address
 * \param reg The register to read
 * \param lowFirst If true the lowest byte is get first
 * \return The value as unsigned integer
 */
[[nodiscard]] uint32_t read32(uint8_t address, uint8_t reg, bool lowFirst = false) ;

/**
 * \brief Read the 4 bytes at the given register in the given device
 * \param address Device's address
 * \param reg The register to read
 * \param lowFirst If true the lowest byte is get first
 * \return The value as signed integer
 */
[[nodiscard]] int32_t readS32(uint8_t address, uint8_t reg, bool lowFirst = false) ;

}

/**
 * @file timing.h
 * @author argawaen
 * @date 06/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <cstdint>

/**
 * @brief Namespace gathering the time functions
 */
namespace sbs::time {
/**
 * @brief Get the amount milliseconds since start of program
 * @return The milliseconds since start of program
 */
uint32_t millis();

/**
 * @brief Get the amount microseconds since start of program
 * @return The microseconds since start of program
 */
uint32_t micros();

/**
 * @brief Get the amount microseconds since start of program
 * @return The microseconds since start of program
 */
uint64_t micros64();

/**
 * @brief Wait before next execution
 * @param milli Amount of millisecond to wait
 */
void delay(uint32_t milli);

/**
 * @brief Wait before next execution
 * @param micro Amount of microsecond to wait
 */
void delayMicroseconds(uint32_t micro);

}// namespace sbs::time

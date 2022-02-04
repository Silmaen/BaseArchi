/**
 * @file utils.h
 * @author argawaen
 * @date 02/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <cstdint>

/**
 * @brief Namespace for time management
 */
namespace sys::time {

/**
 * @brief Get milliseconds since the system start
 * @return Milliseconds since the system start
 */
uint32_t millis();
/**
 * @brief Get microseconds since the system start
 * @return Microseconds since the system start
 */
uint32_t micros();
/**
 * @brief Get microseconds since the system start
 * @return Microseconds since the system start
 */
uint64_t micros64();
/**
 * @brief Stop execution for some time
 * @param mSec Amount of milliseconds to wait
 */
void delay(uint32_t mSec);
/**
 * @brief Stop execution for some time
 * @param uSec Amount of microseconds to wait
 */
void delayMicroseconds(uint32_t uSec);

}// namespace sys::time

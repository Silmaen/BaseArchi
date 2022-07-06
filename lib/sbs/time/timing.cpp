/**
 * @file timing.cpp
 * @author Silmaen
 * @date 06/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "timing.h"
#include <chrono>

namespace sbs::time {

/// Clock used in the next routines
using internal_clock = std::chrono::high_resolution_clock;

/// Alias for the time point
using time_point = internal_clock::time_point;

/// Alias for milliseconds
using milliseconds = std::chrono::milliseconds;

/// Alias for microseconds
using microseconds = std::chrono::microseconds;

/// Save of the program start date
static const time_point startingPoint = internal_clock::now();

uint32_t millis() {
    return std::chrono::duration_cast<milliseconds>(internal_clock::now() - startingPoint).count();
}

uint32_t micros() { return micros64(); }

uint64_t micros64() {
    return std::chrono::duration_cast<microseconds>(internal_clock::now() - startingPoint).count();
}

void delay(uint32_t milli) {
    time_point start = internal_clock::now();
    while (std::chrono::duration_cast<milliseconds>(internal_clock::now() - start).count() < milli)
        ;
}

void delayMicroseconds(uint32_t micro) {
    time_point start = internal_clock::now();
    while (std::chrono::duration_cast<microseconds>(internal_clock::now() - start).count() < micro)
        ;
}

}// namespace sbs::time

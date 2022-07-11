/**
 * @file timing.cpp
 * @author Silmaen
 * @date 06/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "timing.h"
#ifdef NATIVE
#include <chrono>
#else
#include <Arduino.h>
#endif

namespace sbs::time {

#ifdef NATIVE
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
#endif

uint32_t millis() {
#ifdef NATIVE
    return std::chrono::duration_cast<milliseconds>(internal_clock::now() - startingPoint).count();
#else
    return ::millis();
#endif
}

uint32_t micros() { return micros64(); }

uint64_t micros64() {
#ifdef NATIVE
    return std::chrono::duration_cast<microseconds>(internal_clock::now() - startingPoint).count();
#else
    return ::micros();
#endif
}

void delay(uint32_t milli) {
#ifdef NATIVE
    time_point start = internal_clock::now();
    while (std::chrono::duration_cast<milliseconds>(internal_clock::now() - start).count() < milli)
        ;
#else
    ::delay(milli);
#endif
}

void delayMicroseconds(uint32_t micro) {
#ifdef NATIVE
    time_point start = internal_clock::now();
    while (std::chrono::duration_cast<microseconds>(internal_clock::now() - start).count() < micro)
        ;
#else
    ::delayMicroseconds(micro);
#endif
}

}// namespace sbs::time

/**
 * @file utils.cpp
 * @author argawaen
 * @date 02/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "utils.h"
#ifdef ARDUINO
#ifdef ESP8266
#include <core_esp8266_features.h>
#endif
#ifdef ARDUINO_ARCH_SAMD
#include <api/Common.h>
#endif
#ifdef ARDUINO_ARCH_AVR
#include <Arduino.h>
#endif
#else
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::milliseconds;
/// Clock's type
using sysClock = std::chrono::high_resolution_clock;
/// Initial starting time
static const sysClock::time_point startPoint = sysClock::now();
#endif


namespace sys::time {

uint32_t millis() {
#ifdef ARDUINO
    return ::millis();
#else
    return duration_cast<milliseconds>(sysClock::now() - startPoint).count();
#endif
}

uint32_t micros() {
#ifdef ARDUINO
    return ::micros();
#else
    return duration_cast<microseconds>(sysClock::now() - startPoint).count();
#endif
}

uint64_t micros64() {
#ifdef ARDUINO
#ifdef ESP8266
    return ::micros64();
#else
    return ::micros();
#endif
#else
    return duration_cast<microseconds>(sysClock::now() - startPoint).count();
#endif
}

void delay(uint32_t mSec) {
#ifdef ARDUINO
    ::delay(mSec);
#else
    sysClock::time_point start = sysClock::now();
    while (duration_cast<milliseconds>(sysClock::now() - start).count() < mSec) {}
#endif
}

void delayMicroseconds(uint32_t uSec) {
#ifdef ARDUINO
    ::delayMicroseconds(uSec);
#else
    sysClock::time_point start = sysClock::now();
    while (duration_cast<microseconds>(sysClock::now() - start).count() < uSec) {}
#endif
}

}// namespace sys::time
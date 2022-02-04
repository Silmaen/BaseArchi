/**
 * @file time.cpp
 * @author argawaen
 * @date 02/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../testBase.h"
#include <time/utils.h>

void utils_timing() {
    uint32_t milli   = sys::time::millis();
    uint32_t micro   = sys::time::micros();
    uint64_t micro64 = sys::time::micros64();
    sys::time::delay(10);
    uint32_t n_milli   = sys::time::millis();
    uint32_t n_micro   = sys::time::micros();
    uint64_t n_micro64 = sys::time::micros64();
    TEST_ASSERT_UINT32_WITHIN(1, 10, n_milli - milli);
    TEST_ASSERT_UINT32_WITHIN(30, 10030, n_micro - micro);
    TEST_ASSERT_UINT32_WITHIN(30, 10030, n_micro64 - micro64);
    sys::time::delayMicroseconds(100);
    n_milli   = sys::time::millis();
    n_micro   = sys::time::micros();
    n_micro64 = sys::time::micros64();
    TEST_ASSERT_UINT32_WITHIN(1, 10, n_milli - milli);
    TEST_ASSERT_UINT32_WITHIN(60, 10160, n_micro - micro);
    TEST_ASSERT_UINT32_WITHIN(60, 10160, n_micro64 - micro64);
}

void runTests() {
    UNITY_BEGIN();
    RUN_TEST(utils_timing);
    UNITY_END();
}
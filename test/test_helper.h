/**
 * @file test_helper.h
 * @author Silmaen
 * @date 17/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <sbs.h>
#include <unity.h>

#ifdef NATIVE
#include <iostream>
#include <sstream>

namespace testHelper {
[[maybe_unused]] static std::streambuf* old = nullptr;
[[maybe_unused]] static std::stringstream buffer;
}// namespace testHelper

#define SBS_REDIRECT_OUT                                               \
    if (testHelper::old == nullptr) {                                  \
        testHelper::old = std::cout.rdbuf(testHelper::buffer.rdbuf()); \
        testHelper::buffer.str("");                                    \
    }
#define SBS_RESET_OUT                     \
    if (testHelper::old != nullptr) {     \
        std::cout.rdbuf(testHelper::old); \
        testHelper::buffer.str("");       \
        testHelper::old = nullptr;        \
    }
#define SBS_TEST_OUT(X) TEST_ASSERT_EQUAL_STRING(X, testHelper::buffer.str().c_str());
#else
#define SBS_REDIRECT_OUT
#define SBS_RESET_OUT
#define SBS_TEST_OUT(X)
#endif

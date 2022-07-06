/**
 * @file test_time.cpp
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "../test_base.h"
#include "timing_utest.h"

int runtest(){
    UNITY_BEGIN();
    RUN_TEST(timing);
    return UNITY_END();
}

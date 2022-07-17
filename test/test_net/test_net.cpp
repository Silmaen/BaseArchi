/**
 * @file test_core.cpp
 * @author Silmaen
 * @date 17/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "../test_base.h"
#include "address_utest.h"

int runtest(){
    UNITY_BEGIN();
    RUN_TEST(ipAddress_test);
    RUN_TEST(macAddress_test);
    return UNITY_END();
}

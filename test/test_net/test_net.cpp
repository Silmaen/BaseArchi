/**
 * @file test_core.cpp
 * @author Silmaen
 * @date 17/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "../test_base.h"
#include "address_utest.h"
#include "wifi_utest.h"

int runtest(){
    UNITY_BEGIN();
    run_address();
    run_wifi();
    return UNITY_END();
}

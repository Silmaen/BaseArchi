/**
 * @file test_time.cpp
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "../test_base.h"
#include "bme280_utest.h"
#include "device_utest.h"

int runtest(){
    UNITY_BEGIN();
    run_device();
    run_bme280();
    return UNITY_END();
}

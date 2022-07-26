/**
 * @file test_time.cpp
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "../test_base.h"
#include "mkrenv_utest.h"
#include "batteryMonitor_utest.h"

int runtest(){
    UNITY_BEGIN();
    run_mkrenv();
    run_battmot();
    return UNITY_END();
}

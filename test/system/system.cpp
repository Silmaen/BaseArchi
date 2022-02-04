/**
 * @file system.cpp
 * @author argawaen
 * @date 04/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../testBase.h"
#include <base/System.h>

void System_constructor(){
    sys::base::System hardware;
    hardware.setup();
    TEST_ASSERT_FALSE(hardware.doReset())
    hardware.loop();
    hardware.requestReset();
    TEST_ASSERT(hardware.doReset())
    class StringOutput: public sys::io::Output{};
    hardware.pushOutput(StringOutput());
}

void runTests(){
    UNITY_BEGIN();
    RUN_TEST(System_constructor);
    UNITY_END();
}

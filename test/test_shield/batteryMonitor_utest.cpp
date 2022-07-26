/**
 * @file batteryMonitor_utest.cpp
 * @author Silmaen
 * @date 26/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include "core/Print.h"
#include "io/i2c/utils.h"
#include "shield/BatteryMonitor.h"

void battmot_base() {
    sbs::shield::BatteryMonitor device;
    TEST_ASSERT_EQUAL(sbs::shield::BatteryMonitor::Status::Disabled, device.getStatus());
    TEST_ASSERT_EQUAL(0, device.getInputVoltage());
    TEST_ASSERT_EQUAL(0, device.getBatteryPercent());

    sbs::shield::BatteryMonitor device2{1,4,0};
    device2.init();
    TEST_ASSERT_EQUAL(sbs::shield::BatteryMonitor::Status::Disabled, device.getStatus());
}

/**
 * @file bme280_utest.cpp
 * @author Silmaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include "io/i2c/utils.h"
#include "sensor/Veml6075.h"

void veml6075_base() {
    sbs::sensor::Veml6075 device;
    TEST_ASSERT_EQUAL_STRING("VEML6075", device.getName().c_str());
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, data.uva);
}
void veml6075_emulated() {
    sbs::sensor::Veml6075 device;
    sbs::io::i2c::setEmulatedMode(true);
    uint8_t buffer[] = {0x26, 0x00, 0x26, 0x00};
    sbs::io::i2c::setEmulatedBuffer(4, buffer);
    device.selfCheck();
    TEST_ASSERT_TRUE(device.presence());
    uint8_t buffer2[] = {0x10, 0x01, 0x10, 0x01, 0x07, 0x00, 0x07, 0x00};
    sbs::io::i2c::setEmulatedBuffer(8, buffer2);
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 247.15, data.uva);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 239.17, data.uvb);
    sbs::io::i2c::setEmulatedMode(false);
}

void veml6075_result() {
    using Data = sbs::sensor::Veml6075::SensorData;
    Data result{10.0, 12.0};
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.022851, result.getUVIndex());
}

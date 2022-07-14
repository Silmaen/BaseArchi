/**
 * @file bme280_utest.cpp
 * @author Silmaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include "io/i2c/utils.h"
#include "sensor/Hts221.h"

void hts221_base() {
    sbs::sensor::Hts221 device;
    TEST_ASSERT_EQUAL_STRING("HTS221", device.getName().c_str());
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, data.temperature);
}
void hts221_emulated() {
    sbs::sensor::Hts221 device;
    sbs::io::i2c::setEmulatedMode(true);
    uint8_t buffer[] = {0xBC, 0xBC,
                        0x3A, 0x85,
                        0xA6, 0xC4, 0x16, 0xC4,
                        0xF3, 0xFF, 0x88, 0xCF,
                        0xFD, 0xFF, 0xFB, 0x02};
    sbs::io::i2c::setEmulatedBuffer(16, buffer);
    device.selfCheck();
    TEST_ASSERT_TRUE(device.presence());
    uint8_t buffer2[] = {0x01, 0x00, 0x01, 0x00, 0x58, 0x02, 0x1E, 0xE8};
    sbs::io::i2c::setEmulatedBuffer(8, buffer2);
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 31.7708877, data.temperature);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 47.4580476, data.humidity);
    sbs::io::i2c::setEmulatedMode(false);
}

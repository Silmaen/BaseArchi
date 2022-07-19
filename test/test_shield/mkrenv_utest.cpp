/**
 * @file bme280_utest.cpp
 * @author Silmaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include "core/Print.h"
#include "io/i2c/utils.h"
#include "shield/MKREnv.h"

void mkrenv_base() {
    sbs::shield::MKREnv device;
    TEST_ASSERT_EQUAL(sbs::io::baseDevice::Protocol::Shield, device.getProtocol());
    TEST_ASSERT_EQUAL(2, device.checkVersion());
    TEST_ASSERT_FALSE(device.checkPresence());
}

void mkrenv_emulated() {
    sbs::shield::MKREnv device;
    sbs::io::i2c::setEmulatedMode(true);
    uint8_t buffer[] = {0xBC, 0xBC, 0x3A, 0x85, 0xA6, 0xC4, 0x16, 0xC4,
                        0xF3, 0xFF, 0x88, 0xCF, 0xFD, 0xFF, 0xFB, 0x02,
                        0x3A, 0x85, 0xA6, 0xC4, 0x16, 0xC4,
                        0xF3, 0xFF, 0x88, 0xCF, 0xFD, 0xFF, 0xFB, 0x02,
                        0xB1, 0xB1, 0x26, 0x00, 0x26, 0x00};
    sbs::io::i2c::setEmulatedBuffer(36, buffer);
    device.init();
    uint8_t buffer2[] = {
            0x01,
            0x00,
            0x01,
            0x00,
            0x58,
            0x02,
            0x1E,
            0xE8,
            0x01,
            0x00,
            0xE2,
            0xF8,
            0x3D,
            0xD9,
            0x0A,
            0x10,
            0x01,
            0x10,
            0x01,
            0x07,
            0x00,
            0x07,
            0x00,
    };
    sbs::io::i2c::setEmulatedBuffer(23, buffer2);
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 29.7704439, data.temperature);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 991.555176, data.pressure);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 47.4580476, data.humidity);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 247.15, data.UVa);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 239.17, data.UVb);
    sbs::io::i2c::setEmulatedMode(false);
}

void mkrenv_result() {
    using Data = sbs::shield::MKREnv::ShieldData;
    Data result{30.0, 986.0926125, 45.3, 145.0, 123.0, 210.0};
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 45.3, result.humidity);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 1020, result.getQnh(300));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 300, result.getAltitude(1020));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 16.8748892, result.getDewPoint());
}

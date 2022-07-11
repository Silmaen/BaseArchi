/**
 * @file bme280_utest.cpp
 * @author argawaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include "io/i2c/utils.h"
#include "sensor/Lps22hb.h"

void lps22hb_base(){
    sbs::sensor::Lps22hb device;
    TEST_ASSERT_EQUAL_STRING("LPS22HB", device.getName().c_str());
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001,0.0,data.temperature);
}
void lps22hb_emulated(){
    sbs::sensor::Lps22hb device;
    sbs::io::i2c::setEmulatedMode(true);
    uint8_t buffer[] = {0xb1,0xb1};
    sbs::io::i2c::setEmulatedBuffer(2, buffer);
    device.selfCheck();
    TEST_ASSERT_TRUE(device.presence());
    uint8_t buffer2[] = {0x01, 0x00,0xE2,0xF8,0x3D,0xD9,0x0A};
    sbs::io::i2c::setEmulatedBuffer(7, buffer2);
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 27.77,data.temperature);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 991.555176,data.pressure);
    sbs::io::i2c::setEmulatedMode(false);
}

void lps22hb_result(){
    using Data = sbs::sensor::Lps22hb::SensorData;
    Data result{30.0, 986.0926125};
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 1020, result.getQnh(300));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 300, result.getAltitude(1020));
}

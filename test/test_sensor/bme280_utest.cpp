/**
 * @file bme280_utest.cpp
 * @author Silmean
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include "io/i2c/utils.h"
#include "sensor/Bme280.h"

void bme280_base(){
    sbs::sensor::BME280 device;
    TEST_ASSERT_EQUAL_STRING("BME280", device.getName().c_str());
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001,0.0,data.temperature);
}
void bme280_emulated(){
    sbs::sensor::BME280 device;
    sbs::io::i2c::setEmulatedMode(true);
    uint8_t buffer[] = {0x60,0x60,
            0xB4,0x6F,0x38,0x68,0x32,0x00,0x59,0x8E,0x06,0xD7,0xD0,0x0B,0xF0,0x20,0x97,0xFF,0xF9,0xFF,0xAC,0x26,0x0A,0xD8,0xBD,0x10,0x4B,
            0x83,0x01,0x00,0x10,0x26,0x03,0x1E,
    };
    sbs::io::i2c::setEmulatedBuffer(34, buffer);
    device.selfCheck();
    TEST_ASSERT_TRUE(device.presence());
    uint8_t buffer2[] = {0x01, 0x00,0x52,0x6C,0x00,0x84,0xF8,0x00,0x61,0x41};
    sbs::io::i2c::setEmulatedBuffer(10, buffer2);
    auto data = device.getValue();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 27.772465,data.temperature);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 991.555407,data.pressure);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001,  47.8610955,data.humidity);
    sbs::io::i2c::setEmulatedMode(false);
}

void bme280_settings(){
    using Setting = sbs::sensor::BME280::Setting;
    {
        Setting setting = Setting::getPredefined(Setting::PredefinedSettings::Gaming);
        TEST_ASSERT_EQUAL(0b00001011, setting.maxMeasurementTime());
        TEST_ASSERT_EQUAL(0b00010000, setting.toConfigReg());
        TEST_ASSERT_EQUAL(0b00000000, setting.toCtrlHumReg());
        TEST_ASSERT_EQUAL(0b00101111, setting.toCtrlMeasReg());
    }
    {
        Setting setting = Setting::getPredefined(Setting::PredefinedSettings::IndoorNavigation);
        TEST_ASSERT_EQUAL(0b00010101, setting.maxMeasurementTime());
        TEST_ASSERT_EQUAL(0b00010000, setting.toConfigReg());
        TEST_ASSERT_EQUAL(0b00000001, setting.toCtrlHumReg());
        TEST_ASSERT_EQUAL(0b01010111, setting.toCtrlMeasReg());
    }
    {
        Setting setting = Setting::getPredefined(Setting::PredefinedSettings::HumiditySensing);
        TEST_ASSERT_EQUAL(0b00000110, setting.maxMeasurementTime());
        TEST_ASSERT_EQUAL(0b00000000, setting.toConfigReg());
        TEST_ASSERT_EQUAL(0b00000001, setting.toCtrlHumReg());
        TEST_ASSERT_EQUAL(0b00100001, setting.toCtrlMeasReg());
    }

    {
        Setting setting = Setting::getPredefined(Setting::PredefinedSettings{-1});
        TEST_ASSERT_EQUAL(0b00001001, setting.maxMeasurementTime());
        TEST_ASSERT_EQUAL(0b00000000, setting.toConfigReg());
        TEST_ASSERT_EQUAL(0b00000001, setting.toCtrlHumReg());
        TEST_ASSERT_EQUAL(0b00100101, setting.toCtrlMeasReg());
    }
}


void bme280_result(){
    using Data = sbs::sensor::BME280::SensorData;
    Data result{30.0, 54.3, 986.0926125};
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 1020, result.getQnh(300));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 300, result.getAltitude(1020));
}

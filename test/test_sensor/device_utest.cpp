/**
 * @file device_utest.cpp
 * @author argawaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include "io/baseDevice.h"
#include "io/i2c/Device.h"
#include "io/i2c/utils.h"

void device_base_tests(){
  sbs::io::baseDevice device;
  TEST_ASSERT_EQUAL_STRING("Unknown Device", device.getName().c_str());
  TEST_ASSERT_FALSE(device.presence());
  TEST_ASSERT_EQUAL(sbs::io::baseDevice::Protocol::Unknown, device.getProtocol());
  device.selfCheck();
  TEST_ASSERT_FALSE(device.presence());
  device.fakePresence = true;
  device.selfCheck();
  TEST_ASSERT_TRUE(device.presence());
  device.fakePresence = false;
  device.selfCheck();
  TEST_ASSERT_FALSE(device.presence());

}

void device_i2c_base_tests(){
    sbs::io::i2c::Device device(0xFF);
    TEST_ASSERT_EQUAL_STRING("Unknown I2C Device", device.getName().c_str());
    TEST_ASSERT_EQUAL(0xFF, device.getAddress());
    device.setAddress(0x00);
    TEST_ASSERT_EQUAL(0x00, device.getAddress());
    TEST_ASSERT_FALSE(device.presence());
    TEST_ASSERT_EQUAL(sbs::io::baseDevice::Protocol::I2C, device.getProtocol());
    device.selfCheck();
    TEST_ASSERT_FALSE(device.presence());
    device.fakePresence = true;
    device.selfCheck();
    TEST_ASSERT_TRUE(device.presence());
    device.fakePresence = false;
    device.selfCheck();
    TEST_ASSERT_FALSE(device.presence());

}

void i2c_base_tests() {
    sbs::io::i2c::writeCommand(0x00,0x00,0x00);
    TEST_ASSERT_EQUAL(0x00, sbs::io::i2c::readS32(0x00, 0x00));
    TEST_ASSERT_EQUAL(0x00, sbs::io::i2c::readS32(0x00, 0x00,true));
    TEST_ASSERT_EQUAL(0x00, sbs::io::i2c::readS24(0x00, 0x00));
    TEST_ASSERT_EQUAL(0x00, sbs::io::i2c::readS16(0x00, 0x00));
    TEST_ASSERT_EQUAL(0x00, sbs::io::i2c::readS8(0x00, 0x00));
}


void i2c_emulated_tests() {
    uint8_t buffer[14] = {0x12,0x34,0x56,0x78,
                          0x12,0x34,0x65,0x78,
                          0x12,0x34,0x56,
                          0x12,0x34,
                          0x12};
    sbs::io::i2c::setEmulatedBuffer(14,buffer);
    sbs::io::i2c::setEmulatedMode(true);
    sbs::io::i2c::setEmulatedBuffer(14,buffer);
    TEST_ASSERT_EQUAL(0x12345678, sbs::io::i2c::readS32(0x00, 0x00));
    TEST_ASSERT_EQUAL(0x78653412, sbs::io::i2c::readS32(0x00, 0x00,true));
    TEST_ASSERT_EQUAL(0x123456, sbs::io::i2c::readS24(0x00, 0x00));
    TEST_ASSERT_EQUAL(0x1234, sbs::io::i2c::readS16(0x00, 0x00));
    TEST_ASSERT_EQUAL(0x12, sbs::io::i2c::readS8(0x00, 0x00));
    TEST_ASSERT_EQUAL(0x00, sbs::io::i2c::readS8(0x00, 0x00));
    sbs::io::i2c::setEmulatedMode(false);
}
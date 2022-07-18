/**
 * @file bq24195l_utest.cpp
 * @author Silmaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include "io/i2c/utils.h"
#include "sensor/Bq24195l.h"

using namespace sbs::sensor;

void bq24195l_base(){
    Bq24195l device;
    TEST_ASSERT_EQUAL_STRING("BQ24195L", device.getName().c_str());
    sbs::io::i2c::setEmulatedMode(true);
    device.init();
    device.setChargingMode(Bq24195l::ChargingMode::Normal);
    // fault check
    TEST_ASSERT_EQUAL(Bq24195l::ThermalFault::Ok, device.getThermalFault());
    TEST_ASSERT_EQUAL(Bq24195l::ChargeFault::Ok, device.getChargeFault());
    TEST_ASSERT_FALSE(device.isWatchdogExpired());
    TEST_ASSERT_FALSE(device.isBatteryInOverVoltage());
    // status check
    TEST_ASSERT_EQUAL(Bq24195l::VBusStatus::unknown, device.getVbusStatus());
    TEST_ASSERT_EQUAL(Bq24195l::ChargeStatus::NotCharging, device.getChargeStatus());
    TEST_ASSERT_FALSE(device.isInDPM());
    TEST_ASSERT_FALSE(device.isPowerGood());
    TEST_ASSERT_FALSE(device.isInThermalRegulation());
    TEST_ASSERT_FALSE(device.isInVSYSRegulation());
    // settings should be default values
    TEST_ASSERT_EQUAL(0x30, device.getSettings().toInputSourceReg());
    TEST_ASSERT_EQUAL(0x1B, device.getSettings().toPowerOnReg());
    TEST_ASSERT_EQUAL(0x60, device.getSettings().toCurrentControlReg());
    TEST_ASSERT_EQUAL(0x11, device.getSettings().toPreChargeCurrentControlReg());
    TEST_ASSERT_EQUAL(0xB2, device.getSettings().toChargeVoltageReg());
    TEST_ASSERT_EQUAL(0x9A, device.getSettings().toChargeTimerReg());
    TEST_ASSERT_EQUAL(0x03, device.getSettings().toThermalReg());
    TEST_ASSERT_EQUAL(0x4B, device.getSettings().toMiscOpReg());
    uint8_t buffer[] = {0x23, 0x23};
    sbs::io::i2c::setEmulatedBuffer(2,buffer);
    device.init();
    // settings must be void except mandatory bits
    TEST_ASSERT_EQUAL(0, device.getSettings().toInputSourceReg());
    TEST_ASSERT_EQUAL(1, device.getSettings().toPowerOnReg());
    TEST_ASSERT_EQUAL(0, device.getSettings().toCurrentControlReg());
    TEST_ASSERT_EQUAL(0, device.getSettings().toPreChargeCurrentControlReg());
    TEST_ASSERT_EQUAL(0, device.getSettings().toChargeVoltageReg());
    TEST_ASSERT_EQUAL(0, device.getSettings().toChargeTimerReg());
    TEST_ASSERT_EQUAL(0, device.getSettings().toThermalReg());
    TEST_ASSERT_EQUAL(8, device.getSettings().toMiscOpReg());
    sbs::io::i2c::setEmulatedMode(false);
}

void bq24195l_emulated(){
    Bq24195l device;
    sbs::io::i2c::setEmulatedMode(true);
    uint8_t buffer[] = {0x23,0x23, 0x30, 0x1B, 0x60, 0x11, 0xB2, 0x9A, 0x03, 0x4B, 0xFF,
                        0b110, 0b101, 0xFF, 0b00100000, 0b00010000, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    sbs::io::i2c::setEmulatedBuffer(24, buffer);
    device.selfCheck();
    TEST_ASSERT_TRUE(device.presence());
    // settings should be default values
    TEST_ASSERT_EQUAL(0x30, device.getSettings().toInputSourceReg());
    TEST_ASSERT_EQUAL(0x1B, device.getSettings().toPowerOnReg());
    TEST_ASSERT_EQUAL(0x60, device.getSettings().toCurrentControlReg());
    TEST_ASSERT_EQUAL(0x11, device.getSettings().toPreChargeCurrentControlReg());
    TEST_ASSERT_EQUAL(0xB2, device.getSettings().toChargeVoltageReg());
    TEST_ASSERT_EQUAL(0x9A, device.getSettings().toChargeTimerReg());
    TEST_ASSERT_EQUAL(0x03, device.getSettings().toThermalReg());
    TEST_ASSERT_EQUAL(0x4B, device.getSettings().toMiscOpReg());

    // fault check
    TEST_ASSERT_EQUAL(Bq24195l::ThermalFault::Unknown, device.getThermalFault());
    TEST_ASSERT_EQUAL(Bq24195l::ThermalFault::UpperThresholdTemperature, device.getThermalFault());
    TEST_ASSERT_EQUAL(Bq24195l::ThermalFault::LowerThresholdTemperature, device.getThermalFault());
    TEST_ASSERT_EQUAL(Bq24195l::ChargeFault::ChargeSafetyTimeExpired, device.getChargeFault());
    TEST_ASSERT_EQUAL(Bq24195l::ChargeFault::ThermalShutDown, device.getChargeFault());
    TEST_ASSERT_EQUAL(Bq24195l::ChargeFault::InputOverVoltage, device.getChargeFault());
    TEST_ASSERT_TRUE(device.isWatchdogExpired());
    TEST_ASSERT_TRUE(device.isBatteryInOverVoltage());
    // status check
    TEST_ASSERT_EQUAL(Bq24195l::VBusStatus::otg, device.getVbusStatus());
    TEST_ASSERT_EQUAL(Bq24195l::ChargeStatus::ChargeTerminaison, device.getChargeStatus());
    TEST_ASSERT_TRUE(device.isInDPM());
    TEST_ASSERT_TRUE(device.isPowerGood());
    TEST_ASSERT_TRUE(device.isInThermalRegulation());
    TEST_ASSERT_TRUE(device.isInVSYSRegulation());
    sbs::io::i2c::setEmulatedMode(false);
}

void bq24195l_settings(){
    Bq24195l device;
    sbs::io::i2c::setEmulatedMode(true);
    uint8_t buffer[] = {0x23,0x23, 0x30, 0x1B, 0x60, 0x11, 0xB2, 0x9A, 0x03, 0x4B};
    sbs::io::i2c::setEmulatedBuffer(10, buffer);
    device.selfCheck();
    TEST_ASSERT_TRUE(device.presence());
    device.setChargingMode(Bq24195l::ChargingMode::Disconnected);
    TEST_ASSERT_TRUE(device.getSettings().batFetDisable);
    device.setChargingMode(Bq24195l::ChargingMode::Disable);
    TEST_ASSERT_FALSE(device.getSettings().batFetDisable);
    TEST_ASSERT_EQUAL(Bq24195l::Settings::ChargerConfiguration::disable, device.getSettings().chgConfig);
    device.setChargingMode(Bq24195l::ChargingMode::OTG);
    TEST_ASSERT_FALSE(device.getSettings().batFetDisable);
    TEST_ASSERT_EQUAL(Bq24195l::Settings::ChargerConfiguration::otg, device.getSettings().chgConfig);
    device.setChargingMode(Bq24195l::ChargingMode::Normal);
    TEST_ASSERT_EQUAL(Bq24195l::Settings::ChargerConfiguration::normal, device.getSettings().chgConfig);
    device.setChargingMode(static_cast<Bq24195l::ChargingMode>(-1));
    sbs::io::i2c::setEmulatedMode(false);
}

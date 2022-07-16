/**
 * @file Bq24195l.cpp
 * @author Silmaen
 * @date 15/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Bq24195l.h"
#include "io/i2c/utils.h"
#include "time/timing.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif

namespace sbs::sensor {
constexpr uint8_t defaultAddress = 0x6B;///< Default BQ24125L i2C address
constexpr uint8_t chipId         = 0x23;///< chip Id

Bq24195l::Bq24195l() :
    io::i2c::Device{defaultAddress} {
}

void Bq24195l::init() {
    Device::init();
#ifdef ARDUINO_ARCH_SAMD
    pinMode(PIN_USB_HOST_ENABLE, OUTPUT);
    digitalWrite(PIN_USB_HOST_ENABLE, LOW);
#if defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500)
    pinMode(PMIC_IRQ_PIN, INPUT_PULLUP);
#endif
#endif
    //check PMIC version
    if (!checkPresence()) {
        return;
    }
    ReadSettings();
}

bool Bq24195l::checkPresence() const {
    return getVersion() == chipId;
}

void Bq24195l::setChargingMode(const ChargingMode& mode) {
    if (!presence()) return;
    switch (mode) {
    case ChargingMode::Disconnected:
        settings.batFetDisable = true;
        break;
    case ChargingMode::Disable:
        settings.chgConfig = Settings::ChargerConfiguration::disable;
        settings.safetyTimer   = Settings::SafetyTimer::disable;
        settings.interruptMode = Settings::InterruptMode::none;
        settings.batFetDisable = false;
        break;
    case ChargingMode::Normal:
        settings.chgConfig = Settings::ChargerConfiguration::normal;
        // Enable Charge Termination Pin
        settings.safetyTimer = Settings::SafetyTimer::enable;
        // Enable Charge and Battery Fault Interrupt
        settings.interruptMode = Settings::InterruptMode::Both;
        settings.batFetDisable = false;
        break;
    case ChargingMode::OTG:
        settings.chgConfig = Settings::ChargerConfiguration::otg;
        // Disable Charge Termination Pin
        settings.safetyTimer = Settings::SafetyTimer::disable;
        // Enable Battery Fault interrupt and disable Charge Fault Interrupt
        settings.interruptMode = Settings::InterruptMode::BatFaultOnly;
        settings.batFetDisable = false;
        // wait for enable boost mode
        break;
    default:
        return;
    }
    ApplySettings();
    if (mode==ChargingMode::OTG)
        time::delay(500);
}

uint8_t Bq24195l::getVersion() const {
    return io::i2c::read8(getAddress(), Registers::PMIC_VERSION);
}

void Bq24195l::ReadSettings() {
    settings.fromInputSourceReg(io::i2c::read8(getAddress(), Registers::INPUT_SOURCE));
    settings.fromPowerOnReg(io::i2c::read8(getAddress(), Registers::POWERON_CONFIG));
    settings.fromCurrentControlReg(io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL));
    settings.fromPreChargeCurrentControlReg(io::i2c::read8(getAddress(), Registers::PRECHARGE_CURRENT_CONTROL));
    settings.fromChargeVoltageReg(io::i2c::read8(getAddress(), Registers::CHARGE_VOLTAGE_CONTROL));
    settings.fromChargeTimerReg(io::i2c::read8(getAddress(), Registers::CHARGE_TIMER_CONTROL));
    settings.fromThermalReg(io::i2c::read8(getAddress(), Registers::THERMAL_REG_CONTROL));
    settings.fromMiscOpReg(io::i2c::read8(getAddress(), Registers::MISC_CONTROL));
}

void Bq24195l::ApplySettings() {
    io::i2c::writeCommand(getAddress(), Registers::INPUT_SOURCE, settings.toInputSourceReg());
    io::i2c::writeCommand(getAddress(), Registers::POWERON_CONFIG, settings.toPowerOnReg());
    io::i2c::writeCommand(getAddress(), Registers::CHARGE_CURRENT_CONTROL, settings.toCurrentControlReg());
    io::i2c::writeCommand(getAddress(), Registers::PRECHARGE_CURRENT_CONTROL, settings.toPreChargeCurrentControlReg());
    io::i2c::writeCommand(getAddress(), Registers::CHARGE_VOLTAGE_CONTROL, settings.toChargeVoltageReg());
    io::i2c::writeCommand(getAddress(), Registers::CHARGE_TIMER_CONTROL, settings.toChargeTimerReg());
    io::i2c::writeCommand(getAddress(), Registers::THERMAL_REG_CONTROL, settings.toThermalReg());
    io::i2c::writeCommand(getAddress(), Registers::MISC_CONTROL, settings.toMiscOpReg());
}

// ----------------- FAULT REGISTER MANAGEMENT ------------------------

uint8_t Bq24195l::readFaultRegister() const {
    return io::i2c::read8(getAddress(), Registers::FAULT);
}

Bq24195l::ThermalFault Bq24195l::getThermalFault() const {
    auto fault = readFaultRegister() & 0b00000111;
    if (fault == 0b000)
        return ThermalFault::Ok;
    // Temperature Fault
    if (fault == 0b101)
        return ThermalFault::LowerThresholdTemperature;
    if (fault == 0b110)
        return ThermalFault::UpperThresholdTemperature;
    return ThermalFault::Unknown;
}

Bq24195l::ChargeFault Bq24195l::getChargeFault() const {
    auto fault = (readFaultRegister() & 0b00110000) >> 4;
    if (fault == 0x00)
        return ChargeFault::Ok;
    // Charge faults
    if (fault == 0b01)
        return ChargeFault::InputOverVoltage;
    if (fault == 0b10)
        return ChargeFault::ThermalShutDown;
    return ChargeFault::ChargeSafetyTimeExpired;
}

bool Bq24195l::isWatchdogExpired() const {
    if (!presence()) return false;
    return (readFaultRegister() & 0x80) != 0;
}

bool Bq24195l::isBatteryInOverVoltage() const {
    if (!presence()) return false;
    return (readFaultRegister() & 0x08) != 0;
}
// ----------------- STATUS REGISTER MANAGEMENT ------------------------

uint8_t Bq24195l::readSystemStatusRegister() const {
    return io::i2c::read8(getAddress(), Registers::SYSTEM_STATUS);
}

Bq24195l::VBusStatus Bq24195l::getVbusStatus() const {
    return static_cast<VBusStatus>((readSystemStatusRegister()&0b11000000)>>6);
}

Bq24195l::ChargeStatus Bq24195l::getChargeStatus() const {
    return static_cast<ChargeStatus>((readSystemStatusRegister()&0b00110000)>>4);
}

bool Bq24195l::isInDPM() const {
    return (readSystemStatusRegister()&0b00001000) != 0;
}

bool Bq24195l::isPowerGood() const {
    return (readSystemStatusRegister()&0b00000100) != 0;
}

bool Bq24195l::isInThermalRegulation() const {
    return (readSystemStatusRegister()&0b00000010) != 0;
}

bool Bq24195l::isInVSYSRegulation() const {
    return (readSystemStatusRegister()&0b00000001) != 0;
}

}// namespace sbs::sensor

/**
 * @file Bq24125l.cpp
 * @author Silmaen
 * @date 15/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Bq24125l.h"
#include "io/i2c/utils.h"
#include "math/base.h"
#include "time/timing.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef round
#define round(x) ((x) >= 0 ? (long) ((x) + 0.5) : (long) ((x) -0.5))
#endif


namespace sbs::sensor {
constexpr uint8_t defaultAddress = 0x6B;///< Default BQ24125L i2C address
constexpr uint8_t chipId         = 0x23;///< chip Id

Bq24125l::Bq24125l() :
    io::i2c::Device{defaultAddress} {
}

void Bq24125l::init() {
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
    // Sets the charge current to 100 mA
    return setChargeCurrent(0.01);
}

bool Bq24125l::checkPresence() const {
    return getVersion() == chipId;
}


void Bq24125l::setChargingMode(const ChargingMode& mode) {
    if (!presence()) return;
    switch (mode) {
    case ChargingMode::Disconnected:
        disableBATFET();
        break;
    case ChargingMode::Disable: {
        uint8_t mask = readPowerONRegister() & 0xCF;
        io::i2c::writeCommand(getAddress(), Registers::POWERON_CONFIG, mask);
        mask = readChargeTermRegister() & 0x7F;
        io::i2c::writeCommand(getAddress(), Registers::CHARGE_TIMER_CONTROL, mask);
        mask = readOpControlRegister() & 0xFC;
        io::i2c::writeCommand(getAddress(), Registers::MISC_CONTROL, mask);
        enableBATFET();
    } break;
    case ChargingMode::Normal: {
#ifdef ARDUINO_ARCH_SAMD
        digitalWrite(PIN_USB_HOST_ENABLE, LOW);
#endif
        uint8_t mask = readPowerONRegister() & 0xCF;
        // Enable PMIC Charge Mode
        io::i2c::writeCommand(getAddress(), Registers::POWERON_CONFIG, mask | 0x10);
        mask = readChargeTermRegister() & 0x7F;
        // Enable Charge Termination Pin
        io::i2c::writeCommand(getAddress(), Registers::CHARGE_TIMER_CONTROL, mask | 0x80);

        // Enable Charge and Battery Fault Interrupt
        mask = readOpControlRegister() & 0xFC;
        io::i2c::writeCommand(getAddress(), Registers::MISC_CONTROL, mask | 0x03);
        enableBATFET();
    } break;
    case ChargingMode::Boost: {
        uint8_t mask = readPowerONRegister() & 0xCF;
        // Enable PMIC Boost Mode
        io::i2c::writeCommand(getAddress(), Registers::POWERON_CONFIG, mask | 0x20);
#ifdef ARDUINO_ARCH_SAMD
        digitalWrite(PIN_USB_HOST_ENABLE, LOW);
#endif
        // Disable Charge Termination Pin
        mask = readChargeTermRegister() & 0x7F;
        io::i2c::writeCommand(getAddress(), Registers::CHARGE_TIMER_CONTROL, mask);

        // Enable Battery Fault interrupt and disable Charge Fault Interrupt
        mask = readOpControlRegister() & 0xFC;
        io::i2c::writeCommand(getAddress(), Registers::MISC_CONTROL, mask | 0x03);
        enableBATFET();
        // wait for enable boost mode
        time::delay(500);
    } break;
    }
}

void Bq24125l::enableCharge() {
    if (!presence()) return;
#ifdef ARDUINO_ARCH_SAMD
    digitalWrite(PIN_USB_HOST_ENABLE, LOW);
#endif
    uint8_t mask = readPowerONRegister() & 0xCF;
    // Enable PMIC Charge Mode
    io::i2c::writeCommand(getAddress(), Registers::POWERON_CONFIG, mask | 0x10);
    mask = readChargeTermRegister() & 0x7F;
    // Enable Charge Termination Pin
    io::i2c::writeCommand(getAddress(), Registers::CHARGE_TIMER_CONTROL, mask | 0x80);

    // Enable Charge and Battery Fault Interrupt
    mask = readOpControlRegister() & 0xFC;
    io::i2c::writeCommand(getAddress(), Registers::MISC_CONTROL, mask | 0x03);
    enableBATFET();
}

void Bq24125l::enableBoostMode() {
    if (!presence()) return;
    uint8_t mask = readPowerONRegister() & 0xCF;
    // Enable PMIC Boost Mode
    io::i2c::writeCommand(getAddress(), Registers::POWERON_CONFIG, mask | 0x20);
#ifdef ARDUINO_ARCH_SAMD
    digitalWrite(PIN_USB_HOST_ENABLE, LOW);
#endif
    // Disable Charge Termination Pin
    mask = readChargeTermRegister() & 0x7F;
    io::i2c::writeCommand(getAddress(), Registers::CHARGE_TIMER_CONTROL, mask);

    // Enable Battery Fault interrupt and disable Charge Fault Interrupt
    mask = readOpControlRegister() & 0xFC;
    io::i2c::writeCommand(getAddress(), Registers::MISC_CONTROL, mask | 0x03);
    // wait for enable boost mode
    time::delay(500);
}

void Bq24125l::disableCharge() {
    if (!presence()) return;
    uint8_t mask = readPowerONRegister() & 0xCF;
    io::i2c::writeCommand(getAddress(), Registers::POWERON_CONFIG, mask);
    mask = readChargeTermRegister() & 0x7F;
    io::i2c::writeCommand(getAddress(), Registers::CHARGE_TIMER_CONTROL, mask);
    mask = readOpControlRegister() & 0xFC;
    io::i2c::writeCommand(getAddress(), Registers::MISC_CONTROL, mask);
}

void Bq24125l::disableBoostMode() {
    if (!presence()) return;
#ifdef ARDUINO_ARCH_SAMD
    digitalWrite(PIN_USB_HOST_ENABLE, HIGH);
#endif
    uint8_t mask = readPowerONRegister() & 0xCF;
    // set default Charger Configuration value
    io::i2c::writeCommand(getAddress(), Registers::POWERON_CONFIG, mask | 0x10);
}


void Bq24125l::setChargeCurrent(float current) {
    if (!presence()) return;
    uint8_t mask = io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0x01;
    io::i2c::writeCommand(getAddress(), Registers::CHARGE_CURRENT_CONTROL, (round((math::clamp(current, 0.512F, 4.544F) - 0.512F) / 0.016F) & 0xFC) | mask);
}

float Bq24125l::getChargeCurrent() const {
    if (!presence()) return 0;
    return ((io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0xFC) * 0.016F) + 0.512F;
}

void Bq24125l::setPreChargeCurrent(float current) {
    if (!presence()) return;
    uint8_t mask = io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0x0F;
    io::i2c::writeCommand(getAddress(), Registers::PRECHARGE_CURRENT_CONTROL, mask | (round((math::clamp(current, 0.128F, 2.048F) - 0.128F) / 0.008F) & 0xF0));
}

[[nodiscard]] float Bq24125l::getPreChargeCurrent() const {
    if (!presence()) return 0;
    return ((io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0xF0) * 0.008F) + 0.128F;
}

void Bq24125l::setTermChargeCurrent(float current) {
    if (!presence()) return;
    uint8_t mask = io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0xF0;
    io::i2c::writeCommand(getAddress(), Registers::PRECHARGE_CURRENT_CONTROL, mask | (round((math::clamp(current, 0.128F, 2.048F) - 0.128F) / 0.128F) & 0x0F));
}

[[nodiscard]] float Bq24125l::getTermChargeCurrent() const {
    if (!presence()) return 0;
    return ((io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0x0F) * 0.128F) + 0.128F;
}


uint8_t Bq24125l::getVersion() const {
    return io::i2c::read8(getAddress(), Registers::PMIC_VERSION);
}

bool Bq24125l::isBattConnected() const {
    if (!presence()) return false;
    return (readSystemStatusRegister() & 0x08) == 0x08;
}

int Bq24125l::USBmode() {
    if (!presence()) return 0xFF;
    return readSystemStatusRegister() & 0b11000000;
}


uint8_t Bq24125l::readOpControlRegister() const {
    return io::i2c::read8(getAddress(), Registers::MISC_CONTROL);
}

uint8_t Bq24125l::readChargeTermRegister() const {
    return io::i2c::read8(getAddress(), Registers::CHARGE_TIMER_CONTROL);
}

uint8_t Bq24125l::readPowerONRegister() const {
    return io::i2c::read8(getAddress(), Registers::POWERON_CONFIG);
}

uint8_t Bq24125l::readInputSourceRegister() const {
    return io::i2c::read8(getAddress(), Registers::INPUT_SOURCE);
}

uint8_t Bq24125l::readSystemStatusRegister() const {
    return io::i2c::read8(getAddress(), Registers::SYSTEM_STATUS);
}

// ----------------- FAULT REGISTER MANAGEMENT ------------------------

uint8_t Bq24125l::readFaultRegister() const {
    return io::i2c::read8(getAddress(), Registers::FAULT);
}

Bq24125l::ThermalFault Bq24125l::getThermalFault() const {
    auto fault = readFaultRegister();
    if (fault == 0x00)
        return ThermalFault::Ok;
    // Temperature Fault
    if (fault == 0x05)
        return ThermalFault::LowerThresholdTemperature;
    if (fault == 0x06)
        return ThermalFault::UpperThresholdTemperature;
    return ThermalFault::Unknown;
}

Bq24125l::ChargeFault Bq24125l::getChargeFault() const {
    auto fault = readFaultRegister();
    if (fault == 0x00)
        return ChargeFault::Ok;
    // Charge faults
    if (fault == 0x10)
        return ChargeFault::InputOverVoltage;
    if (fault == 0x20)
        return ChargeFault::ThermalShutDown;
    if (fault == 0x30)
        return ChargeFault::ChargeSafetyTimeExpired;
    return ChargeFault::Unknown;
}

bool Bq24125l::isWatchdogExpired() const {
    if (!presence()) return false;
    return (readFaultRegister() & 0x80) != 0;
}

bool Bq24125l::isBatteryInOverVoltage() const {
    if (!presence()) return false;
    return (readFaultRegister() & 0x08) != 0;
}

}// namespace sbs::sensor

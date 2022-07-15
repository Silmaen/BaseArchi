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

void Bq24125l::setChargeCurrent(float current) {
    if (!presence()) return;
    byte mask = io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0x01;
    io::i2c::writeCommand(getAddress(), Registers::CHARGE_CURRENT_CONTROL, (round(((math::clamp(current,0.512F,4.544F) - 0.512F) / 0.016F)) & 0xFC) | mask);
}
float Bq24125l::getChargeCurrent() const {
    if (!presence()) return 0;
    return ((io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0xFC) * 0.016F) + 0.512F;
}


void Bq24125l::setPreChargeCurrent(float current) {
    if (!presence()) return;
    byte mask = io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0x0F;
    io::i2c::writeCommand(getAddress(), Registers::PRECHARGE_CURRENT_CONTROL, mask | (round((math::clamp(current,0.128F,2.048F) - 0.128F) / 0.008F) & 0xF0));
}

[[nodiscard]] float Bq24125l::getPreChargeCurrent() const {
    if (!presence()) return 0;
    return ((io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0xF0) * 0.008F) + 0.128F;
}

void Bq24125l::setTermChargeCurrent(float current) {
    if (!presence()) return;
    byte mask = io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0xF0;
    io::i2c::writeCommand(getAddress(), Registers::PRECHARGE_CURRENT_CONTROL, mask | (round((math::clamp(current,0.128F,2.048F) - 0.128F) / 0.128F) & 0x0F));
}

[[nodiscard]] float Bq24125l::getTermChargeCurrent() const {
    if (!presence()) return 0;
    return ((io::i2c::read8(getAddress(), Registers::CHARGE_CURRENT_CONTROL) & 0x0F) * 0.128F) + 0.128F;
}


bool Bq24125l::isBatteryInOverVoltage() const {
    if (!presence()) return false;
    return (readFaultRegister() & 0x08) != 0;
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
    return readSystemStatusRegister() & 0xC0;
}

uint8_t Bq24125l::readOpControlRegister() const {
    return io::i2c::read8(getAddress(), Registers::MISC_CONTROL);
}

uint8_t Bq24125l::readChargeTermRegister() const {
    return io::i2c::read8(getAddress(), Registers::);
}

uint8_t Bq24125l::readPowerONRegister() const {
    return io::i2c::read8(getAddress(), Registers::POWERON_CONFIG);
}

uint8_t Bq24125l::readInputSourceRegister() const {
    return io::i2c::read8(getAddress(), Registers::INPUT_SOURCE);
}

uint8_t Bq24125l::readSystemStatusRegister() const {
    return io::i2c::read8(getAddress(), Registers::SYSTEM_STATUS);
    ;
}

uint8_t Bq24125l::readFaultRegister() const {
    return io::i2c::read8(getAddress(), Registers::FAULT);
}

}// namespace sbs::sensor

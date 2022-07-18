/**
 * @file Lps22hb.cpp
 * @author Silmaen
 * @date 11/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Lps22hb.h"
#include "io/i2c/utils.h"
#include "physic/conversions.h"

namespace sbs::sensor {
constexpr uint8_t defaultAddress  = 0x5C;///< Default LPS22HB i2C address
constexpr uint8_t chipId          = 0xb1;///< chip Id
constexpr uint8_t byteShift       = 8U;  ///< 8 bits shift
constexpr uint8_t doubleByteShift = 16U; ///< 16 bits shift

Lps22hb::Lps22hb() :
    io::i2c::Device{defaultAddress} {
}

const Lps22hb::SensorData& Lps22hb::getValue() {
    if (!presence()) {
        init();
    }
    if (presence()) {
        io::i2c::writeCommand(getAddress(), R_CTRL2, 0x01);
        while (io::i2c::read8(getAddress(), R_CTRL2 & 0x01) != 0)
            ;
        readAndCompensate();
    }
    return data;
}

void Lps22hb::init() {
    Device::init();
    selfCheck();
}

bool Lps22hb::checkPresence() const {
    return io::i2c::read8(getAddress(), Registers::R_WHOAMI) == chipId;
}

void Lps22hb::readAndCompensate() {
    uint8_t rawData[5];
    for (uint8_t hum = 0; hum < 5; ++hum)
        rawData[hum] = io::i2c::read8(getAddress(), Registers::R_PRESS_OUT_XL + hum);
    uint32_t rawT    = rawData[3] | rawData[4] << byteShift;
    data.temperature = rawT / 100.0;
    uint32_t rawP    = static_cast<uint32_t>(rawData[0]) | static_cast<uint32_t>(rawData[1]) << byteShift | static_cast<uint32_t>(rawData[2]) << doubleByteShift;
    data.pressure    = rawP / 4096.0 - pressureOffset;
}

double Lps22hb::SensorData::getAltitude(double qnh) const {
    return physic::getAltitude(qnh, pressure, temperature);
}

double Lps22hb::SensorData::getQnh(double actualAltitude) const {
    return physic::computeQnh(actualAltitude, pressure, temperature);
}

}// namespace sbs::sensor

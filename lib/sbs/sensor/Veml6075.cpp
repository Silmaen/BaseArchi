/**
 * @file Veml6075.cpp
 * @author Silmaen
 * @date 11/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Veml6075.h"
#include "io/i2c/utils.h"
#include "physic/conversions.h"



namespace sbs::sensor {
constexpr uint8_t defaultAddress  = 0x10;///< Default LPS22HB i2C address
constexpr uint16_t chipId          = 0x0026;///< chip Id
constexpr uint8_t byteShift       = 8U;  ///< 8 bits shift
constexpr uint8_t doubleByteShift = 16U; ///< 16 bits shift

Veml6075::Veml6075() :
    io::i2c::Device{defaultAddress} {
}
const Veml6075::SensorData& Veml6075::getValue() {
    if (!presence()) {
        init();
    }
    if (presence()) {
        readAndCompensate();
    }
    return data;
}
void Veml6075::init() {
    Device::init();
    // configure VEML6075 for 100 ms
    io::i2c::writeCommand(getAddress(), Registers::R_UV_CONF, 0x10);
    selfCheck();
}
bool Veml6075::checkPresence() const {
    return io::i2c::read16(getAddress(), Registers::R_ID, true) == chipId;
}

void Veml6075::readAndCompensate() {
    constexpr double a = 2.22;
    constexpr double b = 1.33;
    constexpr double c = 2.95;
    constexpr double d = 1.74;
    // read UVA and UV COMP's, then calculate compensated value
    uint16_t uva     = io::i2c::read16(getAddress(), Registers::R_UVA_DATA, true);
    uint16_t uvb     = io::i2c::read16(getAddress(), Registers::R_UVB_DATA, true);
    uint16_t uvcomp1 = io::i2c::read16(getAddress(), Registers::R_UVCOMP1, true);
    uint16_t uvcomp2 = io::i2c::read16(getAddress(), Registers::R_UVCOMP2, true);
    data.uva = uva - (a * uvcomp1) - (b * uvcomp2);
    data.uvb = uvb - (c * uvcomp1) - (d * uvcomp2);
}

double Veml6075::SensorData::getUVIndex() const {
    double AResp = 0.001461;
    double BResp = 0.002591;
    return (uva * AResp + uvb * BResp ) * 0.5;
}

}// namespace sbs::sensor

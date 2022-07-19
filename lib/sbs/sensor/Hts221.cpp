/**
 * @file Hts221.cpp
 * @author Silmaen
 * @date 11/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Hts221.h"
#include "io/i2c/utils.h"
#include "physic/conversions.h"

namespace sbs::sensor {
constexpr uint8_t defaultAddress = 0x5F;///< Default HTS221 i2C address
constexpr uint8_t chipId         = 0xBC;///< chip Id
constexpr uint8_t byteShift       = 8U;  ///< 8 bits shift

Hts221::Hts221() :
    io::i2c::Device{defaultAddress} {
}
const Hts221::SensorData& Hts221::getValue() {
    if (!presence()) {
        init();
    }
    if (presence()) {
        // wait for clear space
        while ((io::i2c::read8(getAddress(), Registers::R_CTRL2_REG) & 0x01) != 0)
            ;
        // trigger one shot
        io::i2c::writeCommand(getAddress(), Registers::R_CTRL2_REG, 0x01);

        // wait for completion
        while ((io::i2c::read8(getAddress(), Registers::R_CTRL2_REG) & 0x01) != 0)
            ;
        readAndCompensate();
    }
    return data;
}

void Hts221::init() {
    Device::init();
    selfCheck();
    if (presence()) {
        readCalibration();

        // turn on the HTS221 and enable Block Data Update
        io::i2c::writeCommand(getAddress(), Registers::R_CTRL1_REG, 0x84);

        // Disable HTS221_DRDY by default and make the output open drain
        // This allows to use pin D6 for other purposes (e.g. LED_BUILTIN on the Arduino MKR WAN 1300)
        io::i2c::writeCommand(getAddress(), Registers::R_CTRL3_REG, 0x40);
    }
}

bool Hts221::checkPresence() const {
    return io::i2c::read8(getAddress(), Registers::R_WHOAMI) == chipId;
}

void Hts221::readCalibration() {
    uint8_t h0rH = io::i2c::read8(getAddress(), Registers::R_H0_rH_x2_REG);
    uint8_t h1rH = io::i2c::read8(getAddress(), Registers::R_H1_rH_x2_REG);

    auto t0degC = static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_T0_degC_x8_REG) | (static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_T1_T0_MSB_REG) & 0x03) << byteShift));
    auto t1degC = static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_T1_degC_x8_REG) | (static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_T1_T0_MSB_REG) & 0x0c) << 6));

    auto h0t0Out = static_cast<int16_t>(io::i2c::read8(getAddress(), Registers::R_H0_T0_OUT_REG) | static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_H0_T0_OUT_REG + 1)) << byteShift);
    auto h1t0Out = static_cast<int16_t>(io::i2c::read8(getAddress(), Registers::R_H1_T0_OUT_REG) | static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_H1_T0_OUT_REG + 1)) << byteShift);

    auto t0Out = static_cast<int16_t>(io::i2c::read8(getAddress(), Registers::R_T0_OUT_REG) | static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_T0_OUT_REG + 1)) << byteShift);
    auto t1Out = static_cast<int16_t>(io::i2c::read8(getAddress(), Registers::R_T1_OUT_REG) | static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_T1_OUT_REG + 1)) << byteShift);

    // calculate slopes and 0 offset from calibration values,
    // for future calculations: value = a * X + b

    cal.H_Slope = (h1rH - h0rH) / (2.0 * (h1t0Out - h0t0Out));
    cal.H_Zero  = (h0rH / 2.0) - cal.H_Slope * h0t0Out;

    cal.T_Slope = (t1degC - t0degC) / (8.0 * (t1Out - t0Out));
    cal.T_Zero  = (t0degC / 8.0) - cal.T_Slope * t0Out;
}

void Hts221::readAndCompensate() {
    // read value and convert
    auto tout     = static_cast<int16_t>(io::i2c::read8(getAddress(), Registers::R_TEMP_OUT_L_REG) | static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_TEMP_OUT_L_REG + 1)) << byteShift);
    data.temperature = tout * cal.T_Slope + cal.T_Zero;

    // read value and convert
    auto hout  = static_cast<int16_t>(io::i2c::read8(getAddress(), Registers::R_HUMIDITY_OUT_L_REG) | static_cast<uint16_t>(io::i2c::read8(getAddress(), Registers::R_HUMIDITY_OUT_L_REG + 1)) << byteShift);
    data.humidity = hout * cal.H_Slope + cal.H_Zero;
}


double Hts221::SensorData::getDewPoint() const {
    return physic::computeDewPoint(temperature,humidity);
}

}// namespace sbs::sensor

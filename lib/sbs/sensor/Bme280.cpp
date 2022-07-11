/**
 * @file Bme280.cpp
 * @author Silmean
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Bme280.h"
#include "io/i2c/utils.h"
#include "math/base.h"
#include "physic/conversions.h"
#include "time/timing.h"

#ifdef ARDUINO
#include <Wire.h>
#endif

namespace sbs::sensor {
constexpr uint8_t defaultAddress    = 0x76;   ///< Default BME280 i2C address
constexpr uint8_t semiByteShift     = 4U;     ///< 4 bits shift
constexpr uint8_t byteShift         = 8U;     ///< 8 bits shift
constexpr uint8_t doubleByteShift   = 16U;    ///< 16 bits shift
constexpr static uint8_t chipId     = 0x60;   ///< chip Id
constexpr static uint8_t resetCode  = 0x56;   ///< code for device reset
constexpr static uint8_t statusMask = 0b1001U;///< Status mask

BME280::BME280() :
    io::i2c::Device{defaultAddress} {
}

const BME280::SensorData& BME280::getValue() {
    if (!presence()) {
        init();
    }
    if (presence()) {
        if (setting.mode == Setting::WorkingMode::Forced) {// device need to be waked up
            io::i2c::writeCommand(getAddress(), R_CTRL_MEAS, setting.toCtrlMeasReg());
            time::delay(setting.maxMeasurementTime());
        }
        while (io::i2c::read8(getAddress(), R_STATUS & statusMask) != 0)
            ;
        readAndCompensate();
    }
    return data;
}

void BME280::init() {
    Device::init();
#ifdef ARDUINO
    Wire.begin();
#endif
    selfCheck();
    if (presence()) {
        readCalibration();
        applySetting();
    }
}

bool BME280::checkPresence() const {
    return io::i2c::read8(getAddress(), Registers::R_ID) == chipId;//---UNCOVER---
}

void BME280::applySetting() {
    io::i2c::writeCommand(getAddress(), R_CTRL_HUM, setting.toCtrlHumReg());
    io::i2c::writeCommand(getAddress(), R_CONFIG, setting.toConfigReg());
    io::i2c::writeCommand(getAddress(), R_CTRL_MEAS, setting.toCtrlMeasReg());
    io::i2c::writeCommand(getAddress(), R_RESET, resetCode);
}

void BME280::readCalibration() {
    uint8_t dataTPH1[25];
    uint8_t dataH[7];
    io::i2c::read(getAddress(), R_T1_LSB, 25U, dataTPH1, true);
    io::i2c::read(getAddress(), R_H2_LSB, 7U, dataH, true);
    auto temp  = static_cast<uint16_t>(dataTPH1[0]) | static_cast<uint16_t>(dataTPH1[1]) << byteShift;
    cal.T1     = static_cast<double>(temp) * 16.0;
    auto temps = static_cast<int16_t>(static_cast<uint16_t>(dataTPH1[2]) | static_cast<uint16_t>(dataTPH1[3]) << byteShift);
    cal.T2     = static_cast<double>(temps) / 16384.0;
    temps      = static_cast<int16_t>(static_cast<uint16_t>(dataTPH1[4]) | static_cast<uint16_t>(dataTPH1[5]) << byteShift);
    cal.T3     = static_cast<double>(temps) / 1073741824.0;
    //                                          17179869184.0
    temp          = static_cast<uint16_t>(dataTPH1[6]) | static_cast<uint16_t>(dataTPH1[7]) << byteShift;
    cal.P1        = static_cast<double>(temp) / 6250.0;
    temps         = static_cast<int16_t>(static_cast<int16_t>(dataTPH1[8]) | static_cast<int16_t>(dataTPH1[9]) << byteShift);
    cal.P2        = static_cast<double>(temps) / 524288.0 / 65536.0;
    temps         = static_cast<int16_t>(dataTPH1[10] | dataTPH1[11] << byteShift);
    cal.P3        = static_cast<double>(temps) / 524288.0 / 524288.0 / 131072.0;
    temps         = static_cast<int16_t>(dataTPH1[12] | dataTPH1[13] << byteShift);
    cal.P4        = static_cast<double>(temps) * 16.0 - 1048576.0;
    temps         = static_cast<int16_t>(dataTPH1[14] | dataTPH1[15] << byteShift);
    cal.P5        = static_cast<double>(temps) / 4.0 / 4096.0;
    temps         = static_cast<int16_t>(dataTPH1[16] | dataTPH1[17] << byteShift);
    cal.P6        = static_cast<double>(temps) / 32768.0 / 65536.0;
    temps         = static_cast<int16_t>(dataTPH1[18] | dataTPH1[19] << byteShift);
    cal.P7        = static_cast<double>(temps) / 1600.0;
    temps         = static_cast<int16_t>(dataTPH1[20] | dataTPH1[21] << byteShift);
    cal.P8        = (static_cast<double>(temps) / 524288.0 + 1.0) / 100.0;
    temps         = static_cast<int16_t>(dataTPH1[22] | dataTPH1[23] << byteShift);
    cal.P9        = static_cast<double>(temps) / 2147483648.0 / 1600.0;
    uint8_t temp8 = dataTPH1[24];
    cal.H1        = static_cast<double>(temp8);
    temps         = static_cast<int16_t>(dataH[0] | dataH[1] << byteShift);
    cal.H2        = static_cast<double>(temps);
    temp8         = dataH[2];
    cal.H3        = static_cast<double>(temp8);
    uint8_t cplmt = dataH[4];
    temp8         = dataH[3];
    temp          = static_cast<uint16_t>((static_cast<uint16_t>(temp8) << semiByteShift) | (cplmt & 0x0F ));
    cal.H4        = static_cast<double>(temp);
    temp8         = dataH[5];
    temp          = (static_cast<uint16_t>(temp8) << semiByteShift) | (cplmt >> semiByteShift);
    cal.H5        = static_cast<double>(temp);
    temp8         = dataH[6];
    cal.H6        = static_cast<double>(temp8);
}

void BME280::readAndCompensate() {
    uint8_t rawData[8];
    io::i2c::read(getAddress(), Registers::R_PRESS_MSB, 8, rawData, true);
    // Temperature Compensation
    const int32_t rawT = ((static_cast<int32_t>(rawData[3]) << doubleByteShift) | (static_cast<int32_t>(rawData[4]) << byteShift) | static_cast<int32_t>(rawData[5])) >> semiByteShift;
    double var1        = (rawT - cal.T1);
    double var2        = var1 * var1 * cal.T3;
    auto fine       = static_cast<int32_t>(var1 * cal.T2 + var2);
    data.temperature   = (var1 * cal.T2 + var2) / 5120.0;

    // Pressure Compensation
    const uint32_t rawP  = ((static_cast<uint32_t>(rawData[0]) << doubleByteShift) | (static_cast<uint32_t>(rawData[1]) << byteShift) | static_cast<uint32_t>(rawData[2])) >> semiByteShift;
    constexpr double P10 = 128000.0;
    var1                 = static_cast<double>(fine) - P10;
    var2                 = cal.P6 * var1 * var1 + cal.P5 * var1 + cal.P4;
    var1                 = cal.P1 * (cal.P3 * var1 * var1 + cal.P2 * var1 + 1.0);
    if (var1 == 0.0) {
        data.pressure = 0.0;//---UNCOVER---
    } else {
        data.pressure = -(rawP + var2) / var1;
        data.pressure = cal.P9 * data.pressure * data.pressure + cal.P8 * data.pressure + cal.P7;
    }

    // Humidity Compensation
    const uint32_t rawH = (static_cast<uint32_t>(rawData[6]) << byteShift) | static_cast<uint32_t>(rawData[7]);
    constexpr double H7_ = 76800.0;
    var1                = static_cast<double>(fine) - H7_;
    var2                = cal.H2/65536.0 * (1.0 + cal.H6 / 67108864.0 * var1 * (1.0 + cal.H3 / 67108864.0 * var1));
    var1                = (rawH - (cal.H4 * 64.0 + cal.H5 / 16384.0 * var1)) * var2;
    var1 *= (1.0 - cal.H1 * var1 / 524288.0);
    data.humidity = math::clamp(var1, 0.0, 100.0);
}

double BME280::SensorData::getAltitude(double qnh) const {
    // h = -R*T/(µ*g). ln(P/P0)
    return physic::getAltitude(qnh, pressure, temperature);
}

double BME280::SensorData::getQnh(double actualAltitude) const {
    // qnh = P * exp(µ*g*AltitudeRef / (R * T))
    return physic::computeQnh(actualAltitude, pressure, temperature);
}

}// namespace sbs::sensor

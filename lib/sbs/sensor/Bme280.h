/**
 * @file Bme280.h
 * @author damien.lachouette 
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "io/i2c/Device.h"
/**
 * @brief namespace for the sensors
 */
namespace sbs::sensor {


/**
 * @brief Class BME280
 */
class BME280 : public io::i2c::Device {
public:
    BME280(const BME280&)            = delete;
    BME280(BME280&&)                 = delete;
    BME280& operator=(const BME280&) = delete;
    BME280& operator=(BME280&&)      = delete;
    /**
     * @brief Default constructor.
     */
    BME280();
    /**
     * @brief Destructor.
     */
    ~BME280() override = default;//---UNCOVER---

    /**
     * @brief Sensor Data
     */
    struct SensorData {
        float Temperature;///< Atmospheric Temperature
        float Humidity;   ///< Atmospheric Humidity
        float Pressure;   ///< Atmospheric pressure
    };
    /**
     * \brief device settings
     */
    struct Setting {
        /**
         * @brief The internal modes of work
         */
        enum struct WorkingMode {
            Sleep  = 0b00,///< No operation, all register accessible, lowest power, startup mode
            Forced = 0b01,///< Perform 1 measurement, store results, then sleep (wake up only on demand)
            Normal = 0b11,///< Perpetual measurement and inactive period cycle (set by StandyByTime)
        };

        /**
         * @brief oversampling possibilities
         *
         * The oversampling is set for each sensor. the values are the same.
         */
        enum struct Oversampling {
            Off   = 0,    ///< sensor deactivated
            O_X1  = 0b001,///< one sample
            O_X2  = 0b010,///< 2 sample
            O_X4  = 0b011,///< 4 sample
            O_X8  = 0b100,///< 8 sample
            O_X16 = 0b101,///< 16 sample
        };

        /**
         * @brief filtering options
         */
        enum struct FilterCoefficient {
            Off  = 0b000,///< filter off
            F_2  = 0b001,///< filter coefficient 2
            F_4  = 0b010,///< filter coefficient 4
            F_8  = 0b011,///< filter coefficient 8
            F_16 = 0b100,///< filter coefficient 16
        };

        /**
         * @brief the stand by time between two measure
         */
        enum struct StandyByTime {
            SBT_0_5  = 0b000,///< 0.5 ms
            SBT_62_5 = 0b001,///< 62.5 ms
            SBT_125  = 0b010,///< 125 ms
            SBT_250  = 0b011,///< 250 ms
            SBT_500  = 0b100,///< 500 ms
            SBT_100  = 0b101,///< 100 ms
            SBT_10   = 0b110,///< 10 ms
            SBT_20   = 0b111,///< 20 ms
        };

        WorkingMode mode                     = WorkingMode::Sleep;    ///< operating mode
        Oversampling pressureOversampling    = Oversampling::Off;     ///< oversampling for pressure
        Oversampling temperatureOversampling = Oversampling::Off;     ///< oversampling for temperature
        Oversampling humidityOversampling    = Oversampling::Off;     ///< oversampling for humidity
        StandyByTime sdTime                  = StandyByTime::SBT_0_5; ///< stand by time
        FilterCoefficient filter             = FilterCoefficient::Off;///< filter coefficient

        constexpr Setting(const WorkingMode& m,
                          const Oversampling& po,
                          const Oversampling& to,
                          const Oversampling& ho,
                          const StandyByTime& sdt,
                          const FilterCoefficient& fc) :
            mode{m},
            pressureOversampling{po}, temperatureOversampling{to}, humidityOversampling{ho}, sdTime{sdt}, filter{fc} {}

        [[nodiscard]] uint8_t toCtrlHumReg() const { return static_cast<uint8_t>(humidityOversampling); }
        [[nodiscard]] uint8_t toCtrlMeasReg() const {
            return (static_cast<uint8_t>(temperatureOversampling) << 5U) + (static_cast<uint8_t>(pressureOversampling) << 2U) +
                   static_cast<uint8_t>(mode);
        }
        [[nodiscard]] uint8_t toConfigReg() const { return (static_cast<uint8_t>(sdTime) << 5U) + (static_cast<uint8_t>(filter) << 2U); }
        [[nodiscard]] uint16_t maxMeasurementTime() const {
            float estimation = 1.25F + (2.3F * static_cast<float>(temperatureOversampling));
            if (pressureOversampling != Oversampling::Off)
                estimation += (2.3F * static_cast<float>(pressureOversampling) + 0.575F);
            if (humidityOversampling != Oversampling::Off)
                estimation += (2.3F * static_cast<float>(humidityOversampling) + 0.575F);
            return estimation + 0.5F;
        }
    };

private:
    /// Device's settings
    Setting settings;
    /**
     * @brief Definition of registers constants
     */
    enum Registers {
        // config
        R_ID        = 0xD0,///< Chip ID
        R_RESET     = 0xE0,///< soft reset
        R_CTRL_HUM  = 0xF2,///< Humidity options register
        R_STATUS    = 0xF3,///< Status of the device bit 0 : im_update (1 copying, 0 ready) bit 3 measuring (0: ready)
        R_CTRL_MEAS = 0xF4,///< pressure/temp (need to be set after ctrl_hum)
        R_CONFIG    = 0xF5,///< set rates, filter & interface
        // measure data
        R_PRESS_MSB  = 0xF7,///< pressure data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_PRESS_LSB  = 0xF8,///< pressure data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_PRESS_XLSB = 0xF9,///< pressure data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_TEMP_MSB   = 0xFA,///< temperature data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_TEMP_LSB   = 0xFB,///< temperature data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_TEMP_XLSB  = 0xFC,///< temperature data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_HUM_MSB    = 0xFD,///< humidity data = `MSB << 8 + LSB`
        R_HUM_LSB    = 0xFE,///< humidity data = `MSB << 8 + LSB`
        // calibration data
        R_T1_LSB = 0x88,///< T1 coefficient LSB-first
        R_T2_LSB = 0x8A,///< T2 coefficient LSB-first
        R_T3_LSB = 0x8C,///< T3 coefficient LSB-first
        R_P1_LSB = 0x8E,///< P1 coefficient LSB-first
        R_P2_LSB = 0x90,///< P2 coefficient LSB-first
        R_P3_LSB = 0x92,///< P3 coefficient LSB-first
        R_P4_LSB = 0x94,///< P4 coefficient LSB-first
        R_P5_LSB = 0x96,///< P5 coefficient LSB-first
        R_P6_LSB = 0x98,///< P6 coefficient LSB-first
        R_P7_LSB = 0x9A,///< P7 coefficient LSB-first
        R_P8_LSB = 0x9C,///< P8 coefficient LSB-first
        R_P9_LSB = 0x9E,///< P9 coefficient LSB-first
        R_H1     = 0xA1,///< H1 coefficient
        R_H2_LSB = 0xE1,///< H2 coefficient LSB-first
        R_H3     = 0xE3,///< H3
        R_H4_MSB = 0xE4,///< H4 must bust left-shited by 4
        R_H4_H5  = 0xE5,///< H4 the firsts 4 bits are the first four bits of H4, the last 4bit are the LSB for H5
        R_H5_MSB = 0xE6,///< H5 must bust left-shited by 4
        R_H6     = 0xE7,///< H6
    };

    /**
     * @brief Structure for handling calibration data
     */
    struct CalibrationData {
        uint16_t T1 = 0;///< T1
        int16_t T2  = 0;///< T2
        int16_t T3  = 0;///< T3
        uint16_t P1 = 0;///< P1
        int16_t P2  = 0;///< P2
        int16_t P3  = 0;///< P3
        int16_t P4  = 0;///< P4
        int16_t P5  = 0;///< P5
        int16_t P6  = 0;///< P6
        int16_t P7  = 0;///< P7
        int16_t P8  = 0;///< P8
        int16_t P9  = 0;///< P9
        uint8_t H1  = 0;///< H1
        int16_t H2  = 0;///< H2
        uint8_t H3  = 0;///< H3
        int16_t H4  = 0;///< H4
        int16_t H5  = 0;///< H5
        int8_t H6   = 0;///< H6
    };
};

}// namespace sbs::sensor

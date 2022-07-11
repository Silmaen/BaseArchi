/**
 * @file Hts221.h
 * @author Silmean
 * @date 11/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "io/i2c/Device.h"

namespace sbs::sensor {
/**
 * @brief Class Hts221
 */
class Hts221 : public io::i2c::Device {
public:
    Hts221(const Hts221&)            = delete;
    Hts221(Hts221&&)                 = delete;
    Hts221& operator=(const Hts221&) = delete;
    Hts221& operator=(Hts221&&)      = delete;
    /**
     * @brief Default constructor.
     */
    Hts221();
    /**
     * @brief Destructor.
     */
    ~Hts221() override = default;

    /**
     * @brief Sensor Data
     */
    struct SensorData {
        double temperature = 0.0;///< Atmospheric Temperature
        double humidity    = 0.0;///< Atmospheric Humidity
        /**
         * @brief Internal addition
         * @param other Data to add
         * @return updated data
         */
        SensorData& operator+=(const SensorData& other) {
            temperature += other.temperature;
            humidity += other.humidity;
            return *this;
        }
        /**
         * @brief Internal subtract
         * @param other Data to subtract
         * @return updated data
         */
        SensorData& operator-=(const SensorData& other) {
            temperature -= other.temperature;
            humidity -= other.humidity;
            return *this;
        }
        /**
         * @brief Internal product
         * @param other Scalar to multiply
         * @return updated data
         */
        SensorData& operator*=(const double& other) {
            temperature *= other;
            humidity *= other;
            return *this;
        }
        /**
         * @brief Internal division
         * @param other Scalar to divide
         * @return updated data
         */
        SensorData& operator/=(const double& other) {
            temperature /= other;
            humidity /= other;
            return *this;
        }
        /**
         * @brief Addition
         * @param other Data to add.
         * @return Updated data
         */
        SensorData operator+(const SensorData& other) const {
            SensorData result{*this};
            result += other;
            return result;
        }
        /**
         * @brief Subtract
         * @param other Data to subtract.
         * @return Updated data
         */
        SensorData operator-(const SensorData& other) const {
            SensorData result{*this};
            result -= other;
            return result;
        }
        /**
         * @brief Product
         * @param other constant to multipliy
         * @return updated data
         */
        SensorData operator*(const double& other) const {
            SensorData result{*this};
            result *= other;
            return result;
        }
        /**
         * @brief Division
         * @param other constant to divide
         * @return updated data
         */
        SensorData operator/(const double& other) const {
            SensorData result{*this};
            result /= other;
            return result;
        }
    };

    /**
     * @brief Get measured values
     * @return The mease of the sensor
     */
    [[nodiscard]] const SensorData& getValue();

    /**
     * @brief Init device
     */
    void init() override;

    /**
     * @brief Get device's name
     * @return The device's name.
     */
    [[nodiscard]] string getName() const override { return "HTS221"; }

    /**
     * @brief Check the presence of the device.
     * @return Return true if the device is found.
     */
    [[nodiscard]] bool checkPresence() const override;

    /**
     * @brief Make the data backup void
     */
    void voidData() {
        data = SensorData{};
    }

private:
    /// Sensor Data
    SensorData data = SensorData{};

    /**
     * @brief Definition of registers constants
     */
    enum Registers {
        R_WHOAMI             = 0x0f,///< Who am i register
        R_CTRL1_REG          = 0x20,///< register
        R_CTRL2_REG          = 0x21,///< register
        R_CTRL3_REG          = 0x22,///< register
        R_STATUS_REG         = 0x27,///< register
        R_HUMIDITY_OUT_L_REG = 0x28,///< register
        R_TEMP_OUT_L_REG     = 0x2a,///< register
        R_H0_rH_x2_REG       = 0x30,///< Calibration register
        R_H1_rH_x2_REG       = 0x31,///< Calibration register
        R_T0_degC_x8_REG     = 0x32,///< Calibration register
        R_T1_degC_x8_REG     = 0x33,///< Calibration register
        R_T1_T0_MSB_REG      = 0x35,///< Calibration register
        R_H0_T0_OUT_REG      = 0x36,///< Calibration register
        R_H1_T0_OUT_REG      = 0x3a,///< Calibration register
        R_T0_OUT_REG         = 0x3c,///< Calibration register
        R_T1_OUT_REG         = 0x3e,///< Calibration register
    };

    /**
     * @brief Sensor Calibration constants for compensation computation
     */
    struct CalibrationDataDbl {
        double T_Zero;
        double T_Slope;
        double H_Zero;
        double H_Slope;
    };

    CalibrationDataDbl cal;///< storage of calibration data

    /**
     * \brief read & store calibration data
     */
    void readCalibration();

    /**
     * @brief Get data from device and compute the compensations
     */
    void readAndCompensate();
};
}// namespace sbs::sensor

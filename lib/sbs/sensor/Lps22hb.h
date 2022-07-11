/**
 * @file Lps22hb.h
 * @author argawaen
 * @date 11/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include "io/i2c/Device.h"

namespace sbs::sensor {

/**
 * @brief Class Lps22hb
 */
class Lps22hb : public io::i2c::Device {
public:
    Lps22hb(const Lps22hb&)            = delete;
    Lps22hb(Lps22hb&&)                 = delete;
    Lps22hb& operator=(const Lps22hb&) = delete;
    Lps22hb& operator=(Lps22hb&&)      = delete;
    /**
     * @brief Default constructor.
     */
    Lps22hb();
    /**
     * @brief Destructor.
     */
    ~Lps22hb() override = default;//---UNCOVER---

    /**
     * @brief Sensor Data
     */
    struct SensorData {
        double temperature = 0.0;///< Atmospheric Temperature
        double pressure    = 0.0;///< Atmospheric pressure
        /**
         * @brief Internal addition
         * @param other Data to add
         * @return updated data
         */
        SensorData& operator+=(const SensorData& other) {
            temperature += other.temperature;
            pressure += other.pressure;
            return *this;
        }
        /**
         * @brief Internal subtract
         * @param other Data to subtract
         * @return updated data
         */
        SensorData& operator-=(const SensorData& other) {
            temperature -= other.temperature;
            pressure -= other.pressure;
            return *this;
        }
        /**
         * @brief Internal product
         * @param other Scalar to multiply
         * @return updated data
         */
        SensorData& operator*=(const double& other) {
            temperature *= other;
            pressure *= other;
            return *this;
        }
        /**
         * @brief Internal division
         * @param other Scalar to divide
         * @return updated data
         */
        SensorData& operator/=(const double& other) {
            temperature /= other;
            pressure /= other;
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
        /**
         * @brief Get altitude based on QNH
         * @param qnh the MSL-corrected pressure
         * @return The sensor altitude
         */
        [[nodiscard]] double getAltitude(double qnh) const;
        /**
         * @brief Get MSL-Corrected pressure base on sensor altitude
         * @param actualAltitude Sensor altitude
         * @return The MSL-Corrected pressure
         */
        [[nodiscard]] double getQnh(double actualAltitude) const;
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
    [[nodiscard]] string getName() const override { return "LPS22HB"; }

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
        R_THS_P_L      = 0x0C,///< LSB pressure threshold register
        R_THS_P_H      = 0x0D,///< MSB pressure threshold register
        R_WHOAMI       = 0x0F,///< Who am I register
        R_CTRL1        = 0x10,///< Control1 register
        R_CTRL2        = 0x11,///< Control2 register
        R_CTRL3        = 0x12,///< Control3 register
        R_REF_P_XL     = 0x15,///< XLSB reference pressure register
        R_REF_P_L      = 0x16,///< LSB reference pressure register
        R_REF_P_H      = 0x17,///< MSB reference pressure register
        R_RPDS_L       = 0x18,///< LSB pressure offset register
        R_RPDS_H       = 0x19,///< MSB pressure offset register
        R_RES_CONF     = 0x1A,///< MSB Resolution register
        R_STATUS       = 0x27,///< Status register
        R_PRESS_OUT_XL = 0x28,///< XLSB Pressure read register
        R_PRESS_OUT_L  = 0x29,///< LSB Pressure read register
        R_PRESS_OUT_H  = 0x2A,///< MSB Pressure read register
        R_TEMP_OUT_L   = 0x2B,///< LSB Temperature read register
        R_TEMP_OUT_H   = 0x2C,///< MSB Temperature read register
        R_LPFP         = 0x33,///< Filter reset register
    };
    /**
     * @brief Get data from device and compute the compensations
     */
    void readAndCompensate();
};
}// namespace sbs::sensor

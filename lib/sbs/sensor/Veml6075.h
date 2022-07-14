/**
 * @file Veml6075.h
 * @author Silmaen
 * @date 11/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include "io/i2c/Device.h"

namespace sbs::sensor {

/**
 * @brief Class Veml6075
 */
class Veml6075 : public io::i2c::Device {
public:
    Veml6075(const Veml6075&)            = delete;
    Veml6075(Veml6075&&)                 = delete;
    Veml6075& operator=(const Veml6075&) = delete;
    Veml6075& operator=(Veml6075&&)      = delete;
    /**
     * @brief Default constructor.
     */
    Veml6075();
    /**
     * @brief Destructor.
     */
    ~Veml6075() override = default;//---UNCOVER---

    /**
     * @brief Sensor Data
     */
    struct SensorData {
        double uva = 0.0;///< UV A level
        double uvb = 0.0;///< UV B level
        /**
         * @brief Internal addition
         * @param other Data to add
         * @return updated data
         */
        SensorData& operator+=(const SensorData& other) {
            uva += other.uva;
            uvb += other.uvb;
            return *this;
        }
        /**
         * @brief Internal subtract
         * @param other Data to subtract
         * @return updated data
         */
        SensorData& operator-=(const SensorData& other) {
            uvb -= other.uvb;
            uva -= other.uva;
            return *this;
        }
        /**
         * @brief Internal product
         * @param other Scalar to multiply
         * @return updated data
         */
        SensorData& operator*=(const double& other) {
            uvb *= other;
            uva *= other;
            return *this;
        }
        /**
         * @brief Internal division
         * @param other Scalar to divide
         * @return updated data
         */
        SensorData& operator/=(const double& other) {
            uvb /= other;
            uva /= other;
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
         * @brief Get te UV index
         * @return The UV index
         */
        [[nodiscard]] double getUVIndex() const;
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
    [[nodiscard]] string getName() const override { return "VEML6075"; }

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
        R_UV_CONF  = 0x00,
        R_UVA_DATA = 0x07,
        R_UVB_DATA = 0x09,
        R_UVCOMP1  = 0x0a,
        R_UVCOMP2  = 0x0b,
        R_ID       = 0x0c,
    };

    /**
     * @brief Get data from device and compute the compensations
     */
    void readAndCompensate();
};
}// namespace sbs::sensor

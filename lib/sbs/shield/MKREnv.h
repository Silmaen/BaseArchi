/**
 * @file MKREnv.h
 * @author Silmaen
 * @date 14/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "sensor/Hts221.h"
#include "sensor/Lps22hb.h"
#include "sensor/Veml6075.h"

namespace sbs::shield {

/**
 * @brief Class MKREnv
 */
class MKREnv: public io::baseDevice {
public:
    MKREnv(const MKREnv&) = delete;
    MKREnv(MKREnv&&) = delete;
    MKREnv& operator=(const MKREnv&) = delete;
    MKREnv& operator=(MKREnv&&) = delete;
    /**
     * @brief Destructor.
     */
    ~MKREnv() override = default;
    /**
     * @brief Default constructor.
     */
    MKREnv() = default;

    /**
     * @brief The Data coming from sensor
     */
    struct ShieldData {
        double temperature; ///< Actual temperature
        double pressure; ///< Atmospheric pressure
        double humidity; ///< Atmospheric relative humidity
        double UVa; ///< Amount of UV-A
        double UVb; ///< Amount of UV-B
        double illuminance; ///< Global illuminance
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
        /**
         * @brief Get the dew point
         * @return The dew point
         */
        [[nodiscard]] double getDewPoint()const;
    };

    /**
     * @brief Init device
     */
    void init() override;

    /**
     * @brief Get measured values
     * @return The mease of the sensor
     */
    const ShieldData& getValue();

    /**
     * @brief Make the data backup void
     */
    void voidData() {
        data = ShieldData{};
    }
    /**
     * @brief Get the device's protocol
     * @return Device's protocol
     */
    [[nodiscard]] Protocol getProtocol()const override{return Protocol::Shield;}

    /**
     * @brief Check the version of the shield
     * @return Version of the shield
     *
     * @note Only version 1 has UV sensor
     */
    [[nodiscard]] uint8_t checkVersion()const;

    /**
     * @brief Check for device present
     * @return True if detected
     */
    [[nodiscard]] bool checkPresence() const override;

    /**
     * @brief Access to pressure sensor
     * @return Pressure sensor
     */
    sensor::Lps22hb& gerPTSensor(){return pressureTemperature;}
private:
    /// Sensor Data
    ShieldData data = ShieldData{};
    /// Humidity & Temperature sensor
    sensor::Hts221 humidityTemperature;
    /// Pressure & Temperature sensor
    sensor::Lps22hb pressureTemperature;
    /// UV sensor
    sensor::Veml6075 UVSense;
};

}// namespace sbs::shield
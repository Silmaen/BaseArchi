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
class MKREnv {
public:
    MKREnv(const MKREnv&) = delete;
    MKREnv(MKREnv&&) = delete;
    MKREnv& operator=(const MKREnv&) = delete;
    MKREnv& operator=(MKREnv&&) = delete;
    /**
     * @brief Destructor.
     */
    virtual ~MKREnv() = default;
    /**
     * @brief Default constructor.
     */
    MKREnv() = default;

    /**
     * @brief The Data coming from sensor
     */
    struct ShieldData {
        double Temperature; ///< Actual temperature
        double Pressure; ///< Atmospheric pressure
        double Humidity; ///< Atmospheric relative humidity
        double UVa; ///< Amount of UV-A
        double UVb; ///< Amount of UV-B
        double Illuminance; ///< Global illuminance
    };

    /**
     * @brief Init device
     */
    void Init();

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
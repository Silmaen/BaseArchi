/**
 * @file BatteryMonitor.h
 * @author Silmaen
 * @date 25/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#ifdef ARDUINO_ARCH_AVR
#include <stdint.h>
#else
#include <cstdint>
#endif

namespace sbs::shield {

/**
 * @brief Class BatteryMonitor
 */
class BatteryMonitor {
public:
    BatteryMonitor(const BatteryMonitor&)            = delete;
    BatteryMonitor(BatteryMonitor&&)                 = delete;
    BatteryMonitor& operator=(const BatteryMonitor&) = delete;
    BatteryMonitor& operator=(BatteryMonitor&&)      = delete;
    /**
     * @brief Default constructor.
     */
    BatteryMonitor();
    /**
     * @brief Constructor
     * @param minV Battery min voltage
     * @param maxV Battery max voltage
     * @param pin Battery tension pin
     */
    BatteryMonitor(double minV, double maxV, uint8_t pin);
    /**
     * @brief Destructor.
     */
    virtual ~BatteryMonitor() = default;//---UNCOVER---

    /**
     * @brief initialize
     */
    void init();
    /**
     * @brief The battery status
     */
    enum struct Status {
        External,   ///< External power supply, no monitoring, no battery connected
        Charging,   ///< Battery in charge
        Discharging,///< Using battery as power supply
        Disabled,   ///< Battery is connected but unused
    };
    /**
     * @brief Get the actual monitor status
     * @return Teh monitor status
     */
    [[nodiscard]] Status getStatus() const;

    /**
     * @brief Get Battery amount in percent
     * @return Battery amount
     */
    [[nodiscard]] double getBatteryPercent() const;
    /**
     * @brief Get battery voltage in volts
     * @return Battery voltage
     */
    [[nodiscard]] double getBatteryVolt() const;
    /**
     * @brief Get the input voltage
     * @return
     */
    [[nodiscard]] double getInputVoltage() const;
private:
    /// Minimal battery tension
    double minTension = 2.8;
    /// Maximal battery tension
    double maxTension = 4.1;
    /// Pin on which read the battery tension
    uint8_t BatteryPin;
};

}// namespace sbs::shield

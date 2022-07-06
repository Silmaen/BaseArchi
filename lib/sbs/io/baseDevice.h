/**
 * @file Device.h
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "core/string.h"

/**
 * @brief IO namespace
 */
namespace sbs::io {
/**
 * @brief Class device
 */
class baseDevice {
public:
    /**
     * @brief Default copy constructor
     */
    baseDevice(const baseDevice&)            = delete;
    baseDevice(baseDevice&&)                 = delete;
    baseDevice& operator=(const baseDevice&) = delete;
    baseDevice& operator=(baseDevice&&)      = delete;
    /**
     * @brief Default constructor.
     */
    baseDevice() = default;
    /**
     * @brief Destructor.
     */
    virtual ~baseDevice() = default;//---UNCOVER---

    /**
     * @brief Called at all reconnection of the device
     * @return
     */
    virtual void init() {}

    /**
     * @brief do internal checks for presence
     */
    void selfCheck();

    /**
     * @brief Check for device present
     * @return True if detected
     */
    [[nodiscard]] virtual bool checkPresence() const {return true;}

    /**
     * @brief Action when device newly connected
     */
    virtual void onConnect(){init();}

    /**
     * @brief Action when device newly disconnected
     */
    virtual void onDisconnect() {}
    /**
     * @brief Get the Device name
     * @return Device name
     */
    [[nodiscard]] virtual string getName()const {return "Unknown Device";}

    /**
     * @brief List of device protocols
     */
    enum struct Protocol {
        Unknown, /// unknown protocola
        I2C, /// i2c protocol
        SPI, /// SPI protocol
        Serial /// Uart protocol
    };

    /**
     * @brief Get the device's protocol
     * @return Device's protocol
     */
    [[nodiscard]] virtual Protocol getProtocol()const {return Protocol::Unknown;}
private:
    /// If the device is detected
    bool present = false;
};

}// namespace sbs::io

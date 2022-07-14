/**
 * @file Device.h
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "../baseDevice.h"
#ifdef ARDUINO_ARCH_AVR
#include <stdint.h>
#else
#include <cstdint>
#endif

namespace sbs::io::i2c {

/**
 * @brief Class Device
 */
class Device : public sbs::io::baseDevice {
public:
    Device(const Device&)            = delete;
    Device(Device&&)                 = delete;
    Device& operator=(const Device&) = delete;
    Device& operator=(Device&&)      = delete;
    Device()                         = delete;
    /**
     * @brief Constructor
     * @param address Device Address
     *
     * @note Constructor do not initialize the device.
     */
    explicit Device(uint8_t address) :
        address{address} {}
    /**
     * @brief Destructor.
     */
    ~Device() override = default;//---UNCOVER---

    /**
     * @brief Initialize the device
     */
    void init() override;

    /**
     * @brief Action when device newly connected
     */
    void onConnect() override { init(); }

    /**
     * @brief Action when device newly disconnected
     */
    void onDisconnect() override {}

    /**
     * @brief Get the Device name
     * @return Device name
     */
    [[nodiscard]] string getName() const override { return "Unknown I2C Device"; }

    /**
     * @brief Get the device's protocol
     * @return Device's protocol
     */
    [[nodiscard]] Protocol getProtocol() const final { return Protocol::I2C; }

    /**
     * @brief Access to the device address
     * @return Device's address
     */
    [[nodiscard]] uint8_t getAddress() const { return address; }

    /**
     * @brief Redefine the Device's address
     * @param address The new address
     */
    void setAddress(uint8_t address);

private:
    /// Address of the device
    uint8_t address = 0;
};

}// namespace sbs::io::i2c

/**
 * @file Wifi.h
 * @author Silmaen
 * @date 26/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "Address.h"
#include "core/string.h"

namespace sbs::net {
/**
 * @brief Class Wifi
 */
class Wifi {
public:
    Wifi(const Wifi&)            = delete;
    Wifi(Wifi&&)                 = delete;
    Wifi& operator=(const Wifi&) = delete;
    Wifi& operator=(Wifi&&)      = delete;
    /**
     * @brief Default constructor.
     */
    Wifi() = default;
    /**
     * @brief Destructor.
     */
    virtual ~Wifi() = default;//---UNCOVER---
    /**
     * @brief Initialize the device and try to connect to the given ssid with the pass phrase
     * @param ssid SSID to connect
     * @param pass Pass phrase to use.
     */
    void init(const string& ssid, const string& pass) const;
    /**
     * @brief Access to the singleton instance
     * @return Unique instance reference
     */
    static Wifi& get() {
        static Wifi instance;
        return instance;
    }
    /**
     * @brief Possible statuses
     */
    enum struct Status {
        Unavailable,   ///< No device present
        Disconnected,  ///< Not connected to network
        ClientConnected///< Connected to network
    };
    /**
     * @brief Return the Stats of the device
     * @return Device's stats
     */
    [[nodiscard]] Status getStatus() const;

    /**
     * @brief Get the name of the hotspot
     * @return Name of the hotspot
     */
    [[nodiscard]] string getSSID()const;
    /**
     * @brief Get the local IP
     * @return The local IP
     */
    [[nodiscard]] IpAddress getLocalIP()const;
    /**
     * @brief Get the net mask
     * @return The net mask
     */
    [[nodiscard]] IpAddress getNetMask()const;
    /**
     * @brief Get the gateway's IP
     * @return The gateway's IP
     */
    [[nodiscard]] IpAddress getGateway()const;
    /**
     * @brief Get the DNS IP
     * @param id DNS server's index
     * @return The DNS IP
     */
    [[nodiscard]] IpAddress getDNS(uint8_t id=0)const;
    /**
     * @brief Get the mac address of the device
     * @return The mac address of the device
     */
    [[nodiscard]] MacAddress getMAC()const;
    /**
     * @brief Get the mac address of the hotspot
     * @return The mac address of the hotspot
     */
    [[nodiscard]] MacAddress getBSSID()const;
    /**
     * @brief Get the reception quality
     * @return Reception quality
     */
    [[nodiscard]] double getRSSI()const;
private:
};

}// namespace sbs::net


#ifdef NATIVE
void fakeWifiSetStatus(uint8_t st);
#endif

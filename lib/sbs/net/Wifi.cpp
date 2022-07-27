/**
 * @file Wifi.cpp
 * @author Silmaen
 * @date 26/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Wifi.h"
#if defined(ARDUINO_SAMD_MKRWIFI1010)
#include <WiFiNINA.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
/**
 * @brief Arduino wifi statuses
 */
typedef enum {
    WL_NO_SHIELD   = 255,
    WL_NO_MODULE   = WL_NO_SHIELD,
    WL_IDLE_STATUS = 0,
    WL_NO_SSID_AVAIL,
    WL_SCAN_COMPLETED,
    WL_CONNECTED,
    WL_CONNECT_FAILED,
    WL_CONNECTION_LOST,
    WL_DISCONNECTED,
    WL_AP_LISTENING,
    WL_AP_CONNECTED,
    WL_AP_FAILED
} wl_status_t;
/**
 * @brief Structure to fake Arduino WiFi class
 */
struct FakeWiFi {
    /**
     * @brief starts the fake wifi
     */
    void begin(const sbs::string&, const sbs::string&) {}
    /**
     * @brief Gets the local IP
     * @return The local IP
     */
    [[nodiscard]] sbs::net::IpAddress localIP() const { return sbs::net::IpAddress{127, 0, 0, 1}; }
    /**
     * @brief Gets the gateway IP
     * @return The gateway IP
     */
    [[nodiscard]] sbs::net::IpAddress gatewayIP() const { return sbs::net::IpAddress{0, 0, 0, 0}; }
    /**
     * @brief Get the Dns P
     * @return DNS IP
     */
    [[nodiscard]] sbs::net::IpAddress dnsIP(uint8_t) const { return sbs::net::IpAddress{0, 0, 0, 0}; }
    /**
     * @brief Get the subnet mask
     * @return Subnet mask
     */
    [[nodiscard]] sbs::net::IpAddress subnetMask() const { return sbs::net::IpAddress{255, 255, 255, 0}; }
    /**
     * @brief Get the quality of the reception
     * @return Reception Quality
     */
    [[nodiscard]] uint16_t RSSI() const { return 0; }
    /**
     * @brief Get the device status code
     * @return Device's status code
     */
    [[nodiscard]] uint8_t status() const { return internalStatus; }
    /**
     * @brief Get the mac address of the device
     * @param mac The mac address of the device
     * @return The mac address of the device
     */
    uint8_t* macAddress(uint8_t* mac) { return mac; }
    /**
     * @brief Get the mac address of the hotspot
     * @param mac The mac address of the hotspot
     * @return The mac address of the hotspot
     */
    uint8_t* BSSID(uint8_t* mac) { return mac; }
    /// Just the internal status
    uint8_t internalStatus = WL_NO_SHIELD;
};
/// Fake Wifi
static FakeWiFi WiFi;

#ifdef NATIVE
void fakeWifiSetStatus(uint8_t st){
    WiFi.internalStatus = st;
}
#endif
#endif

namespace sbs::net {

Wifi::Status Wifi::getStatus() const {
    if (WiFi.status() == WL_CONNECTED)
        return Status::ClientConnected;
    if (WiFi.status() == WL_NO_SHIELD)
        return Status::Unavailable;
    return Status::Disconnected;
}

void Wifi::init(const string& ssid, const string& pass) const {
#if defined(ESP8266)
    WiFi.mode(WIFI_STA);
#endif
    WiFi.begin(ssid.c_str(), pass.c_str());
}

[[nodiscard]] string Wifi::getSSID() const {
    return "";
}

[[nodiscard]] IpAddress Wifi::getLocalIP() const {
    return IpAddress{WiFi.localIP()};
}

[[nodiscard]] IpAddress Wifi::getNetMask() const {
    return IpAddress{WiFi.subnetMask()};
}

[[nodiscard]] IpAddress Wifi::getGateway() const {
    return IpAddress{WiFi.gatewayIP()};
}

[[nodiscard]] IpAddress Wifi::getDNS(uint8_t id) const {
#ifdef ARDUINO_SAMD_MKRWIFI1010
    return IpAddress{0,0,0,id};
#else
    return IpAddress{WiFi.dnsIP(id)};
#endif
}

[[nodiscard]] MacAddress Wifi::getMAC() const {
    uint8_t mac[6];
    WiFi.macAddress(mac);
    return MacAddress{mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]};
}

[[nodiscard]] MacAddress Wifi::getBSSID() const {
#if defined(ESP8266)
    uint8_t* mac = WiFi.BSSID();
#else
    uint8_t mac[6];
    WiFi.BSSID(mac);
#endif
    return MacAddress{mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]};
}

[[nodiscard]] double Wifi::getRSSI() const {
    return WiFi.RSSI();
}

}//namespace sbs::net

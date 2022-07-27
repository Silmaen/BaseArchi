/**
 * @file Address.h
 * @author Silmaen
 * @date 17/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include "core/string.h"

/**
 * @brief Namespace for network operations
 */
namespace sbs::net {

/**
 * @brief Class IpAddress
 */
class IpAddress {
public:
    /**
     * @brief Default constructor.
     */
    IpAddress() = default;
    /**
     * @brief Default copy constructor
     */
    IpAddress(const IpAddress&) = default;
    /**
     * @brief Default move constructor
     */
    IpAddress(IpAddress&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    IpAddress& operator=(const IpAddress&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    IpAddress& operator=(IpAddress&&) = default;
    /**
     * @brief Destructor.
     */
    virtual ~IpAddress() = default;
    /**
     * @brief Define ip address by it raw value
     * @param raw The raw value
     */
    explicit IpAddress(uint32_t raw) :
        i_address{raw} {}
    /**
     * @brief Define Ip address by its byte
     * @param aaa First byte
     * @param bbb Second byte
     * @param ccc Third byte
     * @param ddd Fourth byte
     */
    IpAddress(uint8_t aaa, uint8_t bbb, uint8_t ccc, uint8_t ddd) :
        i_address{static_cast<uint32_t>(aaa) << 24 | static_cast<uint32_t>(bbb) << 16 | static_cast<uint32_t>(ccc) << 8 | static_cast<uint32_t>(ddd)} {}
    /**
     * @brief Comparison
     * @param other Ip address to compare
     * @return True if same
     */
    [[nodiscard]] bool operator==(const IpAddress& other) const { return i_address == other.i_address; }
    /**
     * @brief Comparison
     * @param other Ip address to compare
     * @return True if not same
     */
    [[nodiscard]] bool operator!=(const IpAddress& other) const { return i_address != other.i_address; }
    /**
     * @brief Check if 2 address in the same network
     * @param other Ip address to compare
     * @param netMask The netmask
     * @return True if in same network
     */
    [[nodiscard]] bool inSameNetwork(const IpAddress& other, const IpAddress& netMask) const { return (i_address & netMask.i_address) == (other.i_address & netMask.i_address); }
    /**
     * @brief Get raw address value
     * @return Raw address value
     */
    [[nodiscard]] const uint32_t& raw()const{return i_address;}
private:
    /// address
    uint32_t i_address = 0;
};

/// Mask for mac address translation
constexpr uint64_t MacMask = 0x0000FFFFFFFFFFFF;
/**
 * @brief Class MacAddress
 */
class MacAddress {
public:
    /**
     * @brief Default constructor.
     */
    MacAddress() = default;
    /**
     * @brief Default copy constructor
     */
    MacAddress(const MacAddress&) = default;
    /**
     * @brief Default move constructor
     */
    MacAddress(MacAddress&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    MacAddress& operator=(const MacAddress&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    MacAddress& operator=(MacAddress&&) = default;
    /**
     * @brief Destructor.
     */
    virtual ~MacAddress() = default;
    /**
     * @brief Define ip address by it raw value
     * @param raw The raw value
     */
    explicit MacAddress(uint64_t raw) :
        i_address{raw & MacMask} {}
    /**
     * @brief Define Ip address by its byte
     * @param aaa First byte
     * @param bbb Second byte
     * @param ccc Third byte
     * @param ddd Fourth byte
     * @param eee Fifth byte
     * @param fff Sixth byte
     */
    MacAddress(uint8_t aaa, uint8_t bbb, uint8_t ccc, uint8_t ddd, uint8_t eee, uint8_t fff) :
        i_address{static_cast<uint64_t>(aaa) << 40 | static_cast<uint64_t>(bbb) << 32 | static_cast<uint64_t>(ccc) << 24 | static_cast<uint64_t>(ddd) << 16| static_cast<uint64_t>(eee) << 8 | static_cast<uint64_t>(fff)} {}
    /**
     * @brief Comparison
     * @param other Ip address to compare
     * @return True if same
     */
    [[nodiscard]] bool operator==(const MacAddress& other) const { return i_address == other.i_address; }
    /**
     * @brief Comparison
     * @param other Ip address to compare
     * @return True if not same
     */
    [[nodiscard]] bool operator!=(const MacAddress& other) const { return i_address != other.i_address; }
    /**
     * @brief Get raw address value
     * @return Raw address value
     */
    [[nodiscard]] const uint64_t& raw()const{return i_address;}
private:
    /// address
    uint64_t i_address = 0;
};

}// namespace sbs::net

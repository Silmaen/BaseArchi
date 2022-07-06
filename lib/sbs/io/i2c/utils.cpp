/**
 * @file utils.cpp
 * @author damien.lachouette 
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "utils.h"

#ifdef ARDUINO
#include <Wire.h>
#endif

namespace sbs::io::i2c {
constexpr uint8_t byteShift       = 8U; ///< Constant to shift a whole byte
constexpr uint8_t doubleByteShift = 16U;///< Constant to shift 2 bytes
constexpr uint8_t tripleByteShift = 24U;///< Constant to shift 3 bytes

/**
 * @brief Basic Wire Read
 * @return Read byte
 */
uint32_t _read() {
#ifdef ARDUINO
    return static_cast<uint32_t>(Wire.read());
#else
return 0;
#endif
}

/**
 * @brief Basic Wire write
 * @param address Device address
 * @param reg Device's register
 */
void _write([[maybe_unused]] uint8_t address, [[maybe_unused]] uint8_t reg) {
#ifdef ARDUINO
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();
#endif
}

void writeCommand([[maybe_unused]] uint8_t address, [[maybe_unused]] uint8_t reg, [[maybe_unused]] uint8_t value) {
#ifdef ARDUINO
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
#endif
}

[[nodiscard]] uint8_t read8(uint8_t address, uint8_t reg) {
    _write(address, reg);
#ifdef ARDUINO
    Wire.requestFrom(address, 1U);
    uint8_t value = _read();
    Wire.endTransmission();
    return value;
#else
    return 0;
#endif
}

[[nodiscard]] int8_t readS8(uint8_t address, uint8_t reg) { return static_cast<int8_t>(read8(address, reg)); }

[[nodiscard]] uint16_t read16(uint8_t address, uint8_t reg,[[maybe_unused]]  bool lowFirst) {
    _write(address, reg);
#ifdef ARDUINO
    Wire.requestFrom(address, 2U);
    if (lowFirst) {
        uint16_t value = _read() | static_cast<uint16_t>(_read() << byteShift);
        Wire.endTransmission();
        return value;
    }
    uint16_t value = static_cast<uint16_t>(_read() << byteShift) | _read();
    Wire.endTransmission();
    return value;
#else
    return 0;
#endif
}

[[nodiscard]] int16_t readS16(uint8_t address, uint8_t reg, bool lowFirst) {
    return static_cast<int16_t>(read16(address, reg, lowFirst));
}

[[nodiscard]] uint32_t read24(uint8_t address, uint8_t reg, [[maybe_unused]] bool lowFirst) {
    _write(address, reg);
#ifdef ARDUINO
    Wire.requestFrom(address, 3U);
    if (lowFirst) {
        uint32_t value =
                _read() | static_cast<uint32_t>(_read() << byteShift) | static_cast<uint32_t>(_read() << doubleByteShift);
        Wire.endTransmission();
        return value;
    }
    uint32_t value =
            static_cast<uint32_t>(_read() << doubleByteShift) | static_cast<uint32_t>(_read() << byteShift) | _read();
    Wire.endTransmission();
    return value;
#else
    return 0;
#endif
}

[[nodiscard]] int32_t readS24(uint8_t address, uint8_t reg, bool lowFirst) {
    return static_cast<int32_t>(read24(address, reg, lowFirst));
}

[[nodiscard]] uint32_t read32(uint8_t address, uint8_t reg, [[maybe_unused]] bool lowFirst) {
    _write(address, reg);
#ifdef ARDUINO
    Wire.requestFrom(address, 4U);
    if (lowFirst) {
        uint32_t value =
                _read() | static_cast<uint32_t>(_read() << byteShift) | static_cast<uint32_t>(_read() << doubleByteShift) | static_cast<uint32_t>(_read() << tripleByteShift);
        Wire.endTransmission();
        return value;
    }
    uint32_t value =
            static_cast<uint32_t>(_read() << tripleByteShift) | static_cast<uint32_t>(_read() << doubleByteShift) | static_cast<uint32_t>(_read() << byteShift) | _read();
    Wire.endTransmission();
    return value;
#else
    return 0;
#endif
}

[[nodiscard]] int32_t readS32(uint8_t address, uint8_t reg, bool lowFirst) {
    return static_cast<int32_t>(read32(address, reg, lowFirst));
}

}// namespace sbs::io::i2c

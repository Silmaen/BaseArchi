/**
 * @file utils.cpp
 * @author Silmean
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "utils.h"
#include "math/base.h"
#ifdef ARDUINO_ARCH_AVR
#else
#include <memory>
#endif

#ifdef ARDUINO
#include <Wire.h>
#endif

namespace sbs::io::i2c {
constexpr uint8_t byteShift       = 8U; ///< Constant to shift a whole byte
constexpr uint8_t doubleByteShift = 16U;///< Constant to shift 2 bytes
constexpr uint8_t tripleByteShift = 24U;///< Constant to shift 3 bytes

/**
 * \brief Simple structure to emulate i2c communication
 */
struct emulatedWire {
    /// If emulation active
    bool actived = false;
    /**
     * @brief Define buffer size and content.
     * @param size_ Buffer size.
     * @param buffer_ Buffer content.
     */
    void setBuffer(uint8_t size_, const uint8_t* buffer_){
        memcpy(buffer,buffer_, math::min<uint8_t>(size_,50U));
        cursor = 0;
        size =size_;
    }
    /**
     * @brief Read buffer and advance cursor
     * @return The data read
     */
    uint8_t read(){
        if (cursor>=size) {
            return 0;
        }
        return buffer[cursor++];
    }
private:
    /// buffer data
    uint8_t buffer[50];
    /// Cursor in the buffer
    uint8_t cursor = 0;
    /// buffer size
    uint8_t size = 0;
};
/// instance of the i2c emulation
static emulatedWire EmulatedWire{};

void setEmulatedMode(bool emulated_){
    EmulatedWire.actived = emulated_;
}

void setEmulatedBuffer(uint8_t size, uint8_t* buffer){
    if (!EmulatedWire.actived)
        return;
    EmulatedWire.setBuffer(size,buffer);
}

/**
 * @brief Basic Wire Read
 * @return Read byte
 */
uint32_t _read() {
    if (EmulatedWire.actived){
        return EmulatedWire.read();
    }
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
    //if (EmulatedWire.actived){
    //    std::cout << "Request byte @ " << std::hex << static_cast<int>(reg) << "\n";
    //}
#ifdef ARDUINO
    Wire.requestFrom(address, 1U);
#endif
    uint8_t value = _read();
#ifdef ARDUINO
    Wire.endTransmission();
#endif
    return value;
}

[[nodiscard]] int8_t readS8(uint8_t address, uint8_t reg) { return static_cast<int8_t>(read8(address, reg)); }


void read(uint8_t address, uint8_t reg, uint8_t size_, uint8_t* output, bool lowFirst) {
    //if (EmulatedWire.actived){
    //    std::cout << "Request " << std::dec << static_cast<int>(size_) << " bytes @ " << std::hex << static_cast<int>(reg) << "\n";
    //}
    _write(address, reg);
#ifdef ARDUINO
    Wire.requestFrom(address, size_);
#endif
    for (uint8_t i = 0; i < size_; ++i) {
        if (lowFirst) {
            output[i] = _read();
        } else {
            output[size_ - i - 1] = _read();
        }
    }
#ifdef ARDUINO
    Wire.endTransmission();
#endif
}

[[nodiscard]] uint16_t read16(uint8_t address, uint8_t reg, [[maybe_unused]] bool lowFirst) {
    uint16_t value = 0;
    read(address, reg, 2, reinterpret_cast<uint8_t*>(&value), lowFirst);
    return value;
}

[[nodiscard]] int16_t readS16(uint8_t address, uint8_t reg, bool lowFirst) {
    return static_cast<int16_t>(read16(address, reg, lowFirst));
}

[[nodiscard]] uint32_t read24(uint8_t address, uint8_t reg, [[maybe_unused]] bool lowFirst) {
    uint32_t value = 0;
    read(address, reg, 3, reinterpret_cast<uint8_t*>(&value), lowFirst);
    return value;
}

[[nodiscard]] int32_t readS24(uint8_t address, uint8_t reg, bool lowFirst) {
    return static_cast<int32_t>(read24(address, reg, lowFirst));
}

[[nodiscard]] uint32_t read32(uint8_t address, uint8_t reg, [[maybe_unused]] bool lowFirst) {
    uint32_t value = 0;
    read(address, reg, 4, reinterpret_cast<uint8_t*>(&value), lowFirst);
    return value;
}

[[nodiscard]] int32_t readS32(uint8_t address, uint8_t reg, bool lowFirst) {
    return static_cast<int32_t>(read32(address, reg, lowFirst));
}

}// namespace sbs::io::i2c

/**
 * @file hardwareUtils.cpp
 * @author damien.lachouette 
 * @date 14/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "hardwareUtils.h"

#if defined(ARDUINO_ARCH_AVR)
#include <avr/pgmspace.h>
#include <avr/boot.h>
#include <algorithm>
#include <vector>
#elif defined(ARDUINO_ARCH_SAMD)
#include <samd.h>
#elif defined(ESP8266)
#include <core_esp8266_features.h>
#elif defined(NATIVE)
#endif

namespace sys::base::core {

#if defined(ARDUINO_ARCH_AVR)

struct signatureType {
    uint8_t sig[3];
    const char* desc;
    uint32_t flashSize;
    uint32_t baseBootSize;
};

// see Atmega328 datasheet page 298
const std::vector<signatureType> signatures = {
        // Attiny84 family
        {{0x1E, 0x91, 0x0B}, "ATtiny24", 2 * kb, 0},
        {{0x1E, 0x92, 0x07}, "ATtiny44", 4 * kb, 0},
        {{0x1E, 0x93, 0x0C}, "ATtiny84", 8 * kb, 0},
        // Attiny85 family
        {{0x1E, 0x91, 0x08}, "ATtiny25", 2 * kb, 0},
        {{0x1E, 0x92, 0x06}, "ATtiny45", 4 * kb, 0},
        {{0x1E, 0x93, 0x0B}, "ATtiny85", 8 * kb, 0},
        // Atmega328 family
        {{0x1E, 0x92, 0x0A}, "ATmega48PA", 4 * kb, 0},
        {{0x1E, 0x93, 0x0F}, "ATmega88PA", 8 * kb, 256},
        {{0x1E, 0x94, 0x0B}, "ATmega168PA", 16 * kb, 256},
        {{0x1E, 0x94, 0x06}, "ATmega168V", 16 * kb, 256},
        {{0x1E, 0x95, 0x0F}, "ATmega328P", 32 * kb, 512},
        {{0x1E, 0x95, 0x16}, "ATmega328PB", 32 * kb, 512},
        // Atmega644 family
        {{0x1E, 0x94, 0x0A}, "ATmega164P", 16 * kb, 256},
        {{0x1E, 0x95, 0x08}, "ATmega324P", 32 * kb, 512},
        {{0x1E, 0x96, 0x0A}, "ATmega644P", 64 * kb, 1 * kb},
        // Atmega2560 family
        {{0x1E, 0x96, 0x08}, "ATmega640", 64 * kb, 1 * kb},
        {{0x1E, 0x97, 0x03}, "ATmega1280", 128 * kb, 1 * kb},
        {{0x1E, 0x97, 0x04}, "ATmega1281", 128 * kb, 1 * kb},
        {{0x1E, 0x98, 0x01}, "ATmega2560", 256 * kb, 1 * kb},
        {{0x1E, 0x98, 0x02}, "ATmega2561", 256 * kb, 1 * kb},
        // AT90USB family
        {{0x1E, 0x93, 0x82}, "At90USB82", 8 * kb, 512},
        {{0x1E, 0x94, 0x82}, "At90USB162", 16 * kb, 512},
        // Atmega32U2 family
        {{0x1E, 0x93, 0x89}, "ATmega8U2", 8 * kb, 512},
        {{0x1E, 0x94, 0x89}, "ATmega16U2", 16 * kb, 512},
        {{0x1E, 0x95, 0x8A}, "ATmega32U2", 32 * kb, 512},
        // Atmega32U4 family
        {{0x1E, 0x94, 0x88}, "ATmega16U4", 16 * kb, 512},
        {{0x1E, 0x95, 0x87}, "ATmega32U4", 32 * kb, 512},
        // ATmega1284P family
        {{0x1E, 0x97, 0x05}, "ATmega1284P", 128 * kb, 1 * kb},
        {{0x1E, 0x97, 0x06}, "ATmega1284", 128 * kb, 1 * kb},
        // ATtiny4313 family
        {{0x1E, 0x91, 0x0A}, "ATtiny2313A", 2 * kb, 0},
        {{0x1E, 0x92, 0x0D}, "ATtiny4313", 4 * kb, 0},
        // ATtiny13 family
        {{0x1E, 0x90, 0x07}, "ATtiny13A", 1 * kb, 0},
        // Atmega8A family
        {{0x1E, 0x93, 0x07}, "ATmega8A", 8 * kb, 256},

};// end of signatures

data::DString getSystemInfo() {
    data::DString result;
    uint8_t sig[3];
    result += F("Architecture = AVR \n");
    result += F("Signature = ");
    sig[0] = boot_signature_byte_get(0);
    result += data::DString(sig[0], data::IntFormat::Hexadecimal);
    result += F(" ");
    sig[1] = boot_signature_byte_get(2);
    result += data::DString(sig[1], data::IntFormat::Hexadecimal);
    result += F(" ");
    sig[2] = boot_signature_byte_get(4);
    result += data::DString(sig[1], data::IntFormat::Hexadecimal);
    result += F("\n");

    result += F("Fuses");
    uint8_t fuse;

    result += F("\nLow = ");
    fuse = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
    result += data::DString(fuse, data::IntFormat::Hexadecimal);
    result += F("\nHigh = ");
    fuse = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
    result += data::DString(fuse, data::IntFormat::Hexadecimal);
    result += F("\nExt = ");
    fuse = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
    result += data::DString(fuse, data::IntFormat::Hexadecimal);
    result += F("\nLock = ");
    fuse = boot_lock_fuse_bits_get(GET_LOCK_BITS);
    result += data::DString(fuse, data::IntFormat::Hexadecimal);
    result += F("\n\n");

    auto foundSig = std::find_if(signatures.begin(), signatures.end(),
                                 [&sig](const signatureType& signa) { return sig[0] == signa.sig[0] && sig[1] == signa.sig[1] && sig[2] == signa.sig[2] });
    if (foundSig == signatures.end()) {
        result += F("Unrecogized signature.\n");
        return result;
    }
    result += data::DString(F("Processor = ")) + foundSig->desc + F("\n");
    result += data::DString(F("Flash memory size = ")) + data::DString(foundSig->flashSize, data::IntFormat::Decimal) + F("\n");
    return result;
}
#elif  defined(ARDUINO_ARCH_SAMD)

data::DString getSystemInfo() {
    data::DString result;
    result += F("Architecture = SAMD \n");
    result += data::DString(F("Processor freq= ")) + data::DString(SystemCoreClock,data::IntFormat::Decimal) + F("Hz \n");
    result += data::DString(F("Flash memory size = ")) + data::DString(static_cast<uint32_t>(FLASH_SIZE), data::IntFormat::Decimal) + F("\n");
    return result;
}

#elif  defined(ESP8266)
data::DString getSystemInfo() {
    data::DString result;
    result += F("Architecture = ESP8266 \n");
    result += data::DString(F("Processor freq= ")) + data::DString(esp_get_cpu_freq_mhz(),data::IntFormat::Decimal) + F("MHz \n");
    return result;
}
#elif  defined(NATIVE)
data::DString getSystemInfo() {
    data::DString result;
    result += F("Architecture = NATIVE \n");
    return result;
}
#endif



}// namespace sys::base::core

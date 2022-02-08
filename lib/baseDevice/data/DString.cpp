/**
 * @file DString.cpp
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#ifndef ARDUINO
#include <bitset>
#include <iomanip>
#include <sstream>
#endif
#include "DString.h"
#include <fmt/format.h>

namespace sys::data {

DString::DString(uint8_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case IntFormat::Binary:
        fromStr(fmt::format("{:08b}", number));
        break;
    case IntFormat::Octal:
        fromStr(fmt::format("{:04o}", number));
        break;
    case IntFormat::Decimal:
        fromStr(fmt::format("{:d}", number));
        break;
    case IntFormat::Hexadecimal:
        fromStr(fmt::format("{:02x}", number));
        break;
    }
}

DString::DString(uint16_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case IntFormat::Binary:
        fromStr(fmt::format("{:016b}", number));
        break;
    case IntFormat::Octal:
        fromStr(fmt::format("{:08o}", number));
        break;
    case IntFormat::Decimal:
        fromStr(fmt::format("{:d}", number));
        break;
    case IntFormat::Hexadecimal:
        fromStr(fmt::format("{:04x}", number));
        break;
    }
}

DString::DString(uint32_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case IntFormat::Binary:
        fromStr(fmt::format("{:032b}", number));
        break;
    case IntFormat::Octal:
        fromStr(fmt::format("{:016o}", number));
        break;
    case IntFormat::Decimal:
        fromStr(fmt::format("{:d}", number));
        break;
    case IntFormat::Hexadecimal:
        fromStr(fmt::format("{:08x}", number));
        break;
    }
}

DString::DString(uint64_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case IntFormat::Binary:
        fromStr(fmt::format("{:064b}", number));
        break;
    case IntFormat::Octal:
        fromStr(fmt::format("{:032o}", number));
        break;
    case IntFormat::Decimal:
        fromStr(fmt::format("{:d}", number));
        break;
    case IntFormat::Hexadecimal:
        fromStr(fmt::format("{:016x}", number));
        break;
    }
}

DString::DString(int8_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case IntFormat::Binary:
        fromStr(fmt::format("{:08b}", static_cast<uint8_t>(number)));
        break;
    case IntFormat::Octal:
        fromStr(fmt::format("{:04o}", static_cast<uint8_t>(number)));
        break;
    case IntFormat::Decimal:
        fromStr(fmt::format("{:d}", number));
        break;
    case IntFormat::Hexadecimal:
        fromStr(fmt::format("{:02x}", static_cast<uint8_t>(number)));
        break;
    }
}

DString::DString(int16_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case IntFormat::Binary:
        fromStr(fmt::format("{:016b}", static_cast<uint16_t>(number)));
        break;
    case IntFormat::Octal:
        fromStr(fmt::format("{:08o}", static_cast<uint16_t>(number)));
        break;
    case IntFormat::Decimal:
        fromStr(fmt::format("{:d}", number));
        break;
    case IntFormat::Hexadecimal:
        fromStr(fmt::format("{:04x}", static_cast<uint16_t>(number)));
        break;
    }
}

DString::DString(int32_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case IntFormat::Binary:
        fromStr(fmt::format("{:032b}", static_cast<uint32_t>(number)));
        break;
    case IntFormat::Octal:
        fromStr(fmt::format("{:016o}", static_cast<uint32_t>(number)));
        break;
    case IntFormat::Decimal:
        fromStr(fmt::format("{:d}", number));
        break;
    case IntFormat::Hexadecimal:
        fromStr(fmt::format("{:08x}", static_cast<uint32_t>(number)));
        break;
    }
}

DString::DString(int64_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case IntFormat::Binary:
        fromStr(fmt::format("{:064b}", static_cast<uint64_t>(number)));
        break;
    case IntFormat::Octal:
        fromStr(fmt::format("{:032o}", static_cast<uint64_t>(number)));
        break;
    case IntFormat::Decimal:
        fromStr(fmt::format("{:d}", number));
        break;
    case IntFormat::Hexadecimal:
        fromStr(fmt::format("{:016x}", static_cast<uint64_t>(number)));
        break;
    }
}

DString::DString(float number, const FloatFormat& format, const uint8_t decimals) {
    switch (format) {
    case FloatFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case FloatFormat::Decimal:
        fromStr(fmt::format("{:." + fmt::format("{}", decimals) + "f}", number));
        break;
    case FloatFormat::Scientific:
        fromStr(fmt::format("{:." + fmt::format("{}", decimals) + "e}", number));
        break;
    }
}

DString::DString(double number, const FloatFormat& format, const uint8_t decimals) {
    switch (format) {
    case FloatFormat::Auto:
        fromStr(fmt::format("{}", number));
        break;
    case FloatFormat::Decimal:
        fromStr(fmt::format("{:." + fmt::format("{}", decimals) + "f}", number));
        break;
    case FloatFormat::Scientific:
        fromStr(fmt::format("{:." + fmt::format("{}", decimals) + "e}", number));
        break;
    }
}

DString& DString::operator+=(const DString& other) {
    internal += other.internal;
    return *this;
}

DString DString::operator+(const DString& other) const {
    DString res(*this);
    res += other;
    return res;
}

DString& DString::operator/=(const DString& other) {
    internal += F("/") + other.internal;
    return *this;
}

DString DString::operator/(const DString& other) const {
    DString res(*this);
    res /= other;
    return res;
}

void DString::fromStr(std::string&& str) {
#ifdef ARDUINO
    internal = str.c_str();
#else
    internal = std::move(str);
#endif
}

bool DString::startsWith([[maybe_unused]] const DString& pattern) const {
#ifdef ARDUINO
    return internal.startsWith(pattern.c_str());
#else
    return internal.rfind(pattern.c_str(), 0) == 0;
#endif
}

bool DString::endsWith([[maybe_unused]] const DString& pattern) const {
#ifdef ARDUINO
    return internal.endsWith(pattern.c_str());
#else
    return internal.rfind(pattern.c_str()) == internal.size() - pattern.size();
#endif
}

DString DString::getFirstWord() const {
    return substr(0, firstIndexOf(F(" ")));
}

DString DString::getFirstLine() const {
    auto fin = firstIndexOf(F("\n"));
    if (fin != npos)
        ++fin;
    return substr(0, fin);
}

DString::size_type DString::firstIndexOf(const DString& pattern) const {
#ifdef ARDUINO
    return internal.indexOf(pattern.c_str());
#else
    return internal.find(pattern.c_str());
#endif
}

DString::size_type DString::lastIndexOf(const DString& pattern) const {
#ifdef ARDUINO
    return internal.lastIndexOf(pattern.c_str());
#else
    return internal.rfind(pattern.c_str());
#endif
}

DString DString::substr(DString::const_iterator start, DString::size_type length) const {
    unsigned int index = start - internal.begin();
#ifdef ARDUINO
    if (length == 0) {
        return internal.substring(index);
    }
    return internal.substring(index, index + length);
#else
    if (length == 0) {
        return internal.substr(index);
    }
    return internal.substr(index, index + length);
#endif
}

void DString::removeFirstWord() {
    auto index = firstIndexOf(F(" "));
    if (index == npos) {
        internal = internal_str{};
        return;
    }
    internal = substr(index+1).c_str();
}

void DString::removeFirstLine() {
    auto index = firstIndexOf(F("\n"));
    if (index == npos) {
        internal = internal_str{};
        return;
    }
    internal = substr(index+1).c_str();
}


}// namespace sys::data

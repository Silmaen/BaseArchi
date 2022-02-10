/**
 * @file DString.cpp
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "DString.h"

#ifdef USE_FMT
#include <fmt/core.h>
#else
#include <math.h>
#endif


namespace sys::data {

#ifndef USE_FMT
constexpr char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void binary(DString::internal_str& buffer, uint64_t number, uint8_t bits) {
    uint64_t mask = 1ULL << (bits - 1);
    for (uint8_t index = 0; index < bits; ++index) {
        buffer += (number & mask) ? '1' : '0';
        mask >>= 1;
    }
}

void octal(DString::internal_str& buffer, uint64_t number, uint8_t bits, uint64_t bigMask) {
    constexpr uint8_t mask = 0b111;
    number &= bigMask;
    for (uint8_t index = 0; index < bits; ++index) {
        buffer += digits[(number >> (3 * (bits - index - 1))) & mask];
    }
}

void hexadecimal(DString::internal_str& buffer, int64_t number, uint8_t bits) {
    constexpr uint8_t mask  = 0b1111;
    for (uint8_t index = 0; index < bits; ++index) {
        buffer += digits[(number >> (4 * (bits - index - 1))) & mask];
    }
}

void decimal(DString::internal_str& buffer, int64_t number) {
    if (number < 0) {
        buffer += '-';
        number *= -1;
    }
    int l10    = log10(number);
    double p10 = pow(10, l10);
    for (uint8_t i_dig = 0; i_dig <= l10; i_dig++) {
        uint8_t ddd = number / p10;
        number -= ddd * p10;
        p10 /= 10;
        buffer += digits[ddd];
    }
}

template<class T>
T round(T number, uint8_t decimals) {
    T p10 = pow(10, decimals);
    T res = floor(p10 * number);
    if (p10 * number - res > 0.5)
        return (res + 1) / p10;
    return res / p10;
}

template<class T>
inline T myabs(T val){
    return val>0?val:-val;
}

template<class T>
void decimal(DString::internal_str& buffer, T number, uint8_t decimals) {
    if (number < 0) {
        buffer += '-';
        number *= -1;
    }
    if (decimals == 255) {
        for (uint8_t decim = 1; decim < 15; decim++) {
            if (myabs(number - round<T>(number, decim)) * pow(10, decim) < 0.09) {
                decimals = decim;
                break;
            }
        }
    } else {
        number = round<T>(number, decimals);
    }
    int l10 = log10(number);
    if (l10 > 0) {
        T p10 = pow(10, l10);
        for (uint8_t i_dig = 0; i_dig <= l10; i_dig++) {
            uint8_t ddd = number / p10;
            number -= ddd * p10;
            p10 /= 10;
            buffer += digits[ddd];
        }
    } else {
        uint8_t ddd = floor(number);
        number -= ddd;
        buffer += digits[ddd];
    }
    buffer += '.';
    T p10 = 0.1;
    uint8_t ddd;
    for (uint8_t i_dig = 0; i_dig < decimals; i_dig++) {
        if (i_dig == decimals - 1) {
            ddd = round<T>(number / p10, 0);
        } else {
            ddd = number / p10;
        }
        number -= ddd * p10;
        p10 /= 10;
        buffer += digits[ddd];
    }
}

template<class T>
void scientific(DString::internal_str& buffer, T number, uint8_t decimals) {
    int l10                 = log10(number);
    if (l10 < 0) --l10;
    number /= pow(10, l10);
    decimal<T>(buffer, number, decimals);
    buffer += 'e';
    if (l10 < 0) {
        buffer += '-';
        l10 *= -1;
    } else {
        buffer += '+';
    }
    buffer += digits[l10 / 10];
    buffer += digits[l10 % 10];
}
#endif

DString::DString(uint8_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Binary:
#ifdef USE_FMT
        fromStr(fmt::format("{:08b}", number));
#else
        binary(internal, number, 8);
#endif
        break;
    case IntFormat::Octal:
#ifdef USE_FMT
        fromStr(fmt::format("{:03o}", number));
#else
        octal(internal, number, 3, 0xff);
#endif
        break;
    case IntFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:d}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Hexadecimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:02x}", number));
#else
        hexadecimal(internal, number, 2);
#endif
        break;
    }
}

DString::DString(uint16_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Binary:
#ifdef USE_FMT
        fromStr(fmt::format("{:016b}", number));
#else
        binary(internal, number, 16);
#endif
        break;
    case IntFormat::Octal:
#ifdef USE_FMT
        fromStr(fmt::format("{:06o}", number));
#else
        octal(internal, number, 6, 0xffff);
#endif
        break;
    case IntFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:d}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Hexadecimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:04x}", number));
#else
        hexadecimal(internal, number, 4);
#endif
        break;
    }
}

DString::DString(uint32_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Binary:
#ifdef USE_FMT
        fromStr(fmt::format("{:032b}", number));
#else
        binary(internal, number, 32);
#endif
        break;
    case IntFormat::Octal:
#ifdef USE_FMT
        fromStr(fmt::format("{:012o}", number));
#else
        octal(internal, number, 12, 0xffffffff);
#endif
        break;
    case IntFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:d}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Hexadecimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:08x}", number));
#else
        hexadecimal(internal, number, 8);
#endif
        break;
    }
}

DString::DString(uint64_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Binary:
#ifdef USE_FMT
        fromStr(fmt::format("{:064b}", number));
#else
        binary(internal, number, 64);
#endif
        break;
    case IntFormat::Octal:
#ifdef USE_FMT
        fromStr(fmt::format("{:022o}", number));
#else
        octal(internal, number, 22, 0xffffffffffffffff);
#endif
        break;
    case IntFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:d}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Hexadecimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:016x}", number));
#else
        hexadecimal(internal, number, 16);
#endif
        break;
    }
}

DString::DString(int8_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Binary:
#ifdef USE_FMT
        fromStr(fmt::format("{:08b}", static_cast<uint8_t>(number)));
#else
        binary(internal, number, 8);
#endif
        break;
    case IntFormat::Octal:
#ifdef USE_FMT
        fromStr(fmt::format("{:03o}", static_cast<uint8_t>(number)));
#else
        octal(internal, number, 3, 0xff);
#endif
        break;
    case IntFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:d}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Hexadecimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:02x}", static_cast<uint8_t>(number)));
#else
        hexadecimal(internal, number, 2);
#endif
        break;
    }
}

DString::DString(int16_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Binary:
#ifdef USE_FMT
        fromStr(fmt::format("{:016b}", static_cast<uint16_t>(number)));
#else
        binary(internal, number, 16);
#endif
        break;
    case IntFormat::Octal:
#ifdef USE_FMT
        fromStr(fmt::format("{:06o}", static_cast<uint16_t>(number)));
#else
        octal(internal, number, 6, 0xffff);
#endif
        break;
    case IntFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:d}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Hexadecimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:04x}", static_cast<uint16_t>(number)));
#else
        hexadecimal(internal, number, 4);
#endif
        break;
    }
}

DString::DString(int32_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Binary:
#ifdef USE_FMT
        fromStr(fmt::format("{:032b}", static_cast<uint32_t>(number)));
#else
        binary(internal, number, 32);
#endif
        break;
    case IntFormat::Octal:
#ifdef USE_FMT
        fromStr(fmt::format("{:012o}", static_cast<uint32_t>(number)));
#else
        octal(internal, number, 12, 0xffffffff);
#endif
        break;
    case IntFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:d}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Hexadecimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:08x}", static_cast<uint32_t>(number)));
#else
        hexadecimal(internal, number, 8);
#endif
        break;
    }
}

DString::DString(int64_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Binary:
#ifdef USE_FMT
        fromStr(fmt::format("{:064b}", static_cast<uint64_t>(number)));
#else
        binary(internal, number, 64);
#endif
        break;
    case IntFormat::Octal:
#ifdef USE_FMT
        fromStr(fmt::format("{:022o}", static_cast<uint64_t>(number)));
#else
        octal(internal, number, 22, 0xffffffffffffffff);
#endif
        break;
    case IntFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:d}", number));
#else
        decimal(internal, number);
#endif
        break;
    case IntFormat::Hexadecimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:016x}", static_cast<uint64_t>(number)));
#else
        hexadecimal(internal, number, 16);
#endif
        break;
    }
}

DString::DString(float number, const FloatFormat& format, const uint8_t decimals) {
    switch (format) {
    case FloatFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        if (log10(number) < -3) {
            scientific(internal, number, 255);
        } else {
            decimal(internal, number, 255);
        }
#endif
        break;
    case FloatFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:." + fmt::format("{}", decimals) + "f}", number));
#else
        decimal(internal, number, decimals);
#endif
        break;
    case FloatFormat::Scientific:
#ifdef USE_FMT
        fromStr(fmt::format("{:." + fmt::format("{}", decimals) + "e}", number));
#else
        scientific(internal, number, decimals);
#endif
        break;
    }
}

DString::DString(double number, const FloatFormat& format, const uint8_t decimals) {
    switch (format) {
    case FloatFormat::Auto:
#ifdef USE_FMT
        fromStr(fmt::format("{}", number));
#else
        if (log10(number) < -3) {
            scientific(internal, number, 255);
        } else {
            decimal(internal, number, 255);
        }
#endif
        break;
    case FloatFormat::Decimal:
#ifdef USE_FMT
        fromStr(fmt::format("{:." + fmt::format("{}", decimals) + "f}", number));
#else
        decimal(internal, number, decimals);
#endif
        break;
    case FloatFormat::Scientific:
#ifdef USE_FMT
        fromStr(fmt::format("{:." + fmt::format("{}", decimals) + "e}", number));
#else
        scientific(internal, number, decimals);
#endif
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
    internal += internal_str(F("/")) + other.internal;
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
    internal = substr(index + 1).c_str();
}

void DString::removeFirstLine() {
    auto index = firstIndexOf(F("\n"));
    if (index == npos) {
        internal = internal_str{};
        return;
    }
    internal = substr(index + 1).c_str();
}


}// namespace sys::data

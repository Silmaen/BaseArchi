/**
 * @file DString.cpp
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "DString.h"
#include "math/functions.h"

namespace sys::data {
/// List of digit characters
constexpr char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

/**
 * @brief Write an integer in binary format
 * @tparam T Integer type
 * @param buffer Where to write
 * @param number What to write
 */
template<class T>
void binary(DString::internal_str& buffer, T number) {
    uint8_t bits  = 8 * sizeof(T);
    uint64_t mask = 1ULL << (bits - 1);
    for (uint8_t index = 0; index < bits; ++index) {
        buffer += (number & mask) ? '1' : '0';
        mask >>= 1;
    }
}

/**
 * @brief Write an integer in octal format
 * @tparam T Integer type
 * @param buffer Where to write
 * @param number What to write
 */
template<class T>
void octal(DString::internal_str& buffer, T number) {
    constexpr uint8_t mask    = 0b111;
    constexpr uint8_t bitc = math::bitCount<T>();
    constexpr uint8_t bits = bitc / 3 + 1;
    T bigMask                 = 1;
    for (uint8_t iter = 0; iter < bitc; ++iter) {
        bigMask <<= 1;
        bigMask |= 1;
    }
    number &= bigMask;
    for (uint8_t index = 0; index < bits; ++index) {
        buffer += digits[(number >> (3 * (bits - index - 1))) & mask];
    }
}

/**
 * @brief Write an integer in hexadecimal format
 * @tparam T Integer type
 * @param buffer Where to write
 * @param number What to write
 */
template<class T>
void hexadecimal(DString::internal_str& buffer, T number) {
    uint8_t bits           = 2 * sizeof(T);
    constexpr uint8_t mask = 0b1111;
    for (uint8_t index = 0; index < bits; ++index) {
        buffer += digits[(number >> (4 * (bits - index - 1))) & mask];
    }
}

/**
 * @brief Write an integer in decimal format
 * @tparam T Integer type
 * @param buffer Where to write
 * @param number What to write
 */
template<class T>
void decimal(DString::internal_str& buffer, T number) {
    if (number < 0) {
        buffer += '-';
        number *= -1;
    }
    uint8_t l10 = math::log10(number);
    double p10  = math::pow10<double>(l10);
    for (uint8_t i_dig = 0; i_dig <= l10; i_dig++) {
        uint8_t ddd = number / p10;
        number -= ddd * p10;
        p10 /= 10;
        buffer += digits[ddd];
    }
}

/**
 * @brief Write an float in decimal format
 * @tparam T Integer type
 * @param buffer Where to write
 * @param number What to write
 * @param decimals Amount of decimals
 */
template<class T>
void decimal(DString::internal_str& buffer, T number, uint8_t decimals) {
    if (number < 0) {
        buffer += '-';
        number *= -1;
    }
    if (decimals == 255) {
        for (uint8_t dec = 1; dec < 15; dec++) {
            if (math::abs(number - math::round<T>(number, dec)) * math::pow10<T>(dec) < 0.09) {
                decimals = dec;
                break;
            }
        }
    } else {
        number = math::round<T>(number, decimals);
    }
    int l10 = math::log10(number);
    if (l10 > 0) {
        T p10 = math::pow10<T>(l10);
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
            ddd = math::round<T>(number / p10, 0);
        } else {
            ddd = number / p10;
        }
        number -= ddd * p10;
        p10 /= 10;
        buffer += digits[ddd];
    }
}

/**
 * @brief Write an float in scientific format
 * @tparam T Integer type
 * @param buffer Where to write
 * @param number What to write
 * @param decimals Amount of decimals
 */
template<class T>
void scientific(DString::internal_str& buffer, T number, uint8_t decimals) {
    int l10 = math::log10(number);
    if (l10 < 0) --l10;
    number /= math::pow10<T>(l10);
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

DString::DString(uint8_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        decimal(internal, number);
        break;
    case IntFormat::Binary:
        binary(internal, number);
        break;
    case IntFormat::Octal:
        octal(internal, number);
        break;
    case IntFormat::Decimal:
        decimal(internal, number);
        break;
    case IntFormat::Hexadecimal:
        hexadecimal(internal, number);
        break;
    }
}

DString::DString(uint16_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        decimal(internal, number);
        break;
    case IntFormat::Binary:
        binary(internal, number);
        break;
    case IntFormat::Octal:
        octal(internal, number);
        break;
    case IntFormat::Decimal:
        decimal(internal, number);
        break;
    case IntFormat::Hexadecimal:
        hexadecimal(internal, number);
        break;
    }
}

DString::DString(uint32_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        decimal(internal, number);
        break;
    case IntFormat::Binary:
        binary(internal, number);
        break;
    case IntFormat::Octal:
        octal(internal, number);
        break;
    case IntFormat::Decimal:
        decimal(internal, number);
        break;
    case IntFormat::Hexadecimal:
        hexadecimal(internal, number);
        break;
    }
}

DString::DString(uint64_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        decimal(internal, number);
        break;
    case IntFormat::Binary:
        binary(internal, number);
        break;
    case IntFormat::Octal:
        octal(internal, number);
        break;
    case IntFormat::Decimal:
        decimal(internal, number);
        break;
    case IntFormat::Hexadecimal:
        hexadecimal(internal, number);
        break;
    }
}

DString::DString(int8_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        decimal(internal, number);
        break;
    case IntFormat::Binary:
        binary(internal, number);
        break;
    case IntFormat::Octal:
        octal<uint8_t>(internal, number);
        break;
    case IntFormat::Decimal:
        decimal(internal, number);
        break;
    case IntFormat::Hexadecimal:
        hexadecimal(internal, number);
        break;
    }
}

DString::DString(int16_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        decimal(internal, number);
        break;
    case IntFormat::Binary:
        binary(internal, number);
        break;
    case IntFormat::Octal:
        octal<uint16_t>(internal, number);
        break;
    case IntFormat::Decimal:
        decimal(internal, number);
        break;
    case IntFormat::Hexadecimal:
        hexadecimal(internal, number);
        break;
    }
}

DString::DString(int32_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        decimal(internal, number);
        break;
    case IntFormat::Binary:
        binary(internal, number);
        break;
    case IntFormat::Octal:
        octal<uint32_t>(internal, number);
        break;
    case IntFormat::Decimal:
        decimal(internal, number);
        break;
    case IntFormat::Hexadecimal:
        hexadecimal(internal, number);
        break;
    }
}

DString::DString(int64_t number, const IntFormat& format) {
    switch (format) {
    case IntFormat::Auto:
        decimal(internal, number);
        break;
    case IntFormat::Binary:
        binary(internal, number);
        break;
    case IntFormat::Octal:
        octal<uint64_t>(internal, number);
        break;
    case IntFormat::Decimal:
        decimal(internal, number);
        break;
    case IntFormat::Hexadecimal:
        hexadecimal(internal, number);
        break;
    }
}

DString::DString(float number, const FloatFormat& format, const uint8_t decimals) {
    switch (format) {
    case FloatFormat::Auto:
        if (log10(number) < -3) {
            scientific(internal, number, 255);
        } else {
            decimal(internal, number, 255);
        }
        break;
    case FloatFormat::Decimal:
        decimal(internal, number, decimals);
        break;
    case FloatFormat::Scientific:
        scientific(internal, number, decimals);
        break;
    }
}

DString::DString(double number, const FloatFormat& format, const uint8_t decimals) {
    switch (format) {
    case FloatFormat::Auto:
        if (log10(number) < -3) {
            scientific(internal, number, 255);
        } else {
            decimal(internal, number, 255);
        }
        break;
    case FloatFormat::Decimal:
        decimal(internal, number, decimals);
        break;
    case FloatFormat::Scientific:
        scientific(internal, number, decimals);
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

bool DString::startsWith(const DString& pattern) const {
#ifdef ARDUINO
    return internal.startsWith(pattern.c_str());
#else
    return internal.rfind(pattern.c_str(), 0) == 0;
#endif
}

bool DString::endsWith(const DString& pattern) const {
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

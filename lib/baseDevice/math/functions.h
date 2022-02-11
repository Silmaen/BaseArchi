/**
 * @file functions.h
 * @author argawaen
 * @date 11/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <math.h>

/**
 * @brief Namespace for mathematical functions
 */
namespace sys::math {

/**
 * @brief Get the amount of bit of given type
 * @tparam T Type to check
 * @return Amount of bits
 */
template<typename T>
constexpr inline uint8_t bitCount() { return 8 * sizeof(T); }

/**
 * @brief Compute the absolute value of a number
 * @tparam T Data type
 * @param val Data
 * @return the absolute value
 */
template<class T>
constexpr inline T abs(T val) {return val > 0 ? val : -val;}

/**
 * @brief Floor of a number
 * @tparam T Data type
 * @param number Data
 * @return The absolute value
 */
template<class T>
constexpr inline T floor(T number) { return ::floor(number); }

/**
 * @brief Power of ten
 * @tparam T Data type
 * @param exponent The exponent
 * @return Power of ten
 */
template<class T>
constexpr inline T pow10(int16_t exponent) {return ::pow(10, exponent);}

/**
 * @brief Log10 of a number
 * @tparam T Data type
 * @param number Data
 * @return The logarithm base 10
 */
template<class T>
constexpr inline T log10(T number) {return ::log10(number);}

/**
 * @brief Round a number
 * @tparam T Data type
 * @param number The number to round
 * @param decimals Amount of decimal to keep
 * @return The rounded number
 */
template<class T>
inline T round(T number, uint8_t decimals) {
    T p10 = pow10<T>(decimals);
    T res = floor(p10 * number);
    if (p10 * number - res > 0.5)
        return (res + 1) / p10;
    return res / p10;
}

}// namespace sys::math

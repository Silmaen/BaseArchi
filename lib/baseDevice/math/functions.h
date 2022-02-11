/**
 * @file math.h
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

template<typename T>
constexpr inline uint8_t bitCount() { return 8 * sizeof(T); }

template<class T>
constexpr inline T abs(T val) {return val > 0 ? val : -val;}


template<class T>
constexpr inline T floor(T number) { return ::floor(number); }

template<class T>
constexpr inline T pow10(int16_t exponent) {return ::pow(10, exponent);}

template<class T>
constexpr inline T log10(T number) {return ::log10(number);}

template<class T>
inline T round(T number, uint8_t decimals) {
    T p10 = pow10<T>(decimals);
    T res = floor(p10 * number);
    if (p10 * number - res > 0.5)
        return (res + 1) / p10;
    return res / p10;
}


}// namespace sys::math

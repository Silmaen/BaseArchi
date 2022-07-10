/**
 * @file base.h
 * @author argawaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

/**
 * @brief Namespace for maths functions.
 */
namespace sbs::math {

/**
 * @brief Get the min between two values
 * @tparam Type Data type (must have operator < defined)
 * @param value1 First value
 * @param value2 Second value
 * @return The lowest of the two values
 */
template<class Type>
constexpr inline Type min(Type value1, Type value2) noexcept {
    return (value1 < value2) ? value1 : value2;
}

/**
 * @brief Get the max between two values
 * @tparam Type Data type (must have operator < defined)
 * @param value1 First value
 * @param value2 Second value
 * @return The highest of the two values
 */
template<class Type>
constexpr inline Type max(Type value1, Type value2) noexcept {
    return (value1 < value2) ? value2 : value1;
}

/**
 * @brief get a value between bounds
 * @tparam Type Data type (must have operator < defined)
 * @param value Value to clamp
 * @param lowerBound Minimal value
 * @param upperBound Maximal value
 * @return Clamped value
 *
 * @note No checks if upperBound higher than lowerBound, user should care about that.
 */
template<class Type>
constexpr inline Type clamp(Type value, Type lowerBound, Type upperBound) noexcept {
    return min(upperBound, max(lowerBound, value));
}

}// namespace sbs::math

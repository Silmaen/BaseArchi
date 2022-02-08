/**
 * @file DString.h
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <string>
#ifdef ARDUINO
#include <WString.h>
#else
/// Macro normally used to define flash string
#define F(X) X
#endif

/**
 * @brief Namespace for data manipulation
 */
namespace sys::data {

/**
 * @brief Set of Integer format
 */
enum struct IntFormat {
    Auto,       ///< Automated formatting
    Binary,     ///< Write number in base 2
    Octal,      ///< Write number in base 8
    Decimal,    ///< Write number in base 10
    Hexadecimal,///< Write number in base 16
};

/**
 * @brief Set of Float format
 */
enum struct FloatFormat {
    Auto,      ///< Automated formatting
    Decimal,   ///< Write Float as decimals
    Scientific,///< Write float in Scientific format
};

/**
 * @brief Class to wrap strings for compatibility between all platforms
 */
class DString {
public:

#ifdef ARDUINO
    /// Internal string's type
    using internal_str              = String;
    /// Internal string's iterator
    using iterator                  = char*;
    /// Internal string's const iterator
    using const_iterator            = const char*;
    /// Internal string's size type
    using size_type                 = int;
    /// Internal string's size difference type
    using diff_type                 = int;
    /// Internal string's no position
    static constexpr size_type npos = -1;
#else
    /// Internal string's type
    using internal_str              = std::string;
    /// Internal string's iterator
    using iterator                  = internal_str::iterator;
    /// Internal string's const iterator
    using const_iterator            = internal_str::const_iterator;
    /// Internal string's size type
    using size_type                 = internal_str::size_type;
    /// Internal string's size difference type
    using diff_type                 = internal_str::difference_type;
    /// Internal string's no position
    static constexpr size_type npos = internal_str::npos;
#endif

    /**
     * @brief Default constructor.
     */
    DString() = default;

    /**
     * @brief Destructor.
     */
    virtual ~DString() = default;

    /**
     * @brief Copy constructor
     */
    DString(const DString&) = default;

    /**
     * @brief Move constructor
     */
    DString(DString&&) = default;

    /**
     * @brief Copy affectation
     * @return this
     */
    DString& operator=(const DString&) = default;

    /**
     * @brief Move affectation
     * @return this
     */
    DString& operator=(DString&&) = default;

    /**
     * @brief Move constructor
     * @param str The String to move
     */
    DString(internal_str&& str) :
        internal{std::move(str)} {}

    /**
     * @brief Copy constructor
     * @param str The String to copy
     */
    DString(const char* str) :
        internal{str} {}
#ifdef ARDUINO
    /**
     * @brief Copy constructor
     * @param str The String to copy
     */
    DString(const __FlashStringHelper* str) :
        internal{str} {}
#endif
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     */
    DString(uint8_t number, const IntFormat& format = IntFormat::Auto);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     */
    DString(uint16_t number, const IntFormat& format = IntFormat::Auto);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     */
    DString(uint32_t number, const IntFormat& format = IntFormat::Auto);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     */
    DString(uint64_t number, const IntFormat& format = IntFormat::Auto);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     */
    DString(int8_t number, const IntFormat& format = IntFormat::Auto);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     */
    DString(int16_t number, const IntFormat& format = IntFormat::Auto);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     */
    DString(int32_t number, const IntFormat& format = IntFormat::Auto);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     */
    DString(int64_t number, const IntFormat& format = IntFormat::Auto);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     * @param decimals The amount of decimals to print
     */
    DString(float number, const FloatFormat& format = FloatFormat::Auto, uint8_t decimals = 2);
    /**
     * @brief Constructor form int number with formatting
     * @param number The number to format
     * @param format The requested format
     * @param decimals The amount of decimals to print
     */
    DString(double number, const FloatFormat& format = FloatFormat::Auto, uint8_t decimals = 2);

    /**
     * @brief Conversion to native type
     * @return The string as native type
     *
     */
    [[nodiscard]] const internal_str& string() const { return internal; }

    /**
     * @brief Conversion to Constant char array
     * @return Constant char array
     */
    [[nodiscard]] const char* c_str() const { return internal.c_str(); }

    /**
     * @brief Equality operator
     * @param other The other string to compare
     * @return True if identical
     */
    [[nodiscard]] bool operator==(const DString& other) const { return internal == other.internal; }

    /**
     * @brief Equality operator
     * @param other The other string to compare
     * @return True if identical
     */
    [[nodiscard]] bool operator!=(const DString& other) const { return internal != other.internal; }

    /**
     * @brief Concatenation
     * @param other The other string to append to this one
     * @return this
     */
    DString& operator+=(const DString& other);

    /**
     * @brief Concatenation
     * @param other The other string to append to this one
     * @return merged strings
     */
    DString operator+(const DString& other) const;

    /**
     * @brief Concatenation with folder separator
     * @param other The other string to append to this one
     * @return this
     */
    DString& operator/=(const DString& other);

    /**
     * @brief Concatenation with folder separator
     * @param other The other string to append to this one
     * @return merged strings
     */
    DString operator/(const DString& other) const;

    /**
     * @brief Begin iterator
     * @return Begin iterator
     */
    [[nodiscard]] iterator begin() { return internal.begin(); }
    /**
     * @brief Begin constant iterator
     * @return Begin constant iterator
     */
    [[nodiscard]] const_iterator begin() const { return internal.begin(); }

    /**
     * @brief End iterator
     * @return End iterator
     */
    iterator end() { return internal.end(); }

    /**
     * @brief End constant iterator
     * @return End constant iterator
     */
    [[nodiscard]] const_iterator end() const { return internal.end(); }

    /**
     * @brief Check if the string begins with the given pattern
     * @param pattern Pattern to check
     * @return True if the string starts with the given pattern
     */
    [[nodiscard]] bool startsWith(const DString& pattern) const;

    /**
     * @brief Check if the string ends with the given pattern
     * @param pattern Pattern to check
     * @return True if the string ends with the given pattern
     */
    [[nodiscard]] bool endsWith(const DString& pattern) const;

    /**
     * @brief Get the size of the string
     * @return Size of the string
     */
    [[nodiscard]] size_type size() const {
#ifdef ARDUINO
        return internal.length();
#else
        return internal.size();
#endif
    }

    /**
     * @brief Get the first word of the string
     * @return The first word
     */
    [[nodiscard]] DString getFirstWord() const;

    /**
     * @brief Get the first line of the string
     * @return The first line
     */
    [[nodiscard]] DString getFirstLine() const;

    /**
     * @brief Cut the first word of the string
     */
    void removeFirstWord();

    /**
     * @brief Cut the first line of the string
     */
    void removeFirstLine();
    /**
     * @brief Get the index of the first occurrence of a pattern
     * @param pattern The pattern to check
     * @return The index
     */
    [[nodiscard]] size_type firstIndexOf(const DString& pattern) const;

    /**
     * @brief Get the index of the last occurrence of a pattern
     * @param pattern The pattern to check
     * @return The index
     */
    [[nodiscard]] size_type lastIndexOf(const DString& pattern) const;

    /**
     * @brief Get a sub string
     * @param startIndex Stating index
     * @param length The length to extract (0 mean until the end)
     * @return The sub string
     */
    [[nodiscard]] DString substr(size_type startIndex, size_type length = 0) const { return substr(begin() + static_cast<diff_type>(startIndex), length); }

    /**
     * @brief Get a sub string
     * @param start Stating iterator
     * @param length The length to extract (0 mean until the end)
     * @return The sub string
     */
    [[nodiscard]] DString substr(const_iterator start, size_type length = 0) const;

    /**
     * @brief Check the emptiness of the string
     * @return True if empty string
     */
    [[nodiscard]] bool empty() const {
#ifdef ARDUINO
        return internal.isEmpty();
#else
        return internal.empty();
#endif
    }

private:
    /// Internal string object
    internal_str internal;

    /**
     * @brief Conversion from standard string
     * @param str Standard string
     */
    void fromStr(std::string&& str);
};

}// namespace sys::data

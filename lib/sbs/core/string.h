/**
 * @file string.h
 * @author Silmaen
 * @date 21/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#ifdef ARDUINO
#include <WString.h>
#else
#include <string>
#endif

namespace sbs {
/**
 * @brief Abstraction class usable in all platforms
 */
#ifdef ARDUINO
class string : public String {
#else
class string : public std::string {
#endif
public:
    string()          = default;
    virtual ~string() = default;
    /**
     * @brief Copy constructor
     */
    string(const string&) = default;
    /**
     * @brief Move constructor
     */
    string(string&&) = default;
    /**
     * @brief Copy assignment
     * @return this
     */
    string& operator=(const string&) = default;
    /**
     * @brief Move assignment
     * @return this
     */
    string& operator=(string&&) = default;
#ifdef ARDUINO
    using size_type = unsigned int;
    string(const char* str) :
        String(str) {}
    string(const String& str) :
        String(str) {}
    string(const __FlashStringHelper* str) :
        String(str) {}
    string(int number) :
        String(number) {}
#ifdef ARDUINO_ARCH_SAMD
    [[nodiscard]] bool empty() const { return length() == 0; }
#else
    [[nodiscard]] bool empty() const { return isEmpty(); }
#endif
    [[nodiscard]] string substr(size_type begin, size_type end) const { return substring(begin, end); }
    [[nodiscard]] string substr(size_type begin) const { return substring(begin); }
    [[nodiscard]] char back() const { return *(begin() + length() - 1); }
    void pop_back() { remove(length() - 1, 1); }
    [[nodiscard]] size_type find(const string& str, size_type from = 0) const { return indexOf(str, from); }
    [[nodiscard]] size_type find(char str, size_type from = 0) const { return indexOf(str, from); }
    static constexpr size_type npos = -1;
    void erase(const char* pos) {
        int index = pos - c_str();
        remove(index, 1);
    }
#else
    /**
     * @brief Constructor from char type
     * @param str The origin string
     */
    string(const char* str) :
        std::string(str) {}
    /**
     * @brief Constructor by std::string
     * @param str The origin string
     */
    string(const std::string& str) :
        std::string(str) {}
    /**
     * @brief std::string conversion
     * @return Converted string
     */
    [[nodiscard]] std::string s_str() const { return c_str(); }
#endif
private:
};

}// namespace sbs

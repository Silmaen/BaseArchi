/**
 * @file Print.h
 * @author Silmaen
 * @date 12/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "string.h"

namespace sbs::io {

/**
 * @brief Format for Int
 */
enum struct IntFormat {
    Auto,///< Keep automated version
    Decimal,///< Force decimal format
    Binary, ///< Binary format
    Hexadecimal ///< Hexadecimal format
};
/**
 * @brief Verbosity level
 */
enum struct Verbosity {
    Mute,   ///< Nothing display not even the log
    Error,  ///< Print error & log
    Warning,///< Print error, warning and log
    Debug,  ///< Print error, warning, debug and log
};

/**
 * @brief Print string as log verbosity
 * @param str The string to print
 */
void logger(const char* str);
/**
 * @brief Print string as log verbosity
 * @param str The string to print
 */
void logger(const string& str);
/**
 * @brief Print integer as log verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void logger(uint8_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as log verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void logger(int8_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as log verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void logger(uint16_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as log verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void logger(int16_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as log verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void logger(uint32_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as log verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void logger(int32_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as log verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void logger(uint64_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as log verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void logger(int64_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print double as log verbosity
 * @param data The double to print
 * @param digit The number of digits to print
 */
void logger(double data, uint8_t digit = 2);


/**
 * @brief Print string as warning verbosity
 * @param str The string to print
 */
void warning(const char* str);

/**
 * @brief Print string as warning verbosity
 * @param str The string to print
 */
void warning(const string& str);
/**
 * @brief Print integer as warning verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void warning(uint8_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as warning verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void warning(int8_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as warning verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void warning(uint16_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as warning verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void warning(int16_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as warning verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void warning(uint32_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as warning verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void warning(int32_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as warning verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void warning(uint64_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as warning verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void warning(int64_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print double as warning verbosity
 * @param data The double to print
 * @param digit The number of digits to print
 */
void warning(double data, uint8_t digit = 2);

/**
 * @brief Print string as error verbosity
 * @param str The string to print
 */
void error(const char* str);

/**
 * @brief Print string as error verbosity
 * @param str The string to print
 */
void error(const string& str);
/**
 * @brief Print integer as error verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void error(uint8_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as error verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void error(int8_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as error verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void error(uint16_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as error verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void error(int16_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as error verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void error(uint32_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as error verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void error(int32_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as error verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void error(uint64_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as error verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void error(int64_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print double as error verbosity
 * @param data The double to print
 * @param digit The number of digits to print
 */
void error(double data, uint8_t digit = 2);


/**
 * @brief Print string as debug verbosity
 * @param str The string to print
 */
void debug(const char* str);

/**
 * @brief Print string as debug verbosity
 * @param str The string to print
 */
void debug(const string& str);
/**
 * @brief Print integer as debug verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void debug(uint8_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as debug verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void debug(int8_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as debug verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void debug(uint16_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as debug verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void debug(int16_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as debug verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void debug(uint32_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as debug verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void debug(int32_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as debug verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void debug(uint64_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print integer as debug verbosity
 * @param data The integer to print
 * @param format The integer format
 */
void debug(int64_t data, const io::IntFormat& format = io::IntFormat::Auto);
/**
 * @brief Print double as debug verbosity
 * @param data The double to print
 * @param digit The number of digits to print
 */
void debug(double data, uint8_t digit = 2);

/**
 * @brief Define the global verbosity level
 * @param verb The new verbosity
 */
void setVerbosity(const io::Verbosity& verb);

}// namespace sbs::io

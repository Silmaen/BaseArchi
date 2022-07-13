/**
 * @file string_utest.cpp
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"

#include <core/Print.h>
static const double hnan = __builtin_nan("");
static const double hinf = __builtin_inf();

void logger_test() {
    // testing mute does not show messages
    {
        SBS_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Mute);
        sbs::io::logger("toto");
        sbs::io::logger(sbs::string{"toto"});
        sbs::io::logger(static_cast<uint8_t>(1));
        sbs::io::logger(static_cast<int8_t>(1));
        sbs::io::logger(static_cast<uint16_t>(1));
        sbs::io::logger(static_cast<int16_t>(1));
        sbs::io::logger(static_cast<uint32_t>(1));
        sbs::io::logger(static_cast<int32_t>(1));
        sbs::io::logger(static_cast<uint64_t>(1));
        sbs::io::logger(static_cast<int64_t>(1));
        sbs::io::logger(1.0);
        SBS_TEST_OUT("")
        SBS_RESET_OUT
    }
    {
        SBS_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::logger("toto");
        sbs::io::logger(sbs::string{"toto"});
        sbs::io::logger(" ");
        sbs::io::logger(static_cast<uint8_t>(1));
        sbs::io::logger(static_cast<uint8_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::logger(static_cast<uint8_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::logger(" ");
        sbs::io::logger(static_cast<int8_t>(1));
        sbs::io::logger(static_cast<int8_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::logger(static_cast<int8_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::logger(" ");
        sbs::io::logger(static_cast<uint16_t>(1));
        sbs::io::logger(static_cast<uint16_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::logger(static_cast<uint16_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::logger(" ");
        sbs::io::logger(static_cast<int16_t>(1));
        sbs::io::logger(static_cast<int16_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::logger(static_cast<int16_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::logger(" ");
        sbs::io::logger(static_cast<uint32_t>(1));
        sbs::io::logger(static_cast<uint32_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::logger(static_cast<uint32_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::logger(" ");
        sbs::io::logger(static_cast<int32_t>(1));
        sbs::io::logger(static_cast<int32_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::logger(static_cast<int32_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::logger(" ");
        sbs::io::logger(static_cast<uint64_t>(1));
        sbs::io::logger(static_cast<uint64_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::logger(static_cast<uint64_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::logger(" ");
        sbs::io::logger(static_cast<int64_t>(1));
        sbs::io::logger(static_cast<int64_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::logger(static_cast<int64_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::logger(" ");
        sbs::io::logger(1.0);
        SBS_TEST_OUT("totototo 10000000101 10000000101 100000000000000010001 100000000000000010001 10000000000000000000000000000000100000001 10000000000000000000000000000000100000001 100000000000000000000000000000000000000000000000000000000000000010000000000000001 100000000000000000000000000000000000000000000000000000000000000010000000000000001 1.00")
        SBS_RESET_OUT
    }
}

void other_test() {
    {
        SBS_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::error("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Warning);
        sbs::io::error("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Debug);
        sbs::io::error("foo");
        sbs::io::error(sbs::string{"foo"});
        sbs::io::error(static_cast<uint8_t>(1));
        sbs::io::error(static_cast<int8_t>(1));
        sbs::io::error(static_cast<uint16_t>(1));
        sbs::io::error(static_cast<int16_t>(1));
        sbs::io::error(static_cast<uint32_t>(1));
        sbs::io::error(static_cast<int32_t>(1));
        sbs::io::error(static_cast<uint64_t>(1));
        sbs::io::error(static_cast<int64_t>(1));
        sbs::io::error(1.0);
        SBS_TEST_OUT("ERROR fooERROR fooERROR fooERROR fooERROR 1ERROR 1ERROR 1ERROR 1ERROR 1ERROR 1ERROR 1ERROR 1ERROR 1.00")
        SBS_RESET_OUT
    }
    {
        SBS_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::warning("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Warning);
        sbs::io::warning("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Debug);
        sbs::io::warning("foo");
        sbs::io::warning(sbs::string{"foo"});
        sbs::io::warning(static_cast<uint8_t>(1));
        sbs::io::warning(static_cast<int8_t>(1));
        sbs::io::warning(static_cast<uint16_t>(1));
        sbs::io::warning(static_cast<int16_t>(1));
        sbs::io::warning(static_cast<uint32_t>(1));
        sbs::io::warning(static_cast<int32_t>(1));
        sbs::io::warning(static_cast<uint64_t>(1));
        sbs::io::warning(static_cast<int64_t>(1));
        sbs::io::warning(1.0);
        SBS_TEST_OUT("WARNING fooWARNING fooWARNING fooWARNING 1WARNING 1WARNING 1WARNING 1WARNING 1WARNING 1WARNING 1WARNING 1WARNING 1.00")
        SBS_RESET_OUT
    }
    {
        SBS_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::debug("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Warning);
        sbs::io::debug("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Debug);
        sbs::io::debug("foo");
        sbs::io::debug(sbs::string{"foo"});
        sbs::io::debug(static_cast<uint8_t>(1));
        sbs::io::debug(static_cast<int8_t>(1));
        sbs::io::debug(static_cast<uint16_t>(1));
        sbs::io::debug(static_cast<int16_t>(1));
        sbs::io::debug(static_cast<uint32_t>(1));
        sbs::io::debug(static_cast<int32_t>(1));
        sbs::io::debug(static_cast<uint64_t>(1));
        sbs::io::debug(static_cast<int64_t>(1));
        sbs::io::debug(1.0);
        SBS_TEST_OUT("DEBUG fooDEBUG fooDEBUG 1DEBUG 1DEBUG 1DEBUG 1DEBUG 1DEBUG 1DEBUG 1DEBUG 1DEBUG 1.00")
        SBS_RESET_OUT
    }
}

void float_test() {
    {
        SBS_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::logger(-1.0);
        sbs::io::logger(-1e35);
        sbs::io::logger(1e35);
        sbs::io::logger(10.0,0);
        sbs::io::logger(hnan);
        sbs::io::logger(hinf);
        SBS_TEST_OUT("-1.00ovfovf10naninf")
        SBS_RESET_OUT
    }
}

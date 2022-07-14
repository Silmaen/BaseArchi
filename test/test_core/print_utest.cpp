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
        SBS_START_REDIRECT_OUT
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
        SBS_TEST_OUT("");
        SBS_END_REDIRECT_OUT
    }
    {
        SBS_START_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::loggerln("toto");
        sbs::io::loggerln(sbs::string{"toto"});
        sbs::io::loggerln(static_cast<uint8_t>(1));
        sbs::io::loggerln(static_cast<uint8_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::loggerln(static_cast<uint8_t>(0xDE), sbs::io::IntFormat::Hexadecimal);
        sbs::io::loggerln(static_cast<int8_t>(1));
        sbs::io::loggerln(static_cast<int8_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::loggerln(static_cast<int8_t>(0x44), sbs::io::IntFormat::Hexadecimal);
        sbs::io::loggerln(static_cast<uint16_t>(1));
        sbs::io::loggerln(static_cast<uint16_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::loggerln(static_cast<uint16_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::loggerln(static_cast<int16_t>(1));
        sbs::io::loggerln(static_cast<int16_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::loggerln(static_cast<int16_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::loggerln(static_cast<uint32_t>(1));
        sbs::io::loggerln(static_cast<uint32_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::loggerln(static_cast<uint32_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::loggerln(static_cast<int32_t>(1));
        sbs::io::loggerln(static_cast<int32_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::loggerln(static_cast<int32_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::loggerln(static_cast<uint64_t>(1));
        sbs::io::loggerln(static_cast<uint64_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::loggerln(static_cast<uint64_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::loggerln(static_cast<int64_t>(1));
        sbs::io::loggerln(static_cast<int64_t>(1), sbs::io::IntFormat::Binary);
        sbs::io::loggerln(static_cast<int64_t>(1), sbs::io::IntFormat::Hexadecimal);
        sbs::io::loggerln(1.0);
        SBS_TEST_OUT("toto\ntoto\n1\n00000001\nDE\n1\n00000001\n44\n1\n0000000000000001\n0001\n1\n0000000000000001\n0001\n1\n00000000000000000000000000000001\n00000001\n1\n00000000000000000000000000000001\n00000001\n1\n0000000000000000000000000000000000000000000000000000000000000001\n0000000000000001\n1\n0000000000000000000000000000000000000000000000000000000000000001\n0000000000000001\n1.00\n");
        SBS_END_REDIRECT_OUT
    }
}

void other_test() {
    {
        SBS_START_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::errorln("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Warning);
        sbs::io::errorln("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Debug);
        sbs::io::error("foo");
        sbs::io::errorln(sbs::string{"foo"});
        sbs::io::errorln(static_cast<uint8_t>(1));
        sbs::io::errorln(static_cast<int8_t>(1));
        sbs::io::errorln(static_cast<uint16_t>(1));
        sbs::io::errorln(static_cast<int16_t>(1));
        sbs::io::errorln(static_cast<uint32_t>(1));
        sbs::io::errorln(static_cast<int32_t>(1));
        sbs::io::errorln(static_cast<uint64_t>(1));
        sbs::io::errorln(static_cast<int64_t>(1));
        sbs::io::errorln(1.0);
        SBS_TEST_OUT("ERROR foo\nERROR foo\nERROR foofoo\nERROR 1\nERROR 1\nERROR 1\nERROR 1\nERROR 1\nERROR 1\nERROR 1\nERROR 1\nERROR 1.00\n");
        SBS_END_REDIRECT_OUT
    }
    {
        SBS_START_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::warningln("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Warning);
        sbs::io::warningln("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Debug);
        sbs::io::warning("foo");
        sbs::io::warningln(sbs::string{"foo"});
        sbs::io::warningln(static_cast<uint8_t>(1));
        sbs::io::warningln(static_cast<int8_t>(1));
        sbs::io::warningln(static_cast<uint16_t>(1));
        sbs::io::warningln(static_cast<int16_t>(1));
        sbs::io::warningln(static_cast<uint32_t>(1));
        sbs::io::warningln(static_cast<int32_t>(1));
        sbs::io::warningln(static_cast<uint64_t>(1));
        sbs::io::warningln(static_cast<int64_t>(1));
        sbs::io::warningln(1.0);
        SBS_TEST_OUT("WARNING foo\nWARNING foofoo\nWARNING 1\nWARNING 1\nWARNING 1\nWARNING 1\nWARNING 1\nWARNING 1\nWARNING 1\nWARNING 1\nWARNING 1.00\n");
        SBS_END_REDIRECT_OUT
    }
    {
        SBS_START_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::debugln("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Warning);
        sbs::io::debugln("foo");
        sbs::io::setVerbosity(sbs::io::Verbosity::Debug);
        sbs::io::debug("foo");
        sbs::io::debugln(sbs::string{"foo"});
        sbs::io::debugln(static_cast<uint8_t>(1));
        sbs::io::debugln(static_cast<int8_t>(1));
        sbs::io::debugln(static_cast<uint16_t>(1));
        sbs::io::debugln(static_cast<int16_t>(1));
        sbs::io::debugln(static_cast<uint32_t>(1));
        sbs::io::debugln(static_cast<int32_t>(1));
        sbs::io::debugln(static_cast<uint64_t>(1));
        sbs::io::debugln(static_cast<int64_t>(1));
        sbs::io::debugln(1.0);
        SBS_TEST_OUT("DEBUG foofoo\nDEBUG 1\nDEBUG 1\nDEBUG 1\nDEBUG 1\nDEBUG 1\nDEBUG 1\nDEBUG 1\nDEBUG 1\nDEBUG 1.00\n");
        SBS_END_REDIRECT_OUT
    }
}

void float_test() {
    {
        SBS_START_REDIRECT_OUT
        sbs::io::setVerbosity(sbs::io::Verbosity::Error);
        sbs::io::logger(-1.0);
        sbs::io::logger(-1e35);
        sbs::io::logger(1e35);
        sbs::io::logger(10.0,0);
        sbs::io::logger(hnan);
        sbs::io::logger(hinf);
        SBS_TEST_OUT("-1.00ovfovf10naninf");
        SBS_END_REDIRECT_OUT
    }
}

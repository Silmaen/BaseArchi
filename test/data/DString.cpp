/**
 * @file data.cpp
 * @author argawaen
 * @date 02/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../testBase.h"
#include "data/DString.h"

void DString_constructor(){
    sys::data::DString test(F("coucou"));
    TEST_ASSERT_EQUAL_STRING("coucou",test.string().c_str());
    sys::data::DString test2("coucou");
    TEST_ASSERT_EQUAL_STRING("coucou",test2.c_str());
    sys::data::DString test3(sys::data::DString::internal_str{"coucou"});
    TEST_ASSERT_EQUAL_STRING("coucou",test3.c_str());
    TEST_ASSERT(test2 == test3)
    TEST_ASSERT_FALSE(test2 != test3)
    sys::data::DString test4 =sys::data::DString::internal_str{"coucou"};
    TEST_ASSERT(test2 == test4)
    sys::data::DString test5{test2};
    TEST_ASSERT(test2 == test5)
}

void DString_concatenation(){
    sys::data::DString test(F("coucou"));
    TEST_ASSERT_EQUAL_STRING("coucou copain", (test + " copain").c_str());
    TEST_ASSERT_EQUAL_STRING("coucou/copain", (test / "copain").c_str());
}

void DString_FloatNumber(){
    sys::data::DString test(31.2659);
    TEST_ASSERT_EQUAL_STRING("31.2659", test.c_str());
    test = sys::data::DString(7895623431.2659);
    TEST_ASSERT_EQUAL_STRING("7895623431.2659", test.c_str());
    test = sys::data::DString(0.000002659);
    TEST_ASSERT_EQUAL_STRING("2.659e-06", test.c_str());

    test = sys::data::DString(31.2659, sys::data::FloatFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("31.27", test.c_str());
    test = sys::data::DString(7895623431.2659, sys::data::FloatFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("7895623431.27", test.c_str());
    test = sys::data::DString(0.000002659, sys::data::FloatFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("0.00", test.c_str());

    test = sys::data::DString(31.2659, sys::data::FloatFormat::Scientific);
    TEST_ASSERT_EQUAL_STRING("3.13e+01", test.c_str());
    test = sys::data::DString(7895623431.2659, sys::data::FloatFormat::Scientific);
    TEST_ASSERT_EQUAL_STRING("7.90e+09", test.c_str());
    test = sys::data::DString(0.000002659, sys::data::FloatFormat::Scientific);
    TEST_ASSERT_EQUAL_STRING("2.66e-06", test.c_str());


    test = sys::data::DString(31.2659F);
    TEST_ASSERT_EQUAL_STRING("31.2659", test.c_str());
    test = sys::data::DString(8923.261F);
    TEST_ASSERT_EQUAL_STRING("8923.261", test.c_str());
    test = sys::data::DString(0.000002659F);
    TEST_ASSERT_EQUAL_STRING("2.659e-06", test.c_str());

    test = sys::data::DString(31.2659F, sys::data::FloatFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("31.27", test.c_str());
    test = sys::data::DString(89234.265F, sys::data::FloatFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("89234.27", test.c_str());
    test = sys::data::DString(0.000002659F, sys::data::FloatFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("0.00", test.c_str());

    test = sys::data::DString(31.2659F, sys::data::FloatFormat::Scientific);
    TEST_ASSERT_EQUAL_STRING("3.13e+01", test.c_str());
    test = sys::data::DString(89234.265F, sys::data::FloatFormat::Scientific);
    TEST_ASSERT_EQUAL_STRING("8.92e+04", test.c_str());
    test = sys::data::DString(0.000002659F, sys::data::FloatFormat::Scientific);
    TEST_ASSERT_EQUAL_STRING("2.66e-06", test.c_str());
}

void DString_Int8Number(){
    uint8_t testInt = 186;
    sys::data::DString test(testInt);
    TEST_ASSERT_EQUAL_STRING("186", test.c_str());
    test = sys::data::DString(static_cast<uint8_t>(52U), sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("00110100", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("10111010", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Octal);
    TEST_ASSERT_EQUAL_STRING("0272", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("186", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Hexadecimal);
    TEST_ASSERT_EQUAL_STRING("ba", test.c_str());
    int8_t sTestInt = -27;
    sys::data::DString sTest(sTestInt);
    TEST_ASSERT_EQUAL_STRING("-27", sTest.c_str());
    sTest = sys::data::DString(static_cast<int8_t>(52), sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("00110100", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("11100101", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Octal);
    TEST_ASSERT_EQUAL_STRING("0345", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("-27", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Hexadecimal);
    TEST_ASSERT_EQUAL_STRING("e5", sTest.c_str());
}

void DString_Int16Number(){
    uint16_t testInt = 186;
    sys::data::DString test(testInt);
    TEST_ASSERT_EQUAL_STRING("186", test.c_str());
    test = sys::data::DString(static_cast<uint16_t>(52U), sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("0000000000110100", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("0000000010111010", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Octal);
    TEST_ASSERT_EQUAL_STRING("00000272", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("186", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Hexadecimal);
    TEST_ASSERT_EQUAL_STRING("00ba", test.c_str());
    int16_t sTestInt = -27;
    sys::data::DString sTest(sTestInt);
    TEST_ASSERT_EQUAL_STRING("-27", sTest.c_str());
    sTest = sys::data::DString(static_cast<int16_t>(52), sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("0000000000110100", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("1111111111100101", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Octal);
    TEST_ASSERT_EQUAL_STRING("00177745", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("-27", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Hexadecimal);
    TEST_ASSERT_EQUAL_STRING("ffe5", sTest.c_str());
}

void DString_Int32Number(){
    uint32_t testInt = 186;
    sys::data::DString test(testInt);
    TEST_ASSERT_EQUAL_STRING("186", test.c_str());
    test = sys::data::DString(static_cast<uint32_t>(52U), sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("00000000000000000000000000110100", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("00000000000000000000000010111010", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Octal);
    TEST_ASSERT_EQUAL_STRING("0000000000000272", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("186", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Hexadecimal);
    TEST_ASSERT_EQUAL_STRING("000000ba", test.c_str());
    int32_t sTestInt = -27;
    sys::data::DString sTest(sTestInt);
    TEST_ASSERT_EQUAL_STRING("-27", sTest.c_str());
    sTest = sys::data::DString(static_cast<int32_t>(52), sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("00000000000000000000000000110100", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("11111111111111111111111111100101", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Octal);
    TEST_ASSERT_EQUAL_STRING("0000037777777745", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("-27", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Hexadecimal);
    TEST_ASSERT_EQUAL_STRING("ffffffe5", sTest.c_str());
}

void DString_Int64Number(){
    uint64_t testInt = 186;
    sys::data::DString test(testInt);
    TEST_ASSERT_EQUAL_STRING("186", test.c_str());
    test = sys::data::DString(static_cast<uint64_t>(52U), sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("0000000000000000000000000000000000000000000000000000000000110100", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("0000000000000000000000000000000000000000000000000000000010111010", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Octal);
    TEST_ASSERT_EQUAL_STRING("00000000000000000000000000000272", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("186", test.c_str());
    test = sys::data::DString(testInt, sys::data::IntFormat::Hexadecimal);
    TEST_ASSERT_EQUAL_STRING("00000000000000ba", test.c_str());
    int64_t sTestInt = -27;
    sys::data::DString sTest(sTestInt);
    TEST_ASSERT_EQUAL_STRING("-27", sTest.c_str());
    sTest = sys::data::DString(static_cast<int64_t>(52), sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("0000000000000000000000000000000000000000000000000000000000110100", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Binary);
    TEST_ASSERT_EQUAL_STRING("1111111111111111111111111111111111111111111111111111111111100101", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Octal);
    TEST_ASSERT_EQUAL_STRING("00000000001777777777777777777745", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Decimal);
    TEST_ASSERT_EQUAL_STRING("-27", sTest.c_str());
    sTest = sys::data::DString(sTestInt, sys::data::IntFormat::Hexadecimal);
    TEST_ASSERT_EQUAL_STRING("ffffffffffffffe5", sTest.c_str());
}

void DString_BadFormat(){
    sys::data::DString test(static_cast<uint64_t>(52U),sys::data::IntFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
    test = sys::data::DString(static_cast<int64_t>(52), sys::data::IntFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
     test = sys::data::DString(static_cast<uint32_t>(52U),sys::data::IntFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
    test = sys::data::DString(static_cast<int32_t>(52), sys::data::IntFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
    test = sys::data::DString(static_cast<uint16_t>(52U),sys::data::IntFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
    test = sys::data::DString(static_cast<int16_t>(52), sys::data::IntFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
    test = sys::data::DString(static_cast<uint8_t>(52U),sys::data::IntFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
    test = sys::data::DString(static_cast<int8_t>(52), sys::data::IntFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
    test = sys::data::DString(static_cast<float>(52U),sys::data::FloatFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
    test = sys::data::DString(static_cast<double>(52), sys::data::FloatFormat{-1});
    TEST_ASSERT_EQUAL_STRING("", test.c_str());
}

void runTests(){
    UNITY_BEGIN();
    RUN_TEST(DString_constructor);
    RUN_TEST(DString_concatenation);
    RUN_TEST(DString_FloatNumber);
    RUN_TEST(DString_Int8Number);
    RUN_TEST(DString_Int16Number);
    RUN_TEST(DString_Int32Number);
    RUN_TEST(DString_Int64Number);
    RUN_TEST(DString_BadFormat);
    UNITY_END();
}

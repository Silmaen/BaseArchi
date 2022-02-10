/**
 * @file system.cpp
 * @author argawaen
 * @date 04/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../testBase.h"
#include <base/System.h>
#include <io/StringOutput.h>
#include <io/StringInput.h>

void System_constructor(){
    auto hardware = sys::base::System::getInstance();
    TEST_ASSERT_NOT_NULL(hardware);
    hardware->setup();
    TEST_ASSERT_FALSE(hardware->doReset())
#ifdef HAS_SMART_PTR
    hardware->pushOutput(std::shared_ptr<sys::io::Output>(new sys::io::StringOutput()));
    hardware->pushInput(std::shared_ptr<sys::io::Input>(new sys::io::StringInput()));
#else
    hardware->pushOutput(new sys::io::StringOutput());
    hardware->pushInput(new sys::io::StringInput());
#endif
    hardware->loop();
    hardware->requestReset();
    TEST_ASSERT(hardware->doReset())
}

void System_echo(){
    auto hardware = sys::base::System::getInstance();
    // test bad io names
    TEST_ASSERT_NULL(hardware->getInput(F("toto")))
    TEST_ASSERT_NULL(hardware->getOutput(F("toto")))
    // get string input
    auto inputTemp = hardware->getInput(F("String"));
    TEST_ASSERT_NOT_NULL(inputTemp);
#ifdef HAS_SMART_PTR
    auto input = std::static_pointer_cast<sys::io::StringInput>(inputTemp);
#else
    auto input = static_cast<sys::io::StringInput*>(inputTemp);
#endif
    TEST_ASSERT_NOT_NULL(input);
    input->flush();
    // get string output
    auto outputTemp = hardware->getOutput(F("String"));
    TEST_ASSERT_NOT_NULL(outputTemp);
#ifdef HAS_SMART_PTR
    auto output = std::static_pointer_cast<sys::io::StringOutput>(outputTemp);
#else
    auto output = static_cast<sys::io::StringOutput*>(outputTemp);
#endif
    TEST_ASSERT_NOT_NULL(output);

    // push a message into input
    input->pushToBuffer(F("Hello world!"));
    // do a single loop: system should the input (and flush it) and echo in the output
    hardware->loop();
    // test message read
    TEST_ASSERT_FALSE(input->available());
    // test message echoed in output
    TEST_ASSERT_EQUAL_STRING("String> Hello world!\n", output->getBuffer().c_str());
}

void runTests(){
    UNITY_BEGIN();
    RUN_TEST(System_constructor);
    RUN_TEST(System_echo);
    UNITY_END();
}

/**
 * @file SerialDriver.cpp
 * @author argawaen
 * @date 13/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "SerialDriver.h"
#include "SerialInput.h"
#include "SerialOutput.h"
#include <base/System.h>
#ifdef ARDUINO
#include <Arduino.h>
#endif

namespace sys::io {

void SerialDriver::setup() {
#ifdef ARDUINO
    Serial.begin(115200);
#endif
    auto hardware = base::System::getInstance();
    auto output   = base::core::SharedPtr<Output>(new SerialOutput());
    hardware->pushOutput(output);
    hardware->pushInput(base::core::SharedPtr<Input>(new SerialInput()));
#ifdef ESP8266
    output->println(F(""));
#endif
}

}// namespace sys::io

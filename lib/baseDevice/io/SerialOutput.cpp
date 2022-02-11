/**
 * @file SerialOutput.cpp
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <iostream>
#endif
#include "SerialOutput.h"

namespace sys::io {

void SerialOutput::print(const sys::data::DString& str) {
#ifdef ARDUINO
    Serial.print(str.string());
#else
    std::cout << str.string();
#endif
}

}// namespace sys::io

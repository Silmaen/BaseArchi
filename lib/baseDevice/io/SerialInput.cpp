/**
 * @file SerialInput.cpp
 * @author argawaen
 * @date 10/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#ifdef ARDUINO
#include <Arduino.h>
#endif
#include "SerialInput.h"

bool sys::io::SerialInput::available() const {
#ifdef ARDUINO
    return Serial.available()>0;
#else
    return false;
#endif
}

sys::data::DString sys::io::SerialInput::getLine() {
#ifdef ARDUINO
    return Serial.readStringUntil('\n');
#else
    return {};
#endif
}

void sys::io::SerialInput::flush() {
#ifdef ARDUINO
    while (Serial.available()>0)
        Serial.read();
#endif
}

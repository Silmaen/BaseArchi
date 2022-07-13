/**
 * @file sbsMain.cpp
 * @author Silmaen
 * @date 05/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../sbs.h"
#include "core/Print.h"

/// If the main loop should continue
static bool looping   = true;
/// The return code
static int returnCode = 0;

namespace sbs {

void setExecReturn(int _returnCode) {
    returnCode = _returnCode;
}

void killLoop() {
    looping = false;
}

}// namespace sbs

#ifdef ARDUINO

#include <Arduino.h>

void setup() {
    sbs::io::logger("System Starting");
    sbs::setup();
    sbs::io::logger("System Started");
}

void loop() {
    sbs::loop();
    if (!looping) {
        looping = true;
        sbs::io::logger("Return Code: ");
        sbs::io::logger(returnCode);
        sbs::io::logger("\n");
        setup();
    }
}
#else
/**
 * @brief Main entry point for non-Arduino builds
 * @return Return code
 */
int main() {
    sbs::io::logger("System Starting");
    sbs::setup();
    sbs::io::logger("System Started");
    while (looping) {
        sbs::loop();
    }
    sbs::io::logger("Return Code: ");
    sbs::io::logger(returnCode);
    sbs::io::logger("\n");
    return returnCode;
}
#endif

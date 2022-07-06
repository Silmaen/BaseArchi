/**
 * @file sbsMain.cpp
 * @author argawaen
 * @date 05/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../sbs.h"
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

void setup() {
    sbs::setup();
}

void loop() {
    sbs::loop();
    if (!looping) {
        looping = true;
        Serial.print("Return Code: ");
        Serial.println(returnCode);
        setup();
    }
}
#else
/**
 * @brief Main entry point for non-Arduino builds
 * @return Return code
 */
int main() {
    sbs::setup();
    while (looping) {
        sbs::loop();
    }
    return returnCode;
}
#endif

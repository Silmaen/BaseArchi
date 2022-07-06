/**
 * @file test_base.h
 * @author Silmaen
 * @date 09/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "test_helper.h"

int runtest();

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

#ifdef ARDUINO

void sbs::setup() {
    // should be the same value as for the `test_speed` option in "platformio.ini"
    // default value is test_speed=115200
    Serial.begin(115200);

    sbs::delay(2000);

    setExecReturn(runtest());
}

void sbs::loop() {
    killLoop();
}

#else

void sbs::setup(){
    sbs::setExecReturn(runtest());
}

void sbs::loop() {
    sbs::killLoop();
}

#endif
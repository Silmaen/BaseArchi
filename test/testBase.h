/**
 * @file testBase.h
 * @author Silmaen
 * @date 02/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include "testHelper.h"

#ifdef ARDUINO
#include <Arduino.h>
/**
 * @brief Initialization function
 */
void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);
    runTests();
}

/**
 * @brief Iteration of the infinite loop
 */
void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
#else
int main() {
    runTests();
    return 0;
}
#endif

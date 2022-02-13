/**
* @file main.cpp
* @author argawaen
* @date 01/02/2022
* Copyright © 2022 All rights reserved.
* All modification must get authorization from the author.
*/
#ifdef ARDUINO
#include <Arduino.h>
#endif
#include <base/System.h>

/**
 * @brief Initialization function
 */
void setup() {
    sys::base::System::getInstance()->setup();
}

/**
 * @brief Iteration of the infinite loop
 */
void loop() {
    auto hardware = sys::base::System::getInstance();
    hardware->loop();
#ifdef ARDUINO
    if (hardware->doReset())
        setup();
#endif
}

#ifndef ARDUINO
#include <io/StringOutput.h>
#include <io/StringInput.h>

/**
 * @brief Main entry point
 * @retval 0
 */
int main(){
    auto hardware = sys::base::System::getInstance();
    hardware->setup();
    // get string input
    auto inputTemp = hardware->getInput(F("String"));
    auto input = inputTemp.cast<sys::io::StringInput>();
    input->pushToBuffer("coucou");
    hardware->loop();
    return 0;
}
#endif

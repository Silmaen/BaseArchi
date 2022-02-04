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

/// Hardware device
sys::base::System hardware;

/**
 * @brief Initialization function
 */
void setup() {
    hardware.setup();
}

/**
 * @brief Iteration of the infinite loop
 */
void loop() {
    hardware.loop();
#ifdef ARDUINO
    if (hardware.doReset())
        setup();
#endif
}

#ifndef ARDUINO
/**
 * @brief Main entry point
 * @retval 0
 */
int main(){
    setup();
    while (!hardware.doReset()){
        loop();
    }
    return 0;
}
#endif
